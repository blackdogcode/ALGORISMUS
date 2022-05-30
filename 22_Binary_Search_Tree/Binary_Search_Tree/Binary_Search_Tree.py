class BinarySearchTree:
    """
    이진 검색 트리 구현
    """
    def __init__(self, key):
        self.key = key
        self.left_child = None
        self.right_child = None

    def add(self, key):
        if self.key == key:
            return

        if key < self.key:
            if self.left_child is None:
                self.left_child = BinarySearchTree(key)
            else:
                self.left_child.add(key)
        else:
            if self.right_child is None:
                self.right_child = BinarySearchTree(key)
            else:
                self.right_child.add(key)

    def find(self, key):
        if self.key == key:
            return True

        if key < self.key:
            if self.left_child is None:
                return False
            else:
                return self.left_child.find(key)
        else:
            if self.right_child is None:
                return False
            else:
                return self.right_child.find(key)

    def min(self):
        min_key = self.key
        left_child = self.left_child
        while left_child is not None:
            min_key = min(min_key, left_child.key)
            left_child = left_child.left_child

        return min_key

    def max(self):
        max_key = self.key
        right_child = self.right_child
        while right_child is not None:
            max_key = max(max_key, right_child.key)
            right_child = right_child.right_child

        return max_key

    """
    https://withhamit.tistory.com/450
    선위순회, 중위순회, 후위순회 검증을 위한 도식 사이트
    """
    def print_pre_order(self):
        print(self.key, end=' ')

        if self.left_child is not None:
            self.left_child.print_pre_order()

        if self.right_child is not None:
            self.right_child.print_pre_order()

    def print_in_order(self):
        if self.left_child is not None:
            self.left_child.print_in_order()

        print(self.key, end=' ')

        if self.right_child is not None:
            self.right_child.print_in_order()

    def print_post_order(self):
        if self.left_child is not None:
            self.left_child.print_post_order()

        if self.right_child is not None:
            self.right_child.print_post_order()

        print(self.key, end=' ')


with open('sample_input.txt') as test_input:
    keys = list(map(int, test_input.readline().split()))
    bst = BinarySearchTree(keys[0])
    for i in range(1, len(keys)):
        bst.add(keys[i])

    bst.print_pre_order()
    print()
    bst.print_in_order()
    print()
    bst.print_post_order()

    print()
    print(bst.min())
    print(bst.max())
