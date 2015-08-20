/**
 * @file LineSeparator.c
 * @author  amitbenski
 *
 * @brief split between good and bad oranges with linear separator
 *  using learning algorithm.
 *
 * @section DESCRIPTION
 * Input  : file -
 * first line = the dimenstion number (n)
 * second line = the number of training lines (m)
 * 3 - m =  training lines
 * m+1 - end of file = test lines
 * Process:
 * reading the 2 first lines,
 * reading the training lines one by one - for each line:
 * convert line to vector, create inner product of the vector and weight vector,
 * check if the result tag equal to the given tag of the line,
 * and change the weight vector as needed.
 * finishing the training lines the weight vector is the linear separator
 * then run the test lines one by one and print the tag
 * that is result of the inner product of the linear separator and the vector.
 * Output : print the tags of the test lines 1 for good oranges and -1 for bad
 */

// ------------------------------ includes ------------------------------
#include "LineSeparator.h"

// -------------------------- const definitions -------------------------
#define EMPTY -1 // using when the file is empty
#define TRAINING_LINE "training"
#define TEST_LINE "test"
#define DONE 0

// ------------------------------- structs -------------------------------
/**
 * @ brief struct called Vector that holds:
 * 1. array of doubles - the values of the vector
 * 2. int tag 1 or -1
 */
typedef struct Vector
{
	double values[MAX_DIMENSION];
	int tag;
}Vector;

// ------------------------------ functions -----------------------------

/**
 * @ brief get the weight vector and a vector and calculate the inner product of them
 * @ return the inner product
 */
double innerProduct(Vector *vector, double* weightVector, int dimension)
{
	double innerProduct = 0;
	for (int i = 0; i < dimension; i++)
	{
		innerProduct += ((*vector).values[i] * weightVector[i]);
	}
	return innerProduct;
}

/**
 * @ brief get inner product and calculate the tag (1 or -1)
 * @ return the tag
 */
int getTag(double innerProduct)
{
	if ((innerProduct < ALMOST_ZERO) && (innerProduct > -ALMOST_ZERO))
	{
		innerProduct = 0;
	}
	if (innerProduct > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

/**
 * @ brief get the weight vector, vector, and the inner product between them
 * @ updates the weight vector as needed (as the algorithm works)
 */
void updateWeightVector(Vector *vector, double* weightVector, int tag, int dimension)
{
	for (int i = 0; i < dimension; i++)
	{
		weightVector[i] += (tag * (*vector).values[i]);
	}
}

/**
 * @ brief get a line - training or test and creates a Vector struct that fit the data in the line
 * we split the data in the line into doubles and insert them as the values of the vector
 * if its a training line we insert the last number in the line as the tag of the line
 * @ return void
 */
void lineToVector(char* line, int dimenstion, Vector *vector, char* lineType)
{
	char* splittedLine = strtok (line, COMMA);
	double value = strtod(splittedLine, NULL);
	(*vector).values[0] = value;

	//get the values of the line
	for (int i = 1; i < dimenstion; i++)
	{
		splittedLine = strtok(NULL, COMMA);
		value = strtod(splittedLine, NULL);
		(*vector).values[i] = value;
	}

	//get the tag of the line (if its a training line)
	if (lineType == TRAINING_LINE)
	{
		splittedLine = strtok(NULL, COMMA);
		int tag = atoi(splittedLine);
		(*vector).tag = tag;
		assert(((*vector).tag == 1) || ((*vector).tag = -1));
	}
}

/**
 * @ brief read the file, using the other functions
 * to create the weight vector and to tag all the test lines
 * @ return -1 if the file is empty and 0 otherwise (after finishing all the job)
 */
int parseFile(const char* file, double* weightVector)
{
	char dNum[MAX_CHARS_IN_LINE]; //dimension number
	char tNum[MAX_CHARS_IN_LINE]; //number of training lines
	char line[MAX_CHARS_IN_LINE];
	int dimensionNum;

	//create pointer of the file and open it
	FILE *pFile;
	pFile = fopen(file, "r");
	//check if the file is empty
	if (pFile == NULL)
	{
		return EMPTY;
	}

	//get the dimension number
	fgets(dNum, MAX_CHARS_IN_LINE, pFile);
	dimensionNum = atoi(dNum);

	assert(dimensionNum>1);

	//get the number of training lines
	fgets(tNum, MAX_CHARS_IN_LINE, pFile);
	int trainingLines = atoi (tNum);

	assert(trainingLines >= 1);

	Vector vector; //will use one Vector for all the lines (effective in space)
	//updates the weight vector using the data of the training lines
	for (int i = 0; i < trainingLines; i++)
	{
		fgets(line, MAX_CHARS_IN_LINE, pFile);
		lineToVector(line, dimensionNum, &vector, TRAINING_LINE);
		double innerP = innerProduct(&vector, weightVector, dimensionNum);
		int tag = getTag(innerP);
		if (tag!= vector.tag)
		{
			updateWeightVector(&vector, weightVector, vector.tag, dimensionNum);
		}
	}

	//calculate and print the tag of the test lines
	while (fgets(line, MAX_CHARS_IN_LINE, pFile) != NULL)
	{
		lineToVector(line, dimensionNum, &vector, TEST_LINE);
		double innerP = innerProduct(&vector, weightVector, dimensionNum);
		int tagLine = getTag(innerP);
		printf ("%d\n", tagLine);
	}
	fclose(pFile);
	return DONE;
}

/**
 * @ brief create weight vector,
 * read the file, calc and print the tags of the test lines - using the parse function
 * @ return -1 if the file is empty and 0 otherwise
 */
int lineSeparator(const char* file)
{
	double weightVector[MAX_DIMENSION] = {0};
	return parseFile(file, weightVector);
}

/**
 * @ brief create weight vector,
 * get file path as argument and use lineSeparator as the main function
 * @ return -1 if the file is empty and 0 otherwise
 */
int main(int argc, char **argv)
{
	assert(argc == 2);
	const char* file = argv[1];
	return lineSeparator(file);
}