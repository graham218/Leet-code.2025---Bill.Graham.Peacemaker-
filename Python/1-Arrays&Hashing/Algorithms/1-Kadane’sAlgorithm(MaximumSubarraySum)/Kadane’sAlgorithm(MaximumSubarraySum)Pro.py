from multiprocessing import Pool, cpu_count
import threading
import itertools

"""
Problem: Maximum Subarray Sum (Advanced Real-World Implementations)
Given an integer array nums, find the contiguous subarray (containing at least one number) that has the largest sum and return its sum.

Approaches:
1. Kadane’s Algorithm (Classic DP Solution)
2. Divide and Conquer with Memory Optimization
3. Segment Tree for Dynamic Range Query
4. Parallel Computation using Multi-threading
5. Fenwick Tree (Binary Indexed Tree) for Efficient Queries
6. Dynamic Sliding Window for Real-time Processing
"""

# Approach 1: Kadane’s Algorithm (Classic DP Solution)
def max_subarray_kadane(nums):
    """
    Finds the maximum subarray sum using Kadane's algorithm.

    Args:
        nums: A list of integers.

    Returns:
        The maximum subarray sum.

    Explanation:
        Kadane's algorithm is a dynamic programming approach.  It iterates through
        the array, keeping track of the maximum sum ending at the current position.
        It maintains two variables:
        -   `current_sum`:  The sum of the current subarray being considered.
        -   `max_sum`: The maximum sum found so far.

        For each element in the array, it decides whether to extend the current subarray
        (if adding the element increases the sum) or start a new subarray from the
        current element.  It then updates `max_sum` if the current subarray's sum
        is greater.  This approach is efficient with O(n) time complexity.
    """
    max_sum = current_sum = nums[0]  # Initialize with the first element
    for num in nums[1:]:
        # Decide to extend the current subarray or start a new one
        current_sum = max(num, current_sum + num)
        # Update the maximum sum found so far
        max_sum = max(max_sum, current_sum)
    return max_sum

# Approach 2: Divide and Conquer with Memory Optimization
def max_crossing_sum(nums, left, mid, right):
    """
    Finds the maximum subarray sum that crosses the midpoint.

    Args:
        nums: A list of integers.
        left: The left index of the subarray.
        mid: The midpoint index of the subarray.
        right: The right index of the subarray.

    Returns:
        The maximum crossing subarray sum.

    Explanation:
        This helper function finds the maximum sum of a subarray that crosses the
        midpoint of the given array segment.  It works by finding the maximum sum
        of a subarray ending at the midpoint and the maximum sum of a subarray
        starting from the midpoint + 1.  The sum of these two maximums is the
        maximum crossing subarray sum.
    """
    left_sum = float('-inf')
    temp_sum = 0
    # Iterate from the midpoint to the left, finding the max sum ending at mid
    for i in range(mid, left - 1, -1):
        temp_sum += nums[i]
        left_sum = max(left_sum, temp_sum)

    right_sum = float('-inf')
    temp_sum = 0
    # Iterate from the midpoint + 1 to the right, finding the max sum starting from mid+1
    for i in range(mid + 1, right + 1):
        temp_sum += nums[i]
        right_sum = max(right_sum, temp_sum)

    return left_sum + right_sum  # Return the sum of the two maximums

def max_subarray_divide_conquer(nums, left, right):
    """
    Finds the maximum subarray sum using the divide and conquer approach.

    Args:
        nums: A list of integers.
        left: The left index of the subarray.
        right: The right index of the subarray.

    Returns:
        The maximum subarray sum.

    Explanation:
        This function recursively divides the input array into two halves,
        calculates the maximum subarray sum for each half, and then calculates
        the maximum subarray sum that crosses the midpoint.  The maximum of
        these three values is the maximum subarray sum for the given array
        segment.  This approach has a time complexity of O(n log n).
    """
    if left == right:
        return nums[left]  # Base case: single element array
    mid = (left + right) // 2
    # Recursively find max subarray sum for the left and right halves
    left_max = max_subarray_divide_conquer(nums, left, mid)
    right_max = max_subarray_divide_conquer(nums, mid + 1, right)
    # Find the max crossing subarray sum
    cross_max = max_crossing_sum(nums, left, mid, right)
    # Return the maximum of the three values
    return max(left_max, right_max, cross_max)

# Approach 3: Segment Tree for Dynamic Range Query
class SegmentTree:
    """
    A segment tree for efficient range queries.

    Attributes:
        n: The size of the input array.
        tree: The segment tree array.
    """
    def __init__(self, nums):
        """
        Initializes the segment tree.

        Args:
            nums: A list of integers.
        """
        self.n = len(nums)
        self.tree = [0] * (4 * self.n)  # Allocate memory for the tree (size is 4*n in worst case)
        self.build(nums, 0, 0, self.n - 1)

    def build(self, nums, node, start, end):
        """
        Builds the segment tree recursively.

        Args:
            nums: The input array.
            node: The current node index in the segment tree.
            start: The start index of the current segment in the input array.
            end: The end index of the current segment in the input array.

        Explanation:
            This function recursively builds the segment tree.  Each node in the
            segment tree stores the maximum value in the corresponding segment
            of the input array.  The base case is when the segment contains a
            single element.
        """
        if start == end:
            self.tree[node] = nums[start]  # Leaf node: store the array element
        else:
            mid = (start + end) // 2
            # Recursively build the left and right subtrees
            self.build(nums, 2 * node + 1, start, mid)
            self.build(nums, 2 * node + 2, mid + 1, end)
            # Internal node: store the maximum of its children
            self.tree[node] = max(self.tree[2 * node + 1], self.tree[2 * node + 2])

    def query(self, l, r, node=0, start=0, end=None):
        """
        Performs a range query on the segment tree.

        Args:
            l: The left index of the query range in the input array.
            r: The right index of the query range in the input array.
            node: The current node index in the segment tree.
            start: The start index of the current segment.
            end: The end index of the current segment.

        Returns:
            The maximum value in the query range.

        Explanation:
            This function performs a range query on the segment tree to find the
            maximum value in the subarray nums[l:r+1].  It recursively traverses
            the tree, checking for three cases:
            -   The query range is completely outside the current segment.
            -   The query range is completely inside the current segment.
            -   The query range overlaps the current segment.
        """
        if end is None:
            end = self.n - 1  # Initialize end for the first call
        if r < start or l > end:
            return float('-inf')  # Query range is outside the current segment
        if l <= start and end <= r:
            return self.tree[node]  # Current segment is completely inside the query range
        mid = (start + end) // 2
        # Recursively query the left and right subtrees and return the maximum
        return max(
            self.query(l, r, 2 * node + 1, start, mid),
            self.query(l, r, 2 * node + 2, mid + 1, end),
        )

