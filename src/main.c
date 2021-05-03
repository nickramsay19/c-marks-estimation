#include <stdio.h>
#include <string.h>

#include "include/Assessment.h"
#include "include/Subject.h"
#include "include/Grade.h"

int main() {
    printf("hey\n");

    // overwritten
    FILE *fptr = fopen("./assessments.bin", "wb");
    // FILE *fptr = fopen("./assessments.bin", "ab") // append mode

    Subject* math;
    Assessment* exam;
    printf("1\n");
    strcpy(exam->name, "exam");
    printf("2\n");
    exam->weight = (float) 1.0;
    exam->value = (float) 0.51;
    printf("3\n");

    math->assessments[0] = *exam;
    math->mark = 0;
    math->grade = F;


    if(fptr != NULL) {
        //fwrite(math)
    }

    // close file
    fclose(fptr);

    return 0;
}