#include <iostream>
#include <vector>
using namespace std;

class BSTNode
{
public:
    int value;
    BSTNode* left;
    BSTNode* right;
};

class BinarySearchTree
{
public:
    BinarySearchTree();
    ~BinarySearchTree();

    //Main operations
    bool search(const int value) const;
    void insert(const int value);
    bool remove(const int value);

    void printPathsIterative() const;
    void printPathsRecursive() const;

    //Print functions
    void printPreorder() const;       //Preorder (MLR)
    void printInorder() const;        //Inorder (LMR)
    void printPostorder() const;      //Postorder (LRM)

private:
    BSTNode* root;
    int size;

    //Helper functions for recursive algorithms
    void destructHelper(BSTNode* current);
    bool searchHelper(const int value, BSTNode* current) const;
    void insertHelper(const int value, BSTNode*& current);
    BSTNode* removeHelper(const int value, BSTNode*& current);
    void printPathsRecursiveHelper(BSTNode* current, int path[], int& pathLength) const;

    void printPreorderHelper(const BSTNode* current) const;
    void printInorderHelper(const BSTNode* current) const;
    void printPostorderHelper(const BSTNode* current) const;
};

BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
    size = 0;
}


BinarySearchTree::~BinarySearchTree()
{
    destructHelper(root);
}

void BinarySearchTree::destructHelper(BSTNode* current)
{
    if(current != nullptr)
    {
        destructHelper(current->left);
        destructHelper(current->right);
        delete current;
    }
}

bool BinarySearchTree::search(const int value) const
{
    return searchHelper(value, root);
}

bool BinarySearchTree::searchHelper(const int value, BSTNode* current) const
{
    if(current == nullptr)
        return false;
    else if(current->value == value)
        return true;
    else if(current->value > value)
        return searchHelper(value, current->left);
    else
        return searchHelper(value, current->right);
}

void BinarySearchTree::insert(const int value)
{
    insertHelper(value, root);
}

void BinarySearchTree::insertHelper(const int value, BSTNode*& current)
{
    if(current == nullptr)
    {
        current = new BSTNode();
        current->value = value;
        current->left = nullptr;
        current->right = nullptr;
        size++;
    }

    else if(current->value >= value)
        insertHelper(value, current->left);

    else
        insertHelper(value, current->right);
}

bool BinarySearchTree::remove(const int value)
{
    return removeHelper(value, root);
}

BSTNode* BinarySearchTree::removeHelper(const int value, BSTNode*& current)
{
    //Node was not found, so return false
    if(current == nullptr)
        return nullptr;

    //Search left
    else if(current->value > value)
        current->left = removeHelper(value, current->left);

    //Search right
    else if(current->value < value)
        current->right = removeHelper(value, current->right);

    //Node was found
    else
    {
        //Case 0: node to delete is leaf Node
        if(current->left == nullptr && current->right == nullptr)
        {
            delete current;
            current = nullptr;
        }
        //Case 1a: One right child
        else if(current->left == nullptr)
        {
            BSTNode* toDelete = current;
            current = current->right;
            delete toDelete;
        }
        //Case 1b: One left child
        else if(current->right == nullptr)
        {
            BSTNode* toDelete = current;
            current = current->left;
            delete toDelete;
        }
        //Case 2: node has 2 children
        else
        {
            BSTNode* toDelete = current->left;
            while(toDelete->right != nullptr)
                toDelete = toDelete->right;

            //Swap the value of the node we want to delete
            //With value of rightmost node in left subtree
            current->value = toDelete->value;

            //Update current->left
            current->left = removeHelper(toDelete->value, current->left);
        }
    }

    return current;
}

void BinarySearchTree::printPreorder() const
{
    cout << "Preorder: ";
    printPreorderHelper(root);
    cout << "\n";
}

void BinarySearchTree::printPreorderHelper(const BSTNode* current) const
{
    if(current != nullptr)
    {
        cout << current->value << " ";
        printPreorderHelper(current->left);
        printPreorderHelper(current->right);
    }
}

