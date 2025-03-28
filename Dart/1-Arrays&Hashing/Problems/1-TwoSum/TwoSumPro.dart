void main() {
  List<int> nums = [2, 7, 11, 15, 1, 8, 3];
  int target1 = 9;
  int target2 = 10;
  int target3 = 18;

  print(twoSumBruteForce(nums, target1)); // Output: [0, 1]
  print(twoSumHashMap(nums, target1)); // Output: [0, 1]
  print(twoSumTwoPointers(nums, target1)); // Output: [0, 1]

  print(twoSumBruteForce(nums, target2)); // Output: [4, 5]
  print(twoSumHashMap(nums, target2)); // Output: [4, 5]
  print(twoSumTwoPointers(nums, target2)); // Output: [4, 5]

  print(twoSumBruteForce(nums, target3)); // Output: [2, 3]
  print(twoSumHashMap(nums, target3)); // Output: [2, 3]
  print(twoSumTwoPointers(nums, target3)); // Output: [2, 3]
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
  return [];
}

// Approach 2: Using a HashMap
List<int> twoSumHashMap(List<int> nums, int target) {
  Map<int, int> map = {};
  for (int i = 0; i < nums.length; i++) {
    int complement = target - nums[i];
    if (map.containsKey(complement)) {
      return [map[complement]!, i];
    }
    map[nums[i]] = i;
  }
  return [];
}

// Approach 3: Using Sorting and Two Pointers
List<int> twoSumTwoPointers(List<int> nums, int target) {
  List<MapEntry<int, int>> indexedNums = nums.asMap().entries.toList();
  indexedNums.sort((a, b) => a.value.compareTo(b.value));

  int left = 0, right = nums.length - 1;
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
  return [];
}