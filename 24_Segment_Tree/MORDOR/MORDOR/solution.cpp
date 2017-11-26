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
	MinMaxPair() {}
	MinMaxPair(int _min, int _max) : min(_min), max(_max) {}

	int min, max;
};

struct SegmentTree {
public:
	SegmentTree() {}
	SegmentTree(int _size) : size(_size), minMaxNode(_size * 4) {
		buildTree(0, size-1, 1);
	}

	MinMaxPair findMinMax(int rangeLeft, int rangeRight) {
		return findMinMaxInRange(rangeLeft, rangeRight, 0, size - 1, 1);
	}
private:
	MinMaxPair buildTree(int nodeLeft, int nodeRight, int node) {
		if (nodeLeft == nodeRight)
			return minMaxNode[node] = MinMaxPair(altitude[nodeLeft], altitude[nodeRight]);

		int nodeMid = (nodeLeft + nodeRight) / 2;
		MinMaxPair leftMinMax = buildTree(nodeLeft, nodeMid, node * 2);
		MinMaxPair rightMinMax = buildTree(nodeMid + 1, nodeRight, node * 2 + 1);
		int minAltitude = Min(leftMinMax.min, rightMinMax.min);
		int maxAltitude = Max(leftMinMax.max, rightMinMax.max);

		return minMaxNode[node] = MinMaxPair(minAltitude, maxAltitude);
	}

	MinMaxPair findMinMaxInRange(int rangeLeft, int rangeRight, int nodeLeft, int nodeRight, int node) {
		if (nodeRight < rangeLeft || rangeRight < nodeLeft)
			return MinMaxPair(POS_INF, NEG_INF);

		if (rangeLeft <= nodeLeft && nodeRight <= rangeRight) return minMaxNode[node];

		int nodeMid = (nodeLeft + nodeRight) / 2;
		MinMaxPair leftMinMax = findMinMaxInRange(rangeLeft, rangeRight, nodeLeft, nodeMid, node * 2);
		MinMaxPair rightMinMax = findMinMaxInRange(rangeLeft, rangeRight, nodeMid + 1, nodeRight, node * 2 + 1);
		int minAltitude = Min(leftMinMax.min, rightMinMax.min);
		int maxAltitude = Max(leftMinMax.max, rightMinMax.max);

		return MinMaxPair(minAltitude, maxAltitude);
	}

	vector<MinMaxPair> minMaxNode;
	int size;
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
			MinMaxPair minMaxAltitude = minMaxTree.findMinMax(a, b);
			int maxAltitude = minMaxAltitude.max;
			int minAltitude = minMaxAltitude.min;
			printf("%d\n", maxAltitude - minAltitude);
		}
	}
	return 0;
}