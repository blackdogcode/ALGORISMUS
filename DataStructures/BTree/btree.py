# Reference Algorithm: https://algorithmtutor.com/Data-Structures/Tree/B-Trees/
# Reference Visualization: https://www.cs.usfca.edu/~galles/visualization/BTree.html
from collections import deque
import csv
import filecmp
from typing import Optional


class TreeNode:
    max_degree = 29

    def __init__(self):
        self.keys = []
        self.values = []
        self.children = []
        self.leaf = True
        self.parent = None

    def add_key(self, key, value):
        self.keys.append(key)
        self.keys.sort()
        idx = self.keys.index(key)
        self.values.insert(idx, value)


class BTree:
    def __init__(self):
        self.root: TreeNode = None

    def insert(self, key, value):
        if self.root is None:
            self.root = TreeNode()
            self.root.add_key(key, value)
            self.root.children.extend([None, None])
            self.root.parent = None
            return

        y = None
        x = self.root
        if x.leaf is True:
            x.add_key(key, value)
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
            x.add_key(key, value)
            x.children.append(None)
            if len(x.keys) == TreeNode.max_degree:
                self.split(x)

    def split(self, node: Optional[TreeNode]):
        if node is None:
            return
        if len(node.keys) < TreeNode.max_degree:
            return

        mid_point = len(node.keys) // 2
        median_key = node.keys[mid_point]
        median_val = node.values[mid_point]
        new_node = TreeNode()
        new_node.children = node.children[mid_point + 1:]
        node.children = node.children[:mid_point + 1]
        new_node.keys = node.keys[mid_point + 1:]
        node.keys = node.keys[:mid_point]
        new_node.values = node.values[mid_point + 1:]
        node.values = node.values[:mid_point]

        if None not in node.children:
            node.leaf = False
        if None not in new_node.children:
            new_node.leaf = False

        if node == self.root:
            new_root = TreeNode()
            new_root.add_key(median_key, median_val)
            new_root.children = [node, new_node]
            new_root.leaf = False
            self.root = new_root
        else:
            new_node.parent = node.parent
            parent_node: TreeNode = node.parent
            parent_node.add_key(median_key, median_val)
            idx = parent_node.keys.index(median_key)
            parent_node.children.insert(idx + 1, None)
            parent_node.children[idx + 1] = new_node
            self.split(parent_node)

    def search(self, node: Optional[TreeNode], key):
        if node is None:
            return -1
        i = 0
        while i < len(node.keys) and key > node.keys[i]:
            i += 1
        if i < len(node.keys) and key == node.keys[i]:
            return node.values[i]
        elif node.leaf is True:
            return -1
        else:
            return self.search(node.children[i], key)

    def preorder_traversal(self, node: Optional[TreeNode]):
        if node is None:
            return

        for i in range(len(node.keys)):
            print(node.keys[i], end=' ')
            self.preorder_traversal(node.children[i])
        self.preorder_traversal(node.children[-1])

    def clear(self):
        self.root = None


btree = BTree()
while True:
    operation = int(input('''
B-Tree Simulation
Select Command Number
1. insert
2. delete
3. quit
4. clear
--> '''))
    if operation == 1:
        # insert
        file_name = input('insert file name(e.g. input.csv): ')
        with open(file_name, mode='r') as input_file:
            csvFile = csv.reader(input_file, delimiter='\t')
            print('inserting key-value pairs in b-tree...')
            for line in csvFile:
                key, val = map(int, line)
                btree.insert(key, val)
            print('inserting is completed')
        # search
        keys_vals = deque()
        with open(file_name, mode='r') as search_file:
            csvFile = csv.reader(search_file, delimiter='\t')
            print('searching...')
            for line in csvFile:
                key, val = map(int, line)
                ret_val = btree.search(btree.root, key)
                keys_vals.append((key, ret_val))
            print('searching completed')
        # write
        result_file = 'input_result.csv'
        print('writing result file')
        with open(result_file, mode='w') as write_file:
            for key_val in keys_vals:
                key, val = key_val
                write_file.write(f'{key}\t{val}\r')
        print('writing completed')
        # compare
        print(f'comparing {file_name} with {result_file}')
        result = filecmp.cmp(file_name, result_file)
        if result == 0:
            print('both file matched')
        else:
            print('both file mismatched')
    elif operation == 2:
        print('deletion is not implemented yet')
    elif operation == 3:
        break
    elif operation == 4:
        btree.clear()
    else:
        print(f'Invalid Command')


# Testing and Debugging
# btree = BTree()
# with open('input.csv', mode='r') as input_file:
#     csvFile = csv.reader(input_file, delimiter='\t')
#     i = 0
#     for line in csvFile:
#         key, val = map(int, line)
#         btree.insert(key, val)
#         i += 1
#         if i == 20:
#             break
#
# btree.preorder_traversal(btree.root)
