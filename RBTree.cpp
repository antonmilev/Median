#include "RBTree.h"

RBTree::RBTree()
{
    root = 0;
    count = 0;
}

//-------------------------------------------------------------------------
/*                     P                   P
                       |                   |
                      node                 L
                     /  \                /   \
                    L    R      ->      LL   node
                   / \                       /  \
                  LL  LR                    LR   R

*/
void RBTree::rotateRight(Node* node)
{
    Node* L = node->left;

    if (!L)
        return;

    Node* LR = L->right;
    Node* P = node->parent;

    //if(!P)  return ; //dont do this for parent

    node->left = LR;
    L->right = node;

    L->parent = P;
    if (LR) LR->parent = node;
    if (P) node == P->right ? P->right = L : P->left = L;
    else root = L;
    node->parent = L;

    L->nChilds += node->numChildsRight() + 1;
    node->nChilds -= (L->numChildsLeft() + 1);
}


//-------------------------------------------------------------------------
/*                     P                   P
                       |                   |
                      node                 R
                     /  \                /   \
                    L    R      ->     node
                        /  \           / \
                      RL              L   RL
*/

void RBTree::rotateLeft(Node* node)
{
    Node* R = node->right;
    if (!R)
        return;

    Node* RL = R->left;
    Node* P = node->parent;

    //if(!P)  return ; //dont do this for parent

    node->right = RL;
    R->left = node;

    R->parent = P;
    if (RL) RL->parent = node;
    if (P) node == P->right ? P->right = R : P->left = R;
    else root = R;
    node->parent = R;

    R->nChilds += node->numChildsLeft() + 1;
    node->nChilds -= (R->numChildsRight() + 1);
}

//  maintain Red-Black tree balance  
//  after inserting node x           
void RBTree::insertFixup(Node *x)
{
    // check Red-Black properties
    while (x != root && x->parent->type == RED)
    {
        Node* z = x->parent->parent;
        // we have a violation
        if (x->parent == z->left)
        {
            Node *y = z->right;
            if (y && y->type == RED)
            {

                // uncle is RED
                x->parent->type = BLACK;
                y->type = BLACK;
                z->type = RED;
                x = z;
            }
            else
            {
                // uncle is BLACK
                if (x == x->parent->right)
                {
                    // make x a left child
                    x = x->parent;
                    rotateLeft(x);
                }

                // recolor and rotate
                x->parent->type = BLACK;
                z->type = RED;
                rotateRight(z);
            }
        }
        else
        {
            // mirror image of above code
            Node *y = z->left;
            if (y && y->type == RED)
            {

                // uncle is RED
                x->parent->type = BLACK;
                y->type = BLACK;
                z->type = RED;
                x = z;
            }
            else
            {

                // uncle is BLACK
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x);
                }
                x->parent->type = BLACK;
                z->type = RED;
                rotateLeft(z);
            }
        }
    }
    root->type = BLACK;
}

RBTree::Node* RBTree::allocNode(const int& key, Node* parent)
{
    return new Node(key, parent);
}

void RBTree::deleteNode(Node* node)
{
    delete node;
}

void RBTree::emptySubtree(Node* node)
{
    if (node->left)
        emptySubtree(node->left);
    if (node->right)
        emptySubtree(node->right);

    count--;

    deleteNode(node);
}

bool RBTree::clear()
{
    if (!root)
        return false;

    if (count)
        emptySubtree(root);

    root = 0;
    count = 0;

    return true;
}


RBTree::Node* RBTree::findParent(Node* node, const int& key) const
{
    Node* parent = 0;

    while (node)
    {
        parent = node;

        if (key > node->key)
            node = parent->right;
        else
            node = parent->left;
    }

    return parent;
}

RBTree::Node* RBTree::insertNode(Node* node, const int& key)
{
    if (!node)
        node = root;

    if (!node)
    {
        root = allocNode(key, 0);
        count++;
        return root;
    }

    int index = 0;

    // find the parent of 
    Node* parent = findParent(node, key);

    if (!parent)
        return 0;  

    Node* newNode = allocNode(key, parent);

    // link with parent 
    if (key > parent->key)
        parent->right = newNode;
    else
        parent->left = newNode;

    // update childs number
    while (parent)
    {
        parent->nChilds++;
        parent = parent->parent;
    }

    count++;
    return newNode;
}

bool RBTree::insert(const int& key)
{
    Node* newNode = insertNode(root, key);

    if (!newNode)
        return false;

    if (newNode == root)
        newNode->type = BLACK;
    else
        newNode->type = RED;

    insertFixup(newNode);

    return true;
}

int RBTree::middleValue() const
{
    if (!count)
        return 0;

    Node* node = root;

    int idx = (count - 1) / 2;

    int nIndex;

    while (node)
    {
        nIndex = 0;
        if (node->left)
            nIndex = node->left->nChilds + 1;

        if (idx == nIndex)
            return node->key;

        if (idx < nIndex)     //go left
            node = node->left;
        else                 
        {
            idx -= nIndex + 1;
            node = node->right;
        }
    };

    return 0;
}

