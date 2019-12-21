// NaiveInversionCount.cpp : O(N^2)

#include <iostream>
#include <fstream>

using namespace std;

int getInvCount(int arr[], int n)
{
   int inv_count = 0;
   for (int i = 0; i < n - 1; i++)
      for (int j = i + 1; j < n; j++)
         if (arr[i] > arr[j])
            inv_count++;

   return inv_count;
}

int main(int argc, char *argv[])
{
   cout.sync_with_stdio(false);

   int test_case; cin >> test_case;
   for (register int i = 0; i < test_case; ++i) {
      int size; cin >> size;
      int* arr = new int[size];
      for (register int i = 0; i < size; ++i)
         cin >> arr[i];
      cout << getInvCount(arr, size) << "\n";
      delete[] arr;
   }
   return 0;
}