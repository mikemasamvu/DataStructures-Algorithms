/*
Implementations of helper functions for Game of Life assignment for CPSC 223 Fall 2023.

Author: Alan Weide

TO STUDENT: You may add to this file, but do not change anything that is already here!
Modified by: Mike Masamvu on 09/13/2023
Changelog: Added 3 functions that validate and verify user input (command-line arguments) to see if it meets the specifications. 
*/

#include "helpers.h"
#include <stdio.h>
#include <string.h>

void print_initial(int field[], size_t size)
{
    printf("%-16s[ ", "Initial Values");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", field[i]);
    }
    printf("]\n");
}

void print_generation(int field[], unsigned int gen, size_t size)
{
    printf("Step %-10d [ ", gen);
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", field[i]);
    }
    printf("]\n");
}

// Check if user inputs correct number of arguments
int verifyArgCount(int argc)
{
     if (argc != 3)
    {
        printf("Incorrect number of arguments!\n");
        exit(1);
    }
    else
    {
        return 0;
    }
}

// Check if user inputs valid input for number of steps
int verifyStepsInput(int steps)
{
    if (!(steps > 0))
    {
        printf("Invalid input for number of steps!\n");
        exit(1);
    }
    else
    {
        return 0;
    }
}

// Check if the second-command line argument has correct number of 0s and 1s
int verifyBinaryInput(char *input, size_t size)
{
     if (!(strlen(input) == size))
    {
        printf("Incorrect input for number of 1s and 0s!\n");
        exit(1);
    }
    else
    {
        return 0;
    }
}

// Check if the second command line argument only consists of 1s and 0s
int validateBinaryInput(int item)
{
     if (!((item == 0) || (item == 1))) 
    {
        printf("Invalid input for 1s and 0s!\n");
        exit(1);
    }
    else
    {
        return 0;
    }
}