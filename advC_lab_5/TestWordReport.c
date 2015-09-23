//
//  TestWordReport.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/13/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include "WordReport.h"
#include "TestWordReport.h"

#pragma mark MAIN TEST
void testWordReport() {
    
    /*
    // Test Helper Functions
    testTimestamp();
    
    // Create a Word Report
    WORD_REPORT *wr = testWordReportConstructor();
    testWriteWordReport(wr);
    testOutputWordReport(wr);
     freeWordReport(wr);
     */

    testSmallFile();
    //testSpecialCase();
}



#pragma mark TESTCASES
void testSpecialCase() {
    // Create a New Word Report
    WORD_REPORT *specialCase = newWordReport("specialCases.txt", 10, 10);
    testProcessFile(specialCase);
    PRINT_BUFFER
    testWriteWordReport(specialCase);
    PRINT_BUFFER
    testOutputWordReport(specialCase);
    PRINT_BUFFER
    freeWordReport(specialCase);
}

void testSmallFile() {
    // Create a New Word Report
    WORD_REPORT *smallTest = newWordReport("lab5_smallTestFile.txt", 10, 10);
    testProcessFile(smallTest);
    testWriteWordReport(smallTest);
    testOutputWordReport(smallTest);
    freeWordReport(smallTest);
}


WORD_REPORT* testWordReportConstructor() {
    printf("TESTCASE: Constructor\n");
    // Call constructor
    WORD_REPORT *wr = newWordReport("TestFile.txt", 10, 10);
    
    // Words for tree
    char* validWords[] = { "mnm", "zzz", "aaa", "car", "cara", "aaa", "zzz", "zzz", "test", "final" };
    
    // Generate a tree
    freeBST(wr->validWordTree);
    wr->validWordTree = generateBST(15, validWords);
    wr->longestWordSize = 10;
    
    return wr;
}

void testWriteWordReport(WORD_REPORT *wr) {
    printf("TESTCASE: Write Word Report\n");
    // Setup the test file in the WR struct
    wr->filepath = "specialCases.txt";
    // Test writeReport
    char *report = writeReport(wr);
    printf("%s", report);
}

void testOutputWordReport(WORD_REPORT *wr) {
    printf("TESTCASE: Output Word Report\n");
    
    outputReportFile(wr,"out.txt");
}

void testProcessFile(WORD_REPORT *wr) {
    printf("TESTCASE: Process File\n");
    processFile(wr);
    //printf("%s", writeReport(wr));
}

void testIsValid() {
    
    char invalid[6] = "mass'";
    char valid[6]   = "can't";
    char endSentence[6] = "stop:";
    
    
    if (searchWord((char*) &invalid, "'") == TRUE) printf("FAILED: searchWord(\"mass'\", \"'\")\n");
    
    PRINT_BUFFER
    
    if (searchWord((char*) &valid, "'") == FALSE) printf("FAILED: searchWord(\"mass'\", \"'\")\n");
    
    PRINT_BUFFER
    
    if (matchLastChar((char*) &invalid, "'-") == TRUE) printf("INVALID WORD: %s\n", invalid);
    
    PRINT_BUFFER
    
    if (matchLastChar((char*) &endSentence, ".,?!;:") == TRUE) printf("End of Sentence: %s\n", (char*) &endSentence);
}


#pragma mark TESTCASES - HELPERS
void testHelpers(WORD_REPORT *wr) {
    testTimestamp();
    testIsValid();
}
void testTimestamp() {
    printf("TESTCASE: Timestamp\n");
    printf("Timestamp: %s", timestamp());
    
}