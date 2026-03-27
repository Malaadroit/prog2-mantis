/******************************************************************************
 *  Description     : The file contains the logic of the actual game simulation.
 *  Author/s        : Agamata, Loraine Beatriz C.
 *                    Lapuz, Dale Lucian M.
 *  Section         : S12A & S22A
 *  Last Modified   : March 27, 2026
 *  Acknowledgments : https://community.unix.com/t/how-to-log-time-in-c-c/238890/6
 ******************************************************************************/


/* ----- preprocessor directives ----- */
#include <stdio.h>
#include <string.h>
//#include "defs.h"
//#include "../Essentials/Additionals/interface.c"

/* ----- function prototypes ----- */
int colorToIndex(char color);
int  colorToInterface(char color);
void displayGameState(GameState Playing[], int numPlayers);
void shuffle(void* array, size_t nitems, size_t size, unsigned int seed);
void runGame(GameState Playing[], int numPlayers, GameSettings settings, Player PlayerList[]);
void performScore(GameState Playing[], int currentPlayer, Card deck[], int *deckSize);
int performSteal(GameState Playing[], int currentPlayer, int targetPlayerIdx, Card deck[], int *deckSize); 
void displayGameResults(GameState Playing[], int numPlayers, int winnerIdx, Player PlayerList[], int twoPlayerMode);
int checkWinCondition(GameState Playing[], int numPlayers, int* winnerIdx, int deckSize, int winningPts, int twoPlayerMode);
void addWin(int winnerIdx, GameState Playing[], int numPlayers, Player PlayerList[]);

//Extras
void logGameResult(GameState Playing[], int numPlayers, int winnerIdx);
void topDesign2();
/* ----- function implementations ----- */
/*
 * Converts a color character to its corresponding index in the tank array.
 * @param color The color character (R, O, Y, G, B, I, V)
 * @return The index of the color, or -1 if not found
 */
int colorToIndex(char color)
{
    int colorIdx = -1; //not found
    char colors[NUM_COLORS] = {'R', 'O', 'Y', 'G', 'B', 'I', 'V'};
    
    for(int i = 0; i < NUM_COLORS; i++)
    {
        if(colors[i] == color)
            colorIdx = i;
    }
    
    return colorIdx;
}

/*
 * Converts a color character to its corresponding interface color code.
 * @param color The color character (R, O, Y, G, B, I, V)
 * @return The interface color code, or I_COLOR_WHITE if not found
 */
int colorToInterface(char color)
{
    int colorCode;

    if(color == 'R')
        colorCode = I_COLOR_RED;
    else if(color == 'O')
        colorCode = I_COLOR_WHITE;
    else if(color == 'Y')
        colorCode = I_COLOR_YELLOW;
    else if(color == 'G')
        colorCode = I_COLOR_GREEN;
    else if(color == 'B')
        colorCode = I_COLOR_BLUE;
    else if(color == 'I')
        colorCode = I_COLOR_CYAN;
    else if(color == 'V')
        colorCode = I_COLOR_PURPLE;
    else
        colorCode = I_COLOR_WHITE;

    return colorCode;
}


/*
 * Displays the current game state for all players with colored tank counts.
 * @param Playing    The array of active GameState players
 * @param numPlayers The number of players in the game
 */
void displayGameState(GameState Playing[], int numPlayers)
{
    char colorChars[NUM_COLORS] = {'R', 'O', 'Y', 'G', 'B', 'I', 'V'};
    printf("Current Game State:\n");
    for(int i = 0; i < numPlayers; i++)
    {
        iSetColor(I_COLOR_CYAN);
        printf("Player %d: %s\n", i + 1, Playing[i].info->username);
        iSetColor(I_COLOR_WHITE);
        printf("  Score pile : %d pts (%d cards)\n", Playing[i].score, Playing[i].scoreCards);
        printf("  Tanks      : ");
        for (int c = 0; c < NUM_COLORS; c++)
        {
            //print each count in its own color for readability
            iSetColor(colorToInterface(colorChars[c]));
            printf("%c:%d ", colorChars[c], Playing[i].tank[c]);
        }
        iSetColor(I_COLOR_WHITE);
        printf("\n\n");
    }
}

