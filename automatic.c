#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "variables.h"

//simple 'AI' that just randomizes the moves
//To add: checking if there are any moves possible (it gets stuck in a while loop otherwise...)

void AutoPlacement( gameV *game )
{
    coordinates place;

    do
    {
        place.y = rand() % game->boardSizeY;
        place.x = 2 * ( rand() % game->boardSizeX ) + place.y % 2;
    } while ( game->board[place.x][place.y] != 1 );

    PutPenguin( game, place );
}

void AutoMovement( gameV *game )
{
    coordinates to, from;
    int success = 0;

    RandomizePenguin( game, &from, &success);
    if ( success == 0 ) return;

    RandomizeMove( game, from, &to );

    TakePenguin( game, from );
    PutPenguin( game, to );
}

void RandomizePenguin( gameV *game, coordinates *from, int *success )
{
    int n = rand() % game->penguins;

    int i;
    for ( i = 0; i < game->penguins; i ++ )
    {
        FindPenguin( game, from, ( n + i ) % game->penguins );

        char check = CheckMoves( game, *from );
        if ( check == 'y' )
        {
            *success = 1;
            break;
        }
    }
}

void FindPenguin( gameV *game, coordinates *from, int n )
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

void RandomizeMove( gameV *game, coordinates from, coordinates *to )
{
    int dr = rand() % 6;
    int k, d;
    int direction;
    int bestmove = 0;
    coordinates test;
    coordinates best;
    coordinates dir;
    int threefound = 0;

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

        for ( k = 1; k < 2 * game->boardSizeX - from.x && k < from.x; k ++ )
            {
                test.x = from.x + k * dir.x; test.y = from.y + k * dir.y;

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

    to->x = best.x; to->y = best.y;
}
