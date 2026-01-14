#include <ncurses.h>
int main() {
  initscr();
  raw();
  noecho();  
  endwin();  
  return 0;  
}
