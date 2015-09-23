//
//  Word.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/7/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_Word_h
#define advC_lab_5_Word_h

#include "DoubleLinkedQueue.h"
#include "WordReportConstants.h"


// Pneumonoultramicroscopicsilicovolcanoconiosis
// Source: http://en.wikipedia.org/wiki/Longest_word_in_English

// DEFINE
typedef struct WordList WORD;
struct WordList {
    char *word;   // Word
    long count;                  // Frequency - counts every occorence
    
    // Storage - Stores a Word Location, only unique (not same page/line)
    DBLQueue *uniqueLocationQueue;
};

#pragma mark INITIALIZATION
WORD* newWord(char *word, WORD_LOCATION *loc);
WORD* newDefaultWord(char *word);
WORD* newDefaultWord();

#pragma mark DESTRUCTION
int freeWord(WORD *word);

#pragma mark ACCESSORS
int mergeWord(WORD *dest, WORD *merger);

#pragma mark COMPARISON
int  compareWord(WORD *word1, WORD *word2);

#pragma mark STRING PROCESSING
void printWord(WORD *word, long wordFrameSize, int maxPageDigits, int maxLineDigits);
char* wordString(WORD *word, long wordFrameSize, int maxPageDigits, int maxLineDigits);

#pragma mark FILE OUTPUT
int writeWord(FILE *fp, WORD *word, long wordFrameSize, int maxPageDigits, int maxLineDigits);


#endif
