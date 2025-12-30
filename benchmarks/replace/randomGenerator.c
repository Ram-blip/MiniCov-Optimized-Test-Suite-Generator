#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINES 5542
#define MAX_LENGTH 700
#define MAX_LINE_LENGTH 700

// Function to swap two strings
void swap(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// Function to shuffle an array of strings
void shuffle(char *lines[], int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&lines[i], &lines[j]);
    }
}

int main() {
    char *lines[MAX_LINES];
    char line[MAX_LENGTH];
    int num_lines = 0;

    // Open input file for reading
    FILE *input_file = fopen("universe.txt", "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    // Read lines from input file into an array
    while (fgets(line, sizeof(line), input_file) && num_lines < MAX_LINES) {
        lines[num_lines] = strdup(line);
        if (lines[num_lines] == NULL) {
            perror("Memory allocation failed");
            return EXIT_FAILURE;
        }
        num_lines++;
    }

    // Close input file
    fclose(input_file);

    // Shuffle the array of lines
    shuffle(lines, num_lines);

    // Open output file for writing
    FILE *output_file = fopen("randomPrioritization.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        return EXIT_FAILURE;
    }

    // Write shuffled lines to output file
    for (int i = 0; i < num_lines; i++) {
        fputs(lines[i], output_file);
        free(lines[i]); // Free memory allocated by strdup
    }

    // Close output file
    fclose(output_file);


    // Create a new file randomP.txt that stores only the test cases that causes change in statement coverage
    FILE *randomP;
    randomP = fopen("randomP.txt", "w");
    if (randomP == NULL) {
        fprintf(stderr, "Error opening file randomP\n");
        return 1;
    }

    FILE *branchRandomP;
    branchRandomP = fopen("branchRandomP.txt", "w");
    if (branchRandomP == NULL) {
        fprintf(stderr, "Error opening file branchRandomP\n");
        return 1;
    }


    // Getting only the required test cases which have 98.46% statement coverage and no repeated coverage.
    FILE *randomPrioritization;
    char testcase[1000];
    randomPrioritization = fopen("randomPrioritization.txt", "r");
    if (randomPrioritization == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    system("gcc -Wno-return-type -fprofile-arcs -ftest-coverage  -g -o replace replace.c -lm");
    system("clear");

    int i = 0;
    float prevStatementCoverage = 0.0;
    float prevBranchCoverage = 0.0;
    int foundStatementCoverage = 0;
    int foundBranchCoverage = 0;

    while (fgets(testcase, sizeof(testcase), randomPrioritization) != NULL && (!foundStatementCoverage || !foundBranchCoverage)) {
        // Run replace file using each of these test cases
        char string[1000] = "./replace ";
        strcat(string, testcase);
        system(string);
        // Print coverage for each test case
        system("gcov -b replace.c > coverage.txt");
        FILE *file;
        char line[MAX_LINE_LENGTH]; // Coverage line
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
            if (strstr(line, "Lines executed") && !foundStatementCoverage) {
                // Extract the coverage percentage value
                sscanf(line, "Lines executed:%f", &coverage);
                if(i == 0){
                    fprintf(randomP, "%s", testcase);
                    prevStatementCoverage = coverage;
                }
                else{
                    if (coverage != prevStatementCoverage){
                        fprintf(randomP, "%s", testcase);
                        prevStatementCoverage = coverage;
                    }
                }
                if(coverage >= 95.28){
                    foundStatementCoverage = 1;
                }

            }   


            if (strstr(line, "Branches executed") && !foundBranchCoverage) {
                // Extract the coverage percentage value

                sscanf(line, "Branches executed:%f", &branchCoverage);
                if(i == 0){

                    fprintf(branchRandomP, "%s", testcase);
                    prevBranchCoverage = branchCoverage;
                }
                else{
                    if (branchCoverage != prevBranchCoverage){
                        fprintf(branchRandomP, "%s", testcase);
                        prevBranchCoverage = branchCoverage;
                    }

                }

                if(branchCoverage >= 100.0){
                    foundBranchCoverage = 1;
                }
            }
        }

        i = 1;
    }

    fclose(randomP);
    // fclose(branchRandomP);

    fclose(randomPrioritization);

    // Delete Random Prioritization file and coverage files
    // system("rm randomPrioritization.txt");
    system("rm coverage.txt");
    system("rm replace.gcda");
    system("rm replace.c.gcov");

    return EXIT_SUCCESS;
}