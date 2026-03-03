#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
    Coordinates pieces[TOTAL_POSITION];
    int totalPieces;
} Player;

typedef struct
{
    Coordinates cords[TOTAL_POSITION];
    int cordsCount;
} State;

typedef struct 
{
    String3 grid[SIZE + 1][SIZE + 1];

    State S;
    State T;
    State F;
} Board;

typedef struct 
{
    int val;

    String6 result;

    bool start, over, go, found, good;

    Player R;
    Player B;

    Coordinates pos;

    Board board;
} Game;

// Function Prototypes
void Remove();
void Replace();
void Expand();
void Update();
void NextPlayerMove(Game *g);
void GameOver(Game *g);
void setUpGame(Game *g);
void setUpBoard(Board *board);
void displayBoard(Game g);
void promptPlayerMove(Game *g);
void addToPlayer(Player *currentPlayer, Coordinates pos);
void updateState(State *dest, Coordinates pos, char mode);
void updateBoard(Game *g);
bool cordsFound(Player currentPlayer, int x, int y);