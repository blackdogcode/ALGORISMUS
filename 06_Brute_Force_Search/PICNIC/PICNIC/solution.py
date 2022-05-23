# https://algospot.com/judge/problem/read/PICNIC

def make_pairs(n: int, friendship: list, is_have_pair: list):
    first_candidate = -1
    for i in range(n):
        if not is_have_pair[i]:
            first_candidate = i
            break
    if first_candidate == -1:
        return 1

    count = 0
    for second_candidate in range(first_candidate + 1, n):
        if (not is_have_pair[second_candidate]) and (friendship[first_candidate][second_candidate]):
            is_have_pair[first_candidate], is_have_pair[second_candidate] = True, True
            count += make_pairs(n, friendship, is_have_pair)
            is_have_pair[first_candidate], is_have_pair[second_candidate] = False, False

    return count


def display_friendship(n: int, friendship: list):
    for y in range(n):
        for x in range(n):
            print(friendship[y][x], end=' ')
        print()


# 테스트용
with open('sample_input.txt') as test_input:
    test_case = int(test_input.readline())
    for _ in range(test_case):
        n, m = tuple(map(int, test_input.readline().split()))
        friendship = [[0] * n for _ in range(n)]
        friends = tuple(map(int, test_input.readline().split()))
        for k in range(0, 2 * m, 2):
            i = friends[k]
            j = friends[k + 1]
            friendship[i][j], friendship[j][i] = 1, 1
        print(n, m)
        display_friendship(n, friendship)
        ret = make_pairs(n, friendship, [False] * n)
        print(ret)
        print()

# 제출용
# test_case = int(input())
# for _ in range(test_case):
#     n, m = map(int, input().split())
#     friendship = [[False] * n for _ in range(n)]
#     friends = list(map(int, input().split()))
#     for k in range(0, 2 * m, 2):
#         i = friends[k]
#         j = friends[k + 1]
#         friendship[i][j], friendship[j][i] = True, True
#
#     ret = make_pair(n, friendship, [False] * n)
#     print(ret)
