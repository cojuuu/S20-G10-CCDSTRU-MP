#include "defs.h"

/* ---------- helpers ---------- */

bool outOfBounds(Coordinates pos)
{
    bool out = false;

    if (pos.x < 1 || pos.x > SIZE || pos.y < 1 || pos.y > SIZE)
        out = true;

    return out;
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

/* mode == ADD: add only if not already present
   mode == REMOVE: remove if present */
void modifyCoordinateArr(CordsArr *dest, Coordinates pos, char mode)
{
    bool already = false;

    if (mode == ADD)
    {
        already = cordsFound(*dest, pos.x, pos.y);

        if (!already && dest->cordsCount < TOTAL_POSITION)
        {
            dest->cords[dest->cordsCount] = pos;
            dest->cordsCount++;
        }
    }
    else if (mode == REMOVE)
    {
        for (int i = 0; i < dest->cordsCount; i++)
        {
            if (dest->cords[i].x == pos.x && dest->cords[i].y == pos.y)
            {
                dest->cords[i] = dest->cords[dest->cordsCount - 1];
                dest->cords[dest->cordsCount - 1].x = 0;
                dest->cords[dest->cordsCount - 1].y = 0;
                dest->cordsCount--;

                i = dest->cordsCount;
            }
        }
    }
}

void clearScreen()
{
    printf("\033[H\033[J");
}

void pauseScreen()
{
    int ch = 0;

    printf("\nPress Enter to continue");
    do
    {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    getchar();
}

/* ---------- spec functions ---------- */

void Remove(Game *g, Coordinates pos)
{
    if (!outOfBounds(pos))
    {
        if (g->go)
            modifyCoordinateArr(&g->R, pos, REMOVE);
        else
            modifyCoordinateArr(&g->B, pos, REMOVE);

        modifyCoordinateArr(&g->board.S, pos, REMOVE);
        modifyCoordinateArr(&g->board.T, pos, REMOVE);
    }
}

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

void Replace(Game *g, Coordinates pos)
{
    bool inS = false;
    bool inT = false;

    g->found = false;

    if (!outOfBounds(pos))
    {
        if (g->go)
        {
            if (cordsFound(g->B, pos.x, pos.y))
            {
                modifyCoordinateArr(&g->B, pos, REMOVE);
                g->found = true;
            }

            if (cordsFound(g->R, pos.x, pos.y))
                g->found = true;

            if (!cordsFound(g->R, pos.x, pos.y))
                modifyCoordinateArr(&g->R, pos, ADD);
        }
        else
        {
            if (cordsFound(g->R, pos.x, pos.y))
            {
                modifyCoordinateArr(&g->R, pos, REMOVE);
                g->found = true;
            }

            if (cordsFound(g->B, pos.x, pos.y))
                g->found = true;

            if (!cordsFound(g->B, pos.x, pos.y))
                modifyCoordinateArr(&g->B, pos, ADD);
        }

        if (g->found)
        {
            inS = cordsFound(g->board.S, pos.x, pos.y);
            inT = cordsFound(g->board.T, pos.x, pos.y);

            if (!inS)
            {
                modifyCoordinateArr(&g->board.S, pos, ADD);
                g->found = false;
            }
            else if (inS && !inT)
            {
                modifyCoordinateArr(&g->board.T, pos, ADD);
                Expand(g, pos);
            }
        }
    }
}

void Update(Game *g)
{
    bool inS = false;
    bool inT = false;

    g->good = false;

    inS = cordsFound(g->board.S, g->pos.x, g->pos.y);
    inT = cordsFound(g->board.T, g->pos.x, g->pos.y);

    if (!inS)
    {
        modifyCoordinateArr(&g->board.S, g->pos, ADD);
        g->good = !g->good;
    }

    if (!g->good && inS && !inT)
    {
        modifyCoordinateArr(&g->board.T, g->pos, ADD);
        Expand(g, g->pos);
    }
}

void promptPlayerMove(Game *g)
{
    bool ok = false;

    do
    {
        if (g->go)
            printf("Player R enter coordinates x y: ");
        else
            printf("Player B enter coordinates x y: ");

        scanf("%d %d", &g->pos.x, &g->pos.y);

        if (outOfBounds(g->pos))
        {
            printf("Invalid coordinates\n");
            ok = false;
        }
        else
        {
            ok = true;
        }

    } while (!ok);
}

void NextPlayerMove(Game *g)
{
    bool valid = false;

    g->good = false;

    do
    {
        promptPlayerMove(g);

        valid = false;

        if (!g->over)
        {
            if (g->start)
            {
                if (!cordsFound(g->R, g->pos.x, g->pos.y) &&
                    !cordsFound(g->B, g->pos.x, g->pos.y))
                {
                    if (g->go)
                        modifyCoordinateArr(&g->R, g->pos, ADD);
                    else
                        modifyCoordinateArr(&g->B, g->pos, ADD);

                    modifyCoordinateArr(&g->board.S, g->pos, ADD);

                    g->good = true;
                    valid = true;
                }
                else
                {
                    printf("That cell is already taken\n");
                }
            }
            else
            {
                if ((g->go && cordsFound(g->R, g->pos.x, g->pos.y)) ||
                    (!g->go && cordsFound(g->B, g->pos.x, g->pos.y)))
                {
                    Update(g);

                    g->good = true;
                    valid = true;
                }
                else
                {
                    printf("You must select your own piece\n");
                }
            }
        }

    } while (!valid);

    if (g->start && g->R.cordsCount == 1 && g->B.cordsCount == 1)
        g->start = false;

    if (!g->over && g->good)
    {
        g->good = !g->good;
        g->go = !g->go;
        g->val++;
    }
}

void GameOver(Game *g)
{
    if (g->over && g->R.cordsCount > g->B.cordsCount)
        strcpy(g->result, "R wins");
    else if (g->over && g->R.cordsCount < g->B.cordsCount)
        strcpy(g->result, "B wins");
    else if (g->over)
        strcpy(g->result, "draw");
}

void checkWin(Game *g)
{
    bool condF = false;
    bool condMoves = false;
    bool condElim = false;

    g->board.F.cordsCount = 0;

    for (int y = 1; y <= SIZE; y++)
    {
        for (int x = 1; x <= SIZE; x++)
        {
            if (!cordsFound(g->R, x, y) && !cordsFound(g->B, x, y))
            {
                g->board.F.cords[g->board.F.cordsCount].x = x;
                g->board.F.cords[g->board.F.cordsCount].y = y;
                g->board.F.cordsCount++;
            }
        }
    }

    if (g->board.F.cordsCount == 3)
        condF = true;

    if (g->val >= MAX_MOVES)
        condMoves = true;

    if (!g->start)
    {
        if ((g->R.cordsCount > 0 && g->B.cordsCount == 0) ||
            (g->R.cordsCount == 0 && g->B.cordsCount > 0))
            condElim = true;
    }

    g->over = (condF || condMoves || condElim);
}

void updateBoard(Game *g)
{
    for (int y = 1; y <= SIZE; y++)
    {
        for (int x = 1; x <= SIZE; x++)
        {
            strcpy(g->board.grid[y][x], "   ");
        }
    }

    for (int i = 0; i < g->R.cordsCount; i++)
        strcpy(g->board.grid[g->R.cords[i].y][g->R.cords[i].x], " O ");

    for (int i = 0; i < g->B.cordsCount; i++)
        strcpy(g->board.grid[g->B.cords[i].y][g->B.cords[i].x], " O ");

    for (int i = 0; i < g->board.S.cordsCount; i++)
        strcpy(g->board.grid[g->board.S.cords[i].y][g->board.S.cords[i].x], "[O]");
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

void setUpGame(Game *g)
{
    memset(g, 0, sizeof(Game));

    g->go = true;
    g->start = true;
    g->over = false;
    g->good = false;
    g->found = false;
    g->val = 0;

    updateBoard(g);
    checkWin(g);
}