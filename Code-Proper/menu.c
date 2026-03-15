/******************************************************************************
 *  Description     : main menu file chuchu
 *  Author/s        : Agamata, Loraine Beatriz C.
 *                    Lapuz, Dale Lucian M.
 *  Section         : 
 *  Last Modified   : Feb 23, 2026
 *  Acknowledgments : <list of references used in the making of this project>
 ******************************************************************************/

/* ----- preprocessor directives ----- */
#include <stdio.h>
#include <string.h>
#include "../Essentials/Helpers/helpers_1.c"
#include "../Essentials/Helpers/helpers_2.c"
#include "../Essentials/defs.h"
#include "..\Essentials\Players.c"
#include "../Essentials/GameStructure.c"

/* ----- function prototypes ----- */
//I. Core
void menu(GameSettings settings, Player Playing[], Player PlayerList[], String36 PLNames[], int rows, int columns, int MaxPlrGame);
void newGame(String36 PlayerNames[], Player Playing[], Player PlayerList[], int rows, int columns, int MaxPlrGame);
void statisticsMenu(GameSettings settings, Player Playing[], Player PlayerList[], String36 PLNames[], int rows, int columns, int MaxPlrGame);
void settingsMenu(GameSettings* settings, Player Playing[], Player PlayerList[], String36 PLNames[], int rows, int columns, int MaxPlrGame);

//II. Functions in the Core
void errUser(int sameNamePlay, int sameNamePL, char plrInp[], int* attempted); //occurs in newGame when player does not meet the requirements for username
void finalPlayers(String36 PL[], Player Playing[], Player PlayerList[], int rows, int columns, int MaxPlrGame, int* players_Playing); //called in newGame after the player creation is done
void addtoPL(String36 PLName[], int rows, String36 plrname); //called in newGame as the player creates the username.
int checkSameName(Player Playing[], char Playername[], int MaxPlrGame); //called in newGame to check if there is a same name in the player list.

//III. Extras
void displayMainMenu();
void topDesign();

/* ----- function implementations ----- */

/* I. Core Essentials */
void menu(GameSettings settings, Player Playing[], Player PlayerList[], String36 PLNames[], int rows, int columns, int MaxPlrGame)
{
    int checkContinue = 1;
    int choice = -1, processList;
    while(!(choice >= 1 && choice <= 5))
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
                newGame(PLNames, Playing, PlayerList, rows, columns, MaxPlrGame);
                break;

            case 2:
                system("cls");
                statisticsMenu(settings, Playing, PlayerList, PLNames, rows, columns, MaxPlrGame);
                break;

            case 3:
                system("cls");
                settingsMenu(&settings, Playing, PlayerList, PLNames, rows, columns, MaxPlrGame);
                break;

            case 4:
                checkContinue = 0;
                printf("You have exited the program.\n");
                break;
            case 5:
                printf("Playerlist: \n");
                for(processList = 0; processList < MAX_PLAYERS; processList++)
                {
                    printf("%s\n", PlayerList[processList].username);
                }

                processList = 0;

                printf("Playing: \n");
                for(processList = 0; processList < MaxPlrGame; processList++)
                {
                    printf("%s\n", Playing[processList].username);
                }
        }
}

