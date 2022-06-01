# https://www.acmicpc.net/problem/11724
import sys
sys.setrecursionlimit(10 ** 5)
input = sys.stdin.readline


def display_edges(edges):
    for i in range(len(edges)):
        for j in range(len(edges[i])):
            print(edges[i][j], end=' ')
        print()
    print()


def dfs(here, edges, visited):
    for there in range(len(edges[here])):
        if edges[here][there] == 1 and not visited[there]:
            visited[there] = True
            dfs(there, edges, visited)


n, m = map(int, input().split())
edges = [[0] * n for _ in range(n)]

for _ in range(m):
    here, there = map(int, input().split())
    edges[here - 1][there - 1] = 1
    edges[there - 1][here - 1] = 1
visited = [False] * n

connected_components = 0
for i in range(len(edges)):
    if not visited[i]:
        dfs(i, edges, visited)
        connected_components += 1
print(connected_components)


# with open('sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         n, m = map(int, test_input.readline().split())
#         edges = [[0] * n for _ in range(n)]
#
#         for _ in range(m):
#             here, there = map(int, test_input.readline().split())
#             edges[here - 1][there - 1] = 1
#             edges[there - 1][here - 1] = 1
#         display_edges(edges)
#         visited = [False] * n
#
#         connected_components = 0
#         for i in range(len(edges)):
#             if not visited[i]:
#                 dfs(i, edges, visited)
#                 connected_components += 1
#         print(connected_components)






