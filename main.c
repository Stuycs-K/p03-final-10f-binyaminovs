#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LINES 1024


struct EditorState {
  int cx, cy;
  int rows, cols;
  int running;
  char *lines[MAX_LINES];
  int num_lines;
  char *filename;  
};

void insert_char(struct EditorState *E, char c) {
  if (E->cy >= MAX_LINES)
    return;

  char *line = E->lines[E->cy];
  int len = strlen(line);

  if (len >= E->cols - 1)
    return;

  for (int i = len; i >= E->cx; i--) {
    line[i + 1] = line[i];
  }

  line[E->cx] = c;
  E->cx++;
}

void backspace_char(struct EditorState *E) {
  if (E->cx == 0)
    return;

  char *line = E->lines[E->cy];
  int len = strlen(line);

  for (int i = E->cx - 1; i < len; i++) {
    line[i] = line[i + 1];
  }

  E->cx--;
}

void insert_newline(struct EditorState *E) {
  if (E->num_lines >= MAX_LINES)
    return;

  char *current = E->lines[E->cy];
  int len = strlen(current);

  for (int i = E->num_lines; i > E->cy + 1; i--) {
    E->lines[i] = E->lines[i - 1];
  }

  E->lines[E->cy + 1] = strdup(current + E->cx);
  current[E->cx] = '\0';

  E->num_lines++;
  E->cy++;
  E->cx = 0;  
}

void open_file(struct EditorState *E, const char *filename) {
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    E->lines[0] = strdup("");
    E->num_lines = 1;
    E->filename = strdup(filename);    
    return;
  }

  E->num_lines = 0;  
  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != -1) {
    if (E->num_lines >= MAX_LINES) break;

    size_t l = strlen(line);
    if (l > 0 && (line[l-1] == '\n' || line[l-1] == '\r')) line[l-1] = '\0';

    E->lines[E->num_lines++] = strdup(line);
  }

  free(line);
  fclose(fp);

  if (E->num_lines == 0) {
    E->lines[0] = strdup("");
    E->num_lines = 1;    
  }  
}

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

int main(int argc, char **argv) {
  struct EditorState E = {0};
  E.running = 1;

  if (argc >= 2) {
    E.filename = argv[1];
    open_file(&E, E.filename);
  } else {    
    E.lines[0] = strdup("");
    E.num_lines = 1;
    E.filename = NULL;
  }

  E.cx = 0;
  E.cy = 0;

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
    case 127: 
      backspace_char(&E);
      break;
    case 10:
      insert_newline(&E);
      break;      
    default:
      if (ch >= 32 && ch <= 126) {
        insert_char(&E, (char)ch);
      }      
      break;
    }
  }

  endwin();
  return 0;
}
