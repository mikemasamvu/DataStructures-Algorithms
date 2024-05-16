#include "BSTNode.h"

#include <cassert>
#include <algorithm>
#include <string>

/**
 * A pseudo-assert macro that immediately returns from the enclosing function
 *  if e is false.
 */
#define ABORT_UNLESS(e) \
    if (!(e))           \
    {                   \
        return;         \
    }

/**
 * This function is implemented for you, for your convenience.
 *
 * Input: Node node - the node to decorate
 * Returns: the decorator to print with this node using its to_string function.
 *      The decorator is either nothing, '*', 'r', or 'R' (computed as node is
 *      BLACK with count <=1, BLACK with count >1, RED with count =1, or RED
 *      with count >1).
 */
std::string decorator_string(const BSTNode *node)
{
    std::string dec = "";
    if (node && node->node_height() >= 0)
    {
        if (node->color == BSTNode::Color::RED)
        {
            if (node->count > 1)
            {
                dec = "R";
            }
            else
            {
                dec = "r";
            }
        }
        else
        {
            if (node->count > 1)
            {
                dec = "*";
            }
        }
    }
    return dec;
}

/**
 * This function is implemented for you, for your convenience.
 *
 * Input: Node node - the node to get the value label for
 * Returns: node's data as a string, or empty_string if node is an empty tree.
 */
std::string value_string(const BSTNode *node)
{
    std::string value = "";
    if (node && node->node_height() >= 0)
    {
        value = std::to_string(node->data);
    }
    return value;
}

/**
 * This function is implemented for you, for your conveninence.
 *
 * Input: Node a
 *        Node b
 * Returns: N/A
 * Does: Swaps the colors of Nodes a and b.
 * Assumes: a and b are both non-null
 */
void swap_colors(BSTNode *a, BSTNode *b)
{
    BSTNode::Color t = a->color;
    a->color = b->color;
    b->color = t;
}

/**
 * This function is implemented for you, for your convenience.
 *
 * It is implemented in two different ways (one of them commented out):
 *    - The commented-out version makes explicit that LEFT is the opposite of
 *      RIGHT, and that ROOT has no opposite
 *    - The uncommented version uses the fact that enum values in C++ are given
 *      integer values in increasing order starting at 0 and can be implicitly
 *      converted into an int. Since the Direction enum is defined in order
 *      LEFT, ROOT, RIGHT, the values are LEFT=0, ROOT=1, RIGHT=2.
 * Both exhibit constant time and space complexity so are asymptotically
 *  equivalent.
 *
 * Input: Direction dir
 * Returns: the opposite of dir, or ROOT if dir is ROOT.
 */
BSTNode::Direction opposite_direction(BSTNode::Direction dir)
{
    // BSTNode::Direction opp = dir;
    // if (dir == BSTNode::Direction::LEFT)
    // {
    //     opp = BSTNode::Direction::RIGHT;
    // }
    // else if (dir == BSTNode::Direction::RIGHT)
    // {
    //     opp = BSTNode::Direction::LEFT;
    // }
    // return opp;
    return BSTNode::Direction(BSTNode::Direction::RIGHT - dir);
}

/*
 * These BSTNode constructors use intializer lists. They are complete and you
 *  may not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
BSTNode::BSTNode() : count(0), height(-1), color(BLACK),
                     left(nullptr), right(nullptr), parent(nullptr) {}
BSTNode::BSTNode(int data)
    : data(data), count(1), height(0), color(BLACK),
      left(new BSTNode()), right(new BSTNode()), parent(nullptr) {}

/*
 * TODO: The BSTNode copy constructor is incomplete. You must complete it. You
 *  may use an initializer list, or you may write a traditional constructor
 *  function, or both.
 */
BSTNode::BSTNode(const BSTNode &other) {
    
    this->data = other.data;
    this->count = other.count;
    this->height = other.height;
    this->color = other.color;
    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;

    if (other.left)
    {
        this->left = new BSTNode(*other.left);
        this->left->parent = this;
    }

    if (other.right)
    {
        this->right = new BSTNode(*other.right);
        this->right->parent = this;
    }
}

