#include <stdio.h>
#include <string.h>
#include "filefunctions.h" //file with functions regarding files (saving/loading etc)
#include "variables.h"     //file with the structure and possibly more later
#include "game.h"          //file with main game functions (printing the board, generating the board, checking for correct moves etc)
#include "interactive.h"   //file with the interactive mode loop
#include "automatic.h"   //for the automatic mode later

//this is complete garbage placeholder main

int main ( int argc, char **argv )
{
	gameV game;
	time_t tt;
    int seed = &tt;
    srand(seed);

//AUTOMATIC MODE
	if ( argc == 5 )
    {
        strcpy( game.filename, argv[3] );
        LoadBoard( &game );

        int playerNumber = atoi( argv[2] );
        if ( playerNumber <= game.players )
            game.currentPlayer = playerNumber - 1;
        else
        {
            printf( "ERROR: player number too big!\n" );
            return 1;
        }

        if ( strcmp( argv[1], "placement" ) == 0 )
        {
            if ( CheckState( &game ) != 'p' )
            {
                printf ( "Phase does not match with the board state!\n" );
                return 1;
            }

            AutoPlacement( &game );
        }
        else if ( strcmp( argv[1], "movement" ) == 0 )
        {
            if ( CheckState( &game ) != 'm' )
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

    else
    {
        char choice = '0';
        //test loop for interactive mode menu
        while (choice != 'q')
        {
            printf( "n - new game\tl - load game\tq - quit\n" );
            scanf( " %c", &choice );

            switch ( choice )
            {
            case 'n':
                printf( "insert board dimensions, number of players and penguins:\n" );
                scanf( "%d %d %d %d", &game.boardSizeX, &game.boardSizeY, &game.players, &game.penguins );
                GenerateBoard( &game );

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
                break;
            case 'l':
                printf( "insert file name\n" );
                scanf( " %s", game.filename );
                LoadBoard( &game );
                Interactive( &game );
            case 'q':
            default:
                break;

            }
        }
    }

	return 0;
}
