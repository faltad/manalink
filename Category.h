#ifndef CATEGORY_H_
#define CATEGORY_H_

#include <list>
#include <string>
#include <utility>

typedef std::list<std::pair<std::string, std::string> > listPairString;

class Category
{
 private:
  std::list<Category *>	listCategories;
  std::string		name;
  listPairString	listLinks;
  
 public:
  Category(const std::string &name);
  Category(const char *name);
  void	addLink(const std::string &name, const std::string &content);
  Category *addNewCategory(std::string name);
  void	debugLinks(int level) const;
  const std::string	&getName(void) const;
  std::list<Category *>	getListCategories(void) const;
  listPairString	getListLinks(void) const;
};

#endif
