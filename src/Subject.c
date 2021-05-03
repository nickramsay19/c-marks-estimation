#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Subject.h"
#include "include/Estimation.h"

Subject* createSubject(char* name, Estimation* estimations) {
    Subject* subject = (Subject*) malloc(sizeof(Subject));

    // initialise name
    *subject->name = *(char*) malloc(20 * sizeof(char));
    strcpy(subject->name, name);

    // initialise grade
    subject->mark = 0.0;
    subject->grade = 'N';

    // initialise estimations
    *subject->estimations = *(Estimation*) malloc(20 * sizeof(Estimation));
    
    int estimations_count = sizeof(*estimations) / sizeof(Estimation);
    for (int i = 0; i < estimations_count; i++) {
        subject->estimations[i] = *createEstimation(estimations[i].name, estimations[i].assessments);
    }

    // return the newly initialised subject
    return subject;
}

void freeSubject(Subject* subject) {
    free(subject->name);
}