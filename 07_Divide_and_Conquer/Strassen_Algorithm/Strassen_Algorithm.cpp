// Strassen Matrix Multiplication: O(N^2)
// Reference: https://www.geeksforgeeks.org/strassens-matrix-multiplication/
// Online Judge: https://practice.geeksforgeeks.org/problems/multiply-matrices/1

#include <iostream>
#include <fstream>

using namespace std;

void multiply_matrix(long long** A, long long** B, long long** C, long long N);

int main(int argc, char *argv[])
{
   cin.sync_with_stdio(false);
   ifstream in("input.txt", ifstream::in);
   cin.rdbuf(in.rdbuf());

   int test_case; cin >> test_case;
   for (register int t = 0; t < test_case; ++t) {
      int N; cin >> N;
      // Matrix Allocation
      long long** A = new long long*[N];
      long long** B = new long long*[N];
      long long** C = new long long*[N];
      for (register int i = 0; i < N; ++i) {
         A[i] = new long long[N]; B[i] = new long long[N]; C[i] = new long long[N];
      }
      // Matrix initialization: A and B
      for (register int i = 0; i < N; ++i) {
         for (register int j = 0; j < N; ++j) {
            cin >> A[i][j];
         }
      }
      for (register int i = 0; i < N; ++i) {
         for (register int j = 0; j < N; ++j) {
            cin >> B[i][j];
         }
      }
      // Multiply Matrix: C = A * B
      multiply_matrix(A, B, C, N);
      // Print Matrix C
      for (register int i = 0; i < N; ++i) {
         for (register int j = 0; j < N; ++j) {
            cout << C[i][j] << " ";
         }
      }
      cout << "\n";
      // Clear Memory
      for (register int i = 0; i < N; ++i) {
         delete[] A[i]; delete B[i]; delete C[i];
      }
      delete[] A; delete[] B; delete[] C;
   }
   return 0;
}

// T(N) = 7T(N / 2) + O(N ^ 2)
void multiply_matrix(long long** A, long long** B, long long** C, long long N) {
   if (N == 1) return;
   if (N == 2) {
      long long p1 = A[0][0] * (B[0][1] - B[1][1]);
      long long p2 = (A[0][0] + A[0][1]) * B[1][1];
      long long p3 = (A[1][0] + A[1][1]) * B[0][0];
      long long p4 = A[1][1] * (B[0][1] - B[0][0]);
      long long p5 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
      long long p6 = (A[0][1] - A[1][1]) * (B[0][1] + B[1][1]);
      long long p7 = (A[0][0] - A[0][1]) * (B[0][0] + B[0][1]);
      C[0][0] = p5 + p4 - p2 + p6;
      C[0][1] = p1 + p2;
      C[1][0] = p3 + p4;
      C[1][1] = p1 + p5 - p3 - p7;
      return;
   }
   long long half = N / 2;
   multiply_matrix(A, B, C, half);
   multiply_matrix(A + N, B + N, C + N, half);
   multiply_matrix(A + half, B + half, C + half, half);
   multiply_matrix(A + N + half, B + N + half, C + N + half, half);
   return;
}