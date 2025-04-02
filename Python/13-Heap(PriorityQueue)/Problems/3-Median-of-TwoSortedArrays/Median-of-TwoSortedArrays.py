import heapq
import statistics
import bisect

def find_median_naive(nums1, nums2):
    """
    Approach 1: Naive - Merge and sort.

    Time Complexity: O(m + n log(m + n))
    Space Complexity: O(m + n)
    """
    merged_array = nums1 + nums2
    merged_array.sort()  # Sort the merged array
    n = len(merged_array)
    if n % 2 == 0:
        # Even number of elements, average the two middle elements
        median = (merged_array[n // 2 - 1] + merged_array[n // 2]) / 2.0
    else:
        # Odd number of elements, take the middle element
        median = merged_array[n // 2]
    return median

def find_median_merge(nums1, nums2):
    """
    Approach 2: Merge and find median (optimized merge).

    Time Complexity: O(m + n)
    Space Complexity: O(m + n)
    """
    merged_array = []
    i, j = 0, 0
    while i < len(nums1) and j < len(nums2):
        if nums1[i] <= nums2[j]:
            merged_array.append(nums1[i])
            i += 1
        else:
            merged_array.append(nums2[j])
            j += 1
    # Add the remaining elements of nums1, if any
    merged_array.extend(nums1[i:])
    # Add the remaining elements of nums2, if any
    merged_array.extend(nums2[j:])

    n = len(merged_array)
    if n % 2 == 0:
        median = (merged_array[n // 2 - 1] + merged_array[n // 2]) / 2.0
    else:
        median = merged_array[n // 2]
    return median

def find_median_heap(nums1, nums2):
    """
    Approach 3: Using Heaps (Priority Queues).

    Time Complexity: O((m+n)log(m+n)) - due to heapify, although adding elements is log(k) where k is size of heap.
    Space Complexity: O(m + n)
    """
    merged_array = nums1 + nums2
    heapq.heapify(merged_array) # creates a min heap
    n = len(merged_array)
    for _ in range((n // 2)): # remove the smallest n//2 elements
        heapq.heappop(merged_array)

    if n % 2 == 0:
        return (heapq.heappop(merged_array) + heapq.heappop(merged_array))/2
    else:
        return heapq.heappop(merged_array)

def find_median_pythonic(nums1, nums2):
    """
    Approach 4: Using Python's statistics.median.

    Time Complexity: O(m + n) in the average case,  O(n log n) worst case (due to Timsort)
    Space Complexity: O(1) auxiliary space.
    """
    return statistics.median(nums1 + nums2)

def find_median_binary_search(nums1, nums2):
    """
    Approach 5: Binary Search (Optimal).

    Time Complexity: O(log(min(m, n)))
    Space Complexity: O(1)
    """
    if len(nums1) > len(nums2):
        nums1, nums2 = nums2, nums1  # Ensure nums1 is the shorter array for efficiency

    m, n = len(nums1), len(nums2)
    low, high = 0, m

    while low <= high:
        partition_x = (low + high) // 2
        partition_y = (m + n + 1) // 2 - partition_x

        max_left_x = float('-inf') if partition_x == 0 else nums1[partition_x - 1]
        min_right_x = float('inf') if partition_x == m else nums1[partition_x]
        max_left_y = float('-inf') if partition_y == 0 else nums2[partition_y - 1]
        min_right_y = float('inf') if partition_y == n else nums2[partition_y]

        if max_left_x <= min_right_y and max_left_y <= min_right_x:
            # Found the correct partition
            if (m + n) % 2 == 0:
                return (max(max_left_x, max_left_y) + min(min_right_x, min_right_y)) / 2.0
            else:
                return max(max_left_x, max_left_y)
        elif max_left_x > min_right_y:
            # Move towards the left in nums1
            high = partition_x - 1
        else:
            # Move towards the right in nums1
            low = partition_x + 1
    raise ValueError("Input arrays are not sorted.") # added error

# Example Usage and Output
nums1 = [1, 3]
nums2 = [2, 4]

print("Array 1:", nums1)
print("Array 2:", nums2)

print("\nApproach 1: Naive - Merge and Sort")
print("Median:", find_median_naive(nums1, nums2))

print("\nApproach 2: Merge and Find Median")
print("Median:", find_median_merge(nums1, nums2))

print("\nApproach 3: Using Heaps")
print("Median:", find_median_heap(nums1, nums2))

print("\nApproach 4: Using Python's statistics.median")
print("Median:", find_median_pythonic(nums1, nums2))

print("\nApproach 5: Binary Search")
print("Median:", find_median_binary_search(nums1, nums2))

nums3 = [1, 2]
nums4 = [3, 4, 5]
print("\nArray 3:", nums3)
print("Array 4:", nums4)

print("\nApproach 1: Naive - Merge and Sort")
print("Median:", find_median_naive(nums3, nums4))

print("\nApproach 2: Merge and Find Median")
print("Median:", find_median_merge(nums3, nums4))

print("\nApproach 3: Using Heaps")
print("Median:", find_median_heap(nums3, nums4))

print("\nApproach 4: Using Python's statistics.median")
print("Median:", find_median_pythonic(nums3, nums4))

print("\nApproach 5: Binary Search")
print("Median:", find_median_binary_search(nums3, nums4))
