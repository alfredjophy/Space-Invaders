#include <ncurses.h>

class ObjectGraphics
{

    char height, width;
    char objectCharacters[5][5];
    char objectColors[5][5];

public:
    ObjectGraphics(int type)
    {
        switch (type)
        {

            //basic ship
        case 0:
            height = 3, width = 3;
            char chrs[3][3] = {
                ' ', 'v', ' ',
                ' ', 'x', ' ',
                'a', 'a', 'a'};
            char clr[3][3] = {
                0,
                1,
                0,
                0,
                1,
                0,
                1,
                9,
                1};

            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                {
                    objectCharacters[i][j] = chrs[i][j];
                    objectColors[i][j] = clr[i][j];
                }
            break;
        }
    }

    void getDimensions(char &h, char &w)
    {
        h = height;
        w = width;
    }

    void drawObject(int y, int x, WINDOW *win = stdscr)
    {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
            {
                wmove(win, y + i, x + j);
                attron(COLOR_PAIR(objectColors[i][j]));
                waddch(win, NCURSES_ACS(objectCharacters[i][j]));
                attroff(COLOR_PAIR(objectColors[i][j]));
            }
    }
    void eraseObject(int y, int x, WINDOW *win = stdscr)
    {
        attron(COLOR_PAIR(0));
        for (int i = 0; i < height; i++)
            mvwhline(win, y + i, x, ' ', width);
        attroff(COLOR_PAIR(0));
    }
};

ObjectGraphics SHIP(0);