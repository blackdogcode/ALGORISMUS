// https://algospot.com/judge/problem/read/QUADTREE
#define _CRT_SECURE_NO_WARNINGS	
#include <cstdio>

#define MAX_N 1000
#define CNT_CHILDREN 4

enum Section {
	LEFT_UPPER, RIGHT_UPPER, 
	LEFT_DOWN, RIGHT_DOWN
};

struct Node {
public:
	Node() : isLeaf(false) {
		children = NULL;
	}
	~Node() {
		if (children != NULL)
			delete[] children;
	}

public:
	bool isLeaf;
	char key;
	Node *children;
};

class QuadTree {
public:
	QuadTree() {}
	QuadTree(char *data) {
		build(root, data);
	}
	char *build(Node &node, char *data) {
		char key = *data++;
		node.key = key;

		if (key != 'x') {
			node.isLeaf = true;
			return data;
		}
		node.children = new Node[CNT_CHILDREN];
		for (int i = 0; i < CNT_CHILDREN; i++) {
			data = build(node.children[i], data);
		}
		return data;
	}
	void printReverse() {
		reversePath(root);
		puts("");
	}
	void reversePath(Node &node) {
		printf("%c", node.key);
		if (node.isLeaf) return;
		reversePath(node.children[LEFT_DOWN]);
		reversePath(node.children[RIGHT_DOWN]);
		reversePath(node.children[LEFT_UPPER]);
		reversePath(node.children[RIGHT_UPPER]);
	}

private:
	Node root;
};

int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		char *data = new char[MAX_N + 10]; scanf("%s", data);
	
		QuadTree quadTree(data);
		quadTree.printReverse();
	}
	return 0;
}