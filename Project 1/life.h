#ifndef __LIFE_H__
#define __LIFE_H__

/*
Interface for Game of Life assignment in CPSC 223 Fall 2023.

Author: Alan Weide

TO STUDENT: You may add to this file, but do not change anything that is already here!
Remember, this is a header file: there should be no function bodies here, only prototypes.
Modified by: Mike Masamvu on 09/13/2023
Changelog: added shouldLive function which checks if a cell at index i should be activated, activate_cell function which activates
a cell that was previously dead, and kill_cell function which kills a cell that should "die"
*/

#include <stdbool.h>
#include <stdlib.h>

bool isAlive(int field[], size_t i, size_t size);

bool shouldDie(int field[], size_t i, size_t size);

bool shouldLive(int field[], size_t i, size_t size);

void activate_cell(int field[], size_t i, size_t size);

void kill_cell(int field[], size_t i, size_t size);

#endif