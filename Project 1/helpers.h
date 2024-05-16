#ifndef __HELPERS_H__
#define __HELPERS_H__

/*
Interface for helper functions for Game of Life assignment for CPSC 223 Fall 2023.

Author: Alan Weide

TO STUDENT: You may add to this file, but do not change anything that is already here!
Remember, this is a header file: there should be no function bodies here, only prototypes.
Modified by: Mike Masamvu on 09/13/2023
Changelog: Added prototypes for functions that validate and verify user input (command-line arguments) to see if it meets the specifications. 
*/

#include <stdlib.h>

void print_initial(int field[], size_t size);

void print_generation(int field[], unsigned int gen, size_t size);

int verifyArgCount(int argc);

int verifyStepsInput(int steps);

int verifyBinaryInput(char *input, size_t size);

int validateBinaryInput(int item);

#endif