#ifndef WINDOW_H_
#define WINDOW_H_

#include <curses.h>
#include <string>
#include <vector>

#include "Category.h"

class Window
{
 private:
  WINDOW	*top;
  WINDOW	*bot;
  int		row;
  int		col;
  int		cursorPos;
  std::vector<std::string>	vStr;
  int				vSize;
  void		(Window::*funcDisplay)(std::string *);

 public:
  Window(void);
  ~Window(void);
  int	getChar(void);
  void	putChar(int c);
  void	welcome(void);
  void	print(void);
  void	addStrToBuffer(std::string str);
  void  updateCursorPos(int);
  const int getCursorPos(void) const;
  void	clear(void);
  void  clearList(void);
  void	printLink(pairString p);
  void	displayBot(const std::string &str);
  std::string	*getString(int c);
  void	setupWritingBot(void);

 private:
  WINDOW *createNewWin(int height, int width, int starty, int startx);
  void	writingBotManagement(std::string *buff);
};

#endif
