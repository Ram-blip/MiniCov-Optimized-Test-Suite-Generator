#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main() {
    
    FILE *fp;
    char line[1000];

    // Open the file for reading
    fp = fopen("universe.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    system("gcc -Wno-return-type -fprofile-arcs -ftest-coverage  -g -o tcas tcas.c");
    // Read and display each line
    int i = 0;

    float coverageArray[1590];
    int coverageIndex[1590];
    // Store the lines of the file in an array
    char *lines[1590];

    // Same for branch coverage
    float branchCoverageArray[1590];
    int branchCoverageIndex[1590];
    // Store the lines of the file in an array
    char *branchLines[1590];

    while (fgets(line, sizeof(line), fp) != NULL) {
        // Run tcas file using each of these test cases
        
        char string[1000] = "./tcas ";
        strcat(string, line);

        // Store line in array
        lines[i] = malloc(strlen(line) + 1);
        strcpy(lines[i], line);

        // Same for branch coverage
        branchLines[i] = malloc(strlen(line) + 1);
        strcpy(branchLines[i], line);

        system(string);
        // Print coverage for each test case
        system("gcov -b tcas.c > coverage.txt");

        FILE *file;
        char line[MAX_LINE_LENGTH];
        float coverage = 0.0;

        float branchCoverage = 0.0;

        // Open the coverage.txt file for reading
        file = fopen("coverage.txt", "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file\n");
            return 1;
        }

        // Read each line of the file
        
        while (fgets(line, sizeof(line), file)) {
            // Look for the line containing "Lines executed"
            if (strstr(line, "Lines executed")) {
                // Extract the coverage percentage value
                sscanf(line, "Lines executed:%f", &coverage);
                // break; // Break out of the loop once we find the percentage
            }

            // Branch coverage
            if (strstr(line, "Branches executed")) {
                // Extract the coverage percentage value
                sscanf(line, "Branches executed:%f", &branchCoverage);
                break; // Break out of the loop once we find the percentage
            }


        }
        // printf("Coverage: %.2f%%\n", coverage);
        coverageArray[i] = coverage;
        coverageIndex[i] = i;

        branchCoverageArray[i] = branchCoverage;
        branchCoverageIndex[i] = i;

        // Close the file



        fclose(file);

        // Delete the coverage files
        system("rm coverage.txt");
        system("rm tcas.gcda");
        system("rm tcas.c.gcov");

        
        i += 1;
    }
    fclose(fp);

    // Sort the coverage array in descending order
    for (int i = 0; i < 1590; i++) {
        for (int j = i + 1; j < 1590; j++) {
            if (coverageArray[i] < coverageArray[j]) {
                float temp = coverageArray[i];
                coverageArray[i] = coverageArray[j];
                coverageArray[j] = temp;

                int tempIndex = coverageIndex[i];
                coverageIndex[i] = coverageIndex[j];
                coverageIndex[j] = tempIndex;

                // Swap the lines in the array
                char *tempLine = lines[i];
                lines[i] = lines[j];
                lines[j] = tempLine;

            }
        }
    }

    // Sort the branch coverage array in descending order
    for (int i = 0; i < 1590; i++) {
        for (int j = i + 1; j < 1590; j++) {
            if (branchCoverageArray[i] < branchCoverageArray[j]) {
                float temp = branchCoverageArray[i];
                branchCoverageArray[i] = branchCoverageArray[j];
                branchCoverageArray[j] = temp;

                int tempIndex = branchCoverageIndex[i];
                branchCoverageIndex[i] = branchCoverageIndex[j];
                branchCoverageIndex[j] = tempIndex;

                // Swap the lines in the array
                char *tempLine = branchLines[i];
                branchLines[i] = branchLines[j];
                branchLines[j] = tempLine;

            }
        }
    }


    printf("Top 10 test cases: \n");
    for (int i = 0; i < 10; i++) {
        printf("Test case %d: %.2f%%\n", coverageIndex[i], coverageArray[i]);
    }

    printf("Bottom 10 test cases: \n");
    for (int i = 1580; i < 1590; i++) {
        printf("Test case %d: %.2f%%\n", coverageIndex[i], coverageArray[i]);
    }

    printf("Top 10 branch test cases: \n");
    for (int i = 0; i < 10; i++) {
        printf("Test case %d: %.2f%%\n", branchCoverageIndex[i], branchCoverageArray[i]);
    }

    printf("Bottom 10 branch test cases: \n");
    for (int i = 1580; i < 1590; i++) {
        printf("Test case %d: %.2f%%\n", branchCoverageIndex[i], branchCoverageArray[i]);
    }


    // Create a new text file to store the sorted test cases with data
    FILE *sortedFile;
    sortedFile = fopen("totalPrioritization.txt", "w");
    if (sortedFile == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    for (int i = 0; i < 1590; i++) {
        fprintf(sortedFile, "%s", lines[i]);
    }

    fclose(sortedFile);

    // Create a new text file to store the sorted test cases with data for branch coverage
    FILE *branchSortedFile;
    branchSortedFile = fopen("branchTotalPrioritization.txt", "w");
    if (branchSortedFile == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    for (int i = 0; i < 1590; i++) {
        fprintf(branchSortedFile, "%s", branchLines[i]);
    }

    fclose(branchSortedFile);


    // Create a new file totalP.txt that stores only the test cases that causes change in statement coverage
    FILE *totalP;
    totalP = fopen("totalP.txt", "w");
    if (totalP == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    FILE *branchTotalP;
    branchTotalP = fopen("branchTotalP.txt", "w");
    if (branchTotalP == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }


    // Getting only the required test cases which have 98.46% statement coverage and no repeated coverage.
    FILE *totalPrioritization;
    char testcase[1000];
    totalPrioritization = fopen("totalPrioritization.txt", "r");
    if (totalPrioritization == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    system("gcc -Wno-return-type -fprofile-arcs -ftest-coverage  -g -o tcas tcas.c");

    // Delete the system gcda files
    

    i = 0;
    float prevStatementCoverage = 0.0;
    int foundStatementCoverage = 0;

    while (fgets(testcase, sizeof(testcase), totalPrioritization) != NULL && !foundStatementCoverage) {
        // Run tcas file using each of these test cases
        char string[1000] = "./tcas ";
        strcat(string, testcase);
        system(string);
        // Print coverage for each test case
        system("gcov -b tcas.c > coverage.txt");
        FILE *file;
        char line[MAX_LINE_LENGTH]; // Coverage line
        float coverage = 0.0;

        // Open the coverage.txt file for reading
        file = fopen("coverage.txt", "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file\n");
            return 1;
        }

        // Read each line of the file
        
        while (fgets(line, sizeof(line), file)) {
            // Look for the line containing "Lines executed"
            if (strstr(line, "Lines executed")) {
                // Extract the coverage percentage value
                sscanf(line, "Lines executed:%f", &coverage);
                if(i == 0){
                    fprintf(totalP, "%s", testcase);
                    prevStatementCoverage = coverage;
                }
                else{
                    if (coverage != prevStatementCoverage){
                        fprintf(totalP, "%s", testcase);
                        prevStatementCoverage = coverage;
                    }
                }
                if(coverage >= 98.45){
                    foundStatementCoverage = 1;
                    break;
                }
            }
        }
        i = 1;
    }

    system("rm tcas.gcda");
    system("rm tcas.c.gcov");
    system("rm coverage.txt");

    // Do the same for branch coverage
    FILE *branchTotalPrioritization;
    char branchTestcase[1000];
    branchTotalPrioritization = fopen("branchTotalPrioritization.txt", "r");
    if (branchTotalPrioritization == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    i = 0;
    float prevBranchCoverage = 0.0;
    int foundBranchCoverage = 0;

    while (fgets(branchTestcase, sizeof(branchTestcase), branchTotalPrioritization) != NULL && !foundBranchCoverage) {
        // Run tcas file using each of these test cases
        char string[1000] = "./tcas ";
        strcat(string, branchTestcase);
        system(string);
        // Print coverage for each test case
        system("gcov -b tcas.c > coverage.txt");
        FILE *file;
        char line[MAX_LINE_LENGTH]; // Coverage line
        float branchCoverage = 0.0;

        // Open the coverage.txt file for reading
        file = fopen("coverage.txt", "r");
        if (file == NULL) {
            fprintf(stderr, "Error opening file\n");
            return 1;
        }

        // Read each line of the file
        
        while (fgets(line, sizeof(line), file)) {
            // Look for the line containing "Branches executed"
            if (strstr(line, "Branches executed")) {
                // Extract the coverage percentage value
                sscanf(line, "Branches executed:%f", &branchCoverage);
                if(i == 0){
                    fprintf(branchTotalP, "%s", branchTestcase);
                    prevBranchCoverage = branchCoverage;
                }
                else{
                    if (branchCoverage != prevBranchCoverage){
                        fprintf(branchTotalP, "%s", branchTestcase);
                        prevBranchCoverage = branchCoverage;
                    }
                }
                if(branchCoverage >= 100.0){
                    foundBranchCoverage = 1;
                    break;
                }
            }
        }
        i = 1;
    }


    return 0;
    }

