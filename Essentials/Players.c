/******************************************************************************
 *  Description     : <short description of the project>
 *  Author/s        : Agamata, Loraine Beatrice
 *                    Lapuz, Dale Lucian M. 
 *  Section         : 
 *  Last Modified   : March 4, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/



/* ----- preprocessor directives ----- */
#include <stdio.h>
#include <string.h>
#include "defs.h"

/* ----- function prototypes ----- */
void finalizePLNames(String36 PLNames[], int max_players);
void createPlayerList(Player PL[], String36 PLNames[], int max_players);
void updatePlayerList(Player PL[], String36 PLNames[], int max_players);
/* ----- function implementations ----- */
void createPlayerList(Player PL[], String36 PLNames[], int max_players)
{
    FILE *fp_output;
    int processList;

    fp_output = fopen("players.txt", "w");
    for(processList = 0; processList < max_players; processList++)
    {
        strcpy(PL[processList].username, PLNames[processList]);
        fprintf(fp_output, "%s\n", PL[processList].username);
    }
    
    fclose(fp_output);
}

void updatePlayerList(Player PL[], String36 PLNames[], int max_players)
{
    FILE *fp_update;
    int processList, players = 0, requiredAdding = 0, toAdd = 0, isAdded = 0;
    for(processList = 0; processList < max_players; processList++)
    {
        if(strcmp(PL[processList].username, "_") != 0)
        {
            players++; 
        }
        if(strcmp(PL[processList].username, PLNames[processList]) != 0) 
        //if not same name and is blank ("_", though technically di sya blank computer-wise, both PLNames and PL have this) then
        {
            toAdd++;
        }
    }

    requiredAdding = players + toAdd;
    for(processList = 0; processList < requiredAdding; processList++)
    {
        if(strcmp(PL[processList].username, PLNames[processList]) != 0 && strcmp(PL[processList].username, "_") == 0)
        {
            strcpy(PL[processList].username, PLNames[processList]);
        }
    }

    fp_update = fopen("players.txt", "w");
    for(processList = 0; processList < max_players; processList++)
    {
        fprintf(fp_update, "%s\n", PL[processList].username);
    }
    fclose(fp_update);
}

void finalizePLNames(String36 PLNames[], int max_players)
{
    int processList;
    for(processList = 0; processList < max_players; processList++)
    {
        if(strcmp(PLNames[processList], "") == 0)
        {
            strcpy(PLNames[processList], "_");
        }
    }
}