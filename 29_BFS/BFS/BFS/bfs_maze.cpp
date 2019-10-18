//
//  TYPE: BFS(Breadth First Search) : https://www.acmicpc.net/problem/2178
//  GOAL: Length of shortest path from start to destination in Maze
//  Created by Brian, Song on 06/09/16.
//  Copyright © 2016 MPPECS. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

enum NodeType { WALL, PATH };

class Node
{
private:
	// Properties
	int y;
	int x;
	Node* predecessor;
	bool discovered;
	bool explored;
	NodeType type;
public:
	// Constructor
	Node() {}
	Node(int n_y, int n_x, char shape) : y(n_y), x(n_x) {
		switch (shape) {
		case '0':
			type = NodeType(WALL);
			break;
		case '1':
			type = NodeType(PATH);
			break;
		}
		predecessor = NULL;
		discovered = explored = false;
	}
	// Methods
	int Y() { return y; }
	int X() { return x; }
	bool isDiscovered() { return discovered; }
	void setDiscovered() { discovered = true; }
	bool isExplored() { return explored; }
	void setExplored() { explored = true; }
	Node* getPredecessor() { return predecessor; }
	void setPredecessor(Node* node) { predecessor = node; }
	NodeType getType() { return type; }
	// Operator Overloading
	friend bool operator== (const Node& n1, const Node& n2) {
		return ((n1.y == n2.y) && (n1.x == n2.x));
	}
};

class Maze
{
private:
	// Properties
	const int H, W; // Height, Width [y : x = height : width]
	vector<vector<Node>> map;
public:
	// Constructor
	Maze(): H(0), W(0) {}
	Maze(int n_H, int n_w);
	// Methods
	const int Height() { return H; }
	const int Width() { return W; }
	// Operator Overloading
	vector<Node>& operator[] (const int& y) {
		return map[y];
	}
};

int BFS(Maze& maze, int s_y, int s_x, int d_y, int d_x); 

int
main(int agrc, char *argv[])
{
	// Temporary
	ifstream in("bfs_maze.txt");
	cin.rdbuf(in.rdbuf());

	int N, M; // [N X M] Matrix
	cin >> N >> M;
	Maze maze(N, M);
	int shortestPathLength;
	shortestPathLength = BFS(maze, 1, 1, N, M);
	cout << shortestPathLength << "\n";

	return 0;
}

Maze::Maze(int n_H, int n_W) : H(n_H), W(n_W) 
{
	string shape;
	map.push_back(vector<Node>(W + 1, Node())); // Zero Row for ease indexing
	for (int y = 1; y <= H; y++) {
		vector<Node> row;
		row.push_back(Node()); // Zero Column for ease indeing
		cin >> shape;
		for (int x = 1; x <= W; x++) {
			row.push_back(Node(y, x, shape[x - 1]));
		}
		map.push_back(row);
	}
}

int BFS(Maze& maze, int s_y, int s_x, int d_y, int d_x)
{
	// BFS Setting
	bool pathExist = false;
	queue<Node*> bfs_queue;
	Node* startNode = &maze[s_y][s_x];
	Node* destinationNode = &maze[d_y][d_x];
	startNode->setDiscovered();
	bfs_queue.push(startNode);

	// BFS Execution
	while (!bfs_queue.empty()) {
		Node* base = bfs_queue.front();
		bfs_queue.pop();
		base->setExplored();
		// Destination Explored
		if (*base == *destinationNode) {
			pathExist = true;
			break;
		}
		// Further Discovering
		else {
			int Y = base->Y(), X = base->X();
			int upY = Y - 1, downY = Y + 1, leftX = X - 1, rightX = X + 1;
			// #1 case: Up Node
			if (upY >= 1 && maze[upY][X].getType() == PATH && !maze[upY][X].isDiscovered()) {
				maze[upY][X].setPredecessor(base);
				maze[upY][X].setDiscovered();
				bfs_queue.push(&maze[upY][X]);
			}
			// #2 case: Down Node
			if (downY <= maze.Height() && maze[downY][X].getType() == PATH && !maze[downY][X].isDiscovered()) {
				maze[downY][X].setPredecessor(base);
				maze[downY][X].setDiscovered();
				bfs_queue.push(&maze[downY][X]);
			}
			// #3 case: Left Node
			if (leftX >= 1 && maze[Y][leftX].getType() == PATH && !maze[Y][leftX].isDiscovered()) {
				maze[Y][leftX].setPredecessor(base);
				maze[Y][leftX].setDiscovered();
				bfs_queue.push(&maze[Y][leftX]);
			}
			// #4 case: Right Node
			if (rightX <= maze.Width() && maze[Y][rightX].getType() == PATH && !maze[Y][rightX].isDiscovered()) {
				maze[Y][rightX].setPredecessor(base);
				maze[Y][rightX].setDiscovered();
				bfs_queue.push(&maze[Y][rightX]);
			}
		}
	}
	// Shortest path from 'Start' to 'Destination'
	int step;
	if (pathExist == true) {
		step = 0;
		Node* base = &maze[d_y][d_x];
		while (base != NULL) {
			step++;
			base = base->getPredecessor();
		}
	}
	else
		step = -1;

	return step;
}