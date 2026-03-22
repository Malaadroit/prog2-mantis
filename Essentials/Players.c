/******************************************************************************
 *  Description     : <short description of the project>
 *  Author/s        : Agamata, Loraine Beatriz
 *                    Lapuz, Dale Lucian M. 
 *  Section         : 
 *  Last Modified   : March 15, 2026
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

//redesigning of fileprocessing of player.txt
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
            fprintf(fp_output, "_ 0 0\n"); //set to 0 since hsore and wins are int
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
                printf("%d. %-25s Wins: %3d\n", rank, sorted[i].username, sorted[i].stats.wins);
            else
                printf("%d. %-25s High Score: %3d\n", rank, sorted[i].username, sorted[i].stats.highScore);

            rank++;
            displayed++;
        }
    }

    if(displayed == 0)
        printf("No players found.\n");

    printf("\nPress Enter to continue...\n");
    getchar();
}