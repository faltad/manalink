#ifndef MANALINK_H_
#define MANALINK_H_

#include "Category.h"
#include "SaveManager.h"
#include "Window.h"

class Manalink
{
 private:
  Window	*win;
  Category	*preCat;
  bool		linkState;
  bool		modified;

 public:
  Manalink(void);
  ~Manalink(void);
  void	run(Category *, SaveManager &);
 private:
  void	displayCategories(Category *cat);
  void	displayLinks(Category *cat);
  pairString	getElementFromList(int n, listPairString l);
  Category	*getElementFromList(int n, std::list<Category *> l);
  void	displayNewCat(Category *cat);
  Category	*handleBackspace(Category *cat);
  Category	*handleSelection(Category *cat);
  void		 handleRemoveItem(Category *cat);
  void		 handleNewCategory(Category *cat);
  void		 handleHelp(Category *cat);
  void		 handleSave(Category *root, SaveManager &saveManager);
};

#endif
