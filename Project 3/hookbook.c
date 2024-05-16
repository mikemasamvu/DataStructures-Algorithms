#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"

/************** headers **************
Filename: hookbook.c
Creator: Mike Masamvu
Class: CS223 Homework 3
Date: 10/15/2023
Purpose: HookBook driver file
*/

int main(int argc, char *argv[])
{
    const char *sort_flag;
    FILE *pirates_file;
    FILE *captains_file;
    parse_arguments(argc, argv, &pirates_file, &captains_file, &sort_flag); // Validate command line arguments
    // flag = sort_flag; 

    int (*comp)(const void*, const void*) = compare_pirates; // Assign function pointer to comparison function
    if (pirates_file == NULL || captains_file == NULL){
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }

    pirate_list *list = list_create(comp); // Create array to store pirate data
    while (!feof(pirates_file)) {
        pirate *p = pirate_read(pirates_file);
        if (p != NULL)
        {
            list_insert(list, p, list_length(list)); // Insert pirate profile read into pirate list 
        }    
    } 
    fclose(pirates_file);
    add_captain(list, captains_file); // Add captain to underling profile
    fclose(captains_file);
    list_sort(list); // sort the list

    for (int i = 0; i < list_length(list); i++){
        pirate_print(list_access(list, i), stdout); // Print every pirate profile 
    }

    list_destroy(list);  // Clean up memory used by the list and its elements
    return 0;
}
