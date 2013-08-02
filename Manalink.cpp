#include "Category.h"
#include "Manalink.h"

#include <curses.h>
#include <exception>
#include <iostream>
#include <stdexcept>

Manalink::Manalink(void) : win(NULL) {
  linkState = false;
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

pairString	Manalink::getElementFromList(int n, listPairString l) {
  listPairString::const_iterator it = l.begin();
  int				 i;

  for (i = 0; it != l.end() && i <= n; it++) {
    if (i == n)
      return (*it);
    i++;
  }
  return *(l.begin()); 
}

Category	*Manalink::getElementFromList(int n, std::list<Category *> l) {
  std::list<Category *>::const_iterator it = l.begin();
  int				 i;

  for (i = 0; it != l.end() && i <= n; it++) {
    if (i == n)
      return (*it);
    i++;
  }
  return *(l.begin());
}

void	Manalink::displayNewCat(Category *cat) {
  win->clear();
  win->clearList();
  win->welcome();
  displayCategories(cat);
  displayLinks(cat);
  win->print();
}


// Move to the parent category
// or reprint the current category if the current state
// is to show links
Category	*Manalink::handleBackspace(Category *cat) {
  Category *prevCat;

  if (linkState == true) {
    win->clear();
    win->welcome();
    win->print();
    linkState = false;
  } else {
    prevCat = cat->getParent();
    if (prevCat != cat) {
      cat = prevCat;
      displayNewCat(cat);
    }
  }
  return cat;
}

// if the user clicks on a category, change the cat argument
// if the user clicks on a link, it will simply print it
Category	*Manalink::handleSelection(Category *cat) {
  listPairString	listLinks = cat->getListLinks();
  std::list<Category *>	listCategories = cat->getListCategories();
  pairString	pStr;
  Category *   newCat;
  unsigned int	offset;
    
  offset = win->getCursorPos();
  win->clear();
  if (offset + 1 > listCategories.size()) {
    offset -= listCategories.size();
    if (offset < listLinks.size()) {
      preCat = cat;    
      pStr = getElementFromList(offset, listLinks);
      win->clear();
      win->welcome();
      win->printLink(pStr);
      linkState = true;
    } else {
      throw std::invalid_argument("Link list index out of boundaries");
    }
  } else {
    preCat = cat;
    newCat = getElementFromList(offset, listCategories);
    displayNewCat(newCat);
    cat = newCat;
  }
  return cat;
}

void	Manalink::run(Category *cat) {
  int	c;
  bool flag = true;

  win = new Window();
  preCat = cat;
  displayNewCat(cat);
  while (flag) {
    c = win->getChar();
    if ((c == KEY_UP || c == KEY_DOWN) && linkState == false) {
      win->updateCursorPos(c);
    } else if ((c == 10 || c == KEY_RIGHT) && linkState == false) {
      cat = handleSelection(cat);
    } else if (c == 8 || c == 127) { // backspace
      cat = handleBackspace(cat);
    } else if (c == 'q') { // quit
      flag = false;
    }
    refresh();
  }
}

Manalink::~Manalink(void) {
  delete win;
}
