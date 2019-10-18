//
//  AI: BFS(Breadth First Search)
//  https://www.hackerrank.com/challenges/pacman-bfs
//  Created by Sangchul, Song on 3/27/16.
//  Copyright © 2016 HYU. All rights reserved.
//
#include <iostream>
#include <queue>

using namespace std;

enum NodeType { WALL, SPACE, PACMAN, FOOD };

class Node
{
private:
    // Member Variables
    int x;
    int y;
    bool explored;
    NodeType type;
    Node* predecessor;
public:
    // Member Functions
    int getX() { return x; }
    int getY() { return y; }
    Node* getPredecessor() { return predecessor; }
    void setPredecessor(Node* newPredecessor) { predecessor = newPredecessor; }
    void setExplored() { explored = true; }
    bool isNotExplored() { return explored == false; }
    bool isNotWall() { return type != NodeType::WALL; }
    bool isFood() { return type == NodeType::FOOD; }
    bool isPacman() { return type == NodeType::PACMAN; }
    void printPosition() { cout << x << " " << y << endl; }
    
    // Constructor & Destructor
    Node() { ; } // Do nothing
    Node(int newX, int newY, char shape);
    ~Node();
};

void BFS(Node **maze, int packman_x, int packman_y, int food_x, int food_y, int row, int col);
void printPath(Node* src, Node* des);

int
main(int argc, const char* argv[])
{
    // Initialization
    int pacman_x, pacman_y;
    int food_x, food_y;
    int row, col;
    cin >> pacman_x >> pacman_y;
    cin >> food_x >> food_y;
    cin >> row >> col;
    
    // Configuration Maze[row x col]
    char shape;
    Node** maze = new Node* [row];
    for (int i = 0; i < row; i++)
    {
        maze[i] = new Node[col];
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> shape; // Wall(%), Space(-), Pacman(P), Food(.)
            maze[i][j] = Node(i, j, shape);
        }
    }
    
    // Breadth First Search: from 'pacman' to 'food'
    BFS(maze, pacman_x, pacman_y, food_x, food_y, row, col);
    
    
    return 0;
}

inline void
BFS (Node **maze, int pacman_x, int pacman_y, int food_x, int food_y, int row , int col)
{
    Node* pacman = &maze[pacman_x][pacman_y];
    Node* food = &maze[food_x][food_y];
    queue<Node*> exploredQueue; // FIFO: Explored Nodes (Discovered but, not yet Conquered)
    queue<Node*> expandedQueue; // FIFO: Expanded Nodes (Discovered and, also Conquered)
    
    pacman -> setExplored();
    exploredQueue.push(pacman);
    while (!exploredQueue.empty())
    {
        Node *node = exploredQueue.front();
        exploredQueue.pop();
        expandedQueue.push(node);
        if (node -> isFood()) // Success Condition: Food Expanded
            break;
        else
        {
            int x = node -> getX();
            int y = node -> getY();
            Node *upNode, *leftNode, *rightNode, *downNode;
            upNode = leftNode = rightNode = downNode = NULL;
            
            // Up node
            if (x - 1 >= 0)
                upNode = &maze[x - 1][y];
            // Left node
            if (y - 1 >= 0)
                leftNode = &maze[x][y - 1];
            // Right node
            if (y + 1 < col)
                rightNode = &maze[x][y + 1];
            // Down node
            if (x + 1 < row)
                downNode = &maze[x + 1][y];
            
            if (upNode -> isNotExplored() && upNode -> isNotWall())
            {
                upNode -> setPredecessor(node);
                upNode -> setExplored();
                exploredQueue.push(upNode);
            }
            if (leftNode -> isNotExplored() && leftNode -> isNotWall())
            {
                leftNode -> setPredecessor(node);
                leftNode -> setExplored();
                exploredQueue.push(leftNode);
            }
            if (rightNode -> isNotExplored() && rightNode -> isNotWall())
            {
                rightNode -> setPredecessor(node);
                rightNode -> setExplored();
                exploredQueue.push(rightNode);
            }
            if (downNode -> isNotExplored() && downNode -> isNotWall())
            {
                downNode -> setPredecessor(node);
                downNode -> setExplored();
                exploredQueue.push(downNode);
            }
        }
    }
    // Print expanded nodes during executing bfs
    Node *expandedNode;
    cout << expandedQueue.size() << endl; // # of expanded nodes
    while (!expandedQueue.empty())
    {
        expandedNode = expandedQueue.front();
        expandedNode -> printPosition();
        expandedQueue.pop();
    }
    
    // Print path from packman to food
    printPath(pacman, food);
}

// Print BFS path(guarantee optimal) from src(packman) to des(food)
void
printPath(Node* src, Node* des)
{
    static int distance = 0;
    if (des -> isPacman())
    {
        cout << distance << endl;
        des -> printPosition();
        return ;
    }
    else
    {
        distance++;
        printPath(src, des -> getPredecessor());
        des -> printPosition();
    }
}

// Constructors
Node:: Node(int newX, int newY, char shape)
{
    x = newX;
    y = newY;
    explored = false;
    predecessor = NULL;
    switch (shape)
    {
        case '%':
            type = WALL;
            break;
        case '-':
            type = SPACE;
            break;
        case 'P':
            type = PACMAN;
            break;
        case '.':
            type = FOOD;
            break;
        default:
            break;
    }
}

// Destructor
Node::~Node()
{
    delete (predecessor);
}

