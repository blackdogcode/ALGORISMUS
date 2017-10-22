// https://algospot.com/judge/problem/read/JAEHASAFE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int kmp(string text, string &word);
vector<int> partialMatchTable(string &word);

int main(int argc, char *argv[]) {
	//setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		int N; scanf("%d", &N);
		string curr; cin >> curr;
		string next;

		int minMove = 0;
		bool clockwise = true;
		for (int i = 1; i <= N; i++) {
			cin >> next;
			if (clockwise)
				minMove += kmp(next + next, curr);
			else
				minMove += kmp(curr + curr, next);
			clockwise = !clockwise;
			curr = next;
		}
		printf("%d\n", minMove);
	}

	return 0;
}

// find the first index of string matched;
int kmp(string text, string &word) {
	vector<int> pi = partialMatchTable(word);
	vector<int> ret;

	int begin = 0, matched = 0;
	while (begin + word.size() <= text.size()) {
		if (matched < word.size() && text[begin + matched] == word[matched]) {
			matched++;
			if (matched == word.size()) return begin; // first match
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return -1; // match fail
}

vector<int> partialMatchTable(string &word) {
	vector<int> pi(word.size(), 0);
	int begin = 1, matched = 0;
	while (begin + matched < word.size()) {
		if (word[begin + matched] == word[matched]) {
			matched++;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}