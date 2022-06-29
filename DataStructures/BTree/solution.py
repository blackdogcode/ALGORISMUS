from typing import Optional


class TreeNode:
    max_degree = 3

    def __init__(self):
        self.keys = []
        self.children = []
        self.leaf = True
        self.parent = None

    def add_key(self, key):
        self.keys.append(key)
        self.keys.sort()


class BTree:
    def __init__(self):
        self.root: TreeNode = None

    def insert(self, key: Optional[int]):
        if self.root is None:
            self.root = TreeNode()
            self.root.add_key(key)
            self.root.children.extend([None, None])
            self.root.parent = None
            return

        y = None
        x = self.root
        if x.leaf is True:
            x.add_key(key)
            if not x.children:
                x.children.extend([None, None])
            else:
                x.children.append(None)
            if len(x.keys) == TreeNode.max_degree:
                self.split(x)
        else:
            while x.leaf is False:
                y = x
                i = 0
                while i < len(x.keys) and key > x.keys[i]:
                    i += 1
                x.children[i].parent = x
                x = x.children[i]
            x.parent = y
            x.add_key(key)
            if not x.children:
                x.children.extend([None, None])
            else:
                x.children.append(None)
            if len(x.keys) == TreeNode.max_degree:
                self.split(x)

    def split(self, node: [TreeNode]):
        if node is None:
            return
        if len(node.keys) < TreeNode.max_degree:
            return

        # increase height
        if node == self.root:
            mid_point = len(self.root.keys) // 2
            median_key = self.root.keys[mid_point]
            new_node = TreeNode()
            new_node.children = node.children[mid_point + 1:]
            node.children = node.children[:mid_point + 1]
            new_node.keys = node.keys[mid_point + 1:]
            node.keys = node.keys[:mid_point]
            new_root = TreeNode()
            new_root.add_key(median_key)
            new_root.children = [node, new_node]
            new_root.leaf = False
            self.root = new_root

            if None not in node.children:
                node.leaf = False
            if None not in new_node.children:
                new_node.leaf = False
            return

        mid_point = len(node.keys) // 2
        median_key = node.keys[mid_point]

        new_node = TreeNode()
        new_node.parent = node.parent
        new_node.children = node.children[mid_point + 1:]
        node.children = node.children[:mid_point]
        new_node.keys = node.keys[mid_point + 1:]
        node.keys = node.keys[:mid_point]

        # node.keys.remove(median_key)
        # del node.children[mid_point]

        parent_node: TreeNode = node.parent
        parent_node.add_key(median_key)
        idx = parent_node.keys.index(median_key)
        parent_node.children.insert(idx + 1, None)

        parent_node.children[idx + 1] = new_node

        self.split(parent_node)

    def search(self, key) -> [int, int]:
        pass

    def preorder_traversal(self, node: Optional[TreeNode]):
        if node is None:
            return

        for i in range(len(node.keys)):
            print(node.keys[i], end=' ')
            self.preorder_traversal(node.children[i])
        self.preorder_traversal(node.children[-1])



btree = BTree()
btree.insert(100)
btree.insert(50)
btree.insert(25)
btree.insert(13)
btree.insert(75)
btree.insert(20)
btree.insert(80)
btree.insert(55)
btree.insert(77)
btree.preorder_traversal(btree.root)