void newGame(String36 PlayerNames[], Player Playing[], Player PlayerList[], int rows, int columns, int MaxPlrGame)
{
    int selectPlayers = 0, CPlr1 = 0, CPlr2 = 1; //CPlrN == Choose Player Number 1 in the choices (look code below)
    int choice = -1, inputDone = 0, attempted = 0;
    int sameNamePlaying = 0, sameNamePL = 0, overall = 0, displayPlaying, initializePlaying, checckPlayerList, checkplayerlist2; //The last 4 are tester variables
    int players_Playing = 0;

    String36 PlayerName;
    String50 Input;
    strcpy(Input, "");
    strcpy(PlayerName, "");

    while(!(players_Playing >= 3 && players_Playing <= 6))
    {
        topDesign();
        printf("How many players are going to play? (at least 3 with the max of 6):\n");
        players_Playing = numInput();
        system("cls");

    }

    for(initializePlaying = 0; initializePlaying < MaxPlrGame; initializePlaying++)
    {
        strcpy(Playing[initializePlaying].username, "_");
    }

    for(selectPlayers = 0; selectPlayers < players_Playing; selectPlayers++)
    {
        while(!(choice >= 1 && choice <= 6))
        {
            system("cls");
            topDesign();
            printf("Player %d: \n", selectPlayers + 1);
            printf("\nSelect Player %d\n", selectPlayers + 1);
            printf("[1] Add new player\n");
            printf("[2] %s\n", PlayerNames[CPlr1]); //here (CPlr1)
            printf("[3] %s\n", PlayerNames[CPlr2]); //here (CPlr2)
            // printf("Playername: %s\n", PlayerName); //Testing Purposes
            // printf("Playername's length: %d\n", strlen(PlayerName)); //Testing Purposes
            // printf("Overall? %d", overall);
            choice = numInput();
        }

            switch (choice)
            {
                case 1:
                    sameNamePL = 1;
                    sameNamePlaying = 1;
                    overall = sameNamePL + sameNamePlaying;
                    
                    while(((strlen(Input) > 36 || strlen(Input) == 0) || strcspn(Input, " ") != strlen(Input)) || overall != 0)
                    {
                        system("cls");
                        topDesign();
                        errUser(sameNamePlaying, sameNamePL, Input, &attempted);
                        printf("Username: ");
                        strInput(Input, 51);
                        attempted++;
                        sameNamePlaying = checkSameName(Playing, Input, MaxPlrGame);
                        sameNamePL = checkSameName(PlayerList, Input, MAX_PLAYERS);
                        overall = sameNamePlaying + sameNamePL;
                    }
                    strcpy(PlayerName, Input);
                    strcpy(Playing[selectPlayers].username, PlayerName);
                    addtoPL(PlayerNames, rows, PlayerName);
                    choice = -1;
                    attempted = 0;
                    break;

                case 2:
                    strcpy(PlayerName,PlayerNames[CPlr1]);
                    strcpy(Playing[selectPlayers].username, PlayerName);
                    addtoPL(PlayerNames, rows, PlayerName);
                    CPlr1++;
                    CPlr2++;
                    while(checkSameName(Playing, PlayerNames[CPlr1], MaxPlrGame) == 1)
                    //This statement is when the choice for Playername is in the Playing List despite increment.
                    {
                        CPlr1++; 
                        CPlr2++;    
                    }
                    choice = -1;
                    break;
                    
                case 3:
                    strcpy(PlayerName,PlayerNames[CPlr2]);
                    strcpy(Playing[selectPlayers].username, PlayerName);
                    addtoPL(PlayerNames, rows, PlayerName);
                    CPlr2++;
                    while(checkSameName(Playing, PlayerNames[CPlr2], MaxPlrGame) == 1)
                    //Same thing but for the third choice.
                    {
                        CPlr2++;    
                    }
                    choice = -1;
                    break;
                case 4:
                    for(checckPlayerList = 0; checckPlayerList < MAX_PLAYERS; checckPlayerList++)
                    {
                        printf("%s\n", PlayerList[checckPlayerList].username);
                    }
                    scanf("%d", &choice);
                    break;
                case 5:
                    for(checkplayerlist2 = 0; checkplayerlist2 < MaxPlrGame; checkplayerlist2++)
                    {
                        printf("%s\n", Playing[checkplayerlist2].username);
                    }
                    scanf("%d", &choice);
                    break;
                case 6:
                    for(checkplayerlist2 = 0; checkplayerlist2 < MAX_PLAYERS; checkplayerlist2++)
                    {
                        printf("%s\n", PlayerNames[checkplayerlist2]);
                    }
                    scanf("%d", &choice);
                    break;
            } 
    }
    updatePlayerList(PlayerList, PlayerNames, MAX_PLAYERS);
    finalPlayers(PlayerNames, Playing, PlayerList, rows, columns, MaxPlrGame, &players_Playing);
}

void statisticsMenu(GameSettings settings, Player Playing[], Player PlayerList[], String36 PLNames[], int rows, int columns, int MaxPlrGame)
{
    int choice = 0;
    while(!(choice >= 1 && choice <= 3))
    {
        system("cls");
        topDesign();
        printf("[1] Top 10 MaxPlrGame based on Wins\n");
        printf("[2] Top 10 MaxPlrGame based on Most Number of points.\n");
        printf("[3] Exit Top 10 MaxPlrGame\n");
        choice = numInput();
    }

    switch(choice)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            menu(settings, Playing, PlayerList, PLNames, rows, columns, MaxPlrGame);
            break;
    }
}

void settingsMenu(GameSettings* settings, Player Playing[], Player PlayerList[], String36 PLNames[], int rows, int columns, int MaxPlrGame)
{

    int choice = 0;
    while(!(choice >= 1 && choice <= 3))
    {
        topDesign();
        printf("Settings\n");
        printf("[1] Change seed\n");
        printf("[2] Change default points to win\n");
        printf("[3] Exit Settings\n");
        choice = numInput();
        system("cls");
    }

    switch(choice)
    {
        case 1:
        {
            int yn = 0;
            printf("The default shuffle speed is normal.\n");
            printf("Would you like to change the shuffle seed?\n");
            printf("[1] Yes\n[2] No\n");
            
            while(!(yn == 1 || yn == 2))
                    yn = numInput();
        
            if(yn == 1)
            {
                do
                {
                    printf("Enter new shuffle seed. \n");
                    settings->shufflingSeed = numInput();
                    if(settings->shufflingSeed < 0)
                        printf("Please enter a non-negative number. \n");
                } while(settings->shufflingSeed < 0);
                printf("Your new shuffle speed is: %d\n", settings->shufflingSeed);
            }

            else if(yn == 2){
                settings->shufflingSeed = Seed;
            }
            
            else
                printf("You have entered a wrong number! Choose from 1 or 2 only. \n");
            
            break;
        }
        case 2:
        {   
            int yn = 0;
            printf("The default winning points is 20.\n");
            printf("Would you like to change the winning point?\n");
            printf("[1] Yes\n[2] No\n");
            
            
            while(!(yn == 1 || yn == 2))
                    yn = numInput();

            if(yn == 1){
                do
                {
                    //printf("Enter new winning point: ");
                    settings->winningPts = numInput();
                    if(settings->winningPts <= 0)
                        printf("Please enter a number above 0. \n");
                }while(settings->winningPts <= 0);
                

            printf("Your new shuffle speed is: %d\n", settings->winningPts);
            }

            else if(choice == 2){
                settings->winningPts = 20; 
            }
            
            else
                printf("You have entered a wrong number! Choose from 1 or 2 only. \n");
        }
            break;

        case 3:
            menu(*settings, Playing, PlayerList, PLNames, rows, columns, MaxPlrGame);
            break;
    }
}


