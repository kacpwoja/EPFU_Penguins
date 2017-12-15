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

char CheckState( gameV *game )
{
    int x, y, n = 0;
    for( y = 0; y < game->boardSizeY; y ++ )
    {
        for( x = y%2; x < 2 * game->boardSizeX; x += 2 )
        {
            if( game->board[x][y] < 0 )
                n++;
        }
    }

    if( n == game->players * game->penguins ) return 'm';
    if( n < game->players * game->penguins ) return 'p';
    return 'e';
}

void NextPlayer( gameV *game )
{
    game->currentPlayer++;
    game->currentPlayer %= game->players;
}

void PutPenguin( gameV *game, int placeX, int placeY )
{
    game->score[ game->currentPlayer ] += game->board[placeX][placeY];
    game->board[placeX][placeY] = -(game->currentPlayer+1);
}

void TakePenguin( gameV *game, int x, int y )
{
    game->board[x][y] = 0;
}
