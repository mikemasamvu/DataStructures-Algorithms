/*
 * LinkedList.cpp
 * CPSC 223 Pset 5
 *
 * Implementation for Linked List of GNHTA Stations
 * TO STUDENT: Don't forget to remove // TODO when you submit!
 *
 * Author: Mike Masamvu
 */

#include "LinkedList.h"
using namespace std;

// Default constructor
LinkedList::LinkedList()
{
    this->length = new int(0);
    this->stations = nullptr;
    resetCurrPos();
}

// Destructor
LinkedList::~LinkedList()
{
    makeEmpty();
    delete length;
}

// Assignment operator overload.
LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    makeEmpty();
    NodeType *current = rhs.stations;
    while (current != nullptr)
    {
        NodeType *newNode = new NodeType;
        newNode->info = current->info;
        insertStation(newNode->info);
        current = current->next;
    }

    *length = *(rhs.length);
    return *this;
}

// Copy constructor
LinkedList::LinkedList(const LinkedList &other)
{
    this->length = new int(*(other.length));
    this->stations = nullptr;  // Initialize stations to nullptr
    resetCurrPos();  // Reset currPos to nullptr
    NodeType *current = other.stations;
    while (current != nullptr)
    {
        NodeType *newNode = new NodeType;
        newNode->info = current->info;
        newNode->next = this->stations;
        this->stations = newNode;
        current = current->next;
    }
}

// Parameters: none
// Returns: length of this linkedlist
// Purpose: Function to return length of linkedlist
int LinkedList::getLength() const
{
    return *length;
}

// Parameters: none
// Returns: bool
// Purpose: Function to check if currPos is NULL or not
bool LinkedList::isCurrPosNull() const
{
    if (this->currPos == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Parameters: station
// Returns: none
// Purpose: Function to insert station into linkedlist
void LinkedList::insertStation(Station s)
{
    NodeType *newNode = new NodeType;
    newNode->info = s;
    newNode->next = this->stations; // inserted station should point to previous head pointer
    this->stations = newNode; // inserted station should pointer to the head pointer
    (*length)++; // increase length after successfully inserting station
}

// Parameters: station
// Returns: none
// Purpose: Function to remove station from linkedlist
void LinkedList::removeStation(Station s)
{
    NodeType *current = this->stations;
    NodeType *previous = nullptr;

    while (current != nullptr && !current->info.isEqual(s)) // Look for station
    {
        previous = current;
        current = current->next;
    }

    if (current != nullptr)
    {
        // Update next pointer of previous node
        if (previous != nullptr)
        {
            previous->next = current->next;
        }
        // Update stations, if first node to be removed
        else
        {
            this->stations = current->next;
        }
        // Reset currPos if it is the station removed
        if (current == this->currPos)
        {
            resetCurrPos();
        }
        delete current;
        (*length)--; // decrease length after successful removal
    }
}

// Parameters: none
// Returns: station
// Purpose: Function to get next station
Station LinkedList::getNextStation()
{
    if (this->currPos == nullptr)
    {
        this->currPos = this->stations;
    }

    Station currStation = this->currPos->info;

    if (this->currPos->next != nullptr)
    {
        this->currPos = this->currPos->next; // Update currPos
    }
    else
    {
        resetCurrPos();
    }

    return currStation;
}

// Parameters: none
// Returns: none
// Purpose: Function to reset currPos
void LinkedList::resetCurrPos()
{
    this->currPos = nullptr;
}

// Parameters: none
// Returns: none
// Purpose: Function to empty linkedlist and free all memory allocated
void LinkedList::makeEmpty()
{
    NodeType *current = this->currPos;
    while (current != nullptr)
    {
        NodeType *next = current->next; // traverse through the linkedlist
        delete current;
        current = next;
    }

    resetCurrPos(); // reset currPos
    this->stations = nullptr;
    *length = 0;
}

// Parameters: output file
// Returns: none
// Purpose: Function to print stations in the linkedlist 
void LinkedList::print(ostream &out)
{
    NodeType *current = this->stations;

    if (current == nullptr)
    {
        out << '\n';
        return;
    }

    int stops = getLength(); // length of linkedlist
    while (current != nullptr) // traverse through the linkedlist
    {
        current->info.print(out);
        out << " " << stops - 1;
        
        if (current->next != nullptr)
        {
            out << " == ";
        }
        else
        {
            out << '\n';
        }

        current = current->next;
        stops--;
    }
}
