import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Collections;
import java.util.Comparator;

/**
 * Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals
 * and return an array of the non-overlapping intervals that cover all the intervals in the input.
 *
 * Example 1:
 *
 * Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
 * Output: [[1,6],[8,10],[15,18]]
 * Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
 *
 * Example 2:
 *
 * Input: intervals = [[1,4],[4,5]]
 * Output: [[1,5]]
 * Explanation: Intervals [1,4] and [4,5] are considered overlapping.
 */
public class MergeIntervals {

    // Definition of Interval (same as problem description) - No need to redefine.
    public static class Interval {
        int start;
        int end;

        Interval() {
            start = 0;
            end = 0;
        }

        Interval(int s, int e) {
            start = s;
            end = e;
        }

        @Override
        public String toString() {
            return "[" + start + "," + end + "]";
        }
    }

    /**
     * Approach 1: Sorting and Iterative Merging
     *
     * 1.  Sort the intervals by start time.
     * 2.  Iterate through the sorted intervals.
     * 3.  If the current interval overlaps with the previous merged interval, merge them.
     * 4.  Otherwise, add the current interval to the result.
     *
     * Time Complexity: O(n log n) for sorting, O(n) for merging => O(n log n)
     * Space Complexity: O(n) for the result list in the worst case.  O(1) if modifying input array (careful with this).
     */
    public static List<Interval> merge1(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) {
            return convertToIntervalList(intervals); // Handles edge cases and conversion
        }

