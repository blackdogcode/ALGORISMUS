# https://www.acmicpc.net/problem/1920
def binary_search(key, arr):
    """
    :param key: 찾고자 하는 수
    :param arr: 정렬된 정수들
    :return: 존재 하면 1, 존재 하지 않으면 0
    """
    first, last = 0, len(arr) - 1
    while first <= last:
        mid = (first + last) // 2
        if arr[mid] == key:
            return 1
        if arr[mid] < key:
            first = mid + 1
        else:
            last = mid - 1
    return 0

# 테스트용
"""
with open('sample_input.txt', mode='r') as test_input:
    n = int(test_input.readline())
    arr = list(map(int, test_input.readline().split()))
    arr.sort()
    print(arr)

    m = int(test_input.readline())
    keys = list(map(int, test_input.readline().split()))
    print(keys)

    for key in keys:
        result = binary_search(key, arr)
        print(result)
"""

# 제출용
n = int(input())
arr = list(map(int, input().split()))
arr.sort()

m = int(input())
keys = list(map(int, input().split()))

for key in keys:
    result = binary_search(key, arr)
    print(result)
