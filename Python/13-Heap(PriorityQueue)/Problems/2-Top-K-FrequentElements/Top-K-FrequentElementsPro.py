import heapq
from collections import Counter
from typing import List, Dict
import random
import time

def generate_random_list(size: int, min_val: int, max_val: int) -> List[int]:
    """
    Generates a list of random integers within a specified range.

    Args:
        size: The number of elements in the list.
        min_val: The minimum possible value of an element.
        max_val: The maximum possible value of an element.

    Returns:
        A list of random integers.
    """
    return [random.randint(min_val, max_val) for _ in range(size)]

def verify_top_k(nums: List[int], k: int, result: List[int]) -> bool:
    """
    Verifies that the given result list contains the top k most frequent elements from the input list.

    Args:
        nums: The original list of numbers.
        k: The number of top frequent elements to check.
        result: The list of elements to verify.

    Returns:
        True if the result is correct, False otherwise.
    """
    counts = Counter(nums)
    expected_top_k = [item for item, _ in counts.most_common(k)]
    # Convert both lists to sets for order-insensitive comparison
    return set(result) == set(expected_top_k)

def run_and_verify(func, nums: List[int], k: int, approach_name: str):
    """
    Runs a given function, measures its execution time, verifies the result, and prints the results.

    Args:
        func: The function to run (one of the top-k finding algorithms).
        nums: The input list of numbers.
        k: The number of top frequent elements to find.
        approach_name: The name of the approach being tested.
    """
    start_time = time.time()
    result = func(nums, k)
    end_time = time.time()
    execution_time = end_time - start_time

    is_correct = verify_top_k(nums, k, result)
    print(f"\n{approach_name}:")
    print(f"  Result: {result}")
    print(f"  Time: {execution_time:.6f} seconds")
    print(f"  Correct: {is_correct}")
    return execution_time # Return execution time for comparison

# Approach 1: Using Counter and most_common
def top_k_frequent_counter(nums: List[int], k: int) -> List[int]:
    """
    Finds the top k frequent elements in a list using Python's Counter class.

    This approach leverages the Counter class from the collections module, which efficiently
    counts the occurrences of each element in the list. The most_common method of Counter
    then returns the k most frequent elements directly.  This is often the most efficient
    and Pythonic way to solve this problem.

    Args:
        nums: The input list of integers.
        k: The number of top frequent elements to find.

    Returns:
        A list of the top k frequent elements.
    """
    counts = Counter(nums)  # Count occurrences of each element
    return [item for item, _ in counts.most_common(k)] # Get the top k elements

# Approach 2: Using a Min-Heap (Priority Queue)
def top_k_frequent_heap(nums: List[int], k: int) -> List[int]:
    """
    Finds the top k frequent elements using a min-heap (priority queue).

    This approach uses a min-heap to keep track of the k most frequent elements
    encountered so far.  The heap always stores the k largest frequencies.
    For each element, we get its frequency.  If the heap has fewer than k elements,
    we add the (frequency, element) pair to the heap.  If the heap is full, we
    compare the current element's frequency with the smallest frequency in the heap
    (the root of the min-heap).  If the current frequency is greater, we pop the
    smallest element from the heap and push the current element.  This ensures that
    the heap always contains the k elements with the highest frequencies.

    Args:
        nums: The input list of integers.
        k: The number of top frequent elements to find.

    Returns:
        A list of the top k frequent elements.
    """
    counts = Counter(nums)  # Count occurrences of each element
    heap = []  # Initialize an empty min-heap

    for element, frequency in counts.items():
        if len(heap) < k:
            heapq.heappush(heap, (frequency, element))  # Push (frequency, element)
        elif frequency > heap[0][0]:  # If current frequency is greater than the smallest in the heap
            heapq.heappop(heap)      # Remove the smallest
            heapq.heappush(heap, (frequency, element))  # Add the current

    # The heap now contains the k most frequent elements.
    # Extract the elements from the heap (the frequencies are not needed in the result).
    return [element for _, element in heap]

# Approach 3: Using Sorting
def top_k_frequent_sorting(nums: List[int], k: int) -> List[int]:
    """
    Finds the top k frequent elements by sorting element frequencies.

    This approach counts the frequency of each element and then sorts the elements
    based on their frequencies in descending order.  The first k elements in the
    sorted list are the top k frequent elements.  While simple, sorting is generally
    less efficient than using a min-heap (especially for large lists) because sorting
    has a time complexity of O(n log n), where n is the number of unique elements.

    Args:
        nums: The input list of integers.
        k: The number of top frequent elements to find.

    Returns:
        A list of the top k frequent elements.
    """
    counts = Counter(nums)  # Count occurrences of each element
    sorted_counts = sorted(counts.items(), key=lambda item: item[1], reverse=True)  # Sort by frequency
    return [item[0] for item in sorted_counts[:k]]  # Get the top k elements

# Approach 4: Using Bucket Sort
def top_k_frequent_bucket_sort(nums: List[int], k: int) -> List[int]:
    """
    Finds the top k frequent elements using bucket sort.

    This approach uses a technique called "bucket sort".  It's efficient when the range
    of frequencies is not very large.  We create a list of "buckets" where the index
    of each bucket represents a frequency.  We iterate through the input list, count
    the frequency of each element, and place each element into the bucket corresponding
    to its frequency.  Then, we iterate through the buckets in reverse order (highest
    frequency to lowest) and collect the top k elements.

    Args:
        nums: The input list of integers.
        k: The number of top frequent elements to find.

    Returns:
        A list of the top k frequent elements.
    """
    counts = Counter(nums)  # Count occurrences of each element
    max_frequency = max(counts.values())  # Find the maximum frequency
    buckets = [[] for _ in range(max_frequency + 1)]  # Create buckets

    for element, frequency in counts.items():
        buckets[frequency].append(element)  # Place elements in buckets

    result = []
    for i in range(max_frequency, 0, -1):  # Iterate through buckets in reverse order
        for element in buckets[i]:
            result.append(element)
            if len(result) == k:
                return result
    return result

