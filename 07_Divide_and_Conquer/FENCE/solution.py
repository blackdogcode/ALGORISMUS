# https://algospot.com/judge/problem/read/FENCE
import sys

def fence(start: int, end: int, board: list):
    # 기저 조건
    if start == end:
        return board[start]

    mid = (start + end) // 2
    max_area = 0
    # 왼쪽 영역에서 최대 값이 존재할 경우
    max_area = max(max_area, fence(start, mid, board))
    # 오른쪽 영역에서 최대 값이 존재할 경우
    max_area = max(max_area, fence(mid + 1, end, board))
    # 최대로 자라낸 울타리 직사각형이 중앙 위치에 걸쳐 있을 때
    left, right = mid, mid + 1
    width = 2
    min_height = min(board[left], board[right])
    max_area = max(max_area, min_height * 2)
    while start < left or right < end:
        if left == start:
            right, width = right + 1, width + 1
            min_height = min(min_height, board[right])
            max_area = max(max_area, width * min_height)
        elif right == end:
            left, width = left - 1, width + 1
            min_height = min(min_height, board[left])
            max_area = max(max_area, width * min_height)
        else:
            width += 1
            if board[left - 1] < board[right + 1]:
                min_height = min(min_height, board[right + 1])
                right += 1
            else:
                min_height = min(min_height, board[left - 1])
                left -= 1
            max_area = max(max_area, width * min_height)

    return max_area

# 제출용
test_case = int(sys.stdin.readline())
for _ in range(test_case):
    n = int(sys.stdin.readline())
    board = list(map(int, sys.stdin.readline().split()))
    print(fence(0, n - 1, board))

# 테스트용
# with open('sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         n = int(test_input.readline())
#         board = list(map(int, test_input.readline().split()))
#         print(fence(0, n - 1, board))
