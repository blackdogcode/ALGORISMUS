#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

void swap(int &A, int &B) {
	int temp = A;
	A = B; B = temp;
}

struct DisjointSet {
	vector<int> parent, rank;

	DisjointSet() {}
	DisjointSet(int N) : parent(N), rank(N, 1) {
		for (int i = 0; i < N; i++)
			parent[i] = i;
	}
	// path compression
	int find(int node) {
		if (parent[node] == node) return node;
		
		return parent[node] = find(parent[node]);
	}
	// union by rank
	void merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) return; // already belong to the same set
		
		if (rank[u] > rank[v]) swap(u, v);
		parent[u] = v;
		if (rank[u] == rank[v]) rank[v] += 1;
	}
};

int main(int argc, char *argv[]) {
	//setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int N, M; scanf("%d %d", &N, &M);
	DisjointSet set(N + 1);
	for (int m = 1; m <= M; m++) {
		int command; scanf("%d", &command);
		int a, b; scanf("%d %d", &a, &b);
		if (command == 0) {
			set.merge(a, b);
		}
		else if (command == 1) {
			a = set.find(a);
			b = set.find(b);
			if (a == b) printf("YES\n");
			else printf("NO\n");
		}
		else {
			printf("ERROR: INVALID COMMAND(%d)\n", command);
		}
	}
	return 0;
}