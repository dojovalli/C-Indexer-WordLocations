//
//  WordCount.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/7/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "StringMaster.h"
#include "WordReport.h"


#pragma mark INITIALIZATION
WORD_REPORT* newWordReport(char *filepath, int linesPerPage, int wordsPerLine) {
    WORD_REPORT* tmp = malloc(sizeof(WORD_REPORT));
    
    if (tmp == NULL) {
        printf("Out of Memory! There is not enough memory to create a new WORD_REPORT.\n");
        perror("ERROR: ");
        exit(OUT_OF_MEMORY);
    }
    
    // Initialize
    tmp->filepath = filepath;
    tmp->linesPerPage = linesPerPage;
    tmp->wordsPerLine = wordsPerLine;
    // Initial STATS Values to 0
    tmp->longestWordSize = 1;
    tmp->longestInvalidSize = 1;
    tmp->totalFileLines = 0;
    tmp->totalPages = 0;
    tmp->totalLines = 0;
    tmp->totalWords = 0;
    // Initial Tracking Values to 0
    tmp->currentPage = 0;
    tmp->currentLine = 0;
    tmp->currentWord = 0;
    // Create a Tree for Storage
    tmp->validWordTree = newBST();
    tmp->invalidWordTree = newBST();
    // Queue for Custom Document Output
    tmp->formattedOutput = newDBLQueue();
    return tmp;
}

#pragma mark DESTRUCTION
/* Frees a WORD_REPORT struct and all internal pointers
 */
void freeWordReport(WORD_REPORT *wr) {
    // Clean Memory/Zero Values for Security
    wr->filepath = 0;
    wr->linesPerPage = 0;
    wr->wordsPerLine = 0;
    wr->longestWordSize = 0;
    wr->totalFileLines = 0;
    wr->totalPages = 0;
    wr->totalLines = 0;
    wr->totalWords = 0;
    wr->currentPage = 0;
    wr->currentLine = 0;
    wr->currentWord = 0;
    
    // Free the BST
    if (wr->validWordTree != NULL) freeBST(wr->validWordTree);
    wr->validWordTree = NULL;
    if (wr->invalidWordTree != NULL) freeBST(wr->invalidWordTree);
    wr->invalidWordTree = NULL;
    
    // Free Queue
    if (wr->formattedOutput != NULL) freeDBLQueue(wr->formattedOutput);
    wr->formattedOutput = NULL;
    
    // Free the WORD_REPORT
    free(wr);
    return;
}

#pragma mark RUN
int runWordReport(char *inputFilepath, char* outputFilepath, int isVerbose) {
    int success = FAILED;
    // Create a New Word Report
    WORD_REPORT *report = newWordReport(inputFilepath, 25, 10);
    
    // Process the Report
    processFile(report);

    // Print to Console if verbose
    /*
    if (isVerbose == TRUE) {
        // Test writeReport
        char *out = writeReport(report);
        printf("%s", out);
    }
     */
    
    // Output Report to file
    success = outputReportFile(report,outputFilepath);
    
    // Print the location of the output file
    printf("\nOutput Filepath: %s\n", outputFilepath);
    
    // Free Memory
    freeWordReport(report);
    
    return success;
}

#pragma mark REPORTS
// Reports
/* Formats the provided text via the output parameters in WORD_REPORT */
char* formattedOutputString(WORD_REPORT *wr) {
    // 999 pages * 80 Lines * 120 chars perline + null terminator (Estimate of Large file
    char* output = initString(999 * 80 * 120 + 1);
    
    // Print Page 1/Line 1
    if (DEBUG_FORMAT_OUTPUT) printf("\n\nCALLED formattedOutputString()\n\n");
    sprintf(output, "Page 1\nLine   1:\t ");
    strcat(output, queueDelimeterString(wr->formattedOutput, " "));
    
    return output;
}

