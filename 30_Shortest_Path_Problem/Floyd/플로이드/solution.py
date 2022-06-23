# https://www.acmicpc.net/problem/11404
import sys, math
input = sys.stdin.readline


def floyd(edges: list):
    """
    :param edges: n x n 그래프 인접 행렬
    :return: 모든 쌍의 최소 거리 행렬
    """
    # 자기 자신으로 가는 최소 거리는 0
    for i in range(1, len(edges)):
        edges[i][i] = 0
    # 모든 쌍 최소 거리 구하기
    for k in range(1, len(edges)):
        for i in range(1, len(edges)):
            for j in range(1, len(edges)):
                edges[i][j] = min(edges[i][j], edges[i][k] + edges[k][j])


n = int(input())
m = int(input())

edges = [[math.inf] * (n + 1) for _ in range(n + 1)]
for _ in range(m):
    here, there, weight = map(int, input().split())
    edges[here][there] = min(weight, edges[here][there])

floyd(edges)

for i in range(1, n + 1):
    for j in range(1, n + 1):
        if edges[i][j] == math.inf:
            edges[i][j] = 0
        print(edges[i][j], end=' ')
    print()


# 테스트용
# with open('sample_input.txt') as test_input:
#     n = int(test_input.readline())
#     m = int(test_input.readline())
#
#     edges = [[math.inf] * (n + 1) for _ in range(n + 1)]
#     for _ in range(m):
#         here, there, weight = map(int, test_input.readline().split())
#         edges[here][there] = min(weight, edges[here][there])
#
#     for i in range(1, n + 1):
#         for j in range(1, n + 1):
#             print(edges[i][j], end=' ')
#         print()
#
#     print()
#     floyd(edges)
#
#     for i in range(1, n + 1):
#         for j in range(1, n + 1):
#             print(edges[i][j], end=' ')
#         print()
#     print()
