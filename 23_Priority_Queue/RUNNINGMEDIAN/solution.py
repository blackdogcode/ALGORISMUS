import heapq

with open('sample_input.txt') as test_input:
    test_case = int(test_input.readline())
    for _ in range(test_case):
        n, a, b = map(int, test_input.readline().split())
        min_heap = []
        heapq.heapify(min_heap)
        max_heap = []
        heapq.heapify(max_heap)

        numbers, mod = [1983], 20090711
        for i in range(1, n):
            numbers.append((numbers[i - 1] * a + b) % mod)

        ret = 0
        for i in range(0, n):
            num = numbers[i]
            if len(max_heap) == len(min_heap):
                heapq.heappush(max_heap, -num)
            else:
                heapq.heappush(min_heap, +num)

            if len(min_heap) != 0 and len(max_heap) != 0 and -max_heap[0] > min_heap[0]:
                a, b = -heapq.heappop(max_heap), heapq.heappop(min_heap)
                heapq.heappush(max_heap, -b)
                heapq.heappush(min_heap, +a)

            ret = (ret + -max_heap[0]) % mod
        print(ret)



