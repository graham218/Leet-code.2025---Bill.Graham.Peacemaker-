/**
 * You are given an array of non-overlapping intervals where each interval intervals[i] = [starti, endi] represent the start and the end of the ith interval and intervals are sorted in ascending order by starti. You are also given an interval newInterval = [start, end] that represents the start and end of another interval.
 *
 * Insert newInterval into intervals such that the resulting intervals are still sorted in ascending order by starti and do not have any overlapping intervals (merge overlapping intervals if necessary).
 *
 *
 *
 * Example 1:
 *
 * Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * Output: [[1,5],[6,9]]
 * Example 2:
 *
 * Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * Output: [[1,2],[3,10],[12,16]]
 * Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
 *
 *
 * Constraints:
 *
 * 0 <= intervals.length <= 104
 * intervals[i].length == 2
 * 0 <= starti <= endi <= 104
 * intervals are sorted in ascending order by starti.
 * newInterval.length == 2
 * 0 <= start <= end <= 104
 */

// Approach 1:  Simple Iterative with Merge (Most Common, Production-Ready)
//   -  Directly iterates through the intervals, merging as needed.
//   -  Clear, concise, and efficient.  Good for most production scenarios.
function insertInterval1(intervals, newInterval) {
    const merged = [];
    let i = 0;

    // Add intervals occurring before the overlap
    while (i < intervals.length && intervals[i][1] < newInterval[0]) {
        merged.push(intervals[i]);
        i++;
    }

    // Merge overlapping intervals
    while (i < intervals.length && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = Math.min(newInterval[0], intervals[i][0]);
        newInterval[1] = Math.max(newInterval[1], intervals[i][1]);
        i++;
    }
    merged.push(newInterval); // Add the merged interval

    // Add the remaining intervals
    while (i < intervals.length) {
        merged.push(intervals[i]);
        i++;
    }

    return merged;
}



// Approach 2:  Reduce with Accumulator (Functional Style)
//   - Uses Array.reduce for a more functional approach.
//   -  Can be slightly less readable for those not familiar with reduce.
function insertInterval2(intervals, newInterval) {
  return intervals.reduce((merged, interval, index) => {
    if (newInterval === null) { // null indicates newInterval was already merged
      merged.push(interval);
      return merged;
    }
    if (interval[1] < newInterval[0]) {
      merged.push(interval);
    } else if (interval[0] > newInterval[1]) {
      merged.push(newInterval, ...intervals.slice(index)); // Push newInterval and the rest
      newInterval = null; // Mark newInterval as consumed
    } else {
      newInterval[0] = Math.min(newInterval[0], interval[0]);
      newInterval[1] = Math.max(newInterval[1], interval[1]);
    }
    return merged;
  }, newInterval ? [] : []); // if newInterval is not null, start with empty array, otherwise with newInterval
}



// Approach 3:  Iterative with Flags (Detailed Control)
//   - Uses boolean flags for more explicit control of the merging process.
//   -  More verbose, but can be easier to debug in complex scenarios.
function insertInterval3(intervals, newInterval) {
    const merged = [];
    let i = 0;
    let inserted = false;

    while (i < intervals.length) {
        if (intervals[i][1] < newInterval[0]) {
            merged.push(intervals[i]);
        } else if (intervals[i][0] > newInterval[1]) {
            if (!inserted) {
                merged.push(newInterval);
                inserted = true;
            }
            merged.push(intervals[i]);
        } else {
            newInterval[0] = Math.min(newInterval[0], intervals[i][0]);
            newInterval[1] = Math.max(newInterval[1], intervals[i][1]);
        }
        i++;
    }

    if (!inserted) {
        merged.push(newInterval);
    }
    return merged;
}

// Approach 4:  Using a Separate Merge Function (Modular)
//   -  Extracts the merging logic into a separate function.
//   -  Promotes code reusability and separation of concerns.
function mergeIntervals(intervals) {
    if (!intervals.length) return [];
    intervals.sort((a, b) => a[0] - b[0]); // Sort, although input is said to be sorted, good for robustness
    const merged = [intervals[0]];
    for (let i = 1; i < intervals.length; i++) {
        const current = intervals[i];
        const lastMerged = merged[merged.length - 1];
        if (current[0] <= lastMerged[1]) {
            lastMerged[1] = Math.max(lastMerged[1], current[1]);
        } else {
            merged.push(current);
        }
    }
    return merged;
}

