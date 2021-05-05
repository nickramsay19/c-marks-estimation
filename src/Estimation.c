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

    // initialise grade
    // TODO: calculate marks here
    estimation->mark = 0.0;
    estimation->grade = 'N';

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

void calculateMarks(Estimation* estimation) {

    // declare an initialise the new mark value
    float mark = 0;

    // loop through each assessment
    for (int i = 0; i < 20; i++) {
        
        // check if the assessment is valid (has a name, positive non-zero mark and weight)
        if(strcmp(estimation->assessments[i].name, "") != 0 && estimation->assessments[i].weight > 0.001 && estimation->assessments[i].value > 0.001) {

            // add the marks attained
            mark += estimation->assessments[i].weight * estimation->assessments[i].value;
        }
    }

    // set the marks and grade
    estimation->mark = mark;
    estimation->grade = calculateGrade(mark);

}

char calculateGrade(float mark) {
    if (mark >= 0.85) return 'H';
    else if (mark >= 0.75) return 'D';
    else if (mark >= 0.65) return 'C';
    else if (mark >= 0.5) return 'P';
    else if (mark >= 0) return 'F';
    else return 'N';
}