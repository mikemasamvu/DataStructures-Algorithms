#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pirate.h"

/************** headers **************
Filename: pirate.c
Creator: Mike Masamvu
Class: CS223 Homework 3
Date: 10/15/2023
Purpose: Contains getters and setters for the pirate struct
*/

// Parameters: pirates list, file to be read
// Returns: nothing
// Purpose: Function to create a new pirate structure and allocate memory for it
pirate* pirate_create(void)
{
    pirate *new_pirate = malloc(sizeof(pirate));
    if (new_pirate != NULL)
    { 
        // Initialize struct objects
        new_pirate->name = NULL;
        new_pirate->captain = NULL;
        new_pirate->rank = NULL;
        new_pirate->vessel = NULL;
        new_pirate->port = NULL;
        new_pirate->treasures = 0;
        new_pirate->skills = NULL;
    }
    else
    {
        return NULL;
    }
    return new_pirate;
}

// Parameters: file to be read
// Returns: pirate pointer
// Purpose: Function to read pirate data from a file and create a pirate structure
pirate *pirate_read(FILE *restrict input)
{
    if (input == NULL)
    {
        return NULL;
    }

    char c = fgetc(input);
    if (c == EOF || c == '\n')
    {
        return NULL; // Return NULL if end of file or newline character is encountered
    }

    fseek(input, -1, SEEK_CUR); // Move cursor to previous line
    char line[256];

    if (fgets(line, sizeof(line), input)) {
        size_t size = strlen(line);
        if (size > 0 && line[size - 1] == '\n') {
            line[size - 1] = '\0'; // Remove the newline character if present
        }

        // Directly copy the first line as the name
        pirate *p = pirate_create();
        p->name = malloc(strlen(line) + 1);
        pirate_set_name(p, line); // Set pirate name

        while (fgets(line, sizeof(line), input)) {
            size_t size = strlen(line);
            if (size > 0 && line[size - 1] == '\n') {
                line[size - 1] = '\0'; // Remove the newline character if present
            }

            if (line[0] == '\0') {
                break;
            }
            
            char* key = strtok(line, ":"); // Take string before ":"
            char* value = strtok(NULL, ":\n"); // Take string after ":"

            if (key !=NULL && value != NULL)
            {
                // Check for the value of the key and update the appropriate struct object
                if (strcmp(key, "rank") == 0) {
                    p->rank = malloc(strlen(value) + 1);
                    pirate_set_rank(p, value);
                } 
                else if (strcmp(key, "vessel") == 0) {
                    p->vessel = malloc(strlen(value) + 1);
                    pirate_set_vessel(p, value);
                } 
                else if (strcmp(key, "port") == 0) {
                    p->port = malloc(strlen(value) + 1);
                    pirate_set_port(p, value);
                } 
                else if (strcmp(key, "treasure") == 0) {
                    p->treasures = atoi(value);
                }
                else if (strcmp(key, "skill") == 0) {
                // Add skill to the skills list (you may need to implement this)
                    update_skills(&p->skills, value);
                }
            }
        }

        return p;
    }
    else
    {
        return NULL;
    }
}

// Parameters: pirate, stdout format
// Returns: nothing
// Purpose: Function to print a pirate's name to a specified output stream
void pirate_print(const pirate *p, FILE *restrict output)
{
    if (p == NULL || output == NULL)
    {
        return;
    }

    fprintf(output, "%s\n", p->name);
    if (p->captain != NULL)
    {
        if (pirate_vessel((const pirate*)(p->captain)) == NULL)
        {
            fprintf(output, "    Captain: %s\n", pirate_name((const pirate*)(p->captain))); // If captain doesnt have a vessel, dont print the vessel
        }
        else
        {
            fprintf(output, "    Captain: %s (%s)\n", pirate_name((const pirate*)(p->captain)), pirate_vessel((const pirate*)(p->captain)));
        }
        
    }
    if (p->rank != NULL)
    {
        fprintf(output, "    Rank: %s\n", p->rank);
    }
    if (p->vessel != NULL)
    {
        fprintf(output, "    Vessel: %s\n", p->vessel);
    }
    if (p->port != NULL)
    {
        fprintf(output, "    Port: %s\n", p->port);
    }
    if (p->treasures > 0)
    {
        fprintf(output, "    Treasure: %d\n", p->treasures);
    }
    if (p->skills != NULL)
    {
        print_skills(p->skills, output);
    }
    
}

