// https://algospot.com/judge/problem/read/BOARDCOVER
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define MAX_H 20
#define MAX_W 20

int board[4][3][2] = {
	{{0, 0}, {1, 0}, {0, 1}},
	{{0, 0}, {0, 1}, {1, 1}},
	{{0, 0}, {1, 0}, {1, 1}},
	{{0, 0}, {1, 0}, {1, -1}}
};

int H, W;
int map[MAX_H][MAX_W];

bool cover(int type, int y, int x) {
	bool canCover = true;
	for (int i = 0; i < 3; i++) {
		int dy = board[type][i][0];
		int dx = board[type][i][1];
		int ny = y + dy; 
		int nx = x + dx;

		if (ny < 0 || ny >= H || nx < 0 || nx >= W) {
			canCover = false; continue;
		}
		if ((map[ny][nx] += 1) > 1)
			canCover = false;
	}
	return canCover;
}

void uncover(int type, int y, int x) {
	for (int i = 0; i < 3; i++) {
		int dy = board[type][i][0];
		int dx = board[type][i][1];
		int ny = y + dy;
		int nx = x + dx;

		if (ny < 0 || ny >= H || nx < 0 || nx >= W) continue;

		map[ny][nx] += -1;
	}
}

int solve() {
	int y, x;
	for (y = 0; y < H; y++) {
		for (x = 0; x < W; x++) {
			if (map[y][x] == 0)
				break;
		}
		if (x != W) break;
	}
	if (y == H) return 1;

	int ret = 0;
	for (int type = 0; type < 4; type++) {
		if (cover(type, y, x))
			ret += solve();
		uncover(type, y, x);
	}
	return ret;
}

int main(int argc, char *argv[]) {
	//setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T; scanf("%d", &T);
	for (int test_case = 1; test_case <= T; test_case++) {
		int cntPoints = 0;
		scanf("%d %d\n", &H, &W);
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				char point; scanf("%c", &point);
				if (point == '#') map[y][x] = 1;
				if (point == '.') {
					map[y][x] = 0;
					cntPoints++;
				}
			}
			scanf("\n");
		}

		int ret = 0;
		if (cntPoints % 3 == 0)
			ret = solve();
		printf("%d\n", ret);
	}
	return 0;
}