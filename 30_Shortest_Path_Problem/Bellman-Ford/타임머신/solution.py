# https://www.acmicpc.net/problem/11657
import sys, math
input = sys.stdin.readline

offset = 123456789

def bellman_ford(start: int, size_v: int, edges: list):
    upper = [math.inf] * (size_v + 1)
    upper[start] = 0
    updated = True

    # v번 완화를 반복한다
    for v in range(1, size_v + 1):
        updated = False
        for here in range(1, size_v + 1):
            for edge in edges[here]:
                weight, there = edge
                # 간선을 따라 완화를 시도한다
                if upper[here] + weight < upper[there]:
                    upper[there] = upper[here] + weight
                    updated = True
        # 더 이상 간선 완화가 이루어지지 않으면 더이상 시도해볼 필요가 없음
        if not updated:
            break
    # v번 수행해도 완화가 성공 했다면 음수 사이클이 존재
    else:
        upper.clear()
    return upper


# 제출용
size_v, size_e = map(int, input().split())
edges = [[] for _ in range(size_v + 1)]
for _ in range(size_e):
    here, there, weight = map(int, input().split())
    edges[here].append((weight, there))

distances = bellman_ford(1, size_v, edges)
if distances == []:
    print(-1)
else:
    for i in range(2, size_v + 1):
        # 시작 점으로 부터 경로가 존재하지 않을 때
        if distances[i] < math.inf - offset:
            print(distances[i])
        else:
            print(-1)


# 테스트 용
# with open('sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         size_v, size_e = map(int, test_input.readline().split())
#         edges = [[] for _ in range(size_v + 1)]
#         for _ in range(size_e):
#             here, there, weight = map(int, test_input.readline().split())
#             edges[here].append((weight, there))
#
#         distances = bellman_ford(1, size_v, edges)
#         if distances == []:
#             print(-1)
#         else:
#             for i in range(2, size_v + 1):
#                 # 시작 점으로 부터 경로가 존재하지 않을 때
#                 if distances[i] < math.inf - offset:
#                     print(distances[i])
#                 else:
#                     print(-1)