        // Sort the intervals by start time using a lambda comparator.
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));

        List<Interval> mergedIntervals = new ArrayList<>();
        Interval currentInterval = new Interval(intervals[0][0], intervals[0][1]); // Initialize with the first interval

        for (int i = 1; i < intervals.length; i++) {
            int currentStart = intervals[i][0];
            int currentEnd = intervals[i][1];

            if (currentStart <= currentInterval.end) {
                // Overlapping intervals, merge
                currentInterval.end = Math.max(currentInterval.end, currentEnd); // Important:  Take the max of the ends
            } else {
                // Non-overlapping interval, add the previous merged interval and update currentInterval
                mergedIntervals.add(currentInterval);
                currentInterval = new Interval(currentStart, currentEnd);
            }
        }

        // Add the last merged interval
        mergedIntervals.add(currentInterval);
        return mergedIntervals;
    }

    /**
     * Approach 2: In-place Merging (if allowed to modify input array)
     *
     * This approach modifies the input array directly to save space.  It's more efficient
     * in terms of space, but it alters the original input.
     *
     * 1. Sort the intervals by start time.
     * 2. Use two pointers: one to track the last merged interval (`index`) and another to iterate
     * through the intervals.
     * 3. If the current interval overlaps with the last merged interval, merge them in-place.
     * 4. Otherwise, move the `index` pointer and place the current interval at that position.
     *
     * Time Complexity: O(n log n) for sorting, O(n) for merging => O(n log n)
     * Space Complexity: O(1) (modifies input array)
     */
    public static List<Interval> merge2(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) {
            return convertToIntervalList(intervals);
        }

        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0])); // Sort by start

        int index = 0; // Index of the last merged interval
        for (int i = 1; i < intervals.length; i++) {
            if (intervals[i][0] <= intervals[index][1]) {
                // Overlap:  Merge in-place.  Important to use Math.max
                intervals[index][1] = Math.max(intervals[index][1], intervals[i][1]);
            } else {
                // No overlap: Move the 'index' and update
                index++;
                intervals[index][0] = intervals[i][0];
                intervals[index][1] = intervals[i][1];
            }
        }
        // Construct the result list from the modified input array.  Only take the merged intervals.
        List<Interval> result = new ArrayList<>();
        for (int i = 0; i <= index; i++) {
            result.add(new Interval(intervals[i][0], intervals[i][1]));
        }
        return result;
    }

    /**
     * Approach 3: Using a Priority Queue (for unsorted intervals)
     *
     * If the intervals are not sorted, we can use a priority queue to sort them efficiently.
     * 1.  Create a priority queue ordered by the start time of the intervals.
     * 2.  Add all intervals to the priority queue.
     * 3.  Poll intervals from the priority queue and merge them as in Approach 1.
     *
     * Time Complexity: O(n log n) for adding to and polling from the priority queue
     * Space Complexity: O(n) for the priority queue and the result list
     */
    public static List<Interval> merge3(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) {
            return convertToIntervalList(intervals);
        }

        // Use a min-heap (PriorityQueue) to sort intervals by start time.
        PriorityQueue<Interval> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a.start));
        for (int[] interval : intervals) {
            pq.offer(new Interval(interval[0], interval[1]));
        }

        List<Interval> mergedIntervals = new ArrayList<>();
        Interval currentInterval = pq.poll(); // Initialize

        while (!pq.isEmpty()) {
            Interval nextInterval = pq.poll();
            if (nextInterval.start <= currentInterval.end) {
                currentInterval.end = Math.max(currentInterval.end, nextInterval.end);
            } else {
                mergedIntervals.add(currentInterval);
                currentInterval = nextInterval;
            }
        }
        mergedIntervals.add(currentInterval); // Add the last one
        return mergedIntervals;
    }

    /**
     * Approach 4: Using Collections.sort() with a custom Comparator (alternative to Approach 1)
     *
     * This approach is very similar to Approach 1, but it uses `Collections.sort()` instead of `Arrays.sort()`.
     * This approach can be used if you convert the int[][] to List<Interval> first.
     *
     * 1. Convert the int[][] intervals to a List<Interval>
     * 2. Sort the list using Collections.sort() and a custom Comparator.
     * 3. Merge the intervals as in Approach 1.
     *
     * Time Complexity: O(n log n) for sorting, O(n) for merging => O(n log n)
     * Space Complexity: O(n) for the list and the result.
     */
    public static List<Interval> merge4(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) {
            return convertToIntervalList(intervals);
        }

        // Convert the int[][] to List<Interval>
        List<Interval> intervalList = convertToIntervalList(intervals);

        // Sort the intervals using Collections.sort() and a custom Comparator.
        Collections.sort(intervalList, (a, b) -> Integer.compare(a.start, b.start));

        List<Interval> mergedIntervals = new ArrayList<>();
        Interval currentInterval = intervalList.get(0);

        for (int i = 1; i < intervalList.size(); i++) {
            Interval nextInterval = intervalList.get(i);
            if (nextInterval.start <= currentInterval.end) {
                currentInterval.end = Math.max(currentInterval.end, nextInterval.end);
            } else {
                mergedIntervals.add(currentInterval);
                currentInterval = nextInterval;
            }
        }
        mergedIntervals.add(currentInterval);
        return mergedIntervals;
    }

    /**
     * Approach 5: Iterative with Nested Loop (Less Efficient - For illustration)
     *
     * This is a less efficient approach, included for comparison.  It has a nested loop,
     * leading to a higher time complexity.
     *
     * 1. Create a list to store the merged intervals.
     * 2. Iterate through the input intervals.
     * 3. For each interval, check for overlaps with existing merged intervals.
     * 4. If an overlap is found, merge with the existing interval.
     * 5. If no overlap, add the interval to the merged list.
     *
     * Time Complexity: O(n^2) in the worst case (nested loops)
     * Space Complexity: O(n) for the result list
     */
    public static List<Interval> merge5(int[][] intervals) {
        if (intervals == null || intervals.length <= 1) {
            return convertToIntervalList(intervals);
        }

        List<Interval> mergedIntervals = new ArrayList<>();
        for (int[] interval : intervals) {
            Interval current = new Interval(interval[0], interval[1]);
            boolean merged = false;
            for (int j = 0; j < mergedIntervals.size(); j++) {
                Interval existing = mergedIntervals.get(j);
                if (current.start <= existing.end && current.end >= existing.start) {
                    // Overlap found, merge
                    existing.start = Math.min(current.start, existing.start);
                    existing.end = Math.max(current.end, existing.end);
                    merged = true;
                    break;
                }
            }
            if (!merged) {
                mergedIntervals.add(current);
            }
        }
        return mergedIntervals;
    }

    // Helper method to convert int[][] to List<Interval>
    private static List<Interval> convertToIntervalList(int[][] intervals) {
        List<Interval> intervalList = new ArrayList<>();
        if (intervals != null) { // Handle null input
            for (int[] interval : intervals) {
                intervalList.add(new Interval(interval[0], interval[1]));
            }
        }
        return intervalList;
    }

    public static void main(String[] args) {
        // Test cases
        int[][] intervals1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
        int[][] intervals2 = {{1, 4}, {4, 5}};
        int[][] intervals3 = {{1, 4}, {0, 4}};
        int[][] intervals4 = {{1, 4}, {0, 0}};
        int[][] intervals5 = {{1, 4}, {0, 1}};
        int[][] intervals6 = {{2, 3}, {4, 5}, {6, 7}, {8, 9}, {1, 10}};
        int[][] intervals7 = {{2, 3}, {2, 2}, {3, 3}, {1, 3}, {5, 6}, {5, 5}, {4, 6}};


        System.out.println("Test Case 1 - Approach 1: " + merge1(intervals1)); // [[1,6],[8,10],[15,18]]
        System.out.println("Test Case 2 - Approach 1: " + merge1(intervals2)); // [[1,5]]
        System.out.println("Test Case 3 - Approach 1: " + merge1(intervals3)); // [[0,4]]
        System.out.println("Test Case 4 - Approach 1: " + merge1(intervals4)); // [[0,0],[1,4]]
        System.out.println("Test Case 5 - Approach 1: " + merge1(intervals5)); // [[0,4]]
        System.out.println("Test Case 6 - Approach 1: " + merge1(intervals6)); // [[1,10]]
        System.out.println("Test Case 7 - Approach 1: " + merge1(intervals7)); // [[1,3],[4,6]]


        System.out.println("Test Case 1 - Approach 2: " + merge2(intervals1));
        System.out.println("Test Case 2 - Approach 2: " + merge2(intervals2));
        System.out.println("Test Case 3 - Approach 2: " + merge2(intervals3));
        System.out.println("Test Case 4 - Approach 2: " + merge2(intervals4));
        System.out.println("Test Case 5 - Approach 2: " + merge2(intervals5));
        System.out.println("Test Case 6 - Approach 2: " + merge2(intervals6));
        System.out.println("Test Case 7 - Approach 2: " + merge2(intervals7));


        System.out.println("Test Case 1 - Approach 3: " + merge3(intervals1));
        System.out.println("Test Case 2 - Approach 3: " + merge3(intervals2));
        System.out.println("Test Case 3 - Approach 3: " + merge3(intervals3));
        System.out.println("Test Case 4 - Approach 3: " + merge3(intervals4));
        System.out.println("Test Case 5 - Approach 3: " + merge3(intervals5));
        System.out.println("Test Case 6 - Approach 3: " + merge3(intervals6));
        System.out.println("Test Case 7 - Approach 3: " + merge3(intervals7));


        System.out.println("Test Case 1 - Approach 4: " + merge4(intervals1));
        System.out.println("Test Case 2 - Approach 4: " + merge4(intervals2));
        System.out.println("Test Case 3 - Approach 4: " + merge4(intervals3));
        System.out.println("Test Case 4 - Approach 4: " + merge4(intervals4));
        System.out.println("Test Case 5 - Approach 4: " + merge4(intervals5));
        System.out.println("Test Case 6 - Approach 4: " + merge4(intervals6));
        System.out.println("Test Case 7 - Approach 4: " + merge4(intervals7));


        System.out.println("Test Case 1 - Approach 5: " + merge5(intervals1));
        System.out.println("Test Case 2 - Approach 5: " + merge5(intervals2));
        System.out.println("Test Case 3 - Approach 5: " + merge5(intervals3));
        System.out.println("Test Case 4 - Approach 5: " + merge5(intervals4));
        System.out.println("Test Case 5 - Approach 5: " + merge5(intervals5));
        System.out.println("Test Case 6 - Approach 5: " + merge5(intervals6));
        System.out.println("Test Case 7 - Approach 5: " + merge5(intervals7));
    }
}

