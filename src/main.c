#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Assessment.h"
#include "include/Subject.h"
#include "include/SubjectsFile.h"

int main(int argc, char** argv) {

    printf("%d\n", 0.000 == 0);

    // read subjects into array of subjects
    SubjectsFile* subjectsFile = createSubjectsFile("./dist/subjects.bin");

    // write some hardcoded subjects
    _writeExamplesToFile(subjectsFile);

    // add another hardcoded subject
    Assessment spanish_assessments[20];
    spanish_assessments[0] = *createAssessment("Exam", 0.7, 0.81);
    spanish_assessments[1] = *createAssessment("Asn1", 0.3, 0.99);

    Estimation spanish_estimations[20];
    spanish_estimations[0] = *createEstimation("default", spanish_assessments);

    Subject* spanish = createSubject("spanish", spanish_estimations);
    addSubject(subjectsFile, *spanish);

    // print subject details
    printSubjectDetails(subjectsFile->subjects[0]);
    printSubjectDetails(subjectsFile->subjects[1]);
    printSubjectDetails(subjectsFile->subjects[2]);
    printSubjectDetails(subjectsFile->subjects[3]);

    // handle command line args
    // handle help dialog
    if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0) {
        printf("Help menu.\n");

    // handle subject menu
    } else if (strcmp(argv[1], "subject") == 0 || strcmp(argv[1], "s") == 0) {
        printf("Subject menu.\n");

        // handle subject addition
        if (strcmp(argv[2], "add") == 0) {
            printf("add\n");

        // handle subject removal
        } else if (strcmp(argv[2], "rm") == 0) {
            printf("rm\n");

        // handle list subjects
        } else if (strcmp(argv[2], "list") == 0) {
            printf("listing all subjects\n");

        // handle subject selection
        } else {
            printf("subject selection\n");

        }

    // handle unknown command
    } else {
        printf("Unknown command.\n");
    }

    // free the subjects file
    freeSubjectsFile(subjectsFile);

    return 0;
}