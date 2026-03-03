#include "defs.h"

void Remove(Game *g)
{
    if (g->go)
        modifyCoordinateArr(&g->R, g->pos, REMOVE);
    else if (!g->go)
        modifyCoordinateArr(&g->B, g->pos, REMOVE);
    
    modifyCoordinateArr(&g->board.S, g->pos, REMOVE);
    modifyCoordinateArr(&g->board.T, g->pos, REMOVE);
}

void Replace()
{

}

void Expand()
{

}

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
        Expand();
    }
}

void NextPlayerMove(Game *g)
{
    promptPlayerMove(g);

    if (g->start && g->go)
    {
        modifyCoordinateArr(&g->R, g->pos, ADD);
        modifyCoordinateArr(&g->board.S, g->pos, ADD);
    }
    else if (g->start && !g->go)
    {
        modifyCoordinateArr(&g->B, g->pos, ADD);
        modifyCoordinateArr(&g->board.S, g->pos, ADD);
    }
    
    if (!g->start)
    {
        printf("update!\n");
        Update(g);
    }

    if (g->start && g->R.cordsCount == 1 && g->B.cordsCount == 1)
    {
        g->start = false;
    }

    modifyCoordinateArr(&g->board.F, g->pos, REMOVE);

    g->go = !g->go;
    g->good = false;
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
        g->good = true;

        if (g->go)
            printf("Player R, enter coordinates (x y): ");
        else if (!g->go)
            printf("Player B, enter coordinates (x y): ");
        
        scanf("%d %d", &g->pos.x, &g->pos.y);

        if (g->pos.x < 1 || g->pos.x > 3 || g->pos.y < 1 || g->pos.y > 3)
        {
            printf("Invalid coordinates!\n");
            g->good = false;
        }
        else if (!g->start)
        {
            if ((g->go && !cordsFound(g->R, g->pos.x, g->pos.y)) || (!g->go && !cordsFound(g->B, g->pos.x, g->pos.y)))
            {
                printf("Please choose your own piece!\n");
                g->good = false;
            }
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