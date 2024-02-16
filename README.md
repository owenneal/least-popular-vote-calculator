# Minimum Popular Votes to Win Election

## Introduction
This program calculates the minimum popular votes needed to win the U.S. Presidential Election based on electoral votes for a given year.

## Program Details
- **Course:** CS 211, Fall 2023, UIC
- **Author:** Owen Neal

## Usage

### Compilation
Compile the program using a C compiler. For example, using GCC:

gcc MinPopVote.c -o MinPopVote


Run the program with the following command-line arguments:

./MinPopVote [-y year] [-q] [-f]
Command-line Arguments
-y year: Sets the election year (default: 0, user input required).
-q: Quiet mode. If enabled, full State lists and subset details won't be printed (default: OFF).
-f: Fast mode. If enabled, the program uses a faster version with memoization (default: OFF).

Input Data
Place the election data files in the data directory. Ensure the file follows the format data/[year].csv.

Output Data
The program will generate output files in the toWin directory with the format [year]_win.csv.

Program Structure
MinPopVote.c: The main source code file.
MinPopVote.h: Header file containing function prototypes and data structures.
Functions
setSettings: Parses command-line arguments and sets program settings.
inFilename: Creates an input data filename based on the year.
outFilename: Creates an output filename based on the year.
parseLine: Parses a line of data and populates a State structure.
readElectionData: Reads election data from a file and creates an array of State structs.
totalEVs: Calculates the total electoral votes.
totalPVs: Calculates the total popular votes.
minPopVoteAtLeast: Finds the subset of states with the lowest popular votes needed to win the election (recursive).
minPopVoteToWin: Wrapper function for the recursive function.
minPopVoteAtLeastFast: Faster version with memoization.
minPopVoteToWinFast: Wrapper function for the fast version.
writeSubsetData: Writes the subset data to a file.

Main Program
main: The main program that handles user input, reads data, and calculates the minimum popular votes.

Examples
Compile and run the program with the following command:
./MinPopVote -y 2020 -q -f
This will calculate and display the minimum popular votes needed to win the 2020 U.S. Presidential Election quietly and using the fast mode.
