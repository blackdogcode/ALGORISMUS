// https://www.acmicpc.net/problem/1927
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define MAX_N 100010

void swap(int &a, int &b) {
	int temp = a;
	a = b; b = temp;
}
struct MinHeap {
public:
	MinHeap() : size(0) {}

	void push(int _val) {
		data[++size] = _val;
		
		int child = size;
		int parent = child / 2;
		while (parent >= 1) {
			if (data[parent] <= data[child]) break;
			swap(data[parent], data[child]);
			child = parent; parent = child / 2;
		}
	}
	void pop() {
		if (isEmpty()) return;
		
		swap(data[1], data[size--]);
		
		int parent = 1;
		while (parent <= (size / 2)) {
			int minNode = parent;
			int leftChild = parent * 2;
			int rightChild = parent * 2 + 1;
			if (leftChild <= size && data[leftChild] < data[minNode])
				minNode = leftChild;
			if (rightChild <= size && data[rightChild] < data[minNode])
				minNode = rightChild;
			if (minNode == parent) break;

			swap(data[parent], data[minNode]);
			parent = minNode;
		}
	}
	int top() {
		if (isEmpty()) return 0;
		else return data[1];
	}
	bool isEmpty() { return size == 0; }
private:
	int size;
	int data[MAX_N];
};

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	MinHeap minHeap;

	int N; scanf("%d", &N);
	for (int n = 1; n <= N; n++) {
		int val; scanf("%d", &val);
		if (val == 0) {
			printf("%d\n", minHeap.top());
			minHeap.pop();
		}
		else minHeap.push(val);
	}
	return 0;
}