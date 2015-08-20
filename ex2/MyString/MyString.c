/**
 * @file MyString.c
 * @author  amitbenski
 *
 * @brief check how many times one string contains another string
 *
 * @section DESCRIPTION
 * Input  : two strings and isCyclic parameter
 * Process:
 * check if the two arent empty
 * run over the chars in str1.check if the char in specific index equals to the first char in str2
 * if it does, it check if the substring of str1 (starts with the index) is the same as str2
 * if it does, it count it and continue to the remain chars in str1,
 * if not it continue to the next index in str1
 * if its cyclic it will run over str1 in loop while we are in correct contains check.
 * Output : return the number of times str2 is inside str1
 */

// ------------------------------ includes ------------------------------
#include "MyString.h"

// -------------------------- const definitions -------------------------
#define END_OF_LINE '\0'
#define FALSE 0
#define FIRST_INDEX 0
#define SECOND_INDEX 1
#define TRUE 1

// ------------------------------ functions -----------------------------

/**
 * @ brief check if the strings are not null/empty
 * @ return FALSE if one of the string is null/empty and TRUE otherwise
 */
int notNull(const char* str1, const char* str2)
{
	if ((str1) && (str2))
	{
		if ((str1[0] != END_OF_LINE) && (str2[0] != END_OF_LINE))
		{
			return TRUE;
		}
	}
	return FALSE;
}

/**
 * @ brief get str1 and str2 and index when we know str1[index] = str2[index]
 * we check if the substring of str1 that starts from the index equals to str2
 * @ return index of str1 that matches to the last char of str2
 * and -1 if its not equals
 */
int contains(const char* str1, const char* str2, int index1, int isCyclic)
{
	int index2 = FIRST_INDEX;

	while ((str1[index1]!=END_OF_LINE) && (str2[index2]!=END_OF_LINE))
	{
		if (str1[index1] != str2[index2])
		{
			return -1;
		}
		index1 ++;
		index2 ++;
		if (isCyclic)
		{
			if ((str1[index1] == END_OF_LINE) && (str2[index2] != END_OF_LINE))
			{
				index1 = FIRST_INDEX;
			}
		}
	}
	if (str2[index2] == END_OF_LINE)
	{
		return 1;
	}
	else //if str1 got to the end of line
	{
		return -1;
	}
}

/**
 * Counts the amount of str1 substrings that are equal to str2.
 * In case one (or two) of the strings is empty- returns 0.
 * @str1 - the string
 * @str2 -  the substring
 * @isCyclic != 0 - search also for cyclic appearnce
 * @return number appearance of str2 as substring of str1
 */
unsigned int countSubStr(const char* str1, const char* str2, int isCyclic)
{
	if (!notNull(str1, str2))
	{
		return FALSE;
	}
	int i = FIRST_INDEX;
	int containsIndex;
	unsigned int counter = 0;
	//if it's not cyclic
	while (str1[i] != END_OF_LINE)
	{
		if (str1[i] == str2[FIRST_INDEX])
		{
			containsIndex = contains(str1, str2, i, isCyclic);
			if (containsIndex != -1)
			{
				counter++;
			}
		}
		i++;
	}
		return counter;
}

/**
 * @ brief driver for testing
 * @ return 0
 */
int main()
{
	return 0;
}