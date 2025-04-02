from typing import List

def insert_interval_approach1(intervals: List[List[int]], new_interval: List[int]) -> List[List[int]]:
    """
    Approach 1: Iterative with in-place list modification (simulates real-time data feed).
    - Assumes intervals are sorted.
    - Iterates through intervals, merging/inserting the new interval as needed.
    - Modifies the original list in-place for efficiency (simulating a mutable data source).
    - Prints the state of 'intervals' at each step to show the dynamic process.
    """
    result = []
    i = 0

    print("\nApproach 1: Iterative with In-place Modification")
    print(f"Initial intervals: {intervals}, new_interval: {new_interval}")

    while i < len(intervals) and intervals[i][1] < new_interval[0]:
        result.append(intervals[i])
        i += 1
        print(f"Step {i}: No overlap, added {intervals[i-1]} to result. result: {result}, intervals: {intervals[i:]}")

    while i < len(intervals) and intervals[i][0] <= new_interval[1]:
        new_interval[0] = min(new_interval[0], intervals[i][0])
        new_interval[1] = max(new_interval[1], intervals[i][1])
        i += 1
        print(f"Step {i}: Overlap, merged with {intervals[i-1]}. new_interval: {new_interval}, intervals: {intervals[i:]}")

    result.append(new_interval)
    print(f"Step {i}: Merged/inserted new_interval. result: {result}, intervals: {intervals[i:]}")

    while i < len(intervals):
        result.append(intervals[i])
        i += 1
        print(f"Step {i}: No overlap, added {intervals[i-1]} to result. result: {result}, intervals: {intervals[i:]}")

    print(f"Final result: {result}")
    return result

def insert_interval_approach2(intervals: List[List[int]], new_interval: List[int]) -> List[List[int]]:
    """
    Approach 2:  Create new list.
    - Non-destructive: Creates a new list instead of modifying the original.
    - More readable, less prone to errors compared to in-place modification.
    - Suitable when the original list should remain unchanged.
    """
    result = []
    i = 0
    print("\nApproach 2: Create New List")
    print(f"Initial intervals: {intervals}, new_interval: {new_interval}")

    while i < len(intervals) and intervals[i][1] < new_interval[0]:
        result.append(intervals[i])
        i += 1
        print(f"Step {i}: No overlap, added {intervals[i-1]} to result.")

    while i < len(intervals) and intervals[i][0] <= new_interval[1]:
        new_interval[0] = min(new_interval[0], intervals[i][0])
        new_interval[1] = max(new_interval[1], intervals[i][1])
        i += 1
        print(f"Step {i}: Overlap, merged with interval. new_interval: {new_interval}")
    result.append(new_interval)
    print(f"Step {i}: Appended merged interval: {new_interval}")

    while i < len(intervals):
        result.append(intervals[i])
        i += 1
        print(f"Step {i}: No overlap, added {intervals[i-1]} to result.")
    print(f"Final result: {result}")
    return result

def insert_interval_approach3(intervals: List[List[int]], new_interval: List[int]) -> List[List[int]]:
    """
    Approach 3:  Using a 'for' loop
     - Uses a `for` loop, which can be more concise for simple iterations.
    -  Handles edge cases more explicitly within the loop.
    """
    result = []
    merged = False

    print("\nApproach 3: Using a 'for' loop")
    print(f"Initial intervals: {intervals}, new_interval: {new_interval}")

    for i in range(len(intervals)):
        interval = intervals[i]
        if interval[1] < new_interval[0]:
            result.append(interval)
            print(f"Step {i}: No overlap, added {interval} to result.")
        elif interval[0] > new_interval[1]:
            if not merged:
                result.append(new_interval)
                merged = True
                print(f"Step {i}: No overlap, added new_interval {new_interval} to result.")
            result.append(interval)
            print(f"Step {i}: No overlap, added {interval} to result.")
        else:
            new_interval[0] = min(new_interval[0], interval[0])
            new_interval[1] = max(new_interval[1], interval[1])
            print(f"Step {i}: Overlap, merged with interval. new_interval: {new_interval}")

    if not merged:
        result.append(new_interval)
        print(f"Final Step: new_interval was not merged, added to the end: {new_interval}")
    print(f"Final result: {result}")
    return result

def insert_interval_approach4(intervals: List[List[int]], new_interval: List[int]) -> List[List[int]]:
    """
    Approach 4:  Using a while loop with a break.
    - Uses a `while` loop with a `break` statement for more explicit control.
    -  Potentially more efficient if the new interval is inserted early.
    """
    result = []
    i = 0

    print("\nApproach 4: Using a 'while' loop with break")
    print(f"Initial intervals: {intervals}, new_interval: {new_interval}")
    while i < len(intervals):
        if intervals[i][1] < new_interval[0]:
            result.append(intervals[i])
            i += 1
            print(f"Step {i}: No overlap, added {intervals[i-1]} to result.")
        else:
            break

    while i < len(intervals) and intervals[i][0] <= new_interval[1]:
        new_interval[0] = min(new_interval[0], intervals[i][0])
        new_interval[1] = max(new_interval[1], intervals[i][1])
        i += 1
        print(f"Step {i}: Overlap, merged with interval. new_interval: {new_interval}")
    result.append(new_interval)
    print(f"Step {i}: Appended merged interval: {new_interval}")

    while i < len(intervals):
        result.append(intervals[i])
        i += 1
        print(f"Step {i}: No overlap, added {intervals[i-1]} to result.")
    print(f"Final result: {result}")
    return result

