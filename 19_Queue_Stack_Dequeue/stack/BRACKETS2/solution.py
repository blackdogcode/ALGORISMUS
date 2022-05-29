# https://algospot.com/judge/problem/read/BRACKETS2
from collections import deque

valid_bracket_pair = ['()', '{}', '[]']
closed_brackets = [')', '}', ']']


def is_match_barckets(string):
    # 예외처리
    if len(string) == 1: # 문제 조건에서 길이는 1이상 문자열이 주어지므로 길이가 0일 때는 예외처리 필요 없음
        return 'NO'

    stack_brackets = deque(string[0])
    for i in range(1, len(string)):
        if string[i] in closed_brackets:
            # 스택 매치 할 수 있는 열린 괄호가 없는, 즉 비어있는, 상태
            if len(stack_brackets) == 0:
                return 'NO'
            # 유효한 괄호 쌍이 존재한다 는 것은 닫인 괄호 오른 순서 되로
            # 발견 된다면 반드시 바로 왼쪽에 열린 괄호 쌍이 존재해야 한다
            right = string[i]
            left = stack_brackets[-1]
            if (left + right) not in valid_bracket_pair:
                return 'NO'
            stack_brackets.pop()  # 매치 된 괄호 쌍은 추출한다
        else:
            stack_brackets.append(string[i])

    if len(stack_brackets) == 0:  # 매치 되지 못한 괄호들이 존재
        return 'YES'
    else:
        return 'NO'


# 제출용
test_case = int(input())
for _ in range(test_case):
    string = list(input())
    # print(string)
    print(is_match_barckets(string))


# 테스트용
# with open('sample_input.txt') as test_input:
#     test_case = int(test_input.readline())
#     for _ in range(test_case):
#         string = list(test_input.readline().rstrip())
#         print(string)
#         print(is_match_barckets(string))