/**
 * Destructor.
 * Input: Node this - the node to free
 * Returns: N/A
 * Does: Performs a post-order delete to free all memory owned by this.
 */
BSTNode::~BSTNode(){
    delete left;
    delete right;

}

std::string BSTNode::to_string() const
{
    return value_string(this) + decorator_string(this);
}

/**
 * Input: Node this - the root of the tree
 * Returns: a pointer to the node with the minimum value in the tree rooted
 *      at this
 * Assumes: this is not an empty tree
 */
const BSTNode *BSTNode::minimum_value() const
{
    const BSTNode *current = this;
    while (!current->left->is_empty())
    {
        current = current->left;
    }
    return current;
}

/**
 * Input: Node this - the root of the tree
 * Returns: a pointer to the node with the maximum value in the tree rooted
 *      at this.
 * Assumes: this is not an empty tree
 */
const BSTNode *BSTNode::maximum_value() const
{
    const BSTNode *current = this;
    while (!current->right->is_empty())
    {
        current = current->right;
    }
    return current;
}

/**
 * Input: Node this - the root of the tree
 *        int value - the value for which to search in the tree
 * Returns: a pointer to the node with value in the tree rooted at this
 * Does: performs a search in the tree rooted at this and returns the
 *      node with that value in the tree, or an empty tree if the value
 *      does not appear in the tree rooted at this.
 */
