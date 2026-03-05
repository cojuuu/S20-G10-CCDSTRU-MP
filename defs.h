/**
 * Description     : Header file for the CCDSTRU machine project
 *                   Contains constants, type definitions, structures,
 *                   and function prototypes used by the program
 * Author/s        : De Dios, Justin Marco ; Lamano, Kyle
 * Section         : CCDSTRU S09
 * Last Modified   : March 5, 2026
 * Acknowledgments : We thank our professor, Mr. Emerico Aguilar, for
 *                   the lessons and discussions in class, which helped
 *                   us in completing this project.
 */

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

/**
 * Represents a board coordinate (x, y)
 */
typedef struct 
{
    int x;  // x-coordinate (column)
    int y;  // y-coordinate (row)
} Coordinates;

/**
 * Stores a collection of coordinates and its current size
 * Used to represent sets such as R, B, S, T, and F
 */
typedef struct
{
    Coordinates cords[TOTAL_POSITION];  // Array of coordinates
    int cordsCount;                     // Number of valid coordinates in the array
} CordsArr;

/**
 * Represents the game board for display and marker sets
 */
typedef struct 
{
    String3 grid[SIZE + 1][SIZE + 1];   // Printable board cells (1-based indexing)

    CordsArr S; // Set of marked positions 
    CordsArr T; // Set of expanded/triggered positions
    CordsArr F; // Set of free/empty positions
} Board;

/**
 * Stores the complete game state and all variables used by the program
 */
typedef struct 
{
    int val;            // Move counter            

    String6 result;     // Final result string ("R wins", "B wins", or "draw")

    bool start;         // True while in start phase
    bool over;          // True when game is over
    bool go;            // Turn flag (true = R player's turn, false = B player's turn)
    bool found;         // Helper flag used in Replace()
    bool good;          // Helper flag used for move validation/processing

    CordsArr R;         // Set of positions occupied by player R
    CordsArr B;         // Set of positions occupied by player B

    Coordinates pos;    // Current player-selected position

    Board board;        // Board display and marker sets
} Game;

/* ---------- spec functions ---------- */
void Remove(Game *g, Coordinates pos);
void Replace(Game *g, Coordinates pos);
void Expand(Game *g, Coordinates pos);
void Update(Game *g);
void NextPlayerMove(Game *g);
void GameOver(Game *g);

/* ---------- helper functions ---------- */
void setUpGame(Game *g);
void promptPlayerMove(Game *g);
void modifyCoordinateArr(CordsArr *dest, Coordinates pos, char mode);
bool outOfBounds(Coordinates pos);
bool cordsFound(CordsArr arr, int x, int y);
void updateBoard(Game *g);
void checkWin(Game *g);
void displayBoard(Game g);
void clearScreen();
void pauseScreen();
