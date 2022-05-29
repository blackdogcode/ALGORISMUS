# https://algospot.com/judge/problem/read/TRAVERSAL

def print_post_order(pre_order, in_order):
    if len(pre_order) == 0:
        return None

    root = pre_order[0]  # 전위 순회의 첫번째 값은 트리의 루트 값
    # 중위 순회의 루트 값과 같은 위치를 찾으면 그 기준으로
    # 좌측 값들은 왼쪽 서브트리 우측 값들은 오른쪽 서브트리
    root_inorder_idx = 0
    for idx in range(len(in_order)):
        if root == in_order[idx]:
            root_inorder_idx = idx
            break

    # 재귀 호출을 이용하여 후위 순휘를 출력
    left_length = root_inorder_idx
    print_post_order(pre_order[1:left_length + 1], in_order[0:left_length])
    print_post_order(pre_order[left_length + 1:len(pre_order)], in_order[left_length + 1:len(in_order)])

    print(root, end=' ')


# 제출용
# test_case = int(input())
# for _ in range(test_case):
#     n = int(input())
#     pre_order = list(map(int, input().split()))
#     in_order = list(map(int, input().split()))
#     print_post_order(pre_order, in_order)
#     print()


# 테스트용
with open('sample_input.txt') as test_input:
    test_case = int(test_input.readline())
    for _ in range(test_case):
        n = int(test_input.readline())
        pre_order = list(map(int, test_input.readline().split()))
        in_order = list(map(int, test_input.readline().split()))
        print_post_order(pre_order, in_order)
        print()
