"""
Problem: Prefix Sum (Advanced Real-World Implementations)
Given an integer array nums, efficiently compute prefix sums for various operations.

Approaches:
1. Simple Prefix Sum Array (Basic Implementation)
2. Immutable Prefix Sum Query (Precomputed for Fast Access)
3. Dynamic Prefix Sum with Fenwick Tree (Binary Indexed Tree - Efficient Updates)
4. Prefix Sum using Segment Tree (Efficient Range Queries & Updates)
5. Cumulative XOR Prefix Sum (Used for XOR-related queries in security applications)
6. Prefix Sum for 2D Matrices (Optimized for Image Processing & Grid-based Computations)
"""

class PrefixSum:
    """
    Approach 1: Simple Prefix Sum Array
    Time Complexity: O(n) for precompute, O(1) for query
    Space Complexity: O(n)
    """
    def __init__(self, nums):
        self.prefix = [0] * (len(nums) + 1)
        for i in range(len(nums)):
            self.prefix[i + 1] = self.prefix[i] + nums[i]

    def range_sum(self, left, right):
        return self.prefix[right + 1] - self.prefix[left]

class FenwickTree:
    """
    Approach 2: Fenwick Tree (Binary Indexed Tree)
    Efficient for dynamic updates and queries.
    Time Complexity: O(log n) for update and query
    Space Complexity: O(n)
    """
    def __init__(self, nums):
        self.n = len(nums)
        self.tree = [0] * (self.n + 1)
        for i, num in enumerate(nums):
            self.update(i, num)

    def update(self, index, delta):
        index += 1
        while index <= self.n:
            self.tree[index] += delta
            index += index & -index

    def query(self, index):
        total = 0
        index += 1
        while index > 0:
            total += self.tree[index]
            index -= index & -index
        return total

    def range_sum(self, left, right):
        return self.query(right) - self.query(left - 1)

class SegmentTree:
    """
    Approach 3: Segment Tree
    Used for efficient range sum queries and updates.
    Time Complexity: O(log n) for updates and queries
    Space Complexity: O(n)
    """
    def __init__(self, nums):
        self.n = len(nums)
        self.tree = [0] * (4 * self.n)
        self.build(nums, 0, 0, self.n - 1)

    def build(self, nums, node, left, right):
        if left == right:
            self.tree[node] = nums[left]
        else:
            mid = (left + right) // 2
            self.build(nums, 2 * node + 1, left, mid)
            self.build(nums, 2 * node + 2, mid + 1, right)
            self.tree[node] = self.tree[2 * node + 1] + self.tree[2 * node + 2]

    def range_sum(self, node, start, end, left, right):
        if left > end or right < start:
            return 0
        if left <= start and end <= right:
            return self.tree[node]
        mid = (start + end) // 2
        return self.range_sum(2 * node + 1, start, mid, left, right) + self.range_sum(2 * node + 2, mid + 1, end, left, right)

    def query(self, left, right):
        return self.range_sum(0, 0, self.n - 1, left, right)

class PrefixXOR:
    """
    Approach 4: Cumulative XOR Prefix Sum
    Used in cryptography and network security.
    Time Complexity: O(n) for precompute, O(1) for query
    Space Complexity: O(n)
    """
    def __init__(self, nums):
        self.prefix = [0] * (len(nums) + 1)
        for i in range(len(nums)):
            self.prefix[i + 1] = self.prefix[i] ^ nums[i]

    def range_xor(self, left, right):
        return self.prefix[right + 1] ^ self.prefix[left]

class MatrixPrefixSum:
    """
    Approach 5: 2D Matrix Prefix Sum
    Used in image processing and GIS systems.
    Time Complexity: O(n*m) for precompute, O(1) for query
    Space Complexity: O(n*m)
    """
    def __init__(self, matrix):
        self.rows, self.cols = len(matrix), len(matrix[0])
        self.prefix = [[0] * (self.cols + 1) for _ in range(self.rows + 1)]
        for i in range(self.rows):
            for j in range(self.cols):
                self.prefix[i + 1][j + 1] = matrix[i][j] + self.prefix[i][j + 1] + self.prefix[i + 1][j] - self.prefix[i][j]

    def sum_region(self, row1, col1, row2, col2):
        return (self.prefix[row2 + 1][col2 + 1] - self.prefix[row1][col2 + 1] - self.prefix[row2 + 1][col1] + self.prefix[row1][col1])

# Test cases
nums = [1, 2, 3, 4, 5]
prefix = PrefixSum(nums)
print("Simple Prefix Sum:", prefix.range_sum(1, 3))

fenwick = FenwickTree(nums)
print("Fenwick Tree Range Sum:", fenwick.range_sum(1, 3))

seg_tree = SegmentTree(nums)
print("Segment Tree Range Sum:", seg_tree.query(1, 3))

xor_prefix = PrefixXOR(nums)
print("Cumulative XOR Prefix:", xor_prefix.range_xor(1, 3))

matrix = [[1, 2], [3, 4]]
matrix_prefix = MatrixPrefixSum(matrix)
print("2D Matrix Prefix Sum:", matrix_prefix.sum_region(0, 0, 1, 1))
