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
        checkWin(&g);
    } while (!g.over);

    GameOver(&g);

    printf("%s\n", g.result);

    return 0;
}