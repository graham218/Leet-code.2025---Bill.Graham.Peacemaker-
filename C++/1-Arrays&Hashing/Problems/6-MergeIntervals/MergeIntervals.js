/*
Problem:
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals
and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Intervals [1,3] and [2,6] overlap since 2 <= 3, so they are merged to [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
*/

/**
 * Approach 1: Brute Force
 *
 * For each interval, compare it with every other interval to check for overlap.
 * If an overlap is found, merge them and add the merged interval to a new list.
 * This approach is inefficient due to its nested loops.  It's tricky to avoid
 * adding duplicate intervals and handling all edge cases correctly.
 *
 * Time Complexity: O(n^2), where n is the number of intervals.
 * Space Complexity: O(n), to store the merged intervals.
 */
function mergeIntervalsBruteForce(intervals) {
    const mergedIntervals = [];
    const n = intervals.length;
    const visited = new Array(n).fill(false);

    for (let i = 0; i < n; i++) {
        if (visited[i]) continue; // Skip if this interval has already been merged

        let currentStart = intervals[i][0];
        let currentEnd = intervals[i][1];
        visited[i] = true;

        for (let j = 0; j < n; j++) {
            if (i === j || visited[j]) continue; // Skip self and already merged intervals

            const otherStart = intervals[j][0];
            const otherEnd = intervals[j][1];

            // Check for overlap and merge
            if (
                (otherStart >= currentStart && otherStart <= currentEnd) ||
                (otherEnd >= currentStart && otherEnd <= currentEnd) ||
                (currentStart >= otherStart && currentStart <= otherEnd) // Added this condition
            ) {
                currentStart = Math.min(currentStart, otherStart);
                currentEnd = Math.max(currentEnd, otherEnd);
                visited[j] = true;
                j = -1; // Restart the inner loop to check for further merges
            }
        }
        mergedIntervals.push([currentStart, currentEnd]);
    }
    return mergedIntervals;
}


/**
 * Approach 2: Sorting and Iterative Merging
 *
 * Sort the intervals by their start times. This allows us to efficiently check for overlaps
 * in a single pass.  Iterate through the sorted intervals, merging overlapping intervals
 * as we encounter them. This is a standard and efficient approach.
 *
 * Time Complexity: O(n log n), due to the sorting step.
 * Space Complexity: O(n), to store the merged intervals (in the worst case).  Could be O(1) if done in-place.
 */
function mergeIntervalsSortAndMerge(intervals) {
    if (intervals.length <= 1) {
        return intervals;
    }

    // Sort intervals by start time
    intervals.sort((a, b) => a[0] - b[0]);

    const mergedIntervals = [intervals[0]]; // Start with the first interval
    for (let i = 1; i < intervals.length; i++) {
        const currentInterval = intervals[i];
        const lastMergedInterval = mergedIntervals[mergedIntervals.length - 1];

        const currentStart = currentInterval[0];
        const currentEnd = currentInterval[1];
        const lastMergedEnd = lastMergedInterval[1];

        if (currentStart <= lastMergedEnd) {
            // Overlapping intervals, merge
            lastMergedInterval[1] = Math.max(lastMergedInterval[1], currentEnd);
        } else {
            // Non-overlapping interval, add to the result
            mergedIntervals.push(currentInterval);
        }
    }
    return mergedIntervals;
}

/**
 * Approach 3: Iterative with In-Place Modification (Less Space)
 *
 * This approach is similar to the sorting and merging approach, but it attempts to minimize
 * space usage by modifying the input array in-place.  It can be more complex to manage the indices
 * correctly, and it modifies the original input.
 *
 * Time Complexity: O(n log n), due to the sorting step.
 * Space Complexity: O(1),  It modifies the input array.
 */
function mergeIntervalsInPlace(intervals) {
    if (intervals.length <= 1) return intervals;

    intervals.sort((a, b) => a[0] - b[0]); // Sort by start time

    let i = 0;
    while (i < intervals.length - 1) {
        const current = intervals[i];
        const next = intervals[i + 1];

        if (next[0] <= current[1]) {
            // Overlap, merge in-place
            current[1] = Math.max(current[1], next[1]);
            intervals.splice(i + 1, 1); // Remove the next interval
        } else {
            i++;
        }
    }
    return intervals;
}

/**
 * Approach 4: Using Reduce
 *
 * This approach uses the reduce method to iterate through the sorted intervals and merge them.
 * It's a functional approach that can be concise but might be slightly less readable for those
 * not very familiar with reduce.
 *
 * Time Complexity: O(n log n), due to sorting.
 * Space Complexity: O(n), for the accumulated merged intervals.
 */
function mergeIntervalsReduce(intervals) {
    if (intervals.length <= 1) return intervals;

    const sortedIntervals = [...intervals].sort((a, b) => a[0] - b[0]); // Avoid mutating original

    return sortedIntervals.reduce((merged, interval) => {
        if (merged.length === 0 || interval[0] > merged[merged.length - 1][1]) {
            merged.push(interval);
        } else {
            merged[merged.length - 1][1] = Math.max(merged[merged.length - 1][1], interval[1]);
        }
        return merged;
    }, []);
}