/* Formats the provided text via the output parameters in WORD_REPORT */
int formattedOutputFile(FILE *fp, WORD_REPORT *wr) {
    
    // Print Page 1/Line 1
    if (DEBUG_FORMAT_OUTPUT) printf("\n\nCALLED formattedOutputString()\n\n");
    fprintf(fp, "Page 1\nLine   1:\t ");
    //strcat(output, queueDelimeterString(wr->formattedOutput, " "));
    //fprintf(fp, "%s", queueDelimeterString(wr->formattedOutput, " "));
    queueDelimeterFile(fp, wr->formattedOutput, " ");

    return SUCCESS;
}

/* Constructs a String representing a report on the contents/words of a file
 */
char* writeReport(WORD_REPORT *wr) {
    // Traverse the Binary Search Tree and Build a Report String
    //char report[REPORT_MAX_CHARACTERS] = "";
    char *report = malloc( sizeof(char) * REPORT_MAX_CHARACTERS);
    
    // Concatinate the Timestamp Section
    char reportTime[45] = "Report made at: ";
    strcat(reportTime, timestamp());
    strcat(reportTime, "\n");
    strcat(report, reportTime);
    
    // Concatinate the Reporst Summary
    char reportSummary[125];
    sprintf(reportSummary, "There are %ld distinct tokens, %ld pages, %d lines per page.\nThe longest token in this text has %ld characters.\n\n", wr->validWordTree->count, wr->currentPage, wr->linesPerPage, wr->longestWordSize);
    strcat(report, reportSummary);
    
    // Create a report of the validWordTree
    char* validWordTreeReport = inOrderStringBST(wr->validWordTree, wr->longestWordSize, 2, 2);
    
    // If the report is NULL, the BST contians no words
    strcat(report, "REPORT - VALID WORDS\n");
    if (validWordTreeReport == NULL) {
        char tmp[34] = "No valid words found in the file!";
        strcat(report,tmp);
    } else {
        strcat(report, validWordTreeReport);
    }
    strcat(report, "\n");
    free(validWordTreeReport);
    
    // Create a report of the validWordTree
    char* invalidWordTreeReport = inOrderStringBST(wr->invalidWordTree, wr->longestWordSize, 2, 2);
    
    // If the report is NULL, the BST contians no words
    strcat(report, "REPORT - INVALID WORDS\n");
    if (invalidWordTreeReport == NULL) {
        char tmp[40] = "No invalid words found in the file!\n";
        strcat(report,tmp);
    } else {
        strcat(report, validWordTreeReport);
    }
    strcat(report, "\n");
    free(invalidWordTreeReport);
    
    strcat(report, "TEXT FORMATTED VIA PAGES\n");
    strcat(report, formattedOutputString(wr));
    
    // Get the size of the Report string
    long reportLength = strlen(report) + 1;
    
    char *finalReport = malloc( sizeof(char) * reportLength);
    if (finalReport == NULL) {
        printf("The system has allocated all of its memory!");
        perror("ERROR: ");
        exit(OUT_OF_MEMORY);
    }
    strcpy(finalReport, report);
    
    return finalReport;
}

/* Constructs a String representing a report on the contents/words of a file
 */
