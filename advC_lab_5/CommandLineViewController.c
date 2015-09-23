//
//  CommandLineViewController.c
//  advC_lab_5
//
//  Created by Matthew Valli on 6/7/15.
//  Copyright (c) 2015 Matthew Valli. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int promptUser(char* prompt, char* dest) {

    // Print the Prompt
    printf("%s", prompt);
    
    // Read input
    return fscanf(stdin, "%s", dest);
}