class NumberOf1Bits {
  // Approach 1: Using Built-in Method (toRadixString)
  // Converts number to binary and counts '1's
  static int hammingWeightString(int n) {
    return n.toRadixString(2).split('').where((bit) => bit == '1').length;
  }

  // Approach 2: Using Bitwise AND with Right Shift
  // Checks each bit by shifting and counting '1's
  static int hammingWeightBitwiseShift(int n) {
    int count = 0;
    while (n != 0) {
      count += n & 1;
      n >>= 1;
    }
    return count;
  }

  // Approach 3: Using Brian Kernighan’s Algorithm
  // Clears the least significant '1' bit in each iteration
  static int hammingWeightKernighan(int n) {
    int count = 0;
    while (n != 0) {
      n &= (n - 1);
      count++;
    }
    return count;
  }

  // Approach 4: Using Lookup Table (Efficient for Multiple Queries)
  static List<int> _lookupTable = List.generate(256, (i) => i.toRadixString(2).split('').where((bit) => bit == '1').length);
  static int hammingWeightLookup(int n) {
    return _lookupTable[n & 0xFF] +
        _lookupTable[(n >> 8) & 0xFF] +
        _lookupTable[(n >> 16) & 0xFF] +
        _lookupTable[(n >> 24) & 0xFF];
  }

  // Approach 5: Using Parallel Bitwise Operations (Optimized)
  static int hammingWeightParallel(int n) {
    n = n - ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = (n + (n >> 4)) & 0x0F0F0F0F;
    n = n + (n >> 8);
    n = n + (n >> 16);
    return n & 0x3F;
  }
}

void main() {
  int num = 29; // Binary: 11101 (Has 4 ones)
  print("String Method: " + NumberOf1Bits.hammingWeightString(num).toString());      // Output: 4
  print("Bitwise Shift Method: " + NumberOf1Bits.hammingWeightBitwiseShift(num).toString()); // Output: 4
  print("Kernighan's Algorithm: " + NumberOf1Bits.hammingWeightKernighan(num).toString());   // Output: 4
  print("Lookup Table Method: " + NumberOf1Bits.hammingWeightLookup(num).toString());      // Output: 4
  print("Parallel Bitwise Method: " + NumberOf1Bits.hammingWeightParallel(num).toString());    // Output: 4
}
