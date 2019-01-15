#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int MAX_VALUE = 9;

void print(int* data, int size)
{
    for(int i = 0; i < size; i++)
        cout << data[i] << " ";
    cout << "\n";
}

void countingSort(int in[], int out[], int size)
{
    int count[MAX_VALUE + 1];

    //Fill the count array with zeroes
    for(int i = 0; i < MAX_VALUE + 1; i++)
        count[i] = 0;

    //Count all occurrences of each number
    for(int i = 0; i < size; i++)
        count[in[i]]++;

    cout << "\nCount array contents after counting:\n";
    print(count, MAX_VALUE+1);

    //Do the fancy algorithmic thingy
    //(for each index, compute how many items are <= to that index)
    for(int i = 1; i < MAX_VALUE + 1; i++)
        count[i] = count[i] + count[i-1];

    cout << "\nCount array contents after fancy thing:\n";
    print(count, MAX_VALUE+1);

    //Shuffle everything into place
    for(int i = size - 1; i >= 0; i--)
    {
        out[count[in[i]]-1] = in[i];
        count[in[i]]--;

        cout << "\nCount array contents after examining: " << in[i] << "\n";
        print(count, MAX_VALUE+1);
    }
}

int main()
{
    srand(time(NULL));

    int size = 10;
    int unsorted[size];

    for(int i = 0; i < size; i++)
        unsorted[i] = rand() % (MAX_VALUE + 1);

    cout << "Unsorted numbers:\n";
    print(unsorted, size);
    int sorted[size];
    countingSort(unsorted, sorted, size);
    cout << "\nSorted numbers:\n";
    print(sorted, size);

    return 0;
}
