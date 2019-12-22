// https://www.coursera.org/learn/algorithms-graphs-data-structures/exam/Ij5au/programming-assignment-2/attempt
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const int CNT_V = 201;
const int INF = 1000000;
vector<int> ret { 7, 37, 59, 82, 99, 115, 133, 165, 188, 197 };


vector<pair<int, int>> edge[CNT_V];
vector<int> dijkstra(int src);

int main(int argc, char *argv[])
{
	ifstream in("dijkstraData.txt", ifstream::in);
	if (!in.is_open()) {
		cerr << "Error: dijkstraData.txt not found!";
		return -1;
	}

	while (!in.eof()) {
		string line;
		getline(in, line);
		stringstream strStream(line);
		int v; strStream >> v;
		while (!strStream.eof()) {
			int w, cost; strStream >> w >> cost;
			edge[v].push_back(make_pair(w, cost));
		}
	}
	// Exact Output: 2599,2610,2947,2052,2367,2399,2029,2442,2505,3068
	vector<int> dist = dijkstra(1);
	for (int i = 0; i < ret.size(); ++i) {
		cout << dist[ret[i]] << ",";
	}
	return 0;
}

vector<int> dijkstra(int src) {
	vector<int> dist(CNT_V, INF);
	dist[src] = 0;
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost) continue;

		for (int i = 0; i < edge[here].size(); ++i) {
			int there = edge[here][i].first;
			int nextDist = cost + edge[here][i].second;

			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}