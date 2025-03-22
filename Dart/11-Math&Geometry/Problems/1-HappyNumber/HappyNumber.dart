// Dart program implementing the Happy Number problem using 5 different approaches
import 'dart:collection';

void main() {
  int num = 19;

  print("Happy Number computations for $num using different approaches:");
  print("1. Standard Iterative Approach: ${isHappyIterative(num)}");
  print("2. Recursive Approach: ${isHappyRecursive(num)}");
  print("3. Floyd’s Cycle Detection (Optimized for Performance): ${isHappyFloyd(num)}");
  print("4. HashSet Approach (Detecting Cycles Efficiently): ${isHappyHashSet(num)}");
  print("5. Mathematical Optimization (Precomputed Cycles): ${isHappyMathOptimized(num)}");
}

// Helper function to compute the sum of squares of digits
// This function calculates the sum of the squares of the digits of a given number.
int sumOfSquares(int n) {
  int sum = 0;
  while (n > 0) {
    int digit = n % 10; // Extract the last digit.
    sum += digit * digit; // Add the square of the digit to the sum.
    n ~/= 10; // Remove the last digit.
  }
  return sum;
}

// Approach 1: Standard Iterative Approach
// This approach uses a HashSet to detect cycles.
// It iteratively calculates the sum of squares until it reaches 1 or encounters a cycle.
bool isHappyIterative(int n) {
  Set<int> seen = {}; // Initialize a HashSet to store seen numbers.
  while (n != 1 && !seen.contains(n)) { // Loop until n is 1 or a cycle is detected.
    seen.add(n); // Add the current number to the HashSet.
    n = sumOfSquares(n); // Calculate the sum of squares.
  }
  return n == 1; // Return true if n is 1 (happy number), false otherwise.
}

// Approach 2: Recursive Approach
// This approach uses recursion and a HashSet to detect cycles.
// It's similar to the iterative approach but uses recursion.
bool isHappyRecursive(int n, [Set<int>? seen]) {
  seen ??= {}; // Initialize seen HashSet if it's null.
  if (n == 1) return true; // Base case: n is 1 (happy number).
  if (seen.contains(n)) return false; // Base case: cycle detected.
  seen.add(n); // Add the current number to the HashSet.
  return isHappyRecursive(sumOfSquares(n), seen); // Recursive call.
}

// Approach 3: Floyd’s Cycle Detection Algorithm (Optimized for Performance)
// This approach uses Floyd’s cycle detection algorithm (tortoise and hare).
// It's optimized for performance as it avoids storing all seen numbers.
bool isHappyFloyd(int n) {
  int slow = n, fast = sumOfSquares(n); // Initialize slow and fast pointers.
  while (fast != 1 && slow != fast) { // Loop until fast is 1 or slow and fast meet.
    slow = sumOfSquares(slow); // Move slow pointer one step.
    fast = sumOfSquares(sumOfSquares(fast)); // Move fast pointer two steps.
  }
  return fast == 1; // Return true if fast is 1 (happy number), false otherwise.
}

// Approach 4: HashSet Approach (Efficient Cycle Detection)
// This approach is identical to the iterative approach, but uses a HashSet explicitly.
// It's efficient for cycle detection due to the HashSet's constant-time lookup.
bool isHappyHashSet(int n) {
  HashSet<int> seen = HashSet<int>(); // Initialize a HashSet.
  while (n != 1 && !seen.contains(n)) { // Loop until n is 1 or a cycle is detected.
    seen.add(n); // Add the current number to the HashSet.
    n = sumOfSquares(n); // Calculate the sum of squares.
  }
  return n == 1; // Return true if n is 1 (happy number), false otherwise.
}

// Approach 5: Mathematical Optimization (Precomputed Cycles)
// This approach uses mathematical optimization by precomputing the unhappy cycle.
// It's efficient as it avoids repeated calculations by checking against a known cycle.
bool isHappyMathOptimized(int n) {
  const Set<int> unhappyCycle = {4, 16, 37, 58, 89, 145, 42, 20}; // Precomputed unhappy cycle.
  while (n != 1 && !unhappyCycle.contains(n)) { // Loop until n is 1 or in the unhappy cycle.
    n = sumOfSquares(n); // Calculate the sum of squares.
  }
  return n == 1; // Return true if n is 1 (happy number), false otherwise.
}