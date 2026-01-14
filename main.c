#include <ncurses.h>
int main() {
  int running = 1;
  
  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);
  
  while (running) {
    int ch = getch();

    clear();
    mvprintw(0, 0, "Key code: %d", ch);
    mvprintw(1, 0, "Press Ctrl+Q to quit");
    refresh();

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
