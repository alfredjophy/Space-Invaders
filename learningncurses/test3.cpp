#include <ncurses.h>

#include "colors.h"
#include "screen.h"
#include "objects.h"
#include "kbhit.h"

#define delay(ms) usleep(ms * 1000)

int main()
{

    Init_Screen();
    keypad(stdscr, TRUE);
    int x = 0;
    ObjectList Objs(stdscr);
    Objs.newObject(ObjectType::SHIP_BASIC, COLS / 2, LINES - 4);
    Objs.newObject(ObjectType::SHIP_BASIC, COLS / 3, LINES / 2);

    int t = 1;

    while (x != 'q')
    {
        //render
        Objs.drawObjects();
        refresh();

        //user_input
        if (kbhit())
        {
            x = getch();
            switch (x)
            {
            case KEY_RIGHT:
                if (t == -1)
                {
                    Objs.player->revVelocity();
                    t = 1;
                }
                break;
            case KEY_LEFT:
                if (t == 1)
                {
                    Objs.player->revVelocity();
                    t = -1;
                }
                break;
            }
        }

        //update_environment
        Objs.updatePositions();

        delay(40);
    }
    endwin();
}
