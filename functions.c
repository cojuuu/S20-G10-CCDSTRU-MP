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
        addToPlayer(&g->R, g->pos);
        updateState(&g->board.S, g->pos, ADD);
    }
    else if (g->start && !g->go)
    {
        addToPlayer(&g->B, g->pos);
        updateState(&g->board.S, g->pos, ADD);
    }
    
    if (g->start && g->R.totalPieces == 1 && g->B.totalPieces == 1)
    {
        g->start = false;
    }

    updateState(&g->board.F, g->pos, REMOVE);

    g->go = !g->go;
    g->good = false;
    g->val++;
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
        else
        {
            g->good = true;
        }
    } while (!g->good);
}

void addToPlayer(Player *currentPlayer, Coordinates pos)
{
    currentPlayer->pieces[currentPlayer->totalPieces] = pos;
    currentPlayer->totalPieces++;
}

void updateState(State *dest, Coordinates pos, char mode)
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
                dest->cords[i].x = dest->cords[dest->cordsCount].x;
                dest->cords[i].y = dest->cords[dest->cordsCount].y;

                dest->cords[dest->cordsCount].x = 0;
                dest->cords[dest->cordsCount].y = 0;

                dest->cordsCount--;
            }
        }
    }
}

void updateBoard(Game *g)
{
    for (int i = 0; i < g->board.F.cordsCount; i++)
        strcpy(g->board.grid[g->board.F.cords[i].y][g->board.F.cords[i].x], "   ");

    for (int i = 0; i < g->R.totalPieces; i++)
        strcpy(g->board.grid[g->R.pieces[i].y][g->R.pieces[i].x], " O ");

    for (int i = 0; i < g->B.totalPieces; i++)
        strcpy(g->board.grid[g->B.pieces[i].y][g->B.pieces[i].x], " O ");

    for (int i = 0; i < g->board.S.cordsCount; i++)
        strcpy(g->board.grid[g->board.S.cords[i].y][g->board.S.cords[i].x], "[O]");
}