const BSTNode *BSTNode::search(int value) const
{
    const BSTNode *current = this;
    while (!current->is_empty())
    {
        if (value == current->data)
        {
            return current;
        }
        else if (value < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return current;
}

/**
 * Input: Node this - the root of the tree
 *        int value - the value to insert
 * Returns: a pointer to the root of the tree into which value has just
 *      been inserted, with parent `nullptr`
 * Does: inserts (a single occurrence of) value into the tree rooted at
 *      this. Uses the "naive BST" insertion algorithm.
 */
BSTNode *BSTNode::insert(int value)
{
    if (is_empty()) {
        delete this;
        return new BSTNode(value);
    }

    if (value < data) {
        // Insert recursively on the left if left child exists, else create a new left child
        left = left ? left->insert(value) : new BSTNode(value);
    } else if (value > data) {
        // Insert recursively on the right if right child exists, else create a new right child
        right = right ? right->insert(value) : new BSTNode(value);
    } else {
        // If the value is equal to the current node's data
        count++;
        return this;
    }

    this->make_locally_consistent();
    return this;
}

/**
 * Input: Node this - the root of the tree
 *        int value - the value to insert
 * Returns: a pointer to the root of the tree into which value has just
 *      been inserted, with parent `nullptr`. The returned tree is an AVL
 *      Tree.
 * Does: inserts (a single occurrence of) value into the tree rooted at
 *      this. Uses the AVL Tree insertion algorithm.
 */
BSTNode *BSTNode::avl_insert(int value)
{
    /********************************
     ***** BST Insertion Begins *****
     ********************************/
    if (this->is_empty())
    {
        delete this;
        return new BSTNode(value);
    }

    if (value < data)
    {
        if (left)
        {
            left = left->avl_insert(value);
        }
        else
        {
            left = new BSTNode(value);
        }
        
    }
    else if (value > data)
    {
        if (right)
        {
            right = right->avl_insert(value);
        }
        else
        {
            right = new BSTNode(value);
        }
        
    }
    else
    {
        count++;
        return this;
    }
    
    /********************************
     ****** BST Insertion Ends ******
     ********************************/

    /********************************
     **** AVL Maintenance Begins ****
     ********************************/
    
    this->make_locally_consistent(); //update height and parent nodes
    return this->avl_balance(); // balance the tree

    /********************************
     ***** AVL Maintenance Ends *****
     ********************************/
}

/**
 * Input: Node this - the root of the tree
 *        int value - the value to insert
 * Returns: a pointer to the root of the tree into which value has just
 *      been inserted, with parent `nullptr`. The returned tree is a
 *      Red-Black Tree.
 * Does: inserts (a single occurrence of) value into the tree rooted at
 *      this. Uses the Red-Black Tree insertion algorithm.
 */
BSTNode *BSTNode::rb_insert(int value)
{
    /********************************
     ***** BST Insertion Begins *****
     ********************************/

    if (this->is_empty())
    {
        BSTNode *node = new BSTNode(value);
        node->color = RED;
        delete this; // free memory for existing object
        return node;
    }

    if (value < data)
    {
        if (left)
        {
            left = left->rb_insert(value);
        }
        else
        {
            left = new BSTNode(value);
            left->color = RED;
        }
    }
    else if (value > data)
    {
        if (right)
        {
            right = right->rb_insert(value);
        }
        else
        {
            right = new BSTNode(value);
            right->color = RED; 
        }
    }
    else
    {
        count++;
        return this;
    }

    /********************************
     ****** BST Insertion Ends ******
     ********************************/

    /********************************
     ***** RB Maintenance Begins ****
     ********************************/
    this->make_locally_consistent();
    return this->rb_eliminate_red_red_violation();

    /********************************
     ****** RB Maintenance Ends *****
     ********************************/
}

/**
 * Input: Node this - the root of the tree
 *        int value - the value to remove
 * Returns: a pointer to the root of the tree from which value has just
 *      been removed, whose parent pointer is `nullptr`. This method may
 *      return an empty tree.
 * Does: removes (a single occurrence of) value from the tree rooted at
 *      this. Uses the "naive BST" removal algorithm.
 */
BSTNode *BSTNode::remove(int value)
{
    BSTNode *root = this;
    if (this->is_empty())
    {
        return this;
    }

    if (value < data)
    {
        root->left = root->left->remove(value);
    }
    else if (value > data)
    {
        root->right = root->right->remove(value);
    }
    else
    {
        // If the count of the current node is greater than 1 (duplicate values)
        if (root->count > 1)
        {
            root->count--;
            return root;
        }
        
        // If both left and right subtrees are empty
        if (root->left->is_empty() &&
                root->right->is_empty())
        {
            this->parent = nullptr;
            delete this;
            root = new BSTNode();
        }
        // If only the left subtree is empty
        else if (root->left->is_empty())
        {
            root = this->right;
            this->right = nullptr;
            this->parent = nullptr;
            delete this;
        }
        // If only the right subtree is empty
        else if (root->right->is_empty())
        {
            root = root->left;
            this->left = nullptr;
            this->parent = nullptr;
            delete this;
        }
        // If both left and right subtrees are non-empty
        else
        {
            BSTNode *successor = (BSTNode *)root->right->minimum_value();
            root->data = successor->data;
            root->count = successor->count;
            successor->count = 1; // in order to be able to remove it
            root->right = root->right->remove(successor->data);
        }
    }
    root->make_locally_consistent();
    return root;
}

/**
 * Input: Node this - the root of the tree
 *        int value - the value to remove
 * Returns: a pointer to the root of the tree from which value has just
 *      been removed, whose parent pointer is `nullptr`. This method may
 *      return an empty tree. The returned tree is an AVL Tree.
 * Does: removes (a single occurrence of) value from the tree rooted at
 *      this. Uses the AVL Tree removal algorithm.
 */
BSTNode *BSTNode::avl_remove(int value)
{
    /********************************
     ****** BST Removal Begins ******
     ********************************/
    BSTNode *root = this;
    if (!root->is_empty())
    {
        if (value < root->data)
        {
            root->left = root->left->avl_remove(value);
        }
        else if (value > root->data)
        {
            root->right = root->right->avl_remove(value);
        }
        else
        {
            // If the count of the current node is greater than 1 (duplicate values)
            if (root->count > 1)
            {
                root->count--;
            }
            else
            {
                // If both left and right subtrees are empty
                if (root->left->is_empty() && root->right->is_empty())
                {
                    this->parent = nullptr;
                    delete this;
                    root = new BSTNode();
                }
                // If only the left subtree is empty
                else if (!root->left->is_empty() && root->right->is_empty())
                {
                    root = this->left;
                    this->left = nullptr;
                    this->parent = nullptr;
                    delete this;
                }
                // If only the right subtree is empty
                else if (root->left->is_empty() && !root->right->is_empty())
                {
                    root = this->right;
                    this->right = nullptr;
                    this->parent = nullptr;
                    delete this;
                }
                // If both left and right subtrees are non-empty
                else
                {
                    BSTNode *successor = (BSTNode *)root->right->minimum_value();
                    root->data = successor->data;
                    root->count = successor->count;
                    successor->count = 1;
                    root->right = root->right->avl_remove(successor->data);
                } 
            }
        }
    }

    /********************************
     ******* BST Removal Ends *******
     ********************************/

    /********************************
     **** AVL Maintenance Begins ****
     ********************************/
    root->make_locally_consistent();
    root = root->avl_balance();
    return root;

    /********************************
     ***** AVL Maintenance Ends *****
     ********************************/
}

BSTNode *BSTNode::rb_remove(int value)
{
    // This is implemented for you.
    BHVNeighborhood nb(this, ROOT);
    BSTNode *root = this->rb_remove_helper(value, nb);
    nb.fix_blackheight_imbalance();
    return root;
}

/**
 * Input: Node this - the root of the tree
 * Returns: the height of the tree rooted at this (an empty tree has height
 *      -1).
 */
int BSTNode::node_height() const
{
    if (this->is_empty())
    {
        return -1;
    }
    else
    {
        return this->height;
    }
}

 /**
 * Input: Node this - the root of the tree
 * Returns: the number of non-empty nodes in the tree rooted at this
 */
unsigned int BSTNode::node_count() const
{
    if (this->is_empty())
    {
        return 0;
    }
    else
    {
        unsigned int lcount = left->node_count();
        unsigned int rcount = right->node_count();
        
        return 1 + lcount + rcount;
    }
}

/**
 * Input: Node this - the root of the tree
 * Returns: the total of all counts in the tree rooted at this
 */
unsigned int BSTNode::count_total() const
{
    if (this->is_empty())
    {
        return 0;
    }
    // Calculate the total node count in the subtree rooted at the current node
    else
    {
        unsigned int ltotal = left->count_total();
        unsigned int rtotal = right->count_total();

        return this->count + ltotal + rtotal; // add the current node
    }
}

/**
 * Input: Node this - the node whose parent we are searching for
 *        Node root - the root of the tree in which to search
 * Returns: a pointer to the parent of this in the tree rooted at root, or
 *      nullptr if this is the root of the tree
 * Does: Searches the tree rooted at root for this, then returns that
 *      node's parent.
 * Assumes: this.data has nonzero count in the tree rooted at root
 */
const BSTNode *BSTNode::parent_in(BSTNode *root) const
{
    if (root->is_empty() || this == root)
    {
        return nullptr;
    } 
    // If the current node is the right child of the root and the right subtree is non-empty
    if (!root->left->is_empty() && this == root->left) 
    {
        return root;
    }

    if (!root->right->is_empty() && this == root->right) 
    {
        return root;
    }
   // Recursively find the parent in the left and right subtrees
   const BSTNode *lparent = parent_in(root->left);
   const BSTNode *rparent = parent_in(root->right);
   // Return the first non-null parent found in either left or right subtree
   return (lparent) ? lparent : rparent;
}

bool BSTNode::is_empty() const
{
    bool empty_by_count = this->count == 0;
    bool empty_by_height = this->height == -1;
    bool empty_by_children = !this->left && !this->right;

    // Assert some invariants about binary search trees
    assert(!this->left == !this->right);
    assert(empty_by_count == empty_by_height);
    assert(empty_by_height == empty_by_children);

    // Return any of the equivalent checks
    return empty_by_count;
}

BSTNode *BSTNode::child(Direction dir) const
{
    BSTNode *child = nullptr;
    if (dir == LEFT)
    {
        child = this->left;
    }
    else if (dir == RIGHT)
    {
        child = this->right;
    }
    return child;
}

void BSTNode::set_child(Direction dir, BSTNode *child)
{
    if (dir != ROOT)
    {
        if (dir == LEFT)
        {
            this->left = child;
        }
        else if (dir == RIGHT)
        {
            this->right = child;
        }
        child->parent = this;
    }
    else
    {
        assert(false);
    }
}

/*************************
 * BEGIN PRIVATE SECTION *
 *************************/

BSTNode::RRVNeighborhood::RRVNeighborhood(BSTNode *root)
    : g{root}, p{nullptr}, x{nullptr}, y{nullptr}, shape{SHAPE_NONE}
{
    // Stop if g is RED or too short
    ABORT_UNLESS((this->g->color == BLACK) &&
                 (this->g->node_height() > 1));

    if (this->g->left->color == BLACK)
    {
        // If there is a red-red violation, it's to the right
        this->y = this->g->left;
        this->p = this->g->right;

        // Stop if g has two BLACK children
        ABORT_UNLESS(this->p->color == RED);

        if (this->p->left->color == RED)
        {
            this->shape = RL;
            this->x = this->p->left;
        }
        else
        {
            // Stop if there is no red-red violation
            ABORT_UNLESS(this->p->right->color == RED);

            this->shape = RR;
            this->x = this->p->right;
        }
    }
    else if (this->g->right->color == BLACK)
    {
        // If there is a red-red violation, it's to the left
        this->y = this->g->right;
        this->p = this->g->left;

        if (this->p->left->color == RED)
        {
            this->shape = Shape::LL;
            this->x = this->p->left;
        }
        else
        {
            // Stop if there is no red-red violation
            ABORT_UNLESS(p->right->color == RED);

            this->shape = LR;
            this->x = this->p->right;
        }
    }
    else
    {
        // Both children of g are RED. Find the red-red violation
        BSTNode *lc = this->g->left;
        BSTNode *llc = lc->left;
        BSTNode *lrc = lc->right;
        BSTNode *rc = this->g->right;
        BSTNode *rlc = rc->left;
        BSTNode *rrc = rc->right;

        if (llc && llc->color == RED)
        {
            this->shape = LL;
            this->p = lc;
            this->x = llc;
            this->y = rc;
        }

        if (lrc && lrc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == SHAPE_NONE);

            this->shape = LR;
            this->p = lc;
            this->x = lrc;
            this->y = rc;
        }

        if (rlc && rlc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == Shape::SHAPE_NONE);

            this->shape = Shape::RL;
            this->p = rc;
            this->x = rlc;
            this->y = lc;
        }

        if (rrc && rrc->color == RED)
        {
            // Stop if there are multiple red-red violations
            ABORT_UNLESS(this->shape == SHAPE_NONE);

            this->shape = RR;
            this->p = rc;
            this->x = rrc;
            this->y = lc;
        }

        // Stop if there is no red-red violation
        ABORT_UNLESS(this->shape != SHAPE_NONE);
    }
}

