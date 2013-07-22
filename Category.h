#ifndef CATEGORY_H_
#define CATEGORY_H_

#include <list>
#include <string>
#include <utility>


class Category
{
 private:
  std::list<Category *>	listCategories;
  std::string		name;
  std::list<std::pair<std::string, std::string> > listLinks;
  
 public:
  Category(std::string &name);
  Category(const char *name);
  void	addLink(const std::string &name, const std::string &content);
  Category *addNewCategory(std::string name);
  void	debugLinks(int level) const;
  const std::string	&getName(void) const;
};

#endif
