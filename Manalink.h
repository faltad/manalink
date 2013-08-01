#ifndef MANALINK_H_
#define MANALINK_H_

#include "Category.h"
#include "Window.h"

class Manalink
{
 private:
  Window	*win;

 public:
  Manalink(void);
  ~Manalink(void);
  void	run(Category *);
 private:
  void	displayCategories(Category *cat);
  void	displayLinks(Category *cat);


};

#endif
