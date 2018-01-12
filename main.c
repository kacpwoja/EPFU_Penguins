#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "filefunctions.h" //file with functions regarding files (saving/loading etc)
#include "variables.h"     //file with the structure and possibly more later
#include "game.h"          //file with main game functions (printing the board, generating the board, checking for correct moves etc)
#include "interactive.h"   //file with the interactive mode loop
#include "automatic.h"   //for the automatic mode later

//this is complete garbage placeholder main

int main ( int argc, char **argv )
{
	time_t tt;
    srand( (unsigned) time( &tt ) );
	gameV game;             //initializes the game struct and the random seed

//AUTOMATIC MODE
    if ( argc >= 5 )
    {
        strcpy( game.filename, argv[3] );
        game.players = 0;
        LoadBoard( &game );
        if ( game.players == 0 )
            return 1;

        int playerNumber = atoi( argv[2] );

        if ( playerNumber <= game.players )
            game.currentPlayer = playerNumber - 1;

        else
        {
            printf( "ERROR: player number incorrect!\n" );
            return 1;
        }

        if ( strcmp( argv[1], "placement" ) == 0 )
        {
            if ( CheckState( &game ) <= 0 )
            {
                printf ( "Phase does not match with the board state!\n" );
                return 1;
            }

            AutoPlacement( &game );
        }

        else if ( strcmp( argv[1], "movement" ) == 0 )
        {
            if ( CheckState( &game ) != 0 )
            {
                printf ( "Phase does not match with the board state!\n" );
                return 1;
            }

            AutoMovement( &game );
        }

        else
        {
            printf( "ERROR: wrong phase name!\n" );
            return 1;
        }

        strcpy( game.filename, argv[4] );
        SaveBoard( &game );
    }
//INTERACTIVE MODE
    else
    {
        char choice = '0';
        //test loop for interactive mode menu
        while (choice != 'q')
        {
            printf( "n - create new random board\tl - load game\tq - quit\n" );
            scanf( " %c", &choice );
            if (choice=='n')
            {
                printf( "insert board dimensions, number of players and penguins for each player:\n" );
                scanf( "%d %d %d %d", &game.boardSizeX, &game.boardSizeY, &game.players, &game.penguins );
                GenerateBoard( &game );
                PrintBoard( &game );
                printf( "save file? (y/n)\n" );
                scanf( " %c", &choice );
                if ( choice == 'y' )
                {
                    printf( "insert file name\n" );
                    scanf( " %s", game.filename );
                    SaveBoard( &game );
                }
                printf( "play now? (y/n)\n" );
                scanf( " %c", &choice );
                if ( choice == 'y' )
                Interactive( &game );
            }
            if (choice=='l')
            {
                printf( "insert file name\n" );
                scanf( " %s", game.filename );
                LoadBoard( &game );
                Interactive( &game );
            }
        }
    }

	return 0;
}
