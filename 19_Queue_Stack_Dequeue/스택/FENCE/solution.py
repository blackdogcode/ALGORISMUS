from collections import deque


def fence(boards):
    boards.append(0)
    remain = deque()
    ret = 0
    for i in range(len(boards)):
        while(len(remain) != 0) and (boards[remain[-1]] >= boards[i]):
            j = remain[-1]
            remain.pop()

            width = -1
            if len(remain) == 0:
                width = i
            else:
                width = (i - remain[-1] - 1)
            ret = max(ret, boards[j] * width)

        remain.append(i)
    return ret

# 제출용
# test_case = int(input())
# for _ in range(test_case):
#     size = int(input())
#     boards = deque(map(int, input().split()))
#     ret = fence(boards)
#     print(ret)


# 테스트용
with open('sample_input.txt') as test_input:
    test_case = int(test_input.readline())
    for _ in range(test_case):
        size = int(test_input.readline())
        boards = deque(map(int, test_input.readline().split()))
        ret = fence(boards)
        print(ret)
