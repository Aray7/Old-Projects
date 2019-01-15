#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int compareCounter;
int moveCounter;

//------------------------------------------------------------------
// Initialize data array with random values
//------------------------------------------------------------------
void create_random_data(int data[], int count, int range)
{
   // Put specified count of random numbers into data array
   for (int index = 0; index < count; index++)
      data[index] = rand() % range;
}

//------------------------------------------------------------------
// Initialize data array with mostly sorted values
//------------------------------------------------------------------
void create_mostly_sorted_data(int data[], int count, int swaps)
{
   // Put sorted data values into array
   for (int index = 0; index < count; index++)
      data[index] = index;

   // Shuffle data by swapping random pairs of values
   for (int index = 0; index < swaps; index++)
   {
      int pos1 = rand() % count;
      int pos2 = rand() % count;
      int temp = data[pos1];
      data[pos1] = data[pos2];
      data[pos2] = temp;
   }
}

//----------------------------------------------------------------
// Insertion sort algorithm
//----------------------------------------------------------------
void insertion_sort(int data[], int low, int high)
{
   // Insert each element of unsorted list into sorted list
   for (int unsorted = low+1; unsorted <= high; unsorted++)
   {
      // Select unsorted value to be inserted
      int value = data[unsorted];
      int posn = unsorted;

      // Make room for new data value
      while ((posn > 0) && (data[posn - 1] > value))
      {
	        data[posn] = data[posn - 1];
          moveCounter++;
	        posn--;
          compareCounter++;
      }

      // Put new value into array
      data[posn] = value;
      moveCounter++;
   }
}

//----------------------------------------------------------------
// Partition function used by Quicksort.
//----------------------------------------------------------------
void partition(int data[], int low, int high, int &mid)
{
   // Select pivot value
   int pivot = data[high];
   int left = low;
   int right = high;

   // Partition array into two parts
   while (left < right)
   {
      // Scan left to right
      compareCounter++;
      while ((left < right) && (data[left] < pivot))
      {
         left++;
         compareCounter++;
      }

      // Scan right to left
      compareCounter++;
      while ((left < right) && (data[right] >= pivot))
      {
         right--;
         compareCounter++;
      }

      // Swap data values
      int temp = data[left];
      data[left] = data[right];
      data[right] = temp;
      moveCounter += 2;
   }

   // Swap pivot to mid
   mid = left;
   data[high] = data[mid];
   data[mid] = pivot;
   moveCounter += 2;
}

//----------------------------------------------------------------
// Recursive Quicksort algorithm using basic partition function.
//----------------------------------------------------------------
void quick_sort(int data[], int low, int high)
{
   // Check terminating condition
   if (low < high)
   {
      // Partition data into two parts
      int mid = 0;
      partition(data, low, high, mid);

      // Recursive calls to sort array
      quick_sort(data, low, mid - 1);
      quick_sort(data, mid + 1, high);
   }
}

//----------------------------------------------------------------
// Mergesort using secondary storage for data merging.
//----------------------------------------------------------------
void merge_sort(int data[], int low, int high)
{
   if(high - low < 20)
   {
      insertion_sort(data, low, high);
   }
   else
   {

     // Check terminating condition
     int range = high - low + 1;
     if (range > 1)
     {
        // Divide the array and sort both halves
        int mid = (low + high) / 2;
        merge_sort(data, low, mid);
        merge_sort(data, mid + 1, high);

        // Create temporary array for merged data
        int *copy = new int[range];

        // Initialize array indices
        int index1 = low;
        int index2 = mid + 1;
        int index = 0;

        // Merge smallest data elements into copy array
        while (index1 <= mid && index2 <= high)
        {
           compareCounter++;
           moveCounter++;
  	       if (data[index1] < data[index2])
  	         copy[index++] = data[index1++];
  	       else
           {
  	         copy[index++] = data[index2++];

           }
        }

        // Copy any remaining entries from the first half
        while (index1 <= mid)
        {
  	       copy[index++] = data[index1++];
           moveCounter++;
        }

        // Copy any remaining entries from the second half
        while (index2 <= high)
        {
  	       copy[index++] = data[index2++];
           moveCounter++;
        }

        // Copy data back from the temporary array
        for (index = 0; index < range; index++)
        {
  	       data[low + index] = copy[index];
           moveCounter++;
        }

        delete []copy;
     }
   }
}

int main()
{
    const int Num = 1000;
    int* randomData = new int[Num];
    create_random_data(randomData, Num, Num-1);

    int* mostlySorted = new int[Num];
    create_mostly_sorted_data(mostlySorted, Num, Num/10);

    int* sorted = new int[Num];
    for( int i = 0; i < Num; i++)
        sorted[i] = i;

    cout << "Num = " << Num << endl << endl;

    merge_sort(randomData, 0, Num-1);
    cout << "compare_counter = " << compareCounter << endl << "move_counter = "
    << moveCounter << endl << endl;

    compareCounter = 0;
    moveCounter = 0;

    merge_sort(mostlySorted, 0, Num-1);
    cout << "compare_counter = " << compareCounter << endl << "move_counter = "
    << moveCounter << endl << endl;

    compareCounter = 0;
    moveCounter = 0;

    merge_sort(sorted, 0, Num-1);
    cout << "compare_counter = " << compareCounter << endl << "move_counter = "
    << moveCounter << endl << endl;

    compareCounter = 0;
    moveCounter = 0;

    return 0;
}
