// SnakeProjectByLiorRoife.c
// Name: Lior Roife
// ID: 206257826
// 20/01/20

//***********************************************************  Snake Project Rules:  **********************************************************//
// This project is a "Snake Game" project.
// The snake grows up by one cell and increases it's speed every 5 steps.
// If the snake hits the board lines/hits itself the game is over (the player loses).
// Have Fun :)
//*********************************************************************************************************************************************//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//**********************************************************  Built-in Functions:  ************************************************************//
// terminal escape codes/ANSI escape codes (or ANSI escape sequences)
// "\x1B" is the escape character that tells your terminal that what comes next is not meant to be printed on the screen, 
// but rather a command to the terminal (or most likely terminal emulatoion).
// Turn escape codes ON.
void init(void);

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the posiiton.
//     y: the column of the posiiton.
void gotoxy(int x, int y);

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep(float secs);

//=============================================================================================================================================//
//**************************************************************  Own Parimeters  *************************************************************//
//**************************************************************  Explanation:    *************************************************************//
//=============================================================================================================================================//

//**************************************************************  Structures:  ****************************************************************//
typedef struct snake
{
	int x;
	int y;
	struct snake* next;
} SNAKE;

//**********************************************************  Constant Variable:  *************************************************************//
#define ROWS 25
#define COLS 75
const float STARTING_SPEED = 1.0; // The starting speed of the snake.
const float BOOST = 0.03;         // The speed boost the snake gets every 5 steps.
const char SNAKE_SHAPE = '@';     // The shape of the snake's body cells.
const char BOARD_SHAPE = '#';     // The shape of the game board cells.
#define RIGHT 'd'                 // Right direction (also the starting direction the snake goes to.
#define LEFT 'a'                  // Left direction.
#define UP 'w'                    // Up direction.
#define DOWN 's'                  // Down direction.

//**************************************************************  Functions:  *****************************************************************//
void PrintBoard();	                                                // This function prints the game board.

SNAKE* CreateCell(SNAKE* head, int x, int y);                       // This function gets as input a pointer to the snake's head , cordintaes (x,y).
																	// The function creates a new "Cell" and Initializes it's Cordinates to x,y.

void RemoveTail(SNAKE* head);                                       // This function gets as input a pointer to the snake's head , removes it's tail (The last "Cell" of the snake)
																	// and updates the snake.

bool CheckOutOfBounds(SNAKE* head, char dir, int* rows, int* cols); // This function gets as input pointer of the snake's head, current direction , pointers of rows, cols values.
																	// The function checks if the player passes the bounds of the board and returns true if he passed.
																	// Else, the function updates the values of cols/rows (according to the direction) and returns false.

bool CheckEatItself(SNAKE* head, char dir);                         // This function gets as input a pointer to the snake's head and the current direction.
																	// The function checks if the player made the snake to step on it's body.

void FreeSnake(SNAKE* head);                                        // This function gets as input a pointer to the snake's head.
																	// The function frees every "Cell" of the snake and prints " " (space) according to the Cell's indicates.

void PrintGameOver();                                               // This function prints "Game Over" when the player lose.

//************************************************************  Main Function:  ***************************************************************//
int main()
{
	init();
	PrintBoard();
	int steps = 0;                                  // Sums the steps of the snake.
	int rows = ROWS / 2, cols = COLS / 2;           // Initializes the strating cordinates to the center of the board.
	float speed = STARTING_SPEED;                   // Initializes the speed to the starting speed (1).
	char dir = RIGHT, oldDir = RIGHT;               // Initializes dir (current direction) and oldDir (the direction of the last step) to the starting direction ('d' -->).                                
	bool GameOver = false;                          // Flag variable indicates when the game is over (while GameOver = false the game is running).
	SNAKE* head = NULL;
	head = CreateCell(head, rows, cols);            // The first "Cell" of the snake.
	SNAKE* newHead;                                 // Being used later on the code when the snake grow up. 
	while (GameOver == false)
	{
		if (_kbhit())
		{
			dir = _getch();
			switch (dir)                            // This part of the code checks if the player made a wrong direction choise that makes him lose immediately.
													// For exmaple: the snake moves right (d) and the player presses left (a).
													// Or if the player passes the bounds of the board.
			{
			case RIGHT:
				if (oldDir == LEFT && steps > 5 || head->y == COLS - 1)
					GameOver = true;
				else
					cols++;
				break;
			case UP:
				if (oldDir == DOWN && steps > 5 || head->x == 2)
					GameOver = true;
				else
					rows--;
				break;
			case LEFT:
				if (oldDir == RIGHT && steps > 5 || head->y == 2)
					GameOver = true;
				else
					cols--;
				break;
			case DOWN:
				if (oldDir == UP && steps > 5 || head->x == ROWS - 1)
					GameOver = true;
				else
					rows++;
				break;
			default:                                                        // In case the player pressed a wrong Key (NOT one of: a,w,d,s).
			{
				GameOver = CheckOutOfBounds(head, oldDir, &rows, &cols);    // This part checks if the snake pass the board bounds using the old direction of the snake.
			}
			dir = oldDir;
			}
			if (GameOver == false && CheckEatItself(head, dir))
				GameOver = true;
			oldDir = dir;
		}
		else                                                                // This part of the code being activated every time/turn the player didn't press any key.
		{
			GameOver = CheckOutOfBounds(head, dir, &rows, &cols);
			if (GameOver == false && CheckEatItself(head, dir))
				GameOver = true;
		}
		if (GameOver == false)                                              // This part being activated if the player didn't lose yet (lose condition = false).
		{
			if (steps % 5 == 0 && steps != 0)
			{
				newHead = CreateCell(head, rows, cols);
				head = newHead;
				if (speed >= 0.1)
				{
					speed -= BOOST;
				}
			}
			else
			{
				if (steps > 5)
					RemoveTail(head);
				newHead = CreateCell(head, rows, cols);
				head = newHead;
				if (steps < 5)
					RemoveTail(head);
			}
			gotoxy(26, 1);  // Moves the cursor out of the game board (For aesthetic purposes).
			sleep(speed);
			steps++;
		}
	}
	FreeSnake(head);   // This part of the code being activated when the player lose (lose condition = true). It frees the memory allocated to the list.
	init();
	PrintBoard();
	PrintGameOver();
}

