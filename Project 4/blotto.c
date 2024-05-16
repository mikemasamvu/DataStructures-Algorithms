#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "libblotto.h"
#include "entry.h"
#include "gmap.h"

/************** headers **************
Filename: blottoc.c
Creator: Mike Masamvu
Class: CS223 Homework 3
Date: 11/01/2023
Purpose: Blotto main function
*/

int main(int argc, char *argv[])
{
    // Validate command line argument count
    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s <number_of_battlefields>\n", argv[0]);
        return 1;
    }

    int battlefields = argc - 1; // Battlefield Count
    int *numbers = (int *)malloc(battlefields * sizeof(int)); // Allocate memory for the array
    
    if (numbers == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Convert command line arguments to integers and store in the array
    for (int i = 1; i < argc; i++) {
        numbers[i - 1] = atoi(argv[i]);
    }

    implementation(stdin, numbers, battlefields); // Full Blotto implementation
    free(numbers);
    return 0;
}