#include "pirate_list.h"
#include "libhookbook.h"
#include "pirate.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/************** headers **************
Filename: pirate_list.c
Creator: Mike Masamvu
Class: CS223 Homework 3
Date: 10/15/2023
Purpose: Contains getters and setters for the pirate_list struct
*/

// Parameters: nothing
// Returns: nothing
// Purpose: Structure definition for the pirate list instance
struct pirate_list_instance_t
{
    pirate **array;
    size_t size;
    size_t capacity;
    int (*compare)(const void*, const void*);
};

#define INITIAL_CAPACITY 25
#define RESIZE_FACTOR 2

// Parameters: comparison function pointer
// Returns: pirate_list
// Purpose: Function to create a new pirate list
pirate_list *list_create(int (*comp)(const void*, const void*))
{
    pirate_list *new_pirate_list = malloc(sizeof(pirate_list));
    
    if (new_pirate_list == NULL)
    {
        return NULL;
    }
    
    new_pirate_list->size = 0; // Initialize the size to 0
    new_pirate_list->capacity = INITIAL_CAPACITY;
    new_pirate_list->compare = comp;
    new_pirate_list->array = malloc(new_pirate_list->capacity * sizeof(pirate*));

    return new_pirate_list;
}

// Parameters: pirate and pirate_list
// Returns: index of a specific pirate
// Purpose: Function to find the index of a pirate in the list
size_t list_index_of(pirate_list *pirates, pirate *p)
{
    if (pirates == NULL || p == NULL)
    {
        return SIZE_MAX;
    }
    for (size_t i = 0; i < pirates->size; i++)
    {
        if (strcmp(pirates->array[i]->name, p->name) == 0)
        {
            return i;
        }
    }
    
    return pirates->size;
}

// Parameters: index, pirate and pirate_list
// Returns: pirate if it already exists, otherwise NULL
// Purpose: Function to insert a pirate at a specified index in the list
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
    if (pirates == NULL || p == NULL)
    {
        return NULL;
    }
    if (idx > pirates->size)
    {
        return NULL;
    }
    if (list_index_of(pirates, p) != pirates->size)
    {
        return p; // Return the pirate if it already exists in the list
    }

    list_expand_if_necessary(pirates); // Expand the list if necessary

    for (size_t i = pirates->size; i > idx; i--)
    {
        pirates->array[i] = pirates->array[i - 1]; // Shift elements to make space for the new pirate
    }

    pirates->array[idx] = p; // Insert the pirate at the specified index
    pirates->size++;
    return NULL;
}

// Parameters: pirate and pirate_list
// Returns: removed pirate if removal was succesful, otherwise NULL
// Purpose: Function to remove a pirate from the list
pirate *list_remove(pirate_list *pirates, pirate *p)
{
    if (pirates == NULL || p == NULL)
    {
        return NULL;
    }

    if (list_index_of(pirates, p) != pirates->size)
    {
        size_t j = list_index_of(pirates, p);
        pirate *removed_pirate = pirates->array[j]; // Store the pirate to be removed

        for (size_t i = j; i < pirates->size - 1; i++) 
        {
            pirates->array[i] = pirates->array[i + 1]; // Shift elements to fill the gap left by the removed pirate
        }
        pirates->size--;

        list_contract_if_necessary(pirates); // Contract the list if necessary

        return removed_pirate; // Return the removed pirate 
    }

    return NULL; // Return NULL if the pirate is not found in the list
}

// Parameters: pirate, index and pirate_list
// Returns: pirate profile if it exists, otherwise NULL
// Purpose: Function to access a pirate at a specified index in the list
pirate *list_access(pirate_list *pirates, size_t idx)
{
    if (pirates == NULL)
    {
        return NULL;
    }
    if (idx >= pirates->size)
    {
        return NULL; // Return NULL if the index is out of bounds
    }

    return pirates->array[idx]; // Return the pirate at the specified index
}

// Parameters: pirate, index and pirate_list
// Returns: integer 0, positive and negative integer after comparison
// Purpose: Custom comparison function for merging pirates
int compare_pirates(const void *a, const void *b) {
    pirate *pirateA = (pirate *)a;
    pirate *pirateB = (pirate *)b;

    if (pirateA == NULL || pirateB == NULL) {
        // Handle null pointers as needed
        return 0; // You can adjust this as per your requirements
    }

    const char *sortFlag = get_flag(); // Get the sort flag

    // Handle sorting by names (default)
    if (sortFlag == NULL || strcmp(sortFlag, "-n") == 0) {
        return strcmp(pirateA->name, pirateB->name);
    }
    // Handle sorting by vessels
    else if (strcmp(sortFlag, "-v") == 0) {
        const char *vesselA = pirateA->vessel;
        const char *vesselB = pirateB->vessel;

        // Pirates without a vessel should be sorted by name
        if (vesselA == NULL && vesselB == NULL) {
            return strcmp(pirateA->name, pirateB->name);
        } else if (vesselA == NULL) {
            return 1; // PirateA has a null vessel, so it should appear last
        } else if (vesselB == NULL) {
            return -1; // PirateB has a null vessel, so it should appear last
        } else {
            return strcmp(vesselA, vesselB);
        }
    }
    // Handle sorting by treasures (in descending order)
    else if (strcmp(sortFlag, "-t") == 0) {
        int treasureDiff = pirateB->treasures - pirateA->treasures;
        if (treasureDiff == 0) {
            // If treasures are equal, sort tied pirates by names
            return strcmp(pirateA->name, pirateB->name);
        } else {
            return treasureDiff;
        }
    }
    // Default case (sorting by names)
    return strcmp(pirateA->name, pirateB->name);
}



