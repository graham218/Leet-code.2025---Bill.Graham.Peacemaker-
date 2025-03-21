import 'dart:math' as Math;

class AdvancedPowerOfTwoChecker {
  // Approach 1: Using Bitwise AND (Most Efficient)
  static bool isPowerOfTwoAnd(int num) {
    return (num > 0) && ((num & (num - 1)) == 0);
  }

  // Approach 2: Using Bitwise OR and XOR
  static bool isPowerOfTwoXorOr(int num) {
    return (num > 0) && ((num | (num - 1)) == (2 * num - 1));
  }

  // Approach 3: Using Math.log2 (Floating Point Precision Approach)
  static bool isPowerOfTwoLog(int num) {
    if (num <= 0) return false;
    double logValue = Math.log(num) / Math.ln2;
    return logValue == logValue.roundToDouble();
  }

  // Approach 4: Using Shift Operations
  static bool isPowerOfTwoShift(int num) {
    for (int i = 0; i < 31; i++) {
      if ((1 << i) == num) return true;
    }
    return false;
  }

  // Approach 5: Using Recursion (Divide by 2 Until 1 is Reached)
  static bool isPowerOfTwoRecursive(int num) {
    if (num == 1) return true;
    if (num <= 0 || num % 2 != 0) return false;
    return isPowerOfTwoRecursive(num ~/ 2);
  }

  // Approach 6: Using Set Containment (Precomputed Powers of Two)
  static final Set<int> _precomputedPowers = {
    for (int i = 0; i < 31; i++) 1 << i
  };
  static bool isPowerOfTwoLookup(int num) {
    return _precomputedPowers.contains(num);
  }
}

void main() {
  int num = 32;
  print("Using Bitwise AND: ${AdvancedPowerOfTwoChecker.isPowerOfTwoAnd(num)}");
  print("Using Bitwise OR and XOR: ${AdvancedPowerOfTwoChecker.isPowerOfTwoXorOr(num)}");
  print("Using Logarithm: ${AdvancedPowerOfTwoChecker.isPowerOfTwoLog(num)}");
  print("Using Shift Operations: ${AdvancedPowerOfTwoChecker.isPowerOfTwoShift(num)}");
  print("Using Recursion: ${AdvancedPowerOfTwoChecker.isPowerOfTwoRecursive(num)}");
  print("Using Lookup Table: ${AdvancedPowerOfTwoChecker.isPowerOfTwoLookup(num)}");
}