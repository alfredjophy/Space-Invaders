
void initColorPairs()
{
    init_color(COLOR_BLACK, 0, 0, 0);
    for (int i = 0; i < 15; i++)
    {
        init_pair(i,i, 0);
    }
}