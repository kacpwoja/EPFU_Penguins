#ifndef _VARIABLESH_
#define _VARIABLESH_

typedef struct gamevariables
{
	int boardSizeX;     //dimensions of the board
	int boardSizeY;
	int players;        //number of players and number of penguins each player has
	int penguins;
	int currentPlayer;  //the number of the player taking his
	char filename[50];
	int board[50][50];  //array with the board state
	int score[10];      //scores of each player
}gameV;

#endif
