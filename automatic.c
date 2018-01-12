#include <stdlib.h>

#include "game.h"
#include "variables.h"

//simple 'AI' that just randomizes the penguin and then picks the best move for that penguin for movement and completely randomizes for placement

void AutoPlacement( gameV *game ) //randomizes a suitable place for a penguin
{
    coordinates place;

    do
    {
        place.y = rand() % game->boardSizeY;
        place.x = 2 * ( rand() % game->boardSizeX ) + place.y % 2;
    } while ( game->board[place.x][place.y] != 1 );

    PutPenguin( game, place );
}

void FindPenguin( gameV *game, coordinates *from, int n ) //finds the coordinates of a penguin with a number
{
    int x, y, i = -1;
    for ( y = 0; y < game->boardSizeY; y ++ )
    {
        for ( x = y % 2; x < 2 * game->boardSizeX; x += 2)
        {
            if ( game->board[x][y] == - ( game->currentPlayer + 1 ) )
                i++;
            if ( i == n )
            {
                from->x = x;
                from->y = y;
                return;
            }
        }
    }
}

void RandomizeMove( gameV *game, coordinates *from, coordinates *to ) //randomizes a direction and then finds the closest move that gives the most points
{
    int bestmove = 0;
    coordinates test;
    coordinates best;
    coordinates dir;

    int n = rand() % game->penguins;

    int i;
    for ( i = 0; i < game->penguins; i ++ )
    {
        FindPenguin( game, from, ( n + i ) % game->penguins );

        int dr = rand() % 6;
        int k, d;
        int direction;

        for ( d = 0; d < 6; d ++)
        {
            direction = ( dr + d ) % 6;

            switch (direction)
            {
            case 0:
                dir.x = 2;
                dir.y = 0;
                break;
            case 1:
                dir.x = -2;
                dir.y = 0;
                break;
            case 2:
                dir.x = 1;
                dir.y = 1;
                break;
            case 3:
                dir.x = -1;
                dir.y = -1;
                break;
            case 4:
                dir.x = 1;
                dir.y = -1;
                break;
            case 5:
                dir.x = -1;
                dir.y = 1;
                break;
            }

            for ( k = 1, test.x = from->x + k * dir.x, test.y = from->y + k * dir.y;
                  test.x >= 0 && test.y >= 0 && test.x < 2 * game->boardSizeX && test.y < game->boardSizeY;
                  k ++, test.x = from->x + k * dir.x, test.y = from->y + k * dir.y )
                {
                    if ( game->board[ test.x ][ test.y ] > bestmove )
                    {
                        bestmove = game->board[ test.x ][ test.y ];
                        best.x = test.x; best.y = test.y;
                    }

                    if ( game->board[ test.x ][ test.y ] <= 0 || bestmove == 3 )
                        break;
                }

            if ( bestmove == 3 )
                break;
        }
        if ( bestmove == 3 )
            break;
    }
    if ( bestmove == 0)
    {
        to->x = from->x;
        to->y = from->y;
    }
    else
    {
        to->x = best.x; to->y = best.y;
    }
}


void AutoMovement( gameV *game )
{
    coordinates to, from;

    RandomizeMove( game, &from, &to );

    if ( to.x != from.x )
    {
        TakePenguin( game, from );
        PutPenguin( game, to );
    }
}
