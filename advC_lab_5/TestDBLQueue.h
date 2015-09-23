//
//  testQueue.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/8/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_TestDBLQueue_h
#define advC_lab_5_TestDBLQueue_h

#include "WordReportConstants.h"
#include "DoubleLinkedQueue.h"

// Runs all cases
int testDBLQueue(int verboseMode);

// Test Case Categories
int testDBLQueuePush(DBLQueue *queue, int verboseMode);
int testDBLQueuePop(DBLQueue *queue, int verboseMode);

// Convenience Methods
DBLQueue* generateDBLQueue();
WORD_LOCATION* generateWordLocation(long randomNumber);

#endif
