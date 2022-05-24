# https://algospot.com/judge/problem/read/QUADTREE

def reverse(quad_tree: list, head: list, result: list):
    """
    :param quad_tree: 쿼드트리를 표현하는 문자열 리스트
    :param head: 쿼드트리 문자열 위치를 표현하는 변수 -> head[0]
    :param result: 기저 조건 모든 격자가 하나의 색깔
    :return: 상하로 뒤바뀐 쿼드트리를 표현하는 문자열 리스트
    """
    color = quad_tree[head[0]]
    head[0] += 1
    if color == 'w' or color == 'b':
        result.append(color)
        return result

    left_upper = reverse(quad_tree, head, [])
    right_upper = reverse(quad_tree, head, [])
    left_lower = reverse(quad_tree, head, [])
    right_lower = reverse(quad_tree, head, [])

    return ['x'] + left_lower + right_lower + left_upper + right_upper


test_case = int(input())
for _ in range(test_case):
    quad_tree = [char for char in input()]
    reverse_quad_tree = reverse(quad_tree, [0], [])
    result = ''.join(str(elem) for elem in reverse_quad_tree) # 리스트 -> 문자열로 치환
    print(result)

# with open('sample_input.txt') as test_input:
#     c = int(test_input.readline())
#     for _ in range(c):
#         quad_tree = [char for char in test_input.readline().rstrip()] # rstrip() -> newline 제거
#         print(quad_tree)
#         reverse_quad_tree = reverse(quad_tree, [0], [])
#         print(reverse_quad_tree)
