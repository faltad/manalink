#ifndef CATEGORY_H_
#define CATEGORY_H_

#include <list>
#include <string>
#include <utility>

typedef std::list<std::pair<std::string, std::string> > listPairString;
typedef std::pair<std::string, std::string> pairString;

class Category
{
 private:
  std::list<Category *>	listCategories;
  std::string		name;
  listPairString	listLinks;
  Category		*preCat;
  
 public:
  Category(const std::string &name);
  Category(const char *name);
  void	addLink(const std::string &name, const std::string &content);
  Category *addNewCategory(std::string name);
  void	debugLinks(int level) const;
  const std::string	&getName(void) const;
  std::list<Category *>	getListCategories(void) const;
  listPairString	getListLinks(void) const;
  Category *getParent(void) const;
  void	deleteElementFromList(unsigned int offset, std::list<Category *> l);
  void	deleteElementFromList(unsigned int offset, listPairString l);
  void	deleteLink(unsigned int offset);
  void	deleteCategory(unsigned int offset);

 private:
  void setParent(Category *parent);
  void	deleteAllCategories(void);
};
#endif
