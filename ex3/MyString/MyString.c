// ------------------------------ includes ------------------------------
#include "MyString.h"
#include <stdlib.h>
#include <string.h>

typedef struct _MyString
{
	char* string;
	unsigned long length;
	unsigned long size;
}MyString;

// ------------------------------ functions -----------------------------

/**
 * @brief get the length of the string (the number of characters)
 * @param str
 * RETURN VALUE:
 *  @return the length of the string
 */
static unsigned long getLength(const char* str)
{
	unsigned long i = 0;
	while (str[i] != EOL)
	{
		i++;
	}
	return i;
}

/**
 * @brief Allocates a new MyString and sets its value to "" (the empty string).
 * 			It is the caller's responsibility to free the returned MyString.
 *
 * RETURN VALUE:
 * @return a pointer to the new string, or NULL if the allocation failed.
 */
MyString * myStringAlloc()
{
	MyString *newString = (MyString*)malloc(sizeof(MyString)); // memory allocation for MyString
	// struct
	if (newString == NULL)
	{
		return NULL;
	}
	newString -> string = NULL;
	newString -> length = 0;
	newString -> size = 0;
	return newString;
}

/**
 * @brief Frees the memory and resources allocated to str.
 * @param str the MyString to free.
 * If str is NULL, no operation is performed.
 */
void myStringFree(MyString *str)
{
	if (str != NULL)
	{
		if (str->string != NULL)
		{
			free(str->string);
			str->string = NULL;
		}
		free(str);
	}
}

/**
 * @brief Allocates a new MyString with the same value as str. It is the caller's
 * 			responsibility to free the returned MyString.
 * @param str the MyString to clone.
 * RETURN VALUE:
 *   @return a pointer to the new string, or NULL if the allocation failed.
 */
MyString * myStringClone(const MyString *str)
{
	if (str == NULL)
	{
		return NULL;
	}

	MyString* NewString = myStringAlloc();
	if (NewString == NULL)
	{
		return NULL;
	}

	if ((myStringSetFromMyString(NewString, str)) == MYSTRING_SUCCESS)
	{
		return NewString;
	}
	else
	{
		myStringFree(NewString);
		return NULL;
	}
}

static MyStringRetVal realocate(MyString *str, unsigned long newLength)
{
	char* reallocTest = (char*)realloc(str->string, newLength + 1);
	if (reallocTest == NULL)
	{
		return MYSTRING_ERROR;
	}

	else
	{
		str->string = reallocTest;
		memset(str->string, 0, newLength);
		str->size = newLength;
		return MYSTRING_SUCCESS;
	}
}

/**
 * @brief check if the difference between the two lengthes is significant
 * if it is we will need to do realloc
 * @param len1,len2
 * RETURN VALUE:
 *  @return TRUE if the difference is significant and FALSE otherwise
 */
static unsigned long big_Difference(unsigned long len1, unsigned long len2)
{
	if (((len1 / 2) >= len2) || (len2 <= len2))
	{
		return TRUE;
	}
	return FALSE;
}

/**
 * @brief get MyString and new string (value),
 * update the length of MyString, and also the size if needed
 * @param len1,len2
 * RETURN VALUE:
 *  @return MYSTRING_ERROE if tried to realloc and failed and true otherwise
 */
static MyStringRetVal updateMyString(MyString *str, const char* string)
{
	if (string == NULL)
	{
		return MYSTRING_ERROR;
	}
	unsigned long newLength = getLength(string);
	if (str->string == NULL)
	{
		str->string  = (char*)malloc(newLength + 1);
		memset(str->string, 0, newLength);
		if (str->string == NULL)
		{
			return MYSTRING_ERROR;
		}
	}
	else if (big_Difference(str->length, newLength))
	{
		if (realocate(str, newLength) == MYSTRING_ERROR)
		{
			return MYSTRING_ERROR;
		}
	}
	str->length = newLength;
	return MYSTRING_SUCCESS;
}

/**
 * @brief Sets the value of str to the value of other.
 * @param str the MyString to set
 * @param other the MyString to set from
 * RETURN VALUE:
 *  @return MYSTRING_SUCCESS on success, MYSTRING_ERROR on failure.
 */
MyStringRetVal myStringSetFromMyString(MyString *str, const MyString *other)
{
	if ((str == NULL) || (other == NULL))
	{
		return MYSTRING_ERROR;
	}

	if (updateMyString(str, other->string) == MYSTRING_ERROR)
	{
		return MYSTRING_ERROR;
	}

	memcpy(str->string, other->string, str->length+1);
	return MYSTRING_SUCCESS;
}

