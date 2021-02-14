#include <ncurses.h>
#include <unistd.h>

#include "objectsGraphics.h"
#include "colors.h"
#include "screen.h"
#define delay(ms) usleep(ms * 1000)

int main()
{
    Init_Screen();
    keypad(stdscr, TRUE);
    int ch = 'y';
    int x = 10, y = 10;
    SHIP_BASIC.drawObject(y, x);
    refresh();
    while ((ch = getch()) && ch != 'q')
    {
        SHIP_BASIC.eraseObject(y, x);
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
        SHIP_BASIC.drawObject(y, x);
    }

    // for (int i = 0; i < COLS; ++i)
    // {
    //     SHIP.drawObject(LINES / 2, i);
    //     refresh();
    //     delay(40);
    //     SHIP.eraseObject(LINES / 2, i);
    // }
    endwin();
    return 0;
}