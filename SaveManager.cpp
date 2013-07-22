#include <exception>
#include <iostream>
#include <stdexcept>
#include "SaveManager.h"

const char	*DEFAULT_FILENAME = "save.mana";

SaveManager::SaveManager(const char *filename) {
  file.open(filename);
  if (!file.good())
    throw std::invalid_argument(std::string(filename) + " cannot be open");
}

SaveManager::~SaveManager() {
  file.close();
}

std::string	SaveManager::removeSpaces(const std::string &str) const {
  unsigned int	count;

  count = 0;
  while ((str[count] == ' ' || str[count] == '\t' || str[count] == '\n') &&
	 str.length() >= count) {
    count++;
  }
  return str.substr(count);
}

void		SaveManager::parseLine(std::string buff, Category *cat) {
  bool		isName;
  std::string	name;
  std::string   str;

  isName = true;
  while (!file.eof()) {
    if (buff == "") {
      std::getline(file, str, '}');
    }
    else {
      str = buff;
      buff = "";
    }
    if (str == "")
      return;
    if (str.length() > 0) {
      str = removeSpaces(str);
      if (isName == true) {
	if (str[1] == '{') {
	  throw std::invalid_argument("The save file is corrupted");
	}
	name = str.substr(1);
	isName = false;
      } else {
	if (str[1] == '{') {
	  parseLine(str.substr(1), cat->addNewCategory(name));
	} else {
	  cat->addLink(name, str.substr(1));
	}
	isName = true;
      }
    }
  }
}

Category	*SaveManager::getCategories(void) {
  Category	*root;
  std::string	str;

  root = new Category("/");
  parseLine("", root);
  return root;
}
