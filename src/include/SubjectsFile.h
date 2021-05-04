#ifndef SUBJECTSFILE_H
#define SUBJECTSFILE_H

#include <stdio.h>

#include "Subject.h"

typedef struct SubjectsFile {
    FILE* fp;
    char* name; // TODO: change from array to char pointer in other files
    Subject* subjects;
} SubjectsFile;

SubjectsFile* createSubjectsFile(char* name);

Subject* getSubjectsArray(SubjectsFile* subjectsFile);

Subject* _getSubjectFromFile(SubjectsFile* subjectsFile);

void _writeExamplesToFile(SubjectsFile* subjectsFile);

#endif