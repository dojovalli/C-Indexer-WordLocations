//
//  WordLocation.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/8/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_WordLocation_h
#define advC_lab_5_WordLocation_h

#include "WordReportConstants.h"

// Define Struct
typedef struct WordLocation WORD_LOCATION;
struct WordLocation {
    // Data
    long page;
    long pageLine;
    long fileLine;
};

// FUNCTIONS
// INITIALIZATION
#pragma mark INITIALIZATION
WORD_LOCATION* newWordLocation(long page, long pgLine, long fLine);
WORD_LOCATION* newFileWordLocation(long fileLine);

#pragma mark DESTRUCTION
void freeWordLocation(WORD_LOCATION *loc);

#pragma mark EQUALITY
int equalWordLocation(WORD_LOCATION *loc1, WORD_LOCATION *loc2);
int compareWordLocation(WORD_LOCATION *loc1, WORD_LOCATION *loc2);


// FUNCTIONS
// CONVENIENCE
void printWordLocation(WORD_LOCATION *loc, int maxPageDigits, int maxLineDigits);
char* wordLocationString(WORD_LOCATION *loc, int maxPageDigits, int maxLineDigits);


#endif