function insertInterval4(intervals, newInterval) {
    const combined = [...intervals, newInterval];
    return mergeIntervals(combined);
}


// Approach 5:  Binary Search Optimization (For Very Large Input)
//   - Uses binary search to find the insertion point for the new interval.
//   -  More efficient for very large input arrays, but adds complexity.
function insertInterval5(intervals, newInterval) {
  const start = newInterval[0];
  const end = newInterval[1];
  let left = 0;
  let right = intervals.length - 1;
  let insertPos = intervals.length;

  // Binary search to find the correct insertion point based on start time
  while (left <= right) {
    const mid = Math.floor((left + right) / 2);
    if (intervals[mid][0] < start) {
      left = mid + 1;
    } else {
      insertPos = mid;
      right = mid - 1;
    }
  }

  // Insert the new interval
  const extendedIntervals = [...intervals.slice(0, insertPos), newInterval, ...intervals.slice(insertPos)];
  const mergedIntervals = [];

  for (let i = 0; i < extendedIntervals.length; i++) {
        if (mergedIntervals.length === 0 || mergedIntervals[mergedIntervals.length-1][1] < extendedIntervals[i][0]) {
            mergedIntervals.push(extendedIntervals[i]);
        }
        else {
            mergedIntervals[mergedIntervals.length-1][1] = Math.max(mergedIntervals[mergedIntervals.length-1][1], extendedIntervals[i][1]);
        }
  }
  return mergedIntervals;
}



// Example Usage and Testing
const intervals1 = [[1, 3], [6, 9]];
const newInterval1 = [2, 5];
const intervals2 = [[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]];
const newInterval2 = [4, 8];
const intervals3 = [];
const newInterval3 = [5,7];
const intervals4 = [[1,5]];
const newInterval4 = [0,0];
const intervals5 = [[1,5]];
const newInterval5 = [6,8];

console.log("Approach 1: Simple Iterative");
console.log(insertInterval1(intervals1, newInterval1)); // Output: [[1, 5], [6, 9]]
console.log(insertInterval1(intervals2, newInterval2)); // Output: [[1, 2], [3, 10], [12, 16]]
console.log(insertInterval1(intervals3, newInterval3)); // Output: [[5, 7]]
console.log(insertInterval1(intervals4, newInterval4)); // Output: [[0, 0], [1, 5]]
console.log(insertInterval1(intervals5, newInterval5)); // Output: [[1, 5], [6, 8]]


console.log("\nApproach 2: Reduce with Accumulator");
console.log(insertInterval2(intervals1, newInterval1));
console.log(insertInterval2(intervals2, newInterval2));
console.log(insertInterval2(intervals3, newInterval3));
console.log(insertInterval2(intervals4, newInterval4));
console.log(insertInterval2(intervals5, newInterval5));


console.log("\nApproach 3: Iterative with Flags");
console.log(insertInterval3(intervals1, newInterval1));
console.log(insertInterval3(intervals2, newInterval2));
console.log(insertInterval3(intervals3, newInterval3));
console.log(insertInterval3(intervals4, newInterval4));
console.log(insertInterval3(intervals5, newInterval5));


console.log("\nApproach 4: Using a Separate Merge Function");
console.log(insertInterval4(intervals1, newInterval1));
console.log(insertInterval4(intervals2, newInterval2));
console.log(insertInterval4(intervals3, newInterval3));
console.log(insertInterval4(intervals4, newInterval4));
console.log(insertInterval4(intervals5, newInterval5));


console.log("\nApproach 5: Binary Search Optimization");
console.log(insertInterval5(intervals1, newInterval1));
console.log(insertInterval5(intervals2, newInterval2));
console.log(insertInterval5(intervals3, newInterval3));
console.log(insertInterval5(intervals4, newInterval4));
console.log(insertInterval5(intervals5, newInterval5));
