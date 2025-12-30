This program was built in Ubuntu and MacOs environment and thus we created a DockerImage to ease testing.

## Run the following commands to pull and run the docker image.

docker pull deepakintherace/benchmark:2.0

docker run -it deepakintherace/benchmark:2.0

### Warning the container may run for around 2 hours so please wait patiently!!!

This will run all the files but the outputs will be stored in summary.txt file, inorder to access it you might have to get into the docker CLI and use touch commands

### The summary file locations are

/benchmark/tcas/summary.txt

/benchmark/totinfo/summary.txt

and so...

For Evaluation purposes and to check the summary in an instance we have also uploaded our program that has fully run in the branch data-branch instead of master where the master branch does not have any of the executables or the output text files.

### To check for the generated testcases

1. Please go to the branch "data-branch" in Github
2. In every program folder (like inside tcas, totinfo) you can find the generated testSuites
3. The names of the test case are given as follows:-

   random-statement-suite.txt - randomP.txt

   random-branch-suite.txt - branchRandomP.txt

   total-statement-suite.txt - totalP.txt

   total-branch-suite.txt - branchTotalP.txt

   additional-statement-suite.txt - additionalP.txt

   additional-branch-suite.txt - branchAdditional.txt

If you would like to run each program separately go into the program directory for example tcas and run tcasScript.c and you can do this for the rest.
