#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define POS_INF +123456789
#define NEG_INF -123456789
#define MAX_N 200000

void swap(int &a, int &b);

struct MinHeap {
	MinHeap() : size(0) {
		arr = new int[MAX_N + 10];
	}
	~MinHeap() {
		delete[] arr;
	}

	void insert(int newKey);
	void pop();
	int top();
	bool isEmpty();
	void display();

	int size;
	int *arr;
};

struct MaxHeap {
	MaxHeap() : size(0) {
		arr = new int[MAX_N + 10];
	}
	~MaxHeap() {
		delete[] arr;
	}

	void insert(int newKey);
	void pop();
	bool isEmpty();
	int top();
	void display();

	int size;
	int *arr;
};

int generateNewKey(int idx, int a, int b, int previous) {
	if (idx == 0) return 1983;
	int next = (previous * (long long)a + b) % 20090711;
	return next;
}

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);

	int C; scanf("%d", &C);
	for (int test_case = 1; test_case <= C; test_case++) {
		int N; scanf("%d", &N);
		int a, b; scanf("%d %d", &a, &b);

		MaxHeap leftMaxHeap;
		MinHeap rightMinHeap;

		int newKey = 0, result = 0;
		for (int i = 0; i < N; i++) {
			newKey = generateNewKey(i, a, b, newKey);
			if (leftMaxHeap.size == rightMinHeap.size) {
				if (leftMaxHeap.top() >= newKey)
					leftMaxHeap.insert(newKey);
				else {
					rightMinHeap.insert(newKey);
					int key = rightMinHeap.top();
					rightMinHeap.pop();
					leftMaxHeap.insert(key);
				}
			}
			else {
				if (leftMaxHeap.top() >= newKey) {
					leftMaxHeap.insert(newKey);
					int key = leftMaxHeap.top();
					leftMaxHeap.pop();
					rightMinHeap.insert(key);
				}
				else {
					rightMinHeap.insert(newKey);
				}
			}
			int midKey = leftMaxHeap.top();
			result = (result + midKey) % 20090711;
		}
		printf("%d\n", result);
	}

	return 0;
}

void swap(int &a, int &b) {
	int temp = a;
	a = b; b = temp;
}


//---------------- Min Heap ---------------------//
void MinHeap::insert(int newKey) {
	arr[++size] = newKey;

	int child = size;
	int parent = size / 2;
	while (parent >= 1) {
		if (arr[child] < arr[parent])
			swap(arr[child], arr[parent]);
		else break;
		child = parent; parent /= 2;
	}
}

void MinHeap::pop() {
	if (isEmpty()) return;
	// last --> top
	arr[1] = arr[size--];
	// drop down
	int curr = 1;
	int leftChild = 2 * curr;
	int rightChild = 2 * curr + 1;
	while (curr <= size / 2) {
		int minIdx = curr;
		if (arr[leftChild] < arr[curr]) minIdx = leftChild;
		if (arr[rightChild] < arr[minIdx]) minIdx = rightChild;

		if (curr == minIdx) break;
		swap(arr[curr], arr[minIdx]);
		curr = minIdx;
		leftChild = 2 * curr;
		rightChild = 2 * curr + 1;
	}
}

bool MinHeap::isEmpty() {
	return size == 0;
}
int MinHeap::top() {
	if (isEmpty()) return POS_INF;
	else return arr[1];
}
void MinHeap::display() {
	for (int i = 1; i <= size; i++)
		printf("%d ", arr[i]);
	puts("");
}

//---------------- Max Heap ---------------------//
void MaxHeap::insert(int newKey) {
	arr[++size] = newKey;

	int child = size;
	int parent = size / 2;
	while (parent >= 1) {
		if (arr[child] > arr[parent])
			swap(arr[child], arr[parent]);
		else break;
		child = parent; parent /= 2;
	}
}

void MaxHeap::pop() {
	if (isEmpty()) return;
	// last --> top
	arr[1] = arr[size--];
	// drop down
	int curr = 1;
	int leftChild = 2 * curr;
	int rightChild = 2 * curr + 1;
	while (curr <= size / 2) {
		int maxIdx = curr;
		if (arr[leftChild] > arr[curr]) maxIdx = leftChild;
		if (arr[rightChild] > arr[maxIdx]) maxIdx = rightChild;

		if (curr == maxIdx) break;
		swap(arr[curr], arr[maxIdx]);
		curr = maxIdx;
		leftChild = 2 * curr;
		rightChild = 2 * curr + 1;
	}
}

bool MaxHeap::isEmpty() {
	return size == 0;
}
int MaxHeap::top() {
	if (isEmpty()) return NEG_INF;
	else return arr[1];
}
void MaxHeap::display() {
	for (int i = 1; i <= size; i++)
		printf("%d ", arr[i]);
	puts("");
}