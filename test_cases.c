#include <stdio.h>
#include "Essentials/Helpers/helpers.c"
#include "Code-Proper/menu.c"
#include <math.h>
#define PLAYING_TESTCASE 6
#define TWO_PLAYER 2
int main()
{
    String36 input_TESTCase;
    String36 PlayerListNamesTC[5] = {"_" ,"DaleLapuz", "GreenDay", "Blink182", "Maladroit64"};
    GameState TestCase[PLAYING_TESTCASE];
    GameState TwoPlayerTC[TWO_PLAYER];
    Player TestCasePL[5];



    strcpy(TestCasePL[0].username, "MandatorySubmissionofRequirements67");
    strcpy(TestCasePL[1].username, "OneTwentyOneGuns");
    strcpy(TestCasePL[2].username,  "S12S22A");
    strcpy(TestCasePL[3].username, "DanDanDaniel");
    strcpy(TestCasePL[4].username,  "Daleroblox2133");
    

    int process, processCardNo, AmountCards = 0;
    int winnerIndex_TestCase = -1, decksize_TestCase = 0, winningpts_TestCase = 20, TwoPlayerMode = 0, n; 
    //for deckindex_TestCase, in test input this is written as Reduced Deck Size, in this case 0

    int color1 = colorToIndex('R');
    int color2 = colorToIndex('Z');
    int color3 = colorToIndex('r');
    // printf("%d\n", color1);
    // printf("%d\n", color2);
    // printf("%d\n", color3); 
    
    for(process = 0; process < PLAYING_TESTCASE; process++)
    {
        TestCase[process].info = &TestCasePL[process];
    }
    // for(process = 0; process < PLAYING_TESTCASE; process++)
    // {
    //     for(processCardNo = 0; processCardNo < NUM_COLORS; processCardNo++)
    //     {
    //          n = processCardNo + 1;
    //         if(process == 0)
    //         {
                
    //             TestCase[process].tank[processCardNo] = 2*n - 1;
    //             AmountCards += TestCase[process].tank[processCardNo];
    //         }
    //         else if(process == 1)
    //         {
                
    //             TestCase[process].tank[processCardNo] = 2*n;
    //             AmountCards += TestCase[process].tank[processCardNo];
    //         }
    //         else if(process == 2)
    //         {
    //             TestCase[process].tank[processCardNo] = 2;
    //             AmountCards += TestCase[process].tank[processCardNo];
    //         }
    //         else if(process == 3)
    //         {
                
    //             TestCase[process].tank[processCardNo] = n;
    //             AmountCards += TestCase[process].tank[processCardNo];
    //         }
    //         else if(process == 4)
    //         {
    //             TestCase[process].tank[processCardNo] = pow(2, n);
    //             AmountCards += TestCase[process].tank[processCardNo];
    //         }
    //         else if(process == 5)
    //         {
    //             TestCase[process].tank[processCardNo] = 1;
    //             AmountCards += TestCase[process].tank[processCardNo]; 
    //         }
    //     }
    //     printf("Player %d has %d cards\n", process + 1, AmountCards);
    //     AmountCards = 0;
    //     processCardNo = 0;
    // }

    for(process = 0; process < PLAYING_TESTCASE; process++)
    {
        for(processCardNo = 0; processCardNo < NUM_COLORS; processCardNo++)
        {
            TestCase[process].tank[processCardNo] = 1;
            AmountCards += TestCase[process].tank[processCardNo];
        }
        printf("Player %d has %d cards\n", process + 1, AmountCards);
        AmountCards = 0;
        processCardNo = 0;
    }
    TestCase[0].score = 15; // in the Test input, this is written as Player n + 1's score (where n is the index number, in this case 0)
    TestCase[1].score = 15;
    TestCase[2].score = 15;
    TestCase[3].score = 15;
    TestCase[4].score = 15;
    TestCase[5].score = 15;

    // TestCase[0].scoreCards = 1;
    // TestCase[1].scoreCards = 3;
    // TestCase[2].scoreCards = 5;
    // TestCase[3].scoreCards = 7;
    // TestCase[4].scoreCards = 9;
    // TestCase[5].scoreCards = 11;

    TwoPlayerTC[0].score = 10;
    TwoPlayerTC[1].score = 16;

    printf("\n");
    for(process = 0; process < PLAYING_TESTCASE; process++)
    {
        printf("Player %d has %d points\n", process + 1, TestCase[process].score);
    }

    // int num = numInput();
    // printf("Inputted Number: %d", num);

    //Check win condition if two player mode is disabled
    printf("found? %d\n", checkWinCondition(TestCase, PLAYING_TESTCASE, &winnerIndex_TestCase, decksize_TestCase, winningpts_TestCase, TwoPlayerMode));
    printf("Winner index: %d\n", winnerIndex_TestCase);
    printf("The winner is: player %d\n\n", winnerIndex_TestCase + 1);

    //Check win condition if two player mode is enabled
    printf("found? 2 player mode: %d\n", checkWinCondition(TwoPlayerTC, TWO_PLAYER, &winnerIndex_TestCase, decksize_TestCase, 15, TwoPlayerMode));
    printf("winner index: %d\n", winnerIndex_TestCase);
    printf("winner of 2 player mode: playr %d\n", winnerIndex_TestCase + 1);


    printf("The player is at %d (findPlayer func) \n\n ", findPlayer(TestCasePL, 5, "Maladroit64"));
    printf("Found? Checksamename %d\n\n", checkSameName(TestCase, "Maladroit64", 5));

    addtoPL(PlayerListNamesTC, 5, "Daletheguy1");
    for(process = 0; process < 5; process++)
    {
        printf("%s\n", PlayerListNamesTC[process]);
    }

    printf("Enter input: ");
    strInput(input_TESTCase, MAX_PLAYER_CHAR);
    printf("%s", input_TESTCase);
}


/**
* This is to certify that this project is my/our own work, based on my/our personal
* efforts in studying and applying the concepts learned. I/We have constructed the
* functions and their respective algorithms and corresponding code by myself/ourselves.
* The program was run, tested, and debugged by my/our own efforts. I/We further certify
* that I/we have not copied in part or whole or otherwise plagiarized the work of other
* students and/or persons, nor did I employ the use of AI in any part of the deliverable.
*
* <Agamata, Loraine Beatriz C.> (12507121)
* <Lapuz, Dale Lucian M.> (12505919)
*/

    