void BinarySearchTree::printInorder() const
{
    cout << "Inorder: ";
    printInorderHelper(root);
    cout << "\n";
}

void BinarySearchTree::printInorderHelper(const BSTNode* current) const
{
    if(current != nullptr)
    {
        printInorderHelper(current->left);
        cout << current->value << " ";
        printInorderHelper(current->right);
    }
}

void BinarySearchTree::printPostorder() const
{
    cout << "Postorder: ";
    printPostorderHelper(root);
    cout << "\n";
}

void BinarySearchTree::printPostorderHelper(const BSTNode* current) const
{
    if(current != nullptr)
    {
        printPostorderHelper(current->left);
        printPostorderHelper(current->right);
        cout << current->value << " ";
    }
}

void BinarySearchTree::printPathsIterative() const
{
    int i = 0;
    int iprev = 0;
    int path[size];
    BSTNode* current = root;

    //This vector will hold all the "forks" in the tree that we skipped over.
    //Every time we hit a fork, save it here. We'll return when we finish the path we're on.
    vector<BSTNode*> forks;
    vector<int> prevLengths;

    while(current != nullptr)
    {
        //Add the current node to the path
        path[i++] = current->value;

        //If this is a leaf node, print the whole path
        if(current->left == nullptr && current->right == nullptr)
        {
            for(int index = 0; index < i; index++)
                cout << path[index] << " ";
            cout << "\n";

            //If necessary, return to the most recent fork in the path and continue right
            if(forks.empty())
                current = nullptr;
            else
            {
                current = forks.back();
                forks.pop_back();
                i = prevLengths.back();
                prevLengths.pop_back();
                current = current->right;
            }
        }

        //If this node has only a left child, search that way
        else if(current->right == nullptr)
            current = current->left;

        //If this node has only a right child, search that way
        else if(current->left == nullptr)
            current = current->right;

        //Otherwise, we're at a fork. Save a pointer to this node, and we'll return to it later.
        //For now, go left. (The first if statement in this block will handle the right child).
        else
        {
            forks.push_back(current);
            prevLengths.push_back(i);
            current = current->left;
        }

    }
}

void BinarySearchTree::printPathsRecursive() const
{
    int pathLength = 0;
    int path[size];
    printPathsRecursiveHelper(root, path, pathLength);
}

void BinarySearchTree::printPathsRecursiveHelper(BSTNode* current, int path[], int& pathLength) const
{
    //If this node doesn't exist, do nothing
    if(current == nullptr)
        return;

    //Add the current node to our path before visiting all paths below
    path[pathLength] = current->value;
    pathLength++;

    //If this is a leaf node, print the current path
    if (current->left == nullptr && current->right == nullptr)
    {
        for(int i = 0; i < pathLength; i++)
            cout << path[i] << " ";
        cout << "\n";
    }

    //Otherwise, visit its children
    else
    {
        printPathsRecursiveHelper(current->left, path, pathLength);
        printPathsRecursiveHelper(current->right, path, pathLength);
    }

    //We found all paths involving this node, so "remove" it from the array
    pathLength--;
}

int main()
{
    BinarySearchTree b;

    b.insert(10);
    b.insert(8);
    b.insert(3);
    b.insert(9);
    b.insert(15);
    b.insert(13);
    b.insert(14);
    b.insert(16);
    b.insert(19);
    b.insert(1);
    b.insert(4);

    // b.remove(16);
    // b.remove(8);

    b.printInorder();
    b.printPreorder();
    b.printPostorder();
    cout << endl;

    cout << (b.search(3) ? "3 is in the tree" : "3 is not in the tree") << "\n";
    cout << (b.search(7) ? "7 is in the tree" : "7 is not in the tree") << "\n";
    cout << (b.search(14) ? "14 is in the tree" : "14 is not in the tree") << "\n";

    cout << "\nPrint all paths iteratively:\n";
    b.printPathsIterative();

    cout << "\nPrint all paths recursively:\n";
    b.printPathsRecursive();

    // b.remove(6);
    // b.print();
    // cout << "\n";
    //
    // b.remove(10);
    // b.print();
    // cout << "\n";

    return 0;
}
