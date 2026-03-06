/******************************************************************************
 *  Description     : The main heart of the code used for calling out functions and creating variables.
 *  Author/s        : Agamata, Loraine 
 *                    Lapuz, Dale Lucian M.
 *  Section         : 
 *  Last Modified   : Feb 18, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>
#include "Essentials\defs.h"
#include "Essentials\helpers\helpers_1.c"
#include "Essentials\helpers\helpers_2.c"
#include "Code-Proper\menu.c"


/* ----- definitions (i.e., constants, typedefs, structs) ----- */



/* ----- function implementations ----- */
int main()
{
    int max_playing = 6;
    GameSettings settings;
    settings.shufflingSeed = Seed;
    
    String36 PlayerNames[MAX_PLAYERS] = 
    {"TheLegend27", "John1000Dragonball", "Maladroit64", "Pandaman", "Andre3000",
     "KillerQueen", "KillerBee", "Niki"};
    
    Player Playerlist[MAX_PLAYERS];
    Player Playing[max_playing];
    int checklist, checklist2;
    finalizePLNames(PlayerNames, MAX_PLAYERS);
    createPlayerList(Playerlist, PlayerNames, MAX_PLAYERS);
    
    menu(settings, Playing, Playerlist, PlayerNames, MAX_PLAYERS, MAX_PLAYER_CHAR, max_playing);
    
    return 0;
}




