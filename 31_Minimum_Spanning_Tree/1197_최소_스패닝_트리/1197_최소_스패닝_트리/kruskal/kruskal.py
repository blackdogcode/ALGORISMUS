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


def kruskal(selected: list):
    ret = 0


# 테스트용
with open('sample_input.txt') as test_input:
    test_case = int(test_input.readline())
    for _ in range(test_case):
        V, E = map(int, test_input.readline().split())
        edges = []
        for _ in range(E):
            u, v, w = map(int, test_input.readline().split())
            edges.append((w, u, v))

        for edge in edges:
            print(edge)

        print()

        edges.sort()
        for edge in edges:
            print(edge)

