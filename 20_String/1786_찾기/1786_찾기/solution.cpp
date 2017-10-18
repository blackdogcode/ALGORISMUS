// https://www.acmicpc.net/problem/1786
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> kmp(string &text, string &word);
vector<int> partialMatchTable(string &word);

int main(int argc, char *argv[]) {
	//setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	string text; getline(cin, text);
	string word; getline(cin, word);

	vector<int> pos = kmp(text, word);
	printf("%d\n", pos.size());
	for (int i = 0; i < pos.size(); i++)
		printf("%d ", pos[i] + 1); // 1: offset

	return 0;
}

vector<int> kmp(string &text, string &word) {
	vector<int> pi = partialMatchTable(word);
	vector<int> ret;

	int begin = 0, matched = 0;
	while (begin + word.size() <= text.size()) {
		if (matched < word.size() && text[begin + matched] == word[matched]) {
			matched++;
			if (matched == word.size()) ret.push_back(begin);
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
	return ret;
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