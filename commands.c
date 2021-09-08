//
// Created by Terry Delaney on 12/17/19.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "book.h"

void addStudent(int sock, char* name)
{
	FILE input = openinputfile();
	FILE output = openoutputfile();
	
	// Variable Declarations
		
	int exams = 0;
	int assignments = 0;
	char fileLine[256];
	char ch = NULL;
	char* lineItems;
	char response[256];
	
	// Determine number of Exams and Assignments
	
	while ((ch = fgetc(input)) != EOF | "\n")
	{
		if (ch == EOF)
			break;
		
		strcat(fileLine, ch);
	}
	
	fputc(fileLine, &output);
	lineItems = strtok(fileLine, ", ");
	exams = atoi(lineItems[0]);
	assignments = atoi(lineItems[1]);
	
	// Search if Student Exists
	
	while ((ch = fgetc(&input)) != EOF)
	{
		clear(fileLine);
		strcat(fileLine, ch);
		while ((ch = fgetc(&input)) != "\n" | EOF)
		{
			strcat(fileLine, ch);
		}
		
		lineItems = strtok(fileLine, ",");
		
		if (lineItems[0].equals(name))
		{
			strcpy (response, "The Student: ");
			strcat (response, name);
			strcat (response, "Already Exists.");
			write (sock, response, strlen(response));
			return;
		}
		
			else
			{
				fputc(fileLine, &output);
			}
		}
	}
	
	// Add new Student
	clear(fileLine);
	strcpy(fileLine, name);
	strcat(fileLine, ", ");
		
	// Add zeroes for the existing exam grades
	
	for (int i = 0; i < exams; i++)
	{
		strcat(fileLine, "0, ");
	}
	
	// Add separator between exams and assignments
	strcat(fileLine, "|, ");
	
	// Add zeroes for the existing assignment grades
	
	for (int i = 0; i < assignments; i++)
	{
		strcat(fileLine, "0, ");
	}
	
	fputc(fileLine, output);
	
	closeAndRenameFiles(inFile, outFile);
	
	// Return to calling method
	
	return;
}

void addAssignment(int sock)
{

}

void addExam(int sock)
{

}

void studentGrade(int sock, char* name)
{

}

void assignmentGrade(int sock, char* assignment)
{

}

void examGrade(inr sock, char* exam)
{

}

void displayAllGrades(int sock)
{

}

void clear(char string)
{
	for (int i = 0; i < strlen(string); i++)
		string[1] = "\0";
	
}