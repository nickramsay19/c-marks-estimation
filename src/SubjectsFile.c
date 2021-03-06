#include <stdio.h>
#include <stdlib.h>

#include "include/SubjectsFile.h"
#include "include/Subject.h"

SubjectsFile* createSubjectsFile(char* name) {

    // allocate memory for subjects file
    SubjectsFile* subjectsFile = (SubjectsFile*) malloc(sizeof(SubjectsFile));

    // allocate memory and assign file name
    subjectsFile->name = (char*) malloc(20 * sizeof(char));
    strcpy(subjectsFile->name, name);

    // allocate memory for FILE
    //subjectsFile->fp = (FILE*) malloc(sizeof(FILE));

    // allocate memory for subjects array
    subjectsFile->subjects = (Subject*) malloc(10 * sizeof(Subject));

    // get array of subjects
    subjectsFile->subjects = getSubjectsArray(subjectsFile);

    // finally, return newly allocated subjectsFile
    return subjectsFile;
}

void freeSubjectsFile(SubjectsFile* subjectsFile) {

    // free the subjectsFile's name
    free(subjectsFile->name);

    // free each subjectsFile subject
    //for (int i = 0; i < 10; i++) {
        //freeSubject(&(subjectsFile->subjects[i]));
    //}

    // free the subjectsFile's subjects array
    //free(subjectsFile->subjects);

    // finally free the subjectsFile
    free(subjectsFile);
    
}

Subject* getSubjectsArray(SubjectsFile* subjectsFile){

    // open the file
    subjectsFile->fp = (FILE*) fopen(subjectsFile->name, "rb");
    Subject subjects[10];

    // loop through maximum ten subjects in file, or NULL subject returned
    for (int i = 0; i < 10; i++) {

        // read the next subject
        subjects[i] = *_getSubjectFromFile(subjectsFile);

        // check if we recieve a null pointer, i.e. no more space to read
        if (&(subjects[i]) == NULL) break;

        // we will need to fseek across the padding when structs have been individually written
        //fseek(subjectsFile->fp, 7 * 11628, SEEK_CUR);
    }

    // close file
    fclose(subjectsFile->fp);

    // return the subjects array
    return subjects;
}

Subject* _getSubjectFromFile(SubjectsFile* subjectsFile) {

    //Subject* subject = createNullSubject();
    Subject* subject;

    if(subjectsFile->fp) {
        subject = (Subject*) malloc(sizeof(Subject));

        // get subject details
        fread(subject->name, sizeof(char), 20, subjectsFile->fp);

        // get estimations
        for (int i = 0; i < 20; i++) {

            // read he estimation details
            fread(&subject->estimations[i].name, sizeof(char), 20, subjectsFile->fp); // estimation name
            fread(&subject->estimations[i].mark, sizeof(float), 1, subjectsFile->fp); // estimation mark
            fread(&subject->estimations[i].grade, sizeof(char), 1, subjectsFile->fp); // estimation grade

            // move 3 chars across struct padding
            fseek(subjectsFile->fp, 3, SEEK_CUR);

            // get assessment details for each assessment
            for (int j = 0; j < 20; j++) {
                fread(&subject->estimations[i].assessments[j], sizeof(Assessment), 1, subjectsFile->fp);
            }
        }
    } else {
        return NULL;
    }

    // return the subject
    return subject;
}

Subject* getSubjectByName(SubjectsFile* subjectsFile, char* name) {

    // for some reason this print fixes the illegal hardware instruction error
    printf("");

    // loop through subjects until subject found
    for (int i = 0; i < 10; i++) {

        // check if subject i has name as name
        if (strcmp(subjectsFile->subjects[i].name, name) == 0) {
            
            // return the found subject
            return &subjectsFile->subjects[i];
        }
    }

    // return failure value
    return createNullSubject();
}

int doesSubjectExistByName(SubjectsFile* subjectsFile, char* name) {

    // loop through subjects until subject found
    for (int i = 0; i < 10; i++) {

        // check if subject i has name as name
        if (strcmp(subjectsFile->subjects[i].name, name) == 0) {
            
            // we found the subject, return success code
            return 1;
        }
    }

    // return failure value
    return 0;
}

int addSubject(SubjectsFile* subjectsFile, Subject subject) {

    // loop through subjects until a space is found
    for (int i = 0; i < 10; i++) {

        // check if subject i has no name
        // TODO: we wont find subjects with bugged names
        if (strcmp(subjectsFile->subjects[i].name, "") == 0) {
            
            // add the subject
            subjectsFile->subjects[i] = subject;

            // we found a space for the subject, return success code
            return 1;
        }
    }

    // return failure value
    return 0;
}