/**
 * @brief filter given character, info in return section
 * otherwize
 * @param curChar - the char to filter
 * RETURN VALUE:
 *  @return bool - false if lowercase letter (pass the filter) ,and  true otherwise
 */
static bool filt(const char* curChar)
{
	if (*curChar >= 'a' && *curChar<='z')
	{
		return false;
	}

	else
	{
		return true;
	}
}

/**
 * @brief filter the value of str acording to a filter.
 * 	remove from str all the occurrence of chars that are filtered by filt
 *	(i.e. filr(char)==true)
 * @param str the MyString to filter
 * @param filt the filter
 * RETURN VALUE:
 *  @return MYSTRING_SUCCESS on success, MYSTRING_ERROR on failure. */
MyStringRetVal myStringFilter(MyString *str, bool (*filt)(const char *))
{
	if (str == NULL || str->string == NULL)
	{
		return MYSTRING_ERROR;
	}
	unsigned long newLength = 0;
	MyString* tempString = myStringAlloc();

	for (int i = 0; i < (int)str->length; i++)
	{
		if (!filt(&(str->string[i])))
		{
			newLength ++;
		}
	}
	if (realocate(tempString, newLength) == MYSTRING_ERROR)
	{
		return MYSTRING_ERROR;
	}
	int tempIndex = 0;

	for (int j = 0; j < (int)str->length; j++)
	{
		if (!filt(&(str->string[j])))
		{
			tempString->string[tempIndex] = str->string[j];
			tempIndex ++;
		}
	}
	MyStringRetVal res = myStringSetFromMyString(str, tempString);
	myStringFree(tempString);
	return res;
}

/**
 * @brief Sets the value of str to the value of the given C string.
 * 			The given C string must be terminated by the null character.
 * 			Checking will not use a string without the null character.
 * @param str the MyString to set.
 * @param cString the C string to set from.
 * RETURN VALUE:
 *  @return MYSTRING_SUCCESS on success, MYSTRING_ERROR on failure.
 */
MyStringRetVal myStringSetFromCString(MyString *str, const char * cString)
{
	if ((str == NULL) || (cString == NULL))
	{
		return MYSTRING_ERROR;
	}

	if (updateMyString(str, cString) == MYSTRING_ERROR)
	{
		return MYSTRING_ERROR;
	}

	memcpy(str->string, cString, str->length+1);
	return MYSTRING_SUCCESS;
}

/**
 * @brief return the number of digits in number
 * @param int number
 * RETURN VALUE:
 *  @return counter - the number of digits
 */
int nDigits(int num)
{
	int counter = 0;
	while (num > ZERO)
	{
		counter++;
		num /= BASE;
	}
	return counter;
}

/**
 * @brief convert int to string (char*)
 * @param int number
 * RETURN VALUE:
 *  @return string that represent the given number
 */
char* intToStr(int num)
{
	char* str = NULL;
	unsigned long dCount = 0;
	int negativeNum = FALSE;

	if(num < 0)
	{
		num = -num;
		dCount++;
		negativeNum = TRUE;
	}

	dCount += nDigits(num);
	str = (char*)malloc(dCount + 1);
	if (str == NULL)
	{
		return NULL;
	}
	str[dCount] = EOL;

	while(num > ZERO)
	{
		str[dCount-1] = (char)((num%BASE) + '0');
		num = num / BASE;
		dCount--;
	}

	if (negativeNum)
	{
		str[0] = '-';
	}
	return str;
}

/**
 * @brief Sets the value of str to the value of the integer n.
 *	(i.e. if n=7 than str should contain ‘7’)
 * 	You are not allowed to use itoa (or a similar functions) here but must code your own conversion function.
 * @param str the MyString to set.
 * @param n the int to set from.
 * RETURN VALUE:
 *  @return MYSTRING_SUCCESS on success, MYSTRING_ERROR on failure.
 */
MyStringRetVal myStringSetFromInt(MyString *str, int n)
{
	if (str == NULL)
	{
		return MYSTRING_ERROR;
	}
	char* cString = intToStr(n);

	MyStringRetVal res = (myStringSetFromCString(str,cString));
	free(cString);
	return res;
}


/**
 * @brief Returns the value of str as an integer.
 * 	If str cannot be parsed as an integer,
 * 	the return value should be MYSTR_ERROR_CODE
 * 	NOTE: positive and negative integers should be supported.
 * @param str the MyString
 * @return an integer
 */
