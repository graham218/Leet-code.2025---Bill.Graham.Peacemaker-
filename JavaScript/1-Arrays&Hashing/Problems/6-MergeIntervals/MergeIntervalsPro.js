/*
Problem:
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Intervals [1,3] and [2,6] overlap since 2 <= 3, so they should be merged into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] overlap since 4 <= 4, so they should be merged into [1,5].

Constraints:
-   1 <= intervals.length <= 10^4
-   intervals[i].length == 2
-   0 <= starti <= endi <= 10^4
*/

/**
 * Approach 1: Sort and Merge
 *
 * Description:
 * The most common and efficient approach. First, sort the intervals by their start times.
 * Then, iterate through the sorted intervals, merging overlapping intervals.
 *
 * Time Complexity: O(n log n) - Due to sorting.
 * Space Complexity: O(n) - In the worst case, the output array could contain all the input intervals.
 */
function mergeIntervals_sortAndMerge(intervals) {
    if (intervals.length <= 1) {
        return intervals;
    }

    // Sort intervals by start time
    intervals.sort((a, b) => a[0] - b[0]);

    const mergedIntervals = [intervals[0]]; // Start with the first interval
    for (let i = 1; i < intervals.length; i++) {
        const currentInterval = intervals[i];
        const lastMergedInterval = mergedIntervals[mergedIntervals.length - 1];

        if (currentInterval[0] <= lastMergedInterval[1]) {
            // Overlapping intervals, merge
            lastMergedInterval[1] = Math.max(lastMergedInterval[1], currentInterval[1]);
        } else {
            // Non-overlapping interval, add to the result
            mergedIntervals.push(currentInterval);
        }
    }
    return mergedIntervals;
}

/**
 * Approach 2: Iterative with In-Place Modification (Less Common, Tricky)
 *
 * Description:
 * This approach attempts to merge intervals in-place to avoid extra space.  It's more complex
 * and harder to get right.  It involves iterating through the intervals and modifying the
 * original array.  This approach is generally NOT recommended due to its complexity and
 * potential for errors.
 *
 * Time Complexity: O(n log n) - Due to sorting.
 * Space Complexity: O(1) -  Attempts in-place merging, but the sorting might use extra space.
 *
 * WARNING: This approach is complex and can be error-prone.  Use with caution and thorough testing.
 */
function mergeIntervals_inPlace(intervals) {
     if (intervals.length <= 1) return intervals;

    intervals.sort((a, b) => a[0] - b[0]); // Sort by start times

    let i = 0;
    while (i < intervals.length - 1) {
        if (intervals[i][1] >= intervals[i + 1][0]) {
            // Overlap: Merge intervals
            intervals[i][1] = Math.max(intervals[i][1], intervals[i + 1][1]);
            intervals.splice(i + 1, 1); // Remove the merged interval
        } else {
            i++;
        }
    }
    return intervals;
}



/**
 * Approach 3: Using Reduce
 *
 * Description:
 * This approach uses the `reduce` method to iteratively merge intervals.  It's a functional
 * approach and can be more concise, but might be less readable for those not familiar with `reduce`.
 *
 * Time Complexity: O(n log n) - Due to sorting.
 * Space Complexity: O(n) -  The `reduce` method creates a new array.
 */
function mergeIntervals_reduce(intervals) {
    if (intervals.length <= 1) return intervals;

    const sortedIntervals = [...intervals].sort((a, b) => a[0] - b[0]); //spread to avoid modifying original
    return sortedIntervals.reduce((merged, interval) => {
        if (merged.length === 0 || merged[merged.length - 1][1] < interval[0]) {
            merged.push(interval);
        } else {
            merged[merged.length - 1][1] = Math.max(merged[merged.length - 1][1], interval[1]);
        }
        return merged;
    }, []);
}

/**
 * Approach 4:  Iterative with Stack
 *
 * Description:
 * Uses a stack to keep track of the merged intervals.  Sort the intervals, then push the first
 * interval onto the stack.  Iterate through the remaining intervals, and if the current interval
 * overlaps with the top of the stack, merge them; otherwise, push the current interval onto the stack.
 *
 * Time Complexity: O(n log n) - Due to sorting.
 * Space Complexity: O(n) -  The stack could potentially hold all the input intervals.
 */
function mergeIntervals_stack(intervals) {
    if (intervals.length <= 1) {
        return intervals;
    }

    const sortedIntervals = [...intervals].sort((a, b) => a[0] - b[0]); //non destructive sort
    const stack = [sortedIntervals[0]];

    for (let i = 1; i < sortedIntervals.length; i++) {
        const currentInterval = sortedIntervals[i];
        const top = stack[stack.length - 1];

        if (currentInterval[0] <= top[1]) {
            // Overlap, merge with the top of the stack
            top[1] = Math.max(top[1], currentInterval[1]);
        } else {
            // No overlap, push the current interval onto the stack
            stack.push(currentInterval);
        }
    }
    return stack;
}

