/**
 * Description     : Implements the game logic, board updates, input handling,
 *                   and helper functions for the CCDSTRU machine project
 * Author/s        : De Dios, Justin Marco ; Lamano, Kyle
 * Section         : CCDSTRU S09
 * Last Modified   : March 5, 2026
 * Acknowledgments : We thank our professor, Mr. Emerico Aguilar, for
 *                   the lessons and discussions in class, which helped
 *                   us in completing this project.
 */

#include "defs.h"

/* ---------- spec functions ---------- */

/**
 * Removes a position from the current player's set and from marker sets
 * If the position is valid, it is removed from R or B depending on whose turn
 * it is, and also removed from S and T
 * @param g pointer to the current game state
 * @param pos position to be removed
 * @pre g is not NULL
 */
void Remove(Game *g, Coordinates pos)
{
    if (!outOfBounds(pos))
    {
        if (g->go)
            modifyCoordinateArr(&g->R, pos, REMOVE);
        else if (!g->go)
            modifyCoordinateArr(&g->B, pos, REMOVE);

        modifyCoordinateArr(&g->board.S, pos, REMOVE);
        modifyCoordinateArr(&g->board.T, pos, REMOVE);
        modifyCoordinateArr(&g->board.F, pos, ADD);
    }
}

/**
 * Applies replacement logic on a target position based on the current player
 * Can capture an opponent piece, place a new piece, update marker sets S/T,
 * and trigger expansion when applicable
 * @param g pointer to the current game state
 * @param pos target position to process
 * @pre g is not NULL
 */
void Replace(Game *g, Coordinates pos)
{
    g->found = false;

    if (!outOfBounds(pos))
    {
        if (g->go)
        {
            if (cordsFound(g->B, pos.x, pos.y))
            {
                modifyCoordinateArr(&g->R, pos, ADD);
                modifyCoordinateArr(&g->B, pos, REMOVE);
                g->found = true;
            }
            else if (cordsFound(g->R, pos.x, pos.y))
            {
                g->found = true;
            }
            else if (!cordsFound(g->R, pos.x, pos.y))
            {
                modifyCoordinateArr(&g->R, pos, ADD);
                modifyCoordinateArr(&g->board.F, pos, REMOVE);
            }
        }
        else
        {
            if (cordsFound(g->R, pos.x, pos.y))
            {
                modifyCoordinateArr(&g->B, pos, ADD);
                modifyCoordinateArr(&g->R, pos, REMOVE);
                g->found = true;
            }
            else if (cordsFound(g->B, pos.x, pos.y))
            {
                g->found = true;
            }
            else if (!cordsFound(g->B, pos.x, pos.y))
            {
                modifyCoordinateArr(&g->B, pos, ADD);
                modifyCoordinateArr(&g->board.F, pos, REMOVE);
            }
        }

        if (g->found)
        {
            if (!cordsFound(g->board.S, pos.x, pos.y))
            {
                modifyCoordinateArr(&g->board.S, pos, ADD);
                g->found = false;
            }
            else if (cordsFound(g->board.S, pos.x, pos.y) && !cordsFound(g->board.T, pos.x, pos.y))
            {
                modifyCoordinateArr(&g->board.T, pos, ADD);
                Expand(g, pos);
            }
        }
    }
}

/**
 * Expands from a position by removing the center piece and applying Replace()
 * to neighboring positions according to the current player's direction
 * R expands upward + left + right, while B expands downward + left + right
 * @param g pointer to the current game state
 * @param pos center position to expand from
 * @pre g is not NULL
 */
void Expand(Game *g, Coordinates pos)
{
    Coordinates u, d, k, r;

    if (!outOfBounds(pos))
    {
        u.x = pos.x;
        u.y = pos.y - 1;

        d.x = pos.x;
        d.y = pos.y + 1;

        k.x = pos.x - 1;
        k.y = pos.y;

        r.x = pos.x + 1;
        r.y = pos.y;

        Remove(g, pos);

        if (g->go)
            Replace(g, u);
        else
            Replace(g, d);

        Replace(g, k);
        Replace(g, r);
    }
}

/**
 * Updates the currently selected position during the non-start phase
 * Marks the position in S if not yet marked, or triggers expansion through T
 * if it was already marked in S but not yet in T
 * @param g pointer to the current game state (uses g->pos as selected position)
 * @pre g is not NULL
 */
