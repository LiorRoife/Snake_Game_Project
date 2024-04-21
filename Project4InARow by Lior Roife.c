//Project4InARow.c
// Name: Lior Roife
// ID: 206257826
// 14/12/19

#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h> 



/*************** Board ***************/
#define ROWS 6
#define COLS 7
char board[ROWS][COLS];


/*********** Declarations ************/

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();

/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);

/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);

/// This function clears the screen.
void clearScreen();

//=================================================================================================================================================//
//****************************************************************  Own Functions  ****************************************************************//
//****************************************************************  Explanation:   ****************************************************************//
//=================================================================================================================================================//

/******************** The Stones *********************/
/// Two const chars used as the game stones/tools. 
const char STONE1 = 'X';
const char STONE2 = 'O';

/******************* Print Board ********************/
/// This function prints the current board status.
void PrintBoard();

/******************** Take Turn *********************/
/// This function used every time it is some player's turn to play.
/// It prints which player's turn it is.
/// It gets from the player a choice of a row number where he wants to put his stone.
/// Then it Checks if the choice is valid (1-7 number , not full column).
/// Then it puts the player's stone in the board.
/// Then the function switches player.
int  TakeTurn(int player);

/******************* Search Empty Row *******************/
/// Checks where is the first empty row for the chosen column and returns its number. (Used in takeTurn() function - subfunction).
int emptyRow(int choice);

/******************* Check Horizontal *******************/
/// This function used to check if any player made an Horizontal seria of Four stones.
bool CheckHorizontal();

/******************** Check Vertical ********************/
/// This function used to check if any player made a Vertical seria of Four stones.
bool CheckVertical();

/******************** Check Diagonal ********************/
/// This function used to check if any player made a Diagonal seria of Four stones.
bool CheckDiagonal();

/********************** Check Draw **********************/
/// This function used to check if the board is full and there is no winner (no one made any seria of Four equal stones).
bool CheckDraw();



//=================================================================================================================================================//
//***************************************************************  Main       *********************************************************************//
//***************************************************************  Function:  *********************************************************************//
//====================================================================================================================================+============//
int main()
{
	int player = 1, lastPlayer;
	bool GameOver = false;
	initBoard();
	PrintBoard();                                                                             // First print
	while (GameOver == false)                                                                 // The game continues while GameOver!=true
	{
		if (player == 1)
		{
			lastPlayer = player;
			player = TakeTurn(lastPlayer);
			PrintBoard();
		}
		else
		{
			lastPlayer = player;
			player = TakeTurn(lastPlayer);
			PrintBoard();
		}
		if (CheckHorizontal() || CheckVertical() || CheckDiagonal() || CheckDraw())
		{
			if (CheckHorizontal() || CheckVertical() || CheckDiagonal())
			{
				printf("Congratulations player number %d, YOU WON!", lastPlayer);
				GameOver = true;
			}
			if (CheckDraw())
			{
				printf("ITS A DRAW!");
				GameOver = true;
			}
		}
	}
}

//=================================================================================================================================================//
//****************************************************************  Own Functions  ****************************************************************//
//****************************************************************  Build:         ****************************************************************//
//=================================================================================================================================================//

 /******************* Print Board *******************/
void PrintBoard()
{
	int i, j;
	printf("    1    2    3    4    5    6    7\n");
	for (i = ROWS; i > 0; i--)
	{
		printf("%c ", ('A' + ROWS - i));
		for (j = 0; j < COLS; j++)
			printf("  %c  ", getCell(ROWS - i + 1, j + 1));
		printf("\n");
	}
}

/******************* Take Turn *******************/
int  TakeTurn(int player)
{
	int choice, row = 6, eRow;
	printf("Player number %d:\nPlease choose a column (a number between 1 - 7): ", player);
	scanf_s("%d", &choice);
	while (choice < 1 || choice> 7 || getCell(1, choice) != ' ')
	{
		if (choice < 1 || choice> 7)
		{
			printf("Youv'e entered an invalid column number. Please choose a number between 1-7.\n");  // Check if the choice between 1-7.
			scanf_s("%d", &choice);
		}
		else
		{
			printf("The column you chosed is full. Please choose another column.\n");                  // Check if the chosen column not full.
			scanf_s("%d", &choice);
		}
	}
	eRow = emptyRow(choice);
	if (player == 1)
		setCell(eRow, choice, STONE1);
	else
		setCell(eRow, choice, STONE2);
	clearScreen();
	if (player == 1)                                                                                   // Switch player when finish
		return 2;
	else
		return 1;
}

/******************* Search Empty Row *******************/
int emptyRow(int choice)
{
	int row = 6;
	while (getCell(row, choice) != ' ')  // Place the stone in the first empty row of the chosen column.
		row--;
	return row;
}

/******************* Check Horizontal *******************/
bool CheckHorizontal()
{
	int i, j;
	for (i = 1; i <= ROWS; i++)
		for (j = 1; j <= 4; j++)
			if (getCell(i, j) == getCell(i, j + 1) && getCell(i, j + 1) == getCell(i, j + 2) && getCell(i, j + 2) == getCell(i, j + 3) && getCell(i, j) != ' ')
				return true;
	return false;
}

/******************* Check Vertical *******************/
bool CheckVertical()
{
	int i, j;
	for (i = 1; i <= COLS; i++)
		for (j = 1; j <= 3; j++)
			if (getCell(j, i) == getCell(j + 1, i) && getCell(j + 1, i) == getCell(j + 2, i) && getCell(j + 2, i) == getCell(j + 3, i) && getCell(j, i) != ' ')
				return true;
	return false;
}

/******************* Check Diagonal *******************/
bool CheckDiagonal()
{
	int i, j, k, s;
	for (i = 1; i <= 4; i++)                   //Check Left Diagonal
		for (j = 1; j <= 4; j++)
			if (getCell(i, j) == getCell(i + 1, j + 1) && getCell(i + 1, j + 1) == getCell(i + 2, j + 2) && getCell(i + 2, j + 2) == getCell(i + 3, j + 3) && getCell(i, j) != ' ')
				return true;
	for (k = 6; k >= 3; k--)                  //Check Right Diagonal
		for (s = 1; s <= 4; s++)
			if (getCell(k, s) == getCell(k - 1, s + 1) && getCell(k - 1, s + 1) == getCell(k - 2, s + 2) && getCell(k - 2, s + 2) == getCell(k - 3, s + 3) && getCell(k, s) != ' ')
				return true;
	return false;
}

/********************* Check Draw *********************/
bool CheckDraw()
{
	int i, count = 0;
	for (i = 1; i <= COLS; i++)
		if (getCell(1, i) != ' ')
			count++;
	if (count == 7)
		return true;
	else
		return false;
}

/********** Implementations **********/
char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}

void initBoard()
{
	int i = 0, j = 0;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}
void clearScreen()
{
	system("cls");
}