import 'dart:math' as Math;

class PowerOfTwoChecker {
  // Approach 1: Using Bitwise AND (Most Efficient)
  // Checks if 'num' has exactly one bit set
  static bool isPowerOfTwoAnd(int num) {
    return (num > 0) && ((num & (num - 1)) == 0);
  }

  // Approach 2: Using Bit Count (Counting Set Bits)
  // If a number is a power of two, it has only one '1' in its binary representation
  static bool isPowerOfTwoCount(int num) {
    int count = 0;
    while (num > 0) {
      count += (num & 1);
      num >>= 1;
    }
    return count == 1;
  }

  // Approach 3: Using Logarithm
  // log2(num) should be an integer for powers of two
  static bool isPowerOfTwoLog(int num) {
    if (num <= 0) return false;
    double logValue = (Math.log(num) / Math.log(2));
    return logValue == logValue.toInt();
  }

  // Approach 4: Recursion-Based Approach
  // Keeps dividing by 2 until num becomes 1 (valid) or an odd number (invalid)
  static bool isPowerOfTwoRecursive(int num) {
    if (num <= 0) return false;
    if (num == 1) return true;
    if (num % 2 != 0) return false;
    return isPowerOfTwoRecursive(num ~/ 2);
  }

  // Approach 5: Using a Precomputed Set of Powers of Two (Look-up Table)
  static bool isPowerOfTwoLookup(int num) {
    Set<int> powersOfTwo = {
      1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072,
      262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728,
      268435456, 536870912, 1073741824
    };
    return powersOfTwo.contains(num);
  }
}

void main() {
  int num = 16;
  print("Using Bitwise AND: ${PowerOfTwoChecker.isPowerOfTwoAnd(num)}");
  print("Using Bit Count: ${PowerOfTwoChecker.isPowerOfTwoCount(num)}");
  print("Using Logarithm: ${PowerOfTwoChecker.isPowerOfTwoLog(num)}");
  print("Using Recursion: ${PowerOfTwoChecker.isPowerOfTwoRecursive(num)}");
  print("Using Look-up Table: ${PowerOfTwoChecker.isPowerOfTwoLookup(num)}");
}
