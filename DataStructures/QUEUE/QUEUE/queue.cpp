// https://www.acmicpc.net/problem/10845
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

#define MAX_N 100010
struct Queue {
public:
	Queue() : capacity(MAX_N) { 
		begin = end = 0;
		data = new int[capacity]; // 큐가 다 차지 않도록, 반드시 사이즈를 예상 입력 크기보다 더 크게 잡아준다
	}
	~Queue() { if (data) delete[] data; }

	void push_back(int _val) {
		data[end] = _val;
		if (++end == capacity) end = 0;
	}
	void pop_front() {
		if (isEmpty()) return;
		if (++begin == capacity) begin = 0;
	}
	int front() {
		if (isEmpty()) return -1;
		return data[begin];
	}
	int back() {
		if (isEmpty()) return -1;
		int last = end - 1;
		if (last == -1) last = capacity - 1;
		return data[last];
	}
	int size() {
		if (isEmpty()) return 0;
		int length = 0, iter = begin;
		while (iter != end) {
			length++; iter++;
			if (iter == capacity) iter = 0;
		}
		return length;
	}
	bool isEmpty() { return begin == end; }
private:
	int begin, end;
	int capacity;
	int *data;
};

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	setbuf(stdout, NULL);

	Queue queue;

	int N; scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		char cmd[100]; scanf("%s", cmd);
		if (strcmp(cmd, "push") == 0) {
			int val; scanf("%d", &val);
			queue.push_back(val);
		}
		else if (strcmp(cmd, "pop") == 0) {
			printf("%d\n", queue.front());
			queue.pop_front();
		}
		else if (strcmp(cmd, "front") == 0) {
			printf("%d\n", queue.front());
		}
		else if (strcmp(cmd, "back") == 0) {
			printf("%d\n", queue.back());
		}
		else if (strcmp(cmd, "size") == 0) {
			printf("%d\n", queue.size());
		}
		else if (strcmp(cmd, "empty") == 0) {
			if (queue.isEmpty()) printf("%d\n", 1);
			else printf("%d\n", 0);
		}
		else printf("INVALID COMMAND: %s\n", cmd);
	}
	return 0;
}