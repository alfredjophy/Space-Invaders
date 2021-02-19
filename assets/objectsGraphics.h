namespace ObjectType
{
    enum OBJECT_TYPES
    {
        SHIP_BASIC = 0,
        SHIP_ENEMY_1 = 1,
        SHIP_ENEMY_2 = 2,
        BULLET_1 = 3,
        BULLET_2 = 4

    };
}

class ObjectGraphics
{

    char height, width;
    char objectCharacters[5][5];
    char objectColors[5][5];

public:
    ObjectGraphics(ObjectType::OBJECT_TYPES type)
    {
        switch (type)
        {

            //basic ship
        case ObjectType::SHIP_BASIC:
        {
            const int rows = 3, cols = 5;
            height = rows, width = cols;
            char chrs[rows][cols] = {
                ' ', ' ', 'x', ' ', ' ',
                ' ', 'l', 'x', 'k', ' ',
                'a', 'u', 'a', 't', 'a'};
            char clr[rows][cols] = {
                0,
                0,
                1,
                0,
                0,
                0,
                3,
                1,
                3,
                0,
                2,
                5,
                6,
                5,
                2,
            };
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                {
                    objectCharacters[i][j] = chrs[i][j];
                    objectColors[i][j] = clr[i][j];
                }
        }
        break;
        case ObjectType::SHIP_ENEMY_1:
        {
            const int cols = 3, rows = 2;
            height = rows, width = cols;
            char chrs[rows][cols] = {
                'a', 'n', 'a',
                ' ', 'x', ' '};
            char clr[rows][cols] = {
                4, 5, 4,
                0, 1, 0};
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                {
                    objectCharacters[i][j] = chrs[i][j];
                    objectColors[i][j] = clr[i][j];
                }
        }
        break;
        case ObjectType::BULLET_1:
        {
            const int cols = 1, rows = 1;
            height = rows, width = cols;
            char chr = '`';
            char clr = 1;
            objectCharacters[0][0] = chr;
            objectColors[0][0] = clr;
        }
        break;
        }
    }

    void getDimensions(int &h, int &w)
    {
        h = height;
        w = width;
    }

    void drawObject(int y, int x, WINDOW *win)
    {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
            {
                wmove(win, y + i - height / 2, x + j - width / 2);
                wattron(win, COLOR_PAIR(objectColors[i][j]));
                waddch(win, NCURSES_ACS(objectCharacters[i][j]));
                wattroff(win, COLOR_PAIR(objectColors[i][j]));
            }
    }
    void eraseObject(int y, int x, WINDOW *win)
    {
        wattron(win, COLOR_PAIR(0));
        for (int i = 0; i < height; i++)
            mvwhline(win, y + i - height / 2, x - width / 2, ' ', width);
        wattroff(win, COLOR_PAIR(0));
    }
};

ObjectGraphics SHIP_BASIC(ObjectType::SHIP_BASIC);
ObjectGraphics SHIP_ENEMY_1(ObjectType::SHIP_ENEMY_1);
ObjectGraphics BULLET_1(ObjectType::BULLET_1);
