import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.LinkedList;

public class InsertInterval {

    // Definition for an interval.
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

    public static void main(String[] args) {
        // Example Usage
        List<Interval> intervals1 = new ArrayList<>(Arrays.asList(
                new Interval(1, 3),
                new Interval(6, 9)
        ));
        Interval newInterval1 = new Interval(2, 5);
        System.out.println("Approach 1: " + insert1(intervals1, newInterval1)); // Expected: [[1,5],[6,9]]

        List<Interval> intervals2 = new ArrayList<>(Arrays.asList(
                new Interval(1, 2),
                new Interval(3, 5),
                new Interval(6, 7),
                new Interval(8, 10),
                new Interval(12, 16)
        ));
        Interval newInterval2 = new Interval(4, 8);
        System.out.println("Approach 2: " + insert2(intervals2, newInterval2)); // Expected: [[1,2],[3,10],[12,16]]

        List<Interval> intervals3 = new ArrayList<>(Arrays.asList(
                new Interval(1, 2),
                new Interval(3, 5),
                new Interval(6, 7),
                new Interval(8, 10),
                new Interval(12, 16)
        ));
        Interval newInterval3 = new Interval(4, 8);
        System.out.println("Approach 3: " + insert3(intervals3, newInterval3));

        List<Interval> intervals4 = new ArrayList<>(Arrays.asList(
                new Interval(1, 2),
                new Interval(3, 5),
                new Interval(6, 7),
                new Interval(8, 10),
                new Interval(12, 16)
        ));
        Interval newInterval4 = new Interval(4, 8);
        System.out.println("Approach 4: " + insert4(intervals4, newInterval4));

        List<Interval> intervals5 = new ArrayList<>(Arrays.asList(
                new Interval(1, 2),
                new Interval(3, 5),
                new Interval(6, 7),
                new Interval(8, 10),
                new Interval(12, 16)
        ));
        Interval newInterval5 = new Interval(4, 8);
        System.out.println("Approach 5: " + insert5(intervals5, newInterval5));
    }

    /**
     * Approach 1: Iterative with Merging
     *
     * Core Idea:
     * 1.  Iterate through the existing intervals.
     * 2.  For each interval, check for overlap with the new interval.
     * 3.  If overlap exists, merge the intervals.
     * 4.  If no overlap, add the existing interval to the result.
     * 5.  Handle edge cases (new interval before/after all existing).
     *
     * Time Complexity: O(n) - Linear time, where n is the number of intervals.
     * Space Complexity: O(n) -  In the worst case, we create a new list of size n.
     *
     * Real-world application:
     * -   Calendar event management: Merging or inserting new appointments.
     * -   Resource scheduling:  Combining or adding time slots for resources.
     */
    public static List<Interval> insert1(List<Interval> intervals, Interval newInterval) {
        List<Interval> result = new ArrayList<>();
        int i = 0;

        // Add intervals occurring before the new interval
        while (i < intervals.size() && intervals.get(i).end < newInterval.start) {
            result.add(intervals.get(i));
            i++;
        }

        // Merge overlapping intervals
        while (i < intervals.size() && intervals.get(i).start <= newInterval.end) {
            newInterval.start = Math.min(newInterval.start, intervals.get(i).start);
            newInterval.end = Math.max(newInterval.end, intervals.get(i).end);
            i++;
        }
        result.add(newInterval); // Add the merged interval

        // Add intervals occurring after the new interval
        while (i < intervals.size()) {
            result.add(intervals.get(i));
            i++;
        }
        return result;
    }

    /**
     * Approach 2: Simplified Iterative
     *
     * Core Idea:
     * 1. Improved version of Approach 1 with more concise code.
     * 2. Uses a single loop to handle all three cases: before, overlapping, and after.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     *
     * Real-world application:
     * -   Similar to Approach 1, but with a cleaner implementation.
     * -  Any application where intervals need to be processed sequentially.
     */
    public static List<Interval> insert2(List<Interval> intervals, Interval newInterval) {
        List<Interval> result = new ArrayList<>();
        for (Interval interval : intervals) {
            if (newInterval == null || interval.end < newInterval.start) {
                result.add(interval);
            } else if (interval.start > newInterval.end) {
                result.add(newInterval);
                result.add(interval);
                newInterval = null; // Important:  Prevent further merging
            } else {
                newInterval.start = Math.min(newInterval.start, interval.start);
                newInterval.end = Math.max(newInterval.end, interval.end);
            }
        }
        if (newInterval != null) { // Add the new interval if it wasn't merged
            result.add(newInterval);
        }
        return result;
    }

