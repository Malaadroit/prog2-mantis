/******************************************************************************
 *  Description     : This file contains the file processing of players from players.txt file
 *  Author/s        : Agamata, Loraine Beatriz
 *                    Lapuz, Dale Lucian M. 
 *  Section         : S12A & S22A
 *  Last Modified   : March 27, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>
#include <string.h>
#include "defs.h"

/* ----- function prototypes ----- */
void finalizePLNames(String36 PLNames[], int max_players);
void createPlayerList(Player PL[], int max_players);
void updatePlayerList(Player PL[], int max_players);
/* ----- function implementations ----- */

/*
* The function reads player data from players.txt and populates the PlayerList array.
* @param PL The array of Player structs to be populated
* @param max_players The maximum number of players to read from the file
*/
void createPlayerList(Player PL[], int max_players)
{
    FILE *fp_output;
    int processList;

    fp_output = fopen("players.txt", "r");
    if(fp_output == NULL){
        printf("Error: players.txt not found! A new file will be created.\n");
        fp_output = fopen("players.txt", "w");

        for(processList = 0; processList < max_players; processList++)
        {
            fprintf(fp_output, "_ 0 0\n"); //set to 0 since score and wins are int
        }

        fclose(fp_output);
        fp_output = fopen("players.txt", "r");
    }
    
    for(processList = 0; processList < max_players; processList++)
    {
        fscanf(fp_output, "%s %d %d", PL[processList].username, &PL[processList].stats.wins, &PL[processList].stats.highScore);
    }
    
    fclose(fp_output);
}

/*
* The function updates the player data in players.txt based on the PlayerList array.
* @param PL The array of Player structs containing the updated player data
* @param max_players The maximum number of players to write to the file
*/
void updatePlayerList(Player PL[], int max_players)
{
    FILE *fp_update;
    int processList;

    fp_update = fopen("players.txt", "w");
    for(processList = 0; processList < max_players; processList++)
    {
        fprintf(fp_update, "%s %d %d\n", PL[processList].username, PL[processList].stats.wins, PL[processList].stats.highScore);
    }
    fclose(fp_update);
}

/*
* The function adds a new player name to the PlayerList array.
* @param PL The array of Player structs to be updated
* @param PLUsernames The username to be added
* @param max_players The maximum number of players in the array
* @return 1 if the username was added successfully, 0 otherwise
*/
int addPLNames(Player PL[], String36 PLUsernames, int max_players)
{
    int processList;
    int success = 0;
    for(processList = 0; processList < max_players && success == 0; processList++)
    {
        if(strcmp(PL[processList].username, "_") == 0)
        {
            strcpy(PL[processList].username, PLUsernames);
            PL[processList].stats.wins = 0;
            PL[processList].stats.highScore = 0;
            success = 1;
        }
    }
    return success;
}

/*
* The function displays the top players based on the specified sorting criteria.
* @param PlayerList The array of Player structs to be displayed
* @param max_players The maximum number of players to display
* @param sortBy The criteria for sorting (1 for wins, 2 for high score)
*/
void displayTopPlayers(Player PlayerList[], int max_players, int sortBy)
{
    Player sorted[MAX_PLAYERS];
    int i, j, maxIdx;
    Player temp;

    for(i = 0; i < max_players; i++)
        sorted[i] = PlayerList[i];

    //selection sort by chosen criteria
    for(i = 0; i < max_players - 1; i++)
    {
        maxIdx = i;

        for(j = i + 1; j < max_players; j++)
        {
            if(sortBy == 1) //sort by wins
            {
                if(sorted[j].stats.wins > sorted[maxIdx].stats.wins)
                    maxIdx = j;
            }
            else if(sortBy == 2) //sort by high score
            {
                if(sorted[j].stats.highScore > sorted[maxIdx].stats.highScore)
                    maxIdx = j;
            }
        }

        if(maxIdx != i)
        {
            temp = sorted[i];
            sorted[i] = sorted[maxIdx];
            sorted[maxIdx] = temp;
        }
    }

    // Display top 10 — skip empty slots
    int displayed = 0;
    int rank = 1;

    if(sortBy == 1)
        printf("Top 10 Players by Wins:\n\n");
    else
        printf("Top 10 Players by High Score:\n\n");

    for(i = 0; i < max_players && displayed < 10; i++)
    {
        if(strcmp(sorted[i].username, "_") != 0)
        {
            if(sortBy == 1)
                printf("%2d. %-25s Wins: %3d\n", rank, sorted[i].username, sorted[i].stats.wins);
            else
                printf("%2d. %-25s High Score: %3d\n", rank, sorted[i].username, sorted[i].stats.highScore);

            rank++;
            displayed++;
        }
    }

    if(displayed == 0)
        printf("No players found.\n");

    printf("\nPress Enter to continue...\n");
    getchar();
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