CC = c99
FLAGS = -Wextra -Wvla -Wall

tests: MyString.c MyString.h
	$(CC) -g $(FLAGS) MyString.c -o MyStringTests
	MyStringTests
	
clean:
	-rm -f MyString MyStringMain test.out libmyString.a myTest.txt  *.o MyStringTests
	
main: MyString.c MyString.h MyStringMain.c myString
	$(CC) $(FLAGS) -c MyStringMain.c -o MyStringMain.o
	$(CC) MyStringMain.o -L. -lmyString -o MyStringMain
	MyStringMain
	
myString: MyString.c MyString.h
	$(CC) $(FLAGS) -DNDEBUG -c MyString.c -o MyString.o
	ar rcs libmyString.a MyString.o