void Update(Game *g)
{
    g->good = false;

    if (!cordsFound(g->board.S, g->pos.x, g->pos.y))
    {
        modifyCoordinateArr(&g->board.S, g->pos, ADD);
        g->good = true;
    }

    if (!g->good && cordsFound(g->board.S, g->pos.x, g->pos.y) && !cordsFound(g->board.T, g->pos.x, g->pos.y))
    {
        modifyCoordinateArr(&g->board.T, g->pos, ADD);
        Expand(g, g->pos);
    }
}

/**
 * Processes one full player move/turn
 * Handles input, start phase placement, non-start phase updates, start phase end
 * condition, and turn switching with move count increment
 * @param g pointer to the current game state
 * @pre g is not NULL
 */
void NextPlayerMove(Game *g)
{
    promptPlayerMove(g);
    
    if (g->start)
    {
        if (g->go)
            modifyCoordinateArr(&g->R, g->pos, ADD);
        else if (!g->go)
            modifyCoordinateArr(&g->B, g->pos, ADD);

        modifyCoordinateArr(&g->board.S, g->pos, ADD);
        modifyCoordinateArr(&g->board.F, g->pos, REMOVE);
    }
    else if (!g->start)
    {
        if ((g->go && cordsFound(g->R, g->pos.x, g->pos.y)) || (!g->go && cordsFound(g->B, g->pos.x, g->pos.y)))
        {
            Update(g);
        }
    }

    if (g->start && g->R.cordsCount == 1 && g->B.cordsCount == 1)
    {
        g->start = false;
    }

    g->good = !g->good;
    g->go = !g->go;
    g->val++;
}

/**
 * Determines the final game result string when the game is over
 * Compares the number of occupied positions of players R and B
 * @param g pointer to the current game state
 * @pre g is not NULL and g->over is true before calling
 */
void GameOver(Game *g)
{
    if (g->over && (g->R.cordsCount > g->B.cordsCount))
        strcpy(g->result, "R wins");
    else if (g->over && (g->R.cordsCount < g->B.cordsCount))
        strcpy(g->result, "B wins");
    else if (g->over && (g->R.cordsCount == g->B.cordsCount))
        strcpy(g->result, "draw");
}

/* ---------- helper functions ---------- */

/**
 * Initializes the game state, flags, counters, board cells, and free positions
 * Sets all members to default values and prepares the board for the first move
 * @param g pointer to the current game state
 * @pre g is not NULL
 */
void setUpGame(Game *g)
{
    // Initializes everything in the game struct to 0/NULL/false
    memset(g, 0, sizeof(Game));

    g->go = true;
    g->start = true;

    // Set up board
    for (int y = 1; y <= SIZE; y++)
    {
        for (int x = 1; x <= SIZE; x++)
        {
            strcpy(g->board.grid[y][x], "   ");
            g->board.F.cords[g->board.F.cordsCount].x = x;
            g->board.F.cords[g->board.F.cordsCount].y = y;
            g->board.F.cordsCount++;
         }
    }
}

/**
 * Prompts the current player to enter a coordinate and validates input
 * Repeats until a valid in-bounds coordinate is entered and, after the start
 * phase, ensures the selected position belongs to the current player
 * @param g pointer to the current game state
 * @pre g is not NULL
 */
void promptPlayerMove(Game *g)
{
    do
    {
        g->good = true;

        if (g->go)
            printf("Player R, enter coordinates (x y): ");
        else if (!g->go)
            printf("Player B, enter coordinates (x y): ");
        
        scanf("%d %d", &g->pos.x, &g->pos.y);

        if (outOfBounds(g->pos))
        {
            printf("Invalid coordinates!\n");
            g->good = false;
        }
        
        if (!g->start && !outOfBounds(g->pos))
        {
            if ((g->go && !cordsFound(g->R, g->pos.x, g->pos.y)) || (!g->go && !cordsFound(g->B, g->pos.x, g->pos.y)))
            {
                printf("Please choose your own piece!\n");
                g->good = false;
            }
        }
    } while (!g->good);
}

/**
 * Adds or removes a coordinate from a coordinate array based on the mode
 * ADD appends a coordinate to the array, while REMOVE deletes a matching
 * coordinate if found
 * @param dest pointer to the destination coordinate array
 * @param pos coordinate to add or remove
 * @param mode operation mode (ADD or REMOVE)
 * @pre dest is not NULL
 */
