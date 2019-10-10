//
//  Goal: Sorting Array in descending order
//  Type: QuickSort(In-Place)
//  Approach: Divide and Conquer
//  Created by Sangchul, Song on 06/10/16
//  Copyright © 2016 HYU. All rights reserved.
//  Input:  A[p - r]
//  Output: A[p - r] (Desceding Order)
//
#include <iostream>
#include <fstream>;

using namespace std;

void quick_sort(int* A, int p, int r);
int partition(int* A, int p, int r);
void swap(int* A, int i, int j);

int main(int argc, char* argv[])
{
	cin.sync_with_stdio(false);
	ifstream in("input.txt", ifstream::in);
	cin.rdbuf(in.rdbuf());

	int N, *A;
	cin >> N;
	A = new int[N];

	for (int i = 0; i < N; ++i) cin >> A[i];
	quick_sort(A, 0, N - 1);
	for (int i = 0; i < N; ++i) cout << A[i] << "\n";


	delete[] A;
	return 0;
}

void
quick_sort(int* A, int p, int r) // A[p...r]
{
	if (p >= r) // Base Condition
		return;
	else {
		// Divide and Conqure
		int q = partition(A, p, r);
		quick_sort(A, p, q - 1);
		quick_sort(A, q + 1, r);
	}
}

// Input: A[p...r]
// Output: i (index of pivot, A[p...i-1] <= A[q] && A[i+1...r] > A[q])
int
partition(int* A, int p, int r) // A[p...r]
{
	int pivot = A[r]; // Rightest
	int i = p - 1, j = p;
	while (j < r) {
		if (A[j] >= pivot) // '>=': desceding, '<=': ascending
			swap(A, ++i, j++);
		else
			j++;
	}
	swap(A, ++i, r); // Reposition Pivot

	return i;
}

void
swap(int* A, int i, int j)
{
	int temp = A[j];
	A[j] = A[i];
	A[i] = temp;
}