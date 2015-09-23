//
//  testQueue.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/8/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include "TestDBLQueue.h"
#include "WordLocation.h"
#include "DoubleLinkedQueue.h"



int testDBLQueue(int verboseMode) {
    // Test Run Stats
    int totalFailers = 0;
    int failedCase = 0;
    
    // Shared Queue
    DBLQueue *queue = generateDBLQueue(10); //= newDBLQueue();
    
    /**/
    if ( (failedCase = testDBLQueuePush(queue, verboseMode)) > SUCCESS ) {
        // Case Failed
        printf("DBLQueue - push() FAILED: %d", failedCase);
        totalFailers++;
    }
     
    //printQueue(queue, maxPageDigit, maxLineDigit);
    
    if ( (failedCase = testDBLQueuePop(queue, verboseMode)) > SUCCESS ) {
        // Case Failed
        printf("DBLQueue - pop() FAILED: %d", failedCase);
        totalFailers++;
    }
    
    return failedCase;
}

#pragma mark TESTCASES
// Test Case Categories
int testDBLQueuePush(DBLQueue *queue, int verboseMode) {
    if (verboseMode == TRUE) printf("Running Case: testDBLQueuePush\n");
    int failedCase = SUCCESS;

    // Print the Queue
    printQueue(queue, maxPageDigit, maxLineDigit);
    
    return failedCase;
}

int testDBLQueuePop(DBLQueue *queue, int verboseMode) {
    printf("Initial size of queue: %ld\n", queue->count);
    // While the queue is not empty
    while ( ! isEmpty(queue) ) {
        // Pop and log
        printDBLQNode( popNode(queue), maxPageDigit, maxLineDigit);
        printf("Remaining Elements: %ld\n\n", size(queue));
    }
    
    printf("All of the Items from the Queue have been successfully popped!\n");
    
    return SUCCESS;
}

#pragma mark CONVENIENCE
DBLQueue* generateDBLQueue(long queueLength) {
    DBLQueue *tmp = newDBLQueue();
    
    for (long i = 0; i < queueLength; i++) { push(tmp, generateWordLocation(i)); }
    
    return tmp;
}

WORD_LOCATION* generateWordLocation(long randomNumber) {
    return newWordLocation((randomNumber / 3 + 1),                  randomNumber % 3 + 1, randomNumber);
}