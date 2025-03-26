from collections import deque

def merge_intervals_sorting(intervals):
    """
    Approach 1: Sorting and Merging
    Time Complexity: O(n log n)
    Space Complexity: O(n)
    """
    intervals.sort(key=lambda x: x[0])
    merged = []
    for interval in intervals:
        if not merged or merged[-1][1] < interval[0]:
            merged.append(interval)
        else:
            merged[-1][1] = max(merged[-1][1], interval[1])
    return merged

def merge_intervals_stack(intervals):
    """
    Approach 2: Stack-based Merging
    Time Complexity: O(n log n)
    Space Complexity: O(n)
    """
    intervals.sort()
    stack = []
    for interval in intervals:
        if stack and stack[-1][1] >= interval[0]:
            stack[-1][1] = max(stack[-1][1], interval[1])
        else:
            stack.append(interval)
    return stack

def merge_intervals_sweep_line(intervals):
    """
    Approach 3: Sweep Line Algorithm
    Time Complexity: O(n log n)
    Space Complexity: O(n)
    """
    events = []
    for start, end in intervals:
        events.append((start, 1))
        events.append((end, -1))
    events.sort()
    merged, active_intervals, start = [], 0, None
    for point, effect in events:
        if active_intervals == 0:
            start = point
        active_intervals += effect
        if active_intervals == 0:
            merged.append([start, point])
    return merged

def merge_intervals_dsu(intervals):
    """
    Approach 4: Disjoint Set Union (Union-Find)
    Time Complexity: O(n log n)
    Space Complexity: O(n)
    """
    parent = {}
    def find(x):
        if parent[x] != x:
            parent[x] = find(parent[x])
        return parent[x]
    def union(x, y):
        parent[find(x)] = find(y)
    intervals.sort()
    for start, end in intervals:
        parent[start] = start
        parent[end] = end
    for start, end in intervals:
        union(start, end)
    merged = []
    for key in sorted(parent):
        if not merged or merged[-1][1] < key:
            merged.append([key, key])
        merged[-1][1] = max(merged[-1][1], key)
    return merged

def merge_intervals_tree(intervals):
    """
    Approach 5: Interval Tree
    Time Complexity: O(n log n)
    Space Complexity: O(n)
    """
    intervals.sort()
    result = []
    tree = deque()
    for interval in intervals:
        while tree and tree[-1][1] >= interval[0]:
            interval = [min(tree[-1][0], interval[0]), max(tree[-1][1], interval[1])]
            tree.pop()
        tree.append(interval)
    return list(tree)

# Example Usage
intervals = [[1, 3], [2, 6], [8, 10], [15, 18]]
print("Sorting and Merging:", merge_intervals_sorting(intervals))
print("Stack-based Merging:", merge_intervals_stack(intervals))
print("Sweep Line Algorithm:", merge_intervals_sweep_line(intervals))
print("Disjoint Set Union:", merge_intervals_dsu(intervals))
print("Interval Tree Merging:", merge_intervals_tree(intervals))
