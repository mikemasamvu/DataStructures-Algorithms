#include "gmap.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/************** headers **************
Filename: gmap.c
Creator: Mike Masamvu
Class: CS223 Homework 3
Date: 11/01/2023
Purpose: Contains fuctions for my gmap functions
*/

char *gmap_error = "error";

typedef struct entry
{
    struct entry *next;
    void *key;
    void *value;
} entry;

struct _gmap
{
    entry **table;
    size_t capacity;
    size_t size;
    size_t (*hash)(const void *);
    int (*compare)(const void *, const void *);
    void *(*copy)(const void *);
    void (*free)(void *); 
};

#define GMAP_INITIAL_CAPACITY 100
#define MAX_LOAD_FACTOR 1

/**
 * Resizes the array holding the elements in the given map.  The current
 * implementation does nothing.
 *
 * @param m a pointer to a map, non-NULL
 */
void gmap_embiggen(gmap *m);

// Parameters: function pointers
// Returns: gmap
// Purpose: Function to create a gmap
gmap *gmap_create(void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *s), void (*f)(void *))
{
    if (h == NULL || cp == NULL || comp == NULL || f == NULL)
    {
        // one of the required functions was missing
        return NULL;
    }

    gmap *result = malloc(sizeof(gmap));
    if (result != NULL)
    {
        // remember the functions used to manipulate the keys
        result->copy = cp;
        result->compare = comp;
        result->hash = h;
        result->free = f;

        // initialize the table
        result->table = malloc(sizeof(entry *) * GMAP_INITIAL_CAPACITY);
        if (result->table == NULL)
        {
            return NULL;
        }
        for (size_t i = 0; i < GMAP_INITIAL_CAPACITY; i++) {
            result->table[i] = NULL;
        }
        result->capacity = (result->table != NULL ? GMAP_INITIAL_CAPACITY : 0);
        result->size = 0;
    }
    return result;
}

// Parameters: gmap
// Returns: gmap size
// Purpose: Function to find size of gmap
size_t gmap_size(const gmap *m)
{
    if (m == NULL)
    {
        return 0;
    }

    return m->size;
}

// Parameters: gmap, key, value
// Returns: nothing
// Purpose: Function to put a player struct into gmap
void *gmap_put(gmap *m, const void *key, void *value)
{
    if (m == NULL || key == NULL)
    {
        return gmap_error;
    }

    if (m->size >= m->capacity * MAX_LOAD_FACTOR)
    {
        // table is full
        gmap_embiggen(m);
        
    }

    // find key
    size_t index = m->hash(key) % m->capacity;
    entry *current = m->table[index];
    entry *previous = NULL;

    while (current != NULL)
    {
            if (m->compare(current->key, key) == 0)
            {
                // Replace older value and return it
                void *old_value = current->value;
                current->value = value; 
                return old_value;
            }
            previous = current;
            current = current->next;
    }

    if (m->size >= m->capacity * MAX_LOAD_FACTOR)
    {
        return gmap_error;
    }
    
    // Entry doesnt exist hence add it
    entry *new_entry = malloc(sizeof(entry));
    if (new_entry != NULL)
    {
        new_entry->key = m->copy(key);
        new_entry->value = value;
        new_entry->next = NULL;

        if (previous == NULL)
        {
            m->table[index] = new_entry;
        }
        else
        {
            previous->next = new_entry;
        }
        m->size++;
    } 
    return NULL;
}

// Parameters: gmap, key
// Returns: nothing
// Purpose: Function to remove a player struct from gmap
void *gmap_remove(gmap *m, const void *key)
{
    if (m == NULL || key == NULL)
    {
        return gmap_error;
    }

    // hash key
    size_t index = m->hash(key) % m->capacity;

    entry *current = m->table[index];
    entry *previous = NULL;

    while (current != NULL)
    {
        // Find key
        if (m->compare(current->key, key) == 0)
        {
            if (previous == NULL)
            {
                m->table[index] = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            
            // Return removed value
            void *removed_value = current->value;
            m->free(current->key);
            free(current);
            m->size--;
            return removed_value;
        }

        previous = current;
        current = current->next;
    }
    return NULL;
}

// Parameters: gmap
// Returns: nothing
// Purpose: Function to grow hash map
void gmap_embiggen(gmap *m)
{
    if (m == NULL)
    {
        return;
    }

    size_t new_capacity = m->capacity * 2;
    entry **new_table = malloc(new_capacity * sizeof(entry *));
    if (new_table == NULL) 
    {
        return;
    }
    for (size_t i = 0; i < new_capacity; i++) {
        new_table[i] = NULL;
    }

    // Resize hash map
    for (size_t i = 0; i < m->capacity; i++)
    {
        entry *current = m->table[i];
        while (current != NULL)
        {
            size_t index = m->hash(current->key) % new_capacity;

            entry *next = current->next;
            current->next = new_table[index];
            new_table[index] = current;
            current = next;
        }
    }
    free(m->table);
    m->table = new_table;
    m->capacity = new_capacity;
}

// Parameters: gmap, key
// Returns: boolean
// Purpose: Function to check if key exists
bool gmap_contains_key(const gmap *m, const void *key)
{
    if (m == NULL || key == NULL)
    {
        return false;
    }

    size_t index = m->hash(key) % m->capacity;
    entry *current = m->table[index];

    // Check if key exists
    while (current != NULL)
    {
        if (m->compare(current->key, key) == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Parameters: gmap, key
// Returns: nothing
// Purpose: Function to get value of an entry
void *gmap_get(gmap *m, const void *key)
{
    if (m == NULL || key == NULL)
    {
        return gmap_error;
    }

    size_t index = m->hash(key) % m->capacity;
    entry *current = m->table[index];

    // Check if key exists
    while (current != NULL)
    {
        if (m->compare(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

// Parameters: gmap, pointer function, arg
// Returns: nothing
// Purpose: Function to perform an operation on gmap using given function
void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg)
{
    if (m == NULL || f == NULL)
    {
        return;
    }

    // Traverse through the gmap
    for (size_t i = 0; i < m->capacity; i++)
    {
        entry *current = m->table[i];
        while (current != NULL)
        {
            f(current->key, current->value, arg);
            current = current->next;
        }
    }
}

// Parameters: gmap
// Returns: list of keys
// Purpose: Function to find all the keys in the gmap
const void **gmap_keys(gmap *m)
{
    if (m == NULL)
    {
        return NULL;
    }

    const void **keys = malloc(sizeof(const void *) * m->size);
    if (keys == NULL)
    {
        return NULL;
    }

    size_t index = 0;

    // Traverse through the gmap
    for (size_t i = 0; i < m->capacity; i++)
    {
        entry *current = m->table[i];
        while (current != NULL)
        {
            keys[index] = current->key;
            index++;
            current = current->next;
        }
    }

    return keys;
}

// Parameters: gmap
// Returns: nothing
// Purpose: Destory the gmap
void gmap_destroy(gmap *m)
{
    if (m == NULL)
    {
        return;
    }

    for (size_t i = 0; i < m->capacity; i++)
    {
        // Traverse through the gmap
        entry *current = m->table[i];
        while (current != NULL)
        {
            entry *next = current->next;
            m->free(current->key);
            free(current);
            current = next;
        }
    }
    free(m->table);
    free(m);
}