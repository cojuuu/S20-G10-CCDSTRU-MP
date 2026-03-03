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