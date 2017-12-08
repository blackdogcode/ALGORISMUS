// https://www.acmicpc.net/problem/4195
#define _CRT_SECURE_NO_WARNINGS
#ifndef NULL
#define NULL 0
#endif
#include <stdio.h>

#define MAX_NAME 30
#define MAX_TABLE 4096
#define MAX_PERSON 100010

void strCopy(char *str0, char *str1) {
	while (*str1 != 0)
		*str0++ = *str1++;
	*str0 = 0;
}

int strCompare(char *str0, char *str1) {
	while (*str0 != 0 && *str1 != 0) {
		if (*str0 != *str1) return (*str0 - *str1);
		str0++; str1++;
	}
	return (*str0 - *str1);
}

struct Person {
public:
	Person() : networkID(-1) {}
	Person(const Person &other) : networkID(other.networkID) { strCopy((char *)name, (char *)other.name); }
	~Person() {}
public:
	char name[MAX_NAME];
	int networkID;
};

struct Vector {
public:
	Vector() : length(0), capacity(100) { data = new Person*[capacity]; }
	Vector(int _capacity) : length(0), capacity(_capacity) { data = new Person*[capacity]; }
	~Vector() { delete[] data; }
	void push_back(Person *person) {
		if (isFull()) resize();
		data[length++] = person;
	}
	void pop_back() {
		if (isEmpty()) return;
		length--;
	}
	void resize() {
		// copy
		int _capacity = 2 * capacity;
		Person** _data = new Person*[_capacity];
		for (int i = 0; i < length; i++) _data[i] = data[i];
		// swap
		Person **temp = data;
		data = _data; capacity = _capacity;
		delete[] temp;
	}
	void init() { length = 0; }
	int size() { return length; }
	bool isEmpty() { return length == 0; }
	bool isFull() { return length == capacity; }
	Person *operator[](int idx) { return data[idx]; }
public:
	int length, capacity;
	Person **data;
};
Person persons[MAX_PERSON];

struct HashTable {
public:
	HashTable() {}
	~HashTable() {}
	void init() { for (int i = 0; i < MAX_TABLE; i++) table[i].init(); }
	unsigned long hash(char *str) {
		unsigned long hash = 5381;
		int c;
		while (c = *str++) {
			hash = (((hash << 5) + hash) + c) % MAX_TABLE;
		}
		return hash % MAX_TABLE;
	}
	Person *find(char *name)
	{
		unsigned long key = hash(name);
		for (int idx = 0; idx < table[key].size(); idx++) {
			if (strCompare(name, table[key][idx]->name) == 0)
				return table[key][idx];
		}
		return NULL;
	}
	void add(char *name, Person *person)
	{
		unsigned long key = hash(name);
		table[key].push_back(person);
	}
public:
	Vector table[MAX_TABLE];
};
HashTable hashTable;

struct DisjointSet {
public:
	DisjointSet() : length(0) {}
	~DisjointSet() {}
	void init() { length = 0; }
	void add(Person *person) {
		parent[length] = length;
		rank[length] = size[length] = 1;
		person->networkID = length;
		length++;
	}
	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
	int merge(int a, int b) {
		a = find(a); b = find(b);
		if (a == b) return size[a];

		if (rank[a] > rank[b]) swap(a, b);
		parent[a] = b;
		if (rank[a] == rank[b]) rank[b] += 1;

		return size[b] += size[a];
	}
	void swap(int &p, int &q) {
		int temp = p;
		p = q; q = temp;
	}
public:
	int length;
	int parent[MAX_PERSON];
	int rank[MAX_PERSON], size[MAX_PERSON];
};
DisjointSet socialNetwork;

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	char name[MAX_NAME]; int id[2];
	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		socialNetwork.init();
		hashTable.init();
		int cntPersons = 0;
		int link; scanf("%d", &link);
		for (int l = 0; l < link; l++) {
			for (int i = 0; i < 2; i++) {
				scanf("%s", name);
				Person *person = NULL;
				if (person = hashTable.find(name)) {
					id[i] = person->networkID;
					continue;
				}
				else {
					strCopy(persons[cntPersons].name, name);
					hashTable.add(name, &persons[cntPersons]);
					socialNetwork.add(&persons[cntPersons]);
					id[i] = persons[cntPersons].networkID;
					cntPersons++;
				}
			}
			int networkSize = socialNetwork.merge(id[0], id[1]);
			printf("%d\n", networkSize);
		}
	}
	return 0;
}