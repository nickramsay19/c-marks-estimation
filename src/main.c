#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/Assessment.h"
#include "include/Subject.h"

void writeExample(FILE *fp) {

    // math
    Assessment maths_assessments[20];
    maths_assessments[0] = *createAssessment("Exam", 0.5, 0.43);
    maths_assessments[1] = *createAssessment("Asn1", 0.5, 0.2);

    Estimation maths_estimations[20];
    maths_estimations[0] = *createEstimation("Realistic", maths_assessments);

    Subject* maths = createSubject("maths", maths_estimations);

    // english
    Assessment english_assessments[20];
    english_assessments[0] = *createAssessment("Exam", 0.5, 0.43);
    english_assessments[1] = *createAssessment("Asn1", 0.5, 0.2);

    Estimation english_estimations[20];
    english_estimations[0] = *createEstimation("Realistic", english_assessments);

    Subject* english = createSubject("english", english_estimations);

    // french
    Assessment french_assessments[20];
    french_assessments[0] = *createAssessment("Exam", 0.5, 0.43);
    french_assessments[1] = *createAssessment("Asn1", 0.5, 0.2);

    Estimation french_estimations[20];
    french_estimations[0] = *createEstimation("Realistic", french_assessments);

    Subject* french = createSubject("french", french_estimations);

    // subjects arr
    Subject* subjects = (Subject*) malloc(2 * sizeof(Subject));
    subjects[0] = *english;
    subjects[1] = *maths;
    subjects[2] = *french;

    if(fp != NULL) {
        fwrite(english, 1 * sizeof(Subject), sizeof(english), fp);
        fwrite(maths, 1 * sizeof(Subject), sizeof(maths), fp);
        fwrite(french, 1 * sizeof(Subject), sizeof(french), fp);
    } else {
        printf("Error writing to file\n");
    }

    printf("%s\n", english->name);
}

Subject* getSubjectFromFile(FILE *fp) {

    printf("(0)");
    //Subject* subject = createNullSubject();
    Subject* subject;

    printf("(1)");
    if(fp) {
        subject = (Subject*) malloc(sizeof(Subject));

        // get subject details
        printf("(2)");
        fread(subject->name, sizeof(char), 20, fp);
        fread(&subject->mark, sizeof(float), 1, fp);
        fread(&subject->grade, sizeof(char), 1, fp);
        printf("(3)");

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
    } else {
        return NULL;
    }

    // return the subject
    return subject;
}

int main(int argc, char** argv) {

    FILE* fp = (FILE*) fopen("./dist/subjects.bin", "wb");
    writeExample(fp);
    fclose(fp);

    fp = (FILE*) fopen("./dist/subjects.bin", "rb");

    Subject subjects[40]; //= (Subject*) malloc(40 * sizeof(Subject));

    for (int i = 0; i < 10; i++) { // change to i < 40
        
        subjects[i] = *getSubjectFromFile(fp);

        printf("(");
        printf("%p, %s", &(subjects[i]), subjects[i].name);
        printf(")");

        if (&(subjects[i]) == NULL) break;
        printf(".");

        fseek(fp, 7 * 11628, SEEK_CUR);
        
        printf("%d\n", i);
    }

    printf("%lu\n", sizeof(Subject));
    // close file
    fclose(fp);

    printf("Subject: %s\n", subjects[0].name);
    printf("  Mark: %f, Grade: %c\n", subjects[0].mark, subjects[0].grade);
    printf("  Estimation: %s\n", subjects[0].estimations[0].name);
    printf("  * Assessment 1: %s, %f, %f\n", subjects[0].estimations[0].assessments[0].name, subjects[0].estimations[0].assessments[0].weight, subjects[0].estimations[0].assessments[0].value);
    printf("  * Assessment 2: %s, %f, %f\n", subjects[0].estimations[0].assessments[1].name, subjects[0].estimations[0].assessments[1].weight, subjects[0].estimations[0].assessments[1].value);
    
    printf("Subject: %s\n", subjects[8].name);
    printf("  Mark: %f, Grade: %c\n", subjects[1].mark, subjects[1].grade);
    printf("  Estimation: %s\n", subjects[1].estimations[0].name);
    printf("  * Assessment 1: %s, %f, %f\n", subjects[1].estimations[0].assessments[0].name, subjects[1].estimations[0].assessments[0].weight, subjects[1].estimations[0].assessments[0].value);
    printf("  * Assessment 2: %s, %f, %f\n", subjects[1].estimations[0].assessments[1].name, subjects[1].estimations[0].assessments[1].weight, subjects[1].estimations[0].assessments[1].value);
    

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
        }

    // handle unknown command
    } else {
        printf("Unknown command.\n");
    }

    return 0;

    // handle file read/write
    const int writeMode = 0;
    if(writeMode) {
        fp = (FILE*) fopen("./dist/subjects.bin", "wb");
        //writeMaths(fp);
        return 0;
    } else {
        fp = (FILE*) fopen("./dist/subjects.bin", "rb");
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