/*
 * Loads the deck, shuffles it, deals starting hands, and runs the game loop.
 * @param Playing     The array of active GameState players
 * @param numPlayers  The number of players in the game
 * @param settings    The current game settings
 * @param PlayerList  The persistent player registry for updating stats
 * 
 * ====== BONUS FEATURES IMPLEMENTED IN THIS FUNCTION: ======
 * twoPlayerMode flag activates 2P bonus rules
 * Rematch loop – same players can replay without returning to the main menu (BONUS feature)
 * logGameResult() called after every game
 */
void runGame(GameState Playing[], int numPlayers, GameSettings settings, Player PlayerList[]) {
    int twoPlayerMode = (numPlayers == 2); 
    
    Card deck[STANDARD_DECK];
    int deckSize = 0; 
    int fileLoaded = 0;
    topDesign2();
    //file reading of mantis.txt
    FILE *file = fopen("mantis.txt", "r");
    if (file != NULL) {
        while (deckSize < STANDARD_DECK && fscanf(file, " %c | %3s %d", &deck[deckSize].front, deck[deckSize].back, &deck[deckSize].points) != EOF) {
            deckSize++;
        }
        fclose(file);
        fileLoaded = 1;
    } else {
        iSetColor(I_COLOR_RED);
        printf("Error: mantis.txt not found!\n");
        iSetColor(I_COLOR_WHITE);
    }

    // ============ FOR CHECKING IF SEED PRODUCES CORRECT SHUFFLE (can be removed later) ============
    // printf("DEBUG: loaded %d cards, first=%c|%s, last=%c|%s\n",
    // deckSize,
    // deck[0].front, deck[0].back,
    // deck[deckSize-1].front, deck[deckSize-1].back);
    // if seed = 1; first R | ROI, last = V | OGV 
    // ==============================================================================================

    if(fileLoaded == 1)
    {
        iSetColor(I_COLOR_GREEN);
        printf("The deck was loaded successfully.\n");
        iSetColor(I_COLOR_WHITE);

        // keep a pristine copy of the full loaded deck so every rematch can restore it
        Card originalDeck[STANDARD_DECK];
        int  originalDeckSize = deckSize;
        for(int i = 0; i < deckSize; i++)
            originalDeck[i] = deck[i];
        
        //BONUS: REMATCH LOOP - after game ends, players can choose to play again with same settings and players
        int playAgain = 1;
        int rematchCount = 0; // offset seed so each rematch shuffles differently

        while(playAgain == 1)
        {//reset player state for fresh game
            deckSize = originalDeckSize;
            for(int i = 0; i < deckSize; i++)
                deck[i] = originalDeck[i];

            for(int i = 0; i < numPlayers; i++){
                Playing[i].score = 0;        
                Playing[i].scoreCards = 0;   
                for(int j = 0; j < NUM_COLORS; j++)
                {
                    Playing[i].tank[j] = 0;
                    Playing[i].tankPoints[j] = 0; 
                }
            }
         //reshuffle each match so rematched feel different (di mahulaan or dejavu cards ganon)
            shuffle(deck, deckSize, sizeof(Card), settings.shufflingSeed  + rematchCount);
            rematchCount++;

            //deal 4 card face up
            int drawIdx = 0;
            for(int i = 0; i < numPlayers; i++)
            {
                for(int j = 0; j < 4 && drawIdx < deckSize; j++)
                {
                int cIdx = colorToIndex(deck[drawIdx].front);
                    if (cIdx != -1)
                    {
                        Playing[i].tank[cIdx]++;
                        Playing[i].tankPoints[cIdx] += deck[drawIdx].points;
                    }
                    drawIdx++;
                }
            }
            //makes deck[0] on top
            int remaining = deckSize - drawIdx;
            for(int i = 0; i <remaining; i++){
                deck[i] = deck[drawIdx + i];   
            }
            deckSize = remaining; //deckSize = remaining cards that are drawable

            if (twoPlayerMode)
                {
                    iSetColor(I_COLOR_PURPLE);
                    printf("*** 2-Player Bonus Mode active! ***\n");
                    printf("Win by getting 15 cards into your Score Pile.\n");
                    printf("A successful steal grants an extra turn!\n\n");
                    iSetColor(I_COLOR_WHITE);
                }
            iSetColor(I_COLOR_YELLOW);
                printf("The game has started!\n");
                iSetColor(I_COLOR_WHITE);

                int gameOver = 0;
                int turn = 0;
                int currentPlayer;
                int winnerIdx = -1;
            // Deal 4 cards face up to each player's tank

            //main game loop - continues until win condition met or deck runs out
            while(gameOver == 0 && deckSize > 0)
            {
                currentPlayer = turn % numPlayers;
                displayGameState(Playing, numPlayers);

                //show back of top card - deck[0] is top card since we shifted the deck after dealing
                iSetColor(I_COLOR_WHITE);
                printf("Seed: %d\n", settings.shufflingSeed); //for testing purposes, can be removed later
                printf("Top Deck: ");
                for(int b = 0; b < 3; b++)
                {
                    iSetColor(colorToInterface(deck[0].back[b]));
                    printf("%c", deck[0].back[b]);
                }
                iSetColor(I_COLOR_WHITE);
                printf("  (%d cards remaining in the deck.)\n", deckSize);
                
                iSetColor(I_COLOR_CYAN);
                printf("\nPlayer %d (%s), what would you like to do?\n", currentPlayer + 1, Playing[currentPlayer].info->username);
                
                iSetColor(I_COLOR_WHITE);
                printf("[1] Try to Score\n");
                printf("[2] Try to Steal\n");

                int choice = -1;
                while(!(choice == 1 || choice == 2))
                {
                    choice = numInput();
                    if(choice != 1 && choice != 2){
                        iSetColor(I_COLOR_RED);
                        printf("Invalid choice. Please enter 1 or 2.\n");
                        iSetColor(I_COLOR_WHITE);
                    }
                }

                if(choice == 1){
                    performScore(Playing, currentPlayer, deck, &deckSize);
                    turn++; //score always ends turn
                }
                    
                else if(choice == 2)
                {
                    printf("\nWho would you like to steal from?\n");
                    for(int i = 0; i < numPlayers; i++)
                    {
                        if(i != currentPlayer)
                            printf("[%d] Player %d (%s)\n", i + 1, i + 1, Playing[i].info->username);
                    }

                    int targetChoice = -1;
                    int targetPlayerIdx = -1;

                    while(targetPlayerIdx == -1)
                    {
                        targetChoice = numInput();

                        if(targetChoice >= 1 && targetChoice <= numPlayers && targetChoice != currentPlayer + 1)
                            targetPlayerIdx = targetChoice - 1;
                        else{
                            iSetColor(I_COLOR_RED);
                            printf("Invalid choice. Please select another player.\n");
                            iSetColor(I_COLOR_WHITE);
                        }
                            
                    }
                    //BONUS: In 2P bonus mode, a successful steal grants an extra turn immediately after resolving the steal
                    int stealSuccess = performSteal(Playing, currentPlayer, targetPlayerIdx, deck, &deckSize);

                    if(twoPlayerMode == 1 && stealSuccess == 1)
                    {
                        iSetColor(I_COLOR_PURPLE);
                        printf("Successful steal! Player %d (%s) gets an extra turn!\n\n", currentPlayer + 1, Playing[currentPlayer].info->username);
                        iSetColor(I_COLOR_WHITE);
                    }
                    else
                    {
                        turn++; //only end turn if no extra turn granted
                    }
                }

                if(checkWinCondition(Playing, numPlayers, &winnerIdx, deckSize, settings.winningPts, twoPlayerMode) == 1)
                    gameOver = 1;
                
            } //end of main game loop

            addWin(winnerIdx, Playing, numPlayers, PlayerList);
            //BONUS: append result to history.txt
            logGameResult(Playing, numPlayers, winnerIdx);
            displayGameResults(Playing, numPlayers, winnerIdx, PlayerList, twoPlayerMode);
            //BONUS: rematch prompt 
            int rematchChoice = -1;
            iSetColor(I_COLOR_YELLOW);
            printf("\nWould you like a rematch with the same players?\n");
            iSetColor(I_COLOR_WHITE);
            printf("[1] Yes - play again\n");
            printf("[2] No  - return to main menu\n");
            while (!(rematchChoice == 1 || rematchChoice == 2))
                    rematchChoice = numInput();
            if (rematchChoice == 2)
                    playAgain = 0;
        } //end of rematch loop
    } //end of if file loaded
}

