// https://dmoj.ca/problem/ds4
#define _CRT_SECURE_NO_WARNINGS
#ifndef NULL
#define NULL 0
#endif
#include <stdio.h>

struct Node {
	Node(int _key) : key(_key), size(1), count(1) { leftChild = rightChild = NULL; }
	~Node() { }
	int key;
	int size; // Node를 루트로 하는 트리 사이즈
	int count; // 중복 카운트
	Node *leftChild, *rightChild;
};

int getTreeSize(Node *node) {
	if (node == NULL) return 0;
	else return node->size;
}

struct BST {
	BST() : root(NULL) {}
	~BST() { }
	int searchNthKey(int nth) {
		Node *ret = searchNthNode(nth, root);
		if (ret) return ret->key;
		else return 0;
	}

	int findFirstOccurIdx(int key) {
		return firstOccurhNodeIdx(key, root);
	}
	void remove(int key) {
		Node *node = searchNode(key, root);
		if (node) root = removeNode(key, root, 1);
		else return;
	}
	void insert(int key) {
		root = insertNode(key, root);
	}
	void printSortedOrder() { displayInorderPath(root); }

	Node *searchNode(int key, Node *node) {
		if (node == NULL) return NULL;

		if (key < node->key) return searchNode(key, node->leftChild);
		else if (key > node->key) return searchNode(key, node->rightChild);
		return node;
	}
	Node *searchNthNode(int nth, Node *node) {
		if (node == NULL) return NULL;

		int leftSubTreeSize = getTreeSize(node->leftChild);
		if (nth <= leftSubTreeSize) return searchNthNode(nth, node->leftChild);
		else if (nth > leftSubTreeSize + node->count) return searchNthNode(nth - (leftSubTreeSize + node->count), node->rightChild);
		else return node;
	}

	int firstOccurhNodeIdx(int key, Node *node) {
		if (node == NULL) return -1;

		if (key < node->key) return firstOccurhNodeIdx(key, node->leftChild);
		else if (key > node->key) {
			int temp = firstOccurhNodeIdx(key, node->rightChild);
			int leftSubTreeSize = getTreeSize(node->leftChild);
			if (temp != -1) return leftSubTreeSize + node->count + temp;
			else return -1;
		}
		else {
			int leftSubTreeSize = getTreeSize(node->leftChild);
			return leftSubTreeSize + 1;
		}
	}
	Node *insertNode(int key, Node *node) {
		if (node == NULL) return new Node(key);

		if (key < node->key) {
			node->leftChild = insertNode(key, node->leftChild);
		}
		else if (key > node->key) {
			node->rightChild = insertNode(key, node->rightChild);
		}
		else node->count++;
		node->size++;
		return node;
	}

	Node *removeNode(int key, Node *node, int removeSize) {
		if (node == NULL) return NULL;

		node->size -= removeSize;
		if (key < node->key) {
			node->leftChild = removeNode(key, node->leftChild, removeSize);
		}
		else if (key > node->key) {
			node->rightChild = removeNode(key, node->rightChild, removeSize);
		}
		else {
			node->count--;
			if (node->count >= 1) return node;
			if (node->leftChild == NULL) {
				Node *temp = node->rightChild;
				delete node;
				return temp;
			}
			if (node->rightChild == NULL) {
				Node *temp = node->leftChild;
				delete node;
				return temp;
			}
			static int direct = 0;
			if (direct == 0) { // remove prev(max of left-subtree) node
				Node *prev = findMaxNode(node->leftChild);
				node->key = prev->key; node->count = prev->count;
				int tempCount = prev->count; prev->count = 0;
				node->leftChild = removeNode(prev->key, node->leftChild, tempCount);
			}
			else { // remove next(min of right-subtree) node
				Node *next = findMinNode(node->rightChild);
				node->key = next->key; node->count = next->count;
				int tempCount = next->count; next->count = 0;
				node->rightChild = removeNode(next->key, node->rightChild, tempCount);
			}
			direct = (direct + 1) % 2;
		}
		return node;
	}
	Node *findMinNode(Node *node) {
		if (node == NULL) return NULL;
		while (node->leftChild != NULL)
			node = node->leftChild;
		return node;
	}
	Node *findMaxNode(Node *node) {
		if (node == NULL) return NULL;
		while (node->rightChild != NULL)
			node = node->rightChild;
		return node;
	}
	void displayInorderPath(Node *node) {
		if (node == NULL) return;
		displayInorderPath(node->leftChild);
		for (int i = 0; i < node->count; i++)
			printf("%d ", node->key);
		displayInorderPath(node->rightChild);
	}
	Node *root;
};


int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	BST bst;

	int N, M; scanf("%d %d", &N, &M);
	for (int n = 1; n <= N; n++) {
		int val; scanf("%d", &val);
		bst.insert(val);
	}

	int lastAnswer = 0;
	for (int m = 1; m <= M; m++) {
		char cmd; int val; scanf("%c %d", &cmd, &val);
		val ^= lastAnswer;
		if (cmd == 'I') bst.insert(val);
		else if (cmd == 'R') bst.remove(val);
		else if (cmd == 'S') {
			lastAnswer = bst.searchNthKey(val);
			printf("%d\n", lastAnswer);
		}
		else if (cmd == 'L') {
			lastAnswer = bst.findFirstOccurIdx(val);
			printf("%d\n", lastAnswer);
		}
		else m--;
	}
	bst.printSortedOrder();
	return 0;
}