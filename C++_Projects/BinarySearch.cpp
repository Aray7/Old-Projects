#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

void binarySearch(int numbers[], int SIZE, int target, int& index)
{
    int left = 0;
    int right = SIZE - 1;
    int middle;

    while(left <= right)
    {
        middle = (left + right) / 2;

        if (numbers[middle] == target)
        {
            index = middle;
            return;
        }
        else if (numbers[middle] > target)
            right = middle - 1;
        else
            left = middle + 1;
    }

    index = -1;
}

int rbs(int numbers[], int left, int right, int entry)
{
    if (left > right)
        return -1;

    int middle = (left + right) / 2;

    if (numbers[middle] == entry)
        return middle;

    else if (numbers[middle] > entry)
        return rbs(numbers, left, middle - 1, entry);

    else
        return rbs(numbers, middle + 1, right, entry);

}

void print(int numbers[], int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        cout << setw(5) << numbers[i];
        if (i % 10 == 9)
            cout << endl;
    }
}

int main()
{
    srand(time(0));

    int SIZE = 10000;
    int * numbers = new int[SIZE];

    for (int i = 0; i < SIZE; i++)
        numbers[i] = rand() % SIZE;

    sort(numbers, numbers + SIZE);
    print(numbers, SIZE);

    int entry;
    cout << "What number would you like to search for?\n";
    cin >> entry;

    int index;

    cout << "Iterative Binary search: ";
    binarySearch(numbers, SIZE, entry, index);
    if (index == -1)
        cout << entry << " was not found. ";
    else
        cout << entry << " was found at location " << index << ". ";

    cout << "Recursive Binary search: ";
    int result = rbs(numbers, 0, SIZE - 1, entry);
    if (result != -1)
        cout << entry << " was found at location " << result << endl;
    else
        cout << entry << " was not found.\n";

    delete [] numbers;
    numbers = nullptr;

    return 0;
}
