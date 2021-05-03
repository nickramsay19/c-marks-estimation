#include <stdio.h>
#include <stdlib.h>

#include "include/Estimation.h"

Estimation* createEstimation(char* name, Assessment* assessments) {
    Estimation* estimation = (Estimation*) malloc(sizeof(Estimation));

    // initialise name
    *estimation->name = *(char*) malloc(20);
    strcpy(estimation->name, name);
    printf("Estimation name: %s\n", estimation->name);

    // initialise assessments
    *estimation->assessments = *assessments;

    return estimation;
}