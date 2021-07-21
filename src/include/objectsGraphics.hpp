#ifndef OBJECTSGRAPHICS_H
#define OBJECTSGRAPHICS_H

#include <ncurses.h>

enum OBJECT_TYPES
{
        SHIP_BASIC = 0,
        SHIP_ENEMY_1 = 1,
        SHIP_ENEMY_2 = 2,
        BULLET_1 = 3,
        BULLET_2 = 4

};


class ObjectGraphics
{
        char height, width;
        char objectCharacters[5][5];
        char objectColors[5][5];

        public:
        ObjectGraphics(OBJECT_TYPES type);
        void getDimensions(int &h, int &w);
        void drawObject(int y, int x, WINDOW *win);
        void eraseObject(int y, int x, WINDOW *win);
};

#endif
