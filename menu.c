/******************************************************************************
 *  Description     : main menu file chuchu
 *  Author/s        : Agamata, Loraine 
 *                    Lapuz, Dale Lucian M.
 *  Section         : 
 *  Last Modified   : Feb 18, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>
#include <string.h>

/* ----- definitions (i.e., constants, typedefs, structs) ----- */
#define MAX_PLAYER_CHAR 37
#define MAX_PLAYER_ROWS 50
typedef char String36[37];


/* ----- function implementations ----- */
void menu(char Playerlist[][37], int rows, int columns);
void displayMainMenu();
void topDesign();
void newGame(String36 List[], int rows, int columns);
void statistics();
void settingsMenu();


/* ----- Code Proper ----- */
int getChoice()
{
    int choice;

    printf("Enter choice: ");
    scanf("%d", &choice);

    return choice;
}

void newGame(String36 List[], int rows, int columns)
{
    int Players = 1, selectPlayers = 1, iPlayerArray;
    int choice = -1;

    String36 Playing[Players];

    while(!(Players >= 3 && Players <= 6))
    {
        topDesign();
        printf("How many players are going to play? (at least 3 with the max of 6): ");
        scanf("%d", &Players);
        system("cls");
    }

    topDesign();
    for(selectPlayers = 0; selectPlayers < Players; selectPlayers++)
    {

        while(!(choice >= 0 && choice <= 2))
        {
            printf("Player %d: %s \n", selectPlayers + 1, "__");
            printf("\nSelect Player %d\n", selectPlayers + 1);
            printf("[0] Add new player\n");
            printf("[1] %s\n", List[0]);
            printf("[2] %s\n", List[1]);
            choice = getChoice();
            system("cls");
        }

        switch (choice)
        {
            case 0:
            //put name 
            case 1:
            //append chuchu
                break;
            case 2:
            //append chuchu
                break;
        }
    }
}

void viewStatistics()
{
    //see 1.3.2
    //When the user is in this part of the program, the interface should display the Top 10 Players based on either (a) number of
    //wins, or (b) highest score
}

void settingsMenu()
{
    //see 1.3.3
    //set winning points min is 20 (default)
    //shuffle speed
}

void displayMainMenu()
{
    printf("Main Menu\n");
    printf("[1] New Game\n");
    printf("[2] Top Players\n");
    printf("[3] Settings\n");
    printf("[0] Exit\n");
}

void topDesign()
{
    printf("*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n");
    printf("-----------MANTIS------------\n");
    printf("*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n");
}

void menu(char Playerlist[][37], int rows, int columns)
{
    int checkContinue = 1;
    int choice = -1;

    while(!(choice >= 0 && choice <= 3))
    {
        topDesign();
        displayMainMenu();
        choice = getChoice();
        system("cls");
    }
        switch (choice)
        {
            case 1:
                newGame(Playerlist, rows, columns);
                break;

            case 2:
                viewStatistics();
                break;

            case 3:
                settingsMenu();
                break;

            case 0:
                checkContinue = 0; 
                printf("You have exited the program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n\n");
        }
    
}



