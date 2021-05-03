#ifndef SUBJECT_H
#define SUBJECT_H

#include "Assessment.h"
#include "Estimation.h"
#include "Grade.h"

typedef struct Subject {
    char name[20];
    float mark;
    Grade grade;
    Estimation estimations[20];
} Subject;

Subject* createSubject(char* name, Estimation* estimations);

#endif