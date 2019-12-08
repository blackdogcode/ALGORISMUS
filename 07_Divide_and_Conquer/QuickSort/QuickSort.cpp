// QuickSort(In-Place): O(NlogN)
// Goal: the number of comparisons depends on which elements are chosen as pivots, 
	// so we'll ask you to explore three different pivoting rules
	// You should not count comparisons one-by-one. 
	// Rather, when there is a recursive call on a subarray of length m, 
	// you should simply add m-1 to your running total of comparisons
// #1. always use the first element of the array as the pivot element.
// #2. always using the final element of the given array as the pivot element
// #3. using the "median-of-three" pivot rule
	// Consider the first, middle, and final elements of the given array. 
	// (If the array has odd length it should be clear what the "middle" element is
	// for an array with even length 2k, use the kth element as the "middle" element
	// So for the array 4 5 6 7, the "middle" element is the second one---- 5 and not 6!)

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

enum class Pivot {LEFTMOST, MEDIAN, RIGHTMOST};

int quick_sort(int* A, int p, int r, Pivot choice);
// pair.first = split position, pair.first = comparision count
pair<int, int> partition(int* A, int p, int r);
int getMedianIndex(int* A, int p, int r);
void swap(int& lhs, int& rhs);

int main(int argc, char* argv[])
{
	cin.sync_with_stdio(false);
	ifstream in("input.txt", ifstream::in);
	if (!in.is_open()) {
		cerr << "input.txt file not found!";
		return -1;
	}
	cin.rdbuf(in.rdbuf());

	int size; cin >> size;
	int* A = new int[size];
	for (register int i = 0; i < size; ++i)
		cin >> A[i];

	int total_comparsion_count = 0;
	// Correct Output = 162085
	// total_comparsion_count = quick_sort(A, 0, size - 1 , Pivot::LEFTMOST);
	// Correct Output = 164123
	// total_comparsion_count = quick_sort(A, 0, size - 1, Pivot::RIGHTMOST);
	// Correct Output = 138382
	total_comparsion_count = quick_sort(A, 0, size - 1, Pivot::MEDIAN);
	cout << total_comparsion_count;

	delete[] A;
	return 0;
}

int quick_sort(int* A, int p, int r, Pivot choice)
{
	if (p >= r) return 0;
	int comparision_count = 0; pair<int, int> ret;
	// Divide and Conquer
	switch (choice) {
	case Pivot::LEFTMOST:
		break;
	case Pivot::RIGHTMOST:
		swap(A[p], A[r]);
		break;
	case Pivot::MEDIAN:
		swap(A[p], A[getMedianIndex(A, p, r)]);
		break;
	default:
		cerr << "Error: Undefined Pivot Flag";
		break;
	}
	ret = partition(A, p, r);
	comparision_count += ret.second;
	int q = ret.first;
	comparision_count += quick_sort(A, p, q - 1, choice);
	comparision_count += quick_sort(A, q + 1, r, choice);

	return comparision_count;
}

pair<int, int> partition(int* A, int p, int r) {
	int pivot = A[p];
	int i = p, j = p + 1;
	while (j <= r) {
		if (A[j] < pivot) // '<': ascending, '>': desceding, 
			swap(A[++i], A[j++]);
		else
			j++;
	}
	swap(A[i], A[p]); // Reposition Pivot

	return make_pair(i, r - p);
}

int getMedianIndex(int* A, int p, int r) {
	vector<pair<int, int>> tmp = { make_pair(A[p], p), make_pair(A[(p + r) / 2], (p + r) / 2), make_pair(A[r], r) };
	sort(tmp.begin(), tmp.end());
	return tmp[1].second;
}
void swap(int& lhs, int& rhs)
{
	int temp = lhs;
	lhs = rhs; rhs = temp;
}