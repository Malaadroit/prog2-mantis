#include <stdio.h>
#include <string.h>

#include "C:\Users\BESY C. AGAMATA\c coding tut\c files\CCPROG2\MP\mp-github\prog2-mantis\Essentials\menuredefined.c"

int main()
{
    int i, j;
    int max_players = 6;

    initRandom();

    GameSettings settings;
    settings.winningPts    = WINNING_SCORE;
    settings.shufflingSeed = randomInt();

    GameData game;

    for(i = 0; i < MAX_PLAYERS; i++)
    {
        strcpy(game.PlayerList[i].username, "_");
        game.PlayerList[i].stats.wins = 0;
        game.PlayerList[i].stats.highScore = 0;
    }

    for(i = 0; i < MAX_PLAYERS; i++)
        strcpy(game.PlayerNames[i], "_");

    for(i = 0; i < MAX_PLAYERS_IN_GAME; i++)
    {
        game.Playing[i].info = NULL;
        game.Playing[i].score = 0;
        game.Playing[i].scoreCards = 0;
        for(j = 0; j < NUM_COLORS; j++)
        {
            game.Playing[i].tank[j] = 0;
            game.Playing[i].tankPoints[j] = 0;
        }
    }

    game.playersPlaying = 0;

    createPlayerList(game.PlayerList, MAX_PLAYERS);

    //sync PlayerNames from loaded PlayerList
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(strcmp(game.PlayerList[i].username, "_") != 0)
            strcpy(game.PlayerNames[i], game.PlayerList[i].username);
    }

    menu(&settings, &game);

    return 0;
}