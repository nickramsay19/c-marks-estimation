#include <stdlib.h>

#include "include/Assessment.h"

Assessment* createAssessment(char* name, float weight, float value) {

    // allocate space for an assessment
    Assessment* assessment = (Assessment*) malloc(sizeof(Assessment));

    // initialise name
    *assessment->name = *(char*) malloc(20 * sizeof(char));
    strcpy(assessment->name, name);

    // initialise weight and value
    assessment->weight = weight;
    assessment->value = value;

    // return allocated assessment
    return assessment;
}