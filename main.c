// bring in sick note

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

int line_length(struct EditorState *E, int line) {
  if (line < 0 || line >= E->num_lines)
    return 0;
  return strlen(E->lines[line]);  
}

void draw_editor(struct EditorState *E) {
  clear();

  for (int i = 0; i < E->num_lines && i < E->rows; i++) {
    mvaddstr(i, 0, E->lines[i]);
  }

  int cx = E->cx;
  int cy = E->cy;

  int len = line_length(E, cy);
  if (cx > len)
    cx = len;  

  move(cy, cx);
  refresh();
}

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
    // mvprintw(0, 0, "Key code: %d", ch);
    draw_editor(&E);       
    
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
      if (E.cx < line_length(&E, E.cy))
        E.cx++;
      break;
    case KEY_UP:
      if (E.cy > 0) {
        E.cy--;
        if (E.cx > line_length(&E, E.cy))
          E.cx = line_length(&E, E.cy);
      }
      break;
    case KEY_DOWN:
      if (E.cy < E.num_lines - 1) {
        E.cy++;
        if (E.cx > line_length(&E, E.cy))
          E.cx = line_length(&E, E.cy);
      }
      break;      
    default:
      break;
    }
  }

  endwin();
  return 0;
}
