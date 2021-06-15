#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Assessment.h"
#include "include/Subject.h"
#include "include/SubjectsFile.h"
#include "include/Interface.h"
#include "include/ArgumentParser.h"

int main(int argc, char** argv) {

    // read subjects into array of subjects
    SubjectsFile* subjectsFile = createSubjectsFile("/Users/nickramsay/Documents/Projects/c-marks-estimation/dist/subjects.bin");

    // use argp
    

    // free the subjects file
    freeSubjectsFile(subjectsFile);

    return 0;
}