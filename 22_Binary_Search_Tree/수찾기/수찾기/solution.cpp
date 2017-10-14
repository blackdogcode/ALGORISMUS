// https://www.acmicpc.net/problem/1920
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> numbers(100000 + 10);

bool binary_search(int key, int first, int last) {
	int mid;
	while (first <= last) {
		mid = (first + last) / 2;
		if (numbers[mid] == key) return true;

		if (numbers[mid] > key) last = mid - 1;
		else first = mid + 1;
	}
	return false;
}

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int N; scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &numbers[i]);
	}
	
	sort(numbers.begin(), numbers.begin() + N);

	int M; scanf("%d", &M);
	for (int m = 0; m < M; m++) {
		int key; scanf("%d", &key);
		if (binary_search(key, 0, N - 1))
			printf("1\n");
		else
			printf("0\n");
	}
	return 0;
}