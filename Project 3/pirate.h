#ifndef __PIRATE_H__
#define __PIRATE_H__

#include <stdio.h>
#include "skills_list.h"

/*
Header file for pirate for assignment HookBook assignments in CPSC 223 FA2023.

Author: Alan Weide

TO STUDENT: You may add to this file, but do not change anything that is
    already here!
Modified by: Mike Masamvu on 13/10/2023
Changelog: Completed type definition of pirate struct
*/

/**
 * Type of a pirate.
 */
typedef struct pirate
{
    char *name;
    struct pirate *captain;
    char *rank;
    char *vessel;
    char *port;
    unsigned int treasures;
    skills_list *skills;

} pirate;

/**
 * Allocates enough memory for a pirate, and returns a pointer to the newly-
 *  allocated memory.
 */
pirate *pirate_create(void);

/**
 * Reads a pirate profile from input. Assumes that the input cursor is at the
 *  beginning of a pirate profile (otherwise, its behavior is undefined).
 *
 * Returns a pointer to a pirate created from the profile in input.
 *
 * This function consumes a blank line after the end of the current profile
 *  before returning, meaning that after this function is done, the input
 *  cursor is either at the end of the input file or at the beginning of the
 *  next pirate profile.
 */
pirate *pirate_read(FILE *restrict input);

/**
 * Prints a pirate's profile to output in conformance with the output
 *  specification in the README.
 */
void pirate_print(const pirate *p, FILE *restrict output);

/**
 * Returns the name of the pirate.
 */
const char *pirate_name(const pirate *p);

/**
 * Sets the name of a pirate.
 */
void pirate_set_name(pirate *p, const char *name);

/**
 * Returns the vessel of the pirate.
 */
const char *pirate_vessel(const pirate *p);

/**
 * Sets the vessel of a pirate.
*/
void pirate_set_vessel(pirate *p, const char* vessel);

/**
 * Returns the favorite port of call of the pirate.
 */
const char *pirate_port(const pirate *p);

/**
 * Sets the favorite port of call of a pirate.
*/
void pirate_set_port(pirate *p, const char* port);

/**
 * Returns the rank of the pirate.
 */
const char *pirate_rank(const pirate *p);

/**
 * Sets the rank of a pirate.
*/
void pirate_set_rank(pirate *p, const char* rank);

/**
 * Returns the treasure of the pirate.
 */
unsigned int pirate_treasure(const pirate *p);

/**
 * Sets the treasure of a pirate.
*/
void pirate_set_treasure(pirate *p, unsigned int treasure);

/**
 * Returns a pointer to the profile of the pirate's captain.
 */
const pirate *pirate_captain(const pirate *p);

/**
 * Sets the captain of a pirate.
 */
void pirate_set_captain(pirate *p, const pirate *cpt);

/**
 * Returns a pointer to the list of skills of the pirate.
 */
skills_list *pirate_skills(const pirate *p);

/**
 * Frees all memory associated with this pirate. This function claims ownership
 *  of p.
 */
void pirate_destroy(pirate *p);

#endif