BSTNode::BHVNeighborhood::BHVNeighborhood(BSTNode *n, Direction dir)
    : n{n}, p{nullptr}, s{nullptr}, c{nullptr}, d{nullptr},
      del_case{CASE_NONE}, dir{dir}
{
    ABORT_UNLESS(this->n && !this->n->is_empty() &&
                 this->n->color == BLACK);

    this->p = this->n->parent;

    if (!this->p)
    {
        this->del_case = CASE_1;
        assert(dir == ROOT);
        this->dir = ROOT;
    }
    else
    {
        assert(!this->p->is_empty());
        assert(this->dir != ROOT);

        this->s = this->p->child(opposite_direction(dir));
        this->c = this->s->child(dir);
        this->d = this->s->child(opposite_direction(dir));

        if (this->p->color == BLACK &&
            this->s->color == BLACK &&
            this->c && this->c->color == BLACK &&
            this->d && this->d->color == BLACK)
        {
            this->del_case = CASE_2;
        }
        else if (this->p->color == BLACK &&
                 this->s->color == RED)
        {
            assert(this->c && this->c->color == BLACK &&
                   this->d && this->d->color == BLACK);

            this->del_case = CASE_3;
        }
        else if (this->p->color == RED &&
                 this->s->color == BLACK &&
                 this->c->color == BLACK &&
                 this->d->color == BLACK)
        {
            this->del_case = CASE_4;
        }
        else if (this->s->color == BLACK &&
                 this->c->color == RED &&
                 this->d->color == BLACK)
        {
            this->del_case = CASE_5;
        }
        else if (this->s->color == BLACK &&
                 this->d->color == RED)
        {
            this->del_case = CASE_6;
        }
        else
        {
            this->del_case = CASE_NONE;
        }
    }
}

