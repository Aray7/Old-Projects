#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 30;

void print(int numbers[])
{
    for (int i = 0; i < SIZE; i++)
        cout << numbers[i] << " ";
    cout << endl;
}

void bubblesort1(int numbers[])
{
    int temp;
    int count = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - 1; j++)
        {
            if (numbers[j] > numbers[j+1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }

            count++;
        }
    }

    cout << "\nBubblesort1 completed after " << count << " checks.\n";
}

void bubblesort2(int numbers[])
{
    int temp;
    int count = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - 1 - i; j++)
        {
            if (numbers[j] > numbers[j+1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }

            count++;
        }
    }

    cout << "Bubblesort2 (staircase) completed after " << count << " checks.\n";
}

void bubblesort3(int numbers[])
{
    int temp, k;
    bool inversion = false;
    int count = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - 1; j++)
        {
            if (numbers[j] > numbers[j+1])
            {
                inversion = true;
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }

            count++;
        }

        if (!inversion)
        {
            k = i + 1;
            break;
        }
        inversion = false;
    }

    cout << "Bubblesort3 (early stopping) completed after " << count << " checks. (k = " << k << ")\n";
}

void bubblesort4(int numbers[])
{
    int temp, k;
    bool inversion = false;
    int count = 0;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE - 1 - i; j++)
        {
            if (numbers[j] > numbers[j+1])
            {
                inversion = true;
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;
            }

            count++;
        }

        if (!inversion)
        {
            k = i + 1;
            break;
        }
        inversion = false;
    }

    cout << "Bubblesort4 (2 and 3 combined) completed after " << count << " checks. (k = " << k << ")\n\n";
}

int main()
{
    srand(time(0));

    int numbers1[SIZE];
    int numbers2[SIZE];
    int numbers3[SIZE];
    int numbers4[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        numbers1[i] = rand() % 100;
        numbers2[i] = numbers1[i];
        numbers3[i] = numbers1[i];
        numbers4[i] = numbers1[i];
    }

    //Print array before sorting
    print(numbers1);

    //Bubblesort
    bubblesort1(numbers1);
    bubblesort2(numbers2);
    bubblesort3(numbers3);
    bubblesort4(numbers4);

    //Print array after sorting
    print(numbers1);

    return 0;
}
