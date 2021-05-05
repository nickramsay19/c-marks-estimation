#ifndef SUBJECT_H
#define SUBJECT_H

#include "Assessment.h"
#include "Estimation.h"

typedef struct Subject {
    char name[20];
    Estimation estimations[20];
} Subject;

Subject* createSubject(char* name, Estimation* estimations);
Subject* createNullSubject();

void freeSubject(Subject* subject);

void printSubjectDetails(Subject subject);

#endif