class AdvancedBitmasking {
  // Approach 1: Checking if a Number is a Power of Two (Bitmasking)
  // Useful in memory allocation and optimization
  static bool isPowerOfTwo(int num) {
    return (num > 0) && ((num & (num - 1)) == 0);
  }

  // Approach 2: Finding the Unique Number in an Array where Every Other Number Appears Twice
  // Used in data processing and cryptography
  static int findUnique(List<int> arr) {
    int unique = 0;
    for (int num in arr) {
      unique ^= num; // XOR cancels out duplicate values
    }
    return unique;
  }

  // Approach 3: Generating All Possible Subsets Using Bitmasking
  // Used in combinatorial problems and machine learning feature selection
  static List<List<int>> generateSubsets(List<int> arr) {
    int n = arr.length;
    List<List<int>> subsets = [];
    for (int mask = 0; mask < (1 << n); mask++) {
      List<int> subset = [];
      for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) != 0) {
          subset.add(arr[i]);
        }
      }
      subsets.add(subset);
    }
    return subsets;
  }

  // Approach 4: Flipping All Bits of a Number (Bitwise NOT)
  // Used in image processing and binary manipulation
  static int flipBits(int num) {
    return ~num;
  }

  // Approach 5: Counting Set Bits Using Brian Kernighan’s Algorithm
  // Optimized bit-counting used in image compression and cryptographic hashing
  static int countSetBits(int num) {
    int count = 0;
    while (num > 0) {
      num &= (num - 1); // Drops the lowest set bit
      count++;
    }
    return count;
  }

  // Approach 6: Finding the Position of the Rightmost Set Bit
  // Used in error detection and low-level debugging
  static int positionOfRightmostSetBit(int num) {
    return (num & -num).bitLength - 1;
  }
}

void main() {
  int num = 18; // Binary: 10010
  List<int> arr = [2, 3, 5, 3, 2, 5, 7];

  print("Is $num a power of two? ${AdvancedBitmasking.isPowerOfTwo(num)}");
  print("Unique number in array: ${AdvancedBitmasking.findUnique(arr)}");
  print("All subsets of [1, 2, 3]: ${AdvancedBitmasking.generateSubsets([1, 2, 3])}");
  print("Flipped bits of $num: ${AdvancedBitmasking.flipBits(num)}");
  print("Number of set bits in $num: ${AdvancedBitmasking.countSetBits(num)}");
  print("Position of rightmost set bit in $num: ${AdvancedBitmasking.positionOfRightmostSetBit(num)}");
}
