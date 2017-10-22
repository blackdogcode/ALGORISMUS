// https://www.acmicpc.net/problem/1620
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

#define MAX_N 100010
#define MAX_LENGTH 30
char *pokemons[MAX_N];

struct Node {
	Node() { leftChild = rightChild = NULL; }
	Node(int _pokemonNumber, string &_key) : pokemonNumber(_pokemonNumber), key(_key) {
		leftChild = rightChild = NULL;
	}

	int pokemonNumber;
	string key;
	Node *leftChild;
	Node *rightChild;
};

// binary search tree
class PokemonTree {
public:
	PokemonTree() { root = NULL; }

	int findPokemonNumber(char *pokemonName) {
		string key(pokemonName);
		Node* node = findNode(root, key);
		if (node == NULL) return -1;
		else return node->pokemonNumber;
	}
	void insertPokemon(int pokemonNumber, char *pokemonName) {
		string newKey(pokemonName);
		root = insertNode(root, pokemonNumber, newKey);
	}
	void deletePokemon(char *pokemonName) {
		string key(pokemonName);
		root = deleteNode(root, key);
	}

	void displayTree() {
		printInorderPath(root);
	}
private:
	Node *findNode(Node *root, string &key) {
		if (root == NULL) return NULL;

		int comparor = key.compare(root->key);
		if (comparor == 0) // sucess
			return root;
		if (comparor < 0)
			return findNode(root->leftChild, key);
		else
			return findNode(root->rightChild, key);
	}
	Node *insertNode(Node *root, int pokemonNumber, string &newKey) {
		if (root == NULL) {
			root = new Node(pokemonNumber, newKey);
			return root;
		}

		int comparor = newKey.compare(root->key);
		if (comparor == 0) // already exist
			return root;
		if (comparor < 0)
			root->leftChild = insertNode(root->leftChild, pokemonNumber, newKey);
		else
			root->rightChild = insertNode(root->rightChild, pokemonNumber, newKey);

		return root;
	}
	Node *deleteNode(Node *root, string &key) {
		if (root == NULL) return NULL;

		int comparor = key.compare(root->key);
		if (comparor < 0)
			root->leftChild = deleteNode(root->leftChild, key);
		else if (comparor > 0)
			root->rightChild = deleteNode(root->rightChild, key);
		else {
			if (root->leftChild == NULL)
				return root->rightChild;
			if (root->rightChild == NULL)
				return root->leftChild;

			static bool deleteLeft = true; // for balanced tree
			if (deleteLeft) {
				Node *node = maxNode(root->leftChild);
				swapNode(root, node);
				root->leftChild = deleteNode(root->leftChild, key);
			}
			else {
				Node *node = minNode(root->rightChild);
				swapNode(root, node);
				root->rightChild = deleteNode(root->rightChild, key);
			}
			deleteLeft = !deleteLeft;

		}
		return root;
	}
	Node *minNode(Node *node) {
		while (node->leftChild != NULL)
			node = node->leftChild;
		return node;
	}
	Node *maxNode(Node *node) {
		while (node->rightChild != NULL)
			node = node->rightChild;
		return node;
	}
	void swapNode(Node *node0, Node *node1) {
		string tmpKey(node0->key);
		node0->key = node1->key;
		node1->key = tmpKey;

		int tmpNumber = node0->pokemonNumber;
		node0->pokemonNumber = node1->pokemonNumber;
		node1->pokemonNumber = tmpNumber;
	}

	void printInorderPath(Node *root) {
		if (root == NULL) return;

		cout << root->key << endl;
		printInorderPath(root->leftChild);
		printInorderPath(root->rightChild);
	}
	Node *root;
};

int min(int a, int b) { if (a <= b) return a; else return b; }
int main(int argc, char *argv[]) {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	PokemonTree pokemonTree;

	// insert
	int N, M; cin >> N >> M;
	for (int i = 1; i <= N; i++)
		pokemons[i] = (char *)malloc(MAX_LENGTH * sizeof(char));
	for (int i = 1; i <= N; i++) {
		scanf("%s", pokemons[i]);
		pokemonTree.insertPokemon(i, pokemons[i]);
	}

	// delete: 삭제 검증을 위한 테스트(문제 요구사항 X)
	for (int q = 1; q <= 5; q++) {
		int i = rand() % N + 1;
		pokemonTree.deletePokemon(pokemons[i]);
		pokemonTree.insertPokemon(i, pokemons[i]);
	}

	// find
	char query[MAX_LENGTH];
	for (int m = 1; m <= M; m++) {
		scanf("%s", query);
		if (query[0] >= '1' && query[0] <= '9') {
			int number = stoi(query);
			printf("%s\n", pokemons[number]);
		}
		else {
			printf("%d\n", pokemonTree.findPokemonNumber(query));
		}
	}

	return 0;
}