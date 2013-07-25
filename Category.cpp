#include <iostream>
#include <utility>

#include "Category.h"

Category::Category(const std::string &name) {
  this->name = name;
}

Category::Category(const char *name) {
  this->name = std::string(name);
}

void Category::addLink(const std::string &name, const std::string &content) {
  std::pair<std::string, std::string> linkPair;
  linkPair = std::make_pair(name, content);
  listLinks.push_back(linkPair);
}

void Category::debugLinks(int level) const {
  listPairString::const_iterator it = listLinks.begin();
  std::list<Category *>::const_iterator itList = listCategories.begin();

  std::cout << std::string(level, '-') << " " << this->name << std::endl;
  while (itList != listCategories.end()) {
    (*itList)->debugLinks(level + 1);
    itList++;
  }
  while (it != listLinks.end()) {
    std::cout << std::string(level + 1, '-') << " Name : " << (*it).first << "  description: " << (*it).second << std::endl;
    it++;
  }
}

Category	*Category::addNewCategory(std::string name) {
  Category	*cat;

  cat = new Category(name);
  listCategories.push_back(cat);
  return cat;
}

const std::string	&Category::getName(void) const {
  return name;
}

std::list<Category *>	Category::getListCategories(void) const {
  return listCategories;
}


listPairString		Category::getListLinks(void) const {
  return listLinks;
}
