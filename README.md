# MiniCov-Optimized-Test-Suite-Generator

## What is this project about?

This project evaluates the effectiveness of different test prioritization strategies using **mutation testing**. We compare three approaches for selecting and ordering test cases:

1. **Random Prioritization** - Randomly selects test cases
2. **Total Prioritization** - Prioritizes tests based on individual coverage scores
3. **Additional Prioritization** - Uses greedy algorithm to maximize cumulative coverage

The framework tests these strategies across 7 benchmark programs (tcas, totinfo, replace, printtokens, printtokens2, schedule, schedule2) by:
- Generating test suites using each prioritization strategy
- Running tests against the original program and 100+ mutant versions (artificially buggy versions)
- Measuring how many mutants each test suite can detect (kill)

## Metrics Measured

### 1. **Mutation Score**
- **What**: Number of mutants killed by each test suite
- **How**: Compares output of original program vs. mutant versions for each test case
- **Output**: Reports like `"[TestSuite] Suite identified X bugs in version vY"`

### 2. **Statement Coverage**
- **What**: Percentage of code statements executed by test cases
- **Target**: 98.45% coverage threshold
- **How**: Uses GCC's gcov tool with `-fprofile-arcs -ftest-coverage` flags

### 3. **Branch Coverage**
- **What**: Percentage of code branches (if/else, loops) executed by test cases
- **Target**: 100% coverage threshold
- **How**: Uses GCC's gcov tool with branch coverage analysis

### 4. **Test Suite Size**
- **What**: Number of test cases in each prioritized suite
- **Comparison**: Different strategies may achieve similar coverage with different suite sizes

### 5. **Coverage Efficiency**
- **What**: How quickly each strategy reaches coverage thresholds
- **Comparison**: Which strategy requires fewer tests to reach 98.45% statement or 100% branch coverage

## Results

Results are stored in `summary.txt` files within each benchmark directory, showing:
- Which mutants were killed by each test suite
- Mutation detection effectiveness of each prioritization strategy
- Comparison of random vs. coverage-based vs. greedy approaches

## Quick Start

```bash
# Run a single benchmark
cd benchmarks/tcas
gcc -o tcasScript tcasScript.c && ./tcasScript

# Run all benchmarks (takes ~2 hours)
gcc -o runTestScript runTestScript.c && ./runTestScript
```
