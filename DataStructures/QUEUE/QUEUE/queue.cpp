#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 110
#define MAX_M 110
int N, M;
int maze[MAX_N][MAX_M];
int dy[4] = { -1, +0, +1, +0 };
int dx[4] = { +0, +1, +0, -1 };

struct Node {
public:
	Node() {}
	Node(int _y, int _x, int _cost) : y(_y), x(_x), cost(_cost) {}
	Node(const Node &node) : y(node.y), x(node.x), cost(node.cost) {}
	~Node() {}
public:
	int y, x;
	int cost;
};

struct Queue {
public:
	Queue() : capacity(10010), begin(0), end(0) { data = new Node[capacity]; }
	~Queue() {}
	void push_back(Node val) {
		data[end++] = val;
		if (end == capacity) end = 0;
	}
	void pop_back() {
		begin++;
		if (begin == capacity) begin = 0;
	}
	void init() { begin = end = 0; }
	Node& front() { return data[begin]; }
	bool isEmpty() { return begin == end; }
public:
	int begin, end;
	int capacity;
	Node *data;
};
Queue queue;

bool canMove(int y, int x) {
	if (y < 1 || y > N) return false;
	if (x < 1 || x > M) return false;
	if (maze[y][x] == 0) return false;
	return true;
}

int dist[MAX_N][MAX_M];
bool discovered[MAX_N][MAX_M];
int bfs(int srcY, int srcX, int desY, int desX) {
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			discovered[y][x] = false;
			dist[y][x] = 0;
		}
	}
	discovered[srcY][srcX] = true;

	queue.init();
	queue.push_back(Node(srcY, srcX, 1));
	while (!queue.isEmpty()) {
		int nodeY = queue.front().y;
		int nodeX = queue.front().x;
		int nodeCost = queue.front().cost;
		queue.pop_back();

		for (int direct = 0; direct < 4; direct++) {
			int nextY = nodeY + dy[direct];
			int nextX = nodeX + dx[direct];
			int nextCost = nodeCost + 1;
			if (canMove(nextY, nextX) && !discovered[nextY][nextX]) {
				discovered[nextY][nextX] = true;
				dist[nextY][nextX] = nextCost;
				queue.push_back(Node(nextY, nextX, nextCost));
			}
		}
	}
	return dist[desY][desX];
}

void initMap(int row, char *input) {
	for (int col = 1; col <= M; col++)
		maze[row][col] = input[col - 1] - '0';
}

int main(int argc, char *argv[]) {
	//freopen("sample_input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	char input[MAX_M]; scanf("%d %d", &N, &M);
	for (int row = 1; row <= N; row++) {
		scanf("%s", input);
		initMap(row, input);
	}
	int minDist = bfs(1, 1, N, M);
	printf("%d\n", minDist);

	return 0;
}