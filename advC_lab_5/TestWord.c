//
//  TestWord.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/7/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include "Word.h"
#include "DoubleLinkedQueue.h"
#include "TestDBLQueue.h"
#include "TestWord.h"


int testWord(int verboseMode) {
    // Create Sample Data
    char shortWord[8] = "classic";
    char mediumWord[25] = "hemophiliasophia";
    char oversizedWord[49] = "giberishcanbehardtospellthatlongjustthewayitgoes";
    
    // Create Words
    WORD *word1 = generateWord(shortWord, 11);
    WORD *word2 = generateWord(mediumWord, 22);
    WORD *word3 = generateWord(oversizedWord, 3);
    
    // Print Words
    printWord(word1, 49, maxPageDigit, maxLineDigit);
    printWord(word2, 49, maxPageDigit, maxLineDigit);
    printWord(word3, 49, maxPageDigit, maxLineDigit);
    
    return SUCCESS;
}

void testMergeWord() {
    printf("TESTING WORD - MERGE\n");
    // Create words with many different and like locations
    WORD *w1 = newWord("same", newWordLocation(1, 1, 1));
    WORD *w2 = newWord("same", newWordLocation(1, 1, 1));
    WORD *w3 = newWord("same", newWordLocation(1, 1, 1));
    WORD *w4 = newWord("same", newWordLocation(1, 2, 1));
    WORD *w5 = newWord("same", newWordLocation(1, 2, 1));
    WORD *w6 = newWord("same", newWordLocation(1, 2, 1));
    WORD *w7 = newWord("same", newWordLocation(2, 1, 1));
    WORD *w8 = newWord("same", newWordLocation(2, 1, 1));
    WORD *w9 = newWord("same", newWordLocation(2, 1, 1));
    WORD *w10 = newWord("same", newWordLocation(2, 2, 1));
    WORD *w11 = newWord("same", newWordLocation(2, 2, 1));
    WORD *w12 = newWord("same", newWordLocation(2, 2, 1));
    
    mergeWord(w1, w2);
    mergeWord(w1, w3);
    mergeWord(w1, w4);
    mergeWord(w1, w5);
    mergeWord(w1, w6);
    mergeWord(w1, w7);
    mergeWord(w1, w8);
    mergeWord(w1, w9);
    mergeWord(w1, w10);
    mergeWord(w1, w11);
    mergeWord(w1, w12);
    
    printf("%s\n", wordString(w1, 5, 2, 2));
    
}

WORD* generateWord(char word[MAX_WORD_SIZE], long count) {
    return newWord(word, newWordLocation(count, count, count));
}
