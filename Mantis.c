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

#include "C:/Users/Dale/OneDrive/Desktop/mp-mantis-starter-files/Essentials/defs.h"
#include "C:/Users/Dale/OneDrive/Desktop/mp-mantis-starter-files/Essentials/helpers/helpers_1.c"
#include "C:/Users/Dale/OneDrive/Desktop/mp-mantis-starter-files/Essentials/helpers/helpers_2.c"
#include "C:/Users/Dale/OneDrive/Desktop/mp-mantis-starter-files/Code-Proper/menu.c"

/* ----- definitions (i.e., constants, typedefs, structs) ----- */



/* ----- function implementations ----- */

int main()
{
    int Seed = -999, defaultPoints = 20;
    String36 Players[MAX_PLAYER_ROWS] = 
    {"TheLegend27", "John1000Dragonball", "Maladroit64", "Pandaman", "Andre3000",
     "KillerQueen", "KillerBee", "Niki"};
    menu(Players, MAX_PLAYER_ROWS, MAX_PLAYER_CHAR, Seed, defaultPoints);
    return 0;
}