def insert_interval_approach5(intervals: List[List[int]], new_interval: List[int]) -> List[List[int]]:
    """
    Approach 5:  Using a flag variable.
     - Uses a boolean flag to track whether the new interval has been inserted.
    -  Clear and easy-to-follow logic.
    """
    result = []
    merged = False
    print("\nApproach 5: Using a flag variable")
    print(f"Initial intervals: {intervals}, new_interval: {new_interval}")

    for interval in intervals:
        if interval[1] < new_interval[0]:
            result.append(interval)
            print(f"No overlap, added {interval} to result.")
        elif interval[0] > new_interval[1]:
            if not merged:
                result.append(new_interval)
                merged = True
                print(f"No overlap, added new_interval to result.")
            result.append(interval)
            print(f"No overlap, added {interval} to result.")
        else:
            new_interval[0] = min(new_interval[0], interval[0])
            new_interval[1] = max(new_interval[1], interval[1])
            print(f"Overlap, merged with interval. new_interval: {new_interval}")

    if not merged:
        result.append(new_interval)
        print(f"new_interval was not merged, added to the end.")
    print(f"Final result: {result}")
    return result

def insert_interval_approach6(intervals: List[List[int]], new_interval: List[int]) -> List[List[int]]:
    """
    Approach 6:  Optimized Approach
    - Optimized for both speed and readability.
    -  Reduces redundant checks.
    """
    result = []
    i = 0
    n = len(intervals)

    print("\nApproach 6: Optimized Approach")
    print(f"Initial intervals: {intervals}, new_interval: {new_interval}")

    # Add intervals that come before the new interval
    while i < n and intervals[i][1] < new_interval[0]:
        result.append(intervals[i])
        i += 1
        print(f"Step {i}: Added non-overlapping interval: {intervals[i-1]}")

    # Merge overlapping intervals
    while i < n and intervals[i][0] <= new_interval[1]:
        new_interval[0] = min(new_interval[0], intervals[i][0])
        new_interval[1] = max(new_interval[1], intervals[i][1])
        i += 1
        print(f"Step {i}: Merged with overlapping interval, new_interval: {new_interval}")

    # Add the merged new interval
    result.append(new_interval)
    print(f"Step {i}: Added merged interval: {new_interval}")

    # Add the remaining intervals
    while i < n:
        result.append(intervals[i])
        i += 1
        print(f"Step {i}: Added remaining interval: {intervals[i-1]}")
    print(f"Final result: {result}")
    return result
# Example Usage (Demonstrates all 6 approaches with the same input)
intervals = [[1, 3], [6, 9]]
new_interval = [2, 5]

print(f"Input: intervals = {intervals}, new_interval = {new_interval}")
print("-" * 50)

# Run and print results for each approach
result1 = insert_interval_approach1(intervals, new_interval)
print(f"Result 1: {result1}")
print("-" * 50)

result2 = insert_interval_approach2(intervals, new_interval)
print(f"Result 2: {result2}")
print("-" * 50)

result3 = insert_interval_approach3(intervals, new_interval)
print(f"Result 3: {result3}")
print("-" * 50)

result4 = insert_interval_approach4(intervals, new_interval)
print(f"Result 4: {result4}")
print("-" * 50)

result5 = insert_interval_approach5(intervals, new_interval)
print(f"Result 5: {result5}")
print("-" * 50)

result6 = insert_interval_approach6(intervals, new_interval)
print(f"Result 6: {result6}")
print("-" * 50)

# Additional test cases (for robustness)
print("\nAdditional Test Cases:")
print("-" * 50)
test_intervals1 = [[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]]
test_new_interval1 = [4, 8]
print(f"Test Case 1: intervals = {test_intervals1}, new_interval = {test_new_interval1}")
result_test1 = insert_interval_approach6(test_intervals1, test_new_interval1)
print(f"Result: {result_test1}")
print("-" * 50)

test_intervals2 = [[1, 3], [6, 9]]
test_new_interval2 = [10, 12]
print(f"Test Case 2: intervals = {test_intervals2}, new_interval = {test_new_interval2}")
result_test2 = insert_interval_approach6(test_intervals2, test_new_interval2)
print(f"Result: {result_test2}")
print("-" * 50)

test_intervals3 = [[1, 3], [6, 9]]
test_new_interval3 = [0, 1]
print(f"Test Case 3: intervals = {test_intervals3}, new_interval = {test_new_interval3}")
result_test3 = insert_interval_approach6(test_intervals3, test_new_interval3)
print(f"Result: {result_test3}")
print("-" * 50)

test_intervals4 = [[1, 3], [6, 9]]
test_new_interval4 = [2, 4]
print(f"Test Case 4: intervals = {test_intervals4}, new_interval = {test_new_interval4}")
result_test4 = insert_interval_approach6(test_intervals4, test_new_interval4)
print(f"Result: {result_test4}")
print("-" * 50)

test_intervals5 = [[1, 3], [6, 9]]
test_new_interval5 = [7, 8]
print(f"Test Case 5: intervals = {test_intervals5}, new_interval = {test_new_interval5}")
result_test5 = insert_interval_approach6(test_intervals5, test_new_interval5)
print(f"Result: {result_test5}")
print("-" * 50)

test_intervals6 = [[1, 3], [6, 9], [10,15], [16,18]]
test_new_interval6 = [11, 17]
print(f"Test Case 6: intervals = {test_intervals6}, new_interval = {test_new_interval6}")
result_test6 = insert_interval_approach6(test_intervals6, test_new_interval6)
print(f"Result: {result_test6}")
print("-" * 50)
