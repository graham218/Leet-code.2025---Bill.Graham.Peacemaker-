import 'dart:math';

void main() {
  // Example input arrays
  List<int> nums1 = [2, 3, 1, 1, 4];
  List<int> nums2 = [3, 2, 1, 0, 4];
  List<int> nums3 = [0];
  List<int> nums4 = [2, 0, 0];
  List<int> nums5 = [2, 5, 0, 0];

  // --- Approach 1: Recursive (Top-Down) ---
  print("\nApproach 1: Recursive (Top-Down)");
  print("Can jump to the end for ${nums1}: ${canJumpRecursive(nums1, 0)}"); // true
  print("Can jump to the end for ${nums2}: ${canJumpRecursive(nums2, 0)}"); // false
  print("Can jump to the end for ${nums3}: ${canJumpRecursive(nums3, 0)}"); // true
  print("Can jump to the end for ${nums4}: ${canJumpRecursive(nums4, 0)}"); // false
  print("Can jump to the end for ${nums5}: ${canJumpRecursive(nums5, 0)}"); // true

  // --- Approach 2: Recursive with Memoization (Top-Down) ---
  print("\nApproach 2: Recursive with Memoization (Top-Down)");
  print("Can jump to the end for ${nums1}: ${canJumpMemoized(nums1)}"); // true
  print("Can jump to the end for ${nums2}: ${canJumpMemoized(nums2)}"); // false
  print("Can jump to the end for ${nums3}: ${canJumpMemoized(nums3)}"); // true
  print("Can jump to the end for ${nums4}: ${canJumpMemoized(nums4)}"); // false
  print("Can jump to the end for ${nums5}: ${canJumpMemoized(nums5)}"); // true

  // --- Approach 3: Iterative (Bottom-Up) - Dynamic Programming ---
  print("\nApproach 3: Iterative (Bottom-Up) - Dynamic Programming");
  print("Can jump to the end for ${nums1}: ${canJumpIterativeDP(nums1)}"); // true
  print("Can jump to the end for ${nums2}: ${canJumpIterativeDP(nums2)}"); // false
  print("Can jump to the end for ${nums3}: ${canJumpIterativeDP(nums3)}"); // true
  print("Can jump to the end for ${nums4}: ${canJumpIterativeDP(nums4)}"); // false
  print("Can jump to the end for ${nums5}: ${canJumpIterativeDP(nums5)}"); // true

  // --- Approach 4: Greedy ---
  print("\nApproach 4: Greedy");
  print("Can jump to the end for ${nums1}: ${canJumpGreedy(nums1)}"); // true
  print("Can jump to the end for ${nums2}: ${canJumpGreedy(nums2)}"); // false
  print("Can jump to the end for ${nums3}: ${canJumpGreedy(nums3)}"); // true
  print("Can jump to the end for ${nums4}: ${canJumpGreedy(nums4)}"); // false
  print("Can jump to the end for ${nums5}: ${canJumpGreedy(nums5)}"); // true

  // --- Approach 5: Optimized Greedy ---
  print("\nApproach 5: Optimized Greedy");
  print("Can jump to the end for ${nums1}: ${canJumpGreedyOptimized(nums1)}");
  print("Can jump to the end for ${nums2}: ${canJumpGreedyOptimized(nums2)}");
  print("Can jump to the end for ${nums3}: ${canJumpGreedyOptimized(nums3)}");
  print("Can jump to the end for ${nums4}: ${canJumpGreedyOptimized(nums4)}");
  print("Can jump to the end for ${nums5}: ${canJumpGreedyOptimized(nums5)}");
}

// Approach 1: Recursive (Top-Down)
// Time Complexity: O(2^n) - Exponential
// Space Complexity: O(n) - Call stack depth
bool canJumpRecursive(List<int> nums, int position) {
  if (position == nums.length - 1) {
    return true; // Reached the end, we can jump!
  }

  int maxJump = nums[position]; // Max distance we can jump from current position
  for (int i = 1; i <= maxJump; i++) {
    // Try all possible jumps from the current position
    int nextPosition = position + i;
    if (nextPosition < nums.length) {
      if (canJumpRecursive(nums, nextPosition)) {
        return true; // If any jump leads to the end, we're good
      }
    }
  }
  return false; // No jump leads to the end
}

// Approach 2: Recursive with Memoization (Top-Down)
// Time Complexity: O(n^2)
// Space Complexity: O(n) - Memoization array and call stack
bool canJumpMemoized(List<int> nums) {
  List<bool?> memo = List.filled(nums.length, null); // Use null to represent unvisited
  return _canJumpMemoizedHelper(nums, 0, memo);
}

bool _canJumpMemoizedHelper(List<int> nums, int position, List<bool?> memo) {
  if (position == nums.length - 1) {
    return true;
  }

  if (memo[position] != null) {
    return memo[position]!; // Return the memoized result
  }

  int maxJump = nums[position];
  for (int i = 1; i <= maxJump; i++) {
    int nextPosition = position + i;
    if (nextPosition < nums.length) {
      if (_canJumpMemoizedHelper(nums, nextPosition, memo)) {
        memo[position] = true; // Memoize the result
        return true;
      }
    }
  }
  memo[position] = false; // Memoize the result
  return false;
}

// Approach 3: Iterative (Bottom-Up) - Dynamic Programming
// Time Complexity: O(n^2)
// Space Complexity: O(n)
bool canJumpIterativeDP(List<int> nums) {
  List<bool> dp = List.filled(nums.length, false);
  dp[nums.length - 1] = true; // Last position is reachable

  for (int i = nums.length - 2; i >= 0; i--) {
    int maxJump = nums[i];
    for (int j = 1; j <= maxJump; j++) {
      int nextPosition = i + j;
      if (nextPosition < nums.length && dp[nextPosition]) {
        dp[i] = true; // If any next position is reachable, current is also reachable
        break; // No need to check further jumps
      }
    }
  }
  return dp[0]; // Is the first position reachable?
}

// Approach 4: Greedy
// Time Complexity: O(n)
// Space Complexity: O(1)
bool canJumpGreedy(List<int> nums) {
  int maxReach = 0; // Furthest position we can reach
  for (int i = 0; i < nums.length; i++) {
    if (i > maxReach) {
      return false; // If current position is beyond maxReach, we can't reach here
    }
    maxReach = max(maxReach, i + nums[i]); // Update maxReach
  }
  return true; // If we get through the loop, we can reach the end
}

// Approach 5: Optimized Greedy
// Time Complexity: O(n)
// Space Complexity: O(1)
bool canJumpGreedyOptimized(List<int> nums) {
  int goal = nums.length - 1; // Start from the goal (last index)

  for (int i = nums.length - 2; i >= 0; i--) {
    if (i + nums[i] >= goal) {
      goal = i; // Update the goal to the current position
    }
  }
  return goal == 0; // If the goal is the first position, we can reach the end
}