// Parameters: pirate
// Returns: pirate name
// Purpose: Function to get a pirate's name
const char *pirate_name(const pirate *p)
{
    if (p == NULL)
    {
        return NULL;
    }
    return p->name;
}

// Parameters: pirate and name of pirate
// Returns: nothing
// Purpose: Function to set a pirate's name
void pirate_set_name(pirate *p, const char* name)
{
    if (p == NULL || name == NULL)
    {
        return;
    }
    if (p->name == NULL)
    {
        p->name = malloc(strlen(name) + 1);
    }
    strcpy(p->name, name); // Copy the new name to the pirate structure
}

// Parameters: pirate
// Returns: pirate vessel
// Purpose: Function to get a pirate's vessel
const char *pirate_vessel(const pirate *p)
{
    if (p == NULL)
    {
        return NULL;
    }
    return p->vessel;
}

// Parameters: pirate and vessel of pirate
// Returns: nothing
// Purpose: Function to set a pirate's vessel
void pirate_set_vessel(pirate *p, const char* vessel)
{
    if (p == NULL || vessel == NULL)
    {
        return;
    }
    if (p->vessel == NULL)
    {
        p->vessel = malloc(strlen(vessel) + 1);
    } 
    strcpy(p->vessel, vessel);
}

// Parameters: pirate
// Returns: pirate port
// Purpose: Function to get a pirate's port
const char *pirate_port(const pirate *p)
{
    if (p != NULL)
    {
        return p->port;
    }
    else
    {
        return NULL;
    }
}

// Parameters: pirate and port of pirate
// Returns: nothing
// Purpose: Function to set a pirate's port
void pirate_set_port(pirate *p, const char* port)
{
    if (p == NULL || port == NULL)
    {
        return;
    }
    if (p->port == NULL)
    {
        p->port = malloc(strlen(port) + 1);
    } 
    strcpy(p->port, port);
}

// Parameters: pirate
// Returns: pirate rank
// Purpose: Function to get a pirate's rank
const char *pirate_rank(const pirate *p)
{
    if (p != NULL)
    {
        return p->rank;
    }
    else
    {
        return NULL;
    }
}

// Parameters: pirate and rank of pirate
// Returns: nothing
// Purpose: Function to set a pirate's rank
void pirate_set_rank(pirate *p, const char* rank)
{
    if (p == NULL || rank == NULL)
    {
        return;
    }
    if (p->rank == NULL)
    {
        p->rank = malloc(strlen(rank) + 1);
    }    
    strcpy(p->rank, rank);
}

// Parameters: pirate
// Returns: pirate treasure count
// Purpose: Function to get a pirate's treasure count
unsigned int pirate_treasure(const pirate *p)
{
    if (p != NULL)
    {
        return p->treasures;
    }
    else
    {
        return 0;
    }
}

// Parameters: pirate and treasure count of pirate
// Returns: nothing
// Purpose: Function to set a pirate's treasure count
void pirate_set_treasure(pirate *p, unsigned int treasure)
{
    if (p != NULL)
    {
        p->treasures = treasure;
    }
}

// Parameters: pirate
// Returns: pirate's captain
// Purpose: Function to get a pirate's captain
const pirate *pirate_captain(const pirate *p)
{
    if (p != NULL)
    {
        return (const pirate*)p->captain; 
    }
    else
    {
        return NULL;
    }
}

// Parameters: pirate and captain
// Returns: nothing
// Purpose: Function to set a pirate's captain
void pirate_set_captain(pirate *p, const pirate *cpt)
{
    if (p != NULL && cpt !=NULL)
    {
        p->captain = (struct pirate*)cpt;
    }
}

// Parameters: pirate
// Returns: pirate skills list
// Purpose: Function to get a pirate's skills list
skills_list *pirate_skills(const pirate *p)
{
    if (p != NULL)
    {
        return p->skills;
    }
    else
    {
        return NULL;
    }
}

// Parameters: pirate and name of pirate
// Returns: nothing
// Purpose: Function to destroy a pirate structure and free associated memory
void pirate_destroy(pirate *p)
{
    if (p != NULL)
    {
        if (p->name)
        {
            free(p->name);
        }
        if (p->rank)
        {
            free(p->rank);
        }
        if (p->vessel)
        {
            free(p->vessel);
        }
        if (p->port)
        {
            free(p->port);
        }
        if (p->skills)
        {
            free_skills_list(p->skills); // Free skills list
        }

        free(p); // Free memory for the pirate structure
    }
    
}