// https://algospot.com/judge/problem/read/SOLONG
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>

int strLength(char *str) {
	int length = 0;
	while (*str != 0) {
		++str; ++length;
	}
	return length;
}

int strCompare(char *str0, char *str1) {
	while (*str0 != 0 && *str1 != 0) {
		if (*str0 != *str1) return (*str0 - *str1);
		str0++; str1++;
	}
	return (*str0 - *str1);
}

#define MAX_WORD 10010
#define MAX_TEXT 15
struct Word {
public:
	friend bool operator >= (const Word &left, const Word &right) {
		if (left.count > right.count) return true;
		else if (left.count < right.count) return false;
		else return strCompare((char*)left.text, (char*)right.text) <= 0;
	}
public:
	char text[MAX_TEXT];
	int count;
};
Word words[MAX_WORD];
Word *ptrWords[MAX_WORD];

void merge_sort(int p, int r);
void merge(int p, int q, int r, int s);

#define CNT_ALPHABET 26
int toIndex(char c) { return c - 'A'; }
struct TrieNode {
	TrieNode() : isTerminal(false), recommend(-1) { for (int i = 0; i < CNT_ALPHABET; i++) children[i] = NULL; }
	~TrieNode() { for (int i = 0; i < CNT_ALPHABET; i++) if (children[i]) delete children[i]; }
	void insertWord(char *remains, int wordIdx) {
		if (recommend == -1) recommend = wordIdx;
		if (*remains == 0) {
			isTerminal = true; return;
		}

		int idx = toIndex(*remains);
		if (children[idx] == NULL) children[idx] = new TrieNode();
		children[idx]->insertWord(remains + 1, wordIdx);
	}
	int findWord(char *remains) {
		if (*remains == 0) {
			if (isTerminal) return recommend;
			else return -1; // 단어 사전에 등록 X
		}

		int idx = toIndex(*remains);
		if (children[idx] == NULL) return -1; // 단어 사전에 등록 X
		else return children[idx]->findWord(remains + 1);
	}
	int typeToComplete(char *input, int wordIdx) {
		if (*input == 0) return 0;
		if (wordIdx == recommend) return 1;

		int idx = toIndex(*input);
		return 1 + children[idx]->typeToComplete(input + 1, wordIdx);
	}
	int howManyType(char *input) {
		int wordIdx = findWord(input);
		if (wordIdx == -1) return strLength(input);
		if (strCompare(ptrWords[wordIdx]->text, input) != 0) return strLength(input);

		return typeToComplete(input, wordIdx);
	}
public:
	bool isTerminal;
	int recommend;
	TrieNode *children[CNT_ALPHABET];
};
int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N, M; scanf("%d %d", &N, &M);
		for (register int i = 0; i < N; ++i) {
			scanf("%s %d", words[i].text, &words[i].count);
			ptrWords[i] = &words[i];
		}

		merge_sort(0, N - 1);

		TrieNode *trie = new TrieNode();
		for (register int i = 0; i < N; ++i)
			trie->insertWord(ptrWords[i]->text, i);	
		trie->recommend = -1;

		char text[MAX_TEXT]; int totalType = 0;
		for (register int i = 0; i < M; ++i) {
			scanf("%s", text);
			totalType += trie->howManyType(text);
		}
		totalType += M - 1; // 공백 문자 개수 추가
		printf("%d\n", totalType);
		delete trie;
	}
	return 0;
}

void merge_sort(int p, int r) {
	if (p >= r) return;

	int q = (p + r) / 2;
	merge_sort(p, q);
	merge_sort(q + 1, r);
	merge(p, q, q + 1, r);
}

void merge(int p, int q, int r, int s) {
	// copy
	Word **leftWord = new Word*[q - p + 2];
	Word **rightWord = new Word*[s - r + 2];
	int i, j;
	for (i = 0; i <= q - p; ++i) 
		leftWord[i] = ptrWords[p + i];
	leftWord[i] = NULL;
	for (j = 0; j <= s - r; ++j) 
		rightWord[j] = ptrWords[r + j];
	rightWord[j] = NULL;
	// sort
	i = j = 0;
	for (register int k = p; k <= s; ++k) {
		if (leftWord[i] == NULL)
			ptrWords[k] = rightWord[j++];
		else if (rightWord[j] == NULL)
			ptrWords[k] = leftWord[i++];
		else if (*leftWord[i] >= *rightWord[j])
			ptrWords[k] = leftWord[i++];
		else ptrWords[k] = rightWord[j++];
	}
	// release
	delete[] leftWord;
	delete[] rightWord;
}