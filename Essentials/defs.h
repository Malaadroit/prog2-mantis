/******************************************************************************
 *  Description     : This file contains structs and constants
 *  Author/s        : Agamata, Loraine Beatriz
 *                    Lapuz, Dale Lucian M. 
 *  Section         : S12A & S22A
 *  Last Modified   : March 27, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

#ifndef DEFS_H // Include this to prevent redefinition error
#define DEFS_H // Include this to prevent redefinition error

/******************************************************************************
 * NOTE: These definitions are placed here in defs.h to demonstrate code
 * modularization across multiple files. You may move them to different files
 * if it better fits your code organization.
 ******************************************************************************/

#define PI 3.1415
#define ARR_SIZE 10
#define MAX_PLAYER_CHAR 37 //max characters for player username (36 + 1 for null terminator)
#define MAX_PLAYERS 50 //maximum number of players that can be stored in the player list 
#define MAX_PLAYERS_IN_GAME 6 //maximum number of players that can play in a single game
#define WINNING_SCORE 20 //score needed to win the game, can be changed in settings
#define NUM_COLORS 7 //number of colors in the game
#define STANDARD_DECK  84 //number of cards in the standard deck
/**
 * Represents a 2D point
 */
typedef char String36[MAX_PLAYER_CHAR];
typedef char String50[51];

typedef struct
{
  int x; // The x-coordinate of a point
  int y; // The y-coordinate of a point
} Coordinate;

/**
 * Represents a date
 */
typedef struct
{
  int day;   // The day [1-31]
  int month; // The integer representation of the month [1-12]
  int year;  // The year
} Date;


/* ----- definitions (i.e., constants, typedefs, structs) ----- */
/*
* Represents the game settings
*/
typedef struct {
    int winningPts;
    unsigned int shufflingSeed;
    int twoPlayerMode; //for bonus feature. 0 = off, 1 = 2-Player Bonus Mode on */
} GameSettings;

/*
* Represents a single card in the deck
*/
typedef struct {
    char back[4];
    char front;
    int points;
} Card;

/*
* Represents the statistics of a player, including wins and high score
*/
typedef struct {
    int wins;
    int highScore;
} PlayerStats;

/*
* Represents a player in the game, with their username, wins, high score, current score, and the number of cards in each tank
*/
typedef struct {
    String36 username;
    PlayerStats stats;
    int currentScore;
    int tank[NUM_COLORS];
} Player;

/*
* Represents the state of the game for a single player
*/
typedef struct {
    Player* info; 
    int tank[NUM_COLORS];
    int tankPoints[NUM_COLORS];
    int score; //accumulated points in the score pile
    int scoreCards; //number of cards in the score pile
} GameState;

/*
* Represents the overall game data structure
*/
typedef struct{
    Player PlayerList[MAX_PLAYERS];
    GameState Playing[6]; //players in the current match
    String36 PlayerNames[MAX_PLAYERS];
    int playersPlaying;
} GameData;
#endif // DEFS_H; Include this to prevent redefinition error
