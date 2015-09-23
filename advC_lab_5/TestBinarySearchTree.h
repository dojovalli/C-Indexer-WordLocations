//
//  TestBinarySearchTree.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/11/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_TestBinarySearchTree_h
#define advC_lab_5_TestBinarySearchTree_h

#include "WordReportConstants.h"
#include "BinarySearchTree.h"

// MAIN TEST FUNCTION
int testBinarySearchTree(int isVerbose);

// TESTCASES
int testInsertBST(BST *tree, int isVerbose);
int testSearchBST(BST *tree, char** validWords, char** invalidWords, int isVerbose);
int testFreeBST(BST *tree);
int testBSTReportString(BST *tree, int isVerbose);

// CONVENIENCE
BST* generateTestBST();


#endif
