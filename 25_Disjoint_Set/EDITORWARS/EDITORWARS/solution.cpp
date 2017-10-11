// https://algospot.com/judge/problem/read/EDITORWARS
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#define INF 100000

using namespace std;

int strCompare(char *str0, char *str1);
int max(int a, int b) { if (a >= b) return a; else return b; }
int min(int a, int b) { if (a <= b) return a; else return b; }
void swap(int &a, int &b);

struct BipartitionedSet {
	vector<int> parent, enemy;
	vector<int> rank, size;

	BipartitionedSet() {}
	BipartitionedSet(int N) : parent(N), enemy(N, -1), rank(N, 1), size(N, 1) {
		for (int i = 0; i < N; i++)
			parent[i] = i;
	}

	// return root of set
	int find(int A) {
		if (A == -1) return A;
		if (A == parent[A]) return A;
		else return A = find(parent[A]); // path compression
	}
	// union set operation
	int merge(int A, int B) {
		A = find(A); B = find(B);
		if (A == B) return A; // 이미 같은 집합에 속해 있음
		if (A == -1 || B == -1) return max(A, B); // 어느 한 쪽이 공집합

		if (rank[A] > rank[B]) swap(A, B); // union by rank
		parent[A] = B;

		if (rank[A] == rank[B]) rank[B] += 1;
		size[B] += size[A];

		return B;
	}

	bool ack(int A, int B) {
		A = find(A); int enemyA = find(enemy[A]);
		B = find(B); int enemyB = find(enemy[B]);

		if (enemyA == B) return false;

		int u = merge(A, B);
		int v = merge(enemyA, enemyB);
		enemy[u] = v;
		if (v != -1) enemy[v] = u;
		return true;
	}
	bool dis(int A, int B) {
		A = find(A); int enemyA = find(enemy[A]);
		B = find(B); int enemyB = find(enemy[B]);

		if (A == B) return false;

		int u = merge(A, enemyB);
		int v = merge(B, enemyA);
		enemy[u] = v; enemy[v] = u;
		return true;
	}

	int maxPartySize(int N) {
		int minSize = 0;
		for (int node = 0; node < N; node++) {
			if (node != parent[node]) continue;
			if (node > enemy[node]) continue;

			int mySize = size[node];
			int enemySize = enemy[node] == -1 ? 0 : size[find(enemy[node])];
			minSize += min(mySize, enemySize);
		}
		return N - minSize;
	}
};

int main(int argc, char *argv[]) {
	//setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		int N, M; scanf("%d %d", &N, &M);
		char cmd[5]; int a, b;

		int firstContradiction = INF;
		BipartitionedSet editorParty(N);
		for (int m = 1; m <= M; m++) {
			scanf("%s %d %d", cmd, &a, &b);
			if (strCompare(cmd, "ACK") == 0) {
				if (editorParty.ack(a, b) == false)
					firstContradiction = min(m, firstContradiction);
			}
			if (strCompare(cmd, "DIS") == 0) {
				if (editorParty.dis(a, b) == false)
					firstContradiction = min(m, firstContradiction);
			}
		}
		if (firstContradiction != INF)
			printf("CONTRADICTION AT %d\n", firstContradiction);
		else
			printf("MAX PARTY SIZE IS %d\n", editorParty.maxPartySize(N));
	}
	return 0;
}

void swap(int &a, int &b) {
	int temp = a;
	a = b; b = temp;
}

int strCompare(char *str0, char *str1) {
	while (*str0 != 0 && *str1 != 0) {
		if (*str0 != *str1)
			return *str0 - *str1;
		str0++; str1++;
	}
	return *str0 - *str1;
}