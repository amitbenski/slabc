#include <iostream>

int main()
{
	char *str1;
	char str2[5];
	str1 = str2;
	str1[3] = 'k';
	puts(str1);
	return 0;
}