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
    fprintf(summary, "Summary of totinfo Testing\n\n");
    
    system("python3 versionTesting.py");

    system("rm totinfo.c.gcov");
    system("rm totinfo.gcda");
    system("rm totinfo.gcno");

    printf("totinfo Testing executed successfully (Check totinfo/summary.txt for more details) \n");

    return 0;
}