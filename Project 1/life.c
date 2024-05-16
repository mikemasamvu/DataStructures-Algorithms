/*
Implementation functions for Game of Life assignment in CPSC 223 Fall 2023

Author: Mike Masamvu
*/
#include "life.h"
#include <stdio.h>
#include <stdbool.h>

// isAlive returns true if cell is alive, else return false
bool isAlive(int field[], size_t i, size_t size)
{
    // Check to see if index is in range
    if ((i < 0) || (i > size - 1))
    {
        printf("Index out of scope\n");
        exit(1);
    }
    else 
    {
        if (field[i] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }   
}

// shouldDie returns true if cell should die else return false
bool shouldDie(int field[], size_t i, size_t size)
{
    // Check to see if index is in range
    if ((i < 0) || (i > size - 1))
    {
        printf("Index out of scope\n");
        exit(1);
    }
    // First and last cell do not die once they are alive, hence always return false
    else if ((i == 0) || (i == size - 1))
    {
       return false;
    } 
    else
    {
        // Check neighbours to see if they are both activate, if so return true, else return false
        if ((field[i - 1] == 1) && (field[i + 1] == 1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// shouldLive checks if cell should be made alive
bool shouldLive(int field[], size_t i, size_t size) 
{
    // Check to see if index is in range
    if ((i < 0) || (i > size - 1))
    {
        printf("Index out of scope\n");
        exit(1);
    }
    else if (i == 0)
    {
       // For first element, only checking the element in front 
       // Return true if cell in front is alive
       if (field[i + 1] == 1) 
       {
            return true;
       }
       else
       {
            return false;
       }
    }
    else if (i == size - 1)
    {
       // For last element, only checking the element before it 
       // Return true if cell alive if element before it is alive
       if (field[i - 1] == 1) 
       {
            return true;
       }
       else
       {
            return false;
       }
    }
    else
    {
        // Check for the neighbours of the cell
        // Return true only if at least one of the neighbour cells is alive
        if ((field[i - 1] == 1) || (field[i + 1] == 1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// activate_cell activates cell at index i
void activate_cell(int field[], size_t i, size_t size)
{
    // Check to see if index is in range
    if ((i < 0) || (i > size - 1))
    {
        printf("Index out of scope\n");
        exit(1);
    }
    else
    {
        field[i] = 1;
    }
}

// kill_cell kills cell at index i
void kill_cell(int field[], size_t i, size_t size)
{
    // Check to see if index is in range
    if ((i < 0) || (i > size - 1))
    {
        printf("Index out of scope\n");
        exit(1);
    }
    else
    {
        field[i] = 0;
    }
}

