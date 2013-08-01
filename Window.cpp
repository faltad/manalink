#include "Window.h"

#include <curses.h>
#include <clocale>
#include <string>

Window::Window(void) {
  setlocale(LC_ALL, "UTF-8");
  initscr();
  cbreak();
  noecho();
  intrflush(stdscr, false);
  keypad(stdscr, true);
  start_color();
  init_pair(1 ,COLOR_BLACK, COLOR_WHITE);
  getmaxyx(stdscr, row, col);
  top = subwin(stdscr, 1, col, 0, 0);
  bot = subwin(stdscr, 1, col, row - 1, 0);
  vSize = 0;
  curs_set(0);
  cursorPos = 0;
}

WINDOW *Window::createNewWin(int height, int width, int starty, int startx)
{
  WINDOW *localWin;

  localWin = newwin(height, width, starty, startx);
  wrefresh(localWin);
  return localWin;
}

Window::~Window(void) {
  delwin(top);
  delwin(bot);
  endwin();
}

int	Window::getChar(void) {
  return wgetch(stdscr);
}

void	Window::putChar(int c) {
  mvwaddch(stdscr, 5, 5, c);
}

void	Window::addStrToBuffer(std::string str) {
  vStr.push_back(str);
  vSize++;
}

void	Window::print(void) {
  std::vector<std::string>::const_iterator it;
  int		currentLine;

  it = vStr.begin();
  currentLine = 1;
  while (it != vStr.end()) {
    if (cursorPos == currentLine - 1) {
      wattron(stdscr, A_STANDOUT);
    }
    mvwprintw(stdscr, currentLine, 3, (*it).c_str());
    if (cursorPos == currentLine - 1) {
      wattroff(stdscr, A_STANDOUT);
    }
    currentLine++;
    it++;
  }
}

void	Window::updateCursorPos(int c) {
  int	curCursorPos = cursorPos;

  if (c == KEY_UP) {
    cursorPos--;
  } else if (c == KEY_DOWN) {
    cursorPos++;
  }
  if (cursorPos > vSize - 1) {
    cursorPos = 0;
  }
  if (cursorPos < 0)
    cursorPos = vSize - 1;
  mvwprintw(stdscr, curCursorPos + 1, 3, vStr[curCursorPos].c_str());
  wattron(stdscr, A_STANDOUT);
  mvwprintw(stdscr, cursorPos + 1, 3, vStr[cursorPos].c_str());
  wattroff(stdscr, A_STANDOUT);
}

void	Window::welcome(void) {
  std::string	welcomeStr = "Manalink";

  wbkgd(top, COLOR_PAIR(1));
  mvwprintw(top, 0, col / 2 - (welcomeStr.length() / 2), welcomeStr.c_str());
  wbkgd(bot, COLOR_PAIR(1));
  mvwprintw(bot, 0, col / 2 - (welcomeStr.length() / 2), welcomeStr.c_str());
}
