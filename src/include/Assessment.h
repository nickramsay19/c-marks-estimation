#ifndef ASSESSMENT_H
#define ASSESSMENT_H

#include <string.h>

typedef struct Assessment {
    char name[20];
    float weight;
    float value; 

} Assessment;

Assessment* createAssessment(char* name, float weight, float value);

#endif