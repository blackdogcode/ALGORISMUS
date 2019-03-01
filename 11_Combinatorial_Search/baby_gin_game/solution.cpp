#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

#define MAX_N 10
#define CARD_N 6

int datas[MAX_N];
int cards[MAX_N];

void displayCards(int *arr) {
	for (int i = 0; i < CARD_N; ++i) {
		cout << arr[i];
	}
	cout << "\n";
}
bool isRun(int *arr);
bool isTriplet(int *arr);
int countBits(int val);
int isBabyGin(int *arr);
int solve(int cnt, int selected);


int main(int argc, char *argv[]) {
	freopen("sample_input.txt", "r", stdin);
	cin.sync_with_stdio(false);

	int T; cin >> T; getchar();
	for (int test_case = 1; test_case <= T; ++test_case) {
		for (int i = 0; i < CARD_N; ++i) {
			datas[i] = getchar() - '0';
		}
		getchar();
		//displayCards(datas);
		//cout << isBabyGin(cards) << "\n";
		cout << solve(0, 0) << "\n";
	}
	return 0;
}

int countBits(int val) {
	return 0;
}

int solve(int cnt, int selected) {
	if (cnt == CARD_N) return isBabyGin(cards);
	for (register int i = 0; i < CARD_N; ++i) {
		if (!(selected & (1 << i))) {
			cards[cnt] = datas[i];
			if (solve(cnt + 1, selected | (1 << i))) return 1;
		}
	}
	return 0;
}

int isBabyGin(int *arr) {
	if (!isRun(arr + 0) && !isTriplet(arr + 0)) return 0;
	if (!isRun(arr + 3) && !isTriplet(arr + 3)) return 0;
	return 1;
}

bool isRun(int *arr) {
	if (arr[0] != arr[1] || arr[1] != arr[2]) return false;
	else return true;
}

bool isTriplet(int *arr) {
	if (arr[0] != arr[1]-1 || arr[1]+1 != arr[2]) return false;
	else return true;
}