int removeSubject(SubjectsFile* subjectsFile, Subject subject) {

    // loop through subjects until subject found
    for (int i = 0; i < 10; i++) {

        // check if subject i has the same name as subject
        // TODO: we wont find subjects with bugged names
        if (strcmp(subjectsFile->subjects[i].name, subject.name) == 0) {
            
            // add the subject
            subjectsFile->subjects[i] = *createNullSubject();

            // we found the subject, return success code
            return 1;
        }
    }

    // return failure value
    return 0;
}

int removeSubjectByName(SubjectsFile* subjectsFile, char* name) {

    // loop through subjects until subject found
    for (int i = 0; i < 10; i++) {

        // check if subject i has name as name
        if (strcmp(subjectsFile->subjects[i].name, name) == 0) {
            
            // add the subject
            subjectsFile->subjects[i] = *createNullSubject();

            // we found the subject, return success code
            return 1;
        }
    }

    // return failure value
    return 0;
}

void printSubjectsDetails(SubjectsFile* subjectsFile) {

    // loop through subjects
    for (int i = 0; i < 10; i++) {

        // check if subject i has a name
        // TODO: we wont find subjects with bugged names
        if (strcmp(subjectsFile->subjects[i].name, "") != 0) {
            
            // print the subject details
            printSubjectDetails(subjectsFile->subjects[i]);

        }
    }
}

void printSubjectsNames(SubjectsFile* subjectsFile) {

    // loop through subject marks
    for (int i = 0; i < 10; i++) {

        // check if subject i has a name
        // TODO: we wont find subjects with bugged names
        if (strcmp(subjectsFile->subjects[i].name, "") != 0) {
            
            // print the subject details
            //printSubjectDetails(subjectsFile->subjects[i]);
            printf("* %s\n", subjectsFile->subjects[i].name);
        }
    }
}

int _writeSubjectsToFile(SubjectsFile* subjectsFile) {

    // open file in write mode
    subjectsFile->fp = (FILE*) fopen(subjectsFile->name, "wb");
    
    // check that file has been opened successfully
    if(subjectsFile->fp != NULL) {

        // loop through all subjects individually
        for (int i = 0; i < sizeof(*subjectsFile->subjects) / sizeof(Subject); i++) {

            // write each subject
            fwrite(&subjectsFile->subjects[i], sizeof(Subject), sizeof(&subjectsFile->subjects[i]), subjectsFile->fp);
        }

        // close the file
        fclose(subjectsFile->fp);

        // return success code
        return 1;
    } else {

        // close the file
        fclose(subjectsFile->fp);

        // return error code
        return 0;
    }

    
}

void _writeExamplesToFile(SubjectsFile* subjectsFile) {

    // math
    Assessment maths_assessments[20];
    maths_assessments[0] = *createAssessment("Exam", 0.7, 0.2);
    maths_assessments[1] = *createAssessment("Asn1", 0.3, 0.31);

    Estimation maths_estimations[20];
    maths_estimations[0] = *createEstimation("default", maths_assessments);

    Subject* maths = createSubject("maths", maths_estimations);

    // english
    Assessment english_assessments[20];
    english_assessments[0] = *createAssessment("Asn1", 0.33, 0.43);
    english_assessments[1] = *createAssessment("Asn2", 0.33, 0.2);
    english_assessments[3] = *createAssessment("Asn3", 0.34, 0.1);

    Estimation english_estimations[20];
    english_estimations[0] = *createEstimation("default", english_assessments);

    Subject* english = createSubject("english", english_estimations);

    // french
    Assessment french_assessments[20];
    french_assessments[0] = *createAssessment("Exam", 0.5, 0.43);
    french_assessments[1] = *createAssessment("Asn1", 0.5, 0.2);

    Assessment french_assessments2[20];
    french_assessments2[0] = *createAssessment("Exam", 0.5, 0.50);
    french_assessments2[1] = *createAssessment("Asn1", 0.5, 0.30);

    Estimation french_estimations[20];
    french_estimations[0] = *createEstimation("default", french_assessments);
    french_estimations[1] = *createEstimation("optimistic", french_assessments2);

    Subject* french = createSubject("french", french_estimations);

    // subjects arr
    Subject* subjects = (Subject*) malloc(2 * sizeof(Subject));
    subjects[0] = *english;
    subjects[1] = *maths;
    subjects[2] = *french;

    subjectsFile->fp = (FILE*) fopen(subjectsFile->name, "wb");
    
    if(subjectsFile->fp != NULL) {
        for (int i = 0; i < sizeof(*subjects) / sizeof(Subject); i++) {
            fwrite(&subjects[i], sizeof(Subject), sizeof(&subjects[i]), subjectsFile->fp);
        }
    } else {
        printf("Error writing to file\n");
    }

    // close the file
    fclose(subjectsFile->fp);
}