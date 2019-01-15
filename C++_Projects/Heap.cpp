#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

class Heap
{
public:
    Heap(const int size);
    Heap(const int* numbers, const int _heap_size, const int _max_heap_size);
    ~Heap();

    bool isFull();
    bool search(const int val);
    bool insert(const int val);
    bool removeTop();
    int peekTop();

    void print();

    static void heapsort(int* numbers, int size);

private:
    int MAX_HEAP_SIZE;
    int heap_size;
    int* data;

    //Internal helper functions
    int left(const int i);
    int right(const int i);
    int parent(const int i);

    void swap(int& a, int& b);
    void percolateUp(const int i);
    void maxHeapify(const int i);

    void buildMaxHeap();
};

Heap::Heap(const int size)
{
    MAX_HEAP_SIZE = size;
    heap_size = 0;
    data = new int[MAX_HEAP_SIZE];
}

Heap::Heap(const int* numbers, const int _heap_size, const int _max_heap_size)
{
    MAX_HEAP_SIZE = _max_heap_size;
    data = new int[MAX_HEAP_SIZE];
    heap_size = _heap_size;

    for(int i = 0; i < heap_size; i++)
        data[i] = numbers[i];

    buildMaxHeap();
}

Heap::~Heap()
{
    delete [] data;
}

bool Heap::isFull()
{
    if(heap_size == MAX_HEAP_SIZE)
        return true;
    else
        return false;
}

//Heap is not strictly ordered, so we have to search everything
//Possible optimization: if data[i] < val, val will not be in that subheap, so skip ahead
bool Heap::search(const int val)
{
    for(int i = 0; i < heap_size; i++)
        if(data[i] == val)
            return true;
    return false;
}

bool Heap::insert(const int val)
{
    if(!isFull())
    {
        data[heap_size] = val;
        heap_size++;
        percolateUp(heap_size-1);
        return true;
    }
    else
        return false;
}

//Make the last node in the heap the new root.
//Then push it down until the heap property is no longer violated.
bool Heap::removeTop()
{
    heap_size--;
    data[0] = data[heap_size];
    maxHeapify(0);
}

int Heap::peekTop()
{
    return data[0];
}

void Heap::print()
{
    for(int i = 0; i < heap_size; i++)
        cout << data[i] << " ";
    cout << "\n";
}

int Heap::left(const int i)
{
    return 2*i + 1;
}

int Heap::right(const int i)
{
    return 2*i + 2;
}

int Heap::parent(const int i)
{
    return ceil(i - 1) / 2;
}

void Heap::swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

//If node i is greater than its parent, swap it up as far as it can go
void Heap::percolateUp(const int i)
{
    if(i <= 0 || i >= heap_size)
        return;

    int p = parent(i);
    if(data[i] > data[p])
    {
        swap(data[i], data[p]);
        percolateUp(p);
    }
}

//A.K.A. percolateDown. "maxHeapify" is the name used in CLRS (the course textbook),
//so I stuck with that name here
void Heap::maxHeapify(const int i)
{
    int lc = left(i);
    int rc = right(i);
    int largest;

    if(lc < heap_size && data[lc] > data[i])
        largest = lc;
    else
        largest = i;

    if(rc < heap_size && data[rc] > data[largest])
        largest = rc;

    if(largest != i)
    {
        swap(data[i], data[largest]);
        maxHeapify(largest);
    }
}

//Assume elements in bottom half of array are all little heaps of size 1
//Join them into a big heap from the bottom up
void Heap::buildMaxHeap()
{
    for(int i = floor(heap_size/2); i >= 0; i--)
        maxHeapify(i);
}

//static
void Heap::heapsort(int* numbers, int size)
{
    //Create a new max heap from the array
    Heap h(numbers, size, size+1);

    //Keep popping the max off until the heap is empty
    for(int i = size-1; i >= 0; i--)
    {
        numbers[i] = h.peekTop();
        h.removeTop();
    }
}

int main()
{
    srand(time(NULL));

    int size = 10;

    Heap h(size);

    for(int i = 0; i < size; i++)
        h.insert(rand() % 100);

    h.print();

    h.removeTop();
    h.print();

    //Test buildMaxHeap by calling the non-default constructor
    // int size = 7;
    // int* numbers = new int[size];
    //
    // for(int i = 0; i < size; i++)
    // {
    //     numbers[i] = (rand() % 100);
    //     cout << numbers[i] << " ";
    // }
    // cout << "\n";
    //
    // Heap h(numbers, size, 50);
    //
    // h.removeTop();
    // h.print();

    //Test heapsort
    /*int size = 10;
    int* numbers = new int[size];

    for(int i = 0; i < size; i++)
    {
        numbers[i] = (rand() % 100);
        cout << numbers[i] << " ";
    }
    cout << "\n";

    Heap::heapsort(numbers, size);

    for(int i = 0; i < size; i++)
        cout << numbers[i] << " ";
    cout << "\n";*/

    return 0;
}
