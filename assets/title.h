#include <ncurses.h>

void GAME_TITLE()
{
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    int maxx, maxy;

    getmaxyx(stdscr, maxy, maxx);
    //calculate scaling

    int HL,VL;
    clear();

    attron(COLOR_PAIR(1) | A_BOLD);
    //space
addch(ACS_ULCORNER);
    mvhline(getcury(stdscr), getcurx(stdscr), ACS_HLINE, 10);
    move(getcury(stdscr), getcurx(stdscr) + 10);
    addch(ACS_URCORNER);
    addch(' ');
    //hline 0
    move(20, 30);
    addch(ACS_ULCORNER);
    mvhline(getcury(stdscr), getcurx(stdscr), ACS_HLINE, 10);
    move(getcury(stdscr), getcurx(stdscr) + 10);
    addch(' ');
    addch(ACS_ULCORNER);
    mvhline(getcury(stdscr), getcurx(stdscr), ACS_HLINE, 10);
    move(getcury(stdscr), getcurx(stdscr) + 10);
    addch(ACS_URCORNER);
    addch(' ');
    addch(ACS_ULCORNER);
    mvhline(getcury(stdscr), getcurx(stdscr), ACS_HLINE, 10);
    move(getcury(stdscr), getcurx(stdscr) + 10);
    addch(ACS_URCORNER);
    addch(' ');
    mvhline(getcury(stdscr), getcurx(stdscr), ACS_HLINE, 10);
    move(getcury(stdscr), getcurx(stdscr) + 10);
    addch(' ');
    mvhline(getcury(stdscr), getcurx(stdscr), ACS_HLINE, 10);
    move(getcury(stdscr), getcurx(stdscr) + 10);

    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2) | A_BLINK);
    //invaders
    attroff(COLOR_PAIR(2) | A_BLINK | A_BOLD);
    refresh();
}