// https://algospot.com/judge/problem/read/PALINDROMIZE
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int kmp(string &text, string &word);
vector<int> partialMatchTable(string &word);

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		string forward_word; cin >> forward_word;
		string reverse_word(forward_word);
		reverse(reverse_word.begin(), reverse_word.end());

		int maxMatched = kmp(forward_word, reverse_word);
		int paddingLen = forward_word.size() - maxMatched;
		printf("%d\n", forward_word.size() + paddingLen);
	}

	return 0;
}

int kmp(string &forward_word, string &reverse_word) {
	vector<int> pi = partialMatchTable(reverse_word);
	vector<int> ret;

	int begin = 0, matched = 0;
	while (begin + matched < forward_word.size()) {
		if (forward_word[begin + matched] == reverse_word[matched]) {
			matched++;
			if (begin + matched == forward_word.size()) return matched;
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
	return -1; // never executed
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