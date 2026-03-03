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
}

void GameOver(Game *g)
{
    if (g->over && (g->R.totalPieces > g->B.totalPieces))
        strcpy(g->result, "R wins");
    else if (g->over && (g->R.totalPieces < g->B.totalPieces))
        strcpy(g->result, "B wins");
    else if (g->over && (g->R.totalPieces == g->B.totalPieces))
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
            board->F[board->fCount].x = x;
            board->F[board->fCount].y = y;
            board->fCount++;
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
            printf("%s|", g.board.grid[y][x]);
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
    } while (!g->good);
}