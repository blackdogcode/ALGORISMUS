// C++ program for implementation of selection sort 
#include <iostream>
#include <fstream>
using namespace std;

void selectionSort(int arr[], int N);
void swap(int& lh, int& rh);

int main(int argc, char* argv[]) {
	cin.sync_with_stdio(false); // <cstdio> 표준 입출력 함수 동기화 끄기
	ifstream in("input.txt", ifstream::in);
	if (!in.is_open()) { std::cerr << "input.txt file nout found!"; return -1; }
	cin.rdbuf(in.rdbuf());

	int N; cin >> N;
	int* arr = new int[N];
	for (register int i = 0; i < N; ++i) cin >> arr[i];
	
	for (register int i = 0; i < N; ++i) cout << arr[i]; cout << "\n";
	selectionSort(arr, N);
	for (register int i = 0; i < N; ++i) cout << arr[i]; cout << "\n";

	delete[] arr;
	return 0;
}

void selectionSort(int arr[], int N) {
	for (register int i = 0; i < N - 1; ++i) {
		int min_idx = i;
		for (register int j = i + 1; j < N; ++j) {
			if (arr[j] < arr[min_idx]) min_idx = j;
		}
		swap(arr[i], arr[min_idx]);
	}
}

void swap(int& lh, int& rh) {
	int temp = lh;
	lh = rh; 
	rh = temp;
}