int outputWordReport(FILE* fp, WORD_REPORT *wr) {
    // Traverse the Binary Search Tree and Build a Report String
    //char report[REPORT_MAX_CHARACTERS] = "";
    char *report = malloc( sizeof(char) * REPORT_MAX_CHARACTERS);
    
    // Concatinate the Timestamp Section
    char reportTime[45] = "Report made at: ";
    strcat(reportTime, timestamp());
    strcat(reportTime, "\n");
    strcat(report, reportTime);
    
    // Concatinate the Reporst Summary
    char reportSummary[125];
    sprintf(reportSummary, "There are %ld distinct tokens, %ld pages, %d lines per page.\nThe longest token in this text has %ld characters.\n\n", wr->validWordTree->count, wr->currentPage, wr->linesPerPage, wr->longestWordSize);
    fprintf(fp, "%s", reportSummary);
    
    
    // Create a report of the validWordTree
    char* validWordTreeReport = inOrderStringBST(wr->validWordTree, wr->longestWordSize, 2, 2);
    
    // If the report is NULL, the BST contians no words
    fprintf(fp, "REPORT - VALID WORDS\n");
    if (validWordTreeReport == NULL) {
        char tmp[34] = "No valid words found in the file!";
        fprintf(fp,"%s",tmp);
    } else {
        fprintf(fp, "%s", validWordTreeReport);
    }
    fprintf(fp, "\n");
    free(validWordTreeReport);
    
    // Create a report of the validWordTree
    char* invalidWordTreeReport = inOrderStringBST(wr->invalidWordTree, wr->longestWordSize, 2, 2);
    
    // If the report is NULL, the BST contians no words
    fprintf(fp, "%s", "REPORT - INVALID WORDS\n");
    if (invalidWordTreeReport == NULL) {
        char tmp[40] = "No invalid words found in the file!\n";
        fprintf(fp, "%s",tmp);
    } else {
        fprintf(fp, "%s", validWordTreeReport);
    }
    fprintf(fp, "%s", "\n");
    free(invalidWordTreeReport);
    
    fprintf(fp, "%s", "TEXT FORMATTED VIA PAGES\n");
    formattedOutputFile(fp, wr);
    
    return SUCCESS;
}

/* Outputs a WORD_REPORT in its String representation to the provided filepath
 */
int outputReportFile(WORD_REPORT *wr, char *outputFilename) {
    // Generate a Name using the filepath and a Timestamp
    //char outFile[100];
    //strcpy(outFile, wr->filepath);
    // Generate Timestamp
    //strcat(outFile, timestamp());

    // Start with a Fresh file
    remove(outputFilename);
    
    // Create a File pointer
    FILE *output = fopen(outputFilename, "a");
    
    if (output == NULL) {
        printf("There was a problem while trying to output the file!\n");
        perror("ERROR: ");
        exit(OPEN_FOR_WRITE_ERROR);
    }
    
    // Write the report to the file
    //fprintf(output, "%s", writeReport(wr));
    outputWordReport(output, wr);
    
    // Close File Pointer
    fclose(output);
    
    return SUCCESS;
}

#pragma mark VALIDATION
// Validation
/* Validates a String based on the Punctuation and Invalid Characters
 */
int validateWord(char* word) {
    long lastCharPos = strlen(word) - 1;
    // if the Word does NOT end with a possessive character: TRUE
    if ( matchChar(word, 0, VALID_CHARACTERS) == FALSE )    return FALSE;
    if ( matchChar(word, lastCharPos,POSSESSIVE) == TRUE )  return FALSE;
    if ( matchLastChar(word, HYPHENATION) == TRUE )         return FALSE;
    if ( matchChar(word, 0, INVALID_CHARACTERS) == TRUE )   return FALSE;
    if ( matchChar(word, lastCharPos, INVALID_CHARACTERS) == TRUE )   return FALSE;
    
    // if the Word ends with a punctuation: TRUE
    if ( matchLastChar(word, PUNCTUATION) == TRUE ) trimEnd(word, PUNCTUATION);
    
    return TRUE;
}

#pragma mark GENERATION
/* Generates a Timestamp using the Systems Clock  */
char* timestamp() {
    time_t  timeval;  // time
    char   *chtime = malloc(30 * sizeof(char));   // ctime
    
    time(&timeval);
    chtime  = ctime(&timeval);
    return chtime;
}

#pragma mark PROCESSING
// Processing
/*  Handles Looping Mechanisms for Processing an Input File.
    Uses a WORD_REPORT to track words, lines, and page counts in
    addition to other file statics
 */
