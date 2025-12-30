import os

def main():
    os.system("rm coverage.txt")
    os.system("rm printtokens.gcda")
    with open('totalPrioritization.txt', 'r') as file:
        statementLines = file.readlines()

    # Remove all newline char
    for i in range(len(statementLines)):
        if statementLines[i].endswith("\n"):
            statementLines[i] = statementLines[i][:-1]

    cummulativeStatmentTestCases = []
    cummulativeStatmentTestCases.append(statementLines[0])
    statementLines.remove(statementLines[0])

    cummulativeStatementCoverage = 0.0
    os.system("./printtokens " + cummulativeStatmentTestCases[0])
    
    os.system("gcov -b printtokens.c > coverage.txt")

    with open('coverage.txt', 'r') as file:
        coverageLines = file.readlines()
        # Get statement coverage as the float value in lines executed
        for line in coverageLines:
            if "Lines executed:" in line:
                coverageLine = line.split(" ")[-3] #in the format (executed:83.08%)
                coverageLine = coverageLine[:-1]
                coverageLine = coverageLine[9:] # remove the "executed" word
                # extract the float value
                cummulativeStatementCoverage = float(coverageLine)
                break
    
    while cummulativeStatementCoverage < 94.96:

        
        maxTempStatementLine = ""
        cummulativeStatementCoverage = cummulativeTestCaseUpdater(cummulativeStatmentTestCases)
        maxStatementCoverage = cummulativeStatementCoverage

        for tempLine in statementLines:

            _ = cummulativeTestCaseUpdater(cummulativeStatmentTestCases)
            
            os.system("./printtokens " + tempLine)
            os.system("gcov -b printtokens.c > coverage.txt")
            with open('coverage.txt', 'r') as tempCoverageFile:
                tempCoverageLines = tempCoverageFile.readlines()
                # Get statement coverage as the float value in lines executed
                for line in tempCoverageLines:
                    if "Lines executed:" in line:
                        tempCoverageLine = line.split(" ")[-3]
                        tempCoverageLine = tempCoverageLine[:-1]
                        tempCoverageLine = tempCoverageLine[9:]
                        # extract the float value
                        tempStatementCoverage = float(tempCoverageLine)

                        if tempStatementCoverage > maxStatementCoverage:
                            maxStatementCoverage = tempStatementCoverage
                            maxTempStatementLine = tempLine
                            break

                
                

        cummulativeStatmentTestCases.append(maxTempStatementLine)
        if maxTempStatementLine in statementLines:
            statementLines.remove(maxTempStatementLine)
        os.system("clear")
        
    if cummulativeStatmentTestCases[-1] == "":
        cummulativeStatmentTestCases.pop()

    # Write the test cases to a file called "additionalP.txt"
    with open('additionalP.txt', 'w') as file:
        for line in cummulativeStatmentTestCases:
            file.write(line + "\n")
    

            
    # Now do the same for branch coverage
    os.system("rm coverage.txt")
    os.system("rm printtokens.gcda")
    with open('branchTotalPrioritization.txt', 'r') as file:
        branchLines = file.readlines()

    # Remove all newline char
    for i in range(len(branchLines)):
        if branchLines[i].endswith("\n"):
            branchLines[i] = branchLines[i][:-1]

    cummulativeBranchTestCases = []
    cummulativeBranchTestCases.append(branchLines[0])
    branchLines.remove(branchLines[0])

    cummulativeBranchCoverage = 0.0
    os.system("./printtokens " + cummulativeBranchTestCases[0])
    os.system("gcov -b printtokens.c > coverage.txt")

    with open('coverage.txt', 'r') as file:
        coverageLines = file.readlines()
        # Get statement coverage as the float value in lines executed
        for line in coverageLines:
            if "Branches executed:" in line:
                coverageLine = line.split(" ")[-3]
                coverageLine = coverageLine[:-1]
                coverageLine = coverageLine[9:]
                # extract the float value
                cummulativeBranchCoverage = float(coverageLine)
                break

    while cummulativeBranchCoverage < 100.0:
            
            maxTempBranchLine = ""
            cummulativeBranchCoverage = branchCummulativeTestCaseUpdater(cummulativeBranchTestCases)
            maxBranchCoverage = cummulativeBranchCoverage
    
            for tempLine in branchLines:
    
                _ = branchCummulativeTestCaseUpdater(cummulativeBranchTestCases)
                os.system("./printtokens " + tempLine)
                os.system("gcov -b printtokens.c > coverage.txt")
                with open('coverage.txt', 'r') as tempCoverageFile:
                    tempCoverageLines = tempCoverageFile.readlines()
                    # Get statement coverage as the float value in lines executed
                    for line in tempCoverageLines:
                        if "Branches executed:" in line:
                            tempCoverageLine = line.split(" ")[-3]
                            tempCoverageLine = tempCoverageLine[:-1]
                            tempCoverageLine = tempCoverageLine[9:]
                            # extract the float value
                            tempBranchCoverage = float(tempCoverageLine)
    
                            if tempBranchCoverage > maxBranchCoverage:
                                maxBranchCoverage = tempBranchCoverage
                                maxTempBranchLine = tempLine
                                break

            cummulativeBranchTestCases.append(maxTempBranchLine)
            if maxTempBranchLine in branchLines:
                branchLines.remove(maxTempBranchLine)
            os.system("clear")

    if cummulativeBranchTestCases[-1] == "":
        cummulativeBranchTestCases.pop()

    # Write the test cases to a file called "additionalBranchP.txt"
    with open('branchAdditionalP.txt', 'w') as file:
        for line in cummulativeBranchTestCases:
            file.write(line + "\n")

    os.system("rm coverage.txt")
    os.system("rm printtokens.gcda")
    os.system("rm totalPrioritization.txt")
    os.system("rm branchTotalPrioritization.txt")
    os.system("clear")




    


