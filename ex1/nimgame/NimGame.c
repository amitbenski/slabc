/**
 * @file NimGame.c
 * @author  amitbenski
 *
 * @brief an simple version of the nim strategy game
 *
 * @section DESCRIPTION
 * Input  : the user enter initial number of balls in the 2 boxes
 * Process: each turn a player choose one of the boxes and reduce up to 3 balls from the box
 * Output : prints who is the winner (the loser is the player that made one of the boxes empty)
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>

// -------------------------- const definitions -------------------------
#define POSITIVE 1
#define UNPOSITIVE -1
#define NUM_OF_BOXES 2
#define TRUE 1
#define FALSE 0
#define MAX_NUM_OF_BALLS 3
#define FIRST_PLAYER 1
#define SECOND_PLAYER 2
int gNumOfBalls[NUM_OF_BOXES];
int gCurPlayer;

// ------------------------------ functions -----------------------------

/**
 * @ brief the function check if the given num of balls is positive or not
 * @ return POSITIVE if the number is positive end UNPOSITIVE otherwise
 */
int isPositiveNumOfBalls(int balls)
{
	if (balls<POSITIVE)
	{
		printf("Number of balls in box must be positive.\n");
		return UNPOSITIVE;
	}
	else
	{
		return POSITIVE;
	}
}

/**
 * @ brief the function initial the boxes with num of balls given by the user
 * @ return POSITIVE if the number of balls in each box is positive end UNPOSITIVE otherwise
 */
int initialBoxes()
{
	const char HOW_MANY[] = "How many balls in box ";
	int i;
	for(i = 0; i < NUM_OF_BOXES; i++)
	{
		printf("%s%d?\n", HOW_MANY, i + 1);
		scanf("%d", &gNumOfBalls[i]) ;
		int numOfBalls = isPositiveNumOfBalls(gNumOfBalls[i]);
		if (numOfBalls == UNPOSITIVE)
		{
			return UNPOSITIVE;
		}
	}
	return POSITIVE;
}

/**
 * @ brief prints the board
 * @ return prints the number of balls in each box in the current situation of the game
 */
void printBoxes()
{
	printf("---------------\n");
	int i;
	for(i = 0; i < NUM_OF_BOXES; i++)
	{
		printf("Box %d: ", i + 1);
		int j;
		for (j = 0; j < gNumOfBalls[i]; j++)
		{
			printf("o");
		}
		printf("\n");
	}
	printf("---------------\n");
}

/**
 * @ brief check if the number of balls the player want to reduce from the box is unvalid
 * @ return TRUE if the number of balls is unvalid -
 * happans when: the num is unpositive/bigger then the number of balls in the box/bigger then 3
 *   return FALSE otherwise - which means the move is valid
 */
int unValidNumOfBalls(int chosenBox, int numberOfBalls)
{
	if (numberOfBalls < POSITIVE)//the num is unpositive
	{
		printf("Number of balls to take must be positive.\n");
		return (TRUE);
	}
	else if (numberOfBalls > MAX_NUM_OF_BALLS)//the num is bigger then 3
	{
		printf("Cannot take more than 3 balls at a time.\n");
		return(TRUE);
	}
	else if (numberOfBalls > gNumOfBalls[chosenBox - 1])//the num is bigger the num of balls in the
	// box
	{
		printf("Cannot take more balls than what's in the box.\n");
		return(TRUE);
	}
	else //every other choise
	{
		return FALSE;
	}
}

/**
 * @ brief makes a player turn
 * @ return void - makes the move (while checking its validation)
 * and changes the current player in the end of the turn
 */
void playerTurn(int player)
{
	int chosenBox;

	//choose a box
	do
	{
		printf("Player %d, it's your turn.\n", player);
		printf("Player %d, choose a box (1 or 2):\n", player);
		scanf("%d", &chosenBox) ;
	}
	while ((chosenBox != 1) && (chosenBox != 2));

	//pick the number of balls to reduce from the box
	int howMany;
	do
	{
		printf("Player %d, how many balls do you want to take from box %d?\n", player, chosenBox);
		scanf("%d", &howMany) ;
	}
	while (unValidNumOfBalls(chosenBox, howMany));

	//makes the move - reduce the amount of balls from the wanted box
	gNumOfBalls[chosenBox - 1] -= howMany;

	//change the current player (for the next turn)
	if (gCurPlayer == FIRST_PLAYER)
	{
		gCurPlayer = SECOND_PLAYER;
	}
	else
	{
		gCurPlayer = FIRST_PLAYER;
	}

}

// thisnis comment

/**
 * @ brief run a nim game between two player until one of the boxes is empty
 * @ return 0 - exit the program.
 * if the input from the user is valid, in the end of the game the function prints the winner
 */
int main()
{
	//initial the boxes - exit the program if the input is unvalid
	int initial = initialBoxes();
	if (initial == UNPOSITIVE)
	{
		return 0;
	}
	printBoxes();
	gCurPlayer = FIRST_PLAYER;

	while ((gNumOfBalls[0]) && (gNumOfBalls[1]))//while the 2 boxes arent empty
	{
		playerTurn(gCurPlayer);
		printBoxes();
	}
	//print who is the winner
	printf("Player %d wins the game.\n", gCurPlayer);
	return 0;
}

