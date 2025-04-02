def insert_interval_approach1(intervals, new_interval):
    """
    Approach 1: Iterative with Overlapping Checks

    Inserts a new interval into a list of sorted non-overlapping intervals, merging if necessary.

    Args:
        intervals: A list of non-overlapping intervals, sorted by start time.
        new_interval: The interval to insert.

    Returns:
        A new list of intervals with the new interval inserted and merged as needed.

    Time Complexity: O(n), where n is the number of intervals.
    Space Complexity: O(n) in the worst case (new list created).
    """
    result = []
    i = 0

    # Add intervals occurring before the new interval
    while i < len(intervals) and intervals[i][1] < new_interval[0]:
        result.append(intervals[i])
        i += 1

    # Merge overlapping intervals
    while i < len(intervals) and intervals[i][0] <= new_interval[1]:
        new_interval[0] = min(new_interval[0], intervals[i][0])
        new_interval[1] = max(new_interval[1], intervals[i][1])
        i += 1

    # Add the merged (or non-overlapping) new interval
    result.append(new_interval)

    # Add the remaining intervals
    while i < len(intervals):
        result.append(intervals[i])
        i += 1

    return result


def insert_interval_approach2(intervals, new_interval):
    """
    Approach 2: Simplified Iteration

    A slightly more concise version of the iterative approach.

    Args:
        intervals: List of sorted non-overlapping intervals.
        new_interval: Interval to insert.

    Returns:
        Merged list of intervals.

    Time Complexity: O(n)
    Space Complexity: O(n)
    """
    result = []
    for i, interval in enumerate(intervals):
        if new_interval[1] < interval[0]:  # new_interval is before current
            result.append(new_interval)
            result.extend(intervals[i:])
            return result
        elif new_interval[0] > interval[1]:  # new_interval is after current
            result.append(interval)
        else:  # Overlapping case
            new_interval[0] = min(new_interval[0], interval[0])
            new_interval[1] = max(new_interval[1], interval[1])
    result.append(new_interval)  # Append new_interval in case it goes at the end
    return result

def insert_interval_approach3(intervals, new_interval):
    """
    Approach 3: Using a Function for Overlap Check

    This approach encapsulates the overlap check in a helper function
    for better readability.

    Args:
        intervals: List of sorted non-overlapping intervals
        new_interval: Interval to insert

    Returns:
        Merged list of intervals
    """
    def is_overlapping(interval1, interval2):
        """Checks if two intervals overlap."""
        return interval1[1] >= interval2[0] and interval2[1] >= interval1[0]

    result = []
    i = 0
    while i < len(intervals) and not is_overlapping(intervals[i], new_interval):
        if intervals[i][1] < new_interval[0]:
            result.append(intervals[i])
        else:
            result.append(new_interval)
            result.extend(intervals[i:])
            return result
        i += 1

    # Merge overlapping intervals
    while i < len(intervals) and is_overlapping(intervals[i], new_interval):
        new_interval[0] = min(new_interval[0], intervals[i][0])
        new_interval[1] = max(new_interval[1], intervals[i][1])
        i += 1
    result.append(new_interval)
    result.extend(intervals[i:])
    return result

def insert_interval_approach4(intervals, new_interval):
    """
    Approach 4:  In-place Modification (Less Pythonic, but shows idea)

    This approach attempts to modify the original intervals list in-place.
    This is generally less preferred in Python due to potential side-effects
    and the immutability of integers, but it's included for illustration.
    It's more common in languages like C++ where you have direct memory manipulation.
    This approach can be harder to reason about and debug in Python.

    Args:
        intervals: List of sorted non-overlapping intervals.
        new_interval: Interval to insert.

    Returns:
       Modified list of intervals.  (The original list is also modified!)
    """
    i = 0
    while i < len(intervals):
        if new_interval[1] < intervals[i][0]:
            intervals.insert(i, new_interval)
            return intervals  # Important: Return here!
        elif new_interval[0] > intervals[i][1]:
            i += 1
        else:
            new_interval[0] = min(new_interval[0], intervals[i][0])
            new_interval[1] = max(new_interval[1], intervals[i][1])
            intervals.pop(i) # Remove the interval at i.
    intervals.append(new_interval)
    return intervals

