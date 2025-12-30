import os


def main():


    os.system("gcc -Wno-return-type -fprofile-arcs -ftest-coverage -g -o tcas tcas.c")
    os.system("clear")
    testSuites = [
        "randomP.txt",
        "branchRandomP.txt",
        "totalP.txt",
        "branchTotalP.txt",
        "additionalP.txt",
        "branchAdditionalP.txt",
        "universe.txt"
    ]
    
    for testSuite in testSuites:
        versionTester(testSuite)
    
        
    os.system("clear")
    os.system("rm tcas")
    os.system("rm tcas.gcda")
    os.system("rm output.txt")
        
def versionTester(testSuite):
    
    with open(testSuite, 'r') as file:
        lines = file.readlines()


    benchMarkOutput = []

    # Print the content of the file
    for line in lines:
        # Prevent the last line from being a new line
        if line.endswith("\n"):
            line = line[:-1]
        command = "./tcas " + line + " > " + "output.txt"
        os.system(command)
        # Clear screen
        # os.system("clear")
        with open('output.txt', 'r') as file:
            output = file.readlines()
            if output != []:
                benchMarkOutput.append(output)

    # Read all folders that starts from v1 to v41
    tcasFolders = [f for f in os.listdir('.') if os.path.isdir(f) and f.startswith("v")]

    prioritizationVersionOutputs = []

    for folder in tcasFolders:
        
        compileCommand = "gcc -o prior" + folder + " " + folder + "/tcas.c"
        os.system(compileCommand)

        versionOutput = []

        for line in lines:
            if line.endswith("\n"):
                line = line[:-1]
            command = "./prior" + folder + " " + line + " > " + "output.txt"
            os.system(command)
            with open('output.txt', 'r') as file:
                output = file.readlines()
                if output != []:
                    versionOutput.append(output)

        prioritizationVersionOutputs.append([folder, versionOutput])
        os.system("rm prior" + folder)
        

    os.system("rm output.txt")
    os.system("rm tcas.gcda")
    os.system("clear")

    testSuiteSummary = []
    for versions in range(len(prioritizationVersionOutputs)):
        errorsInVersion = 0
        for i in range(len(benchMarkOutput)):
            if benchMarkOutput[i] != prioritizationVersionOutputs[versions][1][i]:
                errorsInVersion += 1
                
        if errorsInVersion > 0:
            testSuiteSummary.append(testSuite + " Suite identified " + str(errorsInVersion) + " bugs in version " + prioritizationVersionOutputs[versions][0])


    # Append testSuiteSummary to a file
    with open("summary.txt", "a") as file:
        for line in testSuiteSummary:
            file.write(line + "\n")

        file.write("--------------------------------------------------------\n")
        file.close()


if __name__ == "__main__":
    main()