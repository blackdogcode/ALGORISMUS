#  https://www.acmicpc.net/problem/2750
#  TYPE: Merge Sort[O(nlogn)]
#  GOAL: Sort Array in non-decreasing order
#  Paradigm: Divide_and_Conque
import math, random, sys
sys.setrecursionlimit(10 ** 6)
sys.stdin.readline


def merge_sort(arr: list, p: int, r: int):
    # base condition
    if p >= r:
        return
    # divide
    q = (p + r) // 2
    merge_sort(arr, p, q)
    merge_sort(arr, q+1, r)
    # conquer
    merge(arr, p, q, q+1, r)
    return


def merge(arr: list, p: int, q: int, r: int, s: int):
    # lhs: left-hand side
    lhs_arr = arr[p:q+1]
    lhs_arr.append(math.inf)
    # rhs: right-hand side
    rhs_arr = arr[r:s+1]
    rhs_arr.append(math.inf)

    # compare and merge
    lhs_idx = rhs_idx = 0
    for k in range(p, s + 1):
        if lhs_arr[lhs_idx] <= rhs_arr[rhs_idx]:
            arr[k] = lhs_arr[lhs_idx]
            lhs_idx += 1
        else:
            arr[k] = rhs_arr[rhs_idx]
            rhs_idx += 1


n = int(input())
arr = []
for _ in range(n):
    num = int(input())
    arr.append(num)
merge_sort(arr, 0, n - 1)
for num in arr:
    print(num)
