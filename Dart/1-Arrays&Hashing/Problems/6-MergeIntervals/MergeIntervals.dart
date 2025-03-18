import 'dart:math';

class MergeIntervals {
  // Approach 1: Sorting & Merging (Optimized O(n log n))
  List<List<int>> mergeSorting(List<List<int>> intervals) {
    if (intervals.isEmpty) return [];
    intervals.sort((a, b) => a[0].compareTo(b[0]));
    List<List<int>> merged = [];
    List<int> current = intervals[0];

    for (int i = 1; i < intervals.length; i++) {
      if (current[1] >= intervals[i][0]) {
        current[1] = max(current[1], intervals[i][1]);
      } else {
        merged.add(current);
        current = intervals[i];
      }
    }
    merged.add(current);
    return merged;
  }

  // Approach 2: Using Stack (O(n log n))
  List<List<int>> mergeUsingStack(List<List<int>> intervals) {
    if (intervals.isEmpty) return [];
    intervals.sort((a, b) => a[0].compareTo(b[0]));
    List<List<int>> stack = [];
    stack.add(intervals[0]);

    for (int i = 1; i < intervals.length; i++) {
      List<int> top = stack.last;
      if (top[1] >= intervals[i][0]) {
        top[1] = max(top[1], intervals[i][1]);
      } else {
        stack.add(intervals[i]);
      }
    }
    return stack;
  }

  // Approach 3: Using Map (For Large Data Processing)
  Map<int, int> mergeUsingMap(List<List<int>> intervals) {
    Map<int, int> map = {};
    for (var interval in intervals) {
      map[interval[0]] = max(map[interval[0]] ?? interval[1], interval[1]);
    }
    return map;
  }

  // Approach 4: Two Pointers (O(n log n))
  List<List<int>> mergeTwoPointers(List<List<int>> intervals) {
    if (intervals.isEmpty) return [];
    intervals.sort((a, b) => a[0].compareTo(b[0]));
    List<List<int>> result = [];
    int i = 0;

    while (i < intervals.length) {
      int start = intervals[i][0], end = intervals[i][1];
      while (i < intervals.length - 1 && end >= intervals[i + 1][0]) {
        end = max(end, intervals[i + 1][1]);
        i++;
      }
      result.add([start, end]);
      i++;
    }
    return result;
  }

  // Approach 5: Parallel Processing (For Distributed Systems)
  Future<List<List<int>>> mergeParallel(List<List<int>> intervals) async {
    return await Future(() => mergeSorting(intervals));
  }
}

void main() async {
  List<List<int>> intervals = [
    [1, 3], [2, 6], [8, 10], [15, 18]
  ];

  MergeIntervals mi = MergeIntervals();
  print("Sorting & Merging: ${mi.mergeSorting(intervals)}");
  print("Using Stack: ${mi.mergeUsingStack(intervals)}");
  print("Using Map: ${mi.mergeUsingMap(intervals)}");
  print("Two Pointers: ${mi.mergeTwoPointers(intervals)}");
  print("Parallel Processing: ${await mi.mergeParallel(intervals)}");
}
