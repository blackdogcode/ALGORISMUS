import sys
input = sys.stdin.readline

# 유니온 파인드 - 상호 베타적 집합
class DisjointSet:
    def __init__(self, size):
        self.parents = [i for i in range(size)]
        self.ranks = [1 for _ in range(size)]

    def find(self, u):
        if self.parents[u] == u:
            return u
        else:
            # path compression
            self.parents[u] = self.find(self.parents[u])
            return self.parents[u]

    def union(self, u, v):
        set_u, set_v = self.find(u), self.find(v)
        if set_u == set_v:
            return

        if self.ranks[set_u] > self.ranks[set_v]:
            set_u, set_v = set_v, set_u

        self.parents[set_u] = set_v
        if self.ranks[set_u] == self.ranks[set_v]:
            self.ranks[set_v] += 1


def kruskal(size_vertex: int, sorted_edges: list):
    min_span_weight = 0
    selected_edges = []

    disjoint_set = DisjointSet(size_vertex + 1)  # 정점의 번호가 1부터 시작

    for edge in edges:
        weight, here, there = edge
        if disjoint_set.find(here) == disjoint_set.find(there):
            continue
        else:
            disjoint_set.union(here, there)
            min_span_weight += weight
            selected_edges.append((here, there))

    return min_span_weight, selected_edges


# 제출용
size_v, size_e = map(int, input().split())
edges = []
for _ in range(size_e):
    u, v, w = map(int, input().split())
    edges.append((w, u, v))
edges.sort()
min_span_weight, selected_edges = kruskal(size_v, edges)
print(min_span_weight)


# 테스트용
# with open('../sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         size_v, size_e = map(int, test_input.readline().split())
#         edges = []
#         for _ in range(size_e):
#             u, v, w = map(int, test_input.readline().split())
#             edges.append((w, u, v))
#         edges.sort()
#         min_span_weight, selected_edges = kruskal(size_v, edges)
#         print(min_span_weight)
#         print(selected_edges)

