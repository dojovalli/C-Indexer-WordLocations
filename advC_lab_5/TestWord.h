//
//  TestWord.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/9/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_TestWord_h
#define advC_lab_5_TestWord_h

#include "WordReportConstants.h"
#include "Word.h"

// TESTCASES
int testWord(int verboseMode);
void testMergeWord();


// CONVENIENCE
WORD* generateWord(char word[MAX_WORD_SIZE], long count);


#endif
