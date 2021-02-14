#include <ncurses.h>

#include "colors.h"
#include "screen.h"
#include "objects.h"
#include "kbhit.h"

#define delay(ms) usleep(ms * 1000)

int main()
{
    printf("$1\n");
    getch();
    Init_Screen();
    keypad(stdscr, TRUE);
    printw("$2\n");
    int x = 0;
    ObjectList Objs(stdscr);
    Objs.newObject(ObjectType::SHIP_BASIC, COLS / 2, LINES - 4);
    int t = 1;

    while (x != (int)'q')
    {
        Objs.player->drawObject();
        refresh();
        Objs.player->move();

        if (kbhit())
        {
            x = getch();
            switch (x)
            {
            case KEY_RIGHT:
                if (t == -1)
                    Objs.player->revVelocity(), t = 1;
                break;
            case KEY_LEFT:
                if (t == 1)
                    Objs.player->revVelocity(), t = -1;
                break;
            }
        }
        delay(40);
    }
    endwin();
}
