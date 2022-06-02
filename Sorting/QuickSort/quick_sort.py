#  https://www.acmicpc.net/problem/2750
#  TYPE: Merge Sort[O(nlogn)]
#  GOAL: Sort Array in non-decreasing order
#  Paradigm: Divide_and_Conque
import sys, random
sys.setrecursionlimit(10 ** 6)
input = sys.stdin.readline


def quick_sort(arr: list, p: int, r: int):
    # base condition
    if p >= r:
        return
    # partitioning - divide
    i = p - 1
    for j in range(p, r + 1):
        if arr[j] < arr[r]:  # arr[r] is pivot
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    i += 1
    arr[i], arr[r] = arr[r], arr[i]

    # conquer
    quick_sort(arr, p, i - 1)
    quick_sort(arr, i + 1, r)


n = int(input())
numbers = []
for _ in range(n):
    num = int(input())
    numbers.append(num)
quick_sort(numbers, 0, len(numbers) - 1)
for num in numbers:
    print(num)
