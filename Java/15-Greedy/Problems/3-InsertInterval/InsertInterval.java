import java.util.ArrayList;
import java.util.List;

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
        // Example usage
        List<Interval> intervals1 = new ArrayList<>();
        intervals1.add(new Interval(1, 3));
        intervals1.add(new Interval(6, 9));
        Interval newInterval1 = new Interval(2, 5);
        System.out.println("Approach 1: " + insert1(intervals1, newInterval1)); // Expected: [[1,5],[6,9]]

        List<Interval> intervals2 = new ArrayList<>();
        intervals2.add(new Interval(1, 2));
        intervals2.add(new Interval(3, 5));
        intervals2.add(new Interval(6, 7));
        intervals2.add(new Interval(8, 10));
        intervals2.add(new Interval(12, 16));
        Interval newInterval2 = new Interval(4, 8);
        System.out.println("Approach 2: " + insert2(intervals2, newInterval2)); // Expected: [[1,2],[3,10],[12,16]]

        List<Interval> intervals3 = new ArrayList<>();
        intervals3.add(new Interval(1, 3));
        intervals3.add(new Interval(6, 9));
        Interval newInterval3 = new Interval(2, 5);
        System.out.println("Approach 3: " + insert3(intervals3, newInterval3));

        List<Interval> intervals4 = new ArrayList<>();
        intervals4.add(new Interval(1, 2));
        intervals4.add(new Interval(3, 5));
        intervals4.add(new Interval(6, 7));
        intervals4.add(new Interval(8, 10));
        intervals4.add(new Interval(12, 16));
        Interval newInterval4 = new Interval(4, 8);
        System.out.println("Approach 4: " + insert4(intervals4, newInterval4));

        List<Interval> intervals5 = new ArrayList<>();
        intervals5.add(new Interval(1, 3));
        intervals5.add(new Interval(6, 9));
        Interval newInterval5 = new Interval(2, 5);
        System.out.println("Approach 5: " + insert5(intervals5, newInterval5));
    }

    /**
     * Approach 1: Iterative with Merging
     * - Time Complexity: O(n), where n is the number of intervals.
     * - Space Complexity: O(n) in the worst case (new list).
     */
    public static List<Interval> insert1(List<Interval> intervals, Interval newInterval) {
        List<Interval> result = new ArrayList<>();
        int i = 0;

        // Add intervals that come before the new interval
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

        // Add the remaining intervals
        while (i < intervals.size()) {
            result.add(intervals.get(i));
            i++;
        }
        return result;
    }

    /**
     * Approach 2: Iterative with In-Place Modification (if allowed)
     * - Time Complexity: O(n), where n is the number of intervals.
     * - Space Complexity: O(1) if modifying the input list is allowed, O(n) for the new list.
     */
    public static List<Interval> insert2(List<Interval> intervals, Interval newInterval) {
        List<Interval> result = new ArrayList<>();
        int i = 0;

        // Add non-overlapping intervals before newInterval
        while (i < intervals.size() && intervals.get(i).end < newInterval.start) {
            result.add(intervals.get(i++));
        }

        // Merge overlapping intervals
        while (i < intervals.size() && intervals.get(i).start <= newInterval.end) {
            newInterval.start = Math.min(newInterval.start, intervals.get(i).start);
            newInterval.end = Math.max(newInterval.end, intervals.get(i).end);
            i++;
        }
        result.add(newInterval);

        // Add non-overlapping intervals after merged interval
        while (i < intervals.size()) {
            result.add(intervals.get(i++));
        }
        return result;
    }

    /**
     * Approach 3: Simplified Iterative
     * - Time Complexity: O(n)
     * - Space Complexity: O(n)
     */
    public static List<Interval> insert3(List<Interval> intervals, Interval newInterval) {
        List<Interval> result = new ArrayList<>();
        int i = 0;

        while (i < intervals.size() && intervals.get(i).end < newInterval.start) {
            result.add(intervals.get(i++));
        }

        if (i < intervals.size()) {
            while (i < intervals.size() && intervals.get(i).start <= newInterval.end) {
                newInterval.start = Math.min(newInterval.start, intervals.get(i).start);
                newInterval.end = Math.max(newInterval.end, intervals.get(i).end);
                i++;
            }
        }
        result.add(newInterval);

        while (i < intervals.size()) {
            result.add(intervals.get(i++));
        }

        return result;
    }

    /**
     * Approach 4:  More concise iterative
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public static List<Interval> insert4(List<Interval> intervals, Interval newInterval) {
        List<Interval> result = new ArrayList<>();
        int i = 0;

        while (i < intervals.size() && intervals.get(i).end < newInterval.start)
            result.add(intervals.get(i++));

        while (i < intervals.size() && intervals.get(i).start <= newInterval.end) {
            newInterval.start = Math.min(newInterval.start, intervals.get(i).start);
            newInterval.end = Math.max(newInterval.end, intervals.get(i).end);
            i++;
        }
        result.add(newInterval);

        while (i < intervals.size())
            result.add(intervals.get(i++));

        return result;
    }

    /**
     * Approach 5: Using a for-each loop
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public static List<Interval> insert5(List<Interval> intervals, Interval newInterval) {
        List<Interval> result = new ArrayList<>();

        boolean inserted = false;
        for (Interval interval : intervals) {
            if (interval.end < newInterval.start) {
                result.add(interval);
            } else if (interval.start > newInterval.end) {
                if (!inserted) {
                    result.add(newInterval);
                    inserted = true;
                }
                result.add(interval);
            } else {
                newInterval.start = Math.min(newInterval.start, interval.start);
                newInterval.end = Math.max(newInterval.end, interval.end);
            }
        }
        if (!inserted) {
            result.add(newInterval);
        }
        return result;
    }
}

