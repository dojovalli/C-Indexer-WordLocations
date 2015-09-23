//
//  TestBinarySearchTree.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/11/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include "TestBinarySearchTree.h"
#include "Word.h"

#pragma mark MAIN TEST FUNCTION
int testBinarySearchTree(int isVerbose) {
    char* testName = "TestBinarySearchTree";
    // Initialize testResult
    int testResult = SUCCESS;
    
    // Generate a Default Tree
    char* validWords[] = { "mnm", "zzz", "aaa", "car", "cara", "aaa", "zzz", "zzz", "test", "final" };
    char* invalidWords[5] = { "bug", "error", "failure", "can't", "won't" };
    BST *tree = generateTestBST(validWords);
    
    
    if (testInsertBST(tree, isVerbose) > 0) testResult = FAILED;
    if (testSearchBST(tree, validWords, invalidWords, isVerbose) > 0) testResult = FAILED;
    if (testBSTReportString(tree, isVerbose) > 0) testResult = FAILED;
    if (testFreeBST(tree) > 0 ) testResult = FAILED;
    
    
    
    if (testResult == SUCCESS) {
        printf("\n%s - ALL TESTS EXECUTED SUCCESSFULLY!\n", testName);
    } else {
        printf("\n%s - SOME TESTS FAILED!\n", testName);
    }
    
    return testResult;
}

#pragma mark TESTCASES
int testInsertBST(BST *tree, int isVerbose) {
    printf("TESTCASE: INSERTION\n");
    // Print the tree
    if (isVerbose == TRUE) {
        printf("PRE-INSERTION - TREE OVERVIEW\n");
        inOrderPrintBST(tree);
    }
    
    // Create test word
    WORD *insertionTestWord = newWord(TEST_WORD, newWordLocation(1, 1, 1));
    
    if (isVerbose == TRUE) {
        printf("INSERTION - TEST WORD\n");
        printWord(insertionTestWord, 15, maxPageDigit, maxLineDigit);
    }
    
    // Run the insert function
    insertBST(tree, insertionTestWord);
    
    // Print the tree
    if (isVerbose == TRUE) {
        printf("POST-INSERTION - TREE OVERVIEW\n");
        inOrderPrintBST(tree);
    }
    
    if (searchBST(tree, TEST_WORD) != NULL) {
        return SUCCESS;
    }
    return FAILED;
}
int testSearchBST(BST *tree, char** validWords, char** invalidWords, int isVerbose) {
    printf("\nTESTCASE: SEARCH\n");
    // Search for valid words
    printf("Search - Valid Words\n");
    // Start - Long Way
    char *searchWord = validWords[3];
    WORD *w = searchBST(tree, searchWord);
    printWord(w, FRAME_SIZE, maxPageDigit, maxLineDigit);
    // End - Long way
    printWord(searchBST(tree, "mnm"), FRAME_SIZE, maxPageDigit, maxLineDigit);          // Using String Literal
    printWord(searchBST(tree, validWords[6]), FRAME_SIZE, maxPageDigit, maxLineDigit);  // Using Short Array Access -> char*
    printWord(searchBST(tree, validWords[9]), FRAME_SIZE, maxPageDigit, maxLineDigit);
    
    printf("\nSearch - Invalid Words\n");
    for (int i = 0; i < 5; i++) {
        // Print Word if invalid word is in the BST, else, print message that word is not in the BST
        if ( (w = searchBST(tree, invalidWords[i]))  != NULL) printWord(w, FRAME_SIZE, maxPageDigit, maxLineDigit);
        else printf("Cannot find '%s' in the Search Tree!\n", invalidWords[i]);
    }
    
    return SUCCESS;
}

int testBSTReportString(BST *tree, int isVerbose) {
    printf("TESTCASE: REPORT STRING\n");
    char* report = NULL;
    
    // Build a Report String
    report = inOrderStringBST(tree, 15, 2, 2);
    
    
    if (report != NULL) {
        printf("REPORT STRING: SUCCESS\n");
        if (isVerbose) {
            printf("REPORT\n");
            printf("%s", report);
        }
        return SUCCESS;
    }
    printf("REPORT STRING: FAILED\n");
    return FAILED;
}
int testFreeBST(BST *tree) {
    printf("\nTESTCASE: FREE TREE MEMORY\n");
    return freeBST(tree);
}

#pragma mark CONVENIENCE
BST* generateTestBST(char* words[10]) {
    return generateBST(15, words);
}