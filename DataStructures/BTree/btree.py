# Reference Algorithm: https://algorithmtutor.com/Data-Structures/Tree/B-Trees/
# Reference Visualization: https://www.cs.usfca.edu/~galles/visualization/BTree.html
from collections import deque
import csv
import math
import filecmp
from typing import Tuple
from typing import Optional


class TreeNode:
    max_degree = 5

    def __init__(self):
        self.keys = []
        self.values = []
        self.children = []
        self.leaf = True
        self.parent = None

    def add_key_val(self, key, value):
        self.keys.append(key)
        self.keys.sort()
        idx = self.keys.index(key)
        self.values.insert(idx, value)

    def append_left(self, key, value, child):
        self.keys.insert(0, key)
        self.values.insert(0, value)
        self.children.insert(0, child)

    def append_right(self, key, value, child):
        self.keys.append(key)
        self.values.append(value)
        self.children.append(child)

    def pop_left_child(self):
        self.keys.pop(0)
        self.values.pop(0)
        return self.children.pop(0)

    def pop_right_child(self):
        self.keys.pop()
        self.values.pop()
        return self.children.pop()

    def has_least_keys(self):
        return len(self.keys) == math.ceil(TreeNode.max_degree / 2) - 1

    def has_extra_keys(self):
        return len(self.keys) > math.ceil(TreeNode.max_degree / 2) - 1

    def has_less_keys(self):
        return len(self.keys) < math.ceil(TreeNode.max_degree / 2) - 1

    def __str__(self):
        return str(self.keys)