void BSTNode::BHVNeighborhood::fix_blackheight_imbalance()
{
    /*
     * This is implemented for you. Study it carefully so you understand what
     *  is going on when a node is deleted from a Red-Black Tree.
     */
    BSTNode::BHVNeighborhood nb = *this;
    while (nb.p)
    {
        BSTNode::Direction pdir = ROOT;
        if (nb.p->parent)
        {
            if (nb.p == nb.p->parent->left)
            {
                pdir = LEFT;
            }
            else if (nb.p == nb.p->parent->right)
            {
                pdir = RIGHT;
            }
            else
            {
                // Should never happen: nb.p is non-null.
                assert(false);
            }
        }
        BSTNode *grandparent = nb.p->parent;

        switch (nb.del_case)
        {
        case CASE_2:
            nb.s->color = RED;
            nb.n = nb.p;
            nb = BSTNode::BHVNeighborhood(nb.n->parent, nb.dir);
            break;
        case CASE_3:
            nb.s = nb.p->dir_rotate(nb.dir);
            if (pdir != ROOT)
            {
                grandparent->set_child(pdir, nb.s);
            }
            swap_colors(nb.p, nb.s);
            nb = BSTNode::BHVNeighborhood(nb.p, nb.dir);
            assert(nb.del_case >= CASE_4);
            break;
        case CASE_4:
            swap_colors(nb.p, nb.s);
            return;
        case CASE_5:
            nb.p->set_child(opposite_direction(nb.dir),
                            nb.s->dir_rotate(opposite_direction(nb.dir)));
            swap_colors(nb.c, nb.s);
            nb = BSTNode::BHVNeighborhood(nb.p, nb.dir);
            assert(nb.del_case == CASE_6);
            break;
        case CASE_6:
            nb.s = nb.p->dir_rotate(nb.dir);
            if (pdir != ROOT)
            {
                grandparent->set_child(pdir, nb.s);
            }
            swap_colors(nb.p, nb.s);
            nb.d->color = BLACK;
            return;
        default:
            // CASE_NONE or CASE_1 (should never happen; nb.p is non-null)
            assert(false);
            break;
        }
    }
}

