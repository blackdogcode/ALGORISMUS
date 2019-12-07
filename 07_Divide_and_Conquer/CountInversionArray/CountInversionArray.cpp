// Count the number of Inversion in Array using Merge Sort: O(Nlog(N) 
// https://www.geeksforgeeks.org/counting-inversions/
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

long long merge_sort(int *arr, int p, int r);
long long merge(int*arr, int p, int q, int r, int s);

int main(int argc, char *argv[]) {
   cout.sync_with_stdio(false);

   ifstream in("input.txt", ifstream::in);
   if (!in.is_open()) cout << "Open Input File Failed" << endl;
   cin.rdbuf(in.rdbuf());

   long long totalNumberOfInvCount = 0;
   int size; cin >> size;
   int* arr = new int[size];
   for (register int i = 0; i < size; ++i)
      cin >> arr[i];
   totalNumberOfInvCount = merge_sort(arr, 0, size - 1);
   cout << totalNumberOfInvCount; // Correct Output:2407905288
   delete[] arr;
   return 0;
}

long long merge_sort(int *arr, int p, int r) {
   if (p >= r) return 0;
   long long inversion_count = 0;
   
   int q = (p + r) / 2;
   inversion_count += merge_sort(arr, p, q);
   inversion_count += merge_sort(arr, q + 1, r);
   inversion_count += merge(arr, p, q, q + 1, r);

   return inversion_count;
}

long long merge(int *arr, int p, int q, int r, int s) {
   int i, j;
   int *lhs = new int[q - p + 2];
   int *rhs = new int[s - r + 2];
   for (i = 0; i <= q - p; ++i) 
      lhs[i] = arr[p + i];
   lhs[i] = INT_MAX;
   for (j = 0; j <= s - r; ++j) 
      rhs[j] = arr[r + j];
   rhs[j] = INT_MAX;

   long long inversion_count = 0; i = j = 0;
   for (register int k = p; k <= s; ++k) {
      if (lhs[i] <= rhs[j]) {
         arr[k] = lhs[i++];
         p++;
      }
      else {
         arr[k] = rhs[j++];
         // Core Part!
         if (lhs[i] != INT_MAX)  
            inversion_count += r - p;
      }
   }
   delete[] lhs; 
   delete[] rhs;
   return inversion_count;
}