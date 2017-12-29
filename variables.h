#ifndef _VARIABLESH_
#define _VARIABLESH_

#define MAXSIZE 100
#define MAXPLAYERS 20

typedef struct gamevariables
{
	int boardSizeX;     //dimensions of the board
	int boardSizeY;
	int players;        //number of players and number of penguins each player has
	int penguins;
	int currentPlayer;  //the number of the player taking his
	char filename[50];
	int board[MAXSIZE * 2][MAXSIZE];  //array with the board state
	int score[MAXPLAYERS];      //scores of each player
	int maxmoves; // in interactive mode maximal number of movements or sth like that
}gameV;

typedef struct //simple structure to make things less messy
{
    int x;
    int y;
}coordinates;

#endif
