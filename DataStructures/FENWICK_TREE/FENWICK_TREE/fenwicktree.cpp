// https://algospot.com/judge/problem/read/MEASURETIME
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define MAX_VAL 1000000

struct FenwickTree {
public:
	FenwickTree(int _size) : size(_size) {
		tree = new int[size + 10];
		for (int i = 0; i <= size; i++) tree[i] = 0;
	}
	~FenwickTree() { if (tree) delete[] tree; }

	int howManyEqualOrLessThan(int _val) {
		int idx = _val + 1; // index 1 부터 시작
		int psum = 0;
		while (idx > 0) {
			psum += tree[idx];
			idx -= (idx & -idx);
		}
		return psum;
	}
	void increaseFrequencyOf(int _freq, int _val) {
		int idx = _val + 1; // index 1 부터 시작
		while (idx <= size) {
			tree[idx] += _freq;
			idx += (idx & -idx);
		}
	}
private:
	int size;
	int *tree;
};

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);

	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		FenwickTree fenwick(MAX_VAL);

		unsigned long long swapCount = 0;
		int N; scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			int val; scanf("%d", &val);
			fenwick.increaseFrequencyOf(1, val);

			swapCount += i - fenwick.howManyEqualOrLessThan(val);
		}
		printf("%llu\n", swapCount);
	}
	return 0;
}