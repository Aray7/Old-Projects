//-----------------------------------------------------------
//  Purpose:    Header file for the BinaryTree class.
//  Author:     John Gauch
//-----------------------------------------------------------
#include <iostream>
#include <fstream>
using namespace std;

// Data node definition
class Node
{
   public:
   int Value;
   Node *Left;
   Node *Right;
};

//-----------------------------------------------------------
// Define the binary tree class interface.
//-----------------------------------------------------------
class BinaryTree
{
 public:
   // Constructor functions
   BinaryTree();
  ~BinaryTree();

   // General binary tree operations
   bool Search(int Value);
   bool Insert(int Value);
   bool Delete(int Value);
   void Print();
   int Count();
   int Height();

 private:
   // Helper functions
   bool SearchHelper(int Value, Node * Tree);
   bool InsertHelper(int Value, Node * &Tree);
   bool DeleteNode(Node * &Tree);
   bool DeleteHelper(int Value, Node * &Tree);
   void PrintHelper(Node * Tree);
   void CountHelper(int& count, Node* current);
   int HeightHelper(int height, Node* current);

   // Tree pointer
   Node *Root;
};
//BinaryTree Implementation
//Consider the partial implementation of the BinaryTree class below. We have intentionally left several functions empty, and we have omitted the Delete functions for now.

//-----------------------------------------------------------
//  Purpose:    Implementation of BinaryTree class.
//  Author:     John Gauch
//-----------------------------------------------------------
//#include "tree.h"

//-----------------------------------------------------------
// Constructor function.
//-----------------------------------------------------------
BinaryTree::BinaryTree()
{
   Root = NULL;
}

//-----------------------------------------------------------
// Destructor function.
//-----------------------------------------------------------
BinaryTree::~BinaryTree()
{
}

//-----------------------------------------------------------
// Search helper function.
//-----------------------------------------------------------
bool BinaryTree::SearchHelper(int Value, Node * Tree)
{
   // Data value not found
   if (Tree == NULL)
      return false;

   // Data value found
   else if (Tree->Value == Value)
      return true;

   // Recursively search for data value
   else if (Tree->Value > Value)
      return (SearchHelper(Value, Tree->Left));
   else if (Tree->Value < Value)
      return (SearchHelper(Value, Tree->Right));
}

//-----------------------------------------------------------
// Search for data in the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Search(int Value)
{
   // Call tree searching function
   return (SearchHelper(Value, Root));
}

//-----------------------------------------------------------
// Insert helper function.
//-----------------------------------------------------------
bool BinaryTree::InsertHelper(int Value, Node * &Tree)
{
   // Insert data into the tree
   if (Tree == NULL)
   {
      Tree = new Node;
      Tree->Value = Value;
      Tree->Left = NULL;
      Tree->Right = NULL;
      return true;
   }

   // Data value already inserted
   else if (Tree->Value == Value)
      return false;

   // Recursively search for insertion position
   else if (Tree->Value > Value)
      return (InsertHelper(Value, Tree->Left));
   else if (Tree->Value < Value)
      return (InsertHelper(Value, Tree->Right));
}

//-----------------------------------------------------------
// Insert data into the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Insert(int Value)
{
   // Call tree insertion function
   return (InsertHelper(Value, Root));
}

//-----------------------------------------------------------
// Print helper function.
//-----------------------------------------------------------
void BinaryTree::PrintHelper(Node * Tree)
{
   // Check terminating condition
   if (Tree != NULL)
   {
      // Print left subtree
      cout << "(";
      PrintHelper(Tree->Left);

      // Print node value
      cout << " " << Tree->Value << " ";

      // Print right subtree
      PrintHelper(Tree->Right);
      cout << ")";
   }
}

//-----------------------------------------------------------
// Print all records in the binary tree.
//-----------------------------------------------------------
void BinaryTree::Print()
{
   // Call tree printing function
   PrintHelper(Root);
   cout << endl;
}

int BinaryTree::Count()
{
    int count = 0;
    CountHelper(count, Root);
    return count;
}

void BinaryTree::CountHelper(int& count, Node* current)
{
    if(current != nullptr)
    {
        CountHelper(count, current->Left);
        CountHelper(count, current->Right);
        count++;
    }
}

int BinaryTree::Height()
{
    int height = 0;
    HeightHelper(height, Root);
}

int BinaryTree::HeightHelper(int height, Node* current)
{
    if(current == nullptr)
        return height;
    else
    {
        height++;
        int h = HeightHelper(height, current->Left);
        int h2 = HeightHelper(height, current->Right);
        return(h > h2 ? h : h2);
    }
}

//-----------------------------------------------------------
// Main program.
//-----------------------------------------------------------
int main()
{
   // ADD HERE
   BinaryTree tree;
   BinaryTree tree2;
   BinaryTree tree3;

   for(int i = 0; i < 10; i++)
      {
          cout << (tree.Insert(rand() % 10) ?
          "Value was inserted correctly" : "Value was not inserted correctly")
          << endl;
      }

   for(int i = 0; i < 10; i++)
   {
      tree2.Insert(i);
   }

   for(int i = 9; i >= 1; i--)
   {
      tree3.Insert(i);
   }

   tree.Print();
   tree2.Print();
   tree3.Print();

   cout << tree.Count() << endl;
   cout << tree2.Count() << endl;

   cout << tree.Height() << endl;
   cout << tree2.Height() << endl;

   return 0;
}