void modifyCoordinateArr(CordsArr *dest, Coordinates pos, char mode)
{
    if (mode == ADD)
    {
        dest->cords[dest->cordsCount] = pos;
        dest->cordsCount++;
    }
    else if (mode == REMOVE)
    {
        for (int i = 0; i < dest->cordsCount; i++)
        {
            if (dest->cords[i].x == pos.x && dest->cords[i].y == pos.y)
            {
                dest->cords[i].x = dest->cords[dest->cordsCount - 1].x;
                dest->cords[i].y = dest->cords[dest->cordsCount - 1].y;

                dest->cords[dest->cordsCount - 1].x = 0;
                dest->cords[dest->cordsCount - 1].y = 0;

                dest->cordsCount--;

                i = dest->cordsCount;
            }
        }
    }
}

/**
 * Checks whether a coordinate is outside the valid board boundaries
 * @param pos coordinate to check
 * @return true if the coordinate is out of bounds, otherwise false
 */
bool outOfBounds(Coordinates pos)
{
    if (pos.x < 1 || pos.x > SIZE || pos.y < 1 || pos.y > SIZE)
        return true;
    return false;
}

/**
 * Checks whether a coordinate exists in a coordinate array
 * @param arr coordinate array to search
 * @param x x-coordinate to find
 * @param y y-coordinate to find
 * @return true if the coordinate exists in arr, otherwise false
 */
bool cordsFound(CordsArr arr, int x, int y)
{
    bool foundCords = false;

    for (int i = 0; i < arr.cordsCount; i++)
    {
        if (arr.cords[i].x == x && arr.cords[i].y == y)
        {
            foundCords = true;
            i = arr.cordsCount;
        }
    }

    return foundCords;
}

/**
 * Updates the printable board grid using the current contents of F, R, B, and S
 * Free cells are cleared, player pieces are drawn, and marked cells in S are
 * displayed with brackets
 * @param g pointer to the current game state
 * @pre g is not NULL
 */
void updateBoard(Game *g)
{
    for (int i = 0; i < g->board.F.cordsCount; i++)
        strcpy(g->board.grid[g->board.F.cords[i].y][g->board.F.cords[i].x], "   ");

    for (int i = 0; i < g->R.cordsCount; i++)
        strcpy(g->board.grid[g->R.cords[i].y][g->R.cords[i].x], " O ");

    for (int i = 0; i < g->B.cordsCount; i++)
        strcpy(g->board.grid[g->B.cords[i].y][g->B.cords[i].x], " O ");

    for (int i = 0; i < g->board.S.cordsCount; i++)
        strcpy(g->board.grid[g->board.S.cords[i].y][g->board.S.cords[i].x], "[O]");
}

/**
 * Checks whether any game-over condition has been met
 * Sets g->over to true if the free-cell condition, move-limit condition, or
 * elimination condition is satisfied
 * @param g pointer to the current game state
 * @pre g is not NULL and g->board.F is updated before calling
 */
void checkWin(Game *g)
{
    if (g->board.F.cordsCount == 3 || 
        g->val >= MAX_MOVES || 
        (!g->start && ((g->R.cordsCount > 0 && g->B.cordsCount == 0) || 
                    (g->R.cordsCount == 0 && g->B.cordsCount > 0)))) 
    {
        g->over = true;
    }
}

/**
 * Displays the current board state with row/column labels and piece colors
 * @param g current game state (passed by value for display only)
 */
void displayBoard(Game g)
{
    printf("\n");
    printf("  1   2   3\n");
    printf("+---+---+---+\n");

    for (int y = 1; y <= SIZE; y++)
    {
        printf("|");
        for (int x = 1; x <= SIZE; x++)
        {
            if (cordsFound(g.R, x, y))
                printf("%s", RED);
            else if (cordsFound(g.B, x, y))
                printf("%s", BLUE);

            printf("%s%s|", g.board.grid[y][x], RESET);
        }
        printf(" %d", y);
        printf("\n+---+---+---+\n");
    }
}

/**
 * Clears the console screen using the appropriate command for the platform
 * Uses "cls" on Windows and "clear" on POSIX systems
 */
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    // Assume POSIX (Linux, macOS, etc.)
    system("clear");
#endif
}

/**
 * Pauses the program and waits for the user to press Enter before continuing
 * Consumes the leftover newline from previous input, then waits again
 */
void pauseScreen()
{
    getchar();
    printf("Press Enter to continue...\n");
    getchar();
}