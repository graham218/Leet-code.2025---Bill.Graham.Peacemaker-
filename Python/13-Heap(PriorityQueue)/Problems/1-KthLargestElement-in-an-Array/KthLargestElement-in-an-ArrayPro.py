import heapq
import random
import statistics

def find_kth_largest_heapq(nums, k):
    """
    Approach 1: Using heapq (min-heap) - Efficient for general cases, good for online processing.
    -   Maintain a min-heap of size k.
    -   Iterate through the array, if the current element is larger than the smallest in the heap,
    -   replace the smallest with the current element.
    -   The root of the heap will be the kth largest element.
    -   Time Complexity: O(N log k), Space Complexity: O(k)
    -   Real-world application: Live ranking of top k players in a game, continuously updated statistics.
    """
    heap = []
    for num in nums:
        if len(heap) < k:
            heapq.heappush(heap, num)  # Push the first k elements into the min-heap
        elif num > heap[0]:
            heapq.heapreplace(heap, num) # Replace the min (root) with the new larger number
    return heap[0]

def find_kth_largest_sorted(nums, k):
    """
    Approach 2: Using sorting - Simple but less efficient for large arrays and small k.
    -   Sort the array in descending order.
    -   The kth largest element will be at index k-1.
    -   Time Complexity: O(N log N), Space Complexity: O(1) (in-place sort) or O(N) (depending on sort)
    -   Real-world application: Finding the top k performers in a batch, where the whole batch is available at once.
    """
    nums.sort(reverse=True) # Sort the array in descending order
    return nums[k - 1]

def find_kth_largest_quickselect(nums, k):
    """
    Approach 3: QuickSelect (Hoare's selection algorithm) - Average case O(N), efficient.
    -   Choose a pivot element.
    -   Partition the array around the pivot such that elements smaller than the pivot are on the left
    -   and elements greater than the pivot are on the right.
    -   Recursively apply the partitioning to the subarray that contains the kth largest element.
    -   Time Complexity: O(N) average, O(N^2) worst case, Space Complexity: O(log N)
    -   Real-world application: Finding the median or quartiles of a dataset, database query optimization.
    """
    def partition(nums, low, high):
        pivot = nums[high]
        i = low - 1
        for j in range(low, high):
            if nums[j] <= pivot:
                i += 1
                nums[i], nums[j] = nums[j], nums[i]
        nums[i + 1], nums[high] = nums[high], nums[i + 1]
        return i + 1

    def quickselect(nums, low, high, k):
        if low <= high:
            pivot_index = partition(nums, low, high)
            if pivot_index == k - 1:
                return nums[pivot_index]
            elif pivot_index > k - 1:
                return quickselect(nums, low, pivot_index - 1, k)
            else:
                return quickselect(nums, pivot_index + 1, high, k)

    return quickselect(nums, 0, len(nums) - 1, k)

def find_kth_largest_introselect(nums, k):
    """
    Approach 4: Introselect (Hybrid of QuickSelect and HeapSort) - Guaranteed O(N) time.
        - Introselect combines the average-case efficiency of QuickSelect with the worst-case guarantee of HeapSort.
        - It starts with QuickSelect, but if the recursion depth becomes too large (indicating a bad pivot choice),
        - it switches to HeapSort to ensure O(N) time complexity.
        - Time Complexity: O(N), Space Complexity: O(log N)
        - Real world application: Used in standard library implementations (like C++'s std::nth_element)
          where both speed and worst-case guarantees are important.
    """
    def partition(nums, low, high):
        pivot = nums[high]
        i = low - 1
        for j in range(low, high):
            if nums[j] <= pivot:
                i += 1
                nums[i], nums[j] = nums[j], nums[i]
        nums[i + 1], nums[high] = nums[high], nums[i + 1]
        return i + 1

    def introselect(nums, low, high, k, max_depth):
        if low <= high:
            if max_depth == 0:  # Switch to HeapSort
                nums[low:high+1] = sorted(nums[low:high+1], reverse=True) # Sort the sub-array
                return nums[k-1]
            pivot_index = partition(nums, low, high)
            if pivot_index == k - 1:
                return nums[pivot_index]
            elif pivot_index > k - 1:
                return introselect(nums, low, pivot_index - 1, k, max_depth - 1)
            else:
                return introselect(nums, pivot_index + 1, high, k, max_depth - 1)
        return nums[k-1] #Added this to handle edge cases where low > high, k might be out of bound,

    max_depth = (len(nums).bit_length() - 1) * 2  # 2 * log2(n)
    return introselect(nums.copy(), 0, len(nums) - 1, k, max_depth) # Pass a copy to avoid modifying original