/*
 * Resolves the Try to Score action for the current player.
 * @param Playing       The array of active GameState players
 * @param currentPlayer Index of the player taking the turn
 * @param deck          The card deck array
 * @param deckIdx       Pointer to the current draw index
 * @param deckSize      Total number of cards in the deck
 */
void performScore(GameState Playing[], int currentPlayer, Card deck[], int *deckSize){
    if(*deckSize > 0){
        Card drawnCard = deck[0];
        
        //make deck[0] top by shifting
        for (int i = 0; i < *deckSize - 1; i++)
            deck[i] = deck[i + 1];
        (*deckSize)--;
        
        int colorIdx = colorToIndex(drawnCard.front);
        
        printf("\nResolving turn for Player %d...\n", currentPlayer + 1);
        printf("- Drawn card color reveal: ");
        iSetColor(colorToInterface(drawnCard.front));
        printf("%c", drawnCard.front);
        iSetColor(I_COLOR_WHITE);
        printf(" (%d pt/s)!\n", drawnCard.points);

        if(Playing[currentPlayer].tank[colorIdx] > 0)
        {
            ///points already in tank
            int tankWorth = Playing[currentPlayer].tankPoints[colorIdx];
            
            //full amount going to score pile
            int totalPoints = tankWorth + drawnCard.points;   
            
            printf("- Player %d has (%d) ", currentPlayer + 1, Playing[currentPlayer].tank[colorIdx]);
            iSetColor(colorToInterface(drawnCard.front));
            printf("%c", drawnCard.front);
            iSetColor(I_COLOR_WHITE);
            printf(" card/s worth a total of (%d) pts!\n", tankWorth);

            iSetColor(I_COLOR_GREEN);
            printf("- +%d points to Player %d's Score pile!\n\n", totalPoints, currentPlayer + 1);
            iSetColor(I_COLOR_WHITE);

            Playing[currentPlayer].score += totalPoints;
            Playing[currentPlayer].scoreCards += Playing[currentPlayer].tank[colorIdx] + 1;
            Playing[currentPlayer].tank[colorIdx] = 0;
            Playing[currentPlayer].tankPoints[colorIdx] = 0;
        }
        else
        {
            //no matching color - add to tank
            printf("- Player %d has no ", currentPlayer + 1);
            iSetColor(colorToInterface(drawnCard.front));
            printf("%c", drawnCard.front);
            iSetColor(I_COLOR_WHITE);
            printf(" cards...\n");
            printf("- Adding drawn card to Player %d's Tank\n\n", currentPlayer + 1);
            Playing[currentPlayer].tank[colorIdx]++;
            Playing[currentPlayer].tankPoints[colorIdx] += drawnCard.points;
        }
    }
    
}

