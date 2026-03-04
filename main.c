#include "defs.h"

int main()
{
    Game g;

    setUpGame(&g);

    while (!g.over)
    {
        clearScreen();
        displayBoard(g);

        NextPlayerMove(&g);

        checkWin(&g);
        updateBoard(&g);
    }

    clearScreen();
    displayBoard(g);

    GameOver(&g);
    printf("%s\n", g.result);

    return 0;
}