def insert_interval_approach5(intervals, new_interval):
    """
    Approach 5:  Functional Approach with Reduce (More Advanced)

    This approach uses the reduce function from the functools module
    to perform the merging.  It's a more functional style, and can be
    more concise, but potentially less readable for those not familiar
    with reduce.

    Args:
        intervals: List of sorted non-overlapping intervals.
        new_interval: Interval to insert.

    Returns:
        Merged list of intervals.
    """
    from functools import reduce

    def merge_or_append(acc, interval):
        if not acc:
            return [interval]
        last_interval = acc[-1]
        if last_interval[1] < interval[0]:
            acc.append(interval)
        elif last_interval[0] > interval[1]:  # Corrected condition.
            acc.append(interval)  # Added missing append
        else:
            merged_interval = [
                min(last_interval[0], interval[0]),
                max(last_interval[1], interval[1]),
            ]
            acc[-1] = merged_interval  # Modify the last interval in place
        return acc

    combined = intervals + [new_interval]
    combined.sort(key=lambda x: x[0])  # Sort is crucial for reduce to work correctly here
    return reduce(merge_or_append, combined, [])



if __name__ == "__main__":
    # Example Usage and Testing
    intervals = [[1, 3], [6, 9]]
    new_interval = [2, 5]

    print("Original Intervals:", intervals)
    print("New Interval:", new_interval)
    print("-" * 20)

    print("Approach 1: Iterative with Overlapping Checks")
    result1 = insert_interval_approach1(intervals, new_interval)
    print("Result:", result1)
    print("-" * 20)

    print("Approach 2: Simplified Iteration")
    result2 = insert_interval_approach2(intervals, new_interval)
    print("Result:", result2)
    print("-" * 20)

    print("Approach 3: Using a Function for Overlap Check")
    result3 = insert_interval_approach3(intervals, new_interval)
    print("Result:", result3)
    print("-" * 20)

    print("Approach 4: In-place Modification")
    intervals4 = [[1, 3], [6, 9]] # Reset to original
    result4 = insert_interval_approach4(intervals4, new_interval)
    print("Result:", result4)
    print("Modified Original (intervals4):", intervals4) # Show the modification
    print("-" * 20)

    print("Approach 5: Functional Approach with Reduce")
    result5 = insert_interval_approach5(intervals, new_interval)
    print("Result:", result5)
    print("-" * 20)

    # Test case with no overlap
    intervals2 = [[1, 3], [5, 7], [8, 10], [12, 16]]
    new_interval2 = [4, 4]
    print(f"Test Case: No Overlap, intervals: {intervals2}, new_interval: {new_interval2}")
    result_no_overlap = insert_interval_approach1(intervals2, new_interval2)
    print("Result (No Overlap):", result_no_overlap)

    # Test case where new interval is at the beginning
    intervals3 = [[2, 5], [6, 9]]
    new_interval3 = [0, 1]
    print(f"Test Case: Insert at Beginning, intervals: {intervals3}, new_interval: {new_interval3}")
    result_beginning = insert_interval_approach1(intervals3, new_interval3)
    print("Result (Beginning):", result_beginning)

    # Test case where new interval is at the end
    intervals4 = [[2, 5], [6, 9]]
    new_interval4 = [10, 11]
    print(f"Test Case: Insert at End, intervals: {intervals4}, new_interval: {new_interval4}")
    result_end = insert_interval_approach1(intervals4, new_interval4)
    print("Result (End):", result_end)

    # Test case with full overlap
    intervals5 = [[1, 5]]
    new_interval5 = [0, 6]
    print(f"Test Case: Full Overlap, intervals: {intervals5}, new_interval: {new_interval5}")
    result_full_overlap = insert_interval_approach1(intervals5, new_interval5)
    print("Result (Full Overlap):", result_full_overlap)

    # Test case with empty intervals list
    intervals6 = []
    new_interval6 = [1, 2]
    print(f"Test Case: Empty intervals, intervals: {intervals6}, new_interval: {new_interval6}")
    result_empty_intervals = insert_interval_approach1(intervals6, new_interval6)
    print("Result (Empty Intervals):", result_empty_intervals)