/**
 * Approach 5:  Recursive Approach
 *
 * Description:
 * A recursive approach. Sort the intervals.  Recursively merge the first interval with the
 * rest of the sorted intervals.
 *
 * Time Complexity: O(n log n) - Due to sorting.
 * Space Complexity: O(n) -  Due to the recursive call stack.
 */
function mergeIntervals_recursive(intervals) {
    if (intervals.length <= 1) return intervals;

    const sortedIntervals = [...intervals].sort((a, b) => a[0] - b[0]);

    function mergeHelper(arr) {
        if (arr.length <= 1) return arr;

        const first = arr[0];
        const rest = arr.slice(1);
        const mergedRest = mergeHelper(rest);

        if (mergedRest.length > 0 && first[1] >= mergedRest[0][0]) {
            // Overlap, merge
            return [[first[0], Math.max(first[1], mergedRest[0][1])], ...mergedRest.slice(1)];
        } else {
            // No overlap
            return [first, ...mergedRest];
        }
    }

    return mergeHelper(sortedIntervals);
}

/**
 * Approach 6:  Sorting and Iterating with ForEach
 *
 * Description:
 * This approach sorts the intervals and then uses a forEach loop to iterate through them.
 * It's very similar to the standard sort-and-merge approach, but uses a different way to
 * iterate through the sorted intervals.
 *
 * Time Complexity: O(n log n) - Due to sorting.
 * Space Complexity: O(n) - The mergedIntervals array.
 */
function mergeIntervals_forEach(intervals) {
    if (intervals.length <= 1) return intervals;

    const sortedIntervals = [...intervals].sort((a, b) => a[0] - b[0]);
    const mergedIntervals = [];

    sortedIntervals.forEach(interval => {
        if (mergedIntervals.length === 0 || mergedIntervals[mergedIntervals.length - 1][1] < interval[0]) {
            mergedIntervals.push(interval);
        } else {
            const lastMerged = mergedIntervals[mergedIntervals.length - 1];
            lastMerged[1] = Math.max(lastMerged[1], interval[1]);
        }
    });

    return mergedIntervals;
}



// Example Usage and Output
const intervals1 = [[1, 3], [2, 6], [8, 10], [15, 18]];
const intervals2 = [[1, 4], [4, 5]];
const intervals3 = [[1, 4], [0, 4]];
const intervals4 = [[2,3],[4,5],[6,7],[8,9],[1,10]];

console.log("Input: [[1,3],[2,6],[8,10],[15,18]]");
console.log("Sort and Merge:", mergeIntervals_sortAndMerge(intervals1));   // Output: [[1, 6], [8, 10], [15, 18]]
console.log("In-Place:", mergeIntervals_inPlace(intervals1));           // Output: [[1, 6], [8, 10], [15, 18]]
console.log("Reduce:", mergeIntervals_reduce(intervals1));               // Output: [[1, 6], [8, 10], [15, 18]]
console.log("Stack:", mergeIntervals_stack(intervals1));                 // Output: [[1, 6], [8, 10], [15, 18]]
console.log("Recursive:", mergeIntervals_recursive(intervals1));         // Output: [[1, 6], [8, 10], [15, 18]]
console.log("ForEach:", mergeIntervals_forEach(intervals1));             // Output: [[1, 6], [8, 10], [15, 18]]

console.log("\nInput: [[1,4],[4,5]]");
console.log("Sort and Merge:", mergeIntervals_sortAndMerge(intervals2));   // Output: [[1, 5]]
console.log("In-Place:", mergeIntervals_inPlace(intervals2));           // Output: [[1, 5]]
console.log("Reduce:", mergeIntervals_reduce(intervals2));               // Output: [[1, 5]]
console.log("Stack:", mergeIntervals_stack(intervals2));                 // Output: [[1, 5]]
console.log("Recursive:", mergeIntervals_recursive(intervals2));         // Output: [[1, 5]]
console.log("ForEach:", mergeIntervals_forEach(intervals2));             // Output: [[1, 5]]

console.log("\nInput: [[1,4],[0,4]]");
console.log("Sort and Merge:", mergeIntervals_sortAndMerge(intervals3));   // Output: [[0, 4]]
console.log("In-Place:", mergeIntervals_inPlace(intervals3));
console.log("Reduce:", mergeIntervals_reduce(intervals3));               // Output: [[0, 4]]
console.log("Stack:", mergeIntervals_stack(intervals3));                 // Output:  [[0, 4]]
console.log("Recursive:", mergeIntervals_recursive(intervals3));         // Output: [[0, 4]]
console.log("ForEach:", mergeIntervals_forEach(intervals3));             // Output: [[0, 4]]

console.log("\nInput: [[2,3],[4,5],[6,7],[8,9],[1,10]]");
console.log("Sort and Merge:", mergeIntervals_sortAndMerge(intervals4));
console.log("In-Place:", mergeIntervals_inPlace(intervals4));
console.log("Reduce:", mergeIntervals_reduce(intervals4));
console.log("Stack:", mergeIntervals_stack(intervals4));
console.log("Recursive:", mergeIntervals_recursive(intervals4));
console.log("ForEach:", mergeIntervals_forEach(intervals4));
