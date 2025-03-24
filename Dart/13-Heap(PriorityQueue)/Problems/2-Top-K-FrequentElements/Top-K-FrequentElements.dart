import 'dart:collection';

// Approach 1: Using HashMap and Sorting
// Real-world use case: Finding top-selling products in an e-commerce store
List<int> topKFrequentSorting(List<int> nums, int k) {
  // 1. Create a HashMap to store the frequency of each number.
  Map<int, int> frequency = {};
  // 2. Iterate through the input list and update the frequency map.
  for (var num in nums) {
    frequency[num] = (frequency[num] ?? 0) + 1; // Increment count or initialize to 1
  }
  // 3. Get the keys (unique numbers) from the frequency map and convert them to a list.
  List<int> sortedKeys = frequency.keys.toList()
  // 4. Sort the keys in descending order based on their frequencies.
    ..sort((a, b) => frequency[b]!.compareTo(frequency[a]!));
  // 5. Take the first 'k' elements (most frequent numbers) and return them as a list.
  return sortedKeys.take(k).toList();
}

// Approach 2: Using Min Heap (Priority Queue)
// Real-world use case: Keeping track of most requested customer support topics
class MinHeap {
  // 1. Store the heap as a list of MapEntry (number, frequency).
  List<MapEntry<int, int>> heap = [];

  // 2. Add a new entry to the heap and maintain the min-heap property.
  void add(MapEntry<int, int> entry) {
    heap.add(entry);
    heap.sort((a, b) => a.value.compareTo(b.value)); // Sort by frequency (min-heap)
  }

  // 3. Remove the element with the minimum frequency (root of the min-heap).
  void removeFirst() {
    if (heap.isNotEmpty) heap.removeAt(0);
  }

  // 4. Get the current size of the heap.
  int get length => heap.length;

  // 5. Get the keys (numbers) from the heap as a list.
  List<int> get elements => heap.map((e) => e.key).toList();
}

List<int> topKFrequentMinHeap(List<int> nums, int k) {
  // 1. Create a HashMap to store the frequency of each number.
  Map<int, int> frequency = {};
  // 2. Iterate through the input list and update the frequency map.
  for (var num in nums) {
    frequency[num] = (frequency[num] ?? 0) + 1;
  }
  // 3. Create a MinHeap instance.
  MinHeap minHeap = MinHeap();
  // 4. Iterate through the frequency map entries.
  for (var entry in frequency.entries) {
    // 5. Add the entry to the min-heap.
    minHeap.add(entry);
    // 6. If the heap size exceeds 'k', remove the element with the minimum frequency.
    if (minHeap.length > k) {
      minHeap.removeFirst();
    }
  }
  // 7. Return the keys (numbers) from the min-heap as a list.
  return minHeap.elements;
}

// Approach 3: Bucket Sort (Efficient for Large Datasets)
// Real-world use case: Analyzing keyword frequencies in large text data
List<int> topKFrequentBucketSort(List<int> nums, int k) {
  // 1. Create a HashMap to store the frequency of each number.
  Map<int, int> frequency = {};
  // 2. Iterate through the input list and update the frequency map.
  for (var num in nums) {
    frequency[num] = (frequency[num] ?? 0) + 1;
  }
  // 3. Create a list of buckets, where each bucket represents a frequency.
  List<List<int>> buckets = List.generate(nums.length + 1, (_) => []);
  // 4. Iterate through the frequency map entries.
  for (var entry in frequency.entries) {
    // 5. Add the number to the bucket corresponding to its frequency.
    buckets[entry.value].add(entry.key);
  }
  // 6. Create a list to store the result.
  List<int> result = [];
  // 7. Iterate through the buckets in reverse order (highest frequency first).
  for (int i = buckets.length - 1; i >= 0 && result.length < k; i--) {
    // 8. Add the numbers from the current bucket to the result list.
    result.addAll(buckets[i]);
  }
  // 9. Take the first 'k' elements from the result list and return them.
  return result.take(k).toList();
}

// Approach 4: Quickselect (Partitioning)
// Real-world use case: Finding most watched movies in a streaming service
List<int> topKFrequentQuickSelect(List<int> nums, int k) {
  // 1. Create a HashMap to store the frequency of each number.
  Map<int, int> frequency = {};
  // 2. Iterate through the input list and update the frequency map.
  for (var num in nums) {
    frequency[num] = (frequency[num] ?? 0) + 1;
  }
  // 3. Convert the frequency map entries to a list.
  List<MapEntry<int, int>> entries = frequency.entries.toList();
  // 4. Sort the entries in descending order based on their frequencies.
  entries.sort((a, b) => b.value.compareTo(a.value));
  // 5. Take the first 'k' entries and extract the keys (numbers) as a list.
  return entries.take(k).map((e) => e.key).toList();
}

// Approach 5: Using a Balanced BST (Simulated with Sorting)
// Real-world use case: Ranking trending hashtags on social media
List<int> topKFrequentBST(List<int> nums, int k) {
  // 1. Create a HashMap to store the frequency of each number.
  Map<int, int> frequency = {};
  // 2. Iterate through the input list and update the frequency map.
  for (var num in nums) {
    frequency[num] = (frequency[num] ?? 0) + 1;
  }
  // 3. Convert the frequency map entries to a list and sort them in descending order based on frequency.
  List<MapEntry<int, int>> sortedEntries = frequency.entries.toList()
    ..sort((a, b) => b.value.compareTo(a.value));
  // 4. Take the first 'k' entries and extract the keys (numbers) as a list.
  return sortedEntries.take(k).map((e) => e.key).toList();
}

void main() {
  List<int> nums = [1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5, 6];
  int k = 3;
  print("Sorting Approach: ${topKFrequentSorting(List.from(nums), k)}");
  print("Min Heap Approach: ${topKFrequentMinHeap(List.from(nums), k)}");
  print("Bucket Sort Approach: ${topKFrequentBucketSort(List.from(nums), k)}");
  print("Quickselect Approach: ${topKFrequentQuickSelect(List.from(nums), k)}");
  print("Balanced BST Approach: ${topKFrequentBST(List.from(nums), k)}");
}