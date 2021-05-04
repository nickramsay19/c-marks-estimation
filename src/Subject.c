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

Subject* createNullSubject() {

    char* name = "";
    Estimation* estimations;
    
    // return the newly allocated estimation
    return createSubject(name, estimations);
}

void freeSubject(Subject* subject) {

    // free the subject name
    free(subject->name);

    // free each estimate
    for (int i = 0; i < 20; i++) {
        freeEstimation(&subject->estimations[i]);
    }

    // finally free the subject
    //free(subject);
}

void printSubjectDetails(Subject subject) {
    printf("Subject: %s\n", subject.name);
    printf("  Mark: %f, Grade: %c\n", subject.mark, subject.grade);
    printf("  Estimation: %s\n", subject.estimations[0].name);
    printf("  * Assessment 1: %s, %f, %f\n", subject.estimations[0].assessments[0].name, subject.estimations[0].assessments[0].weight, subject.estimations[0].assessments[0].value);
    printf("  * Assessment 2: %s, %f, %f\n", subject.estimations[0].assessments[1].name, subject.estimations[0].assessments[1].weight, subject.estimations[0].assessments[1].value);
}