//*******************************************************  Built-in Functions' Body:  *********************************************************//
// Turn escape codes ON.
void init(void)
{
	system("cls");
}

// Moves the cursor to position (x,y) on screen.
// Parameters:
//     x: the row of the posiiton.
//     y: the column of the posiiton.
void gotoxy(int x, int y)
{
	printf("\x1b[%d;%df", x, y);
}

// Delays the execution of the program.
// Parameters:
//     secs: the length of the delay in seconds. 
void sleep(float secs)
{
	clock_t clocks_start = clock();
	while (clock() - clocks_start < secs * CLOCKS_PER_SEC);
}
//*********************************************************  Own Functions' Body:  ************************************************************//
void PrintBoard()
{
	{
		int i, j;
		for (i = 1; i <= ROWS; i++)
		{
			for (j = 1; j <= COLS; j++)
			{
				if (i == 1 || i == ROWS)
				{
					gotoxy(i, j);
					printf("%c", BOARD_SHAPE);
				}
				else if (j == 1 || j == COLS)
				{
					gotoxy(i, j);
					printf("%c", BOARD_SHAPE);
				}
			}
		}
	}
}

SNAKE* CreateCell(SNAKE* head, int x, int y)
{
	SNAKE* Cell;
	Cell = (SNAKE*)malloc(sizeof(SNAKE));
	Cell->x = x;
	Cell->y = y;
	Cell->next = head;
	gotoxy(Cell->x, Cell->y);
	printf("%c", SNAKE_SHAPE);
	return Cell;
}

void RemoveTail(SNAKE* head)
{
	SNAKE* current = head;
	SNAKE* last = head;
	while (current->next != NULL)
	{
		last = current;
		current = current->next;
	}
	gotoxy(current->x, current->y);
	printf(" ");
	free(last->next);
	last->next = NULL;
	gotoxy(26, 1);
}

bool CheckOutOfBounds(SNAKE* head, char dir, int* rows, int* cols)
{
	bool GameOver = false;
	switch (dir)
	{
	case RIGHT:
		if (head->y == COLS - 1)
			GameOver = true;
		else
			(*cols)++;
		break;
	case UP:
		if (head->x == 2)
			GameOver = true;
		else
			(*rows)--;
		break;
	case LEFT:
		if (head->y == 2)
			GameOver = true;
		else
			(*cols)--;
		break;
	case DOWN:
		if (head->x == ROWS - 1)
			GameOver = true;
		else
			(*rows)++;
		break;
	}
	return GameOver;
}

bool CheckEatItself(SNAKE* head, char dir)
{
	SNAKE* temp = head;
	while (temp->next != NULL)
	{
		switch (dir)
		{
		case RIGHT:
			if (temp->y == head->y + 1 && temp->x == head->x)
				return true;
			break;
		case UP:
			if (temp->y == head->y && temp->x == head->x - 1)
				return  true;
			break;
		case LEFT:
			if (temp->y == head->y - 1 && temp->x == head->x)
				return  true;
			break;
		case DOWN:
			if (temp->y == head->y && temp->x == head->x + 1)
				return  true;
			break;
		}
		temp = temp->next;
	}
	return false;
}

void FreeSnake(SNAKE* head)
{
	SNAKE* tempHead;
	while (head != NULL)
	{
		tempHead = head;
		gotoxy(tempHead->x, tempHead->y);
		printf(" ");
		head = head->next;
		free(tempHead);
		gotoxy(ROWS, 1);
	}
}

void PrintGameOver()
{
	gotoxy((ROWS / 2), (COLS / 2) - 4);
	printf("Game Over");
	gotoxy(ROWS, COLS);
}