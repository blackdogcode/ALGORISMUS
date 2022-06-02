import random


def selection_sort(arr: list):
    for i in range(len(arr) - 1):
        min_idx, min_val = i, arr[i]
        for j in range(i + 1, len(arr)):
            if arr[j] < min_val:
                min_idx, min_val = j, arr[j]
        arr[i], arr[min_idx] = min_val, arr[i]


numbers = []
reference = []

for _ in range(50):
    num = random.randint(0, 100)
    numbers.append(num)
    reference.append(num)

selection_sort(numbers)
print(numbers)
reference.sort()
print(reference)
