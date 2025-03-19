void main() {
  List<int> nums = [2, 7, 11, 15];
  int target = 9;

  print(twoSumBruteForce(nums, target)); // Output: [0, 1]
  print(twoSumHashMap(nums, target)); // Output: [0, 1]
  print(twoSumTwoPointers(nums, target)); // Output: [0, 1]
}

// Approach 1: Brute Force
List<int> twoSumBruteForce(List<int> nums, int target) {
  for (int i = 0; i < nums.length; i++) {
    for (int j = i + 1; j < nums.length; j++) {
      if (nums[i] + nums[j] == target) {
        return [i, j];
      }
    }
  }
  return []; // Return empty list if no solution is found
}

// Approach 2: Using a HashMap (Optimized)
List<int> twoSumHashMap(List<int> nums, int target) {
  Map<int, int> numMap = {}; // More descriptive variable name
  for (int i = 0; i < nums.length; i++) {
    int complement = target - nums[i];
    if (numMap.containsKey(complement)) {
      return [numMap[complement]!, i];
    }
    numMap[nums[i]] = i;
  }
  return []; // Return empty list if no solution is found
}

// Approach 3: Using Sorting and Two Pointers (Requires Original Indices)
List<int> twoSumTwoPointers(List<int> nums, int target) {
  // Create a list of tuples containing the value and its original index
  List<MapEntry<int, int>> indexedNums = nums.asMap().entries.toList();

  // Sort the indexedNums based on the values
  indexedNums.sort((a, b) => a.value.compareTo(b.value));

  int left = 0;
  int right = nums.length - 1;

  while (left < right) {
    int sum = indexedNums[left].value + indexedNums[right].value;

    if (sum == target) {
      return [indexedNums[left].key, indexedNums[right].key];
    } else if (sum < target) {
      left++;
    } else {
      right--;
    }
  }

  return []; // Return empty list if no solution is found
}