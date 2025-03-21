class BitwiseOperations {
  // Approach 1: Basic AND, OR, XOR Operations
  static Map<String, int> basicBitwiseOps(int a, int b) {
    return {
      'AND': a & b,
      'OR': a | b,
      'XOR': a ^ b,
    };
  }

  // Approach 2: Using Bitwise Operators for Set Operations
  static Map<String, Set<int>> bitwiseSetOperations(Set<int> setA, Set<int> setB) {
    int a = setA.fold(0, (prev, element) => prev | (1 << element));
    int b = setB.fold(0, (prev, element) => prev | (1 << element));

    return {
      'Intersection (AND)': {for (int i = 0; i < 32; i++) if ((a & b) & (1 << i) != 0) i},
      'Union (OR)': {for (int i = 0; i < 32; i++) if ((a | b) & (1 << i) != 0) i},
      'Symmetric Difference (XOR)': {for (int i = 0; i < 32; i++) if ((a ^ b) & (1 << i) != 0) i},
    };
  }

  // Approach 3: Counting Set Bits (Hamming Weight) Using AND
  static int countSetBits(int n) {
    int count = 0;
    while (n > 0) {
      count += (n & 1);
      n >>= 1;
    }
    return count;
  }

  // Approach 4: Checking If a Number Is Even or Odd Using AND
  static bool isEven(int n) {
    return (n & 1) == 0;
  }

  // Approach 5: Swapping Two Numbers Using XOR (without temporary variable)
  static List<int> swapUsingXOR(int a, int b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    return [a, b];
  }
}

void main() {
  int a = 5, b = 3;
  print("Basic Bitwise Operations: ${BitwiseOperations.basicBitwiseOps(a, b)}");

  Set<int> setA = {1, 2, 3, 5};
  Set<int> setB = {2, 3, 6};
  print("Bitwise Set Operations: ${BitwiseOperations.bitwiseSetOperations(setA, setB)}");

  int num = 29; // Binary: 11101
  print("Count of Set Bits in $num: ${BitwiseOperations.countSetBits(num)}");

  print("Is $num Even? ${BitwiseOperations.isEven(num)}");

  List<int> swapped = BitwiseOperations.swapUsingXOR(a, b);
  print("Swapped values: a=${swapped[0]}, b=${swapped[1]}");
}
