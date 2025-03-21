class BitmaskingAlgorithms {
  // Approach 1: Checking if a Bit is Set
  static bool isBitSet(int num, int pos) {
    return (num & (1 << pos)) != 0;
  }

  // Approach 2: Setting a Specific Bit
  static int setBit(int num, int pos) {
    return num | (1 << pos);
  }

  // Approach 3: Clearing a Specific Bit
  static int clearBit(int num, int pos) {
    return num & ~(1 << pos);
  }

  // Approach 4: Toggling a Specific Bit
  static int toggleBit(int num, int pos) {
    return num ^ (1 << pos);
  }

  // Approach 5: Counting Set Bits (Hamming Weight) Using Bitmasking
  static int countSetBits(int num) {
    int count = 0;
    while (num > 0) {
      count += num & 1;
      num >>= 1;
    }
    return count;
  }
}

void main() {
  int num = 42; // Binary: 101010
  int pos = 3;

  print("Is bit at position $pos set in $num? ${BitmaskingAlgorithms.isBitSet(num, pos)}");
  print("Setting bit at position $pos: ${BitmaskingAlgorithms.setBit(num, pos)}");
  print("Clearing bit at position $pos: ${BitmaskingAlgorithms.clearBit(num, pos)}");
  print("Toggling bit at position $pos: ${BitmaskingAlgorithms.toggleBit(num, pos)}");
  print("Total set bits in $num: ${BitmaskingAlgorithms.countSetBits(num)}");
}
