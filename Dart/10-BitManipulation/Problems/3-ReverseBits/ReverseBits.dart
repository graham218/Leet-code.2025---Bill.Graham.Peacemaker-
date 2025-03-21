class ReverseBits {
  // Approach 1: Bitwise Reversal with Loop
  // Iterates through all bits and constructs reversed number.
  static int reverseBitsLoop(int n) {
    int result = 0;
    for (int i = 0; i < 32; i++) {
      result = (result << 1) | (n & 1);
      n >>= 1;
    }
    return result;
  }

  // Approach 2: Using String Manipulation
  // Converts number to binary string, reverses, and parses back.
  static int reverseBitsString(int n) {
    String binaryStr = n.toRadixString(2).padLeft(32, '0');
    String reversedStr = binaryStr.split('').reversed.join();
    return int.parse(reversedStr, radix: 2);
  }

  // Approach 3: Divide and Conquer Bitwise Swapping
  // Uses bitwise operations to swap bits in groups for efficiency.
  static int reverseBitsDivideAndConquer(int n) {
    n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1);
    n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2);
    n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4);
    n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8);
    n = ((n >> 16) & 0x0000FFFF) | ((n & 0x0000FFFF) << 16);
    return n;
  }

  // Approach 4: Lookup Table Method (Precomputed Reverse of Bytes)
  static final List<int> lookupTable = List.generate(256, (i) => reverseBitsLoop(i));
  static int reverseBitsLookup(int n) {
    return (lookupTable[n & 0xFF] << 24) |
    (lookupTable[(n >> 8) & 0xFF] << 16) |
    (lookupTable[(n >> 16) & 0xFF] << 8) |
    (lookupTable[(n >> 24) & 0xFF]);
  }

  // Approach 5: Recursive Bitwise Reversal
  // Uses recursion to reverse bits efficiently.
  static int reverseBitsRecursive(int n, int pos) {
    if (pos == 0) return n;
    return ((n & 1) << (31 - pos)) | reverseBitsRecursive(n >> 1, pos - 1);
  }
}

void main() {
  int num = 43261596; // Example number
  print("Loop Method: ${ReverseBits.reverseBitsLoop(num)}");
  print("String Manipulation: ${ReverseBits.reverseBitsString(num)}");
  print("Divide and Conquer: ${ReverseBits.reverseBitsDivideAndConquer(num)}");
  print("Lookup Table: ${ReverseBits.reverseBitsLookup(num)}");
  print("Recursive Method: ${ReverseBits.reverseBitsRecursive(num, 31)}");
}
