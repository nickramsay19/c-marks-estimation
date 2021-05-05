#ifndef ESTIMATION_H
#define ESTIMATION_H

#include "Assessment.h"

typedef struct Estimation {
    char name[20];
    float mark;
    char grade;
    Assessment assessments[20];
} Estimation;

Estimation* createEstimation(char* name, Assessment* asessments);

void freeEstimation(Estimation* estimation);

void calculateMarks(Estimation* estimation);

char calculateGrade(float mark);

#endif