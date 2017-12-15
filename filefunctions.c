#include <stdio.h>
#include "variables.h"

void SaveBoard( gameV *game )
{
    FILE *savefile;
    savefile = fopen( &game->filename, "w" );
    //printing first data
    fprintf( savefile, "%d\n", game->boardSizeX );
    fprintf( savefile, "%d\n", game->boardSizeY );
    fprintf( savefile, "%d\n", game->players );
    fprintf( savefile, "%d\n", game->penguins );
    //printing the board
    int x, y;
    for ( y = 0; y < game->boardSizeY; y ++ )
    {
        for ( x = y%2; x< 2 * game->boardSizeX; x += 2 )
        {
            fprintf( savefile, "%d ", game->board[x][y] );
        }
        fprintf( savefile, "\n" );
    }
    //printing scores
    for ( x = 0; x < game->players; x++ )
    {
        fprintf( savefile, "%d\n", game->score[x] );
    }
    fclose( savefile );
}


void LoadBoard( gameV *game )
{
    FILE *loadfile;
    loadfile = fopen( &game->filename, "r" );
    //scanning first data
    fscanf( loadfile, "%d\n", &game->boardSizeX );
    fscanf( loadfile, "%d\n", &game->boardSizeY );
    fscanf( loadfile, "%d\n", &game->players );
    fscanf( loadfile, "%d\n", &game->penguins );
    //scanning the board
    int x, y;
    for ( y = 0; y < game->boardSizeY; y ++ )
    {
        for ( x = y%2; x< 2 * game->boardSizeX; x += 2 )
        {
            fscanf( loadfile, "%d ", &game->board[x][y] );
        }
        fscanf( loadfile, "\n" );
    }
    //scanning scores
    for ( x = 0; x < game->players; x++ )
    {
        fscanf( loadfile, "%d\n", &game->score[x] );
    }
    fclose( loadfile );
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
