/* ----- preprocessor directives ----- */
#include <stdio.h>
#include <string.h>
#include "../Essentials/Helpers/helpers_1.c"
#include "../Essentials/Helpers/helpers_2.c"
#include "../Essentials/defs.h"
#include "../Essentials/Players.c"
#include "../Essentials/GameStructure.c"


/* ----- function prototypes ----- */
//I. Core
void menu(GameSettings *settings, GameData *game);
void newGame(GameSettings *settings, GameData *game);
void statisticsMenu(GameSettings *settings, GameData *game);
void settingsMenu(GameSettings *settings, GameData *game);
void runGame(GameState Playing[], int numPlayers, GameSettings settings);

// II. Helper Functions for Player Selection
void selectPlayers(GameState Playing[], Player PlayerList[], String36 PlayerNames[], int *players_Playing);
void createNewPlayer(Player PlayerList[], String36 PlayerNames[], int max_players, String36 name);
int findPlayer(Player PlayerList[], int max_players, String36 name);
int checkSameName(GameState List[], char Playername[], int MaxPlrGame); //GameState stuct to access Player Info
void errUser(int sameNamePlay, int sameNamePL, char plrInp[], int *attempted);
void addtoPL(String36 PLName[], int rows, String36 plrname);
void displayAvailablePlayers(Player PlayerList[], int max_players);
void finalPlayers(GameSettings *settings, GameData *game, int *confirmed);
void displayTopPlayers(Player PlayerList[], int max_players, int sortBy);

//III. Extras
void displayMainMenu();
void topDesign();

/* ----- function implementations ----- */

/* I. Core Essentials */
void menu(GameSettings *settings, GameData *game)
{
    int checkContinue = 1;
    int choice = 0;
    while(checkContinue == 1){
        choice = 0; //reset choice each loop iteration

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
                    newGame(settings, game);
                    break;

                case 2:
                    system("cls");
                    statisticsMenu(settings, game);
                    break;

                case 3:
                    system("cls");
                    settingsMenu(settings, game);
                    break;

                case 4:
                    checkContinue = 0;
                    printf("You have exited the program.\n");
                    break;
                // case 5:
                //     printf("Playerlist: \n");
                //     for(processList = 0; processList < MAX_PLAYERS; processList++)
                //     {
                //         printf("%s\n", game->PlayerList[processList].username);
                //     }

                //     printf("Playing: \n");
                //     for(processList = 0; processList < game->playersPlaying; processList++)
                //     {
                //         printf("%s\n", Playing[processList].username);
                //     }
                //     break;
            }
    }
}

void newGame(GameSettings *settings, GameData *game)
{
    int players_Playing = 0;
    int confirmed = 0;

    while(confirmed == 0)
    {
        players_Playing = 0;

        while(!(players_Playing >= 3 && players_Playing <= 6))
        {
            topDesign();
            printf("How many players are going to play? (minimum 3, maximum 6):\n");
            players_Playing = numInput();
            //system("cls");

            if(!(players_Playing >= 3 && players_Playing <= 6))
                printf("Invalid number. Please enter between 3 and 6.\n");
        }
        game->playersPlaying = players_Playing;

        // Initialize Playing array
        for(int i = 0; i < MAX_PLAYERS_IN_GAME; i++)
        {
            game->Playing[i].info = NULL; //no player assigned yet
            game->Playing[i].score = 0;
            game->Playing[i].scoreCards = 0;
            for(int j = 0; j < NUM_COLORS; j++)
            {
                game->Playing[i].tank[j] = 0;
                game->Playing[i].tankPoints[j] = 0;
            }
        }

        //select players
        selectPlayers(game->Playing, game->PlayerList, game->PlayerNames, &game->playersPlaying);

        //save updated player list
        updatePlayerList(game->PlayerList, MAX_PLAYERS);

        //finalize and start game
        finalPlayers(settings, game, &confirmed);
    }
    runGame(game->Playing, game->playersPlaying, *settings);
}

void errUser(int sameNamePlay, int sameNamePL, char plrInp[], int *attempted)
{
    if(sameNamePlay == 1 && *attempted != 0)
    {
        printf("There is already a player with that username in the game!\n");
        *attempted = 0;
    }
    if(sameNamePL == 1 && *attempted != 0)
    {
        printf("That username already exists in the player list! Select them instead.\n");
        *attempted = 0;
    }
    if(strcspn(plrInp, " ") != strlen(plrInp) && *attempted != 0)
    {
        printf("Spaces are not allowed in usernames.\n");
        *attempted = 0;
    }
    if(strlen(plrInp) == 0 && *attempted != 0)
    {
        printf("You have not entered anything yet!\n");
        *attempted = 0;
    }
    else if(strlen(plrInp) > 36 && *attempted != 0)
    {
        printf("Username is too long (max 36 characters).\n");
        *attempted = 0;
    }
}

