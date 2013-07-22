#include <exception>
#include <iostream>
#include "Category.h"
#include "SaveManager.h"

int main(int ac, char **av) {
  const char	*filename;

  if (ac > 1) {
    filename = av[1];
  } else {
    filename = DEFAULT_FILENAME;
  }
  
  try {
    SaveManager saveManager(filename);
    Category	*root;

    root = saveManager.getCategories();
    root->debugLinks();
  }
  catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
