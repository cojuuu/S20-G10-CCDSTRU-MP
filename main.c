#include "functions.c"

int main()
{
    Game g;

    setUpGame(&g);

    
    displayBoard(g);

    printf("%s\n", g.result);

    return 0;
}


