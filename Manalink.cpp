#include "Manalink.h"

#include <curses.h>
#include <iostream>

Manalink::Manalink(void) {
  win = NULL;
}

void	Manalink::displayCategories(Category *cat) {
  std::list<Category *> listCategories = cat->getListCategories();
  std::list<Category *>::const_iterator itList = listCategories.begin();
  std::string				buff;

  while (itList != listCategories.end()) {
    buff = (*itList)->getName() + " >";
    win->addStrToBuffer(buff);
    itList++;
  }
}

void	Manalink::displayLinks(Category *cat) {
  listPairString		listLinks = cat->getListLinks();
  listPairString::const_iterator it = listLinks.begin();

  while (it != listLinks.end()) {
    win->addStrToBuffer((*it).first);
    it++;
  }
}

void	Manalink::run(Category *cat) {
  int	c;
  bool flag = true;

  win = new Window();
  win->welcome();
  displayCategories(cat);
  displayLinks(cat);
  win->print();
  while (flag) {
    c = win->getChar();
    if (c == KEY_UP || c == KEY_DOWN) {
      win->updateCursorPos(c);
    } else {
      win->putChar(c);
    }
    refresh();
  }
}

Manalink::~Manalink(void) {
  if (win != NULL)
    delete win;
}
