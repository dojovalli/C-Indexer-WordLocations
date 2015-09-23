//
//  TestWordReport.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/13/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_TestWordReport_h
#define advC_lab_5_TestWordReport_h

#include "WordReport.h"

#pragma mark MAIN TEST
void testWordReport();

#pragma mark TESTCASES
void testSpecialCase();
void testSmallFile();

WORD_REPORT* testWordReportConstructor();
void testWriteWordReport(WORD_REPORT *wr);
void testOutputWordReport(WORD_REPORT *wr);
void testProcessFile(WORD_REPORT *wr);

void testIsValid();
void testTimestamp();

#endif