void addtoPL(String36 PLName[], int rows, String36 plrname)
{
    int processPL;
    int isAdded = 0;

    for(processPL = 0; processPL < rows && isAdded == 0; processPL++)
    {
        if(strcmp(PLName[processPL], "_") == 0)
        {
            strcpy(PLName[processPL], plrname);
            isAdded = 1;
        }
    }
}

void selectPlayers(GameState Playing[], Player PlayerList[], String36 PlayerNames[], int *players_Playing)
{
    int i, j;
    String36 input;
    int validInput, index, choice, attempted, sameNamePlaying, sameNamePL;

    for(i = 0; i < *players_Playing; i++)
    {
        validInput = 0;

        while(validInput == 0)
        {
            system("cls");
            topDesign();

            printf("Player %d\n\n", i + 1);
            printf("[1] Select existing player\n");
            printf("[2] Create new player\n");
            choice = numInput();

            if(choice == 1)
            {
                displayAvailablePlayers(PlayerList, MAX_PLAYERS);
                //printf("Enter player number: ");
                int plyrNum = numInput();

                //counts non empty usernames in playerlist
                int availCount = 0;
                int k;
                for(k = 0; k < MAX_PLAYERS; k++)
                {
                    if(strcmp(PlayerList[k].username, "_") != 0)
                        availCount++;
                }

                if(plyrNum < 1 || plyrNum > availCount)
                {
                    printf("Invalid player number. Please select from 1 to %d.\n", availCount);
                }
                else
                {
                    int count = 0;
                    index = -1;
                    for(k = 0; k < MAX_PLAYERS && index == -1; k++)
                    {
                        if(strcmp(PlayerList[k].username, "_") != 0)
                        {
                            count++;
                            if(count == plyrNum)
                                index = k;
                        }
                    }

                    if(checkSameName(Playing, PlayerList[index].username, *players_Playing) == 1)
                    {
                        printf("That player is already in the game.\n");
                    }
                    else
                    {
                        Playing[i].info = &PlayerList[index];
                        Playing[i].score = 0;
                        Playing[i].scoreCards = 0;
                        for(j = 0; j < NUM_COLORS; j++)
                        {
                            Playing[i].tank[j] = 0;
                            Playing[i].tankPoints[j] = 0;
                        }
                        validInput = 1;
                    }
                } 
            } 
            else if(choice == 2)
            {
                attempted = 0;
                sameNamePlaying = 0;
                sameNamePL = 0;
                strcpy(input, "");
                validInput = 0;

                while(validInput == 0)
                {
                    system("cls");
                    topDesign();
                    printf("Player %d | Create new player\n\n", i + 1);
                    errUser(sameNamePlaying, sameNamePL, input, &attempted);
                    printf("Enter new username (max 36 chars, no spaces): ");
                    strInput(input, MAX_PLAYER_CHAR);
                    attempted = 1;

                    if(strlen(input) == 0 || strlen(input) > 36 || strcspn(input, " ") != strlen(input))
                    {
                        sameNamePlaying = 0;
                        sameNamePL = 0;
                    }
                    else
                    {
                        sameNamePlaying = checkSameName(Playing, input, *players_Playing);
                        sameNamePL = (findPlayer(PlayerList, MAX_PLAYERS, input) != -1); //checks if username already exists in player list

                        if(sameNamePlaying == 0 && sameNamePL == 0)
                        {
                            createNewPlayer(PlayerList, PlayerNames, MAX_PLAYERS, input);
                            index = findPlayer(PlayerList, MAX_PLAYERS, input); 

                            if(index != -1)
                            {
                                Playing[i].info = &PlayerList[index];
                                Playing[i].score = 0;
                                Playing[i].scoreCards = 0;
                                for(j = 0; j < NUM_COLORS; j++)
                                {
                                    Playing[i].tank[j] = 0;
                                    Playing[i].tankPoints[j] = 0;
                                }
                                validInput = 1;
                            }
                        }
                    }
                } 
            } 
            else
            {
                printf("Invalid option.\n");
            }
        } 
    } 
} 

void createNewPlayer(Player PlayerList[], String36 PlayerNames[], int max_players, String36 name)
{
    int i;
    int added = 0;

    for(i = 0; i < max_players && added == 0; i++)
    {
        if(strcmp(PlayerList[i].username, "_") == 0)
        {
            strcpy(PlayerList[i].username, name);
            PlayerList[i].stats.wins = 0;
            PlayerList[i].stats.highScore = 0;
            addtoPL(PlayerNames, max_players, name);
            added = 1;
        }
    }

    if(added == 0)
        printf("Player list full.\n");
}