/* II. Extra Essentials */
void displayMainMenu()
{ 
    printf("Main Menu\n");
    printf("[1] New Game\n");
    printf("[2] Statistics\n");
    printf("[3] Settings\n");
    printf("[4] Exit\n");
}

void topDesign()
{
    printf("*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n");
    printf("-----------MANTIS------------\n");
    printf("*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n");
}

int checkSameName(GameState List[], char Playername[], int MaxPlrGame)
{
    int processList, sameName = 0, checker = 0;

    for(processList = 0; processList < MaxPlrGame && sameName == 0; processList++)
    {
        if(strcmp(Playername, List[processList].username) == 0)
        {
            sameName = 1;
        }
    }
    return sameName;
}

void errUser(int sameNamePlay, int sameNamePL, char plrInp[], int* attempted)
{
    if(sameNamePlay == 1 && *attempted != 0)
    {
        printf("There is already an existing username!\n");
        *attempted = 0;
    }
    if(sameNamePL == 1 && *attempted != 0)
    {
        printf("There is already a username in the player list! Choose there instead!\n");
        *attempted = 0;
    }
    if(strcspn(plrInp, " ") != strlen(plrInp) && *attempted != 0)
    {
        printf("Spaces should not exist in your username.\n");
        *attempted = 0;
    }
    if(strlen(plrInp) == 0 && *attempted != 0)
    {
        printf("You have not typed anything yet!\n");
        *attempted = 0;
    }
    else if(strlen(plrInp) > 36 && *attempted != 0)
    {
        printf("Your username is too long!\n");
        *attempted = 0;
    }
}

void finalPlayers(String36 PL[], Player Playing[], Player PlayerList[], int rows, int columns, int MaxPlrGame, int* players_Playing) //(String36 PlayerNames[], Player Playing[], Player PlayerList[], int rows, int columns, int* MaxPlrGame)
{
    int choice = -1, choice2 = -1, displayFinal, done = 0;

    while(done == 0)
    {
        while(!(choice == 1 || choice == 2)) 
        {
            system("cls");
            topDesign();
            printf("Playing:\n");
            for(displayFinal = 0; displayFinal < *players_Playing; displayFinal++)
            {
                printf("%s\n", Playing[displayFinal].username);
            }
            printf("\nIs this final?\n");
            printf("[1] Yes\n");
            printf("[2] No\n");
            choice = numInput();

            if(choice == 3)
            {
                for(displayFinal = 0; displayFinal < MAX_PLAYERS; displayFinal++)
                {
                    printf("%s\n", PlayerList[displayFinal]);
                }
                scanf("%s", &choice);
            }
        }

        if(choice == 1)
        {
            //game function chuchu this is where they start playing the game yayyy what fun :DD
            done = 1;
        }
        else if (choice == 2)
        {
            while(!(choice2 == 1 || choice2 == 2))
            {
                system("cls");
                topDesign();
                printf("Do you want to reset?\n\n");
                printf("Take note: if you proceed to still do this, you will have to reconfigure the new game portion.\n");
                printf("That means having to re-enter the number of players, as well as inputting their names if they opt to.\n");
                printf("\nAre you ABSOLUTELY sure that you want to do this?\n");
                printf("[1] Yes\n");
                printf("[2] No\n");
                choice2 = numInput();
                }
                if(choice2 == 1)
                {
                    done = -1;
                    *players_Playing = 0;
                    system("cls");
                    newGame(PL, Playing, PlayerList, rows, columns, MaxPlrGame);
                }
                else if(choice2 == 2)
                {
                    choice = -1;
                    choice2 = -1;
                }
        }
    }
}

void addtoPL(String36 PLName[], int rows, String36 plrname)
{
    int processPL, isAdded = 0;

    for(processPL = 0; processPL < rows && isAdded == 0; processPL++)
    {
        if(strcmp(PLName[processPL], "_") == 0)
        {
            strcpy(PLName[processPL], plrname);
            isAdded = 1;
        }
    }
}

