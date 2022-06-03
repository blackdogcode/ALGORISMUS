# https://www.acmicpc.net/problem/1753
import sys, heapq, math
input = sys.stdin.readline


def dijkstra(edges, start):
    distance = [math.inf] * (len(edges))
    min_heap = []
    heapq.heapify(min_heap)

    distance[start] = 0
    heapq.heappush(min_heap, (0, start))  # length, here
    while len(min_heap) != 0:
        length, here = heapq.heappop(min_heap)
        if distance[here] < length:
            continue
        for i in range(0, len(edges[here])):
            there, weight = edges[here][i]
            next_dist = length + weight
            if next_dist < distance[there]:
                distance[there] = next_dist
                heapq.heappush(min_heap, (next_dist, there))

    return distance


# 제출용
V, E = map(int, input().split())
edges = [[] for _ in range(V + 1)]
start = int(input())
for _ in range(E):
    here, there, weight = map(int, input().split())
    edges[here].append((there, weight))

distances = dijkstra(edges, start)
for i in range(1, len(distances)):
    if math.isinf(distances[i]):
        print('INF')
    else:
        print(distances[i])

# 테스트용
# with open('sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         V, E = map(int, test_input.readline().split())
#         edges = [[] for _ in range(V + 1)]
#         start = int(test_input.readline())
#         for _ in range(E):
#             here, there, weight = map(int, test_input.readline().split())
#             edges[here].append((there, weight))
#
#         for edge in edges:
#             print(edge)
#
#         distances = dijkstra(edges, start)
#         for i in range(1, len(distances)):
#             if math.isinf(distances[i]):
#                 print('INF')
#             else:
#                 print(distances[i])

