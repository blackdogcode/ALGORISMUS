// https://www.acmicpc.net/problem/10828
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

struct Vector {
public:
	Vector() : length(0), capacity(100) { data = new int[capacity]; }
	~Vector() { if (data) delete[] data; }

	void push_back(int _val) {
		if (isFull()) resize();
		data[length++] = _val;
	}
	void pop_back() {
		if (isEmpty()) return;
		else length--;
	}
	int back() {
		if (isEmpty()) return -1;
		else return data[length - 1];
	}
	int front() {
		if (isEmpty()) return -1;
		else return data[0];
	}
	void resize() {
		// copy
		int _capacity = capacity * 2;
		int *_data = new int[_capacity];
		for (int i = 0; i < length; i++) _data[i] = data[i];
		// swap
		int *temp = data;
		data = _data; capacity = _capacity;
		delete[] temp;
	}
	int size() { return length; }
	bool isEmpty() { return length == 0; }
	bool isFull() { return length == capacity; }
private:
	int length, capacity;
	int *data;
};

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	Vector stack;

	int N; scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		char cmd[100]; scanf("%s", cmd);
		if (strcmp(cmd, "push") == 0) {
			int val; scanf("%d", &val);
			stack.push_back(val);
		}
		else if (strcmp(cmd, "pop") == 0) {
			printf("%d\n", stack.back());
			stack.pop_back();
		}
		else if (strcmp(cmd, "size") == 0) {
			printf("%d\n", stack.size());
		}
		else if (strcmp(cmd, "empty") == 0) {
			if (stack.isEmpty()) printf("1\n");
			else printf("0\n");
		}
		else if (strcmp(cmd, "top") == 0) {
			printf("%d\n", stack.back());
		}
		else printf("INVALID COMMAND: %s\n", cmd);
	}
	return 0;
}