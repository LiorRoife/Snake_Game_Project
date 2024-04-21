Snake Project By Lior Roife (C)

//***********************************************************  Snake Project Rules:  **********************************************************//
// This project is a "Snake Game" project.
// The snake grows up by one cell and increases it's speed every 5 steps.
// If the snake hits the board lines/hits itself the game is over (the player loses).
// Have Fun :)
//*********************************************************************************************************************************************//
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
