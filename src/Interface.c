#include <stdio.h>
#include <string.h>

#include "include/Interface.h"
#include "include/Estimation.h"
#include "include/Assessment.h"

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
