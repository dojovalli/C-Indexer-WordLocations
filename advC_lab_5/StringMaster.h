//
//  StringMaster.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/19/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_StringMaster_h
#define advC_lab_5_StringMaster_h


char* initString(int bufferSize);
char* allocateString( char *tempString );
void trim(char* str);
void trimEnd(char* str, char *trimChars);
char* convertToLower(char *str);
int matchChar(char *word, long index, char *tokens);
int matchLastChar(char *word, char *tokens);


#endif
