//
//  WordCount.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/7/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_WordReport_h
#define advC_lab_5_WordReport_h

#define DEFAULT_PAGE_SIZE 50
#define DEFAULT_LINE_SIZE 25

#include "WordReportConstants.h"
#include "BinarySearchTree.h"
#include "DoubleLinkedQueue.h"

// DECLARE STRUCTS
#pragma mark WordReport Struct
typedef struct WordReport WORD_REPORT;
struct WordReport {
    char* filepath; // Path to the File to Parse
    
    // Processing Definitions
    int linesPerPage;       // Defines Page Size
    int wordsPerLine;       // Defines Line Size
    
    // Summary
    long totalFileLines;    // total Lines in Original File Format
    long totalWords;         // Total Words in file
    long totalLines;         // Total lines of file
    long totalPages;         // Total Pages of file
    long longestWordSize;    // Stores Longest Word Size
    long longestInvalidSize;
    
    // Processing
    long currentPage;        // Tracks Page
    long currentLine;        // Tracks Line
    long currentWordInLine; // Tracks the position of a word in the current line
    char* currentWord;      // Tracks Word
    
    // Storage
    BST *validWordTree;           // Stores Pointer to BinarySearchTree containing VALID WORDS
    BST *invalidWordTree;         // Stores Pointer to the BinarySearchTree containing INVALID WORDS
    
    // Output Formatting
    DBLQueue *formattedOutput;
};


#pragma mark INITIALIZATION
WORD_REPORT* newWordReport(char *filepath, int linesPerPage, int wordsPerLine);

#pragma mark DESTRUCTION
void freeWordReport(WORD_REPORT *wr);

// FUNCTIONS
#pragma mark REPORTS
char* formattedOutputString(WORD_REPORT *wr);
int formattedOutputFile(FILE *fp, WORD_REPORT *wr);
char* writeReport(WORD_REPORT *report);
int outputWordReport(FILE* fp, WORD_REPORT *wr);
int outputReportFile(WORD_REPORT *wr, char *outputFilename);

#pragma mark THREADING
int runWordReport(char *inputFilepath, char* outputFilepath, int isVerbose);

#pragma mark VALIDATION
int validateWord(char* word);

#pragma mark GENERATION
char* timestamp();

#pragma mark PROCESSING
void processFile(WORD_REPORT *wr);
void processLine(WORD_REPORT *wr, char *line, char *tokens);
char* insertFormatQueue(WORD_REPORT *wr, char *insertion);
void calculatePosition(WORD_REPORT *wr);

// Helpers
//void trim(char* str);
//char* convertToLower(char *str);
long max(long numbA, long numbB);
int searchWord(char *word, char *invalidCharList);
//int matchChar(char *word, long index, char *tokens);
//int matchLastChar(char *word, char *tokens);
//void trimEnd(char* str, char *trimChars);




#endif
