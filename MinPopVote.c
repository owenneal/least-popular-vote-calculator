//@file "MinPopVote.c"
/*-------------------------------------------
Program 4: Minimum popular votes to win election
Course: CS 211, Fall 2023, UIC
System: Advanced zyLab
Author: Owen Neal
------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

// set the program settings from command-line arguments
// @param argc -> the number of command-line arguments
// @param argv -> the array of command-line argument strings
// @param year -> a pointer to store the year
// @param fastMode -> a pointer to store fast mode setting
// @param quietMode -> a pointer to store quiet mode setting
// @return true if the settings are successfully, false if there is an error
bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    *fastMode = false;
    *quietMode = false;
    *year = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0)
        {
            *fastMode = true;
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            *quietMode = true;
        }
        else if (strcmp(argv[i], "-y") == 0)
        {
            if (i + 1 < argc)
            {
                int inYear = atoi(argv[i + 1]);
                if (inYear >= 1828 && inYear <= 2020 && inYear % 4 == 0)
                {
                    *year = inYear;
                    i++;
                }
                else
                {
                *year = 0;
                i++;
                }
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}

// create an input data filename from the year
// @param filename -> character array to save the created filename
// @param year -> year used to create filename
void inFilename(char* filename, int year) {
    snprintf(filename, 256, "data/%d.csv", year);
}

// create an output filename from the year
// @param filename -> character array to save the created filename
// @param year -> year used to create filename
void outFilename(char* filename, int year) {
    snprintf(filename, 256, "toWin/%d_win.csv", year);
}

// parse a line of data and populate a State structure
// @param line -> the input data line to be parsed
// @param myState -> a pointer to a state structure where the parsed data will be saved
// @return -> true if the line is parsed correctly, false if incorrect
bool parseLine(char* line, State* myState) {
    if (line == NULL || line[0] == '\0')
    {
        return false;
    }
    // get the statename by tokenizing the line to the first instance of ','
    char* t = strtok(line, ",");
    if (t == NULL)
    {
        return false;
    }
    strncpy(myState->name, t, sizeof(myState->name));
    myState->name[sizeof(myState->name) - 1] = '\0';

    // get postal code by tokenizing the line to the next instance of ','
    t = strtok(NULL, ",");
    if (t == NULL)
    {
        return false;
    }
    strncpy(myState->postalCode, t, sizeof(myState->postalCode));
    myState->postalCode[sizeof(myState->postalCode) - 1] = '\0';

    // get electoral votes by tokenizing the line to the next instance of ','
    t = strtok(NULL, ",");
    if (t == NULL)
    {
        return false;
    }
    myState->electoralVotes = atoi(t);

    // get popular votes by tokenizing the line to the next instance of ','
    t = strtok(NULL, ",");
    if (t == NULL)
    {
        return false;
    }
    myState->popularVotes = atoi(t);

    return true;
}

// read election data from a file and create an array of State structs
// @param filename -> name of the file containing election data
// @param allStates -> an array of State structures
// @param nStates -> pointer to an inter that will save the number of states read
// @return -> true if the data is successfully read and parsed
bool readElectionData(char* filename, State* allStates, int* nStates) {
    *nStates = 0;
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return false;
    }
    int stcnt = 0;
    char ln[256];

    while (fgets(ln, sizeof(ln), file) != NULL)
    {
        if (parseLine(ln, &allStates[stcnt])) // fills in values for the state sub items
        {
            stcnt++;
        }
        if (stcnt >= 51) // stop reading file if more than 51 states will be read
        {
            break;
        }
    }
    fclose(file);
    *nStates = stcnt;
    return true; //modify or replace this
}

// Calculates the total electoral votes of an array of State structs
// @param states -> an array of State structures
// @param szStates -> number of states in the array
// @return the total electoral votes
int totalEVs(State* states, int szStates) {
    int totalEv = 0;
    for (int i = 0; i < szStates; i++)
    {
        totalEv+=states[i].electoralVotes;
    }
    return totalEv;
}

// Calculates the total popular votes of an array of State structs
// @param states -> an array of State structures
// @param szStates -> number of states in the array
// @return the total popular votes
int totalPVs(State* states, int szStates) {
    int totalPV = 0;
    for (int i = 0; i < szStates; i++)
    {
        totalPV+=states[i].popularVotes;
    }
    return totalPV;
}

// find the subset of states with the lowest popular votes needed to win the election
// done by recursively considering every subset
// @param states -> array of State structs
// @param szStates -> number of states in states array
// @param start -> index of current state being considered
// @param EVs -> number of required electoral votes for each subset
// @return -> a MinInfo struct representing the minimum popular votes to win the election
MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    if (EVs <= 0) // more EVs not necessary 
    {
        MinInfo result;
        result.sufficientEVs = (EVs <= 0);
        result.szSomeStates = 0;
        result.subsetPVs = 0;
        result.someStates;
        return result;
    }

    if (start == szStates) // out of states to consider
    {
        MinInfo result;
        result.szSomeStates = 0;
        result.subsetPVs = 0;
        result.someStates;
        result.sufficientEVs = (EVs <= 0);
        return result;
    }

    // include state recursive branch
       MinInfo includeState;
        includeState = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes); // EVs - EVs - states[start].electoral bc we need less electoral votes
       includeState.someStates[includeState.szSomeStates] = states[start];
       includeState.szSomeStates++;
       includeState.subsetPVs += (states[start].popularVotes/2) + 1;

    MinInfo excludeState = minPopVoteAtLeast(states, szStates, start + 1, EVs);

    if (excludeState.sufficientEVs && excludeState.subsetPVs < includeState.subsetPVs)
    {
        return excludeState;
    }
    else
    {
        return includeState;
    }
}

// wrapper function for the recursive function minPopVoteAtLeast
// @param states -> an array of state structs
// @param szStates -> number of states in the array
// @return -> a MinInfo struct representing the minimum popular votes to win the election
MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}

// find the subset of states with the lowest popular votes needed to win the election
// done by recursively considering every subset and uses memoization to make more efficient
// @param states -> array of State structs
// @param szStates -> number of states in states array
// @param start -> index of current state being considered
// @param EVs -> number of required electoral votes for each subset
// @param memo -> array of already calculated start points and its related EVs and popular votes
// @return -> a MinInfo struct representing the minimum popular votes to win the election
MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    if (EVs <= 0) // no more EVs needed to win election
    {
        MinInfo result;
        result.sufficientEVs = (EVs <= 0);
        result.szSomeStates = 0;
        result.subsetPVs = 0;
        result.someStates;
        return result;
    }
    
    if (start == szStates) // out of states to consider
    {
        MinInfo result;
        result.szSomeStates = 0;
        result.subsetPVs = 0;
        result.someStates;
        result.sufficientEVs = (EVs <= 0);
        return result;
    }

    if (memo[start][EVs].subsetPVs != -1) // check if  this start point and evs have already been calculated
    {
        return memo[start][EVs];
    }

    // include state recursive branch
       MinInfo includeState;
        includeState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo); // EVs - EVs - states[start].electoral bc we need less electoral votes
       includeState.someStates[includeState.szSomeStates] = states[start];
       includeState.szSomeStates++;
       includeState.subsetPVs += (states[start].popularVotes/2) + 1;

    MinInfo excludeState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo);

    MinInfo res;

    if (excludeState.sufficientEVs && excludeState.subsetPVs < includeState.subsetPVs)
    {

        //return excludeState;
        res = excludeState;
    }
    else
    {
        //return includeState;
        res = includeState;
    }
    memo[start][EVs] = res;
    return res;
}

// wrapper function for the recursive function minPopVoteAtLeastFast
// creates a 2D array to store start points, its associated EVs and creates a 2D array
// for memoization purposes
// @param states -> an array of state structs
// @param szStates -> number of states in the array
// @return -> a MinInfo struct representing the minimum popular votes to win the election
MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*));
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);
 
    for (int j = 0; j < szStates + 1; j++)
    {
        free(memo[j]);
    }
    
    free(memo);
    return res;
}

// writes the subset recieved from recursive function to a file
// @param filenameW -> output file name
// @param totEVs -> contains the total electoral votes for the subset
// @param totPVs -> contains the total popular votes for the subset
// @param wonEVs -> contains the total won EVs in the subset
// @param toWin -> MinInfo struct holding the subset found
// returns true -> if file opened correctly
bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    FILE *file = fopen(filenameW, "w");
    if (file == NULL)
    {
        return false;
    }

    fprintf(file, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs);

    for (int i = toWin.szSomeStates - 1; i >= 0; i--)
    {
        State state = toWin.someStates[i];
        fprintf(file, "%s,%s,%d,%d\n", state.name, state.postalCode, state.electoralVotes, state.popularVotes / 2 + 1);
    }
    fclose(file);
    return true;
}
