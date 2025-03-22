// Dart program implementing Fast Exponentiation using 5 different approaches
import 'dart:math';

void main() {
  int base = 3;
  int exponent = 13;
  int mod = 1000000007; // A common prime modulus for cryptographic applications.

  print("Fast Exponentiation results for base $base and exponent $exponent:");
  print("1. Iterative Binary Exponentiation: ${iterativeBinaryExpo(base, exponent)}");
  print("2. Recursive Binary Exponentiation: ${recursiveBinaryExpo(base, exponent)}");
  print("3. Modular Exponentiation (Crypto Applications): ${modularExponentiation(base, exponent, mod)}");
  print("4. Matrix Exponentiation (Fibonacci Computation): ${matrixExponentiation(base, exponent)}");
  print("5. Exponentiation by Squaring using Bitwise Operations: ${bitwiseExponentiation(base, exponent)}");
}

// Approach 1: Iterative Binary Exponentiation
// Calculates base^exponent iteratively using binary exponentiation.
// It exploits the binary representation of the exponent to reduce the number of multiplications.
int iterativeBinaryExpo(int base, int exponent) {
  int result = 1;
  while (exponent > 0) {
    if (exponent % 2 == 1) { // If the least significant bit is 1.
      result *= base; // Multiply result by base.
    }
    base *= base; // Square the base.
    exponent ~/= 2; // Right shift the exponent (divide by 2).
  }
  return result;
}

// Approach 2: Recursive Binary Exponentiation
// Calculates base^exponent recursively using binary exponentiation.
// It follows the same principle as the iterative approach but uses recursion.
int recursiveBinaryExpo(int base, int exponent) {
  if (exponent == 0) return 1; // Base case: base^0 = 1.
  int half = recursiveBinaryExpo(base, exponent ~/ 2); // Recursively calculate base^(exponent/2).
  return (exponent % 2 == 0) ? half * half : half * half * base; // Return half^2 or half^2 * base.
}

// Approach 3: Modular Exponentiation (Used in Cryptography)
// Calculates (base^exponent) % mod efficiently.
// It's crucial in cryptographic applications where large numbers are involved.
int modularExponentiation(int base, int exponent, int mod) {
  int result = 1;
  base %= mod; // Reduce base modulo mod.
  while (exponent > 0) {
    if (exponent % 2 == 1) { // If the least significant bit is 1.
      result = (result * base) % mod; // Multiply and take modulo.
    }
    base = (base * base) % mod; // Square and take modulo.
    exponent ~/= 2; // Right shift the exponent.
  }
  return result;
}

// Approach 4: Matrix Exponentiation (Used in Fibonacci Computation)
// Calculates base^exponent using matrix exponentiation.
// It's used to efficiently compute terms of linear recurrence relations, such as the Fibonacci sequence.
int matrixExponentiation(int base, int exponent) {
  List<List<int>> matrix = [[1, 1], [1, 0]]; // Initialize the matrix for Fibonacci.
  if (exponent == 0) return 1;
  return matrixPower(matrix, exponent)[0][0]; // Return the top-left element of the resulting matrix.
}

// Helper function to calculate matrix^exponent.
List<List<int>> matrixPower(List<List<int>> matrix, int exponent) {
  if (exponent == 1) return matrix; // Base case: matrix^1 = matrix.
  List<List<int>> halfPower = matrixPower(matrix, exponent ~/ 2); // Recursively calculate matrix^(exponent/2).
  List<List<int>> result = multiplyMatrices(halfPower, halfPower); // Multiply halfPower with itself.
  if (exponent % 2 != 0) { // If exponent is odd.
    result = multiplyMatrices(result, [[1, 1], [1, 0]]); // Multiply result with the base matrix.
  }
  return result;
}

// Helper function to multiply two 2x2 matrices.
List<List<int>> multiplyMatrices(List<List<int>> a, List<List<int>> b) {
  return [
    [(a[0][0] * b[0][0] + a[0][1] * b[1][0]), (a[0][0] * b[0][1] + a[0][1] * b[1][1])],
    [(a[1][0] * b[0][0] + a[1][1] * b[1][0]), (a[1][0] * b[0][1] + a[1][1] * b[1][1])]
  ];
}

// Approach 5: Exponentiation by Squaring using Bitwise Operations
// Calculates base^exponent using bitwise operations for efficiency.
// It's similar to the iterative approach but uses bitwise operators.
int bitwiseExponentiation(int base, int exponent) {
  int result = 1;
  while (exponent > 0) {
    if ((exponent & 1) == 1) { // If the least significant bit is 1.
      result *= base; // Multiply result by base.
    }
    base *= base; // Square the base.
    exponent >>= 1; // Right shift the exponent.
  }
  return result;
}