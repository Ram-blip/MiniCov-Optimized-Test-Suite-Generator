#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    
    // Check time of file executions in seconds
    clock_t start, end;
    double cpu_time_used;
    start = clock();


    // Run all relevant tcas files
    system("cd benchmarks/tcas && gcc -o tcasScript tcasScript.c && ./tcasScript && cd ../.. && clear");


    // Run all relevant replace files
    system("cd benchmarks/replace && gcc -o replaceScript replaceScript.c && ./replaceScript && cd ../.. && clear");

    // Run all relevant printtokens files
    system("cd benchmarks/printtokens && gcc -o printtokensScript printtokensScript.c && ./printtokensScript && cd ../.. && clear");


    // Run all relevant printtokens2 files
    system("cd benchmarks/printtokens2 && gcc -o printtokens2Script printtokens2Script.c && ./printtokens2Script && cd ../.. && clear");

    // Run all relevant schedule files
    system("cd benchmarks/schedule && gcc -o scheduleScript scheduleScript.c && ./scheduleScript && cd ../.. && clear");

    // Run all relevant schedule2 files
    system("cd benchmarks/schedule2 && gcc -o schedule2Script schedule2Script.c && ./schedule2Script && cd ../.. && clear");

    // Run all relevant totinfo files
    system("cd benchmarks/totinfo && gcc -o totinfoScript totinfoScript.c && ./totinfoScript && cd ../.. && clear");

    // End time and print time in seconds
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken to run all test scripts: %f seconds\n", cpu_time_used);

    return 0;
}