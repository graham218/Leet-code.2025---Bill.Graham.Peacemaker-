import heapq
import statistics
import bisect
import math

def median_of_two_sorted_arrays_brute_force(nums1, nums2):
    """
    Approach 1: Brute Force - Merge and Sort
    - Time Complexity: O((m+n)log(m+n))
    - Space Complexity: O(m+n)
    - Explanation:
        1. Merge the two sorted arrays into a single array.
        2. Sort the merged array.
        3. Calculate the median of the sorted array.
    - Real-world application:
        - Useful for combining sorted data from multiple sources, like merging sorted log files
        - Can be used in database operations when joining sorted tables.
    """
    merged_array = nums1 + nums2
    merged_array.sort()  # Sort the merged array
    n = len(merged_array)
    if n % 2 == 0:
        median = (merged_array[n // 2 - 1] + merged_array[n // 2]) / 2
    else:
        median = merged_array[n // 2]
    return median

def median_of_two_sorted_arrays_two_pointers(nums1, nums2):
    """
    Approach 2: Two Pointers - Iterative Merging
    - Time Complexity: O(m+n)
    - Space Complexity: O(1)  (excluding the merged array)
    - Explanation:
        1. Use two pointers to iterate through both arrays simultaneously.
        2. Keep track of the two middle elements (or one middle element if the total length is odd).
        3. Calculate the median based on the middle elements.
    - Real-world application:
      - Used in merging sorted lists, such as in a sorted merge join in databases.
      - Efficiently combining sorted data streams, like processing sorted sensor readings.
    """
    m, n = len(nums1), len(nums2)
    merged_length = m + n
    mid = merged_length // 2
    i, j = 0, 0
    count = 0
    first_mid = 0
    second_mid = 0

    while count <= mid:
        if i < m and j < n:
            if nums1[i] < nums2[j]:
                if count == mid - 1:
                    first_mid = nums1[i]
                if count == mid:
                    second_mid = nums1[i]
                i += 1
            else:
                if count == mid - 1:
                    first_mid = nums2[j]
                if count == mid:
                    second_mid = nums2[j]
                j += 1
        elif i < m:
            if count == mid - 1:
                first_mid = nums1[i]
            if count == mid:
                second_mid = nums1[i]
            i += 1
        else:
            if count == mid - 1:
                first_mid = nums2[j]
            if count == mid:
                second_mid = nums2[j]
            j += 1
        count += 1

    if merged_length % 2 == 0:
        return (first_mid + second_mid) / 2.0
    else:
        return second_mid

def median_of_two_sorted_arrays_binary_search(nums1, nums2):
    """
    Approach 3: Binary Search - Optimized Partitioning
    - Time Complexity: O(log(min(m,n)))
    - Space Complexity: O(1)
    - Explanation:
        1. Use binary search on the smaller array to find the correct partition point.
        2. The partition point divides both arrays into two halves such that all elements in the left halves are smaller
           than or equal to the elements in the right halves.
        3. Calculate the median based on the elements around the partition.
    - Real-world application:
        - Efficiently finding split points in sorted data, relevant in database indexing.
        - Used in financial applications for finding median values in large sorted datasets.
    """
    if len(nums1) > len(nums2):
        nums1, nums2 = nums2, nums1  # Ensure nums1 is the smaller array
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
            if (m + n) % 2 == 0:
                return (max(max_left_x, max_left_y) + min(min_right_x, min_right_y)) / 2.0
            else:
                return max(max_left_x, max_left_y)
        elif max_left_x > min_right_y:
            high = partition_x - 1
        else:
            low = partition_x + 1
    return -1

def median_of_two_sorted_arrays_heapq(nums1, nums2):
    """
    Approach 4: Using heapq (Priority Queue)
    - Time Complexity: O((m+n)log(m+n))  in the worst case, but can be faster in practice due to heap optimizations
    - Space Complexity: O(m+n)
    - Explanation:
        1.  Merge the two arrays into a single array.
        2.  Create a min-heap from the merged array.
        3.  Pop elements from the heap until we reach the median position.
    - Real world application:
        - Useful when you need to find the median of continuously incoming sorted data.  The heap can be updated efficiently.
        -  Good for online algorithms where data arrives in streams.
    """
    merged_array = nums1 + nums2
    heapq.heapify(merged_array)  # Create a min-heap
    n = len(merged_array)
    mid = n // 2
    if n % 2 == 0:
        # For even length, pop two smallest and average them
        for _ in range(mid - 1):
            heapq.heappop(merged_array)
        return (heapq.heappop(merged_array) + heapq.heappop(merged_array)) / 2.0
    else:
        # For odd length, pop smallest
        for _ in range(mid):
            heapq.heappop(merged_array)
        return heapq.heappop(merged_array)

def median_of_two_sorted_arrays_statistics(nums1, nums2):
    """
    Approach 5: Using Python's statistics.median
    - Time Complexity: O(m+n)  (due to the merging)
    - Space Complexity: O(m+n)
    - Explanation:
        1. Merge the two arrays.
        2. Use Python's statistics.median() function to find the median.  This is a very concise approach.
    - Real-world application:
        -  Quickly finding the median when you have the entire merged data in memory.
        -  Useful in data analysis scripts where you need a fast, readable way to calculate the median.
    """
    merged_array = nums1 + nums2
    return statistics.median(merged_array)

def median_of_two_sorted_arrays_bisect(nums1, nums2):
    """
    Approach 6: Binary Search with bisect (Optimized)
    - Time Complexity: O(m * log(n)) or O(n * log(m)) - depends on which array is larger
    - Space Complexity: O(1)
    - Explanation:
        1. Iterate through the smaller array.
        2. For each element in the smaller array, use bisect.bisect_left to find its insertion point in the larger array.
        3. Keep track of the merged array virtually, and find the median.
    - Real-world application:
        - Useful when one array is significantly smaller than the other.
        - Can be adapted for online scenarios where elements from one array are received sequentially.
    """
    if len(nums1) > len(nums2):
        nums1, nums2 = nums2, nums1  # Ensure nums1 is the smaller array
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
            if (m + n) % 2 == 0:
                return (max(max_left_x, max_left_y) + min(min_right_x, min_right_y)) / 2.0
            else:
                return max(max_left_x, max_left_y)
        elif max_left_x > min_right_y:
            high = partition_x - 1
        else:
            low = partition_x + 1
    return -1


if __name__ == "__main__":
    nums1 = [1, 3, 8, 9, 15]
    nums2 = [7, 11, 18, 19, 21, 25]

    print("Array 1:", nums1)
    print("Array 2:", nums2)

    print("\nApproach 1: Brute Force - Merge and Sort")
    print("Median:", median_of_two_sorted_arrays_brute_force(nums1, nums2))

    print("\nApproach 2: Two Pointers - Iterative Merging")
    print("Median:", median_of_two_sorted_arrays_two_pointers(nums1, nums2))

    print("\nApproach 3: Binary Search - Optimized Partitioning")
    print("Median:", median_of_two_sorted_arrays_binary_search(nums1, nums2))

    print("\nApproach 4: Using heapq (Priority Queue)")
    print("Median:", median_of_two_sorted_arrays_heapq(nums1, nums2))

    print("\nApproach 5: Using Python's statistics.median")
    print("Median:", median_of_two_sorted_arrays_statistics(nums1, nums2))

    print("\nApproach 6: Binary Search with bisect")
    print("Median:", median_of_two_sorted_arrays_bisect(nums1, nums2))
