"""
Problem: Advanced Sorting Algorithms for Real-World Implementations
Sorting is a fundamental operation in computer science, widely used in data processing, databases, and machine learning. Here, we implement six different sorting techniques optimized for real-world scenarios.

Approaches:
1. Merge Sort (Stable Sorting for Large Data)
2. Quick Sort (In-Place Efficient Sorting)
3. Heap Sort (Priority-Based Sorting)
4. Bucket Sort (Efficient for Floating Points and Distributed Data)
5. Radix Sort (Fast Integer Sorting)
6. Tim Sort (Hybrid Sorting Algorithm Used in Python's Built-in sort())
"""

import random

def merge_sort(arr):
    """Approach 1: Merge Sort (Divide and Conquer)"""
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    return merge(left, right)

def merge(left, right):
    """Helper function to merge two sorted halves."""
    sorted_arr = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            sorted_arr.append(left[i])
            i += 1
        else:
            sorted_arr.append(right[j])
            j += 1
    sorted_arr.extend(left[i:])
    sorted_arr.extend(right[j:])
    return sorted_arr

def quick_sort(arr):
    """Approach 2: Quick Sort (Efficient for Randomized Data)"""
    if len(arr) <= 1:
        return arr
    pivot = arr[random.randint(0, len(arr) - 1)]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def heap_sort(arr):
    """Approach 3: Heap Sort (Used in Priority Queues)"""
    import heapq
    heapq.heapify(arr)
    return [heapq.heappop(arr) for _ in range(len(arr))]

def bucket_sort(arr, bucket_size=5):
    """Approach 4: Bucket Sort (Good for Uniformly Distributed Data)"""
    if len(arr) == 0:
        return arr
    min_val, max_val = min(arr), max(arr)
    bucket_count = (max_val - min_val) // bucket_size + 1
    buckets = [[] for _ in range(bucket_count)]
    for num in arr:
        buckets[(num - min_val) // bucket_size].append(num)
    for bucket in buckets:
        bucket.sort()
    return [num for bucket in buckets for num in bucket]

def radix_sort(arr):
    """Approach 5: Radix Sort (Used for Large Integers and Strings)"""
    max_num = max(arr, default=0)
    exp = 1
    while max_num // exp > 0:
        arr = counting_sort_by_digit(arr, exp)
        exp *= 10
    return arr

def counting_sort_by_digit(arr, exp):
    """Helper function for Radix Sort."""
    output = [0] * len(arr)
    count = [0] * 10
    for num in arr:
        count[(num // exp) % 10] += 1
    for i in range(1, 10):
        count[i] += count[i - 1]
    for num in reversed(arr):
        output[count[(num // exp) % 10] - 1] = num
        count[(num // exp) % 10] -= 1
    return output

def tim_sort(arr):
    """Approach 6: Tim Sort (Hybrid Algorithm Used in Python's Built-in Sort)"""
    arr.sort()
    return arr

# Sample array for testing
arr = [34, 7, 23, 32, 5, 62, 32, 12, 11]
print("Merge Sort:", merge_sort(arr.copy()))
print("Quick Sort:", quick_sort(arr.copy()))
print("Heap Sort:", heap_sort(arr.copy()))
print("Bucket Sort:", bucket_sort(arr.copy()))
print("Radix Sort:", radix_sort(arr.copy()))
print("Tim Sort:", tim_sort(arr.copy()))
