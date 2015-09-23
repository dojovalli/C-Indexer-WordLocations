//
//  Word.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/7/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StringMaster.h"
#include "Word.h"




#pragma mark INITIALIZATION
/*  Initializes a WORD struct */
WORD* newWord(char* word, WORD_LOCATION *loc) {
    WORD* tmp = (WORD*) malloc( sizeof(WORD) );
    
    if ( tmp == NULL ) {
        // Memory Full
        printf("The System has used all memory allocate for the program!");
        perror("ERROR: ");
        exit(OUT_OF_MEMORY);
    }
    
    // Initialization
    tmp->count = 1;
    tmp->uniqueLocationQueue = newDBLQueue();
    push(tmp->uniqueLocationQueue, loc);
    
    // CONSTRUCT NEW STRING
    tmp->word = allocateString(word);
    
    return tmp;
}

/*  Initializes a DEFAULT WORD struct */
WORD* newDefaultWord(char *word) {
    WORD *tmp = newWord(word, newWordLocation(1, 1, 1));
    return tmp;
}

#pragma mark DESTRUCTION
/* Handles freeing memory associated with a Word
 */
int freeWord(WORD *word) {
    // Zero out values for security/clean memory
    word->count = 0;
    
    if (DEBUG_FREE && DEBUG_FREE_WORD) {
        if (word != NULL) {
            printf("Freeing Word: %s\n", word->word);
        } else {
            printf("Attempting to free a NULL WORD*\n");
        }
    }
    // Free Members (No need to free char[], handle by free(word))
    freeDBLQueue(word->uniqueLocationQueue);
    free(word);
    return SUCCESS;
}

#pragma mark ACCESSORS
/*  Merges two word structs if the strings are equal,
    uses a variation of merge sort to sort DBLQueue of WORD_LOCATIONS
 */
int mergeWord(WORD *dest, WORD *merger) {
    
    // Only merge Words if they are the same
    if (strcmp(dest->word, merger->word) != 0) return FALSE;
    // Only merge Words if they have some nodes to merge
    if (merger->uniqueLocationQueue == NULL) {
        // Nothing to merge
        return SUCCESS;
    }

    // Setup variables
    DBLQNode *currentNode = NULL, *destSlowPtr = NULL, *destFastPtr = NULL, *next = NULL;
    int requiresInsert = TRUE;
    int comparison = 0;
    
    // Push the WordLocation
    while (!isEmpty(merger->uniqueLocationQueue)) {
        // ASSUME INSERTION
        requiresInsert = TRUE;
        currentNode = popNode(merger->uniqueLocationQueue);
        
        // Start at the Head of the Dest and Traverse
        destSlowPtr = NULL;
        destFastPtr = dest->uniqueLocationQueue->head;
        
        if (DEBUG_MERGE) {
            if (currentNode != NULL) printf("currentNode: %s\n", wordLocationString(currentNode->data,2,2));
            if (destFastPtr != NULL) printf("destFastNode: %s\n", wordLocationString(destFastPtr->data,2,2));
            if (destSlowPtr != NULL) printf("destSlowNode: %s\n", wordLocationString(destSlowPtr->data, 2, 2));
        }

        // Traverse Dest and Search for Equality
        while (destSlowPtr != dest->uniqueLocationQueue->sentinel) {
            // IF the destFastPtr has reached the Sentinel, then we can assume insertion
            if (destFastPtr == dest->uniqueLocationQueue->sentinel) {
                // The currentNode's location is less than the destFastPtr, Immediate Insert
                // Insert between the fast and slow pointers
                destFastPtr->prev = currentNode;
                destSlowPtr->next = currentNode;
                
                // Save a Reference to the next Node
                next = currentNode->next;
                
                // Update the currentNode with its new neighbors
                currentNode->prev = destSlowPtr;
                currentNode->next = destFastPtr;
                
                // Update the Count
                dest->count++;
            } else {
                comparison = compareWordLocation((WORD_LOCATION*) currentNode->data, (WORD_LOCATION*) destFastPtr->data);
            }
            if (DEBUG_MERGE) printf("comparison: %d\n", comparison);
            if ( comparison == 0 ) {
                // They are equal, no insertion
                next = popNode(merger->uniqueLocationQueue);
                break;
            } else if (comparison < 0) {
                // The currentNode's location is less than the destFastPtr, Immediate Insert
                // Insert between the fast and slow pointers
                destFastPtr->prev = currentNode;
                destSlowPtr->next = currentNode;
                
                // Save a Reference to the next Node
                next = currentNode->next;
                
                // Update the currentNode with its new neighbors
                currentNode->prev = destSlowPtr;
                currentNode->next = destFastPtr;
                
                // Update the Count
                dest->count++;
            } else
            
            // Move iterate the pointers to the next nodes
            destSlowPtr = destFastPtr;
            destFastPtr = destFastPtr->next;
        }
        
        // Move to next Node of Merger
        currentNode = next;
    }
    
    return TRUE;
}



#pragma mark CONVENIENCE
/*  Prints a WORD struct to the Command Line */
void printWord(WORD *word, long wordFrameSize, int maxPageDigits, int maxLineDigits) {
    printf("%s", wordString(word, wordFrameSize, maxPageDigit, maxLineDigit));
    return;
}

/*  Constructs a string representing a WORD struct */
char* wordString(WORD *word, long wordFrameSize, int maxPageDigits, int maxLineDigits) {
    char str[MAX_QUEUE_STRING_SIZE] = "";
    char *queueStr = queueString(word->uniqueLocationQueue, maxPageDigits, maxLineDigits);

    // Format
    sprintf(str, "%3.0ld %*s\t%s", word->count, (int) wordFrameSize, word->word, queueStr);
    free(queueStr);

    return allocateString(str);
}

/*  Writes a WORD struct to a file in WORD struct format */
int writeWord(FILE *fp, WORD *word, long wordFrameSize, int maxPageDigits, int maxLineDigits) {
    char *queueStr = queueString(word->uniqueLocationQueue, maxPageDigits, maxLineDigits);
    
    // Format
    int success = fprintf(fp, "%3.0ld %*s\t%s", word->count, (int) wordFrameSize, word->word, queueStr);
    free(queueStr);
    return success;
}

/*  Compares two WORD structs
    Returns:    - Negative if word1 less than word2
                0 Zero if word1 equals word2
                + Positive if word1 greater than word2
 */
int compareWord(WORD *word1, WORD *word2) {
    return strcmp(word1->word, word2->word);
}