    /**
     * Approach 3: Using LinkedList for Efficient Insertion
     *
     * Core Idea:
     * 1. Uses a LinkedList to avoid O(n) shifting when inserting in the middle.
     * 2. Logic is similar to Approach 1.
     *
     * Time Complexity: O(n) -  LinkedList insertion is O(1) on average, but iteration is still O(n).
     * Space Complexity: O(n) -  Uses a LinkedList to store the result.
     *
     * Real-world application:
     * -   When there are frequent insertions in the middle of the interval list.
     * -   Less suitable for very large lists where ArrayList might have better constant factors.
     */
    public static List<Interval> insert3(List<Interval> intervals, Interval newInterval) {
        LinkedList<Interval> result = new LinkedList<>();
        int i = 0;

        while (i < intervals.size() && intervals.get(i).end < newInterval.start) {
            result.add(intervals.get(i++));
        }

        while (i < intervals.size() && intervals.get(i).start <= newInterval.end) {
            newInterval.start = Math.min(newInterval.start, intervals.get(i).start);
            newInterval.end = Math.max(newInterval.end, intervals.get(i++).end);
        }
        result.add(newInterval);

        while (i < intervals.size()) {
            result.add(intervals.get(i++));
        }
        return new ArrayList<>(result); // Convert back to ArrayList if needed
    }

    /**
     * Approach 4: In-place Modification (Less Common, Be Cautious)
     *
     * Core Idea:
     * 1.  Modifies the original 'intervals' list directly to save space.
     * 2.  This approach can be risky if the original list is needed elsewhere.
     * 3.  It's generally better to return a *new* list.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1) - Modifies input in-place.
     *
     * Real-world application:
     * -   Memory-constrained environments where creating a new list is expensive.
     * -   When the original 'intervals' list is guaranteed to not be used again.
     * -   **Use with extreme caution and clear documentation!** This modifies the input.
     */
    public static List<Interval> insert4(List<Interval> intervals, Interval newInterval) {
        int i = 0;

        while (i < intervals.size() && intervals.get(i).end < newInterval.start) {
            i++;
        }

        while (i < intervals.size() && intervals.get(i).start <= newInterval.end) {
            newInterval.start = Math.min(newInterval.start, intervals.get(i).start);
            newInterval.end = Math.max(newInterval.end, intervals.get(i).end);
            intervals.remove(i); // Remove the merged interval.  i is NOT incremented.
        }
        intervals.add(i, newInterval); // Insert the merged interval
        return intervals;
    }

    /**
     * Approach 5:  Binary Search (Optimized for Sorted Input)
     *
     * Core Idea:
     * 1. If the input 'intervals' list is sorted, we can use binary search
     * to find the insertion point, improving efficiency.
     * 2. This approach assumes the input list is already sorted.
     *
     * Time Complexity: O(log n) to find insertion point, O(n) to merge = O(n)
     * Space Complexity: O(n)
     *
     * Real-world application:
     * -   When dealing with a large number of *pre-sorted* intervals.
     * -   Database systems:  Efficiently inserting time ranges into sorted tables.
     */
    public static List<Interval> insert5(List<Interval> intervals, Interval newInterval) {
        int left = 0, right = intervals.size();
        int insertPos = intervals.size(); // Default: insert at the end

        // Binary search to find the correct insertion position
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (intervals.get(mid).end < newInterval.start) {
                left = mid + 1;
            } else if (intervals.get(mid).start > newInterval.end) {
                insertPos = mid; // Potential insertion point
                right = mid - 1;
            } else {
                // Overlap found during binary search, no need to optimize insertion point
                break;
            }
        }

        intervals.add(insertPos, newInterval); // Insert.  Expensive for ArrayList.

        // Merge logic (same as Approach 1 or 2)
        List<Interval> result = new ArrayList<>();
        for (int i = 0; i < intervals.size(); i++) {
            if (i == 0 || result.get(result.size() - 1).end < intervals.get(i).start) {
                result.add(intervals.get(i));
            } else {
                Interval last = result.get(result.size() - 1);
                last.end = Math.max(last.end, intervals.get(i).end);
            }
        }
        return result;
    }
}

