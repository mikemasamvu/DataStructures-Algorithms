#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pirate_list.h"
#include "pirate.h"


int main(int argc, char *argv[])
{
    if (argc < 2){ // Check number of arguments
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *pirates_file = fopen(argv[1], "r"); // open file for reading
    if (pirates_file == NULL){
        fprintf(stderr, "Failed to open file\n");
        return 1; 
    }

    pirate_list *list = list_create(); // Create array to store pirate data
    pirate *p = pirate_read(pirates_file);
    while (p != NULL) {
        if (strlen(p->name) > 0){  // Remove newline character, if present
            list_insert(list, p, list_length(list));
        }
        else{
            pirate_destroy(p); // If pirate's name is empty, destroy the pirate object
        }

        p = pirate_read(pirates_file); // Read next pirate
    }

    fclose(pirates_file);
    list_sort(list); // sort the list

    for (int i = 0; i < list_length(list); i++){
        pirate_print(list_access(list, i), stdout);
    }

    list_destroy(list);  // Clean up memory used by the list and its elements
    return 0;
}