def find_kth_largest_median_of_medians(nums, k):
    """
    Approach 5: Median of Medians - Guaranteed O(N) time, but more complex.
    -   Finds a good pivot by dividing the array into chunks of 5, finding the median of each chunk,
    -   and then finding the median of those medians.
    -   This pivot is used in QuickSelect, guaranteeing linear time complexity.
    -    Time complexity: O(N), Space complexity: O(N)
    -   Real-world application:  Used in specialized selection algorithms where guaranteed linear time
        is crucial, though the constant factors make it less common than QuickSelect in general.
    """
    def find_median(arr):
        arr.sort()
        return arr[len(arr) // 2]

    def median_of_medians(arr):
        if len(arr) <= 5:
            return find_median(arr)
        medians = [find_median(arr[i:i+5]) for i in range(0, len(arr), 5)]
        return median_of_medians(medians)

    def partition(nums, low, high, pivot):
        i = low
        j = high
        while i <= j:
            while i <= j and nums[i] > pivot:
                i += 1
            while i <= j and nums[j] < pivot:
                j -= 1
            if i <= j:
                nums[i], nums[j] = nums[j], nums[i]
                i += 1
                j -= 1
        return i

    def select(arr, low, high, k):
        if low == high:
            return arr[low]
        pivot = median_of_medians(arr[low:high+1])
        pivot_index = partition(arr, low, high, pivot)
        if k == pivot_index:
            return arr[k]
        elif k < pivot_index:
            return select(arr, low, pivot_index - 1, k)
        else:
            return select(arr, pivot_index, high, k)

    return select(nums.copy(), 0, len(nums) - 1, k - 1) # Pass a copy to avoid modifying original

def find_kth_largest_statistics_module(nums, k):
    """
     Approach 6: Using Python's statistics module (for demonstration) - Simple, but not always the most efficient.
     -  Uses the `statistics.quantiles` function to find the k-th largest.
     -  This method is good for understanding statistical distributions but might not be the fastest for very large datasets
     -  Time Complexity: O(N log N) in the current implementation, Space Complexity: O(N)
     -  Real-world application: Quick data analysis and reporting, especially when combined with other statistical measures.
    """
    if not 1 <= k <= len(nums):
        raise ValueError("k is out of bounds")
    return statistics.quantiles(nums, n=len(nums) - k + 1)[0] # n is number of cuts, which is equivalent to the (N-k+1)-th smallest

if __name__ == '__main__':
    nums = [3, 1, 5, 6, 4, 2, 9, 8, 7]
    k = 3
    print(f"Array: {nums}, k: {k}")

    print("\nApproach 1: Using heapq (min-heap)")
    result1 = find_kth_largest_heapq(nums.copy(), k)
    print(f"Kth largest element: {result1}")

    print("\nApproach 2: Using sorting")
    result2 = find_kth_largest_sorted(nums.copy(), k)
    print(f"Kth largest element: {result2}")

    print("\nApproach 3: QuickSelect")
    result3 = find_kth_largest_quickselect(nums.copy(), k)
    print(f"Kth largest element: {result3}")

    print("\nApproach 4: Introselect")
    result4 = find_kth_largest_introselect(nums.copy(), k)
    print(f"Kth largest element: {result4}")

    print("\nApproach 5: Median of Medians")
    result5 = find_kth_largest_median_of_medians(nums.copy(), k)
    print(f"Kth largest element: {result5}")

    print("\nApproach 6: Using Python's statistics module")
    result6 = find_kth_largest_statistics_module(nums.copy(), k)
    print(f"Kth largest element: {result6}")
