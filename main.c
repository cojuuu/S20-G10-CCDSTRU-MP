#include "defs.h"

int main()
{
    Game g;

    setUpGame(&g);
    clearScreen();
    do
    {
        displayBoard(g);
        NextPlayerMove(&g);
        updateBoard(&g);
        checkWin(&g);
        displayBoard(g);
        pauseScreen();
        clearScreen();
    } while (!g.over);

    GameOver(&g);

    printf("%s\n", g.result);

    return 0;
}