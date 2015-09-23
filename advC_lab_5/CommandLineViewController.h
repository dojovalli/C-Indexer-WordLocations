//
//  CommandLineViewController.h
//  advC_lab_5
//
//  Created by Matthew Valli on 6/7/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#ifndef advC_lab_5_CommandLineViewController_h
#define advC_lab_5_CommandLineViewController_h

// CONSTANTS
#define BUFFER_SIZE 300

// Define a PROGRAM struct
typedef struct program_struct PROGRAM;
struct program_struct {
    char inputBuffer[BUFFER_SIZE];
};

// FUNCTIONS
int promptUser(char* prompt, char* dest);





#endif