BSTNode *BSTNode::rb_remove_helper(int value, BHVNeighborhood &nb)
{
    // This is implemented for you
    BSTNode *root = this;
    if (root->height >= 0)
    {
        if (value < root->data)
        {
            nb.dir = LEFT;
            root->left = root->left->rb_remove_helper(value, nb);
        }
        else if (value > root->data)
        {
            nb.dir = RIGHT;
            root->right = root->right->rb_remove_helper(value, nb);
        }
        else
        {
            // We found the value. Remove it.
            if (root->count > 1)
            {
                root->count--;
            }
            else
            {
                if (root->left->is_empty() &&
                    root->right->is_empty())
                {
                    // root has no children. We may have to do extra work.

                    // Get its neighborhood
                    nb = BHVNeighborhood(this, nb.dir);

                    // Delete it
                    delete this;
                    root = new BSTNode();
                }
                else if (!root->left->is_empty() &&
                         root->right->is_empty())
                {
                    // this has one (left) child. Promote this's child
                    this->left->color = root->color;
                    root = this->left;
                    this->left = nullptr;
                    delete this;
                }
                else if (root->left->is_empty() &&
                         !root->right->is_empty())
                {
                    // this has one (right) child. Promote this's child
                    this->right->color = root->color;
                    root = this->right;
                    this->right = nullptr;
                    delete this;
                }
                else
                {
                    /*
                     * this has two children.
                     *
                     * Find the successor to use as a replacement, then remove it
                     * entirely from this's right subtree. This requires setting
                     * the replacement's count to 1 so that the node is entirely
                     * removed rather than simply having its count decremented.
                     * Removal is the only place a const-to-non-const cast should
                     * appear in your solution.
                     *
                     * TODO: (optional) Rewrite this section of code to eliminate
                     *  the const-to-non-const cast.
                     */

                    BSTNode *replacement = (BSTNode *)root->right->minimum_value();
                    root->data = replacement->data;
                    root->count = replacement->count;
                    replacement->count = 1;
                    nb.dir = RIGHT;
                    root->right = root->right->rb_remove_helper(replacement->data, nb);
                }
            }
        }
    }

    root->make_locally_consistent();

    return root;
}

