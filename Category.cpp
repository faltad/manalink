#include <iostream>
#include <utility>

#include "Category.h"

Category::Category(std::string &name) {
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

void Category::debugLinks(void) const {
  std::list<std::pair<std::string, std::string> >::const_iterator it = listLinks.begin();

  while (it != listLinks.end()) {
    std::cout << "Name : " << (*it).first << "  description: " << (*it).second << std::endl;
    it++;
  }
}
