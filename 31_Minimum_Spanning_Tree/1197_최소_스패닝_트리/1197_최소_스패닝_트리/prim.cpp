#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_V 10010
#define MAX_E 100010
#define POS_INF +123456789

struct Edge {
public:
	Edge() {}
	Edge(int _start, int _end, int _cost) : start(_start), end(_end), cost(_cost) {}
	Edge(const Edge &other) : start(other.start), end(other.end), cost(other.cost) {}
	~Edge() {}
	Edge &operator=(const Edge &other) { start = other.start; end = other.end; cost = other.cost; return *this; }
	friend bool operator<=(const Edge &left, const Edge &right) { return left.cost <= right.cost; }
	friend bool operator<(const Edge &left, const Edge &right) { return left.cost < right.cost; }
public:
	int start, end;
	int cost;
};


struct Vector {
public:
	Vector() : length(0), capacity(100) { data = new Edge[capacity]; }
	~Vector() { if (data) delete[] data; }
	void push_back(Edge val) {
		if (isFull()) resize();
		data[length++] = val;
	}
	void pop_back() {
		if (isEmpty()) return;
		length--;
	}
	void resize() {
		// copy
		int _capacity = 2 * capacity;
		Edge* _data = new Edge[_capacity];
		for (int i = 0; i < length; i++) _data[i] = data[i];
		// swap
		Edge *temp = data;
		data = _data; capacity = _capacity;
		delete[] temp;
	}
	void init() { length = 0; }
	int size() { return length; }
	bool isEmpty() { return length == 0; }
	bool isFull() { return length == capacity; }
	Edge& operator[](int idx) { return data[idx]; }
public:
	int length, capacity;
	Edge *data;
};
Vector edges[MAX_V];


struct MinHeap {
public:
	MinHeap() : size(0) {}
	~MinHeap() {}
	void push(Edge edge) {
		data[++size] = edge;

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
		swap(data[size], data[1]); --size;

		int parent = 1;
		while (parent <= size / 2) {
			int minIdx = parent;
			int leftChild = parent * 2;
			int rightChild = parent * 2 + 1;
			if (leftChild <= size && data[leftChild] < data[minIdx])
				minIdx = leftChild;
			if (rightChild <= size && data[rightChild] < data[minIdx])
				minIdx = rightChild;
			if (minIdx == parent) break;

			swap(data[minIdx], data[parent]);
			parent = minIdx;
		}
	}
	void init() { size = 0; }
	Edge top() {
		if (isEmpty()) return Edge(-1, -1, -1);
		else return data[1];
	}
	bool isEmpty() { return size == 0; }
	void swap(Edge &left, Edge &right) {
		Edge temp = left;
		left = right; right = temp;
	}
public:
	int size;
	Edge data[MAX_E];
};
MinHeap minHeap;


int minWeight[MAX_V];
bool selected[MAX_V];
void primMST(int src, int V) {
	// init
	for (int v = 1; v <= V; v++) {
		minWeight[v] = POS_INF;
		selected[v] = false;
	}
	minWeight[src] = 0;
	minHeap.init();
	minHeap.push(Edge(src, src, 0));
	// dijkstra
	while (!minHeap.isEmpty()) {
		int node = minHeap.top().end;
		int nodeWeight = minHeap.top().cost;
		selected[node] = true;

		minHeap.pop();
		for (int i = 0; i < edges[node].size(); i++) {
			int next = edges[node][i].end;
			int nextWeight = edges[node][i].cost;
			if (!selected[next] && nextWeight < minWeight[next]) {
				minWeight[next] = nextWeight;
				minHeap.push(Edge(node, next, nextWeight));
			}
		}
	}
}

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int V, E; scanf("%d %d", &V, &E);
	for (int e = 1; e <= E; e++) {
		int start, end, cost; scanf("%d %d %d", &start, &end, &cost);
		edges[start].push_back(Edge(start, end, cost));
		edges[end].push_back(Edge(end, start, cost));
	}

	primMST(1, V);
	int minCost = 0;
	for (int v = 2; v <= V; v++) minCost += minWeight[v];
	printf("%d\n", minCost);

	return 0;
}