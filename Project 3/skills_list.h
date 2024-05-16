#ifndef __SKILLS_LIST_H__
#define __SKILLS_LIST_H__

#include <stdio.h>
/*
Header file for skills list for Hookbook assignments for CPSC 223 Fall 2023.

Author: Mike Masamvu
Modified by: Mike Masamvu on 13/10/2023
*/

/**
 * Type of a list of skills, as an opaque struct.
 */
typedef struct skills_list_instance_t skills_list;

/**
 * Function to create skills list
 */
skills_list* create_skills_list(const char *skill_name);

/**
 * Function to look for skill by name
 */
skills_list* access_skill_name(skills_list **list, const char *skill_name);

/**
 * Function to look for skill by index
 */
skills_list* access_skill_index(skills_list **list, size_t index);

/**
 * Function to get the length of the skills list
 */
size_t get_list_length(skills_list *list);

/**
 * Function to update the skills list by adding a skill and handling duplicates
 */
void update_skills(skills_list **list, const char *skill_name); 

/**
 * Function to rpint all the skills for the pirate
 */
void print_skills(skills_list *list, FILE *restrict output);

/**
 * Function to free the skills list struct
 */
void free_skills_list(skills_list *list);

#endif