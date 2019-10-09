//
//  TYPE: Merge Sort[O(nlogn)] : https://www.acmicpc.net/problem/2751
//  GOAL: Sort Array in non-decreasing order
//  Paradigm: Divide_and_Conquer
#include <iostream>
#include <fstream>

#define INF 123456789

using namespace std;

void merge_sort(int* arr, int p, int r);
void merge(int* arr, int p, int q, int r, int s);

int main(int argc, char* argv[])
{
	cin.sync_with_stdio(false);
	ifstream in("input.txt", ifstream::in);
	if (!in.is_open()) { cout << "file open failed!\n"; return -1; }
	cin.rdbuf(in.rdbuf());

	int N; cin >> N;
	int* arr = new int[N];
	for (register int i = 0; i < N; ++i) cin >> arr[i];

	merge_sort(arr, 0, N - 1); // arr[0...N-1]
	
	for (register int i = 0; i < N; ++i) cout << arr[i] << "\n";

	delete[] arr;
	return 0;
}

void merge_sort(int* arr, int p, int r) // arr[p....r]
{
	// Base Condition
	if (p >= r) return; // 1-element
	// Divide
	int q = (p + r) / 2;
	merge_sort(arr, p, q);
	merge_sort(arr, q + 1, r);
	// Conquer
	merge(arr, p, q, q + 1, r);

	return;
}

void merge(int* arr, int p, int q, int r, int s) // arr[p...q] , arr[r...s]
{
	// Duplication Array for Merge
	int lhsIdx = 0, rhsIdx = 0;
	int* lhsArr = new int[q - p + 2];
	int* rhsArr = new int[s - r + 2];
	for (lhsIdx = 0; lhsIdx <= q - p; ++lhsIdx)
		lhsArr[lhsIdx] = arr[p + lhsIdx];
	lhsArr[lhsIdx] = INF;
	for (rhsIdx = 0; rhsIdx <= s - r; ++rhsIdx)
		rhsArr[rhsIdx] = arr[r + rhsIdx];
	rhsArr[rhsIdx] = INF;
	
	// Compare and Merge
	lhsIdx = rhsIdx = 0;
	for (register int k = p; k <= s; ++k) {
		if (lhsArr[lhsIdx] <= rhsArr[rhsIdx])
			arr[k] = lhsArr[lhsIdx++];
		else
			arr[k] = rhsArr[rhsIdx++];
	}
	delete[] lhsArr;
	delete[] rhsArr;

	return;
}