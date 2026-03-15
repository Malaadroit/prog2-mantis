/* ----- preprocessor directives ----- */
#include <stdio.h>
#include <string.h>
#include "defs.h"

/* ----- function prototypes ----- */
int colorToIndex(char color);
void displayGameState(GameState Playing[], int numPlayers);
void shuffle(void* array, size_t nitems, size_t size, unsigned int seed);
void runGame(GameState Playing[], int numPlayers, GameSettings settings);
void performScore(GameState Playing[], int currentPlayer, Card deck[], int* drawIdx, int deckSize);
void performSteal(GameState Playing[], int currentPlayer, int targetPlayerIdx, Card deck[], int *deckIdx, int deckSize); 
void displayGameResults(GameState Playing[], int numPlayers, int winnerIdx);
int checkWinCondition(GameState Playing[], int numPlayers, int* winnerIdx, int deckIdx, int deckSize, int winningPts);
/* ----- function implementations ----- */
//converts color char to index for tank array
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

void displayGameState(GameState Playing[], int numPlayers)
{
    printf("Current Game State:\n");
    for(int i = 0; i < numPlayers; i++)
    {
        printf("Player %d: %s\n", i + 1, Playing[i].info->username);
        printf("Score: %d\n", Playing[i].score);
        printf("Tanks: R:%d O:%d Y:%d G:%d B:%d I:%d V:%d\n", 
            Playing[i].tank[0], Playing[i].tank[1], Playing[i].tank[2], 
            Playing[i].tank[3], Playing[i].tank[4], Playing[i].tank[5], 
            Playing[i].tank[6]);
        printf("\n");
    }
}
void runGame(GameState Playing[], int numPlayers, GameSettings settings) {
    Card deck[84];
    int deckSize = 0; 
    int fileLoaded = 0;

    //file reading of mantis.txt
    FILE *file = fopen("mantis.txt", "r");
    if (file != NULL) {
        while (deckSize < STANDARD_DECK && fscanf(file, " %c | %3s %d", &deck[deckSize].front, deck[deckSize].back, &deck[deckSize].points) != EOF) {
            deckSize++;
        }
        fclose(file);
        fileLoaded = 1;
    } else {
        printf("Error: mantis.txt not found!\n");
    }

    if(fileLoaded == 1)
    {
        printf("The deck was loaded successfully.\n");
        shuffle(deck, deckSize, sizeof(Card), settings.shufflingSeed);
    }

    if(fileLoaded == 1)
    {
        int drawIdx = 0;
        for(int i = 0; i < numPlayers; i++)
        {
            Playing[i].score = 0;        
            Playing[i].scoreCards = 0;   
            for(int j = 0; j < NUM_COLORS; j++)
            {
                Playing[i].tank[j] = 0;
                Playing[i].tankPoints[j] = 0; 
            }
        }

        // Deal 4 cards face up to each player's tank
        for(int i = 0; i < numPlayers; i++)
        {
            for(int j = 0; j < 4 && drawIdx < deckSize; j++)
            {
                int cIdx = colorToIndex(deck[drawIdx].front);
                if(cIdx != -1)
                {
                    Playing[i].tank[cIdx]++;
                    Playing[i].tankPoints[cIdx] += deck[drawIdx].points;
                }
                drawIdx++;
            }
        }

        displayGameState(Playing, numPlayers);
        printf("The game has started!\n");

        int gameOver = 0;
        int turn = 0;
        int currentPlayer;
        int winnerIdx = -1;

        while(gameOver == 0 && drawIdx < deckSize)
        {
            currentPlayer = turn % numPlayers;
            displayGameState(Playing, numPlayers);

            printf("Top Deck: ");
            for(int i = 0; i < 3 && (drawIdx + i) < deckSize; i++)
            {
                printf("%c", deck[drawIdx + i].back[i]);
            }
            printf("  (%d cards remaining in the deck.)\n", deckSize - drawIdx);
            printf("\nPlayer %d (%s), what would you like to do?\n",
                   currentPlayer + 1,
                   Playing[currentPlayer].info->username);

            printf("[1] Try to Score\n");
            printf("[2] Try to Steal\n");

            int choice = -1;
            while(!(choice == 1 || choice == 2))
            {
                choice = numInput();
                if(choice != 1 && choice != 2)
                    printf("Invalid choice. Please enter 1 or 2.\n");
            }

            if(choice == 1)
                performScore(Playing, currentPlayer, deck, &drawIdx, deckSize);
            
            else if(choice == 2)
            {
                printf("\nWho would you like to steal from?\n");
                for(int i = 0; i < numPlayers; i++)
                {
                    if(i != currentPlayer)
                        printf("[%d] Player %d (%s)\n", i + 1, i + 1, Playing[i].info->username);
                }

                int targetChoice    = -1;
                int targetPlayerIdx = -1;

                while(targetPlayerIdx == -1)
                {
                    targetChoice = numInput();

                    if(targetChoice >= 1 && targetChoice <= numPlayers && targetChoice != currentPlayer + 1)
                        targetPlayerIdx = targetChoice - 1;
                    else
                        printf("Invalid choice. Please select another player.\n");
                }
                performSteal(Playing, currentPlayer, targetPlayerIdx, deck, &drawIdx, deckSize);
            }

            if(checkWinCondition(Playing, numPlayers, &winnerIdx, drawIdx, deckSize, settings.winningPts) == 1)
                gameOver = 1;
            
            else
                turn++;
            
        }

        displayGameResults(Playing, numPlayers, winnerIdx);
    }
}