int myStringToInt(const MyString *str)
{
	if (str == NULL)
	{
		return MYSTRING_ERROR;
	}
	int i;
	int result = 0;
	int isNegative = FALSE;
	if ((str->string[0]) == '-')
	{
		isNegative = TRUE;
		i = 1;
	}
	else
	{
		i = 0;
	}
	for ( ; i < (int)str->length; i++)
	{
		char curChar = str->string[i];
		if (curChar >= '0' && curChar <= '9')
			result = result * 10 +  ( curChar - '0' );
		else
		{
			return MYSTR_ERROR_CODE;
		}
	}
	if (isNegative)
	{
		return -result;
	}
	return result;
}

/**
 * @brief Returns the value of str as a C string, terminated with the
 * 	null character. It is the caller's responsibility to free the returned
 * 	string by calling free().
 * @param str the MyString
 * RETURN VALUE:
 *  @return the new string, or NULL if the allocation failed.
 */
char * myStringToCString(const MyString *str)
{
	if (str == NULL)
	{
		return NULL;
	}
	char* newString = malloc(str->length + 1);
	if (newString == NULL)
	{
		return NULL;
	}
	for (int i = 0; i < (int)str->length; i++)
	{
		newString[i] = str->string[i];
	}
	return newString;
}


/**
 * @brief Appends a copy of the source MyString src to the destination MyString dst.
 * @param dest the destination
 * @param src the MyString to append
 * RETURN VALUE:
 *  @return MYSTRING_SUCCESS on success, MYSTRING_ERROR on failure.
 */
MyStringRetVal myStringCat(MyString * dest, const MyString * src)
{
	if ((src == NULL) || (dest == NULL))
	{
		return MYSTRING_ERROR;
	}
	unsigned long newLength = src->length + dest->length;
	int i = (int)(dest->length);
	if (dest->string == NULL)
	{
		dest->string = (char*)malloc(newLength + 1);
		if (dest->string == NULL)
		{
			return MYSTRING_ERROR;
		}
	}
	else if (big_Difference(dest->length, newLength))
	{
		if (realocate(dest, newLength) == MYSTRING_ERROR)
		{
			return MYSTRING_ERROR;
		}
	}
	dest->length = newLength;
	int j = 0;
	for ( ; i < (int)dest->length; i++)
	{
		dest->string[i] = src->string[j];
		j++;
	}
	return MYSTRING_SUCCESS;
}
/**
 * @brief Sets result to be the concatenation of str1 and str2.
 * 	result should be initially allocated by the caller.
 * 	result shouldn't be the same struct as str1 or str2.
 * @param str1
 * @param str2
 * @param result
 * RETURN VALUE:
 *  @return MYSTRING_SUCCESS on success, MYSTRING_ERROR on failure.
 */
MyStringRetVal myStringCatTo(const MyString *str1, const MyString *str2, MyString *result)
{
	if ((str1 == NULL) || (str2 == NULL) || (result == NULL))
	{
		return MYSTRING_ERROR;
	}
	if ((str1->string == NULL) || (str2->string == NULL))
	{
		return  MYSTRING_ERROR;
	}
	unsigned long newLength = str1->length + str2->length;
	char* newString = (char*)malloc((newLength)+1);
	if (newString == NULL)
	{
		return MYSTRING_ERROR;
	}
	memcpy(newString, str1->string, str1->length + 1);
	int j = 0;
	for (int i = (int) (str1->length); i < (int) (newLength); i++)
	{
		newString[i] = str2->string[j];
		j++;
	}
	MyStringRetVal res = myStringSetFromCString(result, newString);
	free(newString);
	return res;
}

/**
 * @brief Compare str1 and str2.
 * @param str1
 * @param str2
 *
 * RETURN VALUE:
 * @return an integral value indicating the relationship between the strings:
 * 	A zero value indicates that the strings are equal.
 * 	A value greater than zero indicates that the first character that does not match has a greater ASCII value in str1 than in str2;
 * 	And a value less than zero indicates the opposite.
 * 	If strings cannot be compared, the return value should be MYSTR_ERROR_CODE
 */
int myStringCompare(const MyString *str1, const MyString *str2)
{
	if ((str1 == NULL) || (str2 == NULL))
	{
		return MYSTR_ERROR_CODE;
	}
	if ((str1->string == NULL) || (str2->string == NULL))
	{
		return MYSTR_ERROR_CODE;
	}
	int i = 0;
	while ((i < (int)str1->length) && (i < (int)str2->length)){
		if (str2->string[i] < str1->string[i])
		{
			return COMPARE_STR1_BIGGER;
		}
		else if (str1->string[i] < str2->string[i])
		{
			return COMPARE_STR2_BIGGER;
		}
		i++;
	}
	if (str1->string[i] != EOL)
	{
		return COMPARE_STR1_BIGGER;
	}
	else if (str2->string[i] != EOL)
	{
		return COMPARE_STR2_BIGGER;
	}
	return COMPARE_EQUAL;
}

