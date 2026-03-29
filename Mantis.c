/******************************************************************************
 *  Description     : The main heart of the code used for calling out functions and creating variables.
 *  Author/s        : Agamata, Loraine Beatriz C.
 *                    Lapuz, Dale Lucian M.
 *  Section         : S12A & S22A
 *  Last Modified   : March 27, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>
#include "Essentials\defs.h"
//#include "Essentials\helpers\helpers_1.c"
#include "Essentials\helpers\helpers.c"
#include "Code-Proper\menu.c"

/* ----- function implementations ----- */
int main()
{
    int i, j;

    initRandom();

    GameSettings settings;
    settings.winningPts = WINNING_SCORE;
    settings.shufflingSeed = randomInt();
    settings.twoPlayerMode = 0; //BONUS: default off

    GameData game;

    for(i = 0; i < MAX_PLAYERS; i++)
    {
        strcpy(game.PlayerList[i].username, "_");
        game.PlayerList[i].stats.wins = 0;
        game.PlayerList[i].stats.highScore = 0;
    }

    for(i = 0; i < MAX_PLAYERS; i++)
        strcpy(game.PlayerNames[i], "_");

    for(i = 0; i < MAX_PLAYERS_IN_GAME; i++)
    {
        game.Playing[i].info = NULL;
        game.Playing[i].score = 0;
        game.Playing[i].scoreCards = 0;
        for(j = 0; j < NUM_COLORS; j++)
        {
            game.Playing[i].tank[j] = 0;
            game.Playing[i].tankPoints[j] = 0;
        }
    }

    game.playersPlaying = 0;

    createPlayerList(game.PlayerList, MAX_PLAYERS);

    //sync PlayerNames from loaded PlayerList
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(strcmp(game.PlayerList[i].username, "_") != 0)
            strcpy(game.PlayerNames[i], game.PlayerList[i].username);
    }

    menu(&settings, &game, game.PlayerList);

    return 0;
}

/**
* This is to certify that this project is my/our own work, based on my/our personal
* efforts in studying and applying the concepts learned. I/We have constructed the
* functions and their respective algorithms and corresponding code by myself/ourselves.
* The program was run, tested, and debugged by my/our own efforts. I/We further certify
* that I/we have not copied in part or whole or otherwise plagiarized the work of other
* students and/or persons, nor did I employ the use of AI in any part of the deliverable.
*
* <Agamata, Loraine Beatriz C.> (12507121)
* <Lapuz, Dale Lucian M.> (12505919)
*/