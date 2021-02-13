#include <ncurses.h>

#include "objects.h"
#include "colors.h"
#include "screen.h"

int main()
{
    Init_Screen();
    keypad(stdscr, TRUE);
    ObjectGraphics SHIP(0);
    int ch = 'y';
    int x = 10, y = 10;
    SHIP.drawObject(y, x);
    refresh();
    while ((ch = getch()) && ch != 'q')
    {
        SHIP.eraseObject(y, x);
        switch (ch)
        {
        case KEY_LEFT:
            --x;
            break;
        case KEY_UP:
            --y;
            break;
        case KEY_DOWN:
            ++y;
            break;
        case KEY_RIGHT:
            ++x;
            break;
        }
        SHIP.drawObject(y, x);
    }
    endwin();
    return 0;
}