/******************************************************************************
 *  Description     : main menu file chuchu
 *  Author/s        : Agamata, Loraine 
 *                    Lapuz, Dale Lucian M.
 *  Section         : 
 *  Last Modified   : Feb 23, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>
#include <string.h>
#include "../Essentials/Helpers/helpers_1.c"

/* ----- definitions (i.e., constants, typedefs, structs) ----- */
#define MAX_PLAYER_CHAR 37
#define MAX_PLAYER_ROWS 50
typedef char String36[MAX_PLAYER_CHAR];


/* ----- function prototypes ----- */
void menu(char Playerlist[][37], int rows, int columns, int seed, int points);
void displayMainMenu();
void topDesign();
void newGame(String36 List[], int rows, int columns);
void statisticsMenu(char Playerlist[][37], int rows, int columns, int seed, int points);
void settingsMenu(char Playerlist[][37], int rows, int columns, int* seed, int* points);

/* ----- code proper ----- */
void menu(char Playerlist[][37], int rows, int columns, int seed, int points)
{
    int checkContinue = 1;
    int choice = -100;
    while(!(choice >= 1 && choice <= 4))
    {
        system("cls");
        topDesign();
        displayMainMenu();
        choice = numInput();
    }
        switch (choice)
        {
            case 1:
                system("cls");
                newGame(Playerlist, rows, columns);
                break;

            case 2:
                system("cls");
                statisticsMenu(Playerlist, rows, columns, seed, points);
                break;

            case 3:
                system("cls");
                settingsMenu(Playerlist, rows, columns, &seed, &points);
                break;

            case 4:
                checkContinue = 0;
                printf("You have exited the program.\n");
                break;
        }
}


void newGame(String36 List[], int rows, int columns)
{
    int Players = -1, selectPlayers = 0, CPlr1 = 0, CPlr2 = 1; //CPlrN == Choose Player Number 1 in the choices (look code below)
    int choice = -1, inputDone = 0;
    String36 PlayerName;
    strcpy(PlayerName, "");
    while(!(Players >= 3 && Players <= 6))
    {
        topDesign();
        printf("How many players are going to play? (at least 3 with the max of 6):\n");
        Players = numInput();
        system("cls");
    }

    String36 Playing[Players];
    

    for(selectPlayers = 0; selectPlayers < Players; selectPlayers++)
    {
        while(!(choice >= 1 && choice <= 3))
        {
            system("cls");
            topDesign();
            printf("Player %d: %s \n", selectPlayers + 1, "____");
            printf("\nSelect Player %d\n", selectPlayers + 1);
            printf("[1] Add new player\n");
            printf("[2] %s\n", List[CPlr1]); //here (CPlr1)
            printf("[3] %s\n", List[CPlr2]); //here (CPlr2)
            printf("Player Name: %s\n", PlayerName);
            choice = numInput();
        }

            switch (choice)
            {
                case 1:
                    system("cls");
                    printf("Username: ");
                    strInput(PlayerName, MAX_PLAYER_CHAR);
                    choice = -1;
                    break;
                case 2:
                //append chuchu
                    break;
                case 3:
                //append chuchu
                    break;
            }
    }
}

void statisticsMenu(char Playerlist[][37], int rows, int columns, int seed, int points)
{
    int choice;
    while(!(choice >= 1 && choice <= 3))
    {
        system("cls");
        topDesign();
        printf("[1] Top 10 Players based on Wins\n");
        printf("[2] Top 10 Players based on Most Number of points.\n");
        printf("[3] Exit Top 10 Players\n");
        choice = numInput();
    }

    switch(choice)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            menu(Playerlist, rows, columns, seed, points);
            break;
    }
}

void settingsMenu(char Playerlist[][37], int rows, int columns, int* seed, int* points)
{

    int choice;
    while(!(choice >= 1 && choice <= 3))
    {
        topDesign();
        printf("[1] Change seed\n");
        printf("[2] Change default points to win\n");
        printf("[3] Exit Settings\n");
        choice = numInput();
        system("cls");
    }

    switch(choice)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            system("cls");
            menu(Playerlist, rows, columns, *seed, *points);
            break;
    }
}

void displayMainMenu()
{ 
    printf("Main Menu\n");
    printf("[1] New Game\n");
    printf("[2] Top Players\n");
    printf("[3] Settings\n");
    printf("[4] Exit\n");
}

void topDesign()
{
    printf("*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n");
    printf("-----------MANTIS------------\n");
    printf("*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n");
}





