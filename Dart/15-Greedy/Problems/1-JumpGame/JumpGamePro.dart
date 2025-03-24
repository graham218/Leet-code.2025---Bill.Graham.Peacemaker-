import 'dart:math';

void main() {
  // Example input arrays representing jump possibilities in different scenarios
  List<int> flightPlan = [2, 3, 1, 1, 4]; // Flight distances between airports
  List<int> gameLevel = [3, 2, 1, 0, 4]; // Player's jump power in a game level
  List<int> networkHops = [1, 0, 2, 0, 3]; // Max hops between network nodes
  List<int> obstacleCourse = [2, 1, 0, 3, 1]; // Jump over obstacles in a course
  List<int> energyLevels = [4, 0, 1, 2, 0];  // Energy units for jumps in a robot's path
  List<int> springSimulation = [2, 3, 0, 1, 2]; // Spring compression units


  // --- Approach 1: Recursive (Top-Down) - Flight Planning ---
  print("\nApproach 1: Recursive (Top-Down) - Flight Planning");
  print("Can reach destination for flightPlan ${flightPlan}: ${canJumpRecursive(flightPlan, 0)}");

  // --- Approach 2: Recursive with Memoization (Top-Down) - Game Level ---
  print("\nApproach 2: Recursive with Memoization (Top-Down) - Game Level");
  print("Can win level for gameLevel ${gameLevel}: ${canJumpMemoized(gameLevel)}");

  // --- Approach 3: Iterative (Bottom-Up) - Dynamic Programming - Network Hops ---
  print("\nApproach 3: Iterative (Bottom-Up) - Dynamic Programming - Network Hops");
  print("Can reach target node for networkHops ${networkHops}: ${canJumpIterativeDP(networkHops)}");

  // --- Approach 4: Greedy - Obstacle Course ---
  print("\nApproach 4: Greedy - Obstacle Course");
  print("Can complete obstacleCourse ${obstacleCourse}: ${canJumpGreedy(obstacleCourse)}");

  // --- Approach 5: Optimized Greedy - Robot Energy Levels ---
  print("\nApproach 5: Optimized Greedy - Robot Energy Levels");
  print("Can navigate path for energyLevels ${energyLevels}: ${canJumpGreedyOptimized(energyLevels)}");

  // --- Approach 6: Iterative with Early Exit - Spring Simulation ---
  print("\nApproach 6: Iterative with Early Exit - Spring Simulation");
  print("Can reach end for springSimulation ${springSimulation}: ${canJumpIterativeEarlyExit(springSimulation)}");
}

// Approach 1: Recursive (Top-Down)
// Time Complexity: O(2^n) - Exponential
// Space Complexity: O(n) - Call stack depth
bool canJumpRecursive(List<int> nums, int position) {
  if (position == nums.length - 1) {
    return true;
  }

  int maxJump = nums[position];
  for (int i = 1; i <= maxJump; i++) {
    int nextPosition = position + i;
    if (nextPosition < nums.length) {
      if (canJumpRecursive(nums, nextPosition)) {
        return true;
      }
    }
  }
  return false;
}

// Approach 2: Recursive with Memoization (Top-Down)
// Time Complexity: O(n^2)
// Space Complexity: O(n) - Memoization array and call stack
bool canJumpMemoized(List<int> nums) {
  List<bool?> memo = List.filled(nums.length, null);
  return _canJumpMemoizedHelper(nums, 0, memo);
}

bool _canJumpMemoizedHelper(List<int> nums, int position, List<bool?> memo) {
  if (position == nums.length - 1) {
    return true;
  }

  if (memo[position] != null) {
    return memo[position]!;
  }

  int maxJump = nums[position];
  for (int i = 1; i <= maxJump; i++) {
    int nextPosition = position + i;
    if (nextPosition < nums.length) {
      if (_canJumpMemoizedHelper(nums, nextPosition, memo)) {
        memo[position] = true;
        return true;
      }
    }
  }
  memo[position] = false;
  return false;
}

// Approach 3: Iterative (Bottom-Up) - Dynamic Programming
// Time Complexity: O(n^2)
// Space Complexity: O(n)
bool canJumpIterativeDP(List<int> nums) {
  List<bool> dp = List.filled(nums.length, false);
  dp[nums.length - 1] = true;

  for (int i = nums.length - 2; i >= 0; i--) {
    int maxJump = nums[i];
    for (int j = 1; j <= maxJump; j++) {
      int nextPosition = i + j;
      if (nextPosition < nums.length && dp[nextPosition]) {
        dp[i] = true;
        break;
      }
    }
  }
  return dp[0];
}

// Approach 4: Greedy
// Time Complexity: O(n)
// Space Complexity: O(1)
bool canJumpGreedy(List<int> nums) {
  int maxReach = 0;
  for (int i = 0; i < nums.length; i++) {
    if (i > maxReach) {
      return false;
    }
    maxReach = max(maxReach, i + nums[i]);
  }
  return true;
}

// Approach 5: Optimized Greedy
// Time Complexity: O(n)
// Space Complexity: O(1)
bool canJumpGreedyOptimized(List<int> nums) {
  int goal = nums.length - 1;
  for (int i = nums.length - 2; i >= 0; i--) {
    if (i + nums[i] >= goal) {
      goal = i;
    }
  }
  return goal == 0;
}

// Approach 6: Iterative with Early Exit
// Time Complexity: O(n) - Best case is O(1)
// Space Complexity: O(1)
bool canJumpIterativeEarlyExit(List<int> nums) {
  int n = nums.length;
  int maxReach = 0;
  for (int i = 0; i < n; i++) {
    if (i > maxReach) {
      return false; // Cannot reach current position
    }
    maxReach = max(maxReach, i + nums[i]);
    if (maxReach >= n - 1) {
      return true; // Reached or exceeded the goal
    }
  }
  return false;
}
