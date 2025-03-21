import 'dart:math' as math;

class AdvancedPowerOfTwo {
  // Approach 1: Bitwise AND Check
  // Fastest method, works in O(1) time
  static bool isPowerOfTwoBitwise(int n) {
    return n > 0 && (n & (n - 1)) == 0;
  }

  // Approach 2: Logarithm Method (Floating Point Precision Handling)
  static bool isPowerOfTwoLog(int n) {
    if (n <= 0) return false;
    double logValue = math.log(n) / math.log(2);
    return (logValue - logValue.floor()).abs() < 1e-10;
  }

  // Approach 3: Iterative Division
  // Useful in environments where bitwise operations are limited
  static bool isPowerOfTwoIterative(int n) {
    if (n <= 0) return false;
    while (n % 2 == 0) {
      n ~/= 2;
    }
    return n == 1;
  }

  // Approach 4: Lookup Table (Useful for Small Numbers in Performance-Critical Apps)
  static final Set<int> powerOfTwoSet = {for (int i = 0; i <= 30; i++) 1 << i};
  static bool isPowerOfTwoLookup(int n) {
    return powerOfTwoSet.contains(n);
  }

  // Approach 5: Using Bit Counting (Hamming Weight Approach)
  static bool isPowerOfTwoBitCount(int n) {
    return n > 0 && n.toRadixString(2).replaceAll('0', '').length == 1;
  }

  // Approach 6: Using Recursion (Elegant but less efficient)
  static bool isPowerOfTwoRecursive(int n) {
    if (n <= 0) return false;
    if (n == 1) return true;
    if (n % 2 != 0) return false;
    return isPowerOfTwoRecursive(n ~/ 2);
  }
}

void main() {
  int testNum = 64;
  print("Bitwise AND Check: ${AdvancedPowerOfTwo.isPowerOfTwoBitwise(testNum)}");
  print("Logarithm Method: ${AdvancedPowerOfTwo.isPowerOfTwoLog(testNum)}");
  print("Iterative Division: ${AdvancedPowerOfTwo.isPowerOfTwoIterative(testNum)}");
  print("Lookup Table: ${AdvancedPowerOfTwo.isPowerOfTwoLookup(testNum)}");
  print("Bit Counting: ${AdvancedPowerOfTwo.isPowerOfTwoBitCount(testNum)}");
  print("Recursive Method: ${AdvancedPowerOfTwo.isPowerOfTwoRecursive(testNum)}");
}
