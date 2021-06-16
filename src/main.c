#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/argp/argp.h"

#include "include/Assessment.h"
#include "include/Subject.h"
#include "include/SubjectsFile.h"
#include "include/Interface.h"
#include "include/ArgumentParser.h"

int main(int argc, char** argv) {

    //read subjects into array of subjects
    SubjectsFile* subjectsFile = createSubjectsFile("/Users/nickramsay/Documents/Projects/c-marks-estimation/dist/subjects.bin");

    // use argp
    struct arguments arguments;

    //Default values.
    arguments.silent = 0;
    arguments.verbose = 0;
    arguments.output_file = "-";

    //Parse our arguments; every option seen by parse_opt will
    //be reflected in arguments.
    argp_parse(&Argp, argc, argv, 0, 0, &arguments);

    printf("ARG1 = %s\nARG2 = %s\nOUTPUT_FILE = %s\n"
            "VERBOSE = %s\nSILENT = %s\n",
            arguments.args[0], arguments.args[1],
            arguments.output_file,
            arguments.verbose ? "yes" : "no",
            arguments.silent ? "yes" : "no");

    //free the subjects file
    freeSubjectsFile(subjectsFile);

    return 0;
}