// SCC.cpp : tarjanSCC - O(V + E)
// https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
// Configuration: stack memory size = 32MB, because size of large graph
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int vertexSize = 875714;
const int maxSccSize = 5;

vector<vector<int>> edge(vertexSize);
// 각 정점의 컴포너는 번호, 컴포터는 번호는 0부터 시작하며,
// 같은 강결합 컴포넌트에 속한 정점들의 컴포너는 번호는 같다.
vector<int> sccID;
// 각 정점 발견 순서
vector<int> discovered;
// 정점의 번호를 담는 스택
stack<int> stk;
int sccCounter, vertextCounter;
// here를 루트로 하는 서브트리에서 역방향 간선이나 교차 간선을
// 통해 갈 수 있는 정점 중 최소 발견 순서를 반환한다.
// (이미 SCC로 묶인 정점으로 연결된 교차간선은 무시한다)
int scc(int here);
// tarjan SCC 알고리즘
void tarjanSCC();

int main(int argc, char *argv[])
{
   ifstream in("SCC.txt", ifstream::in);
   if (!in.is_open()) {
      cerr << "Error: SCC.txt not found!" << endl;
      return -1;
   }
   while (!in.eof()) {
      int from, to; in >> from >> to;
      edge[from - 1].push_back(to - 1);
   }
   
   tarjanSCC();

   vector<int> sccSize(vertexSize, 0);
   sort(sccID.begin(), sccID.end());
   int i = 0;
   while (i < sccID.size()) {
      int count = 0; int id = sccID[i];
      while (i < sccID.size() && sccID[i] == id) {
         ++count; ++i;
      }
      sccSize[id] = count;
   }

   sort(sccSize.begin(), sccSize.end());
   reverse(sccSize.begin(), sccSize.end());
   for (int i = 0; i < maxSccSize; ++i) {
      cout << sccSize[i] << " ";
   }
   return 0;
}

int scc(int here) {
   int ret = discovered[here] = vertextCounter++;
   // 스택에 here를 넣는다. here의 후손들은 모두 스택에서 here 후에 들어간다.
   stk.push(here);
   for (int i = 0; i < edge[here].size(); ++i) {
      int there = edge[here][i];
      // (here, there)가 트리 간선인 경우
      if (discovered[there] == -1)
         ret = min(ret, scc(there));
      // there가 무시해야 하는 교차 간선이 아니라면
      else if (sccID[there] == -1)
         ret = min(ret, discovered[there]);
   }
   // here에서 부모로 올라가는 간선을 끊어야 할지 확인한다.
   if (ret == discovered[here]) {
      // here를 루트로 하는 서브트리에 남아 있는 정점들을 전부 하나의 컴포넌트로 묶는다.
      while (true) {
         int t = stk.top();
         stk.pop();
         sccID[t] = sccCounter;
         if (t == here) break;
      }
      ++sccCounter;
   }
   return ret;
}

void tarjanSCC() {
   // 배열 초기화
   sccID = discovered = vector<int>(edge.size(), -1);
   // 카운터 초기화
   sccCounter = vertextCounter = 0;
   // 모든 정점에 대해 scc() 호출
   for (int i = 0; i < edge.size(); ++i) 
      if (discovered[i] == -1) scc(i);
   return;
}