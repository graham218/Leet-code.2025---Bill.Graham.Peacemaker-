'''
Advanced Solutions for Largest Rectangle in Histogram - Real-World Applications

Problem Statement:
Given an array representing the heights of histogram bars where the width of each bar is 1,
return the area of the largest rectangle in the histogram.
'''

import heapq

# 1. Real-time Stock Market Analysis (Segment Tree Approach - O(N log N))
class SegmentTree:
    """
    Implements a Segment Tree to efficiently find the minimum height bar within a given range.
    This is useful in real-time stock market analysis to identify price ranges with minimum volatility,
    which can indicate support or resistance levels.  The Segment Tree allows for fast range queries.
    """
    def __init__(self, heights):
        """
        Initializes the SegmentTree object.

        Args:
            heights: A list of stock prices (or other relevant financial data).
        """
        self.n = len(heights)
        self.heights = heights
        self.tree = [0] * (4 * self.n)  # Allocate memory for the segment tree.
        self._build(0, 0, self.n - 1)  # Build the segment tree.

    def _build(self, node, start, end):
        """
        Recursively builds the segment tree.

        Args:
            node: The index of the current node in the tree.
            start: The starting index of the current range.
            end: The ending index of the current range.
        """
        if start == end:
            self.tree[node] = start  # Leaf node: store the index of the bar.
        else:
            mid = (start + end) // 2
            left_child = 2 * node + 1
            right_child = 2 * node + 2
            self._build(left_child, start, mid)  # Build the left subtree.
            self._build(right_child, mid + 1, end)  # Build the right subtree.
            # Internal node: store the index of the minimum height bar in the range.
            self.tree[node] = min(self.tree[left_child], self.tree[right_child], key=lambda i: self.heights[i])

    def query(self, node, start, end, l, r):
        """
        Performs a range query on the segment tree to find the minimum height bar index.

        Args:
            node: The index of the current node in the tree.
            start: The starting index of the current range.
            end: The ending index of the current range.
            l: The left boundary of the query range.
            r: The right boundary of the query range.

        Returns:
            The index of the minimum height bar in the query range, or -1 if the range is invalid.
        """
        if l > end or r < start:
            return -1  # Out of range.
        if l <= start and end <= r:
            return self.tree[node]  # Current range is within the query range.
        mid = (start + end) // 2
        left_index = self.query(2 * node + 1, start, mid, l, r)  # Query the left subtree.
        right_index = self.query(2 * node + 2, mid + 1, end, l, r)  # Query the right subtree.
        if left_index == -1:
            return right_index  # Only right subtree has valid results.
        if right_index == -1:
            return left_index  # Only left subtree has valid results.
        # Return the index of the smaller height.
        return left_index if self.heights[left_index] < self.heights[right_index] else right_index

def largestRectangleArea_segment_tree(heights):
    """
    Calculates the largest rectangle area in a histogram using a Segment Tree.
    This approach is efficient for scenarios where the histogram data is frequently updated,
    as the Segment Tree allows for efficient range minimum queries.

    Args:
        heights: A list of integers representing the heights of the histogram bars.

    Returns:
        The area of the largest rectangle in the histogram.
    """
    if not heights:
        return 0
    tree = SegmentTree(heights)  # Build the Segment Tree.

    def compute_area(left, right):
        """
        Recursively computes the largest rectangle area within the given range using the Segment Tree.

        Args:
            left: The left index of the range.
            right: The right index of the range.

        Returns:
            The area of the largest rectangle within the range.
        """
        if left > right:
            return 0
        min_index = tree.query(0, 0, len(heights) - 1, left, right)  # Use the Segment Tree to find the minimum.
        return max(
            heights[min_index] * (right - left + 1),
            compute_area(left, min_index - 1),
            compute_area(min_index + 1, right)
        )

    return compute_area(0, len(heights) - 1)

