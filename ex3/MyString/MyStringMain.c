//#include <stdio.h>
//#include <string.h>
//#include "MyString.h"
//
//#define MAX_SIZE_OF_LINE 500
//#define FINISH 0
//
///**
// * @brief write to test.out the result of the compare action
// * @param result of the compare
// * @param str1, str2 the srings from the user
// * @return void
// */
//void writeResult(int result, FILE* stream,MyString* str1, MyString* str2)
//{
//	char* equal = " is equal to ";
//	char* smaller = " is smaller than ";
//	MyString* resultString = myStringAlloc();
//	//if the strings are equal
//	if (result == COMPARE_EQUAL)
//	{
//		myStringSetFromCString(resultString, equal);
//		myStringCat(str1,resultString);
//		myStringCat(str1,str2);
//		myStringWrite(str1,stream);
//	}
//	//if str1 > str2
//	else if (result == COMPARE_STR1_BIGGER)
//	{
//		myStringSetFromCString(resultString, smaller);
//		myStringCat(str2, resultString);
//		myStringCat(str2, str1);
//		myStringWrite(str2, stream);
//	}
//	//if str1 < str2
//	else
//	{
//		myStringSetFromCString(resultString, smaller);
//		myStringCat(str1, resultString);
//		myStringCat(str1, str2);
//		myStringWrite(str1, stream);
//	}
//	myStringFree(resultString);
//	myStringFree(str1);
//	myStringFree(str2);
//}
//
///**
// * @brief get two strings from the user, compare between them and write the result into file
// * @return int finish
// */
//int main()
//{
//	MyString* str1 = myStringAlloc();
//	MyString* str2 = myStringAlloc();
//
//	//get strings from the user
//	char value1[MAX_SIZE_OF_LINE];
//	char value2[MAX_SIZE_OF_LINE];
//	printf("enter String 1:\n");
//	fscanf(stdin,"%s", value1);
//	//fgets(value1, MAX_SIZE_OF_LINE, stdin);
//	strtok(value1, "\n");
//	printf("enter String 2:\n");
//	fscanf(stdin,"%s[^\n]", value2);
//	//fgets(value2, MAX_SIZE_OF_LINE, stdin);
//	strtok(value2, "\n");
//	//enter values to strings
//	myStringSetFromCString(str1, value1);
//	myStringSetFromCString(str2, value2);
//	//compare strings
//	int result = myStringCompare(str1, str2);
//	//print the result
//	FILE* stream;
//	stream = fopen("C:/Users/amitbenski/Desktop/Cprojects/ex3/test.txt", WRITE_MODE);
//	writeResult(result, stream, str1, str2);
//	fclose(stream);
//	return FINISH;
//}