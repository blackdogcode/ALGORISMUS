# https://www.acmicpc.net/problem/2252
import sys
from collections import deque
sys.setrecursionlimit(10 ** 5)
input = sys.stdin.readline


def dfs(here, edges, visited, order):
    visited[here] = True
    for there in edges[here]:
        if not visited[there]:
            dfs(there, edges, visited, order)
    order.append(here)


n, m = map(int, input().split())
edges = [[] for _ in range(n)]
for _ in range(m):
    here, there = map(int, input().split())
    edges[here - 1].append(there - 1)

visited = [False] * n
general_orders = deque()
for here in range(len(visited)):
    if not visited[here]:
        partial_orders = []
        dfs(here, edges, visited, partial_orders)
        general_orders.extendleft(partial_orders)

for node in general_orders:
    print(node + 1, end=' ')


# with open('sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         n, m = map(int, test_input.readline().split())
#         edges = [[] for _ in range(n)]
#         for _ in range(m):
#             here, there = map(int, test_input.readline().split())
#             edges[here - 1].append(there - 1)
#
#         print(edges)
#
#         visited = [False] * n
#         general_orders = deque()
#         for here in range(len(visited)):
#             if not visited[here]:
#                 partial_orders = []
#                 dfs(here, edges, visited, partial_orders)
#                 general_orders.extendleft(partial_orders)
#
#         for node in general_orders:
#             print(node + 1, end=' ')
#         print()