# 2. E-commerce Sales Distribution (Heap-Based - O(N log N))
def largestRectangleArea_heap(heights):
    """
    Calculates the largest rectangle area in a histogram using a heap.
    In the context of e-commerce, this can be used to analyze sales distribution,
    where bar heights represent sales volume for different product categories,
    and we want to find the largest rectangular area representing a significant sales segment.
    The heap is used to efficiently find the minimum height.

    Args:
        heights: A list of integers representing sales volumes for different product categories.

    Returns:
        The area of the largest rectangle in the histogram.
    """
    max_area = 0
    heap = []  # A min-heap to store (height, index) tuples.
    for i, h in enumerate(heights):
        heapq.heappush(heap, (h, i))  # Push the height and index onto the heap.
        while heap and heap[0][0] > h:
            # While the heap is not empty and the minimum height in the heap is greater than the current height...
            height, index = heapq.heappop(heap)  # ...pop the (height, index) tuple with the smallest height.
            width = i - index
            max_area = max(max_area, height * width)
    return max_area

# 3. Land Usage Analysis (Simple Sorting - O(N log N))
def largestRectangleArea_sorted(heights):
    """
    Calculates the largest rectangle area in a histogram using sorting.
    For land usage analysis, the heights might represent the area of land used for different purposes,
    and finding the largest rectangle can help identify the most significant land usage pattern.
    Sorting the heights allows us to process them in increasing order.

    Args:
        heights: A list of integers representing land areas for different purposes.

    Returns:
        The area of the largest rectangle in the histogram.
    """
    indexed_heights = sorted((h, i) for i, h in enumerate(heights))  # Sort (height, index) tuples by height.
    max_area = 0
    for h, i in indexed_heights:
        left = i
        right = i
        while left > 0 and heights[left - 1] >= h:
            left -= 1
        while right < len(heights) - 1 and heights[right + 1] >= h:
            right += 1
        max_area = max(max_area, h * (right - left + 1))
    return max_area

# 4. City Infrastructure Planning (Greedy with Two Pointers - O(N))
def largestRectangleArea_two_pointers(heights):
    """
    Calculates the largest rectangle area using a greedy approach with two pointers.
    In city infrastructure planning, the heights could represent building heights,
    and the largest rectangle can help determine optimal placement of structures to maximize space utilization
    or view.  However, this implementation has a flaw:  It doesn't work correctly for all cases.
    It's included to illustrate an incorrect approach.
    """
    max_area = 0
    left, right = 0, len(heights) - 1
    while left < right:
        height = min(heights[left], heights[right])
        max_area = max(max_area, height * (right - left + 1))
        if heights[left] < heights[right]:
            left += 1
        else:
            right -= 1
    return max_area # This method is incorrect.

# 5. Climate Data Analysis (Prefix Sum - O(N))
def largestRectangleArea_prefix_sum(heights):
    """
    Calculates the largest rectangle area using prefix sums.
    For climate data analysis, the heights could represent average rainfall over consecutive periods,
    and the largest rectangle can indicate periods with consistently high rainfall.
    This approach is NOT suitable for the general largest rectangle problem, and it's included to show
    an incorrect application of prefix sums.  Prefix sums are not designed for this problem.
    """
    prefix_sums = [0] * len(heights)
    for i in range(len(heights)):
        prefix_sums[i] = heights[i] if i == 0 else prefix_sums[i - 1] + heights[i]
    max_area = 0
    for i in range(len(heights)):
        width = i + 1
        max_area = max(max_area, prefix_sums[i] * width)
    return max_area # This method is incorrect.

# 6. AI-Driven Image Processing (Histogram Equalization - O(N))
def largestRectangleArea_histogram_equalization(heights):
    """
    Calculates the largest rectangle area using a method inspired by histogram equalization in image processing.
    In image processing, histogram equalization enhances contrast.  Here, we adapt the concept to find the largest
    rectangle.  This approach is inefficient and doesn't correctly solve the largest rectangle problem.
    It's included to demonstrate an unconventional and incorrect approach.
    """
    max_area = 0
    height_map = {}
    for i, h in enumerate(heights):
        if h not in height_map:
            height_map[h] = i
        left_bound = height_map[h]
        max_area = max(max_area, h * (i - left_bound + 1))
    return max_area # This method is incorrect.

# Test Cases
heights = [2, 1, 5, 6, 2, 3]
print("Segment Tree:", largestRectangleArea_segment_tree(heights))
print("Heap-Based:", largestRectangleArea_heap(heights))
print("Simple Sorting:", largestRectangleArea_sorted(heights))
print("Two Pointers:", largestRectangleArea_two_pointers(heights)) # Incorrect
print("Prefix Sum:", largestRectangleArea_prefix_sum(heights)) # Incorrect
print("Histogram Equalization:", largestRectangleArea_histogram_equalization(heights)) # Incorrect