BSTNode *BSTNode::dir_rotate(Direction dir)
{
    // This is implemented for you.
    BSTNode *root = this;
    if (dir == LEFT)
    {
        root = root->left_rotate();
    }
    else if (dir == RIGHT)
    {
        root = root->right_rotate();
    }
    return root;
}

/**
 * Input: Node this - the root of the tree.
 * Returns: pointer to the root of rotated tree, whose parent pointer is
 *      the parent of this.
 * Does: right rotate tree rooted at this
 * Assumes: this has a non-empty left subtree
 * Runtime Complexity: O(1)
 */
BSTNode *BSTNode::right_rotate()
{
    if (this->is_empty() || this->left->is_empty())
    {
        return this;
    }

    BSTNode *root = this->left;
    this->left = root->right;
    this->left->parent = this;
    root->right = this;
    root->right->parent = root;
    root->parent = this->parent;
    this->parent = root;
    this->make_locally_consistent();
    root->make_locally_consistent();
    return root;
}

/**
 * Input: Node this - the root of the tree.
 * Returns: pointer to the root of rotated tree, whose parent pointer is
 *      the parent of this.
 * Does: left rotate tree rooted at this
 * Assumes: this has a non-empty right subtree
 */
BSTNode *BSTNode::left_rotate()
{
    if (this->is_empty() || this->right->is_empty())
    {
        return this;
    }

    BSTNode *root = this->right;
    this->right = root->left;
    this->right->parent = root;
    root->left = this;
    root->parent = this->parent;
    this->parent = root;
    this->make_locally_consistent();
    root->make_locally_consistent();
    return root;
}

/**
 * Input: Node this - the root of an almost-balanced AVL Tree.
 * Returns: the balanced tree.
 * Does: If unbalanced, balances the tree rooted at node.
 * Assumes: the height difference between this's left and right children
 *      is no more than 2.
 */
BSTNode *BSTNode::avl_balance()
{
    BSTNode *root = this;
    int h_diff = height_diff();

    if (h_diff > 1) // Right-heavy
    {
        int rheight_diff = right->height_diff();

        if (rheight_diff < 0) // Right-Left (RL) case
        {
            right = right->right_rotate();
            root = this->left_rotate();
            return root;
        }
        else // Right-Right (RR) case
        {
            root = this->left_rotate();
            return root;
        }
    }
    else if (h_diff < -1) // Left-heavy
    {
        int lheight_diff = left->height_diff();

        if (lheight_diff > 0) // Left-Right (LR) case
        {
            left = left->left_rotate();
            root = this->right_rotate();
            return root;
        }
        else // Left-Left (LL) case
        {
            root = this->right_rotate();
            return root;
            
            
        }
    }

    return root;

}

