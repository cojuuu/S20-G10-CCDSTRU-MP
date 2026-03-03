#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 3
#define TOTAL_POSITION (SIZE * SIZE)
#define MAX_MOVES 16
#define STR3 4
#define STR6 7

typedef char String3[STR3];
typedef char String6[STR6];

typedef struct 
{
    int x;
    int y;
} Coordinates;

typedef struct
{
    Coordinates pieces[TOTAL_POSITION];
    int totalPieces;
} Player;

typedef struct 
{
    String3 grid[SIZE + 1][SIZE + 1];

    Coordinates S[TOTAL_POSITION];
    int sCount;

    Coordinates T[TOTAL_POSITION];
    int tCount;

    Coordinates F[TOTAL_POSITION];
    int fCount;
} Board;

typedef struct 
{
    int val;

    String6 result;

    bool start, over, go, found;

    Player R;
    Player B;

    Coordinates pos;

    Board board;
} Game;

// Function Prototype
void Remove();
void Replace();
void Expand();
void Update();
void NextPlayerMove();
void GameOver(Game *g);
void setUpGame(Game *g);
void setUpBoard(Board *board);
void displayBoard(Game g);