/*
 * Resolves the Try to Steal action for the current player.
 * @param Playing          The array of active GameState players
 * @param currentPlayer    Index of the player taking the turn
 * @param targetPlayerIdx  Index of the player being stolen from
 * @param deck             The card deck array
 * @param deckIdx          Pointer to the current draw index
 * @param deckSize         Total number of cards in the deck
 * @return 1 if the steal was successful (stole at least 1 card), 0 if failed steal (stole nothing)
 */
int performSteal(GameState Playing[], int currentPlayer, int targetPlayerIdx, Card deck[], int *deckSize)
{
    int stealSuccess = 0;
    if(*deckSize > 0)
    {
        Card drawnCard = deck[0];
        //make deck[0] top by shifting
        for (int i = 0; i < *deckSize - 1; i++)
            deck[i] = deck[i + 1];
        (*deckSize)--;

        int colorIdx = colorToIndex(drawnCard.front);

        iSetColor(I_COLOR_WHITE);
        printf("\nResolving turn for Player %d...\n", currentPlayer + 1);
        printf("- Drawn card color reveal: ");
        iSetColor(colorToInterface(drawnCard.front));
        printf("%c", drawnCard.front);
        iSetColor(I_COLOR_WHITE);
        printf(" (%d pt/s)!\n", drawnCard.points);

        if(Playing[targetPlayerIdx].tank[colorIdx] > 0)
        {
            int stolenCount  = Playing[targetPlayerIdx].tank[colorIdx];
            int stolenPoints = Playing[targetPlayerIdx].tankPoints[colorIdx];

            printf("- Player %d has (%d) ", targetPlayerIdx + 1, stolenCount);
            iSetColor(colorToInterface(drawnCard.front));
            printf("%c", drawnCard.front);
            iSetColor(I_COLOR_WHITE);
            printf(" card/s!\n");

            iSetColor(I_COLOR_CYAN);
            printf("- +%d (%c) cards to Player %d's Tank!\n\n", stolenCount + 1, drawnCard.front, currentPlayer + 1);
            iSetColor(I_COLOR_WHITE);

            Playing[currentPlayer].tank[colorIdx] += stolenCount + 1;
            Playing[currentPlayer].tankPoints[colorIdx] += stolenPoints + drawnCard.points;
            Playing[targetPlayerIdx].tank[colorIdx] = 0;
            Playing[targetPlayerIdx].tankPoints[colorIdx] = 0;

            stealSuccess = 1; // signal for 2P bonus mode extra turn
        }
        else
        {
            printf("- Player %d has no ", targetPlayerIdx + 1);
            iSetColor(colorToInterface(drawnCard.front));
            printf("%c", drawnCard.front);
            iSetColor(I_COLOR_WHITE);
            printf(" cards...\n");
            printf("- Adding drawn card to Player %d's Tank\n\n", targetPlayerIdx + 1);

            Playing[targetPlayerIdx].tank[colorIdx]++;
            Playing[targetPlayerIdx].tankPoints[colorIdx] += drawnCard.points;

            stealSuccess = 0; // failed steal, no extra turn
        }
    }
    return stealSuccess;
}

