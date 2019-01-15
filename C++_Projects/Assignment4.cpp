#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

class BSTNode
{
public:
    string value;
    BSTNode* left;
    BSTNode* right;
    BSTNode* current;
    BSTNode* node;
    int deleteCurrent;
    int frequency;
    int depth;
    int first;
};

class BinarySearchTree
{
public:
    BinarySearchTree();
    ~BinarySearchTree();

    //Main operations
    bool search(const string value) const;
    void insert(const string value);
    bool remove(const string value);
    int getHeight() const;
    int getFrequency(const string value) const;
    int getDepth(const string value) const;
    int getTotalEntries() const;
    int getDistinctWords() const;
    int getSelection();
    bool insertFromFile(string filename);

    //Print functions
    void printPreorder() const;
    void print() const;
    void selectionList();

private:
    BSTNode* root;
    int numNodes;
    int numEntries;

    //Helper functions for recursive algorithms
    void destructHelper(BSTNode* current);
    BSTNode* searchHelper(const string value, BSTNode* current) const;
    void insertHelper(const string value, BSTNode*& current, int nodeHeight);
    BSTNode* removeHelper(const string value, int numToDelete, BSTNode*& current);
    void printPathsRecursiveHelper(BSTNode* current, int path[], int& pathLength) const;
    int getHeightHelper(BSTNode* current, int nodeHeight) const;

    void printPreorderHelper(const BSTNode* current) const;
};

BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
    numNodes = 0;
    numEntries = 0;
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

bool BinarySearchTree::search(const string value) const
{
    return searchHelper(value, root);
}

BSTNode* BinarySearchTree::searchHelper(const string value, BSTNode* current) const
{
    if(current == nullptr)
        return nullptr;
    else if(current->value == value)
        return current;
    else if(current->value > value)
        return searchHelper(value, current->left);
    else
        return searchHelper(value, current->right);
}

void BinarySearchTree::insert(const string value)
{
    insertHelper(value, root, 0);
}

void BinarySearchTree::insertHelper(const string value, BSTNode*& current, int nodeHeight)
{
    if(current == nullptr)
    {
        current = new BSTNode();
        current->value = value;
        current->depth = nodeHeight;
        numNodes++;
        numEntries++;
    }

    else if(current->value > value)
        insertHelper(value, current->left, nodeHeight + 1);

    else if(current->value < value)
        insertHelper(value, current->right, nodeHeight + 1);

    else
        current->frequency++;
        numEntries++;
}

bool BinarySearchTree::remove(const string value)
{
    int numToDelete;
    return removeHelper(value, numToDelete, root);
}

