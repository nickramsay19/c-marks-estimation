#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Assessment.h"
#include "include/Subject.h"
#include "include/SubjectsFile.h"

int main(int argc, char** argv) {

    // read subjects into array of subjects
    SubjectsFile* subjectsFile = createSubjectsFile("/Users/nickramsay/Documents/Projects/c-marks-estimation/dist/subjects.bin");

    /*
    // write some hardcoded subjects
    _writeExamplesToFile(subjectsFile);

    // add another hardcoded subject
    Assessment spanish_assessments[20];
    spanish_assessments[0] = *createAssessment("Exam", 0.7, 0.81);
    spanish_assessments[1] = *createAssessment("Asn1", 0.3, 0.99);

    Estimation spanish_estimations[20];
    spanish_estimations[0] = *createEstimation("default", spanish_assessments);

    Subject* spanish = createSubject("spanish2", spanish_estimations);
    addSubject(subjectsFile, *spanish);

    _writeSubjectsToFile(subjectsFile);
    */

    //removeSubjectByName(subjectsFile, "spanish2");
    //_writeSubjectsToFile(subjectsFile);

    // handle command line args
    // handle help dialog
    // check that an arg has been passed
    if (argc > 1) {
        if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0) {
            printf("Help menu.\n");

        // handle subject menu
        } else if (strcmp(argv[1], "subject") == 0 || strcmp(argv[1], "s") == 0) {

            // check that there are more than 3 args
            if (argc > 2) {
                // handle subject addition
                if (strcmp(argv[2], "add") == 0) {
                    if (argc > 3) {
                        if (!doesSubjectExistByName(subjectsFile, argv[3])) {
                            // add subject
                            // get name
                            // get -a for assessment -a <name> <weight> <value|empty>
                        } else {
                            printf("Error: A subject already exists with name \"%s\".\n", argv[3]);
                        }
                    } else {
                        printf("Please provide a new subject to be added.\n");
                    }

                // handle subject removal
                } else if (strcmp(argv[2], "rm") == 0) {
                    printf("rm\n");

                // handle list subjects
                } else if (strcmp(argv[2], "list") == 0) {
                    printf("listing all subjects\n");
                    
                    // print subject details
                    printSubjectsNames(subjectsFile);

                // handle subject selection
                } else {
                    
                    // check if arg[2] is a subject
                    Subject* s = getSubjectByName(subjectsFile, argv[2]);

                    if (strcmp(s->name, "") == 0) {
                        printf("No subject of name \"%s\"\n", argv[2]);
                    } else {
                        printSubjectDetails(*s);
                    }

                }
            }
        // handle unknown command
        } else {
            printf("Unknown command.\n");
        }

    // no arguments passed
    } else {
        printf("Please provide some arguments. Type \"help\" to see the available commands.\n");
    }
    

    // free the subjects file
    freeSubjectsFile(subjectsFile);

    return 0;
}