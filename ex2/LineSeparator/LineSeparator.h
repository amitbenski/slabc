#ifndef LINESEPARATOR_HEADER_FILE_H
#define LINESEPARATOR_HEADER_FILE_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARS_IN_LINE 150 //the max length of given line in the file
#define MAX_DIMENSION 74 //the max dimension
#define COMMA "," //the comma separates between values in the vector line
#define ALMOST_ZERO 0.00001 //inner product between this value to -0.0001 will round to 0

/**
 * @ brief create weight vector,
 * read the file, calc and print the tags of the test lines - using the parse function
 * @ return -1 if the file is empty and 0 otherwise
 */
int lineSeparator(const char* file);

#endif //LINESEPARATOR_HEADER_FILE_H
