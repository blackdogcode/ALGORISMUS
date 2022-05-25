# https://algospot.com/judge/problem/read/JUMPGAME

memo = [[-1] * 101 for _ in range(101)]


def init_memo(dimension: int):
    global memo
    for y in range(dimension):
        for x in range(dimension):
            memo[y][x] = -1


def jump_game(start_y: int, start_x: int, dimension: int, board: list):
    # 범위 내를 벗어 났을 때
    if start_y >= dimension or start_x >= dimension:
        return 0
    # 목적지에 도달 했을 때
    if board[start_y][start_x] == 0:
        return 1
    # 이미 시도 해본 결과가 있을 때: memoization
    global memo
    if memo[start_y][start_x] != -1:
        return memo[start_y][start_x]
    # 재귀 호출
    delta = board[start_y][start_x]
    ret = -1
    ret = max(ret, jump_game(start_y + delta, start_x, dimension, board))
    ret = max(ret, jump_game(start_y, start_x + delta, dimension, board))
    # 결과 값을 갱신
    memo[start_y][start_x] = ret
    return ret


def print_matrix(n: int, matrix: list):
    for y in range(n):
        for x in range(n):
            print(matrix[y][x], end=' ')
        print()

# 테스트용
# with open('sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         dimension = int(test_input.readline())
#         matrix = []
#         for _ in range(dimension):
#             matrix.append(list(map(int, test_input.readline().split())))
#         init_memo(dimension)
#         print_matrix(dimension, matrix)
#         ret = jump_game(0, 0, dimension, matrix)
#         if ret == 1:
#             print('YES')
#         elif ret == 0:
#             print('NO')
#         else:
#             print('Invalid Value')

# 제출용
test_case = int(input())
for _ in range(test_case):
    dimension = int(input())
    matrix = []
    for _ in range(dimension):
        matrix.append(list(map(int, input().split())))
    init_memo(dimension)
    ret = jump_game(0, 0, dimension, matrix)
    if ret == 1:
        print('YES')
    elif ret == 0:
        print('NO')
    else:
        print('Invalid Value')