# Approach 5: Using QuickSelect (Partial Sort)
import random

def top_k_frequent_quickselect(nums: List[int], k: int) -> List[int]:
    """
    Finds the top k frequent elements using the QuickSelect algorithm.

    This approach uses the QuickSelect algorithm, a selection algorithm to find the kth
    largest element in an unordered list.  It's similar to QuickSort, but it only
    partitions the list until the kth largest element is found, making it more efficient
    than fully sorting the list.  In this case, we use QuickSelect to find the k elements
    with the highest frequencies.

    Args:
        nums: The input list of integers.
        k: The number of top frequent elements to find.

    Returns:
        A list of the top k frequent elements.
    """
    counts = Counter(nums)  # Count occurrences of each element
    unique_elements = list(counts.keys())

    def partition(left, right, pivot_index):
        """Partitions the unique elements list based on frequency."""
        pivot_frequency = counts[unique_elements[pivot_index]]
        # Move pivot to the end
        unique_elements[pivot_index], unique_elements[right] = unique_elements[right], unique_elements[pivot_index]
        store_index = left

        # Move all elements with frequency > pivot_frequency to the left
        for i in range(left, right):
            if counts[unique_elements[i]] > pivot_frequency:
                unique_elements[store_index], unique_elements[i] = unique_elements[i], unique_elements[store_index]
                store_index += 1

        # Move pivot to its correct position
        unique_elements[right], unique_elements[store_index] = unique_elements[store_index], unique_elements[right]
        return store_index

    def quickselect(left, right, k_smallest):
        """Recursively finds the kth largest element (based on frequency)."""
        if left == right:
            return  # Base case: only one element

        # Select a random pivot index
        pivot_index = random.randint(left, right)
        pivot_index = partition(left, right, pivot_index)

        # The pivot is in its correct sorted position
        if k_smallest == pivot_index:
            return  # Found the kth largest
        elif k_smallest < pivot_index:
            # Search in the left partition
            quickselect(left, pivot_index - 1, k_smallest)
        else:
            # Search in the right partition
            quickselect(pivot_index + 1, right, k_smallest)

    n = len(unique_elements)
    # Find the (n - k)th largest frequency element.  The top k frequent elements
    # are the k elements *before* the (n-k)th largest.
    quickselect(0, n - 1, n - k)
    # Return the last k elements, which are the top k frequent ones
    return unique_elements[n - k:]

# Approach 6: Using a Dictionary and Sorting (Simplified)
def top_k_frequent_dict_sort(nums: List[int], k: int) -> List[int]:
    """
    Finds the top k frequent elements using a dictionary and sorting (simplified).

    This approach is a simplified version of the sorting approach.  It uses a dictionary
    to store the frequencies of the elements and then sorts the dictionary items
    (element-frequency pairs) based on the frequencies.  This is similar to Approach 3
    but uses a plain dictionary instead of the Counter class.

    Args:
        nums: The input list of integers.
        k: The number of top frequent elements to find.

    Returns:
        A list of the top k frequent elements.
    """
    counts: Dict[int, int] = {}  # Use a regular dictionary
    for num in nums:
        counts[num] = counts.get(num, 0) + 1  # Increment counts

    sorted_counts = sorted(counts.items(), key=lambda item: item[1], reverse=True)
    return [item[0] for item in sorted_counts[:k]]

if __name__ == "__main__":
    # Example usage:
    nums = [1, 1, 1, 2, 2, 3, 2, 4, 4, 4, 4, 5, 5]
    k = 2
    print(f"Input List: {nums}, k = {k}")
    print("Finding the top k frequent elements using different approaches:")

    # Generate a larger random list for more robust timing comparisons
    large_nums = generate_random_list(10000, 1, 1000)
    k_large = 200  # Find the top 200 frequent elements in the large list

    # Run and verify each approach, and store the execution times
    execution_times = {}
    execution_times['Counter'] = run_and_verify(top_k_frequent_counter, large_nums, k_large, "Approach 1: Counter")
    execution_times['Heap'] = run_and_verify(top_k_frequent_heap, large_nums, k_large, "Approach 2: Heap")
    execution_times['Sorting'] = run_and_verify(top_k_frequent_sorting, large_nums, k_large, "Approach 3: Sorting")
    execution_times['Bucket Sort'] = run_and_verify(top_k_frequent_bucket_sort, large_nums, k_large, "Approach 4: Bucket Sort")
    execution_times['QuickSelect'] = run_and_verify(top_k_frequent_quickselect, large_nums, k_large, "Approach 5: QuickSelect")
    execution_times['Dict Sort'] = run_and_verify(top_k_frequent_dict_sort, large_nums, k_large, "Approach 6: Dict and Sort")

    # Find the fastest approach
    fastest_approach = min(execution_times, key=execution_times.get)
    print(f"\nFastest Approach: {fastest_approach} with a time of {execution_times[fastest_approach]:.6f} seconds")
