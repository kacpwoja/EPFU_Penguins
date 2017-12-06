#include <stdlib.h>
#include <time.h>
#include "variables.h"

void GenerateBoard( gameV *game )
{
    game->currentPlayer = 0;
    //initializing random seed
    time_t tt;
    int seed = &tt;
    srand(seed);
    //randomizing the board
    int x, y, random;
    for ( y = 0; y <= game->boardSizeY; y ++ )
    {
        for ( x = y%2; x<= 2 * game->boardSizeX; x += 2 )
        {
            random = rand() % 6;
            switch( random )
            {
            case 0:
            case 1:
            case 2:
                game->board[x][y] = 1;
                break;
            case 3:
            case 4:
                game->board[x][y] = 2;
                break;
            case 5:
                game->board[x][y] = 3;
                break;
            }
        }
    }
    //resetting player scores
    for ( x = 0; x < game->players; x++ )
    {
        game->score[x] = 0;
    }
}

void PrintBoard( gameV *game )
{
    //basic placeholder print to see if loading a file works
    printf( "%d\n", game->boardSizeX );
    printf( "%d\n", game->boardSizeY );
    printf( "%d\n", game->players );
    printf( "%d\n", game->penguins );
    int x, y;
    for ( y = 0; y < game->boardSizeY; y ++ )
    {
        for ( x = y%2; x< game->boardSizeX; x += 2 )
        {
            printf( "%d ", game->board[x][y] );
        }
        printf( "\n" );
    }
    for ( x = 0; x < game->players; x++ )
    {
        printf( "%d\n", game->score[x] );
    }
}
