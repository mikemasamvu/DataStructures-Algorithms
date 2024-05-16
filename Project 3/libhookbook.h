#ifndef __LIBHOOKBOOK_H__
#define __LIBHOOKBOOK_H__

/*
Use this file to encapsulate generally useful functionality that doesn't belong
in either pirate.h or pirate_list.h.

Author: Mike Masamvu
Modified by: Mike Masamvu on 13/10/2023
*/
#include <stdio.h>
#include "pirate_list.h"

/*
Function adds read captains and their underling from the file and add the captain to the underling profile.
*/
void *add_captain(pirate_list *pirates, FILE *restrict input);

/*
Function checks if the command-line arguments passed by the user are valid. 
*/
void parse_arguments(int argc, char *argv[], FILE **pirates_file, FILE **captains_file, const char **sort_flag);

/**
 * Getter function for the comparison flag
 */
const char *get_flag();

#endif