int comparator(char char1, char char2)
{
	if (char2 < char1)
	{
		return -1;
	}
	else if (char2 < char1)
	{
		return 1;
	}
	else return 0;
}

/**
 * @brief Compares str1 and str2.
 * @param str1
 * @param str2
 * @param comparator
 * RETURN VALUE:
 * @return an integral value indicating the relationship between the strings:
 * 	A zero value indicates that the strings are equal according to the custom comparator (3rd parameter).
 * 	A value greater than zero indicates that the first MyString is bigger according to the comparator.
 * 	And a value less than zero indicates the opposite.
 * 	If strings cannot be compared, the return value should be MYSTR_ERROR_CODE
 */
int myStringCustomCompare(const MyString *str1, const MyString *str2, int (*comparator)(char,
																						char))
{
	if ((str1 == NULL) || (str2 == NULL))
	{
		return MYSTR_ERROR_CODE;
	}
	if ((str1->string == NULL) || (str2->string == NULL))
	{
		return MYSTR_ERROR_CODE;
	}
	int i = 0;
	int result;
	while ((i < (int)str1->length) && (i < (int)str2->length))
	{
		result = comparator(str1->string[i], str2->string[i]);
		if (result != COMPARE_EQUAL)
		{
			return result;
		}
		i++;
	}
	if (str1->string[i] != EOL)
	{
		return COMPARE_STR1_BIGGER;
	}
	else if (str2->string[i] != EOL)
	{
		return COMPARE_STR2_BIGGER;
	}
	return COMPARE_EQUAL;
}

/**
 * @brief Check if str1 is equal to str2.
 * @param str1
 * @param str2
 *
 * RETURN VALUE:
 * @return an integral value indicating the equality of the strings (logical equality - that they are composed of the very same characters):
 * 	A zero value indicates that the strings are not equal.
 * 	A greater than zero value indicates that the strings are equal.
 * 	If strings cannot be compared, the return value should be MYSTR_ERROR_CODE
  */
int myStringEqual(const MyString *str1, const MyString *str2)
{
	if ((str1 == NULL) || (str2 == NULL))
	{
		return MYSTR_ERROR_CODE;
	}
	if ((str1->string == NULL) || (str2->string == NULL))
	{
		return MYSTR_ERROR_CODE;
	}
	int result = myStringCompare(str1, str2);
	if (result == COMPARE_EQUAL)
	{
		return EQUAL_STRS;
	}
	else
	{
		return NOT_EQUAL_STRS;
	}

}

/**
 * @brief Check if str1 is equal to str2.
 * @param str1
 * @param str2
 * @param comparator
 * RETURN VALUE:
 * @return an integral value indicating the equality of the strings
 * using a custom comparator (3rd parameter):
 * 	A zero value indicates that the strings are not equal.
 * 	A greater than zero value indicates that the strings are equal.
 * 	If string cannot be compared, the return value should be MYSTR_ERROR_CODE
 */
int myStringCustomEqual(const MyString *str1, const MyString *str2, int (*comparator)(char, char))
{
	if ((str1 == NULL) || (str2 == NULL))
	{
		return MYSTR_ERROR_CODE;
	}
	if ((str1->string == NULL) || (str2->string == NULL))
	{
		return MYSTR_ERROR_CODE;
	}
	int i = 0;
	int result;
	while ((i < (int)str1->length) && (i < (int)str2->length)){
		result = comparator(str1->string[i],str2->string[i]);
		if (result != COMPARE_EQUAL)
		{
			return NOT_EQUAL_STRS;
		}
		i++;
	}
	if ((str1->string[i] != EOL) || (str2->string[i] != EOL))
	{
		return NOT_EQUAL_STRS;
	}
	return EQUAL_STRS;
}


/**
 * @return the amount of memory (all the memory that used by the MyString object itself
 * and its allocations), in bytes, allocated to str1.
 */
unsigned long myStringMemUsage(const MyString *str1)
{
	if (str1 == NULL || str1->string == NULL)
	{
		return MYSTRING_ERROR;
	}
	return sizeof(str1) + str1->size + sizeof(int)*2 + sizeof(str1->string);
}

/**
 * @return the length of the string in str1.
 */
unsigned long myStringLen(const MyString *str1)
{
	if (str1 == NULL)
	{
		return MYSTRING_ERROR;
	}
	return str1->length;
}

/**
 * Writes the content of str to stream. (like fputs())
 *
 * RETURNS:
 *  @return MYSTRING_SUCCESS on success, MYSTRING_ERROR on failure.
 */
