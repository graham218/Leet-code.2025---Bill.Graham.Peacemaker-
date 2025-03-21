class AdvancedNumberOf1Bits {
  // Approach 1: Using Integer Bit Count (For Modern Processors)
  // Uses Dart's built-in functions for handling binary conversion.
  static int countBitsBuiltIn(int n) {
    return n.toRadixString(2).replaceAll('0', '').length;
  }

  // Approach 2: Iterative Bit Masking
  // Iterates through each bit position using a bitmask.
  static int countBitsBitMasking(int n) {
    int count = 0;
    for (int i = 0; i < 32; i++) {
      if ((n & (1 << i)) != 0) {
        count++;
      }
    }
    return count;
  }

  // Approach 3: Brian Kernighan’s Algorithm
  // Efficient method for clearing set bits one by one.
  static int countBitsKernighan(int n) {
    int count = 0;
    while (n > 0) {
      n &= (n - 1);
      count++;
    }
    return count;
  }

  // Approach 4: Divide and Conquer Bit Counting (Parallel Computation)
  // Optimized bit counting using parallel processing logic.
  static int countBitsParallel(int n) {
    n = n - ((n >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = (n + (n >> 4)) & 0x0F0F0F0F;
    n = n + (n >> 8);
    n = n + (n >> 16);
    return n & 0x3F;
  }

  // Approach 5: Using Hamming Weight Lookup Table (For Large Datasets)
  static final List<int> _lookupTable = List.generate(256, (i) => i.toRadixString(2).replaceAll('0', '').length);
  static int countBitsLookup(int n) {
    return _lookupTable[n & 0xFF] +
        _lookupTable[(n >> 8) & 0xFF] +
        _lookupTable[(n >> 16) & 0xFF] +
        _lookupTable[(n >> 24) & 0xFF];
  }

  // Approach 6: Using Recursive Method
  // Recursive approach for counting set bits.
  static int countBitsRecursive(int n) {
    if (n == 0) return 0;
    return (n & 1) + countBitsRecursive(n >> 1);
  }
}

void main() {
  int num = 12345; // Example number
  print("Built-in Method: ${AdvancedNumberOf1Bits.countBitsBuiltIn(num)}");
  print("Bit Masking: ${AdvancedNumberOf1Bits.countBitsBitMasking(num)}");
  print("Kernighan's Algorithm: ${AdvancedNumberOf1Bits.countBitsKernighan(num)}");
  print("Parallel Bitwise Computation: ${AdvancedNumberOf1Bits.countBitsParallel(num)}");
  print("Lookup Table Method: ${AdvancedNumberOf1Bits.countBitsLookup(num)}");
  print("Recursive Method: ${AdvancedNumberOf1Bits.countBitsRecursive(num)}");
}
