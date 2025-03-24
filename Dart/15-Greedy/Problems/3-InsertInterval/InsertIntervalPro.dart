import 'dart:math';

// Definition for an interval.
class Interval {
  int start;
  int end;
  Interval(this.start, this.end);

  @override
  String toString() {
    return '[$start, $end]';
  }
}

class InsertInterval {
  // Approach 1: Iterative with Comparisons
  // Time Complexity: O(n), Space Complexity: O(n)
  List<Interval> insertInterval1(List<Interval> intervals, Interval newInterval) {
    List<Interval> result = [];
    int i = 0;

    // Add intervals occurring before the new interval.
    while (i < intervals.length && intervals[i].end < newInterval.start) {
      result.add(intervals[i]);
      i++;
    }

    // Merge overlapping intervals.
    while (i < intervals.length && intervals[i].start <= newInterval.end) {
      newInterval.start = min(newInterval.start, intervals[i].start);
      newInterval.end = max(newInterval.end, intervals[i].end);
      i++;
    }

    // Add the merged interval.
    result.add(newInterval);

    // Add the remaining intervals.
    while (i < intervals.length) {
      result.add(intervals[i]);
      i++;
    }

    return result;
  }

  // Approach 2: Using List.insert and List.remove
  // Time Complexity: O(n), Space Complexity: O(n)
  List<Interval> insertInterval2(List<Interval> intervals, Interval newInterval) {
    // Create a copy to avoid modifying the original list directly.
    List<Interval> modifiedIntervals = List.from(intervals);

    // Find the insertion point.
    int insertIndex = 0;
    while (insertIndex < modifiedIntervals.length &&
        modifiedIntervals[insertIndex].start < newInterval.start) {
      insertIndex++;
    }
    modifiedIntervals.insert(insertIndex, newInterval); // Insert the new interval

    // Merge overlapping intervals
    List<Interval> result = [];
    for (int i = 0; i < modifiedIntervals.length; i++) {
      Interval current = modifiedIntervals[i];
      if (result.isEmpty || result.last.end < current.start) {
        result.add(current);
      } else {
        result.last.end = max(result.last.end, current.end);
      }
    }
    return result;
  }

  // Approach 3:  Fold Method
  // Time Complexity: O(n), Space Complexity: O(n)
  List<Interval> insertInterval3(List<Interval> intervals, Interval newInterval) {
    List<Interval> combined = [...intervals, newInterval];
    combined.sort((a, b) => a.start.compareTo(b.start));

    return combined.fold<List<Interval>>([], (List<Interval> merged, interval) {
      if (merged.isEmpty || merged.last.end < interval.start) {
        merged.add(interval);
      } else {
        merged.last.end = max(merged.last.end, interval.end);
      }
      return merged;
    });
  }

  // Approach 4: Using Recursion
  // Time Complexity: O(n), Space Complexity: O(n) (due to recursion)
  List<Interval> insertInterval4(List<Interval> intervals, Interval newInterval) {
    if (intervals.isEmpty) {
      return [newInterval];
    }

    return _insertRecursive(intervals, newInterval, 0);
  }

  List<Interval> _insertRecursive(List<Interval> intervals, Interval newInterval, int index) {
    if (index >= intervals.length) {
      return [newInterval]; // Base case: add newInterval if we reach the end
    }

    if (newInterval.start > intervals[index].end) {
      // If newInterval is after current interval, add current and recurse
      List<Interval> result = _insertRecursive(intervals, newInterval, index + 1);
      return [intervals[index], ...result];
    } else if (newInterval.end < intervals[index].start) {
      // If newInterval is before current interval, insert and return
      List<Interval> result = _insertRecursive(intervals, newInterval, index + 1);
      return [newInterval, intervals[index], ...result];
    } else {
      // Overlapping case: merge and recurse
      newInterval.start = min(newInterval.start, intervals[index].start);
      newInterval.end = max(newInterval.end, intervals[index].end);
      return _insertRecursive(intervals, newInterval, index + 1);
    }
  }

  // Approach 5: Using extension method
  // Time Complexity: O(n), Space Complexity: O(n)
  List<Interval> insertInterval5(List<Interval> intervals, Interval newInterval) {
    return intervals.insertAndMerge(newInterval);
  }

