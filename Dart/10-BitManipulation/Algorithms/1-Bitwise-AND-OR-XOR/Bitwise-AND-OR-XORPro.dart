class AdvancedBitwiseOperations {
  // Approach 1: Bitwise AND, OR, XOR using Shifting
  static Map<String, int> bitwiseUsingShift(int a, int b) {
    return {
      'AND': (a >> 1) & (b >> 1),
      'OR': (a >> 1) | (b >> 1),
      'XOR': (a >> 1) ^ (b >> 1),
    };
  }

  // Approach 2: Finding the Highest Power of Two Less Than or Equal to n
  static int highestPowerOfTwo(int n) {
    if (n == 0) return 0;
    int power = 1;
    while (power <= n) {
      power <<= 1;
    }
    return power >> 1;
  }

  // Approach 3: Checking if a Number is a Power of Two Using Bitwise Operations
  static bool isPowerOfTwo(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
  }

  // Approach 4: Toggle a Specific Bit in an Integer
  static int toggleBit(int n, int pos) {
    return n ^ (1 << pos);
  }

  // Approach 5: Count Leading Zeros (using bit shifting)
  static int countLeadingZeros(int n) {
    if (n == 0) return 32;
    int count = 0;
    while ((n & (1 << 31)) == 0) {
      count++;
      n <<= 1;
    }
    return count;
  }

  // Approach 6: Reverse Bits of an Integer
  static int reverseBits(int n) {
    int result = 0;
    for (int i = 0; i < 32; i++) {
      result <<= 1;
      result |= (n & 1);
      n >>= 1;
    }
    return result;
  }
}

void main() {
  int a = 6, b = 3;
  print("Bitwise Operations Using Shift: ${AdvancedBitwiseOperations.bitwiseUsingShift(a, b)}");

  int num = 36;
  print("Highest Power of Two ≤ $num: ${AdvancedBitwiseOperations.highestPowerOfTwo(num)}");

  print("Is $num a Power of Two? ${AdvancedBitwiseOperations.isPowerOfTwo(num)}");

  int toggled = AdvancedBitwiseOperations.toggleBit(num, 2);
  print("Number after toggling bit at position 2: $toggled");

  print("Leading zeros in $num: ${AdvancedBitwiseOperations.countLeadingZeros(num)}");

  int reversed = AdvancedBitwiseOperations.reverseBits(num);
  print("Reversed bits of $num: $reversed");
}
