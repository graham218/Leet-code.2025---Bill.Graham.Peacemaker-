"""
Problem: Sorting an Array using Different Approaches
Sorting is a fundamental operation in computer science and is used to organize data for efficient searching, retrieval, and manipulation.
Here, we implement five different sorting algorithms:

1. Merge Sort (Divide and Conquer)
2. Quick Sort (Divide and Conquer, In-Place)
3. Heap Sort (Heap Data Structure)
4. Bubble Sort (Basic Iterative Method)
5. Counting Sort (Non-Comparison Based Sorting for Bounded Integers)
"""

def merge_sort(arr):
    """
    Approach 1: Merge Sort
    Uses Divide and Conquer to recursively split and merge sorted subarrays.
    Time Complexity: O(n log n)
    Space Complexity: O(n)
    """
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    return merge(left, right)

def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def quick_sort(arr):
    """
    Approach 2: Quick Sort
    Uses partitioning to recursively sort elements.
    Time Complexity: O(n log n) (average case), O(n^2) (worst case)
    Space Complexity: O(log n) (recursive stack)
    """
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quick_sort(left) + middle + quick_sort(right)

def heap_sort(arr):
    """
    Approach 3: Heap Sort
    Uses a binary heap to extract elements in sorted order.
    Time Complexity: O(n log n)
    Space Complexity: O(1)
    """
    def heapify(arr, n, i):
        largest = i
        left = 2 * i + 1
        right = 2 * i + 2
        if left < n and arr[left] > arr[largest]:
            largest = left
        if right < n and arr[right] > arr[largest]:
            largest = right
        if largest != i:
            arr[i], arr[largest] = arr[largest], arr[i]
            heapify(arr, n, largest)

    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)
    return arr

def bubble_sort(arr):
    """
    Approach 4: Bubble Sort
    Repeatedly swaps adjacent elements if they are in the wrong order.
    Time Complexity: O(n^2)
    Space Complexity: O(1)
    """
    n = len(arr)
    for i in range(n):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def counting_sort(arr):
    """
    Approach 5: Counting Sort
    Non-comparison sorting technique used for sorting integers within a known range.
    Time Complexity: O(n + k), where k is the range of input values.
    Space Complexity: O(k)
    """
    if not arr:
        return []
    min_val, max_val = min(arr), max(arr)
    count = [0] * (max_val - min_val + 1)
    for num in arr:
        count[num - min_val] += 1
    sorted_arr = []
    for i, freq in enumerate(count):
        sorted_arr.extend([i + min_val] * freq)
    return sorted_arr

# Example usage:
arr = [5, 3, 8, 6, 2, 7, 4, 1]
print("Merge Sort:", merge_sort(arr))
print("Quick Sort:", quick_sort(arr))
print("Heap Sort:", heap_sort(arr[:]))  # Copy to avoid in-place modifications
print("Bubble Sort:", bubble_sort(arr[:]))
print("Counting Sort:", counting_sort(arr))
