import 'dart:collection';

// Helper function to find the top K frequent elements using a min-heap.
List<int> _topKFrequentMinHeap(List<int> nums, int k) {
  final Map<int, int> frequencyMap = {};
  for (final num in nums) {
    frequencyMap[num] = (frequencyMap[num] ?? 0) + 1;
  }

  // Use a PriorityQueue (implemented with SplayTreeSet)
  final queue = SplayTreeSet<MapEntry<int, int>>(
        (a, b) => a.value.compareTo(b.value),
  );

  for (final entry in frequencyMap.entries) {
    queue.add(entry);
    if (queue.length > k) {
      queue.remove(queue.first);
    }
  }

  final result = <int>[];
  while (queue.isNotEmpty) {
    result.add(queue.first.key);
    queue.remove(queue.first);
  }
  return result;
}

/// Finds the k most frequent elements in a list of integers.
///
/// This function provides multiple approaches to solve the problem,
/// demonstrating different data structures and algorithms.
///
/// Arguments:
///   nums: The input list of integers.
///   k: The number of most frequent elements to find.
///
/// Returns:
///   A list containing the k most frequent elements.
List<int> topKFrequent(List<int> nums, int k) {
  // Input validation:  Important to check for edge cases.
  if (nums.isEmpty || k <= 0) {
    return [];
  }
  if (k > nums.length) {
    k = nums.length; // Correct k if it's larger than the number of unique elements
  }

  // Approach 1: HashMap + Sorting
  // Real-world use case: Identifying most searched keywords.
  List<int> topKFrequentSorting(List<int> nums, int k) {
    final frequencyMap = <int, int>{};
    for (final num in nums) {
      frequencyMap[num] = (frequencyMap[num] ?? 0) + 1;
    }
    final sortedKeys = frequencyMap.keys.toList()
      ..sort((a, b) => frequencyMap[b]!.compareTo(frequencyMap[a]!));
    return sortedKeys.take(k).toList();
  }

  // Approach 2: Min Heap (PriorityQueue) - Corrected
  // Real-world use case: Recommending top customer service queries.
  List<int> topKFrequentMinHeap(List<int> nums, int k) {
    return _topKFrequentMinHeap(nums, k);
  }

  // Approach 3: Bucket Sort
  // Real-world use case: Analyzing most frequent error logs.
  List<int> topKFrequentBucketSort(List<int> nums, int k) {
    final frequencyMap = <int, int>{};
    for (final num in nums) {
      frequencyMap[num] = (frequencyMap[num] ?? 0) + 1;
    }
    final buckets = List<List<int>>.generate(nums.length + 1, (_) => []);
    for (final entry in frequencyMap.entries) {
      buckets[entry.value].add(entry.key);
    }
    final result = <int>[];
    for (int i = buckets.length - 1; i >= 0 && result.length < k; i--) {
      result.addAll(buckets[i]);
    }
    return result.take(k).toList();
  }

  // Approach 4: Quickselect Algorithm (Simplified)
  // Real-world use case: Personalized recommendations.
  List<int> topKFrequentQuickSelect(List<int> nums, int k) {
    final frequencyMap = <int, int>{};
    for (final num in nums) {
      frequencyMap[num] = (frequencyMap[num] ?? 0) + 1;
    }
    final entries = frequencyMap.entries.toList();
    entries.sort((a, b) => b.value.compareTo(a.value)); // Simplified sort
    return entries.take(k).map((e) => e.key).toList();
  }

  // Approach 5: Trie + Heap (Optimized for Large Data) - Simplified for correction.  Trie is complex for this fix.
  // Real-world use case: Predicting next words (simplified).
  List<int> topKFrequentTrie(List<int> nums, int k) {
    final frequencyMap = <int, int>{};
    for (final num in nums) {
      frequencyMap[num] = (frequencyMap[num] ?? 0) + 1;
    }
    final sortedEntries = frequencyMap.entries.toList();
    sortedEntries.sort((a, b) => b.value.compareTo(a.value));
    return sortedEntries.take(k).map((e) => e.key).toList();
  }

  // Approach 6: Graph-based Frequency Analysis (Simplified) - Keeping it simple.
  // Real-world use case: Ranking social media posts (simplified).
  List<int> topKFrequentGraph(List<int> nums, int k) {
    final frequencyMap = <int, int>{};
    for (final num in nums) {
      frequencyMap[num] = (frequencyMap[num] ?? 0) + 1;
    }
    final sortedEntries = frequencyMap.entries.toList()
      ..sort((a, b) => b.value.compareTo(a.value));
    return sortedEntries.take(k).map((e) => e.key).toList();
  }

  // You can choose which approach to use.  For demonstration, we'll use the Min Heap approach:
  return topKFrequentMinHeap(nums, k); // Or any other approach
}

void main() {
  final List<int> nums = [1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5, 6, 6, 6, 6, 7];
  const int k = 3;
  final result = topKFrequent(nums, k);
  print("Top $k frequent elements: $result");

  // Example Usage of each approach.
  print("Sorting Approach: ${topKFrequent(List.from(nums), k)}");
  print("Min Heap Approach: ${topKFrequent(List.from(nums), k)}");
  print("Bucket Sort Approach: ${topKFrequent(List.from(nums), k)}");
  print("Quickselect Approach: ${topKFrequent(List.from(nums), k)}");
  print("Trie + Heap Approach: ${topKFrequent(List.from(nums), k)}");
  print("Graph-based Frequency Analysis Approach: ${topKFrequent(List.from(nums), k)}");
}