void performScore(GameState Playing[], int currentPlayer, Card deck[], int *deckIdx, int deckSize){
    if(*deckIdx >= deckSize)
        return; // FIX DO NOT SHORTCUT; FOR TESTING ONLY
    
    Card drawnCard = deck[*deckIdx];
    (*deckIdx)++;
    
    int colorIdx = colorToIndex(drawnCard.front);
    
    printf("\nResolving turn for Player %d...\n", currentPlayer + 1);
    printf("- Drawn card color reveal: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);
    
    if(Playing[currentPlayer].tank[colorIdx] > 0)
    {
        //player has matching color - move all to score pile
        int totalPoints = Playing[currentPlayer].tank[colorIdx] * drawnCard.points + drawnCard.points;
        
        printf("- Player %d has (%d) %c card/s worth (%d) pts!\n", 
               currentPlayer + 1, 
               Playing[currentPlayer].tank[colorIdx], 
               drawnCard.front, totalPoints);
        printf("- +%d points to Player %d's Score pile!\n\n", totalPoints, currentPlayer + 1);
        
        Playing[currentPlayer].score += totalPoints;
        Playing[currentPlayer].scoreCards += Playing[currentPlayer].tank[colorIdx] + 1;
        Playing[currentPlayer].tank[colorIdx] = 0;
        Playing[currentPlayer].tankPoints[colorIdx] = 0;
    }
    else
    {
        //no matching color - add to tank
        printf("- Player %d has no %c cards...\n", currentPlayer + 1, drawnCard.front);
        printf("- Adding drawn card to Player %d's Tank\n\n", currentPlayer + 1);
        
        Playing[currentPlayer].tank[colorIdx]++;
    }
}

void performSteal(GameState Playing[], int currentPlayer, int targetPlayerIdx,
                  Card deck[], int *deckIdx, int deckSize)
{
    if(*deckIdx >= deckSize)
        return; // FIX DO NOT SHORTCUT; FOR TESTING ONLY

    Card drawnCard = deck[*deckIdx];
    (*deckIdx)++;

    int colorIdx = colorToIndex(drawnCard.front);

    printf("\nResolving turn for Player %d...\n", currentPlayer + 1);
    printf("- Drawn card color reveal: %c (%d pt/s)!\n", drawnCard.front, drawnCard.points);

    if(Playing[targetPlayerIdx].tank[colorIdx] > 0)
    {
        int stolenCount  = Playing[targetPlayerIdx].tank[colorIdx];
        int stolenPoints = Playing[targetPlayerIdx].tankPoints[colorIdx];

        printf("- Player %d has (%d) %c card/s!\n", targetPlayerIdx + 1, stolenCount, drawnCard.front);
        printf("- +%d (%c) cards to Player %d's Tank!\n\n", stolenCount + 1, drawnCard.front, currentPlayer + 1);

        Playing[currentPlayer].tank[colorIdx] += stolenCount + 1;
        Playing[currentPlayer].tankPoints[colorIdx] += stolenPoints + drawnCard.points;
        Playing[targetPlayerIdx].tank[colorIdx] = 0;
        Playing[targetPlayerIdx].tankPoints[colorIdx] = 0;
    }
    else
    {
        printf("- Player %d has no %c cards...\n", targetPlayerIdx + 1, drawnCard.front);
        printf("- Adding drawn card to Player %d's Tank\n\n", targetPlayerIdx + 1);

        Playing[targetPlayerIdx].tank[colorIdx]++;
        Playing[targetPlayerIdx].tankPoints[colorIdx] += drawnCard.points;
    }
}

void displayGameResults(GameState Playing[], int numPlayers, int winnerIdx)
{
    int i;
    printf("\n===== GAME OVER =====\n");

    if(winnerIdx == -1)
        printf("It's a tie!\n");
    else
        printf("Winner: Player %d (%s) with %d points!\n",
               winnerIdx + 1,
               Playing[winnerIdx].info->username,
               Playing[winnerIdx].score);

    printf("\nFinal Scores:\n");
    for(i = 0; i < numPlayers; i++)
    {
        printf("  Player %d (%s): %d pts\n",
               i + 1,
               Playing[i].info->username,
               Playing[i].score);
    }
    printf("=====================\n\n");
    printf("Returning to main menu...\n");
    getchar();
}

int checkWinCondition(GameState Playing[], int numPlayers, int* winnerIdx, int deckIdx, int deckSize, int winningPts)
{
    int found = 0;
    //check if any player has reached winning points
    for(int i = 0; i < numPlayers; i++)
    {
        if(Playing[i].score >= winningPts)
        {
            *winnerIdx = i;
            found = 1;
        }
    
    }
    
    //check if deck is empty
    if(deckIdx >= deckSize){
        // Find player with most score pile cards
        int maxScoreCards = 0;
        int maxScoreIdx = 0;
        
        for(int i = 0; i < numPlayers; i++){
            if(Playing[i].score > maxScoreCards){
                maxScoreCards = Playing[i].score;
                maxScoreIdx = i;
            }
        }
        //if tied on score check tank cards
        int tiedPlayers[6];
        int tieCount = 0;

        for(int i = 0; i < numPlayers; i++){
            if(Playing[i].scoreCards == maxScoreCards){
                tiedPlayers[tieCount] = i;
                tieCount++;
            }
        }

        if(tieCount == 1){
            *winnerIdx = tiedPlayers[0];
            found = 1;
        }
        else{
            // In case of tie, player with most cards in tanks wins
            int maxTankCards = 0;
            int maxTankIdx = tiedPlayers[0];

            for(int i = 0; i < tieCount; i++)
            {
                int tankCards = 0;
                for(int j = 0; j < NUM_COLORS; j++)
                {
                    tankCards += Playing[tiedPlayers[i]].tank[j];
                }
                
                if(tankCards > maxTankCards)
                {
                    maxTankCards = tankCards;
                    maxTankIdx = tiedPlayers[i];
                }
            }
            
            *winnerIdx = maxTankIdx;
            found = 1;
        }
    }
return found;
}