/*
 * Displays final game results and updates player stats in players.txt.
 * getchar() waits for user before returning to main menu.
 * @param Playing    The array of active GameState players
 * @param numPlayers The number of players in the game
 * @param winnerIdx  Index of the winner, or -1 if a tie
 * @param PlayerList The persistent player registry
 */
void displayGameResults(GameState Playing[], int numPlayers, int winnerIdx, Player PlayerList[], int twoPlayerMode)
{
    int i;
    iSetColor(I_COLOR_YELLOW);
    printf("\n===== GAME OVER =====\n");

    if (twoPlayerMode == 1)
    {
        iSetColor(I_COLOR_PURPLE);
        printf("[2-Player Bonus Mode]\n");
        iSetColor(I_COLOR_WHITE);
    }

    if(winnerIdx == -1){
        iSetColor(I_COLOR_CYAN);
        printf("It's a tie!\n");
    }
    else{
        iSetColor(I_COLOR_GREEN);
        printf("Winner: Player %d (%s) with %d points!\n", winnerIdx + 1, Playing[winnerIdx].info->username, Playing[winnerIdx].score);
    }
    
    iSetColor(I_COLOR_WHITE);
    printf("\nFinal Scores:\n");
    for(i = 0; i < numPlayers; i++)
    {
        if(i == winnerIdx)
            iSetColor(I_COLOR_GREEN);
        else
            iSetColor(I_COLOR_WHITE);

        printf("  Player %d (%s): %d pts\n", i + 1, Playing[i].info->username, Playing[i].score);
    }
    iSetColor(I_COLOR_YELLOW);
    printf("=====================\n\n");
    iSetColor(I_COLOR_WHITE);
    printf("Returning to main menu...\n");
    getchar();
}

/*
 * Checks if the win condition has been met.
 * @param Playing    The array of active GameState players
 * @param numPlayers The number of players in the game
 * @param winnerIdx  Output — set to winner index, or -1 on full tie
 * @param deckIdx    Current draw index
 * @param deckSize   Total deck size
 * @param winningPts Points threshold to win
 * @return 1 if game is over, 0 otherwise
 */
