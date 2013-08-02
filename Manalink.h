#ifndef MANALINK_H_
#define MANALINK_H_

#include "Category.h"
#include "Window.h"

class Manalink
{
 private:
  Window	*win;
  Category	*preCat;
  bool		linkState;

 public:
  Manalink(void);
  ~Manalink(void);
  void	run(Category *);
 private:
  void	displayCategories(Category *cat);
  void	displayLinks(Category *cat);
  pairString	getElementFromList(int n, listPairString l);
  Category	*getElementFromList(int n, std::list<Category *> l);
  void	displayNewCat(Category *cat);
  void	handleBackspace(void);
  Category	*handleSelection(Category *cat);
};

#endif
