import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Collections;
import java.util.Comparator;

/**
 * LeetCode Problem 56 - Merge Intervals
 *
 * Problem Statement:
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals
 * and return an array of the non-overlapping intervals that cover all the intervals in the input.
 *
 * Example 1:
 * Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
 *
 * Example 2:
 * Input: intervals = [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 */
public class MergeIntervals {

    // Approach 1: Sorting and Iterative Merging
    // Time Complexity: O(n log n) for sorting, O(n) for merging.  Overall: O(n log n)
    // Space Complexity: O(n) in the worst case for the result list.  Can be O(1) if merging in place (but modifies input).
    //
    // Real-world application:  This is the most common and generally preferred approach.  Good for general use cases.
    //   -  Calendar event merging:  Merging overlapping time slots.
    //   -  Resource scheduling:  Combining adjacent time slots for resource allocation.
    public static int[][] mergeIntervals_Sorting(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) {
            return intervals;
        }

        // Sort the intervals by their start times.  Arrays.sort uses a variant of quicksort, O(n log n).
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0])); // Using lambda for concise comparison

        List<int[]> mergedIntervals = new ArrayList<>();
        int[] currentInterval = intervals[0]; // Initialize with the first interval

        // Iterate through the sorted intervals, merging as needed.
        for (int i = 1; i < intervals.length; i++) {
            int[] nextInterval = intervals[i];

            // Check for overlap: currentEnd >= nextStart
            if (currentInterval[1] >= nextInterval[0]) {
                // Merge intervals:  Extend the end of the current interval.
                currentInterval[1] = Math.max(currentInterval[1], nextInterval[1]); // Important:  Take the max of the two ends.
            } else {
                // No overlap:  Add the current interval to the result and update currentInterval.
                mergedIntervals.add(currentInterval);
                currentInterval = nextInterval;
            }
        }

        // Add the last interval to the result.  Crucial!
        mergedIntervals.add(currentInterval);

        // Convert the list of intervals to a 2D array.
        return mergedIntervals.toArray(new int[mergedIntervals.size()][]);
    }


    // Approach 2: Using a Priority Queue (Min Heap)
    // Time Complexity: O(n log n).  O(n log n) to insert into the priority queue, and O(n log n) to extract.
    // Space Complexity: O(n) for the priority queue.
    //
    // Real-world application:  Useful when intervals are arriving in a stream or are not pre-sorted.
    //   -  Online event management:  Merging events as they are received.
    //   -  Dynamic resource allocation:  Merging resource requests as they come in.
    public static int[][] mergeIntervals_PriorityQueue(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) {
            return intervals;
        }

        // Create a min-heap (PriorityQueue) to store intervals, sorted by start time.
        PriorityQueue<int[]> minHeap = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        Collections.addAll(minHeap, intervals); // Add all intervals to the heap

        List<int[]> mergedIntervals = new ArrayList<>();
        int[] currentInterval = minHeap.poll(); // Get the interval with the earliest start

        while (!minHeap.isEmpty()) {
            int[] nextInterval = minHeap.poll();

            if (currentInterval[1] >= nextInterval[0]) {
                currentInterval[1] = Math.max(currentInterval[1], nextInterval[1]);
            } else {
                mergedIntervals.add(currentInterval);
                currentInterval = nextInterval;
            }
        }
        mergedIntervals.add(currentInterval); // Add the last interval

        return mergedIntervals.toArray(new int[mergedIntervals.size()][]);
    }

    // Approach 3:  In-Place Merging (Destructive) -  Only works if input array is modifiable
    // Time Complexity: O(n log n) for sorting, O(n) for merging. Overall: O(n log n)
    // Space Complexity: O(1) - modifies the input array directly.
    //
    // Real-world application:  Useful when memory is extremely limited and modifying the input is acceptable.
    //   -  Embedded systems:  Minimizing memory footprint.
    //   -  Certain data processing scenarios:  Where in-place modification is allowed for efficiency.
    public static int[][] mergeIntervals_InPlace(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) {
            return intervals;
        }

        // Sort the intervals by start time.
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));

        int mergeIndex = 0; // Index to track the position of the merged intervals

        for (int i = 1; i < intervals.length; i++) {
            // Overlap
            if (intervals[mergeIndex][1] >= intervals[i][0]) {
                intervals[mergeIndex][1] = Math.max(intervals[mergeIndex][1], intervals[i][1]);
            } else {
                // No overlap, move the merged interval forward
                mergeIndex++;
                intervals[mergeIndex][0] = intervals[i][0]; // Copy the start of the non-overlapping interval
                intervals[mergeIndex][1] = intervals[i][1]; // Copy the end
            }
        }

        // Create a new array with the merged intervals.  Important:  The original 'intervals' array
        //  has been modified, and may contain extra, non-merged intervals at the end.
        int[][] result = new int[mergeIndex + 1][2];
        for (int i = 0; i <= mergeIndex; i++) {
            result[i] = intervals[i];
        }
        return result;
    }


    // Approach 4: Iterative, No Sorting (Find Minimum Start Time Iteratively)
    // Time Complexity: O(n^2).  For each merge, it iterates through the remaining intervals.
    // Space Complexity: O(n) for the result list.
    //
    // Real-world application:  This approach is generally less efficient than sorting, but it *could*
    //   be adapted for situations where sorting is extremely expensive and the number of intervals is small.
    //   It's generally NOT recommended for typical use.
    public static int[][] mergeIntervals_NoSort(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) {
            return intervals;
        }

        List<int[]> mergedIntervals = new ArrayList<>();
        List<int[]> intervalsList = new ArrayList<>(Arrays.asList(intervals)); // Use ArrayList for easy removal

        while (!intervalsList.isEmpty()) {
            int minStartIndex = 0;
            // Find the interval with the minimum start time.
            for (int i = 1; i < intervalsList.size(); i++) {
                if (intervalsList.get(i)[0] < intervalsList.get(minStartIndex)[0]) {
                    minStartIndex = i;
                }
            }
            int[] currentInterval = intervalsList.get(minStartIndex);
            intervalsList.remove(minStartIndex); // Remove the selected interval

            int i = 0;
            while (i < intervalsList.size()) {
                int[] nextInterval = intervalsList.get(i);
                if (currentInterval[1] >= nextInterval[0]) {
                    // Merge
                    currentInterval[1] = Math.max(currentInterval[1], nextInterval[1]);
                    intervalsList.remove(i); // Remove the merged interval from the list (no need to increment i)
                } else if (nextInterval[1] >= currentInterval[0]) { // Check the other way around as well.
                    currentInterval[0] = Math.min(currentInterval[0], nextInterval[0]);
                    currentInterval[1] = Math.max(currentInterval[1], nextInterval[1]);
                    intervalsList.remove(i);
                }
                else {
                    i++; // Only increment if no merge happened
                }
            }
            mergedIntervals.add(currentInterval);
        }
        return mergedIntervals.toArray(new int[mergedIntervals.size()][]);
    }

    // Approach 5: Using a Stack (Similar to Sorting, but with explicit Stack)
    // Time Complexity: O(n log n) for sorting, O(n) for merging.  Overall: O(n log n)
    // Space Complexity: O(n) for the stack and the result list.
    //
    // Real-world application:  This approach provides an alternative way to manage the merging process,
    //   and can be helpful in scenarios where a stack-like data structure is naturally used in the surrounding code.
    public static int[][] mergeIntervals_Stack(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) {
            return intervals;
        }

        // Sort the intervals by start time
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));

        // Use a Stack to keep track of the merged intervals.
        java.util.Stack<int[]> stack = new java.util.Stack<>();
        stack.push(intervals[0]); // Push the first interval onto the stack

        for (int i = 1; i < intervals.length; i++) {
            int[] currentInterval = intervals[i];
            int[] topInterval = stack.peek();

            if (topInterval[1] >= currentInterval[0]) {
                // Overlapping, merge with the top of the stack
                topInterval[1] = Math.max(topInterval[1], currentInterval[1]);
            } else {
                // No overlap, push the current interval onto the stack
                stack.push(currentInterval);
            }
        }

        // Convert the stack to a 2D array.
        int[][] mergedIntervals = new int[stack.size()][2];
        for (int i = mergedIntervals.length - 1; i >= 0; i--) {
            mergedIntervals[i] = stack.pop();
        }
        return mergedIntervals;
    }


    public static void main(String[] args) {
        // Test cases
        int[][] intervals1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
        int[][] intervals2 = {{1, 4}, {4, 5}};
        int[][] intervals3 = {{1, 4}, {0, 4}};
        int[][] intervals4 = {{1, 4}, {0, 0}};
        int[][] intervals5 = {{1, 4}, {0, 1}};
        int[][] intervals6 = {{2,3},{4,5},{6,7},{8,9},{1,10}};


        System.out.println("Test Case 1 - Sorting:");
        printIntervals(mergeIntervals_Sorting(intervals1)); // Expected: [[1, 6], [8, 10], [15, 18]]

        System.out.println("\nTest Case 2 - Priority Queue:");
        printIntervals(mergeIntervals_PriorityQueue(intervals2)); // Expected: [[1, 5]]

        System.out.println("\nTest Case 3 - In-Place:");
        int[][] intervals3Copy = Arrays.copyOf(intervals3, intervals3.length); // Make a copy, as in-place modifies
        printIntervals(mergeIntervals_InPlace(intervals3Copy)); // Expected: [[0, 4]]

        System.out.println("\nTest Case 4 - No Sort:");
        printIntervals(mergeIntervals_NoSort(intervals4));     // Expected: [[0, 0], [1, 4]]

        System.out.println("\nTest Case 5 - Stack:");
        printIntervals(mergeIntervals_Stack(intervals5));       // Expected: [[0, 4]]

        System.out.println("\nTest Case 6 - Overlapping and Non-overlapping:");
        printIntervals(mergeIntervals_Sorting(intervals6));  // Expected: [[1, 10]]
    }

    // Helper method to print the intervals in a readable format
    private static void printIntervals(int[][] intervals) {
        System.out.print("[");
        for (int i = 0; i < intervals.length; i++) {
            System.out.print(Arrays.toString(intervals[i]));
            if (i < intervals.length - 1) {
                System.out.print(", ");
            }
        }
        System.out.println("]");
    }
}

