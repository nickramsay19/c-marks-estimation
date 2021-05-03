#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Assessment.h"
#include "include/Subject.h"

void writeMaths(FILE *fptr) {
    Assessment maths_assessments[20];
    maths_assessments[0] = *createAssessment("Exam", 0.5, 0.43);
    maths_assessments[1] = *createAssessment("Asn1", 0.5, 0.2);
    printf("inter: %f\n", maths_assessments[0].value);

    Estimation maths_estimations[20];
    maths_estimations[0] = *createEstimation("Realistic", maths_assessments);
    printf("inter2: %f\n", maths_estimations[0].assessments[0].value);

    Subject* maths = createSubject("maths", maths_estimations);

    printf("[%s]\n", maths->estimations[0].name);
    printf("[%s]\n", maths->estimations[0].assessments[0].name);
    printf("[%f]\n", maths->estimations[0].assessments[0].weight);
    printf("[%f]\n", maths->estimations[0].assessments[0].value);

    if(fptr != NULL) {
        fwrite(maths, sizeof(Subject), sizeof(maths), fptr);
    }

    fclose(fptr);
}

Subject* getSubjectFromFile(FILE *fp) {

    //Subject* subject = createNullSubject();
    Subject* subject = (Subject*) malloc(sizeof(Subject));

    // get subject details
    fread(subject->name, sizeof(char), 20, fp);
    fread(&subject->mark, sizeof(float), 1, fp);
    fread(&subject->grade, sizeof(char), 1, fp);

    // move 3 chars across struct padding
    fseek(fp, 3, SEEK_CUR);

    // get estimations
    for (int i = 0; i < 20; i++) {
        fread(&subject->estimations[i].name, sizeof(char), 20, fp);

        // get assessment details for each assessment
        for (int j = 0; j < 20; j++) {
            fread(&subject->estimations[i].assessments[j], sizeof(Assessment), 1, fp);
        }
    }

    // return the subject
    return subject;
}

int main() {

    FILE* fp;
    const int writeMode = 0;
    if(writeMode) {
        fp = (FILE*) fopen("./dist/assessments.bin", "wb");
        writeMaths(fp);
        return 0;
    } else {
        fp = (FILE*) fopen("./dist/assessments.bin", "rb");
    }
    
    Subject* subject = getSubjectFromFile(fp);
    
    printf("Subject: %s\n", subject->name);
    printf("  Mark: %f, Grade: %c\n", subject->mark, subject->grade);
    printf("  Estimation: %s\n", subject->estimations[0].name);
    printf("  * Assessment 1: %s, %f, %f\n", subject->estimations[0].assessments[0].name, subject->estimations[0].assessments[0].weight, subject->estimations[0].assessments[0].value);
    printf("  * Assessment 2: %s, %f, %f\n", subject->estimations[0].assessments[1].name, subject->estimations[0].assessments[1].weight, subject->estimations[0].assessments[1].value);
    
    // free the subject
    freeSubject(subject);

    // close file
    fclose(fp);

    return 0;
}