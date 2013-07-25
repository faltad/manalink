#include <exception>
#include <iostream>
#include <stdexcept>
#include "SaveManager.h"

const char   *SaveManager::DEFAULT_FILENAME = "save.mana";

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

void		SaveManager::generateSaveData(Category *cat, std::string &data, bool printNameCat) {
  std::list<Category *>			listCat;
  std::list<Category *>::const_iterator	it;
  listPairString::const_iterator	itPair;
  listPairString			listLinks;

  listCat = cat->getListCategories();
  listLinks = cat->getListLinks();
  it = listCat.begin();
  itPair = listLinks.begin();
  if (printNameCat == true) {
    data += "{" + cat->getName() + "}{";
  }
  while (it != listCat.end()) {
    generateSaveData(*it, data, true);
    it++;
  }
  while (itPair != listLinks.end()) {
    data += "{" + (*itPair).first + "}{" + (*itPair).second + "}";
    itPair++;
  }
  if (printNameCat == true) {
    data += "}";
  }
}

std::string	SaveManager::saveFile(Category *root) {
  std::string	data;

  generateSaveData(root, data, false);
  return data;
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
    str = removeSpaces(str);
    if (str.length() > 0) {
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
