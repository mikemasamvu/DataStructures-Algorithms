/*
 * Station.cpp
 * CPSC 223 Pset 5
 *
 * Implementation of the Station class
 * TO STUDENT: Don't forget to remove // TODO before you submit!
 *
 * Author: Mike Masamvu
 */

#include "Station.h"

// Default Constructor (Implemented for you)
Station::Station()
{
    this->name = "NoName";
    this->access = false;
}

// Parameters: name, bool
// Returns: Station
// Purpose: Function to create Station
Station::Station(string name, bool access)
{
    this->name = name;
    this->access = access;
}

// Parameters: station
// Returns: bool
// Purpose: Function to check if two stations are equal
bool Station::isEqual(Station s)
{
    // Check if name and access are the same
    if (this->name == s.name && this->access == s.access)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Parameters: output file
// Returns: nothing
// Purpose: Function to print station
void Station::print(ostream &outfile)
{
    if (getAccess())
    {
        outfile << getName() << " " << "A";
    }
    else
    {
        outfile << getName() << " " << "U";
    }
}
