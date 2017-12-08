// https://www.acmicpc.net/problem/1197
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_E 100010
#define MAX_V 10010

#define POS_INF 123456789
struct Edge {
	Edge() {}
	Edge(int _start, int _end, int _cost) : start(_start), end(_end), cost(_cost) {}
	~Edge() {}
	friend bool operator<=(Edge &left, Edge &right) { return left.cost <= right.cost; }
	int start, end;
	int cost;
};
Edge edges[MAX_E];

void swap(int &p, int &q) {
	int temp = p;
	p = q; q = temp;
}

struct DisjointSet {
	DisjointSet() {}
	~DisjointSet() {}
	void init(int V) {
		for (int i = 1; i <= V; i++) {
			parent[i] = i;
			rank[i] = size[i] = 1;
		}
	}
	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
	bool merge(int a, int b) {
		a = find(a); b = find(b);
		if (a == b) return false;

		if (rank[a] > rank[b]) swap(a, b);
		parent[a] = b;

		size[b] += size[a];
		if (rank[a] == rank[b]) rank[b] += 1;
		return true;
	}
	int parent[MAX_V];
	int rank[MAX_V], size[MAX_V];
};
DisjointSet disjointSet;


void merge_sort(int p, int r);
void merge(int p, int q, int r, int s);

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int V, E; scanf("%d %d", &V, &E);
	for (int i = 0; i < E; i++)
		scanf("%d %d %d", &edges[i].start, &edges[i].end, &edges[i].cost);

	merge_sort(0, E - 1);

	disjointSet.init(V);

	int mstCost = 0;
	for (int i = 0; i < E; i++)
		if (disjointSet.merge(edges[i].start, edges[i].end)) mstCost += edges[i].cost;

	printf("%d\n", mstCost);
	return 0;
}


void merge_sort(int p, int r) {
	if (p >= r) return;

	int q = (p + r) / 2;
	merge_sort(p, q);
	merge_sort(q + 1, r);
	merge(p, q, q + 1, r);
}

void merge(int p, int q, int r, int s) {
	// copy
	int i, j;
	Edge *left = new Edge[q - p + 2];
	for (i = 0; i <= q - p; i++) left[i] = edges[p + i];
	left[i] = Edge(-1, -1, POS_INF);
	Edge *right = new Edge[s - r + 2];
	for (j = 0; j <= s - r; j++) right[j] = edges[r + j];
	right[j] = Edge(-1, -1, POS_INF);
	// sort
	i = j = 0;
	for (int k = p; k <= s; k++) {
		if (left[i] <= right[j]) edges[k] = left[i++];
		else edges[k] = right[j++];
	}
	// release
	delete[] left;
	delete[] right;
}