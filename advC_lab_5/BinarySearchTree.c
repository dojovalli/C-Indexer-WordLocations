//
//  BinarySearchTree.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/7/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinarySearchTree.h"
#include "Word.h"

#pragma mark INITIALIZATION
/* Returns a pointer to a new Binary Search Tree */
BST* newBST() {
    BST* tmp = (BST*) malloc( sizeof(BST) );
    
    if (tmp == NULL) {
        // Memory Full
        printf("The System has used all memory allocate for the program!\n");
        perror("ERROR: ");
        exit(OUT_OF_MEMORY);
    }
    
    // Initialization
    tmp->count  = 0;
    tmp->levels = 1;
    tmp->root   = NULL;
    
    return tmp;
}

/* Returns a pointer to a new BSTNode
 *
 * Parameters:
 *      WORD *word - data to be stored in BSTNode
 */
BSTNode* newBSTNode(WORD *word) {
    BSTNode* tmp = (BSTNode*) malloc( sizeof(BSTNode) );
    
    if (tmp == NULL) {
        // Memory Full
        printf("The System has used all memory allocate for the program!\n");
        perror("ERROR: ");
        exit(OUT_OF_MEMORY);
    }
    
    // Initialization
    tmp->parent     = NULL;
    tmp->leftChild  = NULL;
    tmp->rightChild = NULL;
    tmp->isVisible  = TRUE;
    tmp->word       = word;
    
    return tmp;
}

#pragma mark DESTRUCTION
/*  Frees all memory associated with a BST Tree */
int freeBST(BST *tree) {
    // Zero values for security/clean memory
    tree->levels = 0;
    tree->count = 0;
    
    // Free the Tree using post order
    freePostOrderBSTNode(tree->root);
    
    // Free Self
    free(tree);
    return SUCCESS;
}

/* Frees BSTNodes of a BST recursively in post-order */
int freePostOrderBSTNode(BSTNode *node) {
    if (node != NULL) {
        if (node->leftChild) {
            if (DEBUG_FREE && DEBUG_FREE_BST) {
                if (node->word->word != NULL) {
                    printf("%s", node->word->word);
                } else {
                    printf("root");
                }
                printf(" -> Decend LEFT to ");
                if (node->leftChild->word != NULL) {
                    printf("%s\n", node->leftChild->word->word);
                }
            }
            
            freePostOrderBSTNode(node->leftChild);
        }
        if (node->rightChild) {
            if (DEBUG_FREE && DEBUG_FREE_BST) {
                if (node->word->word != NULL) {
                    printf("%s", node->word->word);
                } else {
                    printf("root");
                }
                printf(" -> Decend RIGHT to ");
                if (node->rightChild->word != NULL) {
                    printf("%s\n", node->rightChild->word->word);
                }
            }
            freePostOrderBSTNode(node->rightChild);
        }
        freeBSTNode(node);
    }
    return SUCCESS;
}

/*  Frees all associated memory for a BSTNode */
int freeBSTNode(BSTNode *node) {
    // Zero out pointers for security/clean memory
    node->parent = NULL;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->isVisible = 0;
    
    // Free Sub-Pointers
    freeWord(node->word);
    
    // Free Self
    free(node);
    return SUCCESS;
}


#pragma mark INSERTION
/* Inserts a WORD into a BST Tree */
int insertBST(BST *tree, WORD *word) {
    // Check if the root is NULL
    if ( tree->root == NULL ) {
        // Set the root a new node
        tree->root = newBSTNode(word);
        tree->count++;
        if (DEBUG_INSERTION) printf("Tree was empty, created new node.\n");
        return TRUE;
    }
    
    // Start from the Root
    return BSTNodeInsert(tree, tree->root, word);
}

/* Inserts a WORD into a BST Tree recursively */
static int BSTNodeInsert(BST *tree, BSTNode *currentNode, WORD *word) {
    int compareResult = compareWord(word, currentNode->word);
    
    if (compareResult == EQUAL) {
        // Update word
        //return megreWord(currentNode->word, word);
        return mergeWord(currentNode->word, word);
    }
    // Check Left Node
    if (compareResult < EQUAL) {
        if (currentNode->leftChild == NULL) {
            // Insert
            currentNode->leftChild = newBSTNode(word);
            tree->count++;
            return TRUE;
        } else {
            // Else, Continue to decend to the LEFT
            BSTNodeInsert(tree, currentNode->leftChild, word);
        }
    } else  if (compareResult > EQUAL) {
        if (currentNode->rightChild == NULL) {
            // Insert
            currentNode->rightChild = newBSTNode(word);
            tree->count++;
            return TRUE;
        } else {
            // Else, Continue to decend to the RIGHT
            BSTNodeInsert(tree, currentNode->rightChild, word);
        }
    }
    return FALSE;
}

