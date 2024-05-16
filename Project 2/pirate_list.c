#include "pirate_list.h"
#include "pirate.h"
#include <stdlib.h>
#include <string.h>

// Structure definition for the pirate list instance
struct pirate_list_instance_t
{
    pirate **array;
    size_t size;
    size_t capacity;
    
};

#define INITIAL_CAPACITY 25
#define RESIZE_FACTOR 2

// Function to create a new pirate list
pirate_list *list_create()
{
    pirate_list *new_pirate_list = malloc(sizeof(pirate_list));
    
    if (new_pirate_list != NULL)
    {
        new_pirate_list->size = 0; // Initialize the size to 0
        new_pirate_list->capacity = INITIAL_CAPACITY;
        new_pirate_list->array = malloc(new_pirate_list->capacity * sizeof(pirate));
    }
    else
    {
        return NULL;
    }

    return new_pirate_list;
}

// Function to find the index of a pirate in the list
size_t list_index_of(pirate_list *pirates, pirate *p)
{
    if (pirates == NULL || p->name == NULL)
    {
        return pirates->size;
    }
    for (size_t i = 0; i < pirates->size; i++)
    {
        if (pirate_compare(pirates->array[i], p) == 0)
        {
            return i;
        }
    }
    
    return pirates->size;
}

// Function to insert a pirate at a specified index in the list
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
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
    return p;
}

// Function to remove a pirate from the list
pirate *list_remove(pirate_list *pirates, pirate *p)
{
    if (list_index_of(pirates, p) != pirates->size)
    {
        size_t j = list_index_of(pirates, p);
        for (size_t i = j; i < pirates->size - 1; i++) 
        {
            pirates->array[i] = pirates->array[i + 1]; // Shift elements to fill the gap left by the removed pirate
        }
        pirates->size--;

        list_contract_if_necessary(pirates); // Contract the list if necessary

        return pirates->array[j]; // Return the removed pirate
        
    }

    return NULL; // Return NULL if the pirate is not found in the list
}

// Function to access a pirate at a specified index in the list
pirate *list_access(pirate_list *pirates, size_t idx)
{
    if (idx >= pirates->size)
    {
        return NULL; // Return NULL if the index is out of bounds
    }

    return pirates->array[idx]; // Return the pirate at the specified index
}

void merge(pirate* arr[], int l, int m, int r)
{
    int left = m - l + 1;
    int right = r - m;

    // Duplicate array data into temporary arrays
    pirate* larray[left];
    pirate* rarray[right];

    // Copy data to temporary arrays larray[] and rarray[]
    for (int i = 0; i < left; i++) {
        larray[i] = arr[l + i];
    }
    for (int j = 0; j < right; j++) {
        rarray[j] = arr[m + 1 + j];
    }

    // Re-merge the two subarrays
    int i = 0; // Initial index of the first subarray
    int j = 0; // Initial index of the second subarray
    int k = l; // Initial index of the merged subarray

    while (i < left && j < right) {
        if ((pirate_compare(larray[i], rarray[j])) <= 0)
        {
            arr[k] = larray[i];
            i++;
        } 
        else 
        {
            arr[k] = rarray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of larray[]
    while (i < left) {
        arr[k] = larray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rarray[]
    while (j < right) {
        arr[k] = rarray[j];
        j++;
        k++;
    }
}

void mergeSort(pirate* arr[], int l, int r)
{
    if (l < r) {
        // Same as (l + r) / 2, but avoids overflow for large l and r
        int middle = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, middle);
        mergeSort(arr, middle + 1, r);

        // Merge the sorted halves
        merge(arr, l, middle, r);
    } 
}

// Function to sort a pirate list using merge sort
void list_sort(pirate_list *pirates)
{
    if (pirates != NULL && pirates->size > 1) {
        // Sort the pirate list using merge sort
        mergeSort(pirates->array, 0, pirates->size - 1);
    }
}      

// Function to get the length of the pirate list
size_t list_length(pirate_list *pirates)
{
    if (pirates != NULL)
    {
        return pirates->size; // Return the size of the list
    }
    
    return 0; // Return 0 if the list is NULL
}

// Function to destroy a pirate list and free associated memory
void list_destroy(pirate_list *pirates)
{
    if (pirates != NULL)
    {
        for (size_t i = 0; i < pirates->size; i++)
        {
            pirate_destroy(pirates->array[i]); // Destroy individual pirates in the list
        }
        free(pirates->array); // Free the memory for the pirate array
        free(pirates); // Free the memory for the pirate list structure
    }
}

// Function to expand the pirate list if necessary
void list_expand_if_necessary(pirate_list *pirates)
{
    if (pirates != NULL)
    {
        if (pirates->size + 1 >= pirates->capacity)
        {
            // Calculate the new capacity by multiplying the current capacity by RESIZE_FACTOR
            size_t new_capacity = pirates->capacity * RESIZE_FACTOR;

            pirate **new_array = malloc(new_capacity * sizeof(pirate*));

            for (size_t i = 0; i < pirates->size; i++)
            {
                new_array[i] = pirates->array[i]; // copy elements into new_array
            }

            free(pirates->array); // free memory used by pirates array

            pirates->capacity = new_capacity;
            pirates->array = new_array;

            fprintf(stderr, "Expand to %zu\n", new_capacity);
            }   
    }
}

// Function to contract the pirate list if necessary
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

            if (new_array != NULL)
            {
                pirates->array = new_array;
                pirates->capacity = new_capacity;

                fprintf(stderr, "Contract to %zu\n", new_capacity);
            }

            // Copy the existing pirates into the new array
            // for (size_t i = 0; i < pirates->size; i++) 
            // {
            //     new_array[i] = pirates->array[i];
            // }

            // // Free the old pirate array
            // free(pirates->array);

            // // Update the pirate list's capacity and array with the new values
            // pirates->capacity = new_capacity;
            // pirates->array = new_array;

            // fprintf(stderr, "Contract to %zu\n", new_capacity);
        }
     }
}