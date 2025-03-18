void main() {
  List<int> nums = [-1, 0, 1, 2, -1, -4];
  print("Three sum solutions: ");
  print(threeSumTwoPointers(nums));
  print(threeSumHashSet(nums));
  print(threeSumSorting(nums));
  print(threeSumBruteForce(nums));
  print(threeSumOptimized(nums));
}

// Approach 1: Two Pointers (Efficient O(n^2))
List<List<int>> threeSumTwoPointers(List<int> nums) {
  nums.sort(); // Sorting helps in skipping duplicates
  List<List<int>> result = [];
  for (int i = 0; i < nums.length - 2; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates
    int left = i + 1, right = nums.length - 1;
    while (left < right) {
      int sum = nums[i] + nums[left] + nums[right];
      if (sum == 0) {
        result.add([nums[i], nums[left], nums[right]]);
        while (left < right && nums[left] == nums[left + 1]) { left++; } // Skip duplicates
        while (left < right && nums[right] == nums[right - 1]) { right--; } // Skip duplicates
        left++;
        right--;
      } else if (sum < 0) {
        left++;
      } else {
        right--;
      }
    }
  }
  return result;
}

// Approach 2: HashSet for Unique Triplets
List<List<int>> threeSumHashSet(List<int> nums) {
  nums.sort();
  Set<List<int>> result = {};
  for (int i = 0; i < nums.length - 2; i++) {
    Set<int> seen = {};
    for (int j = i + 1; j < nums.length; j++) {
      int complement = -nums[i] - nums[j];
      if (seen.contains(complement)) {
        result.add([nums[i], complement, nums[j]]);
      }
      seen.add(nums[j]);
    }
  }
  return result.toList();
}

// Approach 3: Sorting and Iteration (Simplified Two Pointers)
List<List<int>> threeSumSorting(List<int> nums) {
  nums.sort();
  List<List<int>> result = [];
  for (int i = 0; i < nums.length - 2; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) continue;
    int left = i + 1, right = nums.length - 1;
    while (left < right) {
      int sum = nums[i] + nums[left] + nums[right];
      if (sum == 0) {
        result.add([nums[i], nums[left], nums[right]]);
        left++;
        right--;
      } else if (sum < 0) {
        left++;
      } else {
        right--;
      }
    }
  }
  return result;
}

// Approach 4: Brute Force (Inefficient O(n^3))
List<List<int>> threeSumBruteForce(List<int> nums) {
  Set<List<int>> result = {};
  for (int i = 0; i < nums.length - 2; i++) {
    for (int j = i + 1; j < nums.length - 1; j++) {
      for (int k = j + 1; k < nums.length; k++) {
        if (nums[i] + nums[j] + nums[k] == 0) {
          List<int> triplet = [nums[i], nums[j], nums[k]];
          triplet.sort();
          result.add(triplet);
        }
      }
    }
  }
  return result.toList();
}

// Approach 5: Optimized Using Map (Alternative Approach)
List<List<int>> threeSumOptimized(List<int> nums) {
  nums.sort();
  List<List<int>> result = [];
  for (int i = 0; i < nums.length - 2; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) continue;
    Map<int, int> map = {};
    for (int j = i + 1; j < nums.length; j++) {
      int complement = -nums[i] - nums[j];
      if (map.containsKey(complement)) {
        result.add([nums[i], complement, nums[j]]);
        while (j + 1 < nums.length && nums[j] == nums[j + 1]) { j++; } // Skip duplicates
      }
      map[nums[j]] = j;
    }
  }
  return result;
}