/**
 * Input: Node this - the root of a Red-Black tree.
 * Returns: A pointer to the root of the balanced tree
 * Does: Eliminates the red-red violation (if there is one) in the
 *      neighborhood of this, meaning this and its children and one of its
 *      grandchildren (the grandchild that is the cause of a red-red
 *      violation, if there is one). The black-height of the returned tree
 *      is the same as the black-height of this and the returned node is
 *      the root of a Red-Black tree, with the possible exception that it
 *      is RED. If there is no violation, return this unchanged.
    */
BSTNode *BSTNode::rb_eliminate_red_red_violation()
{
    /*
     * Get this's neighborhood (children + grandchildren), which might have
     *  shape NONE if this is BLACK or this.height <= 1 or there is no red-red
     *  violation in the neighborhood of this.
     */
    RRVNeighborhood nb(this);
    BSTNode *uncle = nb.y;
    BSTNode *grandparent = nb.g;
    if (nb.shape != SHAPE_NONE)
    {

        /*
         * There is a red-red violation somewhere in the neighborhood of this
         *  Fix it.
         */

        // Case 1: Recoloring
        if (uncle && uncle->color == RED)
        {
            nb.p->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;

            // Check for any violations at the grandparent
            return grandparent;
        }
        else
        {
            // Case 2: Rotation (Left-Left)
            if (nb.shape == LL)
            {
                grandparent = grandparent->right_rotate();
                grandparent->color = BLACK;
                grandparent->right->color = RED;
                grandparent->left->color = RED;
                return grandparent;
            }

            // Case 3: Rotation (Left-Right)
            if (nb.shape == LR)
            {
                nb.p = nb.p->left_rotate();
                grandparent->left = nb.p;
                grandparent = grandparent->right_rotate();
                grandparent->color = BLACK;
                grandparent->right->color = RED;
                grandparent->left->color = RED;
                return grandparent;
            }

            // Case 4: Rotation (Right-Right)
            if (nb.shape == RR)
            {
                grandparent = grandparent->left_rotate();
                grandparent->color = BLACK;
                grandparent->right->color = RED;
                grandparent->left->color = RED;
                return grandparent;
            }

            // Case 5: Rotation (Right-Left)
            if (nb.shape == RL)
            {
                nb.p = nb.p->right_rotate();
                grandparent->right = nb.p;
                grandparent = grandparent->left_rotate();
                grandparent->color = BLACK;
                grandparent->right->color = RED;
                grandparent->left->color = RED;
                return grandparent;
            }
        }
    }
    return grandparent;
}

int BSTNode::height_diff() const
{
    /*
     * This is implemented for you. Note the use of the node_height() function
     *  rather than the height property. Why do you think is it written in this
     *  way?
     */
    int diff = 0;
    if (!this->is_empty())
    {
        diff = this->right->node_height() - this->left->node_height();
    }

    return diff;
}

/**
 * Input: Node this - the root of the tree to make consistent
 * Returns: N/A
 * Does: Updates the tree rooted at this to be locally consistent, in the
 *      following way:
 *        - this.height = 1 + MAX(this.left.height, this.right.height)
 *        - this.left.parent = this
 *        - this.right.parent = this
 *  If this is empty, this.height is set to -1 and nothing is done to its
 *      children.
 */
void BSTNode::make_locally_consistent()
{
    if (!this->is_empty())
    {
        // Update height
        int lheight = left->node_height();
        int rheight = right->node_height();
        this->height = 1 + (lheight > rheight ? lheight : rheight);
        
        // Update parent pointers
        if (left)
        {
            this->left->parent = this;
        }
        if (right)
        {
            this->right->parent = this;
        } 
    }  
}
