#include <stdio.h>
#include <stdlib.h>

#include "include/Estimation.h"

Estimation* createEstimation(char* name, Assessment* assessments) {
    Estimation* estimation = (Estimation*) malloc(sizeof(Estimation));

    // initialise name
    *estimation->name = *(char*) malloc(20);
    strcpy(estimation->name, name);

    // initialise assessments
    for (int i = 0; i < 20; i++) {
        *estimation->assessments[i].name = *(char*) malloc(20);
        strcpy(estimation->assessments[i].name, assessments[i].name);
    }

    printf("%s, %s\n", estimation->assessments[0].name, estimation->assessments[1].name);

    return estimation;
}