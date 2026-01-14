#include <ncurses.h>
int main() {
  int running = 1;
  
  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);
  
  while (running) {
    int ch = getch();

    if (ch == 17) {
      running = 0;
    }
  }
  
  endwin();  
  return 0;  
}
