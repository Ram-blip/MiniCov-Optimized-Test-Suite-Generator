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
    fprintf(summary, "Summary of schedule Testing\n\n");
    
    system("python3 versionTesting.py");

    system("rm schedule.c.gcov");
    system("rm schedule.gcda");
    system("rm schedule.gcno");

    printf("schedule Testing executed successfully (Check schedule/summary.txt for more details) \n");

    return 0;
}