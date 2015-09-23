//
//  DoubleLinkedQueue.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/8/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_DoubleLinkedQueue_h
#define advC_lab_5_DoubleLinkedQueue_h

#include "WordReportConstants.h"
#include "WordLocation.h"



// TYPEDEFS
typedef struct DoubleLinkQueueNode DBLQNode;
typedef struct DoubleLinkQueue DBLQueue;

// Struct Implementation
#pragma mark STRUCTS
struct DoubleLinkQueueNode {
    // Pointers to next node
    DBLQNode *next;
    DBLQNode *prev;
    
    // Data
    void *data;
};

struct DoubleLinkQueue {
    // Pointers
    DBLQNode *sentinel;
    DBLQNode *head;
    DBLQNode *tail;
    
    // Properties
    long count;
};



// INTERFACE
#pragma mark INTERFACE
// DBLQNode - Initialization
DBLQNode* newExplicitDBLQNode(void *data, DBLQNode *next, DBLQNode *prev);
DBLQNode* newDBLQNode(void *data);

#pragma mark INITIALIZATION
// DBLQueue - Initialization
DBLQueue* newDBLQueue();

#pragma mark DESTRUCTION
int freeDBLQueue(DBLQueue *queue);
int freeDBLQNode(DBLQNode *node);


#pragma mark QUERYING
int isEmpty(DBLQueue *queue);
long size(DBLQueue *queue);

#pragma mark INSERTION/RETREIVAL
// Insertion/Retreival
DBLQNode* popNode(DBLQueue *queue); // Returns the first item of the Queue
void* pop(DBLQueue *queue);
void push(DBLQueue *queue, void *data);
void pushNode(DBLQueue *queue, DBLQNode *node); // Places a new node at the end of the Queue

// Logging
#pragma mark STRING PROCESSING
void printDBLQNode(DBLQNode *node, int maxPageDigits, int maxLineDigits);
void printQueue(DBLQueue *queue, int maxPageDigits, int maxLineDigits);
char* queueString(DBLQueue *queue, int maxPageDigits, int maxLineDigits);
char* queueDelimeterString(DBLQueue *queue, char* delimeter);
int queueDelimeterFile(FILE* fp, DBLQueue *queue, char* delimeter);

#pragma mark FILE PROCESSING
int writeQueue(FILE *fp, DBLQueue *queue, int maxPageDigits, int maxLineDigits);

#endif
