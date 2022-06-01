# https://www.acmicpc.net/problem/11403
import sys
sys.setrecursionlimit(10 ** 5)
input = sys.stdin.readline


def dfs(here, edges, visited):
    for there in range(len(edges[here])):
        if edges[here][there] == 1 and visited[there] == -1:
            visited[there] = 1
            dfs(there, edges, visited)


# 입력 받기 그래프 구성
n = int(input())
edges = []
for _ in range(n):
    edge = list(map(int, input().split()))
    edges.append(edge)

# 각 정점을 시작 점으로 연결 되어 있는 정점을 표시
for i in range(n):
    visited = [-1] * n
    dfs(i, edges, visited)
    for j in range(n):
        # 기준 정점으로 부터 연결 되어 있다면
        if visited[j] == 1:
            edges[i][j] = 1

# 출력
for i in range(len(edges)):
    for j in range(len(edges[i])):
        print(edges[i][j], end=' ')
    print()


# with open('sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         n = int(test_input.readline())
#
#         edges = []
#         for _ in range(n):
#             edge = list(map(int, test_input.readline().split()))
#             edges.append(edge)
#
#         for i in range(len(edges)):
#             for j in range(len(edges[i])):
#                 print(edges[i][j], end=' ')
#             print()
#
#         for i in range(n):
#             visited = [-1] * n
#             dfs(i, edges, visited)
#             for j in range(n):
#                 if visited[j] == 1:
#                     edges[i][j] = 1
#         print()
#         for i in range(len(edges)):
#             for j in range(len(edges[i])):
#                 print(edges[i][j], end=' ')
#             print()
#         print()