int checkWinCondition(GameState Playing[], int numPlayers, int* winnerIdx, int deckSize, int winningPts, int twoPlayerMode)
{
    int found = 0;

    if (twoPlayerMode == 1)
    {
        /* BONUS 2-player: win by reaching 15 score*/
        int bestScore = -1;
        int bestIdx = -1;
        int ties = 0;

        for (int i = 0; i < numPlayers; i++)
        {
            if (Playing[i].score >= 15) //NOTE HARDCODED 15 SO WHEN SETTINGS WIN IS CHANGED, 15 IT WILL NOT CHANGE
            {
                if (Playing[i].score > bestScore)
                {
                    bestScore = Playing[i].score;
                    bestIdx = i;
                    ties = 1;
                }
                else if (Playing[i].score == bestScore)
                {
                    ties++;
                }
                found = 1;
            }
        }
        if (found == 1)
        {
            if (ties == 1)
                *winnerIdx = bestIdx;
            else
                *winnerIdx = -1;
        }
    }
    else{ //standard mode win condition: first to reach winningPts in score pile, tiebreaker by most score cards, then by most total tank cards
        int bestScore = -1;
        int bestIdx = -1;
        int ties = 0;

        for(int i = 0; i < numPlayers; i++){
            if(Playing[i].score >= winningPts){
                if (Playing[i].score > bestScore)
                {
                    bestScore = Playing[i].score;
                    bestIdx = i;
                    ties = 1;
                }
                else if (Playing[i].score == bestScore)
                {
                    ties++;
                }
                found = 1;
            }
        }
        
        if (found == 1){
            if (ties == 1) 
                *winnerIdx = bestIdx;
            else 
                *winnerIdx = -1;
        }
    }
    // IF DECK IS EMPTY
    if (deckSize <= 0 && found == 0)
    {
      int maxCards = -1;
        for (int i = 0; i < numPlayers; i++)
        {
            if (Playing[i].scoreCards > maxCards)
                maxCards = Playing[i].scoreCards;
        }

        int tiedPlayers[MAX_PLAYERS_IN_GAME];
        int tieCount = 0;
        for (int i = 0; i < numPlayers; i++)
        {
            if (Playing[i].scoreCards == maxCards)
                tiedPlayers[tieCount++] = i;
        }

        if (tieCount == 1)
        {
            *winnerIdx = tiedPlayers[0];
        }
        else
        {
            //Secondary tiebreak: most total cards across all tanks
            int maxTank = -1;
            int maxTankIdx = tiedPlayers[0];
            int fullTie = 0;

            for (int i = 0; i < tieCount; i++)
            {
                int tot = 0;
                for (int j = 0; j < NUM_COLORS; j++)
                    tot += Playing[tiedPlayers[i]].tank[j];

                if (tot > maxTank)
                {
                    maxTank = tot;
                    maxTankIdx = tiedPlayers[i];
                    fullTie = 0;
                }
                else if (tot == maxTank)
                {
                    fullTie = 1;
                }
            }

            if (fullTie == 1)
                *winnerIdx = -1;
            else
                *winnerIdx = maxTankIdx;
        }
        found = 1;
    }
    return found;
}

/*
* This function appends the result of a completed game to history.txt, including timestamp, winner, and final scores.
* @param Playing    The array of active GameState players
* @param numPlayers The number of players in the game
* @param winnerIdx  Index of the winner, or -1 if a tie
* Format:
* [YYYY-MM-DD HH:MM] Winner: <name> | Players: A(Xpts), B(Ypts)
*/
void logGameResult(GameState Playing[], int numPlayers, int winnerIdx)
{
    FILE *fp = fopen("history.txt", "a");

    if (fp == NULL)
    {
        iSetColor(I_COLOR_RED);
        printf("Warning: could not write to history.txt\n");
        iSetColor(I_COLOR_WHITE);
    }
    else
    {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        fprintf(fp, "[%04d-%02d-%02d %02d:%02d] ", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);

        if (winnerIdx == -1)
            fprintf(fp, "Result: TIE | ");
        else
            fprintf(fp, "Winner: %s | ", Playing[winnerIdx].info->username);

        fprintf(fp, "Players: ");
        for (int i = 0; i < numPlayers; i++)
        {
            fprintf(fp, "%s(%dpts)", Playing[i].info->username, Playing[i].score);
            if (i < numPlayers - 1)
                fprintf(fp, ", ");
        }
        fprintf(fp, "\n");

        fclose(fp);
    }
}

/*
* Displays the MANTIS header for the game interface.
*/
void topDesign2()
{
    iSetColor(I_COLOR_CYAN);
    printf("*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n");
    iSetColor(I_COLOR_YELLOW);
    printf("-----------MANTIS------------\n");
    iSetColor(I_COLOR_CYAN);
    printf("*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n");
    iSetColor(I_COLOR_WHITE);
}

/*
 * Updates wins and high score for the winner(s) then saves to players.txt.
 * Handles tie case (winnerIdx == -1) by updating all players.
 * @param winnerIdx  Index of the winner, or -1 if a tie
 * @param Playing    The array of active GameState players
 * @param numPlayers The number of players in the game
 * @param PlayerList The persistent player registry
 */
void addWin(int winnerIdx, GameState Playing[], int numPlayers, Player PlayerList[])
{
    int i;

    if(winnerIdx == -1){
        for(i = 0; i < numPlayers; i++){
            Playing[i].info->stats.wins += 1;
            if(Playing[i].score > Playing[i].info->stats.highScore)
            {
                Playing[i].info->stats.highScore = Playing[i].score;
            }
        }
    }
    else
    {
        Playing[winnerIdx].info->stats.wins += 1;
        if(Playing[winnerIdx].score > Playing[winnerIdx].info->stats.highScore)
        {
            Playing[winnerIdx].info->stats.highScore = Playing[winnerIdx].score;
        } 
    }

    updatePlayerList(PlayerList, MAX_PLAYERS);
}