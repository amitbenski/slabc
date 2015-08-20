#include "MyString.h"
#include <stdio.h>

int main ()
{
	char str1[50] = {0}, str2[50] = {0};
	int isCyclic;
	printf("str1 str2 mode\n");
	scanf("%s %s %d", str1, str2, &isCyclic);
	printf("the input is : %s, %s, %d\n", str1, str2,isCyclic);
	int num = countSubStr(str1, str2, isCyclic);
	printf("%d\n", num);
	return 0;
}