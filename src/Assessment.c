#include <stdlib.h>

#include "include/Assessment.h"

Assessment* createAssessment(char* name, float weight, float value) {
    Assessment* assessment = (Assessment*) malloc(sizeof(Assessment));

    // initialise name
    *assessment->name = malloc(20 * sizeof(char));
    strcpy(assessment->name, name);

    // initialise weight and value
    assessment->weight = weight;
    assessment->value = value;

    return assessment;
}