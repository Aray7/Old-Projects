//------------------------------------------------------------
// Purpose: Header file for the Heap class.
// Author:  John Gauch
//------------------------------------------------------------
#include <iostream>
#include <cstdlib>
using namespace std;

//------------------------------------------------------------
// The Heap class definition for a heap of integers
//------------------------------------------------------------
#define MAX_HEAP_SIZE 20
class Heap
{
 public:
   // Constructor functions
   Heap();
   Heap(int MaxSize);
   ~Heap();

   // General heap operation
   bool Insert(int num);
   bool Remove(int &num);
   bool IsEmpty();
   bool IsFull();
   void Print();

 private:
   int Count;
   int *heap;
};

//------------------------------------------------------------
// Purpose: Implementation of integer Heap class.
// Author:  John Gauch
//------------------------------------------------------------
//#include "heap.h"

//------------------------------------------------------------
// Constructor function.
//------------------------------------------------------------
Heap::Heap()
{
   Count = 0;
   heap - new int[MAX_HEAP_SIZE+1];
   for (int index = 0; index <= MAX_HEAP_SIZE; index++)
      heap[index] = -1;
}

Heap::Heap(int MaxSize)
{
    Count = 0;
    heap = new int[MaxSize];
    for(int i = 0; i < MaxSize; i++)
        heap[i] = -1;
}

//------------------------------------------------------------
// Destructor function.
//------------------------------------------------------------
Heap::~Heap()
{
    delete [] heap;
}

//------------------------------------------------------------
// Insert an element into the heap.
//------------------------------------------------------------
bool Heap::Insert(int num)
{
    num *= -1;
   // Check for full heap
   if (IsFull())
      return false;

   // Shuffle data up the heap
   Count++;
   int child = Count;
   int parent = child / 2;
   while ((child > 1) && (heap[parent] < num))
   {
      heap[child] = heap[parent];
      child = parent;
      parent = child / 2;
   }

   // Insert new entry in heap
   heap[child] = num;
   return true;
}

//------------------------------------------------------------
// Remove an element from the heap.
//------------------------------------------------------------
bool Heap::Remove(int &num)
{
   // Check for empty heap
   if (IsEmpty())
      return false;

   // Save top of heap
   num = heap[1];

   // Swap last value into root position
   heap[1] = heap[Count];
   heap[Count] = -1;
   Count--;

   // Shuffle data down the heap
   int parent = 1;
   int largest = 0;
   while (parent != largest)
   {
      // Check left node
      largest = parent;
      int left = parent * 2;
      if ((left <= Count) && (heap[left] > heap[largest]))
	 largest = left;

      // Check right node
      int right = left + 1;
      if ((right <= Count) && (heap[right] > heap[largest]))
	 largest = right;

      // Swap data values if needed
      if (parent != largest)
      {
	 int temp = heap[parent];
	 heap[parent] = heap[largest];
	 heap[largest] = temp;
	 parent = largest;
	 largest = 0;
      }
   }

   num *= -1;
   return true;
}

//------------------------------------------------------------
// Print the contents of the heap.
//------------------------------------------------------------
void Heap::Print()
{
   for (int index = 1; index <= Count; index++)
      cout << -1 * heap[index] << " ";
   cout << endl;
}

//------------------------------------------------------------
// Check if the heap is empty
//------------------------------------------------------------
bool Heap::IsEmpty()
{
   return Count == 0;
}

//------------------------------------------------------------
// Check if the heap is full
//------------------------------------------------------------
bool Heap::IsFull()
{
   return (Count == MAX_HEAP_SIZE);
}

//-----------------------------------------------------------
// Main program.
//-----------------------------------------------------------
int main()
{
   Heap* h = new Heap(25);
   int n;
   int removed;

   cout << "Enter a number: ";
   cin >> n;

   for(int i = 0; i < n; i++)
      h->Insert(rand() % 10);

   h->Print();
   cout << endl;

   while(!h->IsEmpty())
   {
      h->Remove(removed);
      cout << "Removed: " << removed << endl;
      h->Print();
   }

}