MyStringRetVal myStringWrite(const MyString *str, FILE *stream)
{
	unsigned long bytesWritten = fwrite(str->string, sizeof(char), str->length, stream);
	if (bytesWritten < str->length)
	{
		return MYSTRING_ERROR;
	}
	return MYSTRING_SUCCESS;
}

/**
 * wrap MyStringCompare so we will be able to use it in the sort functions
 * @param str1 , str2 two strings to compare
 * RETURNS:
 *  @return the result of myStringCompare
 */
static int wrapperMyStringCompare(MyString**str1 ,MyString**str2)
{
	return (myStringCompare(*str1,*str2));
}

/**
 * @brief sort an array of MyString pointers
 * @param arr
 * @param len
 * @param comparator custom comparator
 *
 * RETURN VALUE:none
  */
void myStringCoustomSort( MyString ** arr, unsigned long len, int (*comparator)(const void*,
																				 const void*))
{
	qsort(arr, len, sizeof(MyString*), comparator);
}

/**
 * @brief sorts an array of MyString pointers according to the default comparison (like in
 * myStringCompare)
 * @param arr
 * @param len
 *
 * RETURN VALUE: none
  */
void myStringSort( MyString ** arr, unsigned long len)
{
	if (arr != NULL)
	{
		qsort(arr, len, sizeof(MyString *), (int (*)(const void *, const void *))
				wrapperMyStringCompare);
	}
}

// ------------------------------ testFunctions -----------------------------

#ifndef NDEBUG

/**
 * @brief test allocate and free methods
 * @param
 * RETURN VALUE: bool - true if the function work and false otherwise
  */
static bool testAllocateAndFree()
{
	puts("----------------------------------------------------------------------------");
	MyString* testStr = myStringAlloc();
	if (testStr == NULL)
	{
		return false;
	}
	if (testStr->length != EMPTY_STR)
	{
		printf("myStringAlloc method Failed, length expected %d, but is %lu",EMPTY_STR,
			   testStr->length);
		myStringFree(testStr);
		return false;
	}
	myStringFree(testStr);
	printf("allocate and free Succeed\n");
	return true;
}

/**
 * @brief test myStringSetFromMyString by comparing the two MyString's values after the setting
 * @param str1 and str2 - give str2 the value of str1
 * RETURN VALUE: void
  */
static void testMyStringSetFromMyString(MyString* str1, MyString* str2)
{
	puts("----------------------------------------------------------------------------");
	myStringSetFromMyString(str2, str1);
	if (memcmp(str1->string, str2->string, str1->size))
	{
		printf("myStringSetFromMyString method Failed, string expected %s, but is %s\n",
			   str1->string, str2->string);
	}
	else
	{
		printf("myStringSetFromMyString method Succeed, string expected %s, and is %s\n",
			   str1->string, str2->string);
	}
}

/**
 * @brief test clone method that using allocate and MyStringSetFromMyString
 * @param two strings - source and destination (the clone one)
 * RETURN VALUE: void
  */
static void testMyStringClone(MyString* sourceStr, MyString* destStr)
{
	puts("----------------------------------------------------------------------------");
	destStr = myStringClone(sourceStr);
	if (memcmp(sourceStr->string, destStr->string, sourceStr->size))
	{
		printf("myStringClone method Failed, string expected %s, but is %s\n",
			   sourceStr->string, destStr->string);
	}
	else
	{
		printf("myStringClone method Succeed, string expected %s, and is %s\n",
			   sourceStr->string, destStr->string);
	}
}

/**
 * @brief test filter method by filtering string and comparing to expected result
 * @param MyString string before filte and expcted string after filter
 * RETURN VALUE: void
  */
static void testMyStringFilter(MyString* stringBeforeFilt, char* stringAfterFilt)
{
	puts("----------------------------------------------------------------------------");
	myStringFilter(stringBeforeFilt, filt);
	if (memcmp(stringBeforeFilt->string, stringAfterFilt, stringBeforeFilt->size))
	{
		printf("MyStringFilter method Failed, string expected %s, but is %s\n",stringAfterFilt,
			   stringBeforeFilt->string);
	}
	else
	{
		printf("MyStringFilter method Succeed, string expected %s, and is %s\n",stringAfterFilt,
			   stringBeforeFilt->string);
	}

}

/**
 * @brief test MyStringSetFromCString method by sets sourceString value as the given testString
 * @ param sourceString given MyString
 * @param testString the value to set in sourceString
 * RETURN VALUE: void
  */
