/**
 * You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi]
 * represent the start and the end of the ith interval and intervals is sorted in ascending order by starti.
 * You are also given an interval newInterval = [start, end] that represents the start and end of another interval.
 *
 * Insert newInterval into intervals such that intervals is still sorted in ascending order by starti
 * and intervals no longer has any overlapping intervals (merge overlapping intervals if necessary).
 *
 * Return the intervals after the insertion.
 *
 *
 * Example 1:
 *
 * Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
 * Output: [[1,5],[6,9]]
 *
 * Example 2:
 *
 * Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
 * Output: [[1,2],[3,10],[12,16]]
 *
 *
 * Constraints:
 *
 * 0 <= intervals.length <= 104
 * intervals[i].length == 2
 * 0 <= starti <= endi <= 104
 * intervals is sorted in ascending order by starti.
 * newInterval.length == 2
 * 0 <= start <= end <= 104
 */

/**
 * Approach 1: Iterative with Merge
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function insertInterval1(intervals, newInterval) {
    const result = [];
    let i = 0;

    // Add intervals before the overlap
    while (i < intervals.length && intervals[i][1] < newInterval[0]) {
        result.push(intervals[i]);
        i++;
    }

    // Merge overlapping intervals
    while (i < intervals.length && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = Math[1] = Math.max(newInterval[1], intervals[i][1]);
        i++;
    }
    result.push(newInterval);

    // Add intervals after the overlap
    while (i < intervals.length) {
        result.push(intervals[i]);
        i++;
    }

    return result;
}

/**
 * Approach 2: Simplified Iterative
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function insertInterval2(intervals, newInterval) {
    const result = [];
    for (let i = 0; i < intervals.length; i++) {
        if (newInterval[1] < intervals[i][0]) {
            result.push(newInterval);
            return result.concat(intervals.slice(i));
        } else if (newInterval[0] > intervals[i][1]) {
            result.push(intervals[i]);
        } else {
            newInterval[0] = Math.min(newInterval[0], intervals[i][0]);
            newInterval[1] = Math.max(newInterval[1], intervals[i][1]);
        }
    }
    result.push(newInterval);
    return result;
}
/**
 * Approach 3: Using Reduce
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function insertInterval3(intervals, newInterval) {
  let inserted = false;
  const result = intervals.reduce((acc, interval) => {
    if (newInterval[1] < interval[0]) {
      if (!inserted) {
        acc.push(newInterval);
        inserted = true;
      }
      acc.push(interval);
    } else if (newInterval[0] > interval[1]) {
      acc.push(interval);
    } else {
      newInterval[0] = Math.min(newInterval[0], interval[0]);
      newInterval[1] = Math.max(newInterval[1], interval[1]);
    }
    return acc;
  }, []);

  if (!inserted) {
    result.push(newInterval);
  }

  return result;
}

/**
 * Approach 4:  More concise iterative
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function insertInterval4(intervals, newInterval) {
    const result = [];
    let i = 0;

    while (i < intervals.length && intervals[i][1] < newInterval[0]) {
        result.push(intervals[i++]);
    }

    let start = newInterval[0];
    let end = newInterval[1];
    while (i < intervals.length && intervals[i][0] <= end) {
        start = Math.min(start, intervals[i][0]);
        end = Math.max(end, intervals[i++][1]);
    }
    result.push([start, end]);

    while (i < intervals.length) {
        result.push(intervals[i++]);
    }

    return result;
}

/**
 * Approach 5: Using for...of loop
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function insertInterval5(intervals, newInterval) {
    const result = [];
    let inserted = false;

    for (const interval of intervals) {
        if (newInterval[1] < interval[0]) {
            if (!inserted) {
                result.push(newInterval);
                inserted = true;
            }
            result.push(interval);
        } else if (newInterval[0] > interval[1]) {
            result.push(interval);
        } else {
            newInterval[0] = Math.min(newInterval[0], interval[0]);
            newInterval[1] = Math.max(newInterval[1], interval[1]);
        }
    }

    if (!inserted) {
        result.push(newInterval);
    }

    return result;
}



// Example Usage and Testing
const intervals1 = [[1, 3], [6, 9]];
const newInterval1 = [2, 5];
console.log("Example 1:");
console.log("Approach 1:", insertInterval1(intervals1, newInterval1)); // Output: [[1, 5], [6, 9]]
console.log("Approach 2:", insertInterval2(intervals1, newInterval1)); // Output: [[1, 5], [6, 9]]
console.log("Approach 3:", insertInterval3(intervals1, newInterval1)); // Output: [[1, 5], [6, 9]]
console.log("Approach 4:", insertInterval4(intervals1, newInterval1)); // Output: [[1, 5], [6, 9]]
console.log("Approach 5:", insertInterval5(intervals1, newInterval1)); // Output: [[1, 5], [6, 9]]



const intervals2 = [[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]];
const newInterval2 = [4, 8];
console.log("\nExample 2:");
console.log("Approach 1:", insertInterval1(intervals2, newInterval2)); // Output: [[1, 2], [3, 10], [12, 16]]
console.log("Approach 2:", insertInterval2(intervals2, newInterval2)); // Output: [[1, 2], [3, 10], [12, 16]]
console.log("Approach 3:", insertInterval3(intervals2, newInterval2)); // Output: [[1, 2], [3, 10], [12, 16]]
console.log("Approach 4:", insertInterval4(intervals2, newInterval2)); // Output: [[1, 2], [3, 10], [12, 16]]
console.log("Approach 5:", insertInterval5(intervals2, newInterval2)); // Output: [[1, 2], [3, 10], [12, 16]]


const intervals3 = [];
const newInterval3 = [4,8];
console.log("\nExample 3: Empty Intervals");
console.log("Approach 1:", insertInterval1(intervals3, newInterval3)); // Output: [[4, 8]]
console.log("Approach 2:", insertInterval2(intervals3, newInterval3)); // Output: [[4, 8]]
console.log("Approach 3:", insertInterval3(intervals3, newInterval3)); // Output: [[4, 8]]
console.log("Approach 4:", insertInterval4(intervals3, newInterval3)); // Output: [[4, 8]]
console.log("Approach 5:", insertInterval5(intervals3, newInterval3)); // Output: [[4, 8]]

const intervals4 = [[1,5]];
const newInterval4 = [2,3];
console.log("\nExample 4: New Interval inside");
console.log("Approach 1:", insertInterval1(intervals4, newInterval4)); // Output: [[1, 5]]
console.log("Approach 2:", insertInterval2(intervals4, newInterval4)); // Output: [[1, 5]]
console.log("Approach 3:", insertInterval3(intervals4, newInterval4)); // Output: [[1, 5]]
console.log("Approach 4:", insertInterval4(intervals4, newInterval4)); // Output: [[1, 5]]
console.log("Approach 5:", insertInterval5(intervals4, newInterval4)); // Output: [[1, 5]]

const intervals5 = [[1,5]];
const newInterval5 = [6,8];
console.log("\nExample 5: New Interval after");
console.log("Approach 1:", insertInterval1(intervals5, newInterval5)); // Output: [[1, 5], [6, 8]]
console.log("Approach 2:", insertInterval2(intervals5, newInterval5)); // Output: [[1, 5], [6, 8]]
console.log("Approach 3:", insertInterval3(intervals5, newInterval5)); // Output: [[1, 5], [6, 8]]
console.log("Approach 4:", insertInterval4(intervals5, newInterval5)); // Output: [[1, 5], [6, 8]]
console.log("Approach 5:", insertInterval5(intervals5, newInterval5)); // Output: [[1, 5], [6, 8]]

const intervals6 = [[1,5]];
const newInterval6 = [0,1];
console.log("\nExample 6: New Interval before");
console.log("Approach 1:", insertInterval1(intervals6, newInterval6)); // Output: [[0, 5]]
console.log("Approach 2:", insertInterval2(intervals6, newInterval6)); // Output: [[0, 5]]
console.log("Approach 3:", insertInterval3(intervals6, newInterval6)); // Output: [[0, 5]]
console.log("Approach 4:", insertInterval4(intervals6, newInterval6)); // Output: [[0, 5]]
console.log("Approach 5:", insertInterval5(intervals6, newInterval6)); // Output: [[0, 5]]
