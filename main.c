#include <ncurses.h>

struct EditorState {
  int cx, cy;     // Cursor position
  int rows, cols; // Screen size
  int running;
};

int main() {
  struct EditorState E = {0};

  E.running = 1;
  E.cx = 0;
  E.cy = 0;

  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);

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