static void testMyStringSetFromCString(MyString* sourceString, char* testString)
{
	puts("----------------------------------------------------------------------------");
	myStringSetFromCString(sourceString, testString);
	if (memcmp(sourceString->string, testString, sourceString->length))
	{
		printf("MyStringSetFromCString method Failed, string expected %s, but is %s\n",testString,
			   sourceString->string);
	}
	else
	{
		printf("MyStringSetFromCString method Succeed, string expected %s, and is %s\n",testString,
			   sourceString->string);
	}
}

/**
 * @brief test MyStringSetFromInt method by sets testString value as the given int num
 * @ param testString given MyString
 * @param int value to set in testString
 * RETURN VALUE: void
  */
static void testMyStringSetFromInt(MyString* testString,int num,char* numAsString)
{
	puts("----------------------------------------------------------------------------");
	myStringSetFromInt(testString, num);
	if (memcmp(testString->string,numAsString,testString->length))
	{
		printf("MyStringSetFromInt method Failed, string expected %s, but is %s\n",numAsString,
			   testString->string);
	}
	else
	{
		printf("MyStringSetFromInt method Succeed, string expected %s, and is %s\n",numAsString,
			   testString->string);
	}
}

/**
 * @brief test MyStringToInt by comparing result of the method to expected int result
 * @ param intString given MyString
 * @param expectedResult expected int result
 * RETURN VALUE: void
  */
static void testMyStringToInt(MyString* intString, int expectedResult)
{
	puts("----------------------------------------------------------------------------");
	int num = myStringToInt(intString);
	if (num != expectedResult)
	{
		printf("MyStringToInt method Failed, number expected %d, but is %d\n", expectedResult,
			   num);
	}
	else
	{
		printf("MyStringToInt method Succeed, number expected %d, and is %d\n", expectedResult,
			   num);
	}
}

/**
 * @brief test testMyStringToCString by comparing result of the method to expected result
 * @ param testString given MyString
 * @param str expected string result
 * RETURN VALUE: void
  */
static void testMyStringToCString(MyString* testString, char* str)
{
	puts("----------------------------------------------------------------------------");
	char* result = myStringToCString(testString);
	if  (strcmp(str, result))
	{
		printf("MyStringToCString method Failed, string expected %s, but is %s\n", str,
			   result);
	}
	else
	{
		printf("MyStringToCString method Succeed, string expected %s, and is %s\n", str,
			   result);
	}
	free(result);
}

/**
 * @brief test MyStringCat method by comparing result of the method to expected result
 * @ param str1,str2 given MyStrings - the method append str2 value into str1
 * @param expectedResult expected string result
 * RETURN VALUE: void
  */
static void testMyStringCat(MyString* str1, MyString* str2, char* expectedResult)
{
	puts("----------------------------------------------------------------------------");
	myStringCat(str1,str2);
	if (strcmp(str1->string, expectedResult))
	{
		printf("testMyStringCat method Failed, string expected %s, but is %s\n", expectedResult,
			   str1->string);
	}
	else
	{
		printf("testMyStringCat method Succeed, string expected %s, and is %s\n", expectedResult,
			   str1->string);
	}
}

/**
 * @brief test MyStringCatTo method by comparing result of the method to expected result
 * @ param str1,str2,str3 given MyStrings - the method sets str1+str2 values into str3
 * @param expectedResult expected string result
 * RETURN VALUE: void
  */
static void testMyStringCatTo(MyString* str1, MyString* str2, MyString* str3, char*expectedResult)
{
	puts("----------------------------------------------------------------------------");
	MyStringRetVal res = myStringCatTo(str1, str2, str3);
	if (res == MYSTRING_SUCCESS)
	{
		if (strcmp(str3->string, expectedResult))
		{
			printf("MyStringCatTo method Failed, string expected %s, but is %s\n", expectedResult,
				   str3->string);
		}
		else
		{
			printf("MyStringCatTo method Succeed, string expected %s, and is %s\n", expectedResult,
				   str3->string);
		}
	}
}

/**
 * @brief test MyStringCompare method by comparing result of the method to expected result
 * @ param str1,str2 given MyStrings - the method compares between them
 * @param expectedResult expected comparison result
 * RETURN VALUE: void
  */
static void testMyStringCompare(MyString* str1, MyString* str2, int expectedResult)
{
	puts("----------------------------------------------------------------------------");
	int result = myStringCompare(str1, str2);
	if (expectedResult != result)
	{
		printf("MyStringCompare method Failed, result expected %d, but is %d\n", expectedResult,
			   result);
	}
	else
	{
		printf("MyStringCompare method Succeed, result expected %d, and is %d\n", expectedResult,
			   result);
	}
}

