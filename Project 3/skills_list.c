#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skills_list.h"
#include "pirate.h"

/************** headers **************
Filename: skills_list.c
Creator: Mike Masamvu
Class: CS223 Homework 3
Date: 10/15/2023
Purpose: Contains getters and setters for the skills_list struct
*/

// Parameters: nothing
// Returns: nothing
// Purpose: Structure definition for the pirate list instance
struct skills_list_instance_t
{
    char *skill_name;
    int skill_count;
    struct skills_list_instance_t *node;
    struct skills_list_instance_t *head;
};

// Parameters: skills list
// Returns: name of skill
// Purpose: create skills list
skills_list* create_skills_list(const char *skill_name) {
    skills_list *new_node = (skills_list*)malloc(sizeof(skills_list));
    if (new_node == NULL) {
        // Handle memory allocation error
        return NULL;
    }
    
    new_node->skill_name = (char*)malloc(strlen(skill_name) + 1); // Allocate memory for skill_name
    if (new_node->skill_name == NULL) {
        // Handle memory allocation error
        free(new_node);
        return NULL;
    }
    
    strcpy(new_node->skill_name, skill_name); // Copy skill_name to new_node->skill_name
    new_node->skill_count = 0;
    new_node->node = NULL;
    new_node->head = new_node;
    
    return new_node;
}

// Parameters: skills list, skill name
// Returns: skill if it exists, otherwise NULL
// Purpose: look for skill by name
skills_list* access_skill_name(skills_list **list, const char *skill_name)
{
    skills_list *current = *list;
    while (current)
    {
        if (strcmp(current->skill_name, skill_name) == 0) {
            return current;
        }
        current = current->node;
    }
    return NULL; // Skill not found
}

// Parameters: skills list, index
// Returns: skill index if it exists
// Purpose: look for skill by index
skills_list* access_skill_index(skills_list **list, size_t index)
{
    skills_list* current = *list;
    size_t i = 0;
    while (current && i < index) { // Loop through all  skill nodes
        current = current->node;
        i++;
    }
    return current;
}

// Parameters: skills list, skill name
// Returns: nothing
// Purpose: Function to update the skills list by adding a skill and handling duplicates
void update_skills(skills_list **list, const char *skill_name) {
    if (!*list) {
        *list = create_skills_list(skill_name);
        return;
    }

    skills_list *current = *list;
    skills_list *prev = NULL;

    while (current) {
        int comparison = strcmp(current->skill_name, skill_name);
        if (comparison == 0) {
            // Skill already exists, increment the count
            current->skill_count++;
            return;
        } else if (comparison > 0) {
            // Insert the new skill here
            skills_list *new_skill = create_skills_list(skill_name);
            if (!prev) {
                new_skill->node = *list;
                *list = new_skill;
            } else {
                prev->node = new_skill;
                new_skill->node = current;
            }
            return;
        }

        prev = current;
        current = current->node;
    }

    // If we reached here, the new skill should be added at the end of the list
    prev->node = create_skills_list(skill_name);
}

// Parameters: skills list
// Returns: length of skills list
// Purpose: Function to get the length of the skills list
size_t get_list_length(skills_list *list) {
    size_t length = 0;
    skills_list *current = list;

    while (current != NULL) {
        length++;
        current = current->node;
    }

    return length;
}

// Parameters: skills list, stdout format
// Returns: nothing
// Purpose: Function to rpint all the skills for the pirate
void print_skills(skills_list *list, FILE *restrict output) {
    size_t length = get_list_length(list);

    if (length > 0) {
        fprintf(output, "    Skills: %s ", list->skill_name);  // Print the first skill on the same line
        for (int i = 0; i < list->skill_count; i++) 
        {
            fprintf(output, "*");  // Print "*" for each repeat of the skill
        }

        skills_list *current = list->node;  // Start from the second skill

        while (current != NULL) {
            fprintf(output, "\n            %s", current->skill_name);
            for (int i = 0; i < current->skill_count; i++) {
                fprintf(output, " *");  // Print "*" for each repeat of the skill
            }
            current = current->node;
        }

        fprintf(output, "\n");
    }
}

// Parameters: skills list
// Returns: nothing
// Purpose: Function to free the skills list struct
void free_skills_list(skills_list *list)
{
    skills_list *current = list;
    while (current != NULL) // Loop through all skill nodes
    {
        skills_list *next = current->node;
        free(current->skill_name);
        free(current);
        current = next;
    }
}





