#include "defs.h"

int main()
{
    Game g;

    setUpGame(&g);

    do
    {
        displayBoard(g);
        NextPlayerMove(&g);
        updateBoard(&g);
    } while (!g.over);

    return 0;
}