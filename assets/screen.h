#include "colors.h"
void init_ncurses()
{

    initscr();
    start_color();

    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();

    init_color(COLOR_BLACK, 0, 0, 0);
    initColorPairs();
    //raw();
}