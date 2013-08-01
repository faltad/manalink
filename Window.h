#ifndef WINDOW_H_
#define WINDOW_H_

#include <curses.h>
#include <string>
#include <vector>

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

 public:
  Window(void);
  ~Window(void);
  int	getChar(void);
  void	putChar(int c);
  void	welcome(void);
  void	print(void);
  void	addStrToBuffer(std::string str);
  void  updateCursorPos(int);

 private:
  WINDOW *createNewWin(int height, int width, int starty, int startx);
};

#endif
