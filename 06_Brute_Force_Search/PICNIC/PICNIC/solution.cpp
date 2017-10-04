#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

#define MAX_N 10

using namespace std;

bool isFriends[MAX_N][MAX_N];

bool isComplete(vector<bool> &havePairs) {
	for (int i = 0; i < havePairs.size(); i++) {
		if (havePairs[i] == false) return false;
	}
	return true;
}

int countPairs(vector<bool> &havePairs, const int cntStudents) {
	if (isComplete(havePairs)) return 1;
	int first = -1;
	for (int i = 0; i < cntStudents; i++) {
		if (havePairs[i] == false) {
			first = i; break;
		}
	}
	if (first == -1) return 0;

	int ret = 0;
	for (int second = 0; second < cntStudents; second++) {
		if (havePairs[second] == false && isFriends[first][second]) {
			havePairs[first] = havePairs[second] = true;
			ret += countPairs(havePairs, cntStudents);
			havePairs[first] = havePairs[second] = false;
		}
	}
	return ret;
}

void init() {
	for (int i = 0; i < MAX_N; i++) {
		for (int j = 0; j < MAX_N; j++) {
			isFriends[i][j] = false;
		}
	}
}

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		init();
		
		int N, M; scanf("%d %d", &N, &M);
		int from, to;
		for (int m = 1; m <= M; m++) {
			scanf("%d %d", &from, &to);
			isFriends[from][to] = isFriends[to][from] = true;
		}

		vector<bool> havePairs(N, false);
		int ret = countPairs(havePairs, N);
		printf("%d\n", ret);
	}
	return 0;
}