def cummulativeTestCaseUpdater(cummulativeStatmentTestCases):
    os.system("rm coverage.txt")
    os.system("rm printtokens.gcda")
    for cummulativeStatmentTestCase in cummulativeStatmentTestCases:
            os.system("./printtokens " + cummulativeStatmentTestCase)
            os.system("gcov -b printtokens.c > coverage.txt")
            with open('coverage.txt', 'r') as cummulativeCoverageFile:
                cumulativeCoverageLines = cummulativeCoverageFile.readlines()
                # Get statement coverage as the float value in lines executed
                for line in cumulativeCoverageLines:
                    if "Lines executed:" in line:
                        cumulativeCoverageLine = line.split(" ")[-3] #in the format (executed:83.08%)
                        cumulativeCoverageLine = cumulativeCoverageLine[:-1]
                        cumulativeCoverageLine = cumulativeCoverageLine[9:] # remove the "executed" word
                        # extract the float value
                        cummulativeStatementCoverage = float(cumulativeCoverageLine)
                        break
    return (cummulativeStatementCoverage)
    
def branchCummulativeTestCaseUpdater(cummulativeBranchTestCases):
    os.system("rm coverage.txt")
    os.system("rm printtokens.gcda")
    for cummulativeBranchTestCase in cummulativeBranchTestCases:
            os.system("./printtokens " + cummulativeBranchTestCase)
            os.system("gcov -b printtokens.c > coverage.txt")
            with open('coverage.txt', 'r') as cummulativeCoverageFile:
                cumulativeCoverageLines = cummulativeCoverageFile.readlines()
                # Get statement coverage as the float value in lines executed
                for line in cumulativeCoverageLines:
                    if "Branches executed:" in line:
                        cumulativeCoverageLine = line.split(" ")[-3] #in the format (executed:83.08%)
                        cumulativeCoverageLine = cumulativeCoverageLine[:-1]
                        cumulativeCoverageLine = cumulativeCoverageLine[9:] # remove the "executed" word
                        # extract the float value
                        cummulativeBranchCoverage = float(cumulativeCoverageLine)
                        break
    return (cummulativeBranchCoverage)



if __name__ == "__main__":
    main()