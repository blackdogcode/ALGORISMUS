// 2SUM.cpp : 
//

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream in("2sum.txt", ifstream::in);
	if (!in.is_open()) {
		cerr << "Error: 2sum.txt not found!" << endl;
		return -1;
	}
	// Exact Output: 427
	return 0;
}
