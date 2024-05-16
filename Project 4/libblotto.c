#include "libblotto.h"
#include "gmap.h"
#include "entry.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/************** headers **************
Filename: libblotto.c
Creator: Mike Masamvu
Class: CS223 Homework 3
Date: 11/01/2023
Purpose: Contains fuctions for my Blotto implementation
*/

// Parameters: key
// Returns: hashed value
// Purpose: Function to create a hash value from a given key
size_t java_hash_string(const void *key)
{
    const char *s = key;

    // from Java's String.hashCode()
    // https://docs.oracle.com/javase/7/docs/api/java/lang/String.html#hashCode()
    if (s == NULL)
    {
        return 0;
    }

    size_t power = 31;
    size_t hash = 0;
    const char *p = s + strlen(s) - 1;
    while (p >= s)
    {
        hash += power * *p;
        power *= 31;
        p--;
    }

    return hash;
}

// Parameters: keys
// Returns: nothing
// Purpose: Function to create duplicate a given key
void *duplicate(const void *key)
{
    char *s = malloc(strlen(key) + 1);
    if (s != NULL)
    {
        strcpy(s, key);
    }
    return s;
}

// Parameters: 2 keys
// Returns: integer
// Purpose: Function to compare two keys
int compare_keys(const void *key1, const void *key2)
{
    return strcmp(key1, key2);
}

// Parameters: key, value, gmap
// Returns: hashed value
// Purpose: Free entry value
void free_distributions(const void *key, void *value, void *arg) {
    // Free the value if not null
    if (value != NULL) {
        free(value);
    }
}

// Parameters: 2 keys, battlefield values, battlefield count
// Returns: nothing
// Purpose: Calculates scores for the players and print to stdout using specified format
void calculate_score(gmap *playerMap, const char *player1Id, const char *player2Id, const int *battlefieldValues, int numBattlefields) {
    int *player1Distribution = gmap_get(playerMap, player1Id);
    int *player2Distribution = gmap_get(playerMap, player2Id);

    if (player1Distribution == NULL || player2Distribution == NULL) {
        // Handle the case where either player is not found
        printf("%s 0.0 - %s 0.0\n", player1Id, player2Id);
        return;
    }

    float player1Score = 0.0;
    float player2Score = 0.0;


    // Calculate scores for the players
    for (int i = 0; i < numBattlefields; i++) {
        if (player1Distribution[i] > player2Distribution[i]) {
            player1Score += (float)battlefieldValues[i];
        } else if (player1Distribution[i] < player2Distribution[i]) {
            player2Score += (float)battlefieldValues[i];
        } else {
            player1Score += 0.5 * (float)battlefieldValues[i];
            player2Score += 0.5 * (float)battlefieldValues[i];
        }
    }

    // Print to stdout using specified format
    if (player1Score > player2Score) {
        printf("%s %.1f - %s %.1f\n", player1Id, player1Score, player2Id, player2Score);
    } else if (player1Score < player2Score) {
        printf("%s %.1f - %s %.1f\n", player2Id, player2Score, player1Id, player1Score);
    } else {
        printf("%s %.1f - %s %.1f\n", player1Id, player1Score, player2Id, player2Score);
    }
}

// Parameters: file, battlefield numbers, battlefield count
// Returns: nothing
// Purpose: Main implementation for Blotto
void *implementation(FILE *in, int *numbers, int battlefields)
{
    int check_input = 0; // Flag to check if total units for all players are the same
    gmap *m = gmap_create(duplicate, compare_keys, java_hash_string, free);

    while (1) {
        player_entry result = entry_read(stdin, 31, battlefields);

        // Invalid input in file
        if (result.id == NULL && result.distribution == NULL) {  
            printf("Invalid entry\n");
            break;
        }
        else if (result.id != NULL && result.distribution == NULL)
        {
            if (check_input == 0)
            {
                printf("Invalid entry\n"); // File is empty
                free(result.id);
                break;
            }

            char player1[32], player2[32];
            // Calculates scores for the players and print to stdout using specified format
            while (fscanf(stdin, "%31s %31s", player1, player2) == 2) {
                calculate_score(m, player1, player2, numbers, battlefields); 
            }
            free(result.id);
            break;
        }

        // Print the result (adjust this part based on your actual entry structure)
        
        if (result.distribution != NULL)
        {
            // Check if total units for all players are the same
            int score = 0;
            for (int i = 0; i < battlefields; i++) {
                score += result.distribution[i];
            }
            if (check_input == 0)
            {
                check_input = score;
                gmap_put(m, result.id, result.distribution);
            }
            else if (score != check_input)
            {
                printf("Invalid entry\n");
                free(result.id);
                free(result.distribution);
                break; // battlefield count isnt equal to each other
            }
            else
            {
                gmap_put(m, result.id, result.distribution);
            }
        }
        

        // Clean up memory
        free(result.id);
    }

    // // Clean up memory 
    gmap_for_each(m, free_distributions, m);
    gmap_destroy(m);
    return NULL;
}


