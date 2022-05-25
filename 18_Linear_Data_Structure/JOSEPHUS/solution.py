# https://algospot.com/judge/problem/read/JOSEPHUS
from collections import deque

test_case = int(input())
for _ in range(test_case):
    n, k = map(int, input().split())
    table = deque(n for n in range(1, n + 1)) # 테이블에 앉아 있는 사람들의 번호를 시계방향으로 할당 
    while len(table) != 2:
        table.popleft()
        table.rotate(-k + 1)
    for people in sorted(table):
        print(people, end=' ')
    print()
