#ifndef SAVEMANAGER_H_
#define SAVEMANAGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Category.h"

extern const char	*DEFAULT_FILENAME;

class SaveManager
{
 private:
  Category	*cat;
  std::ifstream	file;

 public:
  SaveManager(const char *filename);
  ~SaveManager();
  Category *	getCategories(void);

 private:
  std::string	removeSpaces(const std::string &str) const;
  void		parseLine(std::string buff, Category *cat);
};

#endif
