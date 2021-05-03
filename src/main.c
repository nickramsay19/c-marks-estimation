#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Assessment.h"
#include "include/Subject.h"
#include "include/Grade.h"

void writeMaths(FILE *fptr) {
    Assessment* maths_exam = createAssessment("Exam", 1.0, 0.43);
    Assessment maths_assessments[] = {maths_exam};
    Estimation* maths_estimation = createEstimation("Realistic", maths_assessments);
    Subject* maths = createSubject("maths", maths_estimation);

    if(fptr != NULL) {
        fwrite(maths, sizeof(Subject), sizeof(maths), fptr);
    }
}

int main() {

    writeMaths(fptr);

    //FILE *fptr = fopen("./assessments.bin", "ab") // append mode
    FILE *fptr = fopen("./dist/assessments.bin", "wb");
    writeMaths(fptr);
    fclose(fptr);
    return 0;
    
    Subject* subject = (Subject*) malloc(sizeof(Subject));
    fread(&subject->name, sizeof(subject->name), 1, fptr);
    printf("%s\n", subject->name);

    // close file
    fclose(fptr);

    return 0;
}