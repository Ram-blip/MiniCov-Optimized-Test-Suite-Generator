#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    system("gcc -o random randomGenerator.c");
    system("./random");

    system("gcc -o total totalGenerator.c");
    system("./total");

    system("python3 additionalGenerator.py");

    // Create a text file called summary.txt
    FILE *summary;
    summary = fopen("summary.txt", "w");
    fprintf(summary, "Summary of Replace Testing\n\n");
    
    system("python3 versionTesting.py");

    system("rm replace.c.gcov");
    system("rm replace.gcda");
    system("rm replace.gcno");

    printf("Replace Testing executed successfully (Check replace/summary.txt for more details) \n");

    return 0;
}