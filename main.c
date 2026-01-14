#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1024


struct EditorState {
  int cx, cy;
  int rows, cols;
  int running;
  char *lines[MAX_LINES];
  int num_lines;  
    
};

int main() {
  struct EditorState E = {0};

  E.running = 1;
  E.cx = 0;
  E.cy = 0;

  E.lines[0] = strdup("");
  E.num_lines = 1;  

  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);

  getmaxyx(stdscr, E.rows, E.cols);  

  while (E.running) {
    int ch = getch();

    clear();
    mvprintw(0, 0, "Key code: %d", ch);
    mvprintw(1, 0, "Press Ctrl+Q to quit");
    refresh();

    switch (ch) {
    case 17:
      E.running = 0;
      break;
    case KEY_RESIZE:
      getmaxyx(stdscr, E.rows, E.cols);
      if (E.cx >= E.cols)
        E.cx = E.cols - 1;
      if (E.cy >= E.rows)
        E.cy = E.rows - 1;
      break;
    case KEY_LEFT:
      if (E.cx > 0)
        E.cx--;
      break;
    case KEY_RIGHT:
      E.cx++;
      break;
    case KEY_UP:
      if (E.cy > 0)
        E.cy--;
      break;
    case KEY_DOWN:
      E.cy++;
      break;
    default:
      break;
    }
  }

  endwin();
  return 0;
}
