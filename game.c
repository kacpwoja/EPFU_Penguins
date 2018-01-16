#include <stdlib.h>
#include "variables.h"

void GenerateBoard( gameV *game ) //a function that generates a random board and puts it in the program's variables
{
    game->currentPlayer = 0;
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

int CheckState( gameV *game )
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

    if( n == game->players * game->penguins ) return 0;
    if( n < game->players * game->penguins ) return game->players * game->penguins - n;
    return -1;
}

int CheckIfMovePossible (gameV *game,coordinates mo)
{
    if((game->boardSizeX)*2<mo.x || game->boardSizeY<mo.y) return 0;
    if(mo.x%2==0 && mo.y%2==1) return 0;
    if(mo.x%2==1 && mo.y%2==0) return 0;
    //
    return 1;


}

void NextPlayer( gameV *game ) //switches to the next player
{
    game->currentPlayer++;
    game->currentPlayer %= game->players;
}

void PutPenguin( gameV *game, coordinates place ) //places a penguin on the board and adds score
{
    game->score[ game->currentPlayer ] += game->board[place.x][place.y];
    game->board[place.x][place.y] = -(game->currentPlayer+1);
}

void TakePenguin( gameV *game, coordinates take ) //removes a penguin from the board
{
    game->board[take.x][take.y] = 0;
}

char CheckMoves( gameV *game, coordinates png ) //checks if the penguin on given coordinates can move - returns 'y' if yes, 'n' if not
{
    coordinates test;

    test.x = png.x + 2;
    test.y = png.y;
    if ( test.x < 2 * game->boardSizeX && game->board[test.x][test.y] > 0 )
        return 'y';

    test.x = png.x - 2;
    test.y = png.y;
    if ( test.x >= 0 && game->board[test.x][test.y] > 0 )
        return 'y';

    test.x = png.x + 1;
    test.y = png.y + 1;
    if ( test.x < 2 * game->boardSizeX && test.y < game->boardSizeY && game->board[test.x][test.y] > 0 )
        return 'y';

    test.x = png.x + 1;
    test.y = png.y - 1;
    if ( test.x < 2 * game->boardSizeX && test.y >= 0 && game->board[test.x][test.y] > 0 )
        return 'y';

    test.x = png.x - 1;
    test.y = png.y + 1;
    if ( test.x >= 0 && test.y < game->boardSizeY && game->board[test.x][test.y] > 0 )
        return 'y';

    test.x = png.x - 1;
    test.y = png.y - 1;
    if ( test.x >= 0 && test.y >= 0 && game->board[test.x][test.y] > 0 )
        return 'y';

    return 'n';
}
