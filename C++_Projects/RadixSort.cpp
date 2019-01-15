#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int MAX_VALUE = 999;

void print(int* data, int size)
{
    for(int i = 0; i < size; i++)
        cout << data[i] << " ";
    cout << "\n";
}

void radixSort(int* data, int size, int numDigits)
{
    //For each digit
    for(int d = 0; d < numDigits; d++)
    {
        //Do counting sort
        int count[10];
        int extra[size];

        //Assuming base 10, we'll count occurrences of each digit
        for(int i = 0; i < 10; i++)
            count[i] = 0;

        //Get digit #d (going from least significant to most significant)
        for(int i = 0; i < size; i++)
            count[data[i]/int(pow(10,d)) % 10]++;

        //Do the fancy algorithmic thing that keeps this a stable sort
        for(int i = 1; i < MAX_VALUE + 1; i++)
            count[i] = count[i] + count[i-1];

        //Insert numbers into extra in partially sorted order (sorted by digit d)
        for(int i = size - 1; i >= 0; i--)
        {
            extra[count[data[i]/int(pow(10,d)) % 10]-1] = data[i];
            count[data[i]/int(pow(10,d)) % 10]--;
        }

        //Copy extra back into data for the next round
        for(int i = 0; i < size; i++)
            data[i] = extra[i];

        //Let's print this array on each iteration so we can watch the algorithm progress
        cout << "\nAfter sorting on digit " << d << ":\n";
        print(data, size);
    }
}

int main()
{
    srand(time(NULL));

    int size = 10;
    int numbers[size];

    for(int i = 0; i < size; i++)
        numbers[i] = rand() % (MAX_VALUE + 1);

    cout << "Unsorted:\n";
    print(numbers, size);

    radixSort(numbers, size, 3);

    cout << "\nSorted:\n";
    print(numbers, size);

    return 0;
}
