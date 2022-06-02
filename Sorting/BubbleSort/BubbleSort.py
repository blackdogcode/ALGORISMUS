# insertion sort 라고도 불림
import random


def insertion_sort(arr: list):
    for i in range(len(arr)):
        j = i
        while j > 0 and arr[j - 1] > arr[j]:
            arr[j - 1], arr[j] = arr[j], arr[j - 1]
            j -= 1


numbers = []
reference = []
for _ in range(50):
    num = random.randint(0, 10)
    numbers.append(num)
    reference.append(num)

insertion_sort(numbers)
reference.sort()

print(numbers)
print(reference)
print(numbers == reference)


