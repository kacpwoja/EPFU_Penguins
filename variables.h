#ifndef _VARIABLESH_
#define _VARIABLESH_

#define MAXSIZE 50
#define MAXPLAYERS 10

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
}gameV;

#endif
