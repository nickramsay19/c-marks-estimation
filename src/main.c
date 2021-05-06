#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Assessment.h"
#include "include/Subject.h"
#include "include/SubjectsFile.h"

void getLine(char* str) {

    char c;
    int i = 0;

    while(1) { 
        c = getc(stdin);

        if (c == '\n') {
            str[i] = '\0';
            return;
        } else {
            str[i++] = c;
        }
    }
}

void clearStr(char* str, int length) {
    for (int i = 0; i < length; i++) {
        str[i] = '\0';
    }
}

Estimation* generateEstimation(char* name) {
    // declare some vars to store obtained assinment information
    char asn_inf[50], asn_name[30], asn_weight_str[10], asn_value_str[10];
    float asn_weight, asn_value;

    Assessment assessments[20];
    int current_assessment = 0;

    // store the part of the assignment we are reading i.e. name, weight or value
    int entry_part = 0;

    // loop until all assignment details provided
    while(1) {

        // TODO: clear vals
        // TODO: fix bug: this only clears the first letter
        // reset all strings
        clearStr(asn_inf, 50);
        clearStr(asn_name, 30);
        clearStr(asn_weight_str, 10);
        clearStr(asn_value_str, 10);

        // get the user info
        getLine(&asn_inf);


        // first check if they are finished (minimum entry is 5 chars long)
        if (strlen(asn_inf) < 5) {
            break;
        }
        // reset the entry part to the assignment name
        entry_part = 0;

        // loop through the chars in the line
        for(int i = 0; i < strlen(asn_inf); i++) {

            // ensure we don't write separators into the strings
            // check if we reached end of entry part and increment to move to the next part
            // TODO: check for multiple spaces
            if (asn_inf[i] == ' ') {
                i++;
                entry_part++;
            }


            // check what part we are reading
            if (entry_part == 0) {
                // we are still obtaining the assignment name
                asn_name[strlen(asn_name)] = asn_inf[i];
            } else if (entry_part == 1) {
                // we are obtaining the assignment name
                asn_weight_str[strlen(asn_weight_str)] = asn_inf[i];
            } else if (entry_part == 2) {
                // we are obtaining the assignment name
                asn_value_str[strlen(asn_value_str)] = asn_inf[i];
            } else {
                // we finished the line break the for loop
                break;
            }
        }

        // now convert asn_weight_str and asn_value_str to floats
        asn_weight = (float) atof(asn_weight_str);
        asn_value = (float) atof(asn_value_str);

        // check if values given as a percentage (above 1) and convert to decimal
        if (asn_weight > 1) asn_weight /= 100.0;
        if (asn_value > 1) asn_value /= 100.0;

        // now add the assignment details to assessment array
        assessments[current_assessment++] = *createAssessment(asn_name, asn_weight, asn_value);
        
    }

    // print added assessments
    printf("Adding the following assessments to estimation \"%s\".\n", name);
    for (int i = 0; i < current_assessment; i++) {
        printf("  * %s: %f, %f\n", assessments[i].name, assessments[i].weight, assessments[i].value);
    }

    // create and return the estimation
    return createEstimation(name, assessments);
}

int main(int argc, char** argv) {

    // read subjects into array of subjects
    SubjectsFile* subjectsFile = createSubjectsFile("/Users/nickramsay/Documents/Projects/c-marks-estimation/dist/subjects.bin");

    /*
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

                        // check if user identified an existing subject
                        if (!doesSubjectExistByName(subjectsFile, argv[3])) {

                            // begin create subject menu
                            printf("Creating a subject of name \"%s\".\n Now adding assignments to \"default\" estimation.\nPlease enter each assignment and its information separated by a newline, assignment information is of the format:\n\n\t<assignment name> <weight> <value>\n\nOnce you are done, enter an empty line to continue.\n", argv[3]);

                            Estimation estimations[20];
                            estimations[0] = *generateEstimation("default");
                            int current_estimation = 1;

                            char new_estimation_name[20];

                            // loop until no more estimations added
                            while(1) {

                                // obtain new estimation name
                                printf("Enter the name of the next estimation to be added; or enter nothing to finish.");
                                getLine(new_estimation_name);

                                // check if no estimation being added
                                if(strcmp(new_estimation_name, "") == 0) break;

                                // generate a new estimation, append to estimations, update counter
                                estimations[current_estimation++] = *generateEstimation(new_estimation_name);
                            }

                            

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