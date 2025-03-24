import 'dart:math';

void main() {
  // Test cases
  List<int> gas = [1, 2, 3, 4, 5];
  List<int> cost = [3, 4, 5, 1, 2];
  print("Test Case 1: gas = $gas, cost = $cost");
  print("Approach 1: Brute Force: ${canCompleteCircuitBruteForce(gas, cost)}");
  print("Approach 2: Optimized Brute Force: ${canCompleteCircuitOptimizedBruteForce(gas, cost)}");
  print("Approach 3: Single Pass with Total Tank: ${canCompleteCircuitSinglePassTotalTank(gas, cost)}");
  print("Approach 4: Single Pass with Start Index Tracking: ${canCompleteCircuitSinglePassStartIndex(gas, cost)}");
  print("Approach 5: Using Kadane's Algorithm (Variation): ${canCompleteCircuitKadane(gas, cost)}");


  gas = [2, 3, 4];
  cost = [3, 4, 3];
  print("\nTest Case 2: gas = $gas, cost = $cost");
  print("Approach 1: Brute Force: ${canCompleteCircuitBruteForce(gas, cost)}");
  print("Approach 2: Optimized Brute Force: ${canCompleteCircuitOptimizedBruteForce(gas, cost)}");
  print("Approach 3: Single Pass with Total Tank: ${canCompleteCircuitSinglePassTotalTank(gas, cost)}");
  print("Approach 4: Single Pass with Start Index Tracking: ${canCompleteCircuitSinglePassStartIndex(gas, cost)}");
  print("Approach 5: Using Kadane's Algorithm (Variation): ${canCompleteCircuitKadane(gas, cost)}");

  gas = [5, 1, 2, 3, 4];
  cost = [4, 4, 1, 5, 1];
  print("\nTest Case 3: gas = $gas, cost = $cost");
  print("Approach 1: Brute Force: ${canCompleteCircuitBruteForce(gas, cost)}");
  print("Approach 2: Optimized Brute Force: ${canCompleteCircuitOptimizedBruteForce(gas, cost)}");
  print("Approach 3: Single Pass with Total Tank: ${canCompleteCircuitSinglePassTotalTank(gas, cost)}");
  print("Approach 4: Single Pass with Start Index Tracking: ${canCompleteCircuitSinglePassStartIndex(gas, cost)}");
  print("Approach 5: Using Kadane's Algorithm (Variation): ${canCompleteCircuitKadane(gas, cost)}");
}

/// Approach 1: Brute Force
///
/// Time Complexity: O(n^2)
/// Space Complexity: O(1)
///
/// For each starting gas station, simulate the entire trip to check if it's possible.
int canCompleteCircuitBruteForce(List<int> gas, List<int> cost) {
  int n = gas.length;
  for (int start = 0; start < n; start++) {
    int currentGas = 0;
    bool possible = true;
    for (int i = 0; i < n; i++) {
      int currentStation = (start + i) % n;
      currentGas += gas[currentStation] - cost[currentStation];
      if (currentGas < 0) {
        possible = false;
        break;
      }
    }
    if (possible) {
      return start;
    }
  }
  return -1;
}

/// Approach 2: Optimized Brute Force
///
/// Time Complexity: O(n^2) in the worst case, but often faster than the pure brute force.
/// Space Complexity: O(1)
///
/// Similar to brute force, but it stops checking a starting point as soon as the gas becomes negative.
int canCompleteCircuitOptimizedBruteForce(List<int> gas, List<int> cost) {
  int n = gas.length;
  for (int start = 0; start < n; start++) {
    int currentGas = 0;
    bool possible = true;
    for (int i = 0; i < n; i++) {
      int currentStation = (start + i) % n;
      currentGas += gas[currentStation] - cost[currentStation];
      if (currentGas < 0) {
        possible = false;
        break; // Important optimization: break here
      }
    }
    if (possible) {
      return start;
    }
  }
  return -1;
}

/// Approach 3: Single Pass with Total Tank
///
/// Time Complexity: O(n)
/// Space Complexity: O(1)
///
/// If the total gas is greater than or equal to the total cost, there must be a solution.
/// This approach calculates the total gas and cost in one pass.
int canCompleteCircuitSinglePassTotalTank(List<int> gas, List<int> cost) {
  int n = gas.length;
  int totalGas = 0;
  int totalCost = 0;

  for (int i = 0; i < n; i++) {
    totalGas += gas[i];
    totalCost += cost[i];
  }

  if (totalGas < totalCost) {
    return -1; // Not possible to complete the circuit
  }

  //Find the starting point.
  for (int start = 0; start < n; start++){
    int currentGas = 0;
    bool possible = true;
    for (int i = 0; i < n; i++) {
      int currentStation = (start + i) % n;
      currentGas += gas[currentStation] - cost[currentStation];
      if (currentGas < 0) {
        possible = false;
        break;
      }
    }
    if (possible) {
      return start;
    }
  }
  return -1;
}

/// Approach 4: Single Pass with Start Index Tracking
///
/// Time Complexity: O(n)
/// Space Complexity: O(1)
///
/// A more efficient single-pass solution.  If the current gas is negative,
/// reset the start index to the next station.
int canCompleteCircuitSinglePassStartIndex(List<int> gas, List<int> cost) {
  int n = gas.length;
  int totalGas = 0;
  int currentGas = 0;
  int start = 0;

  for (int i = 0; i < n; i++) {
    totalGas += gas[i] - cost[i];
    currentGas += gas[i] - cost[i];
    if (currentGas < 0) {
      start = i + 1; // Start from the next station
      currentGas = 0;    // Reset current gas
    }
  }

  if (totalGas < 0) {
    return -1; // Not possible to complete the circuit
  } else {
    return start;
  }
}

/// Approach 5: Using Kadane's Algorithm (Variation)
///
/// Time Complexity: O(n)
/// Space Complexity: O(1)
///
/// This approach adapts Kadane's algorithm to find the starting point.
int canCompleteCircuitKadane(List<int> gas, List<int> cost) {
  int n = gas.length;
  int start = 0;
  int currentGas = 0;
  int totalGas = 0;

  for (int i = 0; i < n; i++) {
    int diff = gas[i] - cost[i];
    currentGas += diff;
    totalGas += diff;

    if (currentGas < 0) {
      start = i + 1;
      currentGas = 0;
    }
  }

  return totalGas < 0 ? -1 : start;
}
