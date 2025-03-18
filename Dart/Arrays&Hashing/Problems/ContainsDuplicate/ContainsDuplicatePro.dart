import 'dart:collection';

void main() {
  List<int> nums = [1, 2, 3, 4, 5, 1];
  print(containsDuplicateHashSet(nums)); // Output: true
  print(containsDuplicateHashMap(nums)); // Output: true
  containsDuplicateStream(nums).then((result) => print(result)); // Output: true
  print(containsDuplicateSQL(nums)); // Simulated SQL check
  print(containsDuplicateBloomFilter(nums)); // Simulated Bloom filter
}

// Approach 1: Using HashSet (Best for general use cases)
// Time Complexity: O(n), Space Complexity: O(n)
bool containsDuplicateHashSet(List<int> nums) {
  Set<int> seen = HashSet();
  for (int num in nums) {
    if (!seen.add(num)) {
      return true;
    }
  }
  return false;
}

// Approach 2: Using HashMap (Counts frequency of elements)
// Time Complexity: O(n), Space Complexity: O(n)
bool containsDuplicateHashMap(List<int> nums) {
  Map<int, int> frequency = HashMap();
  for (int num in nums) {
    if (frequency.containsKey(num)) {
      return true;
    }
    frequency[num] = 1;
  }
  return false;
}

// Approach 3: Using Dart Streams (For reactive programming)
// Time Complexity: O(n), Space Complexity: O(n)
Future<bool> containsDuplicateStream(List<int> nums) async {
  Set<int> seen = HashSet();
  return await Stream.fromIterable(nums).any((num) {
    if (seen.contains(num)) return true;
    seen.add(num);
    return false;
  });
}

// Approach 4: Using a Database Query (SQL-based approach for large datasets)
// Simulating a SQL query that checks for duplicates in a database
// Time Complexity: O(n) (Assuming indexed search in DB)
bool containsDuplicateSQL(List<int> nums) {
  // In real applications, replace this with an actual database query
  return nums.toSet().length != nums.length;
}

// Approach 5: Using a Bloom Filter (For large-scale distributed systems)
// Simulating a Bloom Filter (Probabilistic duplicate detection)
bool containsDuplicateBloomFilter(List<int> nums) {
  Set<int> seen = HashSet(); // Replace with actual Bloom filter in production
  for (int num in nums) {
    if (seen.contains(num)) {
      return true; // In real-world, may return false positives
    }
    seen.add(num);
  }
  return false;
}