class BTree:
    def __init__(self):
        self.root: TreeNode = None

    def search(self, node: Optional[TreeNode], key) -> Tuple[TreeNode, int]:
        if node is None:
            return None, None
        idx = 0
        while idx < len(node.keys) and key > node.keys[idx]:
            idx += 1
        if idx < len(node.keys) and key == node.keys[idx]:
            return node, idx
        elif node.leaf is True:
            return None, None
        else:
            return self.search(node.children[idx], key)

    def insert(self, key, value):
        if self.root is None:
            self.root = TreeNode()
            self.root.add_key_val(key, value)
            self.root.children.extend([None, None])
            self.root.parent = None
            return

        y = None
        x = self.root
        if x.leaf is True:
            x.add_key_val(key, value)
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
            x.add_key_val(key, value)
            x.children.append(None)
            if len(x.keys) == TreeNode.max_degree:
                self.split(x)

    def split(self, node: Optional[TreeNode]):
        if node is None:
            return
        if None not in node.children:
            node.leaf = False
        if len(node.keys) < TreeNode.max_degree:
            return

        mid_index = len(node.keys) // 2
        median_key = node.keys[mid_index]
        median_val = node.values[mid_index]
        new_node = TreeNode()
        new_node.children = node.children[mid_index + 1:]
        node.children = node.children[:mid_index + 1]
        new_node.keys = node.keys[mid_index + 1:]
        node.keys = node.keys[:mid_index]
        new_node.values = node.values[mid_index + 1:]
        node.values = node.values[:mid_index]
        new_node.parent = node.parent

        if None not in node.children:
            node.leaf = False
        if None not in new_node.children:
            new_node.leaf = False

        if not node.leaf:
            for i in range(len(node.children)):
                node.children[i].parent = node
        if not new_node.leaf:
            for i in range(len(new_node.children)):
                new_node.children[i].parent = new_node

        if node == self.root:
            new_root = TreeNode()
            new_root.add_key_val(median_key, median_val)
            new_root.children = [node, new_node]
            node.parent, new_node.parent = new_root, new_root
            new_root.leaf = False
            self.root = new_root
        else:
            parent_node: TreeNode = node.parent
            parent_node.add_key_val(median_key, median_val)
            idx = parent_node.keys.index(median_key)
            parent_node.children.insert(idx + 1, None)
            parent_node.children[idx + 1] = new_node
            self.split(parent_node)

    def delete(self, key):
        node, idx = self.search(self.root, key)  # key is node.keys[idx]
        if node is None:  # There is no key in tree
            return None

        # case 0: leaf node
        if node.leaf:
            node.keys.pop(idx)
            node.values.pop(idx)
            node.children.pop()
            if node == self.root and len(node.keys) == 0:
                self.root = None
                return
            self.make_valid_btree(node)
        # case 1: internal node
        else:
            predecessor = self.find_predecessor(node, node.keys[idx])
            node.keys[idx], predecessor.keys[-1] = predecessor.keys[-1], node.keys[idx]
            node.values[idx], predecessor.values[-1] = predecessor.values[-1], node.values[idx]
            predecessor.keys.pop()
            predecessor.values.pop()
            predecessor.children.pop()
            self.make_valid_btree(predecessor)

            # successor_node = self.find_successor(node, node.keys[idx])
            # node.keys[idx], successor_node.keys[0] = successor_node.keys[0], node.keys[idx]
            # node.values[idx], successor_node.values[0] = successor_node.values[0], node.values[idx]
            # successor_node.keys.pop(0)
            # successor.node.values.pop(0)
            # successor_node.children.pop(0)
            # self.make_valid_btree(successor_node)

    def make_valid_btree(self, node: TreeNode):
        if node.has_least_keys() or node.has_extra_keys():
            return

        left_sibling_node = self.find_left_sibling_node(node, node.keys[0])
        right_sibling_node = self.find_right_sibling_node(node, node.keys[0])

        if left_sibling_node is not None and left_sibling_node.has_extra_keys():
            self.borrow_key_from_left_sibling(node, left_sibling_node)
        elif right_sibling_node is not None and right_sibling_node.has_extra_keys():
            self.borrow_key_from_right_sibling(node, right_sibling_node)
        else:
            if left_sibling_node is not None:
                self.merge_with_left_sibling(node, left_sibling_node)
            else:
                self.merge_with_right_sibling(node, right_sibling_node)

    @staticmethod
    def borrow_key_from_left_sibling(node: TreeNode, left_sibling: TreeNode):
        key = node.keys[0]
        parent: TreeNode = node.parent
        i = 0
        while i < len(parent.keys) and key > parent.keys[i]:
            i += 1
        new_key, new_val = parent.keys[i - 1], parent.values[i - 1]
        parent.keys[i - 1], parent.values[i - 1] = left_sibling.keys[-1], left_sibling.values[-1]
        new_child = left_sibling.pop_right_child()
        node.append_left(new_key, new_val, new_child)
        if new_child is not None:
            new_child.parent = node

    @staticmethod
    def borrow_key_from_right_sibling(node: TreeNode, right_sibling: TreeNode):
        key = node.keys[-1]
        parent: TreeNode = node.parent
        i = 0
        while i < len(parent.keys) and key > parent.keys[i]:
            i += 1
        new_key, new_val = parent.keys[i], parent.values[i]
        parent.keys[i], parent.values[i] = right_sibling.keys[0], right_sibling.values[0]
        new_child = right_sibling.pop_left_child()
        node.append_right(new_key, new_val, new_child)
        if new_child is not None:
            new_child.parent = node

    @staticmethod
    def find_left_sibling_node(node: TreeNode, key) -> TreeNode:
        parent_node: TreeNode = node.parent
        i = 0
        while i < len(parent_node.keys) and key > parent_node.keys[i]:
            i += 1
        if i == 0:
            return None
        else:
            return parent_node.children[i - 1]

    @staticmethod
    def find_right_sibling_node(node: TreeNode, key) -> TreeNode:
        parent: TreeNode = node.parent
        i = 0
        while i < len(parent.keys) and key > parent.keys[i]:
            i += 1
        if i == len(parent.keys):
            return None
        else:
            return parent.children[i + 1]

    def merge_with_left_sibling(self, node: TreeNode, left_sibling: TreeNode):
        key = node.keys[0]
        parent: TreeNode = node.parent
        i = 0
        while i < len(parent.keys) and key > parent.keys[i]:
            i += 1
        parent_key = parent.keys[i - 1]
        parent_val = parent.values[i - 1]

        # remove parent key in parent node
        parent_key_idx = parent.keys.index(parent_key)
        parent.keys = parent.keys[:parent_key_idx] + parent.keys[parent_key_idx + 1:]
        parent.values = parent.values[:parent_key_idx] + parent.values[parent_key_idx + 1:]
        parent.children = parent.children[:parent_key_idx] + parent.children[parent_key_idx + 1:]

        # insert parent key in merge node
        node.keys = left_sibling.keys + [parent_key] + node.keys
        node.values = left_sibling.values + [parent_val] + node.values
        node.children = left_sibling.children + node.children

        if None not in node.children:
            for i in range(len(node.children)):
                node.children[i].parent = node

        if None in node.children:
            node.leaf = True
        else:
            node.leaf = False

        if parent == self.root:
            if len(parent.keys) == 0:
                self.root = node
                node.parent = None
            return

        self.make_valid_btree(parent)

    def merge_with_right_sibling(self, node: TreeNode, right_sibling: TreeNode):
        key = right_sibling.keys[0]
        parent: TreeNode = node.parent
        i = 0
        while i < len(parent.keys) and key > parent.keys[i]:
            i += 1
        parent_key = parent.keys[i - 1]
        parent_val = parent.values[i - 1]

        # remove parent key in parent node
        parent_key_idx = parent.keys.index(parent_key)
        parent.keys = parent.keys[:parent_key_idx] + parent.keys[parent_key_idx + 1:]
        parent.values = parent.values[:parent_key_idx] + parent.values[parent_key_idx + 1:]
        parent.children = parent.children[:parent_key_idx] + parent.children[parent_key_idx + 1:]

        # insert parent key in merge node
        right_sibling.keys = node.keys + [parent_key] + right_sibling.keys
        right_sibling.values = node.values + [parent_val] + right_sibling.values
        right_sibling.children = node.children + right_sibling.children

        if None not in right_sibling.children:
            for i in range(len(right_sibling.children)):
                right_sibling.children[i].parent = right_sibling

        if None in right_sibling.children:
            right_sibling.leaf = True
        else:
            right_sibling.leaf = False

        if parent == self.root:
            if len(parent.keys) == 0:
                self.root = right_sibling
                right_sibling.parent = None
            return
        self.make_valid_btree(parent)

    @staticmethod
    def find_successor(node: TreeNode, key) -> TreeNode:
        idx = node.keys.index(key)
        y = None
        x = node.children[idx + 1]
        while x is not None:
            y = x
            x = x.children[0]
        return y

    @staticmethod
    def find_predecessor(node: TreeNode, key) -> TreeNode:
        idx = node.keys.index(key)
        y = None
        x = node.children[idx]
        while x is not None:
            y = x
            x = x.children[-1]
        return y

    def preorder_traversal(self, node: Optional[TreeNode]):
        if node is None:
            return
        for i in range(len(node.keys)):
            print(node.keys[i], end=' ')
            self.preorder_traversal(node.children[i])
        self.preorder_traversal(node.children[-1])

    def preorder_parent_traversal(self, node: Optional[TreeNode]):
        if node is None:
            return
        for i in range(len(node.keys)):
            print(f'{node.keys[i]} - {node.parent}')
            self.preorder_parent_traversal(node.children[i])
        self.preorder_parent_traversal(node.children[-1])

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
        insert_file_name = input('insert file name(e.g. input_1.csv): ')
        with open(insert_file_name, mode='r') as insert_file:
            csvFile = csv.reader(insert_file, delimiter='\t')
            print('inserting key-value pairs in b-tree...')
            for line in csvFile:
                key, val = map(int, line)
                btree.insert(key, val)
            print('inserting is completed')
        # search
        keys_vals = deque()
        with open(insert_file_name, mode='r') as search_file:
            csvFile = csv.reader(search_file, delimiter='\t')
            print('searching...')
            for line in csvFile:
                key, val = map(int, line)
                node, idx = btree.search(btree.root, key)
                ret_val = 'N/A'
                if node is not None:
                    ret_val = node.values[idx]
                keys_vals.append((key, ret_val))
            print('searching completed')
        # write
        result_file_name = 'input_result.csv'
        print('writing result file')
        with open(result_file_name, mode='w') as result_file:
            for key_val in keys_vals:
                key, val = key_val
                result_file.write(f'{key}\t{val}\r')
        print('writing completed')
        # compare
        print(f'comparing {insert_file_name} with {result_file_name}')
        insert_compare_result = filecmp.cmp(insert_file_name, result_file_name)
        if insert_compare_result == 0:
            print('both file matched')
        else:
            print('both file mismatched')
    elif operation == 2:
        # delete
        delete_file_name = input('delete file name(e.g. delete_1.csv): ')
        delete_compare_file_name = input('delete compare file name(e.g. delete_compare_1.csv): ')
        with open(delete_file_name, mode='r') as delete_file:
            csvFile = csv.reader(delete_file, delimiter='\t')
            print('deleting key-value pairs in b-tree...')
            for line in csvFile:
                key, val = map(int, line)
                btree.delete(key)
            print('deletion is completed')
        # reading key-value paris from compare file name
        compare_delete_keys = deque()
        print(f'reading key-value pair from compare file {delete_compare_file_name}')
        with open(delete_compare_file_name, mode='r') as delete_compare_file:
            csv_compare_file = csv.reader(delete_compare_file, delimiter='\t')
            for line in csv_compare_file:
                key, val = line
                key = int(key)
                compare_delete_keys.append(key)
        print('reading completed')
        # writing result
        delete_result_file_name = 'delete_result.csv'
        print('writing delete result file')
        with open(delete_result_file_name, mode='w') as delete_result_file:
            for key in compare_delete_keys:
                node, idx = btree.search(btree.root, key)
                ret_val = 0
                if node is None:
                    ret_val = 'N/A'
                else:
                    ret_val = node.values[idx]
                delete_result_file.write(f'{key}\t{ret_val}\r')
        print('writing completed')
        # comparing
        print(f'comparing {delete_compare_file_name} with {delete_result_file_name}')
        delete_compare_result = filecmp.cmp(delete_compare_file_name, delete_result_file_name)
        if delete_compare_result == 0:
            print('both file matched')
        else:
            print('both file mismatched')
        pass
    elif operation == 3:
        break
    elif operation == 4:
        btree.clear()
    else:
        print(f'Invalid Command')