/**
 * @brief test MyStringCustomCompare method
 * by comparing result of the method to expected string result
 * the comparison is based on the comparator method
 * @ param str1,str2 given MyStrings - the method compares between them
 * @param expectedResult expected comparison result
 * RETURN VALUE: void
  */
static void testMyStringCustomCompare(MyString* str1,MyString* str2,int expectedResult)
{
	puts("----------------------------------------------------------------------------");
	int result = myStringCustomCompare(str1, str2, comparator);
	if (expectedResult != result)
	{
		printf("MyStringCustomCompare method Failed, result expected %d, but is %d\n",
			   expectedResult, result);
	}
	else
	{
		printf("MyStringCustomCompare method Succeed, result expected %d, and is %d\n",
			   expectedResult, result);
	}
}

/**
 * @brief test MyStringEqual method by comparing result of the method to expected result
 * @ param str1,str2 given MyStrings - the method check if they are equal
 * @param expectedresult expected comparison result
 * RETURN VALUE: void
  */
static void testMyStringEqual(MyString* str1,MyString* str2,int expectedResult)
{
	puts("----------------------------------------------------------------------------");
	int res = myStringEqual(str1,str2);
	if (res != expectedResult)
	{
		printf("MyStringEqual method Failed, result expected %d, but is %d\n",
			   expectedResult, res);
	}
	else
	{
		printf("MyStringEqual method Succeed, result expected %d, and is %d\n",
			   expectedResult, res);
	}
}

/**
 * @brief test MyStringCustomEqual method by comparing result of the method to expected result
 * the comparison is based on the comparator method
 * @ param str1,str2 given MyStrings - the method check if they are equal
 * @param expectedresult expected comparison result
 * RETURN VALUE: void
  */
static void testMyStringCustomEqual(MyString* str1,MyString* str2,int expectedResult)
{
	puts("----------------------------------------------------------------------------");
	int res = myStringCustomEqual(str1, str2, comparator);
	if (res != expectedResult)
	{
		printf("MyStringCustomEqual method Failed, result expected %d, but is %d\n",
			   expectedResult, res);
	}
	else
	{
		printf("MyStringCustomEqual method Succeed, result expected %d, and is %d\n",
			   expectedResult, res);
	}
}

/**
 * @brief test MyStringMemUsage method by comparing result of the method to expected result
 * @ param str given MyString - the method check the memory usage of the str
 * @param expectedresult expected memory usage
 * RETURN VALUE: void
  */
static void testMyStringMemUsage(MyString* str, unsigned long expectedResult)
{
	puts("----------------------------------------------------------------------------");
	unsigned long result = myStringMemUsage(str);
	if (result != expectedResult)
	{
		printf("MyStringMemUsage method Failed, result expected %lu, but is %lu\n",
			   expectedResult, result);
	}
	else
	{
		printf("MyStringMemUsage method Succeed, result expected %lu, and is %lu\n",
			   expectedResult, result);
	}
}

/**
 * @brief test MyStringLen method by comparing result of the method to expected result
 * @ param str given MyString - the method check the length of the string
 * @param expectedresult expected length
 * RETURN VALUE: void
  */
static void testMyStringLen(MyString* str, unsigned long expectedLength)
{
	puts("----------------------------------------------------------------------------");
	unsigned long length = myStringLen(str);
	if (length != expectedLength)
	{
		printf("MyStringLen method Failed, result expected %lu, but is %lu\n",
			   expectedLength, length);
	}
	else
	{
		printf("MyStringLen method Succeed, result expected %lu, and is %lu\n",
			   expectedLength, length);
	}
}

/**
 * @brief test MyStringWrite method by trying to write str into file
 * @ param str given MyString - the string we want to write
 * RETURN VALUE: void
  */
static void testMyStringWrite(MyString* str)
{
	puts("----------------------------------------------------------------------------");
	FILE* stream;
	stream = fopen("test.txt", WRITE_MODE);
	MyStringRetVal result = myStringWrite(str,stream);
	if (result == MYSTRING_ERROR)
	{
		printf("MyStringWrite method Failed, couldnt write %s into stream\n", str->string);
	}
	else
	{
		printf("MyStringWrite method Succeed, wrote %s into stream\n", str->string);
	}
	fclose(stream);
}

/**
 * @brief test MyStringCoustomSort method
 * the sort based on the myStringCompare method
 * by comparing result of the method to expected sort result
 * @ param str1,str2,str3 given MyStrings - the method sort those string in array
 * @param expectedresult expected sorted array
 * RETURN VALUE: void
  */
