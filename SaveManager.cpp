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


Category	*SaveManager::getCategories(void) {
  Category	*root;
  Category	*currentCat;
  std::string	str;
  std::string	name;
  bool		isName;

  isName = true;
  root = new Category("/");
  currentCat = root;

  while (!file.eof()) {
    std::getline(file, str, '}');
    if (str.length() > 0) {
      if (isName == true) {
	if (str == "" || str[1] == '{') {
	  throw std::invalid_argument("The save file is corrupted");
	}
	name = str.substr(1);
	isName = false;
      } else {
	if (str[1] == '{') {
	  
	} else {
	  currentCat->addLink(name, str.substr(1));
	}
	isName = true;
      }
    }
  }
  return root;
}
