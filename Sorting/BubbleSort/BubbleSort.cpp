// C++ program for implementation of Bubble sort 
#include <iostream>
#include <fstream>

using namespace std;

void swap(int &lh, int &rh);
void bubbleSort(int arr[], int N);

int main()
{
	cin.sync_with_stdio(false);
	ifstream in("input.txt", ifstream::in);
	if (!in.is_open()) { cerr << "input.txt file nout found!"; return -1; }
	cin.rdbuf(in.rdbuf());

	int N; cin >> N;
	int* arr = new int[N];
	for (register int i = 0; i < N; ++i) cin >> arr[i];

	for (register int i = 0; i < N; ++i) cout << arr[i]; cout << "\n";
	bubbleSort(arr, N);
	for (register int i = 0; i < N; ++i) cout << arr[i]; cout << "\n";

	delete[] arr;
	return 0;
}

void bubbleSort(int arr[], int N) {
	for (register int i = 0; i < N-1; ++i) {
		for (register int j = 0; j < N-(i+1); ++j)
			if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
	}
}

void swap(int &lh, int &rh) {
	int temp = lh;
	lh = rh;
	rh = temp;
}