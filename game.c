#include <stdlib.h>
#include <time.h>
#include "variables.h"

void GenerateBoard( gameV *game )
{
    game->currentPlayer = 0;
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

void PutPenguin( gameV *game, coordinates place )
{
    game->score[ game->currentPlayer ] += game->board[place.x][place.y];
    game->board[place.x][place.y] = -(game->currentPlayer+1);
}

void TakePenguin( gameV *game, coordinates take )
{
    game->board[take.x][take.y] = 0;
}

char CheckMoves( gameV *game, coordinates png )
{
    int k;

    for ( k = 1; k < 2 * game->boardSizeX - png.x && k < png.x ; k ++ )
    {
        if ( game->board[ png.x + 2 * k ][ png.y ] > 0 ||
             game->board[ png.x - 2 * k ][ png.y ] > 0 ||
             game->board[ png.x + k ][ png.y + k ] > 0 ||
             game->board[ png.x - k ][ png.y + k ] > 0 ||
             game->board[ png.x + k ][ png.y - k ] > 0 ||
             game->board[ png.x - k ][ png.y - k ] > 0 )
            return 'y';
    }

    return 'n';
}