// Parameters: pirate list, comparison function pointer, and integer variables
// Returns: nothing
// Purpose: Merge two subarrays based on custom comparison
void merge(pirate *arr[], int l, int m, int r, int (*comp)(const void*, const void*)) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Merge the subarrays back into the original array in-place
    pirate *tempArr[r - l + 1];

    i = 0; // Index for the first subarray
    j = 0; // Index for the second subarray
    k = l; // Index for the merged array

    while (i < n1 && j < n2) {
        if (comp(arr[l + i], arr[m + 1 + j]) <= 0) {
            tempArr[k - l] = arr[l + i];
            i++;
        } else {
            tempArr[k - l] = arr[m + 1 + j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        tempArr[k - l] = arr[l + i];
        i++;
        k++;
    }

    while (j < n2) {
        tempArr[k - l] = arr[m + 1 + j];
        j++;
        k++;
    }

    for (i = l; i <= r; i++) {
        arr[i] = tempArr[i - l];
    }
}

// Parameters: pirate list, comparison function pointer, and integer variables
// Returns: nothing
// Purpose: merge sort function
void mergeSort(pirate *arr[], int l, int r, int (*comp)(const void*, const void*)) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comp);
        mergeSort(arr, m + 1, r, comp);
        merge(arr, l, m, r, comp);
    }
}

// Parameters: pirate list
// Returns: nothing
// Purpose: merge sort function
void list_sort(pirate_list *pirates) {
    if (pirates != NULL && pirates->size > 1) {
        // Use the comparison function specified in the pirate_list
        mergeSort(pirates->array, 0, pirates->size - 1, pirates->compare);
    }
}

  
// Parameters: pirate list
// Returns: size of pirate list
// Purpose: Function to get the length of the pirate list
size_t list_length(pirate_list *pirates)
{
    if (pirates != NULL)
    {
        return pirates->size; // Return the size of the list
    }
    
    return 0; // Return 0 if the list is NULL
}

// Parameters: pirate list
// Returns: nothing
// Purpose: Function to destroy a pirate list and free associated memory
void list_destroy(pirate_list *pirates)
{
    if (pirates == NULL)
    {
        return;
    }
    if (pirates->array != NULL)
    {
        for (size_t i = 0; i < pirates->size; i++)
        {
            if (pirates->array[i] != NULL)
            {
                pirate_destroy(pirates->array[i]); // Destroy individual pirates in the list
            }

        }
        free(pirates->array); // Free the memory for the pirate array
    }

    free(pirates); // Free the memory for the pirate list structure
}

// Parameters: pirate list
// Returns: nothing
// Purpose: Function to expand the pirate list if necessary
void list_expand_if_necessary(pirate_list *pirates)
{
    if (pirates != NULL)
    {
        if (pirates->size + 1 >= pirates->capacity)
        {
            // Calculate the new capacity by multiplying the current capacity by RESIZE_FACTOR
            size_t new_capacity = pirates->capacity * RESIZE_FACTOR;

            if (new_capacity > pirates->capacity)
            {
                pirate **new_array = realloc(pirates->array, new_capacity * sizeof(pirate*));

                pirates->capacity = new_capacity;
                pirates->array = new_array;

                fprintf(stderr, "Expand to %zu\n", new_capacity);
            }

            
        }   
    }
}

// Parameters: pirate list
// Returns: nothing
// Purpose: Function to contract the pirate list if necessary
void list_contract_if_necessary(pirate_list *pirates)
{
     if (pirates != NULL) 
     {
        // Calculate the new capacity by dividing the current capacity by RESIZE_FACTOR
        size_t new_capacity = pirates->capacity / RESIZE_FACTOR;

        // Ensure the new capacity is not below the initial capacity
        if (new_capacity < INITIAL_CAPACITY) 
        {
            new_capacity = INITIAL_CAPACITY;
        }

        if (pirates->size < new_capacity && pirates->capacity > INITIAL_CAPACITY)
        {
            // pirate **new_array = malloc(new_capacity * sizeof(pirate*));
            pirate **new_array = realloc(pirates->array, new_capacity * sizeof(pirate*));

            pirates->array = new_array;
            pirates->capacity = new_capacity;

            fprintf(stderr, "Contract to %zu\n", new_capacity);
        }
     }
}

// Parameters: pirate list, pirate name
// Returns: pirate pointer
// Purpose: Function to look for pirate by name
pirate* find_pirate_by_name(const char* name, pirate_list* pirates) {
    if (name == NULL || pirates == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < pirates->size; i++) {
        if (pirates->array[i] != NULL && pirates->array[i]->name != NULL) {
            if (strcmp(pirates->array[i]->name, name) == 0) {
                return pirates->array[i]; // Match found, return the pointer to the pirate
            }
        }
    }

    return NULL; // No matching pirate found
}
