# https://www.acmicpc.net/problem/1976
import sys
sys.setrecursionlimit(10 ** 5)
input = sys.stdin.readline

class DisjointSets:
    def __init__(self, n):
        # 도시 번호는 1부터 시작하므로 n + 1까지 생성
        self.parent = [i for i in range(n + 1)]
        self.rank = [1 for i in range(n + 1)]

    def find(self, a):
        if self.parent[a] == a:
            return a
        else:
            self.parent[a] = self.find(self.parent[a])
            return self.parent[a]

    def union(self, a, b):
        set_a, set_b = self.find(a), self.find(b)

        if set_a == set_b: return

        if self.rank[set_a] > self.rank[set_b]:
            set_a, set_b = set_b, set_a
        self.parent[set_a] = set_b

        if self.rank[set_a] == self.rank[set_b]:
            self.rank[set_b] += 1


n = int(input())
m = int(input())

disjoint_set = DisjointSets(n)
for i in range(n):
    links = list(map(int, input().split()))
    for j in range(n):
        if links[j] == 1:
            # 도시 번호는 1번 부터 시작 하므로 +1을 더함
            disjoint_set.union(i + 1, j + 1)

cities = list(map(int, input().split()))
if len(cities) == 1:
    print('YES')
else:
    for i in range(len(cities) - 1):
        from_city, to_city = cities[i], cities[i + 1]
        if disjoint_set.find(from_city) != disjoint_set.find(to_city):
            print('NO')
            break
    else:
        print('YES')


# with open('sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         n = int(test_input.readline())
#         m = int(test_input.readline())
#
#         disjoint_set = DisjointSets(n)
#         for i in range(n):
#             links = list(map(int, test_input.readline().split()))
#             for j in range(n):
#                 print(links[j], end=' ')
#                 if links[j] == 1:
#                     disjoint_set.union(i + 1, j + 1)
#             print()
#         cities = list(map(int, test_input.readline().split()))
#         if len(cities) == 1:
#             print('YES')
#         else:
#             for i in range(len(cities) - 1):
#                 from_city, to_city = cities[i], cities[i + 1]
#                 if disjoint_set.find(from_city) != disjoint_set.find(to_city):
#                     print('NO')
#                     break
#             else:
#                 print('YES')

