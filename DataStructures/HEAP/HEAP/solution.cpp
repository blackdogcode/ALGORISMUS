// https://algospot.com/judge/problem/read/RUNNINGMEDIAN
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define POS_INF +123456789
#define NEG_INF -123456789
#define MAX_N 200000

void swap(int &a, int &b) {
	int temp = a;
	a = b; b = temp;
}

struct MinHeap {
	MinHeap() : size(0) { arr = new int[MAX_N + 10]; }
	~MinHeap() { delete[] arr; }

	void insert(int newKey);
	void pop();
	int top();
	bool isEmpty();

	int *arr, size;
};

struct MaxHeap {
	MaxHeap() : size(0) { arr = new int[MAX_N + 10]; }
	~MaxHeap() { delete[] arr; }

	void insert(int newKey);
	void pop();
	bool isEmpty();
	int top();

	int *arr, size;
};

int generateNextKey(int idx, int a, int b, int prevKey) {
	if (idx == 0) return 1983;
	int next = (prevKey * (long long)a + b) % 20090711; // 오버 플로우 방지: long long
	return next;
}

int main(int argc, char *argv[]) {
	freopen("sample_input.txt", "r", stdin);

	int C; scanf("%d", &C);
	for (int test_case = 1; test_case <= C; test_case++) {
		int N; scanf("%d", &N);
		int a, b; scanf("%d %d", &a, &b);

		MaxHeap leftMaxHeap;
		MinHeap rightMinHeap;

		int nextKey = 0, result = 0;
		for (int idx = 0; idx < N; idx++) {
			nextKey = generateNextKey(idx, a, b, nextKey);
			// 불변식 1: |leftMaxHeap| == |rightMinHeap| or |rightMinHeap| + 1
			if (leftMaxHeap.size == rightMinHeap.size)
				leftMaxHeap.insert(nextKey);
			else
				rightMinHeap.insert(nextKey);
			// 불변식 2: leftMaxHeap.top <= rightMinHeap.top
			if (!leftMaxHeap.isEmpty() && !rightMinHeap.isEmpty()) {
				if (leftMaxHeap.top() > rightMinHeap.top()) {
					int leftMax = leftMaxHeap.top();
					int rightMin = rightMinHeap.top();
					leftMaxHeap.pop(); rightMinHeap.pop();
					leftMaxHeap.insert(rightMin);
					rightMinHeap.insert(leftMax);
				}
			}
			// 결과식: 불변식 1과 2만족 시, 중간 값은 항상 leftMaxHeap.top
			int midKey = leftMaxHeap.top();
			result = (result + midKey) % 20090711;
		}
		printf("%d\n", result);
	}
	return 0;
}

//-----------------------------------------------//
//---------------- Min Heap ---------------------//
//-----------------------------------------------//
void MinHeap::insert(int newKey) {
	// Heap '모양 규칙' 보장
	arr[++size] = newKey;
	// Heap '대소 규칙' 성립
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
	// overwrite: end --> top
	arr[1] = arr[size--];
	// Heap '대소 규칙' 성립
	int curr = 1;
	int leftChild = 2 * curr;
	int rightChild = 2 * curr + 1;
	while (curr <= size / 2) {
		int minIdx = curr;
		if (leftChild <= size && arr[leftChild] < arr[minIdx]) minIdx = leftChild;
		if (rightChild <= size && arr[rightChild] < arr[minIdx]) minIdx = rightChild;

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

//-----------------------------------------------//
//---------------- Max Heap ---------------------//
//-----------------------------------------------//
void MaxHeap::insert(int newKey) {
	// Heap '모양 규칙' 보장
	arr[++size] = newKey;
	// Heap '대소 규칙' 성립
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
	// overwirte: end --> top
	arr[1] = arr[size--];
	// Heap '대소 규칙' 성립
	int curr = 1;
	int leftChild = 2 * curr;
	int rightChild = 2 * curr + 1;
	while (curr <= size / 2) {
		int maxIdx = curr;
		if (leftChild <= size && arr[leftChild] > arr[maxIdx]) maxIdx = leftChild;
		if (rightChild <= size && arr[rightChild] > arr[maxIdx]) maxIdx = rightChild;

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