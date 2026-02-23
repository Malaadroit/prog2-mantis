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

#include "C:\Users\BESY C. AGAMATA\c coding tut\c files\CCPROG2\MP\mp-github\prog2-mantis\Essentials\defs.h"
#include "C:\Users\BESY C. AGAMATA\c coding tut\c files\CCPROG2\MP\mp-github\prog2-mantis\Essentials\Helpers\helpers_1.c"
#include "C:\Users\BESY C. AGAMATA\c coding tut\c files\CCPROG2\MP\mp-github\prog2-mantis\Essentials\Helpers\helpers_2.c"
#include "C:\Users\BESY C. AGAMATA\c coding tut\c files\CCPROG2\MP\mp-github\prog2-mantis\Code-Proper\menu.c"

/* ----- definitions (i.e., constants, typedefs, structs) ----- */



/* ----- function implementations ----- */

int main()
{
    GameSettings settings;
    int Seed = -999, defaultPoints = 20;
    String36 Players[MAX_PLAYER_ROWS] = 
    {"TheLegend27", "John1000Dragonball", "Maladroit64", "Pandaman", "Andre3000",
     "KillerQueen", "KillerBee", "Niki"};
    menu(Players, MAX_PLAYER_ROWS, MAX_PLAYER_CHAR, &settings);
    return 0;
}



