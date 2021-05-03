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

    // initialise estimations
    *subject->estimations = *estimations;


    // return the newly initialised subject
    return subject;
}

void freeSubject(Subject* subject) {
    free(subject->name);
}