static void testMyStringCoustomSort(MyString* str1, MyString* str2, MyString* str3, char*
sortedArray[])
{
	puts("----------------------------------------------------------------------------");
	unsigned long sizeArray = 3;
	bool res = true;
	MyString* arr[3] = {str3,str2,str1};
	printf("the given array is:\n");
	for (int i = 0; i < (int)sizeArray; i++)
	{
		printf("%s, ",arr[i]->string);
	}

	myStringCoustomSort(arr, sizeArray, (void*)wrapperMyStringCompare);////sort the array

	printf("\nthe array after sort is:\n");
	for (int j = 0; j < (int)sizeArray; j++)
	{
		printf("%s, ",arr[j]->string);
		if (sortedArray[j] != arr[j]->string)
		{
			res = false;
		}
	}
	if (res)
	{
		printf("\nMyStringCoustomSort method Failed, the array didnt sort well\n");
	}
	else
	{
		printf("\nMyStringCoustomSort method Succeed, the array sorted well\n");
	}
}

/**
 * @brief test MyStringSort method
 * by comparing result of the method to expected sort result
 * @ param str1,str2,str3 given MyStrings - the method sort those string in array
 * @param expectedresult expected sorted array
 * RETURN VALUE: void
  */
static void testMyStringSort(MyString* str1, MyString* str2, MyString* str3,char* sortedArray[])
{
	puts("----------------------------------------------------------------------------");
	unsigned long sizeArray = 3;
	bool res = true;
	MyString* arr[3] = {str1, str2, str3};
	printf("the given array is:\n");
	for (int i = 0; i < (int)sizeArray; i++)
	{
		printf("%s, ",arr[i]->string);
	}

	myStringSort(arr, 3); //sort the array

	printf("\nthe array after sort is:\n");
	for (int j = 0; j < (int)sizeArray; j++)
	{
		printf("%s, ",arr[j]->string);
		if (sortedArray[j] != arr[j]->string)
		{
			res = false;
		}
	}
	if (res)
	{
		printf("\nMyStringCoustomSort method Failed, the array didnt sort well\n");
	}
	else
	{
		printf("\nMyStringCoustomSort method Succeed, the array sorted well\n");
	}
}

//run all the tests
int main()
{
	if (testAllocateAndFree())
	{
		//create 3 test strings
		MyString *str1 = myStringAlloc();
		MyString *str2 = myStringAlloc();
		MyString *str3 = myStringAlloc();

		//--------------------------run tests----------------------------------
		//fromCstring
		testMyStringSetFromCString(str1, "500hello500world");
		//fromMyString
		testMyStringSetFromMyString(str1,str2);
		//Filter
		testMyStringFilter(str1, "helloworld");
		//fromInt
		testMyStringSetFromInt(str2, 500, "500");
		//clone
		testMyStringClone(str1,str3);
		//ToInt
		myStringSetFromCString(str1, "abc");
		testMyStringToInt(str1, MYSTR_ERROR_CODE);
		testMyStringToInt(str2, 500);
		//toCstring
		testMyStringToCString(str1,"abc");
		//Cat
		myStringSetFromCString(str1, "Hello");
		myStringSetFromCString(str2, "World");
		testMyStringCat(str1, str2, "HelloWorld");
		//CatTo
		myStringSetFromCString(str1, "Hello");
		testMyStringCatTo(str1,str2 ,str3, "HelloWorld");
		//Compare
		myStringSetFromCString(str1, "HelloWorld");
		testMyStringCompare(str1, str3, COMPARE_EQUAL);
		testMyStringCompare(str1,str2, COMPARE_STR2_BIGGER);
		//CustomCompare
		testMyStringCustomCompare(str1,str2, COMPARE_STR2_BIGGER);
		//Equal
		testMyStringEqual(str1,str3, EQUAL_STRS);
		testMyStringEqual(str1,str2, NOT_EQUAL_STRS);
		//CustomEqual
		testMyStringCustomEqual(str1,str3, EQUAL_STRS);
		testMyStringCustomEqual(str1,str2, NOT_EQUAL_STRS);
		//memUsage
		testMyStringMemUsage(str1, 34);
		//myStringLen
		testMyStringLen(str1, 10);
		//Write
		testMyStringWrite(str1);
		//MyStringSort
		char* sortedArray[3] = {"aaa","bbb","ccc"};
		myStringSetFromCString(str1, "bbb");
		myStringSetFromCString(str2, "aaa");
		myStringSetFromCString(str3, "ccc");
		testMyStringSort(str1,str2,str3,sortedArray);
		//MyStringCustomSort
		testMyStringCoustomSort(str1,str2,str3,sortedArray);
		//free the test strings
		myStringFree(str1);
		myStringFree(str2);
		myStringFree(str3);
	}
	return FINISH;
}

#endif