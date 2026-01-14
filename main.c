#include <ncurses.h>

typedef struct {
    int cx, cy;
    int rows, cols;
    int running;
} EditorState;

int main(void) {
    EditorState E = {0};
    E.running = 1;

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, E.rows, E.cols);

    while (E.running) {
        int ch = getch();

        switch (ch) {
            case 17: 
                E.running = 0;
                break;
            case KEY_LEFT:
                if (E.cx > 0) E.cx--;
                break;
            case KEY_RIGHT:
                if (E.cx < E.cols - 1) E.cx++;
                break;
            case KEY_UP:
                if (E.cy > 0) E.cy--;
                break;
            case KEY_DOWN:
                if (E.cy < E.rows - 1) E.cy++;
                break;
            default:
                break;
        }
    }

    endwin();
    return 0;
}
