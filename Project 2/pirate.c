#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pirate.h"

#define INITIAL_CAPACITY

// Function to create a new pirate structure and allocate memory for it
pirate* pirate_create()
{
    pirate *new_pirate = malloc(sizeof(pirate));
    if (new_pirate == NULL)
    {
        return NULL;
    }
    return new_pirate;
}

// Function to read pirate data from a file and create a pirate structure
pirate *pirate_read(FILE *restrict input)
{
    char c = fgetc(input);
    if (c == EOF || c == '\n')
    {
        return NULL; // Return NULL if end of file or newline character is encountered
    }
    pirate *p = pirate_create();
    
    fseek(input, -1, SEEK_CUR);
    char name[127];
    // Remove newline character, if present
    fgets(name, sizeof(name), input);
    size_t size = strlen(name);
    if (size > 0 && name[size - 1] == '\n') 
    {
        name[size - 1] = '\0';
    }
    // Check if the line is not empty and then print it
    if (strlen(name) > 0) {
        p->name = malloc(strlen(name) + 1); // allocate memory for the pirate
        strcpy(p->name, name); // copy name to pirate struct
       
    }
    
    fgets(name, sizeof(name), input); // read next line
    

    return p; // return created pirate structure

}

// Function to print a pirate's name to a specified output stream
void pirate_print(const pirate *p, FILE *restrict output)
{
    fprintf(output, "%s\n", p->name);
}

// Function to get a pirate's name
const char *pirate_name(const pirate *p)
{
    return p->name;
}

// Function to set a pirate's name
void pirate_set_name(pirate *p, const char* name)
{
    if (p->name)
    {
        free(p->name);
    }
    p->name = malloc(sizeof(name));
    strcpy(p->name, name); // Copy the new name to the pirate structure
}

// Function to compare two pirates based on their names
int pirate_compare(pirate *a, pirate *b)
{
    int pirate_cmp = strcmp(a->name, b->name);

    if (pirate_cmp < 0)
    {
        return -1;
    }
    else if (pirate_cmp == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Function to destroy a pirate structure and free associated memory
void pirate_destroy(pirate *p)
{
    if (p->name != NULL)
    {
        free(p->name); // Free memory for the pirate's name
    }
    
    free(p); // Free memory for the pirate structure
}