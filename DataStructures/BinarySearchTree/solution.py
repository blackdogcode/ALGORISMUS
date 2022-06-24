# https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_8_A
# https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_8_B
# https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_8_C
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

    def insert(self, node: Optional[TreeNode]):
        if self.root is None:
            self.root = node
            return

        y = None
        x = self.root
        while x is not None:
            if node.key == x.key:
                return
            y = x
            if node.key < x.key:
                x = x.left
            else:
                x = x.right

        if node.key < y.key:
            y.left = node
        else:
            y.right = node

    def preorder_traversal(self, node: Optional[TreeNode], order: list):
        if node is None:
            return
        order.append(node.key)
        if node.left is not None:
            self.preorder_traversal(node.left, order)
        if node.right is not None:
            self.preorder_traversal(node.right, order)

    def inorder_traversal(self, node: Optional[TreeNode], order: list):
        if node is None:
            return
        if node.left is not None:
            self.inorder_traversal(node.left, order)
        order.append(node.key)
        if node.right is not None:
            self.inorder_traversal(node.right, order)


m = int(input())
bst = BinarySearchTree()
for _ in range(m):
    operation = input().split()
    if operation[0] == 'print':
        in_order, pre_order = [], []
        bst.inorder_traversal(bst.root, in_order)
        print("", *in_order)
        bst.preorder_traversal(bst.root, pre_order)
        print("", *pre_order)
    if operation[0] == 'insert':
        key = int(operation[1])
        bst.insert(TreeNode(key))

# with open('sample_input.txt') as test_input:
#     bst = BinarySearchTree()
#
#     m = int(test_input.readline())
#     for _ in range(m):
#         operation = test_input.readline().split()
#         if operation[0] == 'print':
#             pre_order, in_order = [], []
#             bst.inorder_traversal(bst.root, in_order)
#             print("", *in_order)
#             bst.preorder_traversal(bst.root, pre_order)
#             print("", *pre_order)
#         if operation[0] == 'insert':
#             key = int(operation[1])
#             bst.insert(TreeNode(key))





#     def inorder_traversal(self):
#         print(self.val)
#         if self.left is not None:
#             self.inorder_traversal(self.left)
#         if self.right is not None:
#             self.inorder_traversal(self.right)
#
#
#
# class Solution:
#     def searchBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
#         if root is None:
#             return None
#
#         if val == root.val:
#             self.inorder_traversal(root)
#         elif val < root.val:
#             self.searchBST(root.left, val)
#         else:
#             self.searchBST(root.right, val)
#
#     def inorder_traversal(self, root: Optional[TreeNode]):
#         print(root.val)
#         if root.left is not None:
#             self.inorder_traversal(root.left)
#         if root.right is not None:
#             self.inorder_traversal(root.right)
#
