# Needleman-Wunsch Algorithm

## Overview
Implementation of the Needleman-Wunsch algorithm to find the global sequence alignment. Finds the most optimal alignment between two given sequences using dynamic programming. **The output is the two aligned sequences with the final score.** The output matrices are optional.


## Compilation
Use the provided Makefile to compile the program:
```
make
```
To remove the compiled executable, run:
```
make clean
```

## Usage
To run the program you can do either:
```
make run
```
or
```
./nw.out
```

You will be prompted for two sequences, followed by an option to change the scoring values. You will also be given the option to print the scoring & directional matrices.


