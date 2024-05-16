#include <stdio.h>
#include <string.h>
#include "pirate_list.h"

/************** headers **************
Filename: libhookbook.c
Creator: Mike Masamvu
Class: CS223 Homework 3
Date: 10/15/2023
Purpose: Contains hookbook.c helper functions
*/

// Parameters: pirates list, file to be read
// Returns: nothing
// Purpose: Function adds read captains and their underling from the file 
//          and add the captain to the underling profile.

const char *flag;

void *add_captain(pirate_list *pirates, FILE *restrict input)
{
    char line[256];
    char underling[256];
    char captain[256];

    while(!feof(input))
    {
        fgets(line, sizeof(line), input);
        strcpy(underling, line);
        size_t len_underling = strlen(underling);
        if (len_underling > 0 && underling[len_underling - 1] == '\n') {
            underling[len_underling - 1] = '\0'; // Remove the newline character if present
        }

        fgets(line, sizeof(line), input); // Read first line
        strcpy(captain, line); // Copy data read into char captain
        size_t len_captain = strlen(captain);

        if (len_captain > 0 && captain[len_captain - 1] == '\n') {
            captain[len_captain - 1] = '\0'; // Remove the newline character if present
        }
        
        pirate *cap_ptr = find_pirate_by_name(captain, pirates); // Assign pointer to captain with that name
        pirate *underling_ptr = find_pirate_by_name(underling, pirates); // Assign pointer to underling with that name
        pirate_set_captain(underling_ptr, cap_ptr); // Add captain into underling profile
    }
    return NULL;
}

// Parameters: command-line arguments, and argument count
// Returns: nothing
// Purpose: Function checks if the command-line arguments passed by the user are valid. 
void parse_arguments(int argc, char *argv[], FILE **pirates_file, FILE **captains_file, const char **sort_flag) {
    *pirates_file = NULL;
    *captains_file = NULL;
    *sort_flag = "-n"; // Default sort flag is "-n"

    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];

        if (arg[0] == '-') {
            // Handle sort flag
            if (strcmp(arg, "-n") == 0 || strcmp(arg, "-t") == 0 || strcmp(arg, "-v") == 0) {
                *sort_flag = arg;
                flag = arg;
            } else {
                fprintf(stderr, "Invalid sort flag: %s\n", arg);
                exit(1);
            }
        } else {
            FILE *argfile = fopen(arg, "r");
            if (argfile == NULL) {
                fprintf(stderr, "Failed to open file: %s\n", arg);
                exit(1);
            }
            
            if (*pirates_file == NULL) {
                // First non-flag argument is the pirates file
                *pirates_file = argfile;
            } else if (*captains_file == NULL) {
                // Second non-flag argument is the captains file
                *captains_file = argfile;
            } else {
                fprintf(stderr, "Too many arguments: %s\n", arg);
                fclose(argfile);
                exit(1);
            }
        }
    }

    if (*pirates_file == NULL || *captains_file == NULL) {
        fprintf(stderr, "Not enough arguments.\n");
        exit(1);
    }
}


const char *get_flag(){
    return flag;
}