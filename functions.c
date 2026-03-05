#include "defs.h"

void Remove(Game *g, Coordinates pos)
{
    if (g->go)
        modifyCoordinateArr(&g->R, pos, REMOVE);
    else if (!g->go)
        modifyCoordinateArr(&g->B, pos, REMOVE);
    
    modifyCoordinateArr(&g->board.S, pos, REMOVE);
    modifyCoordinateArr(&g->board.T, pos, REMOVE);

    modifyCoordinateArr(&g->board.F, pos, ADD);
}

void Replace(Game *g, Coordinates pos)
{
    g->found = false;

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
    else if (!g->go)
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
            g->found = true;
        }
        else if (cordsFound(g->board.S, pos.x, pos.y) && !cordsFound(g->board.T, pos.x, pos.y))
        {
            modifyCoordinateArr(&g->board.T, pos, ADD);
            Expand(g, pos);
        }
    }
}

void Expand(Game *g, Coordinates pos)
{
    Coordinates u, d, k, r;

    u.x = pos.x;
    u.y = pos.y - 1;

    d.x = pos.x;
    d.y = pos.y + 1;

    k.x = pos.x - 1;
    k.y = pos.y;

    r.x = pos.x + 1;
    r.y = pos.y;

    Remove(g, pos);

    if (g->go && !outOfBounds(u))
        Replace(g, u);
    else if (!g->go && !outOfBounds(d))
        Replace(g, d);

    if (!outOfBounds(k))
        Replace(g, k);

    if (!outOfBounds(r))
    {
        Replace(g, r); 
    }
        
}

void Update()
{

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

void NextPlayerMove(Game *g)
{
    promptPlayerMove(g);

    if (g->start && g->go)
    {
        modifyCoordinateArr(&g->R, g->pos, ADD);
        modifyCoordinateArr(&g->board.S, g->pos, ADD);
        modifyCoordinateArr(&g->board.F, g->pos, REMOVE);
    }
    else if (g->start && !g->go)
    {
        modifyCoordinateArr(&g->B, g->pos, ADD);
        modifyCoordinateArr(&g->board.S, g->pos, ADD);
        modifyCoordinateArr(&g->board.F, g->pos, REMOVE);
    }

    if (!g->start)
    {
        if (g->go && cordsFound(g->R, g->pos.x, g->pos.y))
            Update(g);
        else if (!g->go && cordsFound(g->B, g->pos.x, g->pos.y))
            Update(g);
    }

    if (g->start && g->R.cordsCount == 1 && g->B.cordsCount == 1)
    {
        g->start = false;
    }

   
    g->go = !g->go;
    g->good = !g->good;
    g->val++;
    
}

void GameOver(Game *g)
{
    if (g->over && (g->R.cordsCount > g->B.cordsCount))
        strcpy(g->result, "R wins");
    else if (g->over && (g->R.cordsCount < g->B.cordsCount))
        strcpy(g->result, "B wins");
    else if (g->over && (g->R.cordsCount == g->B.cordsCount))
        strcpy(g->result, "draw");
}

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

void promptPlayerMove(Game *g)
{
    printf("\n");
    do
    {
        if (g->go)
            printf("Player R, enter coordinates (x y): ");
        else if (!g->go)
            printf("Player B, enter coordinates (x y): ");
        
        scanf("%d %d", &g->pos.x, &g->pos.y);

        if (g->pos.x < 1 || g->pos.x > 3 || g->pos.y < 1 || g->pos.y > 3)
        {
            printf("Invalid coordinates!\n");
        }
        else
        {
            g->good = true;
        }
    } while (!g->good);
}

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

void updateBoard(Game *g)
{
    rebuildF(g);
    
    for (int i = 0; i < g->board.F.cordsCount; i++)
        strcpy(g->board.grid[g->board.F.cords[i].y][g->board.F.cords[i].x], "   ");

    for (int i = 0; i < g->R.cordsCount; i++)
        strcpy(g->board.grid[g->R.cords[i].y][g->R.cords[i].x], " O ");

    for (int i = 0; i < g->B.cordsCount; i++)
        strcpy(g->board.grid[g->B.cords[i].y][g->B.cords[i].x], " O ");

    for (int i = 0; i < g->board.S.cordsCount; i++)
        strcpy(g->board.grid[g->board.S.cords[i].y][g->board.S.cords[i].x], "[O]");
}

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

void checkWin(Game *g)
{
    if (g->board.F.cordsCount == 3 || g->val > 16)
    {
        g->over = true;
    }
    else if (g->over && ((g->R.cordsCount > 0 && g->B.cordsCount) == 0 || (g->R.cordsCount == 0 && g->B.cordsCount > 0)))
    {
        g->over = true;
    }
}

bool outOfBounds(Coordinates pos)
{
    if (pos.x == 0 || pos.y == 0 || pos.x == 4 || pos.y == 4)
        return true;
    else
        return false;
}

void pauseScreen()
{
    getchar();
    printf("Press Enter to continue...\n");
    getchar();
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    // Assume POSIX (Linux, macOS, etc.)
    system("clear");
#endif
}
