#ifndef __LIBBLOTTO_H__
#define __LIBBLOTTO_H__

/*
Author: Mike Masamvu
Modified by: Mike Masamvu on 11/01/2023
*/
#include "gmap.h"
#include <stdio.h>

/**
 * Frees the entry values in the gmap
 */
void free_distributions(const void *key, void *value, void *arg);

/**
 * Calculates scores for each player and print them in the specified format.
 */
void calculate_score(gmap *playerMap, const char *player1Id, const char *player2Id, const int *battlefieldValues, int numBattlefields);

/**
 * Hashing function 
 */
size_t java_hash_string(const void *key);

/**
 * Creates a duplicate of the key
 */
void *duplicate(const void *key);

/**
 * Compare two keys
 */
int compare_keys(const void *key1, const void *key2);

/**
 * Main Blotto implementation
 */
void *implementation(FILE *in, int *numbers, int battlefields);

#endif