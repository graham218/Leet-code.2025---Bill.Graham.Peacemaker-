"""
Problem: Merge Intervals (Advanced Real-World Implementations)
Given a collection of intervals, merge all overlapping intervals.

Approaches:
1. Sorting & Merging (Efficient Baseline)
2. Sweep Line Algorithm (Event Processing)
3. Interval Tree (Efficient Querying)
4. Disjoint Set Union (Union-Find for Clustering)
5. Parallel Processing (Optimized for Large Datasets)
6. Divide and Conquer (Recursive Merging)
"""

from collections import deque
from multiprocessing import Pool, cpu_count

# Approach 1: Sorting & Merging
def merge_intervals_sorting(intervals):
    intervals.sort(key=lambda x: x[0])
    merged = []
    for interval in intervals:
        if not merged or merged[-1][1] < interval[0]:
            merged.append(interval)
        else:
            merged[-1][1] = max(merged[-1][1], interval[1])
    return merged

# Approach 2: Sweep Line Algorithm
def merge_intervals_sweep_line(intervals):
    events = []
    for start, end in intervals:
        events.append((start, 1))
        events.append((end, -1))
    events.sort()
    merged, count, start = [], 0, None
    for time, delta in events:
        if count == 0:
            start = time
        count += delta
        if count == 0:
            merged.append([start, time])
    return merged

# Approach 3: Interval Tree
def merge_intervals_tree(intervals):
    intervals.sort()
    interval_tree = deque()
    for start, end in intervals:
        while interval_tree and interval_tree[-1][1] >= start:
            start = interval_tree[-1][0]
            end = max(interval_tree.pop()[1], end)
        interval_tree.append([start, end])
    return list(interval_tree)

# Approach 4: Disjoint Set Union (Union-Find)
class UnionFind:
    def __init__(self, intervals):
        self.parent = {tuple(interval): tuple(interval) for interval in intervals}
        self.rank = {tuple(interval): 1 for interval in intervals}

    def find(self, interval):
        if self.parent[interval] != interval:
            self.parent[interval] = self.find(self.parent[interval])
        return self.parent[interval]

    def union(self, interval1, interval2):
        root1, root2 = self.find(interval1), self.find(interval2)
        if root1 != root2:
            if self.rank[root1] > self.rank[root2]:
                self.parent[root2] = root1
            elif self.rank[root1] < self.rank[root2]:
                self.parent[root1] = root2
            else:
                self.parent[root2] = root1
                self.rank[root1] += 1

def merge_intervals_union_find(intervals):
    uf = UnionFind(intervals)
    for i in range(len(intervals)):
        for j in range(i + 1, len(intervals)):
            if intervals[i][1] >= intervals[j][0]:
                uf.union(tuple(intervals[i]), tuple(intervals[j]))
    merged = set(uf.find(tuple(interval)) for interval in intervals)
    return sorted(merged, key=lambda x: x[0])

# Approach 5: Parallel Processing
def merge_intervals_parallel(intervals):
    num_workers = cpu_count()
    chunk_size = max(1, len(intervals) // num_workers)
    chunks = [intervals[i:i + chunk_size] for i in range(0, len(intervals), chunk_size)]

    with Pool(num_workers) as pool:
        results = pool.map(merge_intervals_sorting, chunks)

    merged = []
    for result in results:
        merged.extend(result)

    return merge_intervals_sorting(merged)

# Approach 6: Divide and Conquer
def merge_intervals_divide_conquer(intervals):
    if len(intervals) <= 1:
        return intervals
    mid = len(intervals) // 2
    left = merge_intervals_divide_conquer(intervals[:mid])
    right = merge_intervals_divide_conquer(intervals[mid:])
    return merge_intervals_sorting(left + right)

# Test Cases
intervals = [[1, 3], [2, 6], [8, 10], [15, 18]]
print("Sorting and Merging:", merge_intervals_sorting(intervals))
print("Sweep Line Algorithm:", merge_intervals_sweep_line(intervals))
print("Interval Tree Merging:", merge_intervals_tree(intervals))
print("Disjoint Set Union:", merge_intervals_union_find(intervals))
print("Parallel Processing:", merge_intervals_parallel(intervals))
print("Divide and Conquer:", merge_intervals_divide_conquer(intervals))
