// BFS_Graph_Search.cpp : O(V + E)
// https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

vector<int> bfs(int start, vector<vector<int>> &adj);

int main()
{
	cin.sync_with_stdio(false);
	ifstream in("input.txt", ifstream::in);
	cin.rdbuf(in.rdbuf());

	int test_case; cin >> test_case;
	for (register int t = 0; t < test_case; ++t) {
		int V; cin >> V;
		int E; cin >> E;
		vector<vector<int>> adj;
		for (register int v = 0; v < V; ++v) {
			adj.push_back(vector<int>(0));
		}
		for (register int e = 0; e < E; ++e) {
			int from, to; cin >> from >> to;
			adj[from].push_back(to);
		}
		vector<int> order = bfs(0, adj);
		for (register size_t i = 0; i < order.size(); ++i) {
			cout << order[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}

vector<int> bfs(int start, vector<vector<int>> &adj) {
	vector<int> bfs_search_order;
	vector<bool> discovered(adj.size(), false);

	queue<int> q;
	q.push(start);
	discovered[start] = true;
	bfs_search_order.push_back(start);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (register size_t i = 0; i < adj[v].size(); ++i) {
			int w = adj[v][i];
			if (discovered[w] == false) {
				q.push(w);
				discovered[w] = true;
				bfs_search_order.push_back(w);
			}
		}
	}
	return bfs_search_order;
}