#pragma mark SEARCH
/* Searches for a WORD matching a provided string in a BST Tree */
WORD* searchBST(BST *tree, char *word) {
    // Create a WORD struct for comparison
    WORD *tmp = newWord(word, NULL);
    
    // Run search from root
    return searchBSTNode(tree->root, tmp);
}

/* Searches for a WORD matching a provided string in a BST Tree, Recursive search */
static WORD* searchBSTNode(BSTNode *currentNode, WORD *word) {
    int compareResult = compareWord(word, currentNode->word);
    
    if (compareResult == EQUAL) {
        // Update word
        return currentNode->word;
    } else if (compareResult < EQUAL) {
        if (currentNode->leftChild != NULL) {
            // Recurse
            return searchBSTNode(currentNode->leftChild, word);
        }
    } else  if (compareResult > EQUAL) {
        if (currentNode->rightChild != NULL) {
            // Else, Continue to decend to the RIGHT
            return searchBSTNode(currentNode->rightChild, word);
        }
    }
    return NULL;
}

#pragma mark DELETION
/* Sets a lazy delete flag inside a BSTNode */
int lazyDeleteBST(BSTNode *node) {
    node->isVisible = FALSE;
    return SUCCESS;
}
/* Clears a lazy delete flag inside a BSTNode */
int reverseLazyDeleteBST(BSTNode *node) {
    node->isVisible = TRUE;
    return SUCCESS;
}


#pragma mark TRAVERSAL

#pragma mark LOGGING
/* Prints a Tree to the Command Line */
void inOrderPrintBST(BST *tree) {
    inOrderPrintBSTNodes(tree->root);
}

/* Prints a Tree to the Command Line using In Order Recursion */
void inOrderPrintBSTNodes(BSTNode *node) {
    if (node != NULL) {
        if (node->leftChild) inOrderPrintBSTNodes(node->leftChild);
        printWord(node->word, MAX_WORD, maxPageDigit, maxLineDigit);
        if (node->rightChild) inOrderPrintBSTNodes(node->rightChild);
    }
}

/* Constructs a string representing nodes in order */
char* inOrderStringBST(BST *tree, long wordFrameSize, int maxPageDigits, int maxLineDigits) {
    char *str = malloc( sizeof(char) * MAX_CHARS_IN_REPORT );
    str[0]='\0';
    
    if (tree->root == NULL) {
        return NULL;
    }
    
    return inOrderStringBSTNodes(tree->root, str, wordFrameSize, maxPageDigits, maxLineDigits);
}

/* Constructs a string representing nodes in order using In Order Recursion */
char* inOrderStringBSTNodes(BSTNode *node, char* str, long wordFrameSize, int maxPageDigits, int maxLineDigits) {
    if (node->leftChild != NULL) inOrderStringBSTNodes(node->leftChild, str, wordFrameSize, maxPageDigits, maxLineDigits);
    
    // Construct Word String
    char *word = wordString(node->word, wordFrameSize, maxPageDigits, maxLineDigits);
    
    // Check if the Length doesn't exceed the limits of the destination
    long wordStrLength = strlen(word) + 1;
    long strLength = strlen(str) + 1;
    long maxLength = strLength + wordStrLength;
    
    if(DEBUG_NODE_TO_STRING) printf("maxLength = strLength + wordStrLength: %ld = %ld + %ld\n", maxLength, strLength, wordStrLength);
    
    strcat(str, word);
    free(word);
    
    if (node->rightChild != NULL) inOrderStringBSTNodes(node->rightChild, str, wordFrameSize, maxPageDigits, maxLineDigits);
    
    return str;
}

/* Writes a string representing nodes in order to a file */
/*
int writeTree(FILE *fp, BST *tree, int wordFrameSize, int maxPageDigits, int maxLineDigits) {
    return writeNode(fp, tree->root, wordFrameSize, maxPageDigits, maxLineDigits);
}

int writeNode(FILE *fp, BSTNode *node, int wordFrameSize, int maxPageDigits, int maxLineDigits) {
    int success;
    if (node == NULL) return SUCCESS;
    
    if (node->leftChild != NULL) success = writeNode(fp, node->leftChild, wordFrameSize, maxPageDigits, maxLineDigits);
    
    if (node != NULL) success = writeWord(fp, node->word, wordFrameSize, maxPageDigits, maxLineDigits);
    
    if (node->leftChild != NULL) success = writeNode(fp, node->rightChild, wordFrameSize, maxPageDigits, maxLineDigits);
    return success;
}
*/

#pragma mark TESTING
/* Generates a BST of Words from an array of Strings for testing purposes */
BST* generateBST(int numbOfInserts, char* wordArr[SIZE]) {
    BST *tmp = newBST();
    
    for (int i = 0; i < numbOfInserts; i++) {
        // Insert A few nodes
        WORD *word = newWord(wordArr[i % SIZE], newWordLocation(i,i,i));
        insertBST(tmp, word);
    }
    
    return tmp;
}

