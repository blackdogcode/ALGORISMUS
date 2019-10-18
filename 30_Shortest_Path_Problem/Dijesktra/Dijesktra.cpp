#include <iostream>
#include <vector>
#include <queue>

#define MAX_V 100
#define INF 123456789

using namespace std;

int V; // 정점 개수

vector<pair<int, int>> adj[MAX_V];
vector<int> dijkstra(int src);

int main()
{
    std::cout << "Hello World!\n";
}

vector<int> dijkstra(int src) {
	vector<int> dist(V, INF);
	dist[src] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;

			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}