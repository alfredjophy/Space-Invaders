void Init_Screen()
{

    initscr();
    init_color(COLOR_BLACK, 0, 0, 0);
    start_color();
    initColorPairs();
    curs_set(0);
    noecho();
}