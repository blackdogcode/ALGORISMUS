# https://www.acmicpc.net/problem/2178
# shortest path distance when weight of every edge is 1
# time complexity O(V + E)
import sys
from collections import deque
input = sys.stdin.readline


def bfs(maze: list, start_y: int, start_x: int, end_y: int, end_x: int, size_n: int, size_m: int):
    discovered = [[False] * size_m for _ in range(size_n)]
    distance = [[-1] * size_m for _ in range(size_n)]

    dy = [+1, +0, -1, +0]
    dx = [+0, +1, +0, -1]
    discovered[start_y][start_x] = True
    distance[start_y][start_x] = 1  # 시작점도 길이 포함
    stack = deque()
    stack.append((start_y, start_x))
    while len(stack) != 0:
        y, x = stack.popleft()
        for i in range(len(dy)):
            new_y, new_x = y + dy[i], x + dx[i]
            if new_y < 0 or new_y >= size_n:  # 바깥 영역을 벗어 났을 때 예외처리
                continue
            if new_x < 0 or new_x >= size_m:  # 바깥 영역을 벗어 났을 때 예외처리
                continue
            if maze[new_y][new_x] != 0 and not discovered[new_y][new_x]:
                discovered[new_y][new_x] = True
                stack.append((new_y, new_x))
                distance[new_y][new_x] = distance[y][x] + 1

    return distance[end_y][end_x]


# 제출용
maze = []
n, m = map(int, input().split())
for _ in range(n):
    row = list(map(int, input().rstrip()))
    maze.append(row)

print(bfs(maze, 0, 0, n - 1, m - 1, n, m))


# 테스트용
# with open('sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         maze = []
#         n, m = map(int, test_input.readline().split())
#         for _ in range(n):
#             row = list(map(int, test_input.readline().rstrip()))
#             maze.append(row)
#         print(bfs(maze, 0, 0, n - 1, m - 1, n, m))

