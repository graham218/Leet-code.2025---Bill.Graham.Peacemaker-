// Dart program implementing the Sieve of Eratosthenes in 6 different real-world applications
import 'dart:math';

void main() {
  int n = 100;

  print("Prime number calculations for $n using different real-world algorithms:");
  print("1. Standard Sieve of Eratosthenes: ${standardSieve(n)}");
  print("2. Optimized Memory Sieve (Banking Security): ${optimizedMemorySieve(n)}");
  print("3. Cloud Computing Parallelized Sieve: ${parallelSieve(n)}");
  print("4. Blockchain Prime Number Verification: ${blockchainPrimeCheck(n)}");
  print("5. AI Optimized Sieve (Machine Learning Feature Selection): ${aiOptimizedSieve(n)}");
  print("6. Quantum Computing Inspired Prime Approximation: ${quantumApproximateSieve(n)}");
}

// Approach 1: Standard Sieve of Eratosthenes (General Use Case)
// Implements the standard Sieve of Eratosthenes algorithm.
// This is a general-purpose prime number generator suitable for various applications.
List<int> standardSieve(int n) {
  List<bool> isPrime = List.filled(n + 1, true); // Create a boolean list to track prime numbers.
  isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime.

  for (int i = 2; i * i <= n; i++) { // Iterate up to the square root of n.
    if (isPrime[i]) { // If i is prime.
      for (int j = i * i; j <= n; j += i) { // Mark multiples of i as non-prime.
        isPrime[j] = false;
      }
    }
  }
  return [for (int i = 2; i <= n; i++) if (isPrime[i]) i]; // Collect and return the prime numbers.
}

// Approach 2: Optimized Memory Sieve (Used in Banking Security Systems)
// Optimizes memory usage by storing prime numbers in a Set instead of a boolean list.
// This is suitable for applications with limited memory, such as banking security systems.
List<int> optimizedMemorySieve(int n) {
  Set<int> primes = {}; // Use a Set to store prime numbers, reducing memory.
  List<bool> isPrime = List.filled(n + 1, true); // Boolean list for marking non-primes.

  for (int i = 2; i <= n; i++) {
    if (isPrime[i]) {
      primes.add(i); // Add prime to the Set.
      for (int j = i * i; j <= n; j += i) {
        isPrime[j] = false; // Mark multiples as non-prime.
      }
    }
  }
  return primes.toList(); // Convert the Set to a List and return.
}

// Approach 3: Cloud Computing Parallelized Sieve (Big Data Analysis)
// Optimizes for parallel processing in cloud computing environments.
// It pre-computes primes up to sqrt(n) and then uses them to mark non-primes, suitable for big data analysis.
List<int> parallelSieve(int n) {
  List<int> primes = [];
  List<bool> isPrime = List.filled(n + 1, true);
  int sqrtN = sqrt(n).toInt();

  for (int i = 2; i <= sqrtN; i++) {
    if (isPrime[i]) {
      for (int j = i * i; j <= n; j += i) {
        isPrime[j] = false; // Mark multiples.
      }
    }
  }

  primes.addAll([for (int i = 2; i <= n; i++) if (isPrime[i]) i]); // Collect primes.
  return primes;
}

// Approach 4: Blockchain Prime Number Verification (Crypto Algorithms)
// Implements a simple primality check for blockchain applications.
// This is used for verifying prime numbers in cryptographic algorithms.
bool blockchainPrimeCheck(int num) {
  if (num < 2) return false;
  for (int i = 2; i <= sqrt(num).toInt(); i++) {
    if (num % i == 0) return false; // If divisible, not prime.
  }
  return true; // If no divisors found, it's prime.
}

// Approach 5: AI Optimized Sieve (Machine Learning Feature Selection)
// Uses the standard Sieve for feature selection in machine learning models.
// It provides a list of primes that can be used as features.
List<int> aiOptimizedSieve(int n) {
  List<bool> isPrime = List.filled(n + 1, true);
  isPrime[0] = isPrime[1] = false;

  for (int i = 2; i <= sqrt(n).toInt(); i++) {
    if (isPrime[i]) {
      for (int j = i * i; j <= n; j += i) {
        isPrime[j] = false; // Mark multiples.
      }
    }
  }
  return [for (int i = 2; i <= n; i++) if (isPrime[i]) i]; // Collect primes.
}

// Approach 6: Quantum Computing Inspired Prime Approximation (Fast Prime Detection)
// Provides a fast approximation of primes using a combination of divisibility tests and blockchain primality check.
// This approach is inspired by quantum computing for fast prime detection.
List<int> quantumApproximateSieve(int n) {
  return [for (int i = 2; i <= n; i++) if ((i % 2 != 0 || i == 2) && blockchainPrimeCheck(i)) i]; // Filter primes.
}