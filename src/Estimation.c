#include <stdio.h>
#include <stdlib.h>

#include "include/Estimation.h"
#include "include/Assessment.h"

Estimation* createEstimation(char* name, Assessment* assessments) {

    // allocate an estimation
    Estimation* estimation = (Estimation*) malloc(sizeof(Estimation));

    // initialise name
    *estimation->name = *(char*) malloc(20);
    strcpy(estimation->name, name);

    /*
    *estimation->name = (char*) malloc(20 * sizeof(char));
    strcpy(*estimation->name, name);
    */

    // initialise assessments
    for (int i = 0; i < 20; i++) {

        // allocate name
        *estimation->assessments[i].name = *(char*) malloc(20);
        strcpy(estimation->assessments[i].name, assessments[i].name);

        // assign weight and value
        estimation->assessments[i].weight = assessments[i].weight;
        estimation->assessments[i].value = assessments[i].value;
    }

    // return the newly allocated estimation
    return estimation;
}

void freeEstimation(Estimation* estimation) {

    // free estimation name
    //free(estimation->name);

    // free each assessment
    for (int i = 0; i < 20; i++) {
        freeAssessment(&estimation->assessments[i]);
    }

    // finally free the estimation
    //free(estimation);
}