int findPlayer(Player PlayerList[], int max_players, String36 name)
{
    int i;
    int index = - 1;

    for(i = 0; i < max_players && index == -1; i++)
    {
        if(strcmp(PlayerList[i].username, name) == 0)
            index = i;
    }

    return index;
}

int checkSameName(GameState List[], char Playername[], int MaxPlrGame)
{
    int processList, sameName = 0, checker = 0;
    for(processList = 0; processList < MaxPlrGame && sameName == 0; processList++)
    {
        if(List[processList].info != NULL && strcmp(Playername, List[processList].info->username) == 0) //added NULL since it crashes on unsigned value
        {
            sameName = 1;
        }
    }

    return sameName;
}

int usernameExists(GameState List[], int size, String36 name)
{
    int i;
    int stop = 0; int exists = 0;
    for(i = 0; i < size && stop != 1; i++){
        if(List[i].info != NULL && strcmp(List[i].info->username, name) == 0 && stop != 1){
            exists = 1;
            stop = 1;
        }
    }
    return exists;
}

void displayAvailablePlayers(Player PlayerList[], int max_players)
{
    int i;

    printf("\nAvailable Players:\n");

    for(i = 0; i < max_players; i++)
    {
        if(strcmp(PlayerList[i].username, "_") != 0)
        {
            printf("[%d] %-25s\t\t(Wins:%3d HighScore:%3d)\n", i + 1, PlayerList[i].username, PlayerList[i].stats.wins, PlayerList[i].stats.highScore);
        }
    }

    printf("\n");
}

void statisticsMenu(GameSettings *settings, GameData *game)
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
            system("cls");
            topDesign();
            displayTopPlayers(game->PlayerList, MAX_PLAYERS, 1);
            break;
        case 2:
        system("cls");
            topDesign();
            displayTopPlayers(game->PlayerList, MAX_PLAYERS, 2);
            break;
        case 3:
           // menu(settings, game);
            break;
    }
}

void settingsMenu(GameSettings* settings, GameData *game)
{

    int choice = 0;
    while(!(choice >= 1 && choice <= 3))
    {   system("cls");
        topDesign();
        printf("Settings\n");
        printf("[1] Change seed\n");
        printf("[2] Change default points to win\n");
        printf("[3] Exit Settings\n");
        choice = numInput();
        
    }

    switch(choice)
    {
        case 1:
        {
            int yn = 0;
            printf("The default shuffle speed is %d.\n" , settings->shufflingSeed);
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
                //settings->shufflingSeed = Seed;
                printf("Shuffle seed remains at default: %d\n", settings->shufflingSeed);
            }
            printf("Press Enter to continue...\n");
            getchar();
            break;
        }
        case 2:
        {   
            int yn = 0;
            printf("The default winning points is: %d.\n", settings->winningPts);
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

            else if(yn == 2){
                printf("Winning point remains at default: %d\n", settings->winningPts);
            }
            
            break;
        }
        case 3:
           // menu(settings, game);
            break;
    }
}


void finalPlayers(GameSettings *settings, GameData *game, int *confirmed)
{
    int choice = -1, choice2 = -1, displayFinal, done = 0, i;

    while(done == 0)
    {
        choice = -1;
        while(!(choice == 1 || choice == 2))
        {
            system("cls");
            topDesign();
            printf("Playing:\n\n");
            for(i = 0; i < game->playersPlaying; i++)
            {
                printf("  [%d] %s\n", i + 1,
                       game->Playing[i].info->username);
            }
            printf("\nIs this lineup final?\n");
            printf("[1] Yes = start the game\n");
            printf("[2] No  = go back and reconfigure\n");
            choice = numInput();
        }

        if(choice == 1)
        {
            *confirmed = 1;
            done = -1;
        }
        else if(choice == 2)
        {
            choice2 = -1;
            while(!(choice2 == 1 || choice2 == 2))
            {
                system("cls");
                topDesign();
                printf("Do you want to reset?\n\n");
                printf("Take note: if you proceed to still do this, you will have to reconfigure the new game portion.\n");
                printf("That means having to re-enter the number of players, as well as inputting their names if they opt to.\n");
                printf("\nAre you ABSOLUTELY sure that you want to do this?\n");
                printf("[1] Yes, reset\n");
                printf("[2] No, go back\n");
                choice2 = numInput();
            }

            if(choice2 == 1)
            {
                // returns to newGame()'s while loop instead of recursing
                *confirmed = 0;
                done = 1;
            }
            // choice2 == 2: loop back to show lineup again
        }
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

