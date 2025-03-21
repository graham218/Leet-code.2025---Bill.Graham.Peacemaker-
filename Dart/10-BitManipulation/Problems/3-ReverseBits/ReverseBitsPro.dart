class AdvancedReverseBits {
  // Approach 1: Bit Manipulation Using Shift and OR
  static int reverseBitsShift(int n) {
    int reversed = 0;
    for (int i = 0; i < 32; i++) {
      reversed |= (n & 1) << (31 - i);
      n >>= 1;
    }
    return reversed;
  }

  // Approach 2: Recursive Bit Reversal
  static int reverseBitsRecursive(int n, int pos) {
    if (pos < 0) return 0;
    return ((n & 1) << pos) | reverseBitsRecursive(n >> 1, pos - 1);
  }

  // Approach 3: Byte-wise Reverse Using Lookup Table
  static final List<int> lookupTable = List.generate(256, (i) => reverseBitsShift(i));
  static int reverseBitsLookup(int n) {
    return (lookupTable[n & 0xFF] << 24) |
    (lookupTable[(n >> 8) & 0xFF] << 16) |
    (lookupTable[(n >> 16) & 0xFF] << 8) |
    (lookupTable[(n >> 24) & 0xFF]);
  }

  // Approach 4: Divide and Conquer Bitwise Swapping
  static int reverseBitsDivideAndConquer(int n) {
    n = ((n >> 16) & 0x0000FFFF) | ((n & 0x0000FFFF) << 16);
    n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8);
    n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4);
    n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2);
    n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1);
    return n;
  }

  // Approach 5: Using BigInt for Large Numbers
  static int reverseBitsBigInt(int n) {
    BigInt bigN = BigInt.from(n);
    BigInt reversed = BigInt.zero;
    for (int i = 0; i < 32; i++) {
      reversed |= (bigN & BigInt.one) << (31 - i);
      bigN >>= 1;
    }
    return reversed.toInt();
  }

  // Approach 6: Using Binary String Reversal
  static int reverseBitsString(int n) {
    String binaryStr = n.toRadixString(2).padLeft(32, '0');
    String reversedStr = binaryStr.split('').reversed.join();
    return int.parse(reversedStr, radix: 2);
  }
}

void main() {
  int num = 43261596; // Example number
  print("Bit Manipulation: ${AdvancedReverseBits.reverseBitsShift(num)}");
  print("Recursive Method: ${AdvancedReverseBits.reverseBitsRecursive(num, 31)}");
  print("Lookup Table: ${AdvancedReverseBits.reverseBitsLookup(num)}");
  print("Divide & Conquer: ${AdvancedReverseBits.reverseBitsDivideAndConquer(num)}");
  print("BigInt Handling: ${AdvancedReverseBits.reverseBitsBigInt(num)}");
  print("String Reversal: ${AdvancedReverseBits.reverseBitsString(num)}");
}
