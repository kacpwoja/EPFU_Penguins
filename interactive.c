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
