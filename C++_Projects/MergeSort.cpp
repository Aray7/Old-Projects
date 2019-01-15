#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int size = 20;

void merge(int numbers[], int left, int mid, int right)
{
    //Set up indices and create a copy array
    int i = left, j = mid + 1, k = 0;
    int copy[right - left + 1];

    //Interleave the two lists
    while(i <= mid && j <= right)
    {
        if(numbers[i] < numbers[j])
            copy[k++] = numbers[i++];
        else
            copy[k++] = numbers[j++];
    }

    //If we ran out of values from the right list, copy the rest of left
    while(i <= mid)
        copy[k++] = numbers[i++];

    //If we ran out of values from right left list, copy the rest of right
    while(j <= right)
        copy[k++] = numbers[j++];

    //Overwrite numbers with the new sorted portion
    for(int index = 0; index < right - left + 1; index++)
        numbers[left + index] = copy[index];
}

void mergesort(int numbers[], int left, int right)
{
    if(left < right)
    {
        int mid = (left + right)/2;
        mergesort(numbers, left, mid);
        mergesort(numbers, mid+1, right);
        merge(numbers, left, mid, right);
    }
}

void print(int numbers[])
{
    for(int i = 0; i < size; i++)
        cout << numbers[i] << " ";
    cout << "\n";
}

int main()
{
    srand(time(NULL));
    int numbers[size];

    for(int i = 0; i < size; i++)
        numbers[i] = rand() % 100;

    print(numbers);

    mergesort(numbers, 0, size-1);

    print(numbers);
    return 0;
}
