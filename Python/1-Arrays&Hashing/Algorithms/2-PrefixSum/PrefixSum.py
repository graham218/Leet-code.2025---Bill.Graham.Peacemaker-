"""
Problem: Prefix Sum (Multiple Approaches)
Given an integer array nums, efficiently compute prefix sums to answer range sum queries and other operations.

Approaches:
1. Naive Summation (Brute Force)
2. Precomputed Prefix Sum Array
3. Difference Array for Range Updates
4. Fenwick Tree (Binary Indexed Tree)
5. Segment Tree for Dynamic Range Queries
"""

def range_sum_brute_force(nums, left, right):
    """
    Approach 1: Naive Summation (Brute Force)
    Computes sum over range [left, right] using a simple loop.
    Time Complexity: O(n) per query
    Space Complexity: O(1)
    """
    return sum(nums[left:right+1])


def prefix_sum_array(nums):
    """
    Approach 2: Precomputed Prefix Sum Array
    Constructs a prefix sum array to answer range sum queries in O(1) time.
    Time Complexity: O(n) for preprocessing, O(1) per query
    Space Complexity: O(n)
    """
    prefix = [0] * (len(nums) + 1)
    for i in range(len(nums)):
        prefix[i+1] = prefix[i] + nums[i]
    return prefix

def range_sum_prefix(prefix, left, right):
    """
    Uses precomputed prefix array to compute range sum in O(1).
    """
    return prefix[right+1] - prefix[left]


def difference_array_update(nums, updates):
    """
    Approach 3: Difference Array for Range Updates
    Allows efficient range increment operations.
    Time Complexity: O(n) for building, O(1) per update
    Space Complexity: O(n)
    """
    diff = [0] * (len(nums) + 1)
    for left, right, val in updates:
        diff[left] += val
        if right + 1 < len(nums):
            diff[right + 1] -= val

    # Apply prefix sum to reconstruct the updated array
    for i in range(1, len(nums)):
        diff[i] += diff[i-1]
    return [nums[i] + diff[i] for i in range(len(nums))]


class FenwickTree:
    """
    Approach 4: Fenwick Tree (Binary Indexed Tree)
    Supports efficient prefix sum queries and point updates.
    Time Complexity: O(log n) per operation
    Space Complexity: O(n)
    """
    def __init__(self, n):
        self.tree = [0] * (n + 1)

    def update(self, index, value):
        while index < len(self.tree):
            self.tree[index] += value
            index += index & -index

    def prefix_sum(self, index):
        result = 0
        while index > 0:
            result += self.tree[index]
            index -= index & -index
        return result

    def range_sum(self, left, right):
        return self.prefix_sum(right) - self.prefix_sum(left - 1)


class SegmentTree:
    """
    Approach 5: Segment Tree for Dynamic Range Queries
    Allows range sum queries and point updates.
    Time Complexity: O(n) for building, O(log n) for queries and updates
    Space Complexity: O(n)
    """
    def __init__(self, nums):
        self.n = len(nums)
        self.tree = [0] * (2 * self.n)
        self.build(nums)

    def build(self, nums):
        for i in range(self.n):
            self.tree[self.n + i] = nums[i]
        for i in range(self.n - 1, 0, -1):
            self.tree[i] = self.tree[i * 2] + self.tree[i * 2 + 1]

    def update(self, index, value):
        pos = index + self.n
        self.tree[pos] = value
        while pos > 1:
            pos //= 2
            self.tree[pos] = self.tree[2 * pos] + self.tree[2 * pos + 1]

    def range_sum(self, left, right):
        left += self.n
        right += self.n
        total = 0
        while left <= right:
            if left % 2 == 1:
                total += self.tree[left]
                left += 1
            if right % 2 == 0:
                total += self.tree[right]
                right -= 1
            left //= 2
            right //= 2
        return total

# Example Usage
nums = [1, 3, 5, 7, 9, 11]
updates = [(1, 3, 2)]  # Increment elements in range [1,3] by 2
prefix = prefix_sum_array(nums)
diff_updated_nums = difference_array_update(nums, updates)
fenwick_tree = FenwickTree(len(nums))
segment_tree = SegmentTree(nums)

for i, num in enumerate(nums):
    fenwick_tree.update(i + 1, num)

print("Brute Force Range Sum:", range_sum_brute_force(nums, 1, 3))
print("Prefix Sum Array Range Sum:", range_sum_prefix(prefix, 1, 3))
print("Difference Array Update:", diff_updated_nums)
print("Fenwick Tree Range Sum:", fenwick_tree.range_sum(1, 3))
print("Segment Tree Range Sum:", segment_tree.range_sum(1, 3))
