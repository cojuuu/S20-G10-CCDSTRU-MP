#include "defs.h"

int main()
{
    Game g;

    setUpGame(&g);

    displayBoard(g);
    promptPlayerMove(&g);

    return 0;
}


