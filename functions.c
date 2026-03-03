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

void NextPlayerMove()
{

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

    for (int x = 1; x <= SIZE; x++)
    {
        for (int y = 1; y <= SIZE; y++)
        {
            board->F[board->fCount].x = x;
            board->F[board->fCount].y = y;
            board->fCount++;
         }
    }
}