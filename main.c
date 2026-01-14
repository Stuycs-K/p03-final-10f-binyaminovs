#include <ncurses.h>
int main() {
  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);
  getch();  
  endwin();  
  return 0;  
}
