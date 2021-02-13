//first test to learn function

#include <ncurses.h>
#include <stdlib.h>
#include "title.h"

int main()
{
    initscr();
    curs_set(0);

    if (!(has_colors() && can_change_color()))
    {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    start_color();

    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1, COLOR_RED, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    printw("Window Test");
    attroff(COLOR_PAIR(1));
    refresh();
    //move(getmaxy(stdscr)/2,getmaxx(stdscr)/2);
    //GAME_TITLE();
    //WINDOW *lw = newwin(25, 80, getmaxy(stdscr) / 2 - 12, getmaxx(stdscr) / 2 - 40);
    WINDOW *lw = newwin(25, 80, LINES / 2 - 12, COLS / 2 - 40);

    box(lw, 0, 0);
    wrefresh(lw);
    //attroff(COLOR_PAIR(1));
    while (1)
    {
        char c = getch();
        if (c == 'x')
            break;
    }
    delwin(lw);
    clear();
    refresh();
    endwin();
    return 0;
}