BSTNode* BinarySearchTree::removeHelper(const string value, int numToDelete, BSTNode*& current)
{
    //Node was not found, so return false
    if(current == nullptr)
        return nullptr;

    //Search left
    else if(current->value > value)
        current->left = removeHelper(value, numToDelete, current->left);

    //Search right
    else if(current->value < value)
        current->right = removeHelper(value, numToDelete, current->right);

    //Node was found
    else if(current->value == value)
    {
        if(current->left == nullptr && current->right == nullptr)
        {
            delete current;
            current = nullptr;
        }

        else if(current->left == nullptr)
        {
            numEntries = current->first;
            numNodes--;
            BSTNode* deleteCurrent = current;
            current = current->right;
            current->depth--;
            delete deleteCurrent;
        }

        else if(current->right == nullptr)
        {
            numEntries+ current->first;
            numNodes--;
            BSTNode* deleteCurrent = current;
            current = current->left;
            delete deleteCurrent;
        }

        else
        {
            BSTNode* deleteCurrent = current->left;
            while(deleteCurrent->right != nullptr)
                deleteCurrent = deleteCurrent->right;

            current->value = deleteCurrent->value;
            current->left = removeHelper(deleteCurrent->value, numToDelete, current->left);
        }
      }
      else
      {
          current->frequency += numToDelete;
          numEntries -= numToDelete;
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

int BinarySearchTree::getHeight() const
{
    return(root != nullptr ? getHeightHelper(root, 0) : 0);
}

int BinarySearchTree::getHeightHelper(BSTNode* current, int nodeHeight) const
{
    int height;
    int height2;

    if(current->left != nullptr)
        height = getHeightHelper(current->left, nodeHeight + 1);
    else
        height = nodeHeight;

    if(current->right != nullptr)
        height2 = getHeightHelper(current->right, nodeHeight + 1);
    else
        height2 = nodeHeight;

    return(height >= height2 ? height : height2);
}

int BinarySearchTree::getFrequency(const string value) const
{
    BSTNode* node = searchHelper(value, root);
    return(node != nullptr ? node->frequency : 0);
}

int BinarySearchTree::getDepth(const string value) const
{
    BSTNode* node = searchHelper(value, root);
    return(node != nullptr ? node->depth : 1);
}

void BinarySearchTree::print() const
{
    printPreorderHelper(root);
}

void BinarySearchTree::selectionList()
{
    cout << "Which of the following choices would you like?" << endl;
    cout << "1) Insert a word" << endl;
    cout << "2) Insert words from a file" << endl;
    cout << "3) Delete a word" << endl;
    cout << "4) Print out the number of distinct words in the tree" << endl;
    cout << "5) Print out the total number of words in the tree" << endl;
    cout << "6) Print out the number of times a particular word is stored in the tree" << endl;
    cout << "7) Print out the depth of the node storing a particular word in the tree" << endl;
    cout << "8) Print out the height of the tree" << endl;
    cout << "9) Quit" << endl;
    cout << endl;
}

int BinarySearchTree::getTotalEntries() const
{
    return numEntries;
}

int BinarySearchTree::getDistinctWords() const
{
    return numNodes;
}

int BinarySearchTree::getSelection()
{
    int selection;
    selectionList();
    cin >> selection;

    return selection;
}

bool BinarySearchTree::insertFromFile(string filename)
{
    string tmpstr;
    ifstream din;
    din.open(filename.c_str());

    if(din.fail())
    {
        cout << "Error opening file. Please try again." << endl;
        return false;
    }

    else
    {
        while(din >> tmpstr)
        insert(tmpstr);
    }

    din.close();
    return true;
}

int main()
{
    BinarySearchTree b;
    bool done = false;
    int selection;
    string tmpStr;

    while(!done)
    {
        selection = b.getSelection();

        switch(selection)
        {
            case 1:
              cout << "What word would you like to insert?" << endl;
              cin >> tmpStr;
              cout << endl;
              b.insert(tmpStr);
              break;

            case 2:
              cout << "What file would you like to insert?" << endl;
              cin >> tmpStr;
              b.insertFromFile(tmpStr);
              break;

            case 3:
              cout << "What word would you like to delete?" << endl;
              cin >> tmpStr;
              cout << endl;
              b.remove(tmpStr);
              break;

            case 4:
              cout << "There are " << b.getDistinctWords() << " distinct word(s) in the tree." << endl;
              cout << endl;
              break;

            case 5:
              cout << "There are " << b.getTotalEntries() << " word(s) in the tree."<< endl;
              cout << endl;
              break;

            case 6:
              cout << "What word would you like to check?" << endl;
              cin >> tmpStr;
              cout << "Number of times " << tmpStr << " was stored is: " << b.getFrequency(tmpStr) << endl;
              cout << endl;
              break;

            case 7:
              cout << "Enter the word to check the depth of node storing it." << endl;
              cin >> tmpStr;
              cout << "Depth is: " << b.getDepth(tmpStr) << endl;
              cout << endl;
              break;

            case 8:
              cout << "Height of the tree: " << b.getHeight() << endl;
              cout << endl;
              break;

            case 9:
              done = true;
              cout << "Thank you for useing the word tree!" << endl;
        }
    }


    return 0;
}
