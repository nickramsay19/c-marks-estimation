#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Assessment.h"
#include "include/Subject.h"

void writeMaths(FILE *fptr) {
    Assessment maths_assessments[20];
    maths_assessments[0] = *createAssessment("Exam", 1.0, 0.43);
    Estimation maths_estimations[20];
    maths_estimations[0] = *createEstimation("Realistic", maths_assessments);
    Subject* maths = createSubject("maths", maths_estimations);

    printf("[%s]\n", maths->estimations[0].name);

    if(fptr != NULL) {
        fwrite(maths, sizeof(Subject), sizeof(maths), fptr);
    }

    fclose(fptr);
}

int main() {

    //FILE *fptr = fopen("./assessments.bin", "ab") // append mode
    FILE* fptr = (FILE*) fopen("./dist/assessments.bin", "rb");

    //FILE* fptr = (FILE*) fopen("./dist/assessments.bin", "wb");
    //writeMaths(fptr);
    //return 0;
    
    Subject* subject = (Subject*) malloc(sizeof(Subject));
    fread(&subject->name, 20 * sizeof(char), 1, fptr);

    printf("1.\n");

    // read estimations
    fread(&subject->estimations, 20 * sizeof(Estimation), 1, fptr);

    printf("2.\n");

    int estimations_count = sizeof(subject->estimations) / sizeof(Estimation);
    printf("Estimations count: %d\n", estimations_count);
    for (int i = 0; i < estimations_count; i++) {
        
        // estimation name
        fread(&subject->estimations[i].name, 20 * sizeof(char), 1, fptr);
        //printf("%s\n", subject->estimations[i].name);

        // estimation assessments
        fread(&subject->estimations[i], 20 * sizeof(Estimation), 1, fptr);

        int assessments_count = sizeof(subject->estimations[i].assessments) / sizeof(Assessment);
        //printf("Assessments count: %d\n", assessments_count);
        for (int j = 0; j < assessments_count; j++) {

            // assessment name
            fread(&subject->estimations[i].assessments[j].name, sizeof(subject->estimations[i].assessments[j].name), 1, fptr);

            //fread(&subject->estimations[i].assessments[j], sizeof(subject->estimations[i].assessments[j]))
        }
    }



    printf("%s\n", subject->name);
    printf("(%s)\n", subject->estimations[0].name);
    printf("(%s)\n", subject->estimations[0].assessments[0].name);

    // close file
    fclose(fptr);

    return 0;
}