//
//  BinarySearchTree.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/7/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_BinarySearchTree_h
#define advC_lab_5_BinarySearchTree_h

#include "Word.h"



// DEFINE
typedef struct BinarySearchTreeNode BSTNode;
typedef struct BinarySearchTree BST;

#pragma mark STRUCT - Binary Search Tree Node
struct BinarySearchTreeNode {
    // Parent
    BSTNode *parent;
    // Children
    BSTNode *leftChild;
    BSTNode *rightChild;
    
    // Display Options
    int isVisible;
    
    // Data
    WORD *word;
};

#pragma mark STRUCT - Binary Search Tree
struct BinarySearchTree {
    // Pointer to Root Node
    BSTNode *root;
    
    // Properties
    long count;
    int levels;
};

// FUNCTIONS
#pragma mark INITIALIZATION
    // Initialization
    BST* newBST();
    BSTNode* newNodeBST(WORD *word);

#pragma mark DESTRUCTION
int freeBST(BST *tree);
int freePostOrderBSTNode(BSTNode *node);
int freeBSTNode(BSTNode *node);

#pragma mark INSERTION
    // Insertion
    int insertBST(BST *tree, WORD *word);
    static int BSTNodeInsert(BST *tree, BSTNode *currentNode, WORD *word);

#pragma mark SEARCH
    // Search
    WORD* searchBST(BST *tree, char *word);
    static WORD* searchBSTNode(BSTNode *currentNode, WORD *word);

#pragma mark DELETION
    // Deletion
    int lazyDeleteBST(BSTNode *node);
    int reverseLazyDeleteBST(BSTNode *node);

#pragma mark TRAVERSAL

#pragma mark LOGGING
void inOrderPrintBST(BST *tree);
void inOrderPrintBSTNodes(BSTNode *node);

#pragma mark STRING
char* inOrderStringBST(BST *tree, long wordFrameSize, int maxPageDigits, int maxLineDigits);
char* inOrderStringBSTNodes(BSTNode *node, char* str, long wordFrameSize, int maxPageDigits, int maxLineDigits);

#pragma mark FILE PROCESSING
/*
int writeTree(FILE *fp, BST *tree, long wordFrameSize, int maxPageDigits, int maxLineDigits);
int writeNode(FILE *fp, BSTNode *node, long wordFrameSize, int maxPageDigits, int maxLineDigits);
*/
#pragma mark TESTING
BST* generateBST(int numbOfInserts, char* wordArr[SIZE]);

#endif
