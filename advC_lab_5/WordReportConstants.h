//
//  WordReportConstants.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/19/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_WordReportConstants_h
#define advC_lab_5_WordReportConstants_h

// CONSTANTS
#define         TRUE                        1
#define         FALSE                       0


// TOKENS
#define TOKENS " "
#define VALID_CHARACTERS "abcdefghijklmnopqrstuvwxyz1234567890"
#define PUNCTUATION ".,?!;:\""
#define INVALID_CHARACTERS "#$%^&*()_-+=><"
#define POSSESSIVE "'"
#define HYPHENATION "-"


// FLAGS
#define         EQUAL                       0
#define         SUCCESS                     0
#define         FAILED                      1

// ERROR FLAGS
#define         OUT_OF_MEMORY               1
#define         OPEN_FOR_READ_ERROR         2
#define         OPEN_FOR_WRITE_ERROR        3
#define         NULL_PROCESSING             5

// DEBUG
// WordReport
    #define     DEBUG_PROCESS_FILE          FALSE
    #define     DEBUG_PROCESS_LINE          FALSE
    #define     DEBUG_VALIDATION            FALSE
    #define     DEBUG_MATCH_LAST            FALSE
    #define     DEBUG_FORMAT_OUTPUT         FALSE

// BinarySearchTree
    #define     DEBUG_INSERTION             FALSE
    #define     DEBUG_FREE_BST              FALSE
    #define     DEBUG_NODE_TO_STRING        FALSE

// Word
    #define     DEBUG_FREE_WORD             FALSE
    #define     DEBUG_MERGE                 FALSE

// DBLQueue
    #define     DEBUG_CONSTRUCTOR           FALSE
    #define     DEBUG_FREE_DBLQ             FALSE

// WordLocation
#define         DEBUG_FREE                  FALSE
#define         DEBUG_FREE_LOC              FALSE

// TESTING
#define         BUFFER_SIZE                 5000
#define         maxPageDigit                3
#define         maxLineDigit                2
#define         SIZE                        10
#define         MAX_WORD                    15
#define         FRAME_SIZE                  15
#define         MAX_WORD_SIZE               100 // The longest word found in most major English Dictionaries


// TESTING - Report Constants
#define         MAX_PAGE_OUTPUT_CHARS       9999999999999999
#define         MAX_CHARS_IN_REPORT         999999999999
#define         REPORT_MAX_CHARACTERS       999999
#define         MAX_QUEUE_STRING_SIZE       999999

// TESTING - Input Values
#define         VERBOSE_MODE                TRUE
#define         TEST_WORD                   "insertTest"

// MACROS
#define         PRINT_BUFFER                printf("\n");

// CLANG
#pragma clang diagnostic ignored            "-Wunused-function"

#endif
