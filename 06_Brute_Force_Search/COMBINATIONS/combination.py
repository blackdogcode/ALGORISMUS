# 재귀 호출 방법을 이용하여 주어진 수들의 모든 조합을 추출하는 함수 구현
# 이미 제공 되는 라이브러리: 검증용
import random
from itertools import combinations


def usr_comb(arr: list, picked: list, topick: int, comb: list):
    # 기저 조건: 조합을 완성 했을 때
    if topick == 0:
        comb_lst = list()
        for idx in picked:
            comb_lst.append(arr[idx])
        comb.append(tuple(comb_lst))
    # 고를 수 있는 가장 작은 수
    smallest = 0
    if picked:
        smallest = picked[-1] + 1
    else:
        smallest = 0
    # 다음 고를 수를 정한다
    for next_idx in range(smallest, len(arr)):
        picked.append(next_idx)
        usr_comb(arr, picked, topick - 1, comb)
        picked.pop()


# 테스트 데이터 생성
test_set = set()
test_arr = list()
for _ in range(5):
    test_set.add(random.randint(0, 100))
test_arr = list(test_set)
print(test_arr)
test_arr.sort()
print(test_arr)

test_usr_comb = []
usr_comb(test_arr, [], 3, test_usr_comb)
print(test_usr_comb)

test_sys_comb = combinations(test_arr, 3)
test_sys_comb = list(test_sys_comb)
print(test_sys_comb)

print(test_usr_comb == test_sys_comb)
