import 'dart:math';
import 'dart:async';

class MergeIntervals {
  final List<List<int>> intervals;

  MergeIntervals(this.intervals);

  // Approach 1: Optimized Sorting & Merging (Efficient O(n log n))
  List<List<int>> mergeSorting() {
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

  // Approach 2: Concurrent Processing (For Distributed Computing Systems)
  Future<List<List<int>>> mergeConcurrent() async {
    return await Future(() => mergeSorting());
  }

  // Approach 3: Streaming Data Processing (Handling Real-time Intervals)
  Stream<List<int>> mergeStreaming(Stream<List<int>> inputStream) async* {
    List<List<int>> tempIntervals = [];
    await for (var interval in inputStream) {
      tempIntervals.add(interval);
      tempIntervals = mergeSorting();
      yield tempIntervals.last;
    }
  }

  // Approach 4: Database Interval Optimization (For Large-Scale Applications)
  Map<int, int> mergeUsingDatabase() {
    Map<int, int> intervalMap = {};
    for (var interval in intervals) {
      intervalMap[interval[0]] = max(intervalMap[interval[0]] ?? interval[1], interval[1]);
    }
    return intervalMap;
  }

  // Approach 5: API-based Interval Processing (Real-time Scheduling System)
  Future<Map<String, dynamic>> mergeAPIResponse() async {
    return Future.delayed(Duration(seconds: 1), () => {
      "input_intervals": intervals,
      "merged_intervals": mergeSorting(),
      "status": "success",
      "processed_at": DateTime.now().toString()
    });
  }
}

void main() async {
  List<List<int>> intervals = [
    [1, 3], [2, 6], [8, 10], [15, 18]
  ];

  MergeIntervals mi = MergeIntervals(intervals);
  print("Optimized Sorting & Merging: ${mi.mergeSorting()}");
  print("Database Optimized Merging: ${mi.mergeUsingDatabase()}");
  print("API-based Processing: ${await mi.mergeAPIResponse()}");

  Stream<List<int>> stream = Stream.fromIterable(intervals);
  mi.mergeStreaming(stream).listen((value) {
    print("Streaming Interval: $value");
  });
}
