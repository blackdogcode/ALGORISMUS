// https://algospot.com/judge/problem/read/MORDOR
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

#define POS_INF +123456789
#define NEG_INF -123456789
int altitude[100010];

int Min(int a, int b) { if (a <= b) return a; else return b; }
int Max(int a, int b) { if (a >= b) return a; else return b; }
struct MinMaxPair {
	int min;
	int max;

	MinMaxPair() {}
	MinMaxPair(int _min, int _max) : min(_min), max(_max) {}
};

struct SegmentTree {
	vector<int> min, max;
	int size;
	SegmentTree() {}
	SegmentTree(int _size) : size(_size), min(_size * 4), max(_size * 4) {
		buildTree(0, size-1, 1);
	}

	MinMaxPair buildTree(int nodeLeft, int nodeRight, int node) {
		if (nodeLeft == nodeRight) {
			min[node] = altitude[nodeLeft];
			max[node] = altitude[nodeRight];
			return MinMaxPair(min[node], max[node]);
		}

		int nodeMid = (nodeLeft + nodeRight) / 2;
		MinMaxPair leftPair = buildTree(nodeLeft, nodeMid, node * 2);
		MinMaxPair rightPair = buildTree(nodeMid + 1, nodeRight, node * 2 + 1);
		min[node] = Min(leftPair.min, rightPair.min);
		max[node] = Max(leftPair.max, rightPair.max);

		return MinMaxPair(min[node], max[node]);
	}

	int findMinInRange(int rangeLeft, int rangeRight, int nodeLeft, int nodeRight, int node) {
		if (nodeRight < rangeLeft || rangeRight < nodeLeft) return POS_INF;

		if (rangeLeft <= nodeLeft && nodeRight <= rangeRight) return min[node];

		int nodeMid = (nodeLeft + nodeRight) / 2;
		int leftMin = findMinInRange(rangeLeft, rangeRight, nodeLeft, nodeMid, node * 2);
		int rightMin = findMinInRange(rangeLeft, rangeRight, nodeMid + 1, nodeRight, node * 2 + 1);

		return Min(leftMin, rightMin);
	}
	int findMin(int rangeLeft, int rangeRight) {
		return findMinInRange(rangeLeft, rangeRight, 0, size - 1, 1);
	}

	int findMaxInRange(int rangeLeft, int rangeRight, int nodeLeft, int nodeRight, int node) {
		if (nodeRight < rangeLeft || rangeRight < nodeLeft) return NEG_INF;

		if (rangeLeft <= nodeLeft && nodeRight <= rangeRight) return max[node];

		int nodeMid = (nodeLeft + nodeRight) / 2;
		int leftMax = findMaxInRange(rangeLeft, rangeRight, nodeLeft, nodeMid, node * 2);
		int rightMax = findMaxInRange(rangeLeft, rangeRight, nodeMid + 1, nodeRight, node * 2 + 1);

		return Max(leftMax, rightMax);
	}
	int findMax(int rangeLeft, int rangeRight) {
		return findMaxInRange(rangeLeft, rangeRight, 0, size - 1, 1);
	}
};

int main(int argc, char *argv[]) {
	//setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		int N, Q; scanf("%d %d", &N, &Q);
		for (int i = 0; i < N; i++) {
			scanf("%d", altitude + i);
		}

		SegmentTree minMaxTree(N);

		int a, b;
		for (int q = 1; q <= Q; q++) {
			scanf("%d %d", &a, &b);
			int maxAltitude = minMaxTree.findMax(a, b);
			int minAltitude = minMaxTree.findMin(a, b);
			printf("%d\n", maxAltitude - minAltitude);
		}
	}
	return 0;
}