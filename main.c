#include <ncurses.h>
int main() {
  int running = 1;
  
  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);
  
  while (running) {
    int ch = getch();

    switch (ch) {
    case 17:
      running = 0;
      break;
    default:
      break;      
    }
      
  }
  
  endwin();  
  return 0;  
}