  // Approach 6: Iterative with in-place merging (if allowed to modify input)
  // Time Complexity: O(n), Space Complexity: O(1) (if input modification is allowed)
  List<Interval> insertInterval6(List<Interval> intervals, Interval newInterval) {
    List<Interval> result = [];
    int i = 0;

    // Add intervals before the overlap
    while (i < intervals.length && intervals[i].end < newInterval.start) {
      result.add(intervals[i]);
      i++;
    }

    // Merge overlapping intervals
    while (i < intervals.length && intervals[i].start <= newInterval.end) {
      newInterval.start = min(newInterval.start, intervals[i].start);
      newInterval.end = max(newInterval.end, intervals[i].end);
      i++;
    }
    result.add(newInterval);

    // Add the remaining intervals
    while (i < intervals.length) {
      result.add(intervals[i]);
      i++;
    }
    return result;
  }
}

// Extension method for List<Interval>
extension IntervalListExtension on List<Interval> {
  List<Interval> insertAndMerge(Interval newInterval) {
    List<Interval> result = [];
    int i = 0;

    while (i < length && this[i].end < newInterval.start) {
      result.add(this[i]);
      i++;
    }

    while (i < length && this[i].start <= newInterval.end) {
      newInterval.start = min(newInterval.start, this[i].start);
      newInterval.end = max(newInterval.end, this[i].end);
      i++;
    }

    result.add(newInterval);

    while (i < length) {
      result.add(this[i]);
      i++;
    }
    return result;
  }
}

void main() {
  InsertInterval solution = InsertInterval();

  // Example usage
  List<Interval> intervals = [
    Interval(1, 3),
    Interval(6, 9),
  ];
  Interval newInterval = Interval(2, 5);

  // Test all 6 approaches
  List<Interval> result1 = solution.insertInterval1(intervals, newInterval);
  print('Approach 1: ${result1}');

  List<Interval> result2 = solution.insertInterval2(intervals, newInterval);
  print('Approach 2: ${result2}');

  List<Interval> result3 = solution.insertInterval3(intervals, newInterval);
  print('Approach 3: ${result3}');

  List<Interval> result4 = solution.insertInterval4(intervals, newInterval);
  print('Approach 4: ${result4}');

  List<Interval> result5 = solution.insertInterval5(intervals, newInterval);
  print('Approach 5: ${result5}');

  List<Interval> result6 = solution.insertInterval6(intervals, newInterval);
  print('Approach 6: ${result6}');

  // Example 2
  List<Interval> intervals2 = [
    Interval(1, 2),
    Interval(3, 5),
    Interval(6, 7),
    Interval(8, 10),
    Interval(12, 16),
  ];
  Interval newInterval2 = Interval(4, 8);

  List<Interval> result7 = solution.insertInterval1(intervals2, newInterval2);
  print('Approach 1 - Example 2: ${result7}');

  List<Interval> result8 = solution.insertInterval2(intervals2, newInterval2);
  print('Approach 2 - Example 2: ${result8}');

  List<Interval> result9 = solution.insertInterval3(intervals2, newInterval2);
  print('Approach 3 - Example 2: ${result9}');

  List<Interval> result10 = solution.insertInterval4(intervals2, newInterval2);
  print('Approach 4 - Example 2: ${result10}');

  List<Interval> result11 = solution.insertInterval5(intervals2, newInterval2);
  print('Approach 5 - Example 2: ${result11}');

  List<Interval> result12 = solution.insertInterval6(intervals2, newInterval2);
  print('Approach 6 - Example 2: ${result12}');
}

/*
  Real-world project implementations of the "Insert Interval" problem:

  1.  Calendar and Scheduling Applications:
      * Merging new events or appointments into an existing schedule.  Ensuring no overlaps and efficiently updating the calendar.
      * Example: Google Calendar, Outlook Calendar.  When you add a new event, the application needs to merge it with your existing schedule.

  2.  Resource Booking and Allocation Systems:
      * Optimizing reservations for resources like rooms, vehicles, or equipment.  Preventing double-bookings and managing availability.
      * Example: A room booking system at a hotel or a car rental service.

  3.  Financial Data Analysis:
      * Combining time ranges of financial transactions or stock prices.  Simplifying data visualization and analysis.
      * Example:  A stock trading platform might merge overlapping transaction records for a clearer view of activity.

  4.  Genomic Data Processing:
      * Merging overlapping gene annotations or sequence alignments.  Identifying significant regions and reducing data redundancy.
      * Example:  Bioinformatics tools that process gene sequences.

  5.  Network Management:
      * Allocating IP address ranges or managing network traffic windows.  Avoiding conflicts and optimizing network utilization.
      * Example:  Software Defined Networking (SDN) controllers.
*/