void processFile(WORD_REPORT *wr) {
    // Open the file
    printf("File For Report: %s\n", wr->filepath);
    FILE *fileForReport = fopen(wr->filepath, "r");
    
    // Check if opened properly
    if (fileForReport == NULL) {
        printf("There was an error opening: %s", wr->filepath);
        perror("ERROR: ");
        exit(OPEN_FOR_READ_ERROR);
    }
    
    // The file opened succesfully, ready for processing
    char *line = malloc(BUFFER_SIZE * sizeof(char));
    
    // Get and Process a line from the file at a time
    while (fgets(line, BUFFER_SIZE, fileForReport) != NULL)
    {
        // Remove the NewLine Character
        trim(line);
        // Increment the WR line count
        wr->totalFileLines++;
        if (DEBUG_PROCESS_FILE == TRUE) printf("Line %3.0ld: %s\n", wr->totalFileLines, line);
        
        // Process the Line
        processLine(wr, line, TOKENS);
    }
    
    // Add the final newline to the output
    insertFormatQueue(wr, allocateString("\n"));
    
    fclose(fileForReport);
    if (line)
        free(line);
}

/*  Handles parsing a line Word by Word,
    Updating the contents of the WORD_REPORT struct during processing */
void processLine(WORD_REPORT *wr, char *line, char *tokens) {
    char *word;
    if (DEBUG_PROCESS_LINE == TRUE) printf ("Splitting string \"%s\" into tokens:\n",line);
    word = strtok (line, tokens);
    while ( word != NULL )
    {
        
        // Increment the totalWords
        wr->totalWords++;
        
        // Adjust Tracking Variables
        calculatePosition(wr);
        
        // Add the word to the Formatted Output Queue
        word = insertFormatQueue(wr, word);
        
        // Log for debugging
        if (DEBUG_PROCESS_LINE == TRUE) printf ("Page/Line/Word[%ld/%ld/%ld]: %s\n", wr->currentPage, wr->currentLine, wr->currentWordInLine, word);
        
        // Conver to Lower Case before insert
        word = convertToLower(word);
        //trimEnd(word);
        
        // Only insert if the word is valid
        
        if (validateWord(word) == TRUE) {
            if(DEBUG_VALIDATION == TRUE) printf("VALID WORD: %s\n", word);
            // Check to See if it is the largest word in the file
            wr->longestWordSize = max(wr->longestWordSize, strlen(word));
            
            // Insert the Word into the Binary Search Tree
            insertBST(wr->validWordTree, newWord(word, newWordLocation(wr->currentPage, wr->currentLine, wr->totalFileLines)));
        } else {
            if (DEBUG_VALIDATION == TRUE) printf("INVALID WORD: %s\n", word);
            // Check to See if it is the largest word in the file
            wr->longestInvalidSize = max(wr->longestInvalidSize, strlen(word));
            
            // Insert the Word into the Binary Search Tree
            insertBST(wr->invalidWordTree, newWord(word, newWordLocation(wr->currentPage, wr->currentLine, wr->totalFileLines)));
        }
        
        // Get the next word
        word = strtok (NULL, tokens);
    }
    
    /* NOT REQUIRED FOR ASSIGNMENT - MORE REALISTIC OUTPUT FORMATING IN FUTURE
    // Drops line for newline char present in file
    forceLayout(wr);
    char *layoutLine = initString(15);
    
    sprintf(layoutLine, "Line: %*d", wr->currentLine);
    // Add the newline to the Formatted Output Queue
    insertFormatQueue(wr, allocateString());
     */
    
    return;
}

/* Inserts Words into WORD_REPORT Format Queue for output of document in final report */
char* insertFormatQueue(WORD_REPORT *wr, char *insertion) {
    // Use Word report to track if the Page/Line have changed
    
    if (wr->totalWords % (wr->wordsPerLine * wr->linesPerPage) == 0) {
        char *formatString = initString(9);
        sprintf(formatString, "\n\nPage %*ld", 3, wr->currentPage);
        
        // CHOICES
        push(wr->formattedOutput, formatString);
        //strcat(wr->pagedOutput, formatString);
        
        
        if (DEBUG_FORMAT_OUTPUT) printf("%s ", formatString);
    }
    
    
    if (wr->currentWordInLine == 0) {
        char *formatString = initString(11);
        sprintf(formatString, "\nLine %*ld:\t", 3, wr->currentLine);
        // Choices
        push(wr->formattedOutput, formatString);
        //strcat(wr->pagedOutput, formatString);
        
        if (DEBUG_FORMAT_OUTPUT) printf("%s ", formatString);
    }
    
    // ALWAYS INSERT WORD
    char *final = allocateString(insertion);
    push(wr->formattedOutput, final);
    //strcat(wr->pagedOutput, insertion);
    //strcat(wr->pagedOutput, " ");
    
    if (DEBUG_FORMAT_OUTPUT) printf("%s ", allocateString(insertion));
    
    if (wr->currentWordInLine == wr->wordsPerLine) {
        char *formatString = initString(2);
        formatString = "\n";
        // Choices
        push(wr->formattedOutput, formatString);
        //strcat(wr->pagedOutput, formatString);
        if (DEBUG_FORMAT_OUTPUT) printf("%s ", formatString);
    }
    
    return final;
}

