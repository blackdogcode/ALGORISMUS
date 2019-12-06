// O(Nlog(N) 
// https://www.geeksforgeeks.org/counting-inversions/
// https://practice.geeksforgeeks.org/problems/inversion-of-array/0

#include <iostream>
#include <fstream>
#include <cmath>

#define INF 123456789

using namespace std;

long long merge_sort(int *arr, int p, int r);
long long merge(int *arr, int p, int q, int r, int s);
void swap(int& lhs, int& rhs) {
   int tmp = lhs;
   lhs = rhs; rhs = tmp;
}

int main(int argc, char *argv[]) {
   cout.sync_with_stdio(false);

   ifstream in("IntegerArray.txt", ifstream::in);
   if (!in.is_open()) cout << "Open Input File Failed" << endl;
   cin.rdbuf(in.rdbuf());
   ofstream out("output.txt", ofstream::out);

   int test_case; cin >> test_case;
   for (register int i = 0; i < 1; ++i) {
      int val; cin >> val;
      int size = 1, tmp = val;
      while (tmp / 10 != 0) {
         tmp /= 10; ++size;
      }
      int* arr = new int[size];
      for (register int j = size - 1; j >= 0; --j) {
         arr[j] = val % 10;
         val /= 10;
      }
      out << merge_sort(arr, 0, size - 1);
      delete[] arr;
   }

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
   lhs[i] = INF;
   for (j = 0; j <= s - r; ++j) 
      rhs[j] = arr[r + j];
   rhs[j] = INF;

   long long inversion_count = 0; i = j = 0;
   for (register int k = p; k <= s; ++k) {
      if (lhs[i] <= rhs[j]) {
         arr[k] = lhs[i++];
         ++p;
      }
      else {
         arr[k] = rhs[j++];
         // Core Part!
         if (lhs[i] != INF) 
            inversion_count += r - p;
      }
   }
   delete[] lhs; 
   delete[] rhs;
   return inversion_count;
}