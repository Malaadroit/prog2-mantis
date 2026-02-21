/******************************************************************************
 *  Description     : main file for everything, the main heart of the code
 *  Author/s        : Agamata, Loraine 
 *                    Lapuz, Dale Lucian M.
 *  Section         : 
 *  Last Modified   : Feb 18, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>

#include "defs.h"
#include "helpers_1.c"
#include "helpers_2.c"
#include "menu.c"

/* ----- definitions (i.e., constants, typedefs, structs) ----- */



/* ----- function implementations ----- */

int main()
{
    String36 Players[MAX_PLAYER_ROWS] = 
    {"TheLegend27", "John1000Dragonball", "Maladroit64", "Pandaman", "Andre3000",
     "KillerQueen", "KillerBee", "Niki"};
    menu(Players, MAX_PLAYER_ROWS, MAX_PLAYER_CHAR);
    return 0;
}