# Approach 4: Parallel Computation using Multi-threading
def max_subarray_threaded(nums):
    """
    Finds the maximum subarray sum using multi-threading.

    Args:
        nums: A list of integers.

    Returns:
        The maximum subarray sum.

    Explanation:
        This function divides the input array into chunks and processes each chunk
        in a separate thread.  It uses Kadane's algorithm to find the maximum
        subarray sum for each chunk.  Finally, it combines the results from all
        threads to find the overall maximum subarray sum.  This approach can
        improve performance for very large arrays by utilizing multiple CPU cores.
    """
    num_threads = cpu_count()  # Get the number of CPU cores
    chunk_size = len(nums) // num_threads  # Calculate the size of each chunk
    results = [float('-inf')] * num_threads  # Store the results from each thread

    def process_chunk(start, end, index):
        """
        Helper function to process a chunk of the array.

        Args:
            start: The start index of the chunk.
            end: The end index of the chunk.
            index: The index of the result in the results list.
        """
        results[index] = max_subarray_kadane(nums[start:end])  # Use Kadane's for each chunk

    threads = []
    for i in range(num_threads):
        start = i * chunk_size
        end = len(nums) if i == num_threads - 1 else (i + 1) * chunk_size
        thread = threading.Thread(target=process_chunk, args=(start, end, i))
        threads.append(thread)
        thread.start()  # Start the thread

    for thread in threads:
        thread.join()  # Wait for all threads to finish

    return max(results)  # Return the maximum of all chunk results

# Approach 5: Fenwick Tree (Binary Indexed Tree) for Efficient Queries
class FenwickTree:
    """
    A Fenwick tree (Binary Indexed Tree) for efficient prefix sum queries.

    Attributes:
        n: The size of the input array.
        tree: The Fenwick tree array.
    """
    def __init__(self, nums):
        """
        Initializes the Fenwick tree.

        Args:
            nums: A list of integers.
        """
        self.n = len(nums)
        self.tree = [0] * (self.n + 1)  # Initialize the tree with zeros
        for i, num in enumerate(nums):
            self.update(i, num)  # Build the Fenwick tree

    def update(self, index, value):
        """
        Updates the Fenwick tree with a new value.

        Args:
            index: The index of the value to update (0-based).
            value: The value to add to the element at index.
        """
        index += 1  # Fenwick tree uses 1-based indexing
        while index <= self.n:
            self.tree[index] += value
            index += index & -index  # Move to the next node to update

    def prefix_sum(self, index):
        """
        Calculates the prefix sum up to the given index.

        Args:
            index: The index up to which to calculate the prefix sum (0-based).

        Returns:
            The prefix sum.
        """
        index += 1  # Fenwick tree uses 1-based indexing
        result = 0
        while index > 0:
            result += self.tree[index]
            index -= index & -index  # Move to the parent node
        return result

    def range_query(self, left, right):
        """
        Calculates the sum of the range [left, right] (inclusive).

        Args:
            left: The left index of the range (0-based).
            right: The right index of the range (0-based).

        Returns:
            The sum of the elements in the given range.
        """
        return self.prefix_sum(right) - self.prefix_sum(left - 1) # Range sum using prefix sums

# Approach 6: Dynamic Sliding Window for Real-time Processing
def max_subarray_sliding_window(nums):
    """
    Finds the maximum subarray sum using a dynamic sliding window.

    Args:
        nums: A list of integers.

    Returns:
        The maximum subarray sum.

    Explanation:
        This approach uses a sliding window to find the maximum subarray sum.
        It expands the window to the right and contracts it from the left when
        the current sum becomes negative.  This is useful for real-time processing
        where the array is continuously updated.
    """
    left = 0
    max_sum = float('-inf')
    current_sum = 0
    for right in range(len(nums)):
        current_sum += nums[right]  # Expand the window
        while current_sum < 0 and left <= right:
            current_sum -= nums[left]  # Contract the window
            left += 1
        max_sum = max(max_sum, current_sum)  # Update the maximum sum
    return max_sum

# Test cases
nums = [3, -1, 4, -1, 2, -5, 4]
print("Kadane’s Algorithm:", max_subarray_kadane(nums))
print("Divide and Conquer:", max_subarray_divide_conquer(nums, 0, len(nums) - 1))
seg_tree = SegmentTree(nums)
print("Segment Tree Query (0,5):", seg_tree.query(0, 5))
print("Parallel Processing:", max_subarray_threaded(nums))
fenwick_tree = FenwickTree(nums)
print("Fenwick Tree Range Query (0,5):", fenwick_tree.range_query(0, 5))
print("Sliding Window:", max_subarray_sliding_window(nums))
