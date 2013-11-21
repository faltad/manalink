#ifndef SAVEMANAGER_H_
#define SAVEMANAGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include "Category.h"

class SaveManager
{

 public:
  static const char	*DEFAULT_FILENAME;
 private:
  Category	*cat;
  std::fstream	file;
  const	std::string	_filename;

 public:
  SaveManager(const char *filename);
  ~SaveManager();
  Category *	getCategories(void);
  std::string	saveFile(Category *root);

 private:
  std::string	removeSpaces(const std::string &str) const;
  void		parseLine(std::string buff, Category *cat);
  void		generateSaveData(Category *cat, std::string &data, bool printNameCat);
};

#endif
