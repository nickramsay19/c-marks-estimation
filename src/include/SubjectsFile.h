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

void freeSubjectsFile(SubjectsFile* subjectsFile);

Subject* getSubjectsArray(SubjectsFile* subjectsFile);

Subject* _getSubjectFromFile(SubjectsFile* subjectsFile);

Subject* getSubjectByName(SubjectsFile* subjectsFile, char* name);

//int doesSubjectExist(SubjectsFile* subjectsFile, Subject subject);

int doesSubjectExistByName(SubjectsFile* subjectsFile, char* name);

int addSubject(SubjectsFile* subjectsFile, Subject subject);

int removeSubject(SubjectsFile* subjectsFile, Subject subject);

int removeSubjectByName(SubjectsFile* subjectsFile, char* name);

void printSubjectsDetails(SubjectsFile* subjectsFile);

void printSubjectsNames(SubjectsFile* subjectsFile);

int _writeSubjectsToFile(SubjectsFile* subjectsFile);

void _writeExamplesToFile(SubjectsFile* subjectsFile);

#endif