#include "defs.h"

/**
 * Runs the main program loop for the game
 * Initializes the game state, repeatedly processes player turns until the game
 * ends, and prints the final result
 * @return 0 if the program terminates successfully
 */
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