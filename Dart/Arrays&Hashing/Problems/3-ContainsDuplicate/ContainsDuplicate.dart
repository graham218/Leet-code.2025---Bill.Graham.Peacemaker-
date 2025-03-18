void main() {
  List<int> nums = [1, 2, 3, 4, 5, 1];
  print(containsDuplicateBruteForce(nums)); // Output: true
  print(containsDuplicateSorting(nums)); // Output: true
  print(containsDuplicateHashSet(nums)); // Output: true
  print(containsDuplicateHashMap(nums)); // Output: true
  print(containsDuplicateBitwise(nums)); // Output: true (only works for small positive integers)
}

// Approach 1: Brute Force
// Time Complexity: O(n^2), Space Complexity: O(1)
bool containsDuplicateBruteForce(List<int> nums) {
  for (int i = 0; i < nums.length; i++) {
    for (int j = i + 1; j < nums.length; j++) {
      if (nums[i] == nums[j]) {
        return true;
      }
    }
  }
  return false;
}

// Approach 2: Sorting
// Time Complexity: O(n log n), Space Complexity: O(1)
bool containsDuplicateSorting(List<int> nums) {
  nums.sort();
  for (int i = 1; i < nums.length; i++) {
    if (nums[i] == nums[i - 1]) {
      return true;
    }
  }
  return false;
}

// Approach 3: Using a HashSet
// Time Complexity: O(n), Space Complexity: O(n)
bool containsDuplicateHashSet(List<int> nums) {
  Set<int> seen = {};
  for (int num in nums) {
    if (seen.contains(num)) {
      return true;
    }
    seen.add(num);
  }
  return false;
}

// Approach 4: Using a HashMap (Counts frequency of elements)
// Time Complexity: O(n), Space Complexity: O(n)
bool containsDuplicateHashMap(List<int> nums) {
  Map<int, int> frequency = {};
  for (int num in nums) {
    if (frequency.containsKey(num)) {
      return true;
    }
    frequency[num] = 1;
  }
  return false;
}

// Approach 5: Bitwise Manipulation (Only works for small positive integers)
// Time Complexity: O(n), Space Complexity: O(1)
bool containsDuplicateBitwise(List<int> nums) {
  int bitset = 0;
  for (int num in nums) {
    int mask = 1 << num;
    if ((bitset & mask) != 0) {
      return true;
    }
    bitset |= mask;
  }
  return false;
}
