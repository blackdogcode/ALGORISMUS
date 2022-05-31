import sys
sys.setrecursionlimit(10 ** 5)
input = sys.stdin.readline

class DisjointSets:
    def __init__(self, n):
        self.parents = [i for i in range(n + 1)]
        self.ranks = [1 for i in range(n + 1)]

    def find(self, a):
        if self.parents[a] == a:
            return a
        else:
            self.parents[a] = self.find(self.parents[a])
            return self.parents[a]

    def union(self, a, b):
        set_a, set_b = self.find(a), self.find(b)

        if set_a == set_b: return

        if self.ranks[set_a] > self.ranks[set_b]:
            set_a, set_b = set_b, set_a

        self.parents[set_a] = set_b
        if self.ranks[set_a] == self.ranks[set_b]:
            self.ranks[set_b] += 1


# 체점용
n, m = map(int, input().split())
disjoint_sets = DisjointSets(n)
for _ in range(m):
    operation, a, b = map(int, input().split())
    if operation == 0:
        disjoint_sets.union(a, b)
    elif operation == 1:
        if disjoint_sets.find(a) == disjoint_sets.find(b):
            print('YES')
        else:
            print('NO')
    else:
        print('INVALID OPERATION')


# 테스트용
# with open('sample_input.txt') as test_input:
#     n, m = map(int, test_input.readline().split())
#     disjoint_sets = DisjointSets(n)
#     for _ in range(m):
#         operation, a, b = map(int, test_input.readline().split())
#         if operation == 0:
#             disjoint_sets.union(a, b)
#         elif operation == 1:
#             if disjoint_sets.find(a) == disjoint_sets.find(b):
#                 print('YES')
#             else:
#                 print('NO')
#         else:
#             print('INVALID OPERATION')
