//
// Created by Terry Delaney on 12/17/19.
//

#include <stdio.h>

FILE openinputfile()
{
	FILE *input = fopen("grades.txt", "r");
	
	return *input;
}

FILE openoutputfile()
{
	FILE *output = fopen("grades2.txt", "w");

	return *output;
}

void closeandrenamefiles(FILE* input, FILE* output)
{
	fclose(input);
	fclose(output);
	
	remove("grades.txt");
	rename("grades2.txt", "grades.txt");
}