#include "variables.h"

void Interactive( gameV *game )
{
    int state = CheckState( game );
    printf( "put number of maximal movements\n" );
    scanf( "%d", &game->maxmoves );
    int z=0,n,x,y;
    coordinates peng;
    coordinates peng1;
    char choice;
    //placement of penguins
    if(state>0)
    {
        printf("there are penguins left to place, do you want to place them now? y/n \n");
        scanf(" %c",&choice);
        if(choice=='y')
        {
        n=(game->penguins)*(game->players)-state;
        while(n!=0)
        {
            system("cls");
            PrintBoard( game );
            z++;
            printf("player %d place penguin nr. %d (x y)\n", (n%game->players)+1, z );
            scanf("%d %d",&x,&y);
//still need to check if it is possible to place penguin
            PutPenguin(game,x,y);
            NextPlayer(game);
            n--;


        }
        printf("all penguins are placed, do you want to save the board? y/n \n");
        scanf(" %c", &choice);
        if(choice=='y') SaveBoard(game);
        }
    }


    //main loop of interactive mode
    z=0;
    game->currentPlayer=0;
    while(z<=game->maxmoves+1  /* && penguinsabletomove>0 */ )
    {
    z++;
    system("cls");
    PrintBoard( game );
    printf("Move nr. %d:\n", z);
    printf("Player nr. %d, move penguin into another field \n ", game->currentPlayer+1);
    printf("Position of penguin you want to move (x y): \n");
    scanf("%d %d", &peng.x, &peng.y);
    //to do- check if there is a penguin on x,y
    printf("\n\n %c \n",CheckMoves(game, peng ) );
    //while(CheckMoves(game, peng )!='y')
    while(game->board[peng.x][peng.y]+game->currentPlayer+1!=0)
    {
        printf("\n Move unavailable, try another penguin\n", game->currentPlayer+1, (z%game->players)+1);
    scanf("%d %d", &peng.x, &peng.y);
    }

    printf("Field you want penguin to be moved (x y): \n");
    scanf("%d %d",&peng1.x, &peng1.y);

    PutPenguin(game, peng1.x,peng1.y);
    TakePenguin(game, peng.x, peng.y);
    NextPlayer(game);

    }







    /* Previous version
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

    */
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
