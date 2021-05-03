#ifndef ESTIMATION_H
#define ESTIMATION_H

#include "Assessment.h"

typedef struct Estimation {
    char name[20];
    Assessment assessments[20];
} Estimation;

Estimation* createEstimation(char* name, Assessment* asessments);

void freeEstimation(Estimation* estimation);

#endif