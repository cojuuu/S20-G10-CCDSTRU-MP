#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 3
#define TOTAL_POSITION (SIZE * SIZE)
#define MAX_MOVES 16
#define STR3 4
#define STR6 7
#define ADD 'a'
#define REMOVE 'r'
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

typedef char String3[STR3];
typedef char String6[STR6];

typedef struct 
{
    int x;
    int y;
} Coordinates;

typedef struct
{
    Coordinates cords[TOTAL_POSITION];
    int cordsCount;
} CordsArr;

typedef struct 
{
    String3 grid[SIZE + 1][SIZE + 1];

    CordsArr S;
    CordsArr T;
    CordsArr F;
} Board;

typedef struct 
{
    int val;

    String6 result;

    bool start, over, go, found, good;

    CordsArr R;
    CordsArr B;

    Coordinates pos;

    Board board;
} Game;

// Function Prototypes
void Remove(Game *g, Coordinates pos);
void Replace(Game *g, Coordinates pos);
void Expand(Game *g, Coordinates pos);
void Update(Game *g);
void NextPlayerMove(Game *g);
void GameOver(Game *g);
void setUpGame(Game *g);
void displayBoard(Game g);
void promptPlayerMove(Game *g);
void modifyCoordinateArr(CordsArr *dest, Coordinates pos, char mode);
void updateBoard(Game *g);
bool cordsFound(CordsArr arr, int x, int y);
void checkWin(Game *g);
bool outOfBounds(Coordinates pos);
void pauseScreen();
void clearScreen();