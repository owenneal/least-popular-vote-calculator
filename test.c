//@file "test.c"
/*-------------------------------------------
Program 4: Minimum popular votes to win election
System: Advanced zyLab
Author: Owen Neal
------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

// tests the total EVs function
// returns true if the result equals the expected result
bool test_totalEVs() {
    State aStates[10];
    int res;
    
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,6);
    if (res != 48) {
        printf("  individual state EVs are 5, 8, 13, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return 0;
    }

    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 15;
    aStates[6].electoralVotes = 12;
    aStates[7].electoralVotes = 8;
    aStates[8].electoralVotes = 14;
    aStates[9].electoralVotes = 13;
    
    printf(" Checking totalEVs() for 10 States:\n");
    res = totalEVs(aStates,10);
    if (res != 100) {
        printf("  expected total EVs = 100, actual total EVs = %d\n",res);
        return false;
    }

    return true;
}

// tests the total PVs function
// returns true if the result equals the expected result
bool test_totalPVs() {
State aStates[10];
    int res;
    
    aStates[0].popularVotes = 5;
    aStates[1].popularVotes = 8;
    aStates[2].popularVotes = 12;
    aStates[3].popularVotes = 6;
    aStates[4].popularVotes = 7;
    aStates[5].popularVotes = 10;

    printf(" Checking totalPVs() for 5 States:\n");
    res = totalPVs(aStates,6);
    if (res != 48) {
        printf("  individual state PVs are 5, 8, 13, 6, 7\n");
        printf("  expected total PVs = 38, actual total PVs = %d\n",res);
        return 0;
    }

    aStates[0].popularVotes = 5;
    aStates[1].popularVotes = 8;
    aStates[2].popularVotes = 12;
    aStates[3].popularVotes = 6;
    aStates[4].popularVotes = 7;
    aStates[5].popularVotes = 15;
    aStates[6].popularVotes = 12;
    aStates[7].popularVotes = 8;
    aStates[8].popularVotes = 14;
    aStates[9].popularVotes = 13;
    
    printf(" Checking totalPVs() for 10 States:\n");
    res = totalPVs(aStates,10);
    if (res != 100) {
        printf("  expected total PVs = 100, actual total PVs = %d\n",res);
        return false;
    }

    return true;
}

// tests the set settings function
// returns true if the result equals the expected result
bool test_setSettings() {
    int year = 0;
    bool fastMode = false;
    bool quietMode = false;

    char* test1[] = {"./app.exe", "-y", "1832", "-q", "-f"};
    char* test2[] = {"./app.exe", "-y", "1832", "-q", "-v"};
    char* test3[] = {"./app.exe", "-y", "1999", "-f"};

    bool yes;
    yes = setSettings(5, test1, &year, &fastMode, &quietMode);
    yes = setSettings(5, test2, &year, &fastMode, &quietMode);
    yes = setSettings(4, test3, &year, &fastMode, &quietMode);
    return yes == 1;
}

// tests the in filename function
// returns true if the result equals the expected result
bool test_inFilename() {
    int year = 1980;

    char finalN[256];
    char fFinal[] = "data/1980.csv";

    inFilename(finalN, year);
    if (strcmp(finalN, fFinal) > 0)
    {
        return false;
    }

    return true;
}

// tests the out file function
// returns true if the result equals the expected result
bool test_outFilename() {
    int year = 1980;

    char finalN[256];
    char fFinal[] = "toWin/1980_win.csv";

    outFilename(finalN, year);
    if (strcmp(finalN, fFinal) != 0)
    {
        return false;
    }

    return true;
}


// tests the parse line function
// returns true if the result equals the expected result
bool test_parseLine() {
    char line1[] = "California,CA,203,10000";
    State state;
    bool yes = parseLine(line1, &state);
    return yes;
}

// tests the read election data function
// returns true if the result equals the expected result
bool test_readElectionData() {
    State states[51];
    int stnum = 0;
    bool yes = readElectionData("data/1828.csv", states, &stnum);
    return yes;
}

// tests the minPopVoteAtLeast function
// returns true if the result equals the expected result
bool test_minPVsSlow() {
    int size = 5;
    State states[4];
    states[0].electoralVotes = 5;
    states[0].popularVotes = 60;
    strcpy(states[0].name, "A");

    states[1].electoralVotes = 2;
    states[1].popularVotes = 20;
    strcpy(states[1].name, "B");

    states[2].electoralVotes = 8;
    states[2].popularVotes = 70;
    strcpy(states[2].name, "C");

    states[3].electoralVotes = 3;
    states[3].popularVotes = 30;
    strcpy(states[3].name, "D");

    MinInfo res = minPopVoteToWin(states, 4);

    bool expected = (res.subsetPVs == 47);

    return expected;
}

// tests the minPopAtLeastFast function
// returns true if the result equals the expected result
bool test_minPVsFast() {
   int size = 5;
    State states[4];
    states[0].electoralVotes = 5;
    states[0].popularVotes = 60;
    strcpy(states[0].name, "A");

    states[1].electoralVotes = 2;
    states[1].popularVotes = 20;
    strcpy(states[1].name, "B");

    states[2].electoralVotes = 8;
    states[2].popularVotes = 70;
    strcpy(states[2].name, "C");

    states[3].electoralVotes = 3;
    states[3].popularVotes = 30;
    strcpy(states[3].name, "D");

    MinInfo res = minPopVoteToWinFast(states, 4);

    bool expected = (res.subsetPVs == 47);

    return expected;
}

int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    return 0;
}
