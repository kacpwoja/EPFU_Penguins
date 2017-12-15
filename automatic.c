#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "variables.h"

//simple 'AI' that just randomizes the moves
//To add: checking if there are any moves possible (it gets stuck in a while loop otherwise...)

void AutoPlacement( gameV *game )
{
    time_t tt;
    int seed = &tt;
    srand(seed);

    int x, y;

    do
    {
        y = rand() % game->boardSizeY;
        x = 2 * ( rand() % game->boardSizeX ) + y % 2;
    } while ( game->board[x][y] != 1 );

    PutPenguin( game, x, y );
}

void AutoMovement( gameV *game )
{
    time_t tt;
    int seed = &tt;
    srand(seed);

    int toX, toY, fromX, fromY;
    int n = rand() % game->penguins + 1;
    int x, y, i = 0;

    //randomizes the penguin
    for ( y = 0; y < game->boardSizeY; y ++ )
    {
        for ( x = y % 2; x < 2 * game->boardSizeX; x += 2)
        {
            if ( game->board[x][y] == - ( game->currentPlayer + 1 ) )
                i++;
            if ( i == n )
            {
                fromX = x;
                fromY = y;
                break;
            }
        }
        if ( i == n )
            break;
    }

    //randomizes moves until finds a valid one
    do
    {
        toY = rand() % game->boardSizeY;
        if ( toY == fromY )
            toX = 2 * ( rand() % game->boardSizeX ) + toY % 2;
        else
        {
            toX = fromX + toY - fromY;
        }
    } while ( toX < 0 || toX > game->boardSizeX || game->board[toX][toY] <= 0 );

    TakePenguin( game, fromX, fromY );
    PutPenguin( game, toX, toY );
}
