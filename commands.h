//
// Created by Terry Delaney on 12/17/19.
//
#include <stdio.h>
#include <string.h>

#include "book.h"

#ifndef GRADEBOOKSERVER_COMMANDS_H
#define GRADEBOOKSERVER_COMMANDS_H

#endif //GRADEBOOKSERVER_COMMANDS_H

void addStudent(int sock, char* name);
void addAssignment(int sock);
void addExam(int sock);
void studentGrade(int sock, char* name);
void assignmentGrade(int sock, char* assignment);
void examGrade(int sock, char* exam);
void displayAllGrades(int sock);