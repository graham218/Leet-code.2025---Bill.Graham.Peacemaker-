import 'dart:math' as Math;

class PowerOfTwo {
  // Approach 1: Bitwise AND Method
  // A power of two has only one bit set (e.g., 1, 2, 4, 8, ...)
  // n & (n - 1) removes the rightmost bit, so it should become 0
  static bool isPowerOfTwoBitwise(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
  }

  // Approach 2: Using Logarithm (Mathematical Approach)
  // If log2(n) is an integer, then n is a power of two.
  static bool isPowerOfTwoLog(int n) {
    if (n <= 0) return false;
    double logValue = (Math.log(n) / Math.log(2));
    return logValue == logValue.toInt();
  }

  // Approach 3: Recursion Method
  // Recursively divide by 2 until we reach 1, else return false
  static bool isPowerOfTwoRecursive(int n) {
    if (n <= 0) return false;
    if (n == 1) return true;
    if (n % 2 != 0) return false;
    return isPowerOfTwoRecursive(n ~/ 2);
  }

  // Approach 4: Counting Set Bits (Hamming Weight)
  // A power of two should only have one bit set in its binary representation.
  static bool isPowerOfTwoSetBits(int n) {
    int count = 0;
    while (n > 0) {
      count += (n & 1);
      n >>= 1;
    }
    return count == 1;
  }

  // Approach 5: Using Lookup Table (Precomputed Values for Small Numbers)
  static final Set<int> powerOfTwoSet = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};
  static bool isPowerOfTwoLookup(int n) {
    return powerOfTwoSet.contains(n);
  }
}

void main() {
  int num = 16; // Example number
  print("Bitwise AND Method: ${PowerOfTwo.isPowerOfTwoBitwise(num)}");
  print("Logarithm Method: ${PowerOfTwo.isPowerOfTwoLog(num)}");
  print("Recursive Method: ${PowerOfTwo.isPowerOfTwoRecursive(num)}");
  print("Set Bits Counting: ${PowerOfTwo.isPowerOfTwoSetBits(num)}");
  print("Lookup Table Method: ${PowerOfTwo.isPowerOfTwoLookup(num)}");
}