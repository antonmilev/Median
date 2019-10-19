#pragma once

/**
 * @file RBTree.h
 * @brief multiset implementation of a Red-Black tree
 *
 * Similarily to std::multiset, this RB tree allows inserting of duplicate values. 
 * It is specially designed to find the median element in efficient way.
 */

class RBTree
{
public:
    enum { BLACK = 0, RED = 1 };

    class Node
    {
    public:

        Node()
        {
            init();
        }

        Node(const int& key, Node* parent = 0)
        {
            init();
            this->key = key;
            this->parent = parent;
        }

        inline void init()
        {
            left = right = parent = 0;
            nChilds = 0;
            type = 0;
        }

        inline bool isEmpty() const
        {
            return (left == 0 && right == 0);
        }

        inline int numChildsLeft() const
        {
            return left ? left->nChilds + 1 : 0;
        }

        inline int numChildsRight() const
        {
            return right ? right->nChilds + 1 : 0;
        }

    public:
        Node     *left, *right, *parent;
        int       key;
        int       type;
        int       nChilds;
    };
    
    RBTree();

    /// insert new element
    bool insert(const int& key);

    /// return number of all inserted elements
    int size() const    { return count; }

    /// empty tree
    bool clear();

    /// get the value of the middle element
    int  middleValue() const;

protected:
    // functions and members for internal use   
    void rotateRight(Node* node);
    void rotateLeft(Node* node);
    void insertFixup(Node *x);

    virtual Node* allocNode(const int& key, Node* parent = 0);
    virtual void deleteNode(Node* node);

    Node* findParent(Node* node, const int& key) const;
    Node* insertNode(Node* node, const int& key);
    void emptySubtree(Node* node);

    /// pointer to the root of the tree
    Node* root;

    /// integer to keep the number of the inserted elements
    int count;
};






