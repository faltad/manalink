#include <exception>
#include <iostream>
#include "Category.h"
#include "Manalink.h"
#include "SaveManager.h"

int main(int ac, char **av) {
  const char	*filename;

  if (ac > 1) {
    filename = av[1];
  } else {
    filename = SaveManager::DEFAULT_FILENAME;
  }
  
  try {
    SaveManager saveManager(filename);
    Category	*root;
    Manalink	manalink;

    root = saveManager.getCategories();
    manalink.run(root);
  }
  catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
  return 0;
}
