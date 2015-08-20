/**
 * @file StringChange.c
 * @author  amitbenski
 *
 * @brief read line, changes the line as needed and prints the differences
 *
 * @section DESCRIPTION
 * Input  : line from the user
 * Process: changes uppercase letter to lowercase (and opposite)
 * 			changes numbers >=5 to 8 and <5 to 0
 * 			and all the other characters stay the same
 * Output : prints the original line and the converted line with arrow between them
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>


// -------------------------- const definitions -------------------------

#define VALID_CHARS "%[^\n]" //valid line characters
#define MAX_LENGTH 51
#define END_OF_LINE 0

const char CONVERT_CASE = 32; //+32 change Uppercase to Lowercase, -32 does the opposite
const char APOST = 34; //the ascii char represent the " (Apostrophe) sign
char gChangedLine[MAX_LENGTH]; //the converted line
char gLine[MAX_LENGTH]; //the line from the user


// ------------------------------ functions -----------------------------

/**
 * @ brief the function enters the changed characters into the new array
 * @ return void - but fill the gChangedLine array
 */
void createChangedLine()
{
	int i = 0;
	while (gLine[i]!= END_OF_LINE)
	{
		char curChar = gLine[i];
		if (curChar >= 'A' && curChar <= 'Z') //uppercase letter
		{
			gChangedLine[i] = curChar + CONVERT_CASE;
		}
		else if(curChar >= 'a' && curChar <= 'z')//lowercase letter
		{
			gChangedLine[i] = curChar - CONVERT_CASE;
		}
		else if (curChar >= '5' && curChar <= '9')//5<=number>=9
		{
			gChangedLine[i] = '8';
		}
		else if (curChar < '5' && curChar >= '0')//5 > number > 0
		{
			gChangedLine[i] = '0';
		}
		else //all other type of characters
		{
			gChangedLine[i] = curChar;
		}
		i++;
	}
}

/**
 * @ brief read line from the user
 * @ return none, prints the original line next to the new edited line
 */
int main()
{
	//char line[MAX_LENGTH] = {0};
	scanf(VALID_CHARS, gLine);
	createChangedLine(); //fill a new array with the needed filters
	printf("%c%s%c -> %c%s%c\n", APOST, gLine, APOST, APOST, gChangedLine, APOST);
	return 0;
}
