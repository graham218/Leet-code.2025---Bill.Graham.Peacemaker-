// Dart program to compute GCD using 5 different approaches
import 'dart:math';

void main() {
  int a = 56, b = 98;

  print("GCD calculations for $a and $b:"); // Print the input numbers.
  print("1. Recursive Euclidean Algorithm: ${gcdRecursive(a, b)}"); // Print the result of the recursive Euclidean algorithm.
  print("2. Iterative Euclidean Algorithm: ${gcdIterative(a, b)}"); // Print the result of the iterative Euclidean algorithm.
  print("3. Binary GCD Algorithm (Stein's Algorithm): ${gcdBinary(a, b)}"); // Print the result of the binary GCD algorithm.
  print("4. Using Prime Factorization: ${gcdPrimeFactorization(a, b)}"); // Print the result of the prime factorization method.
  print("5. Using Least Common Multiple (LCM): ${gcdUsingLCM(a, b)}"); // Print the result of the LCM method.
}

// Approach 1: Recursive Euclidean Algorithm
// Calculates the GCD of two numbers using the recursive Euclidean algorithm.
// It repeatedly applies the modulo operation until the remainder is 0.
int gcdRecursive(int a, int b) {
  return b == 0 ? a : gcdRecursive(b, a % b); // Base case: if b is 0, a is the GCD. Otherwise, recursively call with b and the remainder.
}

// Approach 2: Iterative Euclidean Algorithm
// Calculates the GCD of two numbers using the iterative Euclidean algorithm.
// It uses a while loop to repeatedly apply the modulo operation until the remainder is 0.
int gcdIterative(int a, int b) {
  while (b != 0) {
    final temp = b; // Store the current value of b. 'final' indicates it's assigned only once.
    b = a % b; // Update b with the remainder of a divided by b.
    a = temp; // Update a with the previous value of b.
  }
  return a; // When b becomes 0, a holds the GCD.
}

// Approach 3: Binary GCD Algorithm (Stein's Algorithm)
// Calculates the GCD of two numbers using Stein's algorithm, which is more efficient in some cases.
// It uses bitwise operations to avoid division.
int gcdBinary(int a, int b) {
  if (a == 0) return b; // If a is 0, b is the GCD.
  if (b == 0) return a; // If b is 0, a is the GCD.

  int shift = 0;
  // Remove common factors of 2.
  while (((a | b) & 1) == 0) { // While both a and b are even.
    a >>= 1; // Divide a by 2.
    b >>= 1; // Divide b by 2.
    shift++; // Increment the shift counter.
  }

  // Remove all factors of 2 from a.
  while ((a & 1) == 0) a >>= 1; // While a is even.

  // From here, a is always odd.
  while (b != 0) {
    // Remove all factors of 2 from b.
    while ((b & 1) == 0) b >>= 1; // While b is even.

    // Ensure a <= b.
    if (a > b) {
      final temp = a; // Store the value of a.
      a = b; // Swap a and b.
      b = temp; // Complete the swap.
    }

    // Replace b with b - a.
    b -= a;
  }
  // Restore common factors of 2.
  return a << shift; // Multiply a by 2^shift.
}

// Approach 4: GCD using Prime Factorization
// Calculates the GCD by finding the prime factors of both numbers and multiplying the common factors.
int gcdPrimeFactorization(int a, int b) {
  final factorsA = primeFactors(a); // Get the prime factors of a.
  final factorsB = primeFactors(b); // Get the prime factors of b.
  int gcd = 1;

  for (final factor in factorsA) {
    if (factorsB.contains(factor)) { // If the factor is present in both lists.
      gcd *= factor; // Multiply the factor to the GCD.
      factorsB.remove(factor); // Remove the factor from factorsB to avoid duplicates.
    }
  }
  return gcd;
}

// Helper function to find the prime factors of a number.
List<int> primeFactors(int n) {
  final factors = <int>[]; // Initialize an empty list to store the factors.
  var tempN = n; // Create a temporary variable to avoid modifying the original n.
  while (tempN % 2 == 0) { // Divide by 2 until tempN is odd.
    factors.add(2);
    tempN ~/= 2;
  }
  for (var i = 3; i <= sqrt(tempN); i += 2) { // Iterate from 3 to the square root of tempN, checking for odd factors.
    while (tempN % i == 0) {
      factors.add(i);
      tempN ~/= i;
    }
  }
  if (tempN > 1) factors.add(tempN); // If tempN is still greater than 1, it must be a prime factor.
  return factors;
}

// Approach 5: GCD using Least Common Multiple (LCM)
// Calculates the GCD using the relationship: GCD(a, b) = (a * b) / LCM(a, b).
int gcdUsingLCM(int a, int b) {
  return (a * b) ~/ lcm(a, b); // Calculate GCD using LCM.
}

// Helper function to calculate the LCM of two numbers.
int lcm(int a, int b) {
  return (a ~/ gcdIterative(a, b)) * b; // Calculate LCM using the iterative GCD function.
}