// https://www.acmicpc.net/problem/11403
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>

struct Stack {
public:
	Stack() : size(0) {}
	~Stack() {}
	void init() { size = 0; }
	void push(int val) { data[size++] = val; }
	void pop() {
		if (isEmpty()) return;
		--size;
	}
	int top() {
		if (isEmpty()) return -1;
		return data[size - 1];
	}
	bool isEmpty() { return size == 0; }
public:
	int size;
	int data[10010];
};
Stack stack;


#define MAX_N 110
int edge[MAX_N][MAX_N];

int visited[MAX_N];
void dfs(int src, int V) {
	for (register int v = 0; v < V; ++v) visited[v] = 0;

	Stack stack; stack.init();
	for (register int next = 0; next < V; ++next) {
		if (edge[src][next] == 1 && visited[next] == 0)
			stack.push(next);
	}
	while (!stack.isEmpty()) {
		int node = stack.top();
		stack.pop();

		visited[node] = 1;
		for (register int next = 0; next < V; ++next) {
			if (edge[node][next] == 1 && visited[next] == 0)
				stack.push(next);
		}
	}
}

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int N; scanf("%d", &N);
	for (register int from = 0; from < N; ++from)
		for (register int to = 0; to < N; ++to)
			scanf("%d", &edge[from][to]);

	for (register int from = 0; from < N; ++from) {
		dfs(from, N);
		for (register int to = 0; to < N; ++to) {
			printf("%d ", visited[to]);
		}
		puts("");
	}
	return 0;
}