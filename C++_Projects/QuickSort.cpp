#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

const int size = 10;

void print(int* numbers, int p = -1, int r = -1, int q = -1)
{
    for(int i = 0; i < size; i++)
    {
        if(i == p)
            cout << " [[";
        if(i == q)
            cout << " <<";
        cout << setw(3) << numbers[i];
        if(i == q)
            cout << ">> ";
        if(i == r)
            cout << " ]]";
    }
    cout << "\n";
}

void swap(int* numbers, int i, int j)
{
    int temp = numbers[i];
    numbers[i] = numbers[j];
    numbers[j] = temp;
}

int partition(int* numbers, int p, int r)
{
    int pivot = numbers[r];
    int i = p - 1;
    for(int j = p; j < r; j++)
    {
        if(numbers[j] <= pivot)
        {
            i++;
            swap(numbers, i, j);
        }
    }
    swap(numbers, i + 1, r);

    cout << "After patitioning with pivot = " << pivot << "\n";
    print(numbers, p, r, i + 1);
    cout << "\n";

    return i + 1;
}

void quicksort(int* numbers, int p, int r)
{
    if(p < r)
    {
        int q = partition(numbers, p, r);
        quicksort(numbers, p, q - 1);
        quicksort(numbers, q + 1, r);
    }
}


int main()
{
    //Set up
    srand(time(NULL));
    int* numbers = new int[size];

    //Generate random numbers
    for(int i = 0; i < size; i++)
        numbers[i] = rand() % 90 + 10;

    //Test quicksort
    cout << "Initial array:\n";
    print(numbers);
    cout << "\n";

    quicksort(numbers, 0, size-1);

    cout << "Final array:\n";
    print(numbers);
    cout << "\n";

    return 0;
}
