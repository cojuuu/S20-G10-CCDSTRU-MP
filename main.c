#include "defs.h"

int main()
{
    Game g;

    setUpGame(&g);

    updateBoard(&g);
    computeOver(&g);

    do
    {
        displayBoard(g);
        NextPlayerMove(&g);
        updateBoard(&g);
        computeOver(&g);
    } while (!g.over);

    GameOver(&g);
    printf("%s\n", g.result);
    
    return 0;
}