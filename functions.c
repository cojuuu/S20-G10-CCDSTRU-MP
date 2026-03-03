#include "defs.h"

void Remove()
{

}

void Replace()
{

}

void Expand()
{

}

void Update()
{

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

    setUpBoard(&g->board);
}

void setUpBoard(Board *board)
{
    for (int i = 0; i < SIZE + 1; i++)
    {
        for (int j = 0; j < SIZE + 1; j++)
        {
            strcpy(board->grid[i][j], "   ");
        }
    }

    for (int y = 1; y <= SIZE; y++)
    {
        for (int x = 1; x <= SIZE; x++)
        {
            board->F.cords[board->F.cordsCount].x = x;
            board->F.cords[board->F.cordsCount].y = y;
            board->F.cordsCount++;
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

int findIndex(CordsArr arr, Coordinates pos)
{
    int idx = -1;
    bool found = false;

    for (int i = 0; i < arr.cordsCount; i++)
    {
        if (!found && arr.cords[i].x == pos.x && arr.cords[i].y == pos.y)
        {
            idx = i;
            found = true;
        }
    }

    return idx;
}

void addUnique(CordsArr *arr, Coordinates pos)
{
    int idx = findIndex(*arr, pos);

    if (idx == -1)
    {
        if (arr->cordsCount < TOTAL_POSITION)
        {
            arr->cords[arr->cordsCount] = pos;
            arr->cordsCount++;
        }
    }
}

void removeIfPresent(CordsArr *arr, Coordinates pos)
{
    int idx = findIndex(*arr, pos);

    if (idx != -1)
    {
        arr->cords[idx] = arr->cords[arr->cordsCount - 1];

        arr->cords[arr->cordsCount - 1].x = 0;
        arr->cords[arr->cordsCount - 1].y = 0;

        arr->cordsCount--;
    }
}