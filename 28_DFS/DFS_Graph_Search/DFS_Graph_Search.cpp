// DFS_Graph_Search.cpp : O(V + E)
//

/*This is a function problem.You only need to complete the function given below*/
/* Function to do DFS of graph
*  g[]: array of vectors to represent graph
*  vis[]: array to keep track of visited vertex
*/
void dfs(int s, vector<int> g[], bool vis[])
{
	if (vis[s] == true) return;
	cout << s << " ";

	vis[s] = true;
	for (register int i = 0; i < g[s].size(); ++i) {
		int v = g[s][i];
		if (vis[v] == false) {
			dfs(v, g, vis);
		}
	}
}
