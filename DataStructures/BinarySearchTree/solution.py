from typing import Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def inorder_traversal(self):
        print(self.val)
        if self.left is not None:
            self.inorder_traversal(self.left)
        if self.right is not None:
            self.inorder_traversal(self.right)

class Solution:
    def searchBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
        if root is None:
            return None

        if val == root.val:
            self.inorder_traversal(root)
        elif val < root.val:
            self.searchBST(root.left, val)
        else:
            self.searchBST(root.right, val)

    def inorder_traversal(self, root: Optional[TreeNode]):
        print(root.val)
        if root.left is not None:
            self.inorder_traversal(root.left)
        if root.right is not None:
            self.inorder_traversal(root.right)