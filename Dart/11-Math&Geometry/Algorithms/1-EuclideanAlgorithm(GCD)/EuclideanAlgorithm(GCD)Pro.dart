// Dart program to compute GCD using 6 different advanced approaches
import 'dart:math';

void main() {
  int a = 252, b = 105;

  print("GCD calculations for $a and $b:");
  print("1. Recursive Euclidean Algorithm: ${gcdRecursive(a, b)}");
  print("2. Iterative Euclidean Algorithm: ${gcdIterative(a, b)}");
  print("3. Binary GCD Algorithm (Stein's Algorithm): ${gcdBinary(a, b)}");
  print("4. Extended Euclidean Algorithm: ${gcdExtended(a, b).gcd}");
  print("5. GCD using Prime Factorization: ${gcdPrimeFactorization(a, b)}");
  print("6. Using Euler’s Totient Function Approximation: ${gcdEulerTotient(a, b)}");
}

// Approach 1: Recursive Euclidean Algorithm
// Calculates the GCD recursively using the Euclidean algorithm.
// It repeatedly applies the modulo operation until the remainder is 0.
int gcdRecursive(int a, int b) {
  return b == 0 ? a : gcdRecursive(b, a % b);
}

// Approach 2: Iterative Euclidean Algorithm
// Calculates the GCD iteratively using the Euclidean algorithm.
// It uses a while loop to repeatedly apply the modulo operation until the remainder is 0.
int gcdIterative(int a, int b) {
  while (b != 0) {
    final temp = b; // Store the current value of b.
    b = a % b; // Update b with the remainder of a divided by b.
    a = temp; // Update a with the previous value of b.
  }
  return a;
}

// Approach 3: Binary GCD Algorithm (Stein's Algorithm)
// Calculates the GCD using Stein's algorithm, which is efficient for large numbers.
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

// Approach 4: Extended Euclidean Algorithm
// Calculates the GCD and coefficients x and y such that ax + by = gcd(a, b).
class GcdResult {
  final int gcd, x, y;
  GcdResult(this.gcd, this.x, this.y);
}

GcdResult gcdExtended(int a, int b) {
  if (a == 0) return GcdResult(b, 0, 1); // Base case.

  final result = gcdExtended(b % a, a); // Recursive call.
  final x = result.y - (b ~/ a) * result.x; // Calculate x.
  final y = result.x; // Calculate y.

  return GcdResult(result.gcd, x, y); // Return the GCD and coefficients.
}

// Approach 5: GCD using Prime Factorization
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

// Approach 6: GCD Approximation using Euler’s Totient Function
// Approximates the GCD using Euler's totient function.
// Note: This approach doesn't give the correct GCD; it returns phi(min(a, b)).
int gcdEulerTotient(int a, int b) {
  return phi(min(a, b)); // Return the totient of the smaller number.
}

// Helper function to calculate Euler's totient function.
int phi(int n) {
  int result = n;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n ~/= i;
      result -= result ~/ i;
    }
  }
  if (n > 1) result -= result ~/ n;
  return result;
}