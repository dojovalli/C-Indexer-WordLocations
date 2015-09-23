/*********************************************************************************
 ** CIS 26B													    Spring, 2015
 ** Advanced C
 ******************
 **
 ** Homework 5: Word Report
 **
 **
 **
 **********************************************************************************
 
 Creates a Report on text files
 
 Save the output as a comment at the end of the program!
 **********************************************************
 **
 **  Written By:        Matthew Valli
 **
 **  Date:              6/19/205
 **  IDE (compiler):    Xcode (Unix - Mach Kernel)
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "TestDBLQueue.h"
#include "TestWord.h"
#include "TestBinarySearchTree.h"
#include "TestWordReport.h"
#include "WordReport.h"

#define TRUE 1

int main(int argc, const char * argv[])
{
    // Label the Application
    printf("WORD REPORT\n");
    
    // Set up text file to constuct report
    char* text = (char *)argv[1];
    if ((char *)argv[1] == NULL) {
        text = "lab5_smallTestFile.txt";
        printf("No filepath provided - Using default file!\n");
    }
    
    // Read Arguments from command line
    printf("Opening file %s...\n\n", text);
    
    // Create report
    runWordReport(text, "out.txt", TRUE);
    
    // Master Test
    //testAllCases();
    
    return 0;
}

void testAllCases(int isVerbose) {
    // TESTING
    printf("TESTING\n");
    testDBLQueue(isVerbose);
    testWord(isVerbose);
    testBinarySearchTree(isVerbose);
    
    testMergeWord();
    testWordReport();
}

/*
 ************* Sample output in out.txt *************
 
 SAMPLE RUN:
    
 */