/**
 * Approach 5:  Sorting and Iterating with ForEach
 *
 * This approach sorts the intervals and then uses a forEach loop to iterate through them.
 * It's very similar to Approach 2, but uses a different way to loop through the sorted intervals.
 *
 * Time Complexity: O(n log n), due to the sorting step.
 * Space Complexity: O(n), to store the merged intervals.
 */
function mergeIntervalsSortAndForEach(intervals) {
      if (intervals.length <= 1) {
        return intervals;
    }

    // Sort intervals by start time
    intervals.sort((a, b) => a[0] - b[0]);

    const mergedIntervals = [];
    let previousInterval = intervals[0];  // Start with the first interval
    mergedIntervals.push(previousInterval);

    intervals.forEach((currentInterval, index) => {
        if(index === 0) return; //skip the first interval, already in mergedIntervals
        const currentStart = currentInterval[0];
        const currentEnd = currentInterval[1];
        const lastMergedEnd = previousInterval[1];

        if (currentStart <= lastMergedEnd) {
            // Overlapping intervals, merge
            previousInterval[1] = Math.max(previousInterval[1], currentEnd);
        } else {
            // Non-overlapping interval, add to the result
            mergedIntervals.push(currentInterval);
            previousInterval = currentInterval; //update previousInterval
        }
    });
    return mergedIntervals;
}



// Example Usage and Output
const intervals1 = [[1, 3], [2, 6], [8, 10], [15, 18]];
const intervals2 = [[1, 4], [4, 5]];
const intervals3 = [[1, 4], [0, 4]];
const intervals4 = [[2,3],[4,5],[6,7],[8,9],[1,10]];
const intervals5 = [[2,2],[5,5],[2,2],[1,8],[0,1]];


console.log("Input: [[1,3],[2,6],[8,10],[15,18]]");
console.log("Brute Force:", mergeIntervalsBruteForce(intervals1));        // Output: [[1, 6], [8, 10], [15, 18]]
console.log("Sort and Merge:", mergeIntervalsSortAndMerge(intervals1));    // Output: [[1, 6], [8, 10], [15, 18]]
console.log("In-Place:", mergeIntervalsInPlace(intervals1));           // Output: [[1, 6], [8, 10], [15, 18]]
console.log("Reduce:", mergeIntervalsReduce(intervals1));               // Output: [[1, 6], [8, 10], [15, 18]]
console.log("Sort and ForEach:", mergeIntervalsSortAndForEach(intervals1)); // Output: [[1, 6], [8, 10], [15, 18]]

console.log("\nInput: [[1,4],[4,5]]");
console.log("Brute Force:", mergeIntervalsBruteForce(intervals2));        // Output: [[1, 5]]
console.log("Sort and Merge:", mergeIntervalsSortAndMerge(intervals2));    // Output: [[1, 5]]
console.log("In-Place:", mergeIntervalsInPlace(intervals2));           // Output: [[1, 5]]
console.log("Reduce:", mergeIntervalsReduce(intervals2));               // Output: [[1, 5]]
console.log("Sort and ForEach:", mergeIntervalsSortAndForEach(intervals2)); // Output: [[1, 5]]

console.log("\nInput: [[1,4],[0,4]]");
console.log("Brute Force:", mergeIntervalsBruteForce(intervals3));       // Output: [[0, 4]]
console.log("Sort and Merge:", mergeIntervalsSortAndMerge(intervals3));   // Output: [[0, 4]]
console.log("In-Place:", mergeIntervalsInPlace(intervals3));          // Output: [[0, 4]]
console.log("Reduce:", mergeIntervalsReduce(intervals3));              // Output: [[0, 4]]
console.log("Sort and ForEach:", mergeIntervalsSortAndForEach(intervals3)); // Output: [[0, 4]]

console.log("\nInput: [[2,3],[4,5],[6,7],[8,9],[1,10]]");
console.log("Brute Force:", mergeIntervalsBruteForce(intervals4));       // Output: [[1, 10]]
console.log("Sort and Merge:", mergeIntervalsSortAndMerge(intervals4));   // Output: [[1, 10]]
console.log("In-Place:", mergeIntervalsInPlace(intervals4));          // Output: [[1, 10]]
console.log("Reduce:", mergeIntervalsReduce(intervals4));              // Output: [[1, 10]]
console.log("Sort and ForEach:", mergeIntervalsSortAndForEach(intervals4)); // Output: [[1, 10]]

console.log("\nInput: [[2,2],[5,5],[2,2],[1,8],[0,1]]");
console.log("Brute Force:", mergeIntervalsBruteForce(intervals5));       // Output: [[0, 1], [2, 2], [5, 5], [1, 8]]
console.log("Sort and Merge:", mergeIntervalsSortAndMerge(intervals5));   // Output: [[0, 8]]
console.log("In-Place:", mergeIntervalsInPlace(intervals5));          // Output:  [[0, 8]]
console.log("Reduce:", mergeIntervalsReduce(intervals5));              // Output: [[0, 8]]
console.log("Sort and ForEach:", mergeIntervalsSortAndForEach(intervals5)); // Output:  [[0, 8]]
