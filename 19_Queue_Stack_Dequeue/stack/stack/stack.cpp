#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

struct Stack {
	int length;
	int capacity;
	int *data; // dynamic array

	Stack() : capacity(2), length(0) {
		data = new int[capacity];
	}
	~Stack() { delete[] data; }

	int top() {
		if (isEmpty()) return -1;
		return data[length-1];
	}
	int pop() {
		if (isEmpty()) return -1;
		return data[--length];
	}
	void push(int val) {
		if (isFull()) resize();
		data[length++] = val;
	}
	int size() { return length; }

	bool isEmpty() { return length == 0; }
	bool isFull() { return length == capacity; }
	
	void resize() {
		// new
		int newCapacity = capacity * 2;
		int *newData = new int[newCapacity];
		// copy
		for (int i = 0; i < length; i++)
			newData[i] = data[i];
		capacity = newCapacity;
		// release
		int *temp = data;
		data = newData;
		delete[] temp;
	}
};

int strCompare(char *str0, char *str1) {
	while (*str0 != 0 && *str1 != 0) {
		if (*str0 != *str1)
			return *str0 - *str1;
		str0++; str1++;
	}
	return *str0 - *str1;
}

int main(int argc, char *argv[]) {
	//setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	Stack stack;

	char cmd[10];
	int N; scanf("%d", &N);
	for (int n = 1; n <= N; n++) {
		scanf("%s", &cmd);
		if (strCompare(cmd, "push") == 0) {
			int val; scanf("%d", &val);
			stack.push(val);
		}
		if (strCompare(cmd, "pop") == 0) {
			int val = stack.pop();
			printf("%d\n", val);
		}
		if (strCompare(cmd, "size") == 0) {
			printf("%d\n", stack.size());
		}
		if (strCompare(cmd, "empty") == 0) {
			if (stack.isEmpty()) printf("1\n");
			else printf("0\n");
		}
		if (strCompare(cmd, "top") == 0) {
			printf("%d\n", stack.top());
		}
	}
	return 0;
}