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

    // print subject details
    printf("Subject: %s\n", subject.name);
    printf("  Mark: %f, Grade: %c\n", subject.mark, subject.grade);

    // print each estimation details
    for (int i = 0; i < 20; i++) {

        // check if the estimation is valid (has a name)
        if(strcmp(subject.estimations[i].name, "") != 0) {

            // print the name of the estimation
            printf("  Estimation: %s\n", subject.estimations[i].name);

            // print each assessment in estimation
            for (int j = 0; j < 20; j++) {

                // check if the subject is valid (has a name, positive non-zero mark and weight)
                if(strcmp(subject.estimations[i].assessments[j].name, "") != 0 && subject.estimations[i].assessments[j].weight > 0.001 && subject.estimations[i].assessments[j].value > 0.001) {

                    // print assessment name and details
                    printf("  * %s: %f, %f\n", subject.estimations[i].assessments[j].name, subject.estimations[i].assessments[j].weight, subject.estimations[i].assessments[j].value);
                } else {
                    //break; // assessments could exist later if an assessment has been removed at (i,j) previously
                }
            }
        } else {
            //break; // estimations could exist later if an estimation has been removed at i previously
        }
    }
}