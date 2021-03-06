#include "Category.h"
#include "Manalink.h"

#include <curses.h>
#include <exception>
#include <iostream>
#include <stdexcept>

Manalink::Manalink(void) : win(NULL) {
  linkState = false;
  modified = false;
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
  //win->addStrToBuffer(std::string(COLS - 5, '-'));
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
    
  win->clear();
  offset = win->getCursorPos();
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
      displayNewCat(cat);
    }
  } else {
    preCat = cat;
    newCat = getElementFromList(offset, listCategories);
    displayNewCat(newCat);
    cat = newCat;
  }
  return cat;
}

void	Manalink::handleRemoveItem(Category *cat) {
  int	c;
  unsigned int	offset;
  listPairString	listLinks = cat->getListLinks();
  std::list<Category *>	listCategories = cat->getListCategories();

  win->displayBot("Are you sure you want to remove this item? Y/[n]");
  c = win->getChar();
  if (c == 'y' || c == 'Y') {
    win->clear();
    offset = win->getCursorPos();
    if (offset + 1 > listCategories.size()) {
      offset -= listCategories.size();
      if (offset < listLinks.size()) {
	cat->deleteLink(offset);
      } else {
	throw std::invalid_argument("Link list index out of boundaries");
      }
    } else {
      cat->deleteCategory(offset);
    }
    this->modified = true;
    displayNewCat(cat);
  } else {
    win->welcome();
  }
}

void	Manalink::handleNewCategory(Category *cat) {
  std::string	*str;

  win->displayBot("New category: ");
  win->setupWritingBot();
  str = win->getString(10);
  cat->addNewCategory(*str);
  this->modified = true;
  displayNewCat(cat);
  delete str;
}

void	Manalink::handleHelp(Category *cat) {
  win->displayBot("Help) c:new category, r:remove, n:new link, s:save");
}

void	Manalink::handleSave(Category *root, SaveManager &saveManager) {
  int	c;

  win->displayBot("Save? Y/[n]");
  c = win->getChar();
  if (c == 'y' || c == 'Y') {
    win->displayBot("Saved!");
    this->modified = false;
    saveManager.saveFile(root);	
  } else {
    win->displayBot("Canceled");
  }
}

void	Manalink::run(Category *cat, SaveManager &saveManager) {
  int	c;
  Category *root = cat;
  bool flag = true;

  win = new Window();
  preCat = cat;
  displayNewCat(cat);
  while (flag) {
    c = win->getChar();
    win->welcome();
    if ((c == KEY_UP || c == KEY_DOWN) && linkState == false) {
      win->updateCursorPos(c);
    } else if ((c == 10 || c == KEY_RIGHT) && linkState == false) {
      cat = handleSelection(cat);
    } else if (c == 8 || c == 127 || c == KEY_LEFT) { // backspace
      cat = handleBackspace(cat);
    } else if (c == 'r' && linkState == false) {
      handleRemoveItem(cat);
    } else if (c == 'c' && linkState == false) {
      handleNewCategory(cat);
    } else if (c == 'h') {
      handleHelp(cat);
    } else if (c == 's') {
      handleSave(root, saveManager);
    } else if (c == 'q') { // quit
      if (this->modified == true)
	handleSave(root, saveManager);
      flag = false;
    }
    refresh();
  }
}

Manalink::~Manalink(void) {
  delete win;
}
