#include "variables.h"

void Interactive( gameV *game )
{
    char state = CheckState( game );
    while( state != 'q' )
    {
        state = CheckState( game );

        if( state == 'e' )
        {
        printf( "ERROR! WRONG NUMBER OF PENGUINS!" );
        break;
        }

        else PrintBoard( game );

        if ( state == 'p' )
        {
            int x, y;
            printf( "Player%d, place your penguin (input x and y coordinates)\n", game->currentPlayer+1 );
            printf( "(negative coordinates to save and quit) " );
            scanf( " %d %d", &x, &y );

            if( x < 0 || y < 0 )
                {
                    state = 'q';
                    SavePrompt( game );
                }

            else
                PlacePenguin( game, x, y );
        }

        if (state == 'm' )
        {
            printf( "movement not availible yet\n" );
            state = 'q';
            SavePrompt( game );
        }
    }
}

void PlacePenguin( gameV *game, int placeX, int placeY )
{
        placeX = placeX * 2 + placeY % 2;

    if ( placeX < 2 * game->boardSizeX && placeY < game->boardSizeY && game->board[placeX][placeY] == 1 )
    {
        PutPenguin( game, placeX, placeY );
        NextPlayer( game );
    }

    else printf( "Not a valid move!\n" );
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

void SavePrompt( gameV *game )
{
    char choice;
    printf( "Do you wish to save? (y/n)\n" );
    scanf( " %c", &choice );
    if ( choice == 'y' )
    {
        printf( "Input file name:\n" );
        scanf( " %s", game->filename );
        SaveBoard( game );
    }
}