/*  Updates a WORD_REPORT struct to accurately calculate a specific WORD_LOCATION
 */
void calculatePosition(WORD_REPORT *wr) {
    // The remainder of (totalWords / wordsPerLine) is the posistion of the word
    wr->currentWordInLine = (wr->totalWords % wr->wordsPerLine);
    // Divide the totalWords by the Page/line size
    wr->totalLines = wr->totalWords / wr->wordsPerLine;
    
    // Current Page is the (totalLines / linesPerPage) + 1
    wr->currentPage = (wr->totalLines / wr->linesPerPage) + 1;
    
    // The currentLine is the remained (totalLines % linesPerPage) + 1
    wr->currentLine = (wr->totalLines % wr->linesPerPage) + 1;
}

/*  Updates a WORD_REPORT struct to accurately display additional lines via file formatting
 */
void forceLayout(WORD_REPORT *wr) {
    // Increment totalLines
    wr->totalLines++;
    
    // The currentLine is the remained (totalLines % linesPerPage) + 1
    wr->currentLine = (wr->totalLines % wr->linesPerPage) + 1;
    
    // Current Page is the (totalLines / linesPerPage) + 1
    wr->currentPage = (wr->totalLines / wr->linesPerPage) + 1;
}

/*  Calculates the Maximum between two long numbers
 *
 */
long max(long numbA, long numbB) {
    if (numbA > numbB) return numbA;
    else return numbB;
}

/* Check string for token
 */
int searchWord(char *word, char *invalidCharList) {
    int isValid = TRUE;
    // Trim off Punctuation and Invalid characters
    // Get the last Character
    long lastCharacter = strlen(word);
    long checkPos = 0, currentCharacter = 0;
    char *nextSegment;
    
    if (DEBUG_VALIDATION == TRUE) {
        printf("WORD: %s\nlastCharacter: %ld\n", word, lastCharacter);
    }
    
        // Check for apostrophies
        while (currentCharacter <= lastCharacter) {
            // Find the INVALID CHARACTERS
            checkPos = strcspn(word + currentCharacter, invalidCharList);
            currentCharacter += checkPos;
            
            // If current character is a null terminate, return TRUE
            if (currentCharacter + 1 >= lastCharacter) {
                break;
            }
            
            nextSegment = &word[currentCharacter + 1];
            if (DEBUG_VALIDATION == TRUE) { printf("nextCharacter: %s\n", nextSegment); }
            if (strcmp(nextSegment, "") == 0) {
                isValid = FALSE;
                break;
            }
            
            checkPos = strcspn(nextSegment, "abcdefghijklmnopqrstuvwxyz");
            
            // Update the currentCharacter to jumpt past the nextSegment Check result
            currentCharacter += checkPos + 1;
            if (DEBUG_VALIDATION == TRUE) printf("currentCharacter: %ld - %c\n", currentCharacter, word[currentCharacter]);
            
            if (checkPos == 0) {
                // Next character is ALPHA
                printf("%s", "Next character is ALPHA\n");
                isValid = TRUE;
                continue;
            } else {
                printf("%s", "Next character is NOT ALPHA\n");
                isValid = FALSE;
                break;
            }
        }
    return isValid;
}

