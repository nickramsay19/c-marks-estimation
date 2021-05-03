#include "include/Subject.h"

Subject* createSubject(char* name, Assessment* assessments) {
    Subject* subject = (Subject*) malloc(sizeof(Subject));

    // initialise name
    *subject->name = malloc(20);
    strcpy(*subject->name, *name);

    // initialise assessments
    *subject->assessments = *assessments;

    // return the newly initialised subject
    return subject;
}