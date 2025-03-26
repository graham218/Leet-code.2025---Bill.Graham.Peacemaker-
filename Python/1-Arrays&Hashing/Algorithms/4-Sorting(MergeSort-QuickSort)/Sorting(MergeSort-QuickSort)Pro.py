"""
Problem: Advanced Sorting Algorithms for Real-World Implementations
Sorting is a fundamental operation in computer science, widely used in data processing, databases, and machine learning.
This module implements six different sorting techniques, optimized for various real-world scenarios.  Each algorithm
is accompanied by detailed comments to explain its operation, time complexity, and suitability for different data types
and distributions.

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
    """
    Approach 1: Merge Sort (Divide and Conquer)

    Description:
    Merge sort is a stable, divide-and-conquer algorithm. It recursively divides the input array into smaller sub-arrays,
    sorts them, and then merges the sorted sub-arrays.  It guarantees a sorted output.

    Time Complexity:
    - Best:    O(n log n)
    - Average: O(n log n)
    - Worst:   O(n log n)

    Space Complexity: O(n) - Requires extra space for merging.

    Advantages:
    - Stable sort (maintains the relative order of equal elements).
    - Efficient for large datasets.
    - Performs consistently well in all cases.

    Disadvantages:
    - Requires additional memory, making it less suitable for memory-constrained environments.

    Suitable Use Cases:
    - Sorting large datasets where stability is important.
    - External sorting (sorting data that doesn't fit into memory).
    - Situations where worst-case performance needs to be guaranteed.
    """
    if len(arr) <= 1:
        return arr  # Base case: an array with 0 or 1 element is already sorted
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])  # Recursively sort the left half
    right = merge_sort(arr[mid:]) # Recursively sort the right half
    return merge(left, right)      # Merge the sorted halves

def merge(left, right):
    """
    Helper function to merge two sorted halves.

    Description:
    This function merges two sorted arrays, `left` and `right`, into a single sorted array.
    It uses two pointers, `i` and `j`, to traverse the two arrays, comparing elements and
    appending the smaller one to the `sorted_arr`.  Any remaining elements in either array
    are then appended to the result.

    Time Complexity:  O(n), where n is the total number of elements in the two input arrays.
    Space Complexity: O(n), for the `sorted_arr`.
    """
    sorted_arr = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            sorted_arr.append(left[i])
            i += 1
        else:
            sorted_arr.append(right[j])
            j += 1
    sorted_arr.extend(left[i:])  # Add any remaining elements from the left array
    sorted_arr.extend(right[j:]) # Add any remaining elements from the right array
    return sorted_arr

def quick_sort(arr):
    """
    Approach 2: Quick Sort (Efficient for Randomized Data)

    Description:
    Quick sort is an efficient, divide-and-conquer algorithm. It works by selecting a 'pivot' element
    from the array and partitioning the other elements into two sub-arrays, according to whether they are
    less than or greater than the pivot. The sub-arrays are then recursively sorted.  The choice of pivot
    is crucial to quicksort's performance.  A random pivot is used here to improve average-case performance
    and avoid worst-case scenarios with already sorted or nearly sorted data.

    Time Complexity:
    - Best:    O(n log n) - Occurs when the pivot is close to the median.
    - Average: O(n log n) - With a good pivot selection strategy (like random pivot).
    - Worst:   O(n^2)   - Occurs when the pivot is consistently the smallest or largest element.

    Space Complexity: O(log n) - Average case (due to recursive call stack).  O(n) in the worst case.
                    Quicksort is generally considered an in-place sorting algorithm
                    because the extra space needed is small compared to the input size.

    Advantages:
    - Very efficient on average.
    - In-place sorting (does not require significant extra memory).
    - Relatively simple to implement.

    Disadvantages:
    - Worst-case performance is O(n^2).
    - Not stable.
    - Performance can vary significantly depending on the pivot selection.

    Suitable Use Cases:
    - Sorting large arrays of primitive data types (integers, floats).
    - Situations where average-case performance is more important than worst-case performance.
    - When in-place sorting is desirable to minimize memory usage.
    """
    if len(arr) <= 1:
        return arr  # Base case: array with 0 or 1 element is sorted
    pivot = arr[random.randint(0, len(arr) - 1)] # Choose a random pivot
    left = [x for x in arr if x < pivot]    # Elements less than the pivot
    middle = [x for x in arr if x == pivot] # Elements equal to the pivot
    right = [x for x in arr if x > pivot]   # Elements greater than the pivot
    return quick_sort(left) + middle + quick_sort(right) # Recursively sort sub-arrays

def heap_sort(arr):
    """
    Approach 3: Heap Sort (Used in Priority Queues)

    Description:
    Heap sort is a comparison-based sorting algorithm that uses a binary heap data structure.
    It first builds a max heap from the input array, then repeatedly extracts the maximum element
    from the heap and places it at the end of the sorted portion of the array.  Heap sort is an
    efficient in-place algorithm, though not stable.

    Time Complexity:
    - Best:    O(n log n)
    - Average: O(n log n)
    - Worst:   O(n log n)

    Space Complexity: O(1) - In-place sorting.

    Advantages:
    - Guaranteed O(n log n) time complexity.
    - In-place sorting (minimal extra memory usage).
    - Works well for large datasets.

    Disadvantages:
    - Not stable.
    - Can be slightly slower than quicksort in practice.
    - Less cache-friendly than other algorithms.

    Suitable Use Cases:
    - Sorting large datasets.
    - Situations where guaranteed O(n log n) performance is required.
    - Implementing priority queues.
    """
    import heapq  # Import the heapq module for heap operations
    heapq.heapify(arr)  # Build a max heap in-place
    return [heapq.heappop(arr) for _ in range(len(arr))] # Repeatedly extract max

def bucket_sort(arr, bucket_size=5):
    """
    Approach 4: Bucket Sort (Good for Uniformly Distributed Data)

    Description:
    Bucket sort is a distribution sort that works by partitioning the input array into a number of buckets.
    Each bucket is then sorted individually, either using a different sorting algorithm or recursively
    applying bucket sort.  Bucket sort is most efficient when the input data is uniformly distributed.
    The choice of `bucket_size` can affect performance.

    Time Complexity:
    - Best:    O(n + k) - When elements are uniformly distributed (k is the number of buckets).
    - Average: O(n + k) - With uniformly distributed data.
    - Worst:   O(n^2)   - When elements are clustered in a few buckets.

    Space Complexity: O(n + k) - Requires extra space for buckets.

    Advantages:
    - Very efficient for uniformly distributed data.
    - Can be parallelized.

    Disadvantages:
    - Performance degrades with non-uniform data distribution.
    - Requires knowledge of the data distribution.
    - Extra memory is required for the buckets.

    Suitable Use Cases:
    - Sorting floating-point numbers with a uniform distribution.
    - Situations where data is known to be evenly distributed.
    - Parallel processing of large datasets.
    """
    if len(arr) == 0:
        return arr # Handle empty array
    min_val, max_val = min(arr), max(arr)
    bucket_count = (max_val - min_val) // bucket_size + 1 # Determine number of buckets
    buckets = [[] for _ in range(bucket_count)] # Create the buckets
    for num in arr:
        buckets[(num - min_val) // bucket_size].append(num) # Place elements into buckets
    for bucket in buckets:
        bucket.sort() # Sort each bucket (using insertion sort or another algorithm)
    return [num for bucket in buckets for num in bucket] # Concatenate sorted buckets

def radix_sort(arr):
    """
    Approach 5: Radix Sort (Used for Large Integers and Strings)

    Description:
    Radix sort is a non-comparison-based sorting algorithm that sorts elements by grouping the digits
    of numbers (or characters of strings) having the same significant position.  It processes digits
    from least significant to most significant.  Radix sort is efficient for integers and strings where
    the keys have a limited range.

    Time Complexity: O(nk)
    - n is the number of elements in the array.
    - k is the maximum number of digits in the elements.

    Space Complexity: O(n + k) - Requires extra space for the output array and count array.

    Advantages:
    - Very efficient for sorting integers.
    - Can be faster than comparison-based sorts for large datasets with fixed-size keys.
    - Stable sort.

    Disadvantages:
    - Only applicable to data that can be represented as digits or characters.
    - Performance depends on the length of the keys (number of digits).

    Suitable Use Cases:
    - Sorting integers.
    - Sorting strings.
    - Situations where the number of digits/characters is relatively small compared to the number of elements.
    """
    max_num = max(arr, default=0) # Find the maximum number to determine the number of digits
    exp = 1 # Start with the least significant digit (1's place)
    while max_num // exp > 0:
        arr = counting_sort_by_digit(arr, exp) # Sort by the current digit
        exp *= 10 # Move to the next significant digit (10's, 100's, etc.)
    return arr

def counting_sort_by_digit(arr, exp):
    """
    Helper function for Radix Sort.

    Description:
    This function sorts the input array `arr` based on the digit at the position specified by `exp`.
    It uses counting sort as a stable sorting algorithm to sort the elements based on this digit.

    Time Complexity: O(n + k), where n is the number of elements and k is the range of the digits (0-9).
    Space Complexity: O(n + k)
    """
    output = [0] * len(arr) # Array to store the sorted output
    count = [0] * 10      # Array to store the count of occurrences of each digit (0-9)

    # Count the occurrences of each digit at the current place value (exp)
    for num in arr:
        count[(num // exp) % 10] += 1

    # Calculate the cumulative counts (for determining the correct position in the output array)
    for i in range(1, 10):
        count[i] += count[i - 1]

    # Build the output array by placing elements in their sorted positions based on the current digit
    for num in reversed(arr): # Iterate in reverse to maintain stability
        output[count[(num // exp) % 10] - 1] = num
        count[(num // exp) % 10] -= 1

    return output

def tim_sort(arr):
    """
    Approach 6: Tim Sort (Hybrid Algorithm)

    Description:
    Tim sort is a hybrid sorting algorithm, derived from merge sort and insertion sort, designed to perform
    well on many kinds of real-world data. It works by dividing the array into blocks called 'runs'. Each run
    is sorted using insertion sort, and then the runs are merged using a merge sort-like approach. Tim sort
    exploits the fact that real-world data often has already existing ordered subsequences.  It is the default
    sorting algorithm in Python.

    Time Complexity:
    - Best:    O(n) - When the array is already sorted or nearly sorted.
    - Average: O(n log n)
    - Worst:   O(n log n)

    Space Complexity: O(n) -  In practice, it can be less than merge sort due to adaptive merging.

    Advantages:
    - Very efficient for partially sorted data.
    - Stable sort.
    - Performs well in practice on a wide variety of data.
    - Adaptable to different data distributions.

    Disadvantages:
    - More complex to implement than merge sort or insertion sort alone.

    Suitable Use Cases:
    - General-purpose sorting.
    - Replacement for other sorting algorithms.
    - Used as Python's default sorting algorithm.
    """
    arr.sort() # Use Python's built-in sort, which is implemented using Tim Sort.
    return arr

# Sample array for testing
arr = [34, 7, 23, 32, 5, 62, 32, 12, 11, 99, 87, 1, 45, 2, 100]
print("Original Array:", arr)
print("\nResults:")
print("Merge Sort:  ", merge_sort(arr.copy()))
print("Quick Sort:  ", quick_sort(arr.copy()))
print("Heap Sort:   ", heap_sort(arr.copy()))
print("Bucket Sort: ", bucket_sort(arr.copy()))
print("Radix Sort:  ", radix_sort(arr.copy()))
print("Tim Sort:    ", tim_sort(arr.copy()))
