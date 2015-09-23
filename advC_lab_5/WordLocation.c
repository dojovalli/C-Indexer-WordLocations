//
//  WordLocation.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/8/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WordLocation.h"

// ERROR CONSTANTS
#define OUT_OF_MEMORY 1

// CONSTANTS
#define INVALID_PAGE -1
#define INVALID_LINE -1

#pragma mark INITIALIZATION
/* Creates a Word Location based on the provided data
 */
WORD_LOCATION* newWordLocation(long page, long pgLine, long fLine) {
    // Initialize Pointer
    WORD_LOCATION *tmp = (WORD_LOCATION*) malloc( sizeof(WORD_LOCATION) );
    
    // If tmp == NULL, OUT OF MEMORY
    if (tmp == NULL) {
        // Inform User
        printf("The System has use all memory allocated for the program!");
        perror("ERROR: ");
        exit(OUT_OF_MEMORY);
    }
    
    // Initialize struct data
    tmp->page = page;
    tmp->pageLine = pgLine;
    tmp->fileLine = fLine;
    
    return tmp;
}


/* Creates a Default Word Location
 */
WORD_LOCATION* newFileWordLocation(long fileLine) {
    return newWordLocation(INVALID_PAGE, INVALID_LINE, fileLine);
}

#pragma mark DESTRUCTION
/* Frees a WORD_LOCATION and all associated memory */
void freeWordLocation(WORD_LOCATION *loc) {
    if (loc != NULL && (DEBUG_FREE && DEBUG_FREE_LOC)) printf("freeing loc: %ld, %ld, %ld\n", loc->page, loc->pageLine, loc->fileLine);
    // Zero out values to clean memory
    loc->fileLine = loc->page = loc->pageLine = 0;
    //if (loc != NULL) free(loc);

}

#pragma mark EQUALITY
/*  Compares to WORD_LOCATIONS are equal
    Returns:    1 - TRUE/ARE EQUAL
                0 - FALSE/ARE NOT EQUAL
 */
int equalWordLocation(WORD_LOCATION *loc1, WORD_LOCATION *loc2) {
    if (loc1 == NULL || loc2 == NULL) return FALSE;
    return (loc1->page == loc2->page) && (loc1->pageLine == loc2->pageLine);
}

/*  Compares to WORD_LOCATIONS
 Returns:    - Negative if loc1 is less than loc2
 0 Zero if loc1 is equal to loc2
 + Positive if loc1 is greater than loc2
 */
int compareWordLocation(WORD_LOCATION *loc1, WORD_LOCATION *loc2) {
    if (loc1 == NULL || loc2 == NULL) {
        printf("Exception: Parameter loc1 or loc2 cannot be null!");
        perror("ERROR: ");
        exit(NULL_PROCESSING);
    }
    if (equalWordLocation(loc1, loc2) == TRUE) {
        return 0;
    }
    
    // SHORT CUT ON PAGE
    long pageEquality = loc1->page - loc2->page;
    if (pageEquality > 0) {
        // Loc1 has a higher page value
        return 1;
    } else if (pageEquality < 0) {
        // Loc2 has a higher page value
        return -1;
    }
    
    // WORD_LOCATIONS share PAGE, check lines
    long lineEquality = loc1->pageLine - loc2->pageLine;
    if (lineEquality > 0) {
        // Loc 1 has a higher line value
        return 2;
    }
    
    // Last case, Loc2->pageLine is higher
    return -2;
}

#pragma mark CONVENIENCE
/*  Prints a formatted string representing a WORD_LOCATION to the Command Line */
void printWordLocation(WORD_LOCATION *loc, int maxPageDigits, int maxLineDigits) {
    //printf("%*ld.%*ld", maxPageDigits, loc->page, maxLineDigits, loc->pageLine);
    printf("%s", wordLocationString(loc, maxPageDigits, maxLineDigits));
    return;
}

/*  Constructs a formatted string representing a WORD_LOCATION */
char* wordLocationString(WORD_LOCATION *loc, int maxPageDigits, int maxLineDigits) {
    if (loc == NULL) {
        return NULL;
    }
    int formatChars = maxPageDigits + maxLineDigits + 2; // maxPageDigits + . + maxLineDigits + \0
    long length = maxPageDigits + maxLineDigits + formatChars + 1;
    
    char *str = (char*) malloc(sizeof(char) * length);
    
    sprintf(str, "%*ld.%0*ld", maxPageDigits, loc->page, maxLineDigits, loc->pageLine);
    return str;
}

/* Outputs a formatted string representing a WORD_LOCATION to a File */
int writeWordLocation(FILE *fp, WORD_LOCATION *loc, int maxPageDigits, int maxLineDigits) {
    return fprintf(fp, "%s", wordLocationString(loc, maxPageDigits, maxLineDigits));
}