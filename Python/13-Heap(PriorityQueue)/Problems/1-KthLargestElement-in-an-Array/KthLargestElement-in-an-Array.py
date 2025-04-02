import heapq
import random
import statistics

def find_kth_largest_heap(nums, k):
    """
    Approach 1: Using a Max-Heap (Priority Queue)

    Time Complexity: O(N log K), where N is the length of nums.  Building the heap of size K takes O(K log K), and
                     then iterating through the rest of the array and potentially replacing elements takes O((N-K) log K).
    Space Complexity: O(K), for storing the heap elements.

    Args:
        nums: The input list of numbers.
        k: The k-th largest element to find.

    Returns:
        The k-th largest element in the array.
    """
    # Create a min-heap of size k.  We use a min-heap because it's more efficient
    # to maintain a small heap of the k largest elements seen so far.
    heap = nums[:k]  # Initialize the heap with the first k elements
    heapq.heapify(heap) # Transform list into heap, in-place, in linear time

    # Iterate through the rest of the array.
    for num in nums[k:]:
        # If the current number is greater than the smallest element in the heap,
        # replace the smallest element with the current number.
        if num > heap[0]:
            heapq.heapreplace(heap, num)  # Efficiently replace and maintain heap property

    # The root of the min-heap is now the k-th largest element.
    return heap[0]

def find_kth_largest_sorting(nums, k):
    """
    Approach 2: Using Sorting

    Time Complexity: O(N log N), where N is the length of nums, due to the sorting operation.
    Space Complexity: O(1) or O(N), depending on the sorting algorithm used.  Most in-place sorts are O(1),
                      but Python's sorted() function creates a new list, so it's O(N).

    Args:
        nums: The input list of numbers.
        k: The k-th largest element to find.

    Returns:
        The k-th largest element in the array.
    """
    # Sort the array in descending order.
    sorted_nums = sorted(nums, reverse=True)  # Sort the array

    # The k-th largest element is at index k-1.
    return sorted_nums[k - 1]

def find_kth_largest_quickselect(nums, k):
    """
    Approach 3: Using QuickSelect (Partitioning)

    Time Complexity: O(N) on average, where N is the length of nums.  In the worst case (rare), it can be O(N^2),
                     but with proper pivot selection (e.g., random), the average case is linear.
    Space Complexity: O(1) in-place.

    Args:
        nums: The input list of numbers.
        k: The k-th largest element to find.

    Returns:
        The k-th largest element in the array.
    """
    def partition(left, right, pivot_index):
        """Partitions the array around the pivot."""
        pivot_value = nums[pivot_index]
        # Move pivot to the end
        nums[pivot_index], nums[right] = nums[right], nums[pivot_index]
        store_index = left
        # Move all smaller elements to the left
        for i in range(left, right):
            if nums[i] < pivot_value:
                nums[store_index], nums[i] = nums[i], nums[store_index]
                store_index += 1
        # Move pivot to its final place
        nums[right], nums[store_index] = nums[store_index], nums[right]
        return store_index

    def quickselect(left, right, k_smallest):
        """Recursively finds the k-th smallest element (which corresponds to the (n-k+1)-th largest)."""
        if left == right:
            return nums[left]

        # Choose a random pivot index
        pivot_index = random.randint(left, right)
        pivot_index = partition(left, right, pivot_index)

        # The pivot is in its correct sorted position
        if k_smallest == pivot_index:
            return nums[pivot_index]
        elif k_smallest < pivot_index:
            return quickselect(left, pivot_index - 1, k_smallest)
        else:
            return quickselect(pivot_index + 1, right, k_smallest)

    # Convert k-th largest to k-th smallest.
    k_smallest = len(nums) - k
    return quickselect(0, len(nums) - 1, k_smallest)

def find_kth_largest_nlargest(nums, k):
    """
    Approach 4: Using nlargest from heapq

    Time Complexity: O(N log K), where N is the length of nums.
    Space Complexity: O(K)

    Args:
        nums: The input list of numbers.
        k: The k-th largest element to find.

    Returns:
        The k-th largest element in the array.
    """
    # heapq.nlargest returns a list of the k largest elements.
    largest_k = heapq.nlargest(k, nums)
    return largest_k[k - 1] # return the kth largest

def find_kth_largest_statistics(nums, k):
    """
    Approach 5: Using statistics.quantiles (Median of Medians) - Available in Python 3.8+
    This approach is generally slower than QuickSelect in practice but provides a guaranteed linear time complexity.

    Time Complexity: O(N)
    Space Complexity: O(N)
    Args:
        nums: The input list of numbers
        k: the kth largest element to find

    Returns:
        The kth largest element in the array
    """
    # Convert k to the index of the kth largest element from the start
    index_of_kth_largest = len(nums) - k
    # statistics.quantiles finds the element at a given quantile.
    # We want the element that would be at the (N-k)/N quantile
    return statistics.quantiles(nums, n=len(nums))[index_of_kth_largest]
    # Note: statistics.quantiles returns a list.  For the kth *largest*, we want element at index len(nums) - k.

if __name__ == '__main__':
    # Example usage:
    numbers = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
    k = 5
    print(f"Input Array: {numbers}, k = {k}")

    # Test each approach and print the result
    result_heap = find_kth_largest_heap(numbers.copy(), k)
    print(f"Approach 1 (Heap): {result_heap}")  # Output: 4

    result_sorting = find_kth_largest_sorting(numbers.copy(), k)
    print(f"Approach 2 (Sorting): {result_sorting}")  # Output: 4

    result_quickselect = find_kth_largest_quickselect(numbers.copy(), k)
    print(f"Approach 3 (QuickSelect): {result_quickselect}")  # Output: 4

    result_nlargest = find_kth_largest_nlargest(numbers.copy(), k)
    print(f"Approach 4 (nlargest): {result_nlargest}") # Output 4

    result_statistics = find_kth_largest_statistics(numbers.copy(), k)
    print(f"Approach 5 (statistics.quantiles): {result_statistics}") # Output 4
