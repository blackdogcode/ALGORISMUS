# implementation problems
# https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_8_A
# https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_8_B
# https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_8_C

# reference solution - insert, traversal
# https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=2929933#1

from typing import Optional
import sys
sys.setrecursionlimit(10 ** 6)
input = sys.stdin.readline


class TreeNode:
    def __init__(self, key=0, left=None, right=None):
        self.key = key
        self.left = left
        self.right = right


class BinarySearchTree:
    def __init__(self):
        self.root = None

    def insert(self, key: int):
        z = TreeNode(key)
        y = None
        x = self.root
        while x:
            y = x
            if z.key < x.key:
                x = x.left
            else:
                x = x.right
        z.parent = y
        if y is None:
            self.root = z
        elif z.key < y.key:
            y.left = z
        else:
            y.right = z

    def preorder_traversal(self, node: Optional[TreeNode]):
        if node is None:
            return []
        ret = [node.key]
        ret += self.preorder_traversal(node.left)
        ret += self.preorder_traversal(node.right)
        return ret

    def inorder_traversal(self, node: Optional[TreeNode]):
        if node is None:
            return []
        ret = []
        ret += self.inorder_traversal(node.left)
        ret += [node.key]
        ret += self.inorder_traversal(node.right)
        return ret

    def postorder_traversal(self, node: Optional[TreeNode]):
        if node is None:
            return []
        ret = []
        ret += self.inorder_traversal(node.left)
        ret += self.inorder_traversal(node.right)
        ret += [node.key]
        return ret


m = int(input())
bst = BinarySearchTree()
for _ in range(m):
    command = input().split()
    if command[0] == 'print':
        in_order = bst.inorder_traversal(bst.root)
        print("", *in_order)
        pre_order = bst.preorder_traversal(bst.root)
        print("", *pre_order)
    if command[0] == 'insert':
        key = int(command[1])
        bst.insert(key)

# with open('sample_input.txt') as test_input:
#     bst = BinarySearchTree()
#     m = int(test_input.readline())
#     for _ in range(m):
#         command = test_input.readline().split()
#         if command[0] == 'print':
#             in_order = bst.inorder_traversal(bst.root)
#             print("", *in_order)
#             pre_order = bst.preorder_traversal(bst.root)
#             print("", *pre_order)
#         if command[0] == 'insert':
#             key = int(command[1])
#             bst.insert(key)
