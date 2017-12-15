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
    int x, y;
    for ( x = 0; x < game->boardSizeX; x++ )
    {
        printf( "/\\");
    }
    printf( "\n" );
    for ( y = 0; y < game->boardSizeY; y++ )
    {
        if ( y%2 == 1 )
        {
            printf( "~" );
            for( x = y%2; x < 2 * game->boardSizeX; x+=2 )
            {
                if( game->board[x][y] == 0 )
                    printf( "~~" );
                if( game->board[x][y] > 0)
                    printf( "%dF", game->board[x][y] );
                if( game->board[x][y] < 0)
                    printf( "P%d", -game->board[x][y] );
            }
            printf("\n/");
            for( x = 0; x < game->boardSizeX; x++ )
                printf( "\\/");
        }
        if ( y%2 == 0 )
        {
            for( x = y%2; x < 2 * game->boardSizeX; x+=2 )
            {
                if( game->board[x][y] == 0 )
                    printf( "~~" );
                if( game->board[x][y] > 0)
                    printf( "%dF", game->board[x][y] );
                if( game->board[x][y] < 0)
                    printf( "P%d", -game->board[x][y] );
            }
            printf( "\n" );
            for( x = 0; x < game->boardSizeX; x++ )
                printf( "\\/");
            printf( "\\" );
        }
        printf( "\n" );
    }
    printf( "Scores: \n" );
    for ( x = 0; x < game->players; x++ )
    {
            printf( "Player%d: %d\t", x+1, game->score[x] );
    }
    printf( "\n" );
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

void PlacePenguin( gameV *game, int placeX, int placeY )
{
    if ( placeY % 2 == 0 )
        placeX *= 2;
    if ( placeY % 2 == 1)
        placeX = placeX * 2 + 1;

    if ( placeX < 2 * game->boardSizeX && placeY < game->boardSizeY && game->board[placeX][placeY] == 1 )
    {
        game->score [ game->currentPlayer ] += game->board[placeX][placeY];
        game->board[placeX][placeY] = -(game->currentPlayer+1);
        NextPlayer( game );
    }

    else printf( "Not a valid move!\n" );
}

void NextPlayer( gameV *game )
{
    game->currentPlayer++;
    game->currentPlayer %= game->players;
}
