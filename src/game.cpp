#include "include/colors.hpp"
#include "include/objects.hpp"
#include "include/kbhit.hpp"


#define delay(ms) usleep(ms * 1000)

int main()
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

    int x = 0;

    WINDOW *game = newwin(LINES - 2, COLS / 2, 1, COLS / 4);
    //game=stdscr;
    //box(game, 0, 0);

    ObjectList Objs(game);
    Objs.newObject(SHIP_BASIC, 20, 20);
    //Objs.newObject(SHIP_ENEMY_1, 60, 10);
    Objs.newObject(SHIP_ENEMY_1, 35, 10);
    Objs.newObject(SHIP_ENEMY_1, 14, 10);
    while (x != 'q')
    {
        //render
        Objs.drawObjects();

        refresh();
        wrefresh(game);

        //user_input
        if (kbhit())
        {
            x = getch();
            switch (x)
            {
            case KEY_RIGHT:
                Objs.player->changeDir(1);
                break;
            case KEY_LEFT:
                Objs.player->changeDir(-1);
                break;
            case ' ':
                Objs.shoot(Objs.player);
                break;
            }
        }

        //update_environment
        Objs.updatePositions();

        delay(40);
    }
    endwin();
    return 0;
}
