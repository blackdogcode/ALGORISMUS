// ACM_Craft.cpp :
// https://www.acmicpc.net/problem/1005

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int build_time[1010], visited[1010];
int edge[1010][1010];
vector<int> build_order;

void dfs(int v, int N);
long long total_build_time(int W, int N);

int main(int argc, char *argv[])
{
	cin.sync_with_stdio(false);
	ifstream in("input.txt", ifstream::in);
	cin.rdbuf(in.rdbuf());

	int T; cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		int N, K; cin >> N >> K;
		for (int i = 1; i <= N; ++i) {
			cin >> build_time[i];
			visited[i] = false;
			for (int j = 1; j <= N; ++j) {
				edge[i][j] = -1;
			}
		}

		for (int i = 0; i < K; ++i) {
			int X, Y; cin >> X >> Y;
			edge[X][Y] = 1;
		}

		int W; cin >> W;
		build_order.clear();
		for (int start = 1; start <= N; ++start) {
			if (visited[start] == false)
				dfs(start, N);
			if (find(build_order.begin(), build_order.end(), W) != build_order.end())
				break;
			else build_order.clear();
		}
		reverse(build_order.begin(), build_order.end());

		cout << total_build_time(W, N) << "\n";
	}
	return 0;
}

void dfs(int v, int N) {
	visited[v] = true;
	for (register int w = 1; w <= N; ++w) {
		if (edge[v][w] == 1 && visited[w] == false) {
			dfs(w, N);
		}
	}
	build_order.push_back(v);
}

long long total_build_time(int W, int N) {
	long long total_build_time = build_time[W]; 
	int to = W;
	while (to != build_order[0]) {
		int prevMaxTime = 0, prevMaxTower = 0;
		for (register int from = 1; from <= N; ++from) {
			if (edge[from][to] == 1 && build_time[from] > prevMaxTime) {
				prevMaxTime = build_time[from];
				prevMaxTower = from;
			}
		}
		for (int k = 0; k < build_order.size(); ++k) {
			if (build_order[k] == prevMaxTower) {
				to = build_order[k]; break;
			}
		}
		total_build_time += prevMaxTime;
	}
	return total_build_time;
}