//
//  DoubleLinkedQueue.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/8/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DoubleLinkedQueue.h"
#include "StringMaster.h"


// INITIALIZATION
#pragma mark DBLQNode - INITIALIZATION
/* Initializes a DBLQNode with explicite settings, used to create custom SENTINEL NODES */
DBLQNode* newExplicitDBLQNode(void *loc, DBLQNode *next, DBLQNode *prev) {
    DBLQNode *tmp = (DBLQNode*) malloc( sizeof(DBLQNode) );
    
    // If tmp == NULL, OUT OF MEMORY
    if (tmp == NULL) {
        // Inform User
        printf("The System has use all memory allocated for the program!");
        perror("ERROR: ");
        exit(OUT_OF_MEMORY);
    }
    
    // Initialize
    tmp->next = next;
    tmp->prev = prev;
    tmp->data = loc;
    
    return tmp;
}

/* Initializes a DBLQNode with a provided location, pointers are initialized to NULL */
DBLQNode* newDBLQNode(void *loc) {
    DBLQNode *tmp = (DBLQNode*) malloc( sizeof(DBLQNode) );
    
    // If tmp == NULL, OUT OF MEMORY
    if (tmp == NULL) {
        // Inform User
        printf("The System has use all memory allocated for the program!");
        perror("ERROR: ");
        exit(OUT_OF_MEMORY);
    }
    
    tmp->data = loc;
    tmp->next = NULL;
    tmp->prev = NULL;
    
    return tmp;
}

#pragma mark DBLQueue - INITIALIZATION
/* Initializes a DBLQueue and creates SENTINEL node */
DBLQueue* newDBLQueue() {
    DBLQueue *tmp = (DBLQueue*) malloc( sizeof(DBLQueue) );
    
    if ( tmp == NULL ) {
        // Memory Full
        printf("The System has used all memory allocate for the program!");
        perror("ERROR: ");
        exit(OUT_OF_MEMORY);
    }
    
    // Initialize
    tmp->count = 0;
    tmp->sentinel = newExplicitDBLQNode(NULL,NULL,NULL);
    tmp->head = NULL;
    tmp->tail = NULL;
    
    if (DEBUG_CONSTRUCTOR) {
        printDBLQNode(tmp->sentinel, maxPageDigit, maxLineDigit);
    }
    
    return tmp;
}

#pragma mark DBLQueue - DESTRUCTION
/* Frees all memory associated with a DBLQueue */
int freeDBLQueue(DBLQueue *queue) {
    // Start From the tail and work towards the head
    DBLQNode *newTail = queue->sentinel->prev;
    DBLQNode *toRemove = newTail;
    
    // Free all nodes
    while (newTail != NULL) {
        // Save the point to the previous node (one preceding newTail)
        newTail = toRemove->prev;
        if (DEBUG_FREE == TRUE) {
            if (toRemove->data != NULL && DEBUG_FREE && DEBUG_FREE_DBLQ ) printf("free DBLQNode - %s\n", wordLocationString(toRemove->data, 2, 2));
        }
        if (toRemove != NULL) freeDBLQNode(toRemove);
        toRemove = newTail;
    }
    
    // Zero out values of DBLQueue
    queue->count = 0;
    queue->head = NULL;
    queue->sentinel = NULL;
    queue->tail = NULL;
    
    // Free the DBLQueue
    free(queue);
    
    return SUCCESS;
}

#pragma mark DBLQNode - DESTRUCTION
/* Frees a DBLQNode and all associated memory */
int freeDBLQNode(DBLQNode *node) {
    // Set the pointers to NULL to clean memory
    node->next = NULL;
    node->prev = NULL;
    // Free WORD_LOCATION
    if (node->data != NULL) freeWordLocation(node->data);
    return SUCCESS;
}

#pragma mark QUERYING
/*  Returns 1, if the queue is EMPTY
 *  Returns 0, if the queue is NOT EMPTY
 */
int isEmpty(DBLQueue *queue) {
    return queue->count == 0;
}

/* Returns the size of the queue
 */
long size(DBLQueue *queue) {
    return queue->count;
}

// INSERTION/RETREIVAL
#pragma mark INSERTION/RETREIVAL
/* Pushes/Inserts a WORD_LOCATION into a DBLQueue */
void push(DBLQueue *queue, void *loc) {
    pushNode(queue, newDBLQNode(loc));
}

/* Inserts a Node at the back of the Queue
 */
void pushNode(DBLQueue *queue, DBLQNode *node) {
    // Conceptially, the newTail == node
    // Move to the Previous from the Sentinel
    DBLQNode *oldTail = queue->sentinel->prev;
    // Check if empty
    if (oldTail == NULL) {
        // Insert at the first position
        queue->head = queue->tail = queue->sentinel->next = queue->sentinel->prev = node;
        node->next = node->prev = queue->sentinel;
    } else {
        // Update the Old Tail to point to the newTail
        oldTail->next = node;
        
        // Update New Pointers
        node->prev = oldTail;
        node->next = queue->sentinel;
        
        // Update Sentinel to point to the newTail
        queue->tail = queue->sentinel->prev = node;
    }
    
    // Increment the Count
    queue->count++;
}

/* Retreives the Node at the front of the Queue
 */
DBLQNode* popNode(DBLQueue *queue) {
    // If pop node is the Sentinel, the list is empty
    if ( queue->count == 0 ) { return NULL; }
    
    // Move to the front of the queue
    DBLQNode *popNode = queue->sentinel->next;
    
    // Update the sentinel to point to the popNode->next
    queue->head = queue->sentinel->next = popNode->next;
    if (popNode->next == queue->sentinel) {
        queue->head = queue->tail = queue->sentinel->next = queue->sentinel->prev = NULL;
    }
    
    // Deduce the count
    queue->count--;
    
    return popNode;
}

/* Pops/Removes/Returns a WORD_LOCATION from the Front of a DBLQueue */
void* pop(DBLQueue *queue) {
    return popNode(queue)->data;
}

#pragma mark LOGGING
/* Prints a DBLQNode to the Command Line - Used for testing purposes */
void printDBLQNode(DBLQNode *node, int maxPageDigits, int maxLineDigits) {
    printf("DBLQNode\nnext: %p\nprev: %p\n", node->next, node->prev);
    printf("location: ");
    if (node->data != NULL) printWordLocation(node->data, maxPageDigits, maxLineDigits);
    else printf("NULL");
    printf("\n");
}

/* Prints a DBLQueue in order from FRONT -> BACK */
void printQueue(DBLQueue *queue, int maxPageDigits, int maxLineDigits) {
    printf("%s", queueString(queue, maxPageDigits, maxLineDigits));
    return;
}

/* Constructs a String representing a a DBLQueue in order from FRONT -> BACK */
char* queueString(DBLQueue *queue, int maxPageDigits, int maxLineDigits) {
    
    // Get the Node
    DBLQNode *nextNode = queue->head;
    char str[MAX_QUEUE_STRING_SIZE] = "";
    
    // If Null, inform user
    if (nextNode->data == NULL) { strcpy(str, "The Queue is empty!"); }
    
    // Iterate Forward, printing nodes
    while (nextNode->data != NULL) {
        // Build string
        strcat(str, wordLocationString(nextNode->data, maxPageDigits, maxLineDigits));
        strcat(str, "\t");
        // Move to next Node
        nextNode = nextNode->next;
    }
    
    // Allocate the memory of the size of the queue
    strcat(str, "\n");  // End Line
    
    return allocateString(str);
}

/* Constructs a String representing a a DBLQueue in order from FRONT -> BACK using formatter */
char* queueDelimeterString(DBLQueue *queue, char* delimeter) {
    
    // Get the Node
    DBLQNode *nextNode = queue->head;
    char str[MAX_QUEUE_STRING_SIZE] = "";
    
    // If Null, inform user
    if (nextNode->data == NULL) { strcpy(str, "The Queue is empty!"); }
    
    // Iterate Forward, printing nodes
    while (nextNode->data != NULL) {
        // Build string
        strcat(str, nextNode->data);
        strcat(str, allocateString(delimeter));
        // Move to next Node
        nextNode = nextNode->next;
    }
    
    return allocateString(str);
}

/* Constructs a String representing a a DBLQueue in order from FRONT -> BACK using formatter */
int queueDelimeterFile(FILE* fp, DBLQueue *queue, char* delimeter) {
    
    // Get the Node
    DBLQNode *nextNode = queue->head;
    char str[MAX_QUEUE_STRING_SIZE] = "";
    
    // If Null, inform user
    if (nextNode->data == NULL) { strcpy(str, "The Queue is empty!"); }
    
    // Iterate Forward, printing nodes
    while (nextNode->data != NULL) {
        // Build string
        fprintf(fp, "%s", nextNode->data);
        fprintf(fp, "%s", delimeter);
        // Move to next Node
        nextNode = nextNode->next;
    }
    
    return SUCCESS;
}

/* Outputs a Queue in String Format to a File */
int writeQueue(FILE *fp, DBLQueue *queue, int maxPageDigits, int maxLineDigits) {
    // Get the Node
    DBLQNode *nextNode = queue->head;
    char str[MAX_QUEUE_STRING_SIZE];
    
    // If Null, inform user
    if (nextNode->data == NULL) {
        strcpy(str, "The Queue is empty!");
    }

    // Iterate Forward, printing nodes
    while (nextNode->data != NULL) {
        // Build string
        strcat(str, wordLocationString(nextNode->data, maxPageDigits, maxLineDigits));
        strcat(str, "\t");
        // Move to next Node
        nextNode = nextNode->next;
    }

    char *output = allocateString(str);
    
    // Write String to file
    return fprintf(fp, "%s",output);
}
