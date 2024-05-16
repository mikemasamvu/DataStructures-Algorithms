/*
Driver for Game of Life assignment in CPSC 223 Fall 2023

Author: Mike Masamvu
*/

#include "life.h"
#include "helpers.h"
#include <stdio.h>

// TO STUDENT: Do not change this definition!
#ifndef SIZE
#define SIZE 10
#endif
// End modification restriction

int main(int argc, char *argv[])
{
    // Check if user inputs correct number of arguments
    verifyArgCount(argc);

    int time_steps = atoi(argv[1]);

    // Check if user inputs valid input for number of steps
    verifyStepsInput(time_steps);
    
    char *init = argv[2];

    // Check if the second-command line argument has correct number of 0s and 1s
    verifyBinaryInput(init, SIZE);
    
    // Create a new statically-allocated array of length SIZE
    int array[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        // Convert into integers
        array[i] = init[i] - '0';

        // Check if the second command line argument only consists of 1s and 0s
        validateBinaryInput(array[i]);
    }

    // Print the initial values held in the array
    print_initial(array, SIZE);

    // Run the game time_steps times, printing the array at the end of each step
    int duplicate_array[SIZE];
    for (int i = 1; i <= time_steps; i++)
    {
        // Creates duplicate array of the original list which is passed as arguments in the if statements
        // Update the duplicate_array after every step
        for (int k = 0; k < SIZE ; k++)
        {
            duplicate_array[k] = array[k];
        }
        for (int j = 0; j < SIZE; j++)
        {
            // Check if cell is alive and should die
            if ((isAlive(duplicate_array, j, SIZE)) && (shouldDie(duplicate_array, j, SIZE)))
            {
                kill_cell(array, j, SIZE);
            }
            // Check if cell is dead and should be alive
            else if (!(isAlive(duplicate_array, j, SIZE)) && (shouldLive(duplicate_array, j, SIZE)))
            {
                activate_cell(array, j, SIZE);
            }
            // If cell should not change, retain the current value
            else 
            {
                array[j] = array[j];
            }
        }
        print_generation(array, i, SIZE);
    }
    return 0;
}