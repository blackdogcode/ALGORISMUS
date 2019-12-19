// BFS_Graph_Search.cpp : O(V + E)
// https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1

/*This is a function problem.You only need to complete the function given below*/
/* You have to complete this function*/
/* Function to do BFS of graph
*  adj[]: array of vectors
*  vis[]: array to keep track of visited nodes
*/
void bfs(int s, vector<int> adj[], bool vis[], int N)
{
	queue<int> q;
	q.push(s);
	vis[s] = true;

	vector<int> bfs_search_order;
	bfs_search_order.push_back(s);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (register size_t i = 0; i < adj[v].size(); ++i) {
			int u = adj[v][i];
			if (vis[u] == false) {
				q.push(u);
				vis[u] = true;
				bfs_search_order.push_back(u);
			}
		}
	}
	for (register int i = 0; i < bfs_search_order.size(); ++i) {
		cout << bfs_search_order[i] << " ";
	}
}