# insert test
# btree = BTree()
# file_name = 'input_1.csv'
# with open(file_name, mode='r') as input_file:
#     csvFile = csv.reader(input_file, delimiter='\t')
#     print('inserting key-value pairs in b-tree...')
#     for line in csvFile:
#         key, val = map(int, line)
#         btree.insert(key, val)
#     print('inserting is completed')
# # search
# keys_vals = deque()
# with open(file_name, mode='r') as search_file:
#     csvFile = csv.reader(search_file, delimiter='\t')
#     print('searching...')
#     for line in csvFile:
#         key, val = map(int, line)
#         node, idx = btree.search(btree.root, key)
#         ret_val = 'N/A'
#         if node is not None:
#             ret_val = node.values[idx]
#         keys_vals.append((key, ret_val))
#     print('searching completed')
# # write
# result_file = 'input_result.csv'
# print('writing result file')
# with open(result_file, mode='w') as write_file:
#     for key_val in keys_vals:
#         key, val = key_val
#         write_file.write(f'{key}\t{val}\r')
# print('writing completed')
# # compare
# print(f'comparing {file_name} with {result_file}')
# result = filecmp.cmp(file_name, result_file)
# if result == 0:
#     print('both file matched')
# else:
#     print('both file mismatched')


# delete test
# btree = BTree()
# print('inserting...')
# with open('input_2.csv', mode='r') as insert_file:
#     csv_insert_file = csv.reader(insert_file, delimiter='\t')
#     i = 0
#     for line in csv_insert_file:
#         key, val = map(int, line)
#         btree.insert(key, val)
#         i += 1
#         # if i == 100:
#         #     break
# print('inserting completed')
# # btree.preorder_traversal(btree.root)
# # print()
# #
# print('deleting...')
# with open('delete_2.csv', mode='r') as delete_file:
#     csv_delete_file = csv.reader(delete_file, delimiter='\t')
#     i = 0
#     for line in csv_delete_file:
#         key, val = map(int, line)
#         print(f'delete {key}')
#         btree.delete(key)
#         # btree.preorder_traversal(btree.root)
#         print()
#         i += 1
#         # if i == 100:
#         #     break
# print('deleting completed')
#
# compare_file = 'delete_compare_2.csv'
# result_file = 'delete_result.csv'
# print('comparing...')
# compare_delete = deque()
# with open(compare_file, mode='r') as delete_compare_file:
#     csv_compare_file = csv.reader(delete_compare_file, delimiter='\t')
#     for line in csv_compare_file:
#         key, val = line
#         key = int(key)
#         compare_delete.append(key)
#
# print('writing result file')
# with open(result_file, mode='w') as delete_result_file:
#     for key in compare_delete:
#         node, idx = btree.search(btree.root, key)
#         ret_val = 0
#         if node is None:
#             ret_val = 'N/A'
#         else:
#             ret_val = node.values[idx]
#         delete_result_file.write(f'{key}\t{ret_val}\r')
# print('writing completed')
#
# print(f'comparing {compare_file} with {result_file}')
# result = filecmp.cmp(compare_file, result_file)
# if result == 0:
#     print('both file matched')
# else:
#     print('both file mismatched')
