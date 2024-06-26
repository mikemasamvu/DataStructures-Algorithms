/*
 * Filename: AVLTree.cpp
 * Contains: Implementation of AVL Trees for CPSC 223
 * Part of: Homework assignment "AVL Trees" for CPSC 223
 */

#include <iostream>

#include "AVLTree.h"
#include "pretty_print.h"

using namespace std;

/********************************
 * BEGIN PUBLIC AVLTREE SECTION *
 ********************************/

/*
 * The AVLTree constructors use intializer lists. They are complete and you
 *  should not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
AVLTree::AVLTree() : root(new BSTNode()) {}

AVLTree::AVLTree(const AVLTree &source)
    : root(new BSTNode(*source.root)) {}

AVLTree::~AVLTree()
{
    delete this->root;
}

AVLTree &AVLTree::operator=(const AVLTree &source)
{
    if (this == &source)
    {
        return *this;
    }

    delete this->root;

    if (source.root)
    {
        this->root = new BSTNode(*source.root);
    }
    return *this;
}

int AVLTree::minimum_value() const
{
    return this->root->minimum_value()->data;
}

int AVLTree::maximum_value() const
{
    return this->root->maximum_value()->data;
}

unsigned int AVLTree::count_of(int value) const
{
    return this->root->search(value)->count;
}

void AVLTree::insert(int value)
{
    this->root = this->root->avl_insert(value);
}

void AVLTree::remove(int value)
{
    this->root = this->root->avl_remove(value);
}

int AVLTree::tree_height() const
{
    return this->root->node_height();
}

int AVLTree::node_count() const
{
    return this->root->node_count();
}

int AVLTree::count_total() const
{
    return this->root->count_total();
}

void AVLTree::print_tree() const
{
    print_pretty(*this->root, 1, 0, std::cout);
}
