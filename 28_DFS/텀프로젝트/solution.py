# https://www.acmicpc.net/problem/9466
import sys
sys.setrecursionlimit(10 ** 6)
input = sys.stdin.readline


def dfs(here, edges, visited, finished, cycle: set):
    visited[here] = True
    there = edges[here]
    if finished[there]:
        finished[here] = True
        return -1, -1
    elif visited[there] and not finished[there]:
        cycle.add(here)
        finished[here] = True
        # 자기 자신을 팀으로
        if here == there:
            return -1, -1
        else:
            return here, there
    else:
        from_here, from_there = dfs(there, edges, visited, finished, cycle)
        finished[here] = True
        if (from_here, from_there) == (-1, -1):
            return -1, -1
        elif here == from_there:
            cycle.add(here)
            return -1, -1
        else:
            cycle.add(here)
            return from_here, from_there


# test_case = int(input())
# for _ in range(test_case):
#     n = int(input())
#     edges = list(map(int, input().split()))
#     for i in range(len(edges)):
#         edges[i] -= 1
#     finished = [False] * n
#     visited = [False] * n
#
#     cycle = set()
#     for i in range(len(visited)):
#         if not visited[i]:
#             dfs(i, edges, visited, finished, cycle)
#     print(n - len(cycle))


with open('sample_input.txt') as test_input:
    test_case = int(test_input.readline())
    for _ in range(test_case):
        n = int(test_input.readline())
        edges = list(map(int, test_input.readline().split()))
        for i in range(len(edges)):
            edges[i] -= 1
        finished = [False] * n
        visited = [False] * n
        print(edges)

        cycle = set()
        for i in range(len(visited)):
            if not visited[i]:
                dfs(i, edges, visited, finished, cycle)
        print(cycle)
        print(n - len(cycle))
