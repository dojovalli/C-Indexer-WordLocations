//
//  StringMaster.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/19/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "WordReportConstants.h"


#pragma mark Strings
/* Initializes an array of char* to the provided size
 *
 * Perameters:
 *      int size - number of elements (char*) allocated for storage
 */
char* initString(int bufferSize) {
    char *pTemp = (char*) malloc( bufferSize * sizeof(char) );
    
    // Exit Program with OUT_OF_MEMORY Flag if NULL Pointer received
    if (pTemp == NULL) {
#ifdef _MSC_VER
        MEM_ERROR;
#endif
        printf("Out of Memory!\nExiting with ERROR: %d", OUT_OF_MEMORY);
        exit(OUT_OF_MEMORY);
    }
    
    return pTemp;
}

/* Create a dynamically allocated string
 Pre:  tempString
 Post: string - dynamically allocated
 */
char* allocateString( char *tempString ) {
	char *string;
	long length;
	length = strlen( tempString ) + 1;
	string = (char *) calloc (length, sizeof(char));
    
    if ( string == NULL) {
		printf ("allocateString: "
                "ERROR, not enough memory!!!\a\n");
		exit (OUT_OF_MEMORY);
	}
	strcpy (string, tempString);
	return string;
}

/* Converts a string ending with a newline character into a C-String
 *
 * Pre-Condition: Expects only a single line of text, not meant to handle multiple '\n' characters
 *
 * Perameters:
 *      char* str - char* to the string to convert C-string
 */
void trim(char* str) {
    char *pos;
    if ((pos=strchr(str, '\n')) != NULL)
        *pos = '\0';
    return;
}

/*  Replaces the last character of a string (str)
    if the given character matches any character in the trimChars set
 */
void trimEnd(char* str, char *trimChars) {
    int lastChar = (int) strlen(str) - 1;
    for (int i = 0; i < strlen(trimChars); i++) {
        if (str[lastChar] == trimChars[i]) str[lastChar] = '\0';
    }
    return;
}

/* Converts a string to Uppercase
 *
 * Perameters:
 *      char *str - char* to the string to convert to Uppercase
 */
char* convertToLower(char *str) {
    char *final = (char*) malloc( sizeof(char) * strlen(str) + 1);
    strcpy(final, str);
    char *tmp = final;
    while(*tmp != '\0') {
        *tmp = tolower(*tmp);
        tmp++;
    }
    str = final;
    return final;
}

/*  Checks a string (word) at a given index for a match of any character in the provided tokens set
    Returns int representing TRUE (1) or FALSE (0)
 */
int matchChar(char *word, long index, char *tokens) {
    if (DEBUG_MATCH_LAST == TRUE) printf("matchCharAtIndex\nword: %s\ntoken: %s\n", word, tokens);
    int isValid = FALSE;
    
    
    for (int i = 0; i < strlen(tokens); i++) {
        if (word[index] == tokens[i]) {
            if (DEBUG_MATCH_LAST) printf("Match\n");
            isValid = TRUE;
        }
    }
    
    return isValid;
}

/*  Checks a string (word) at its last character for a match of any character in the provided tokens set
 Returns int representing TRUE (1) or FALSE (0)
 */
int matchLastChar(char *word, char *tokens) {
    if (DEBUG_MATCH_LAST == TRUE) printf("matchLastChar\nword: %s\ntoken: %s\n", word, tokens);
    int isValid = FALSE;
    
    for (int i = 0; i < strlen(tokens); i++) {
        if (word[strlen(word) - 1] == tokens[i]) {
            if (DEBUG_MATCH_LAST) printf("Match\n");
            isValid = TRUE;
        }
    }
    
    return isValid;
}