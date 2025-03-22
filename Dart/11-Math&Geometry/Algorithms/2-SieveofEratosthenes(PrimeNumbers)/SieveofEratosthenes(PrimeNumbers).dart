// Dart program to generate prime numbers using 5 different approaches
import 'dart:math';

void main() {
  int n = 50;

  print("Prime numbers up to $n using different algorithms:");
  print("1. Basic Sieve of Eratosthenes: ${sieveOfEratosthenes(n)}");
  print("2. Optimized Sieve (Marking Multiples from Square): ${optimizedSieve(n)}");
  print("3. Segmented Sieve Algorithm: ${segmentedSieve(n)}");
  print("4. Bitwise Sieve of Eratosthenes: ${bitwiseSieve(n)}");
  print("5. Wheel Factorization Optimized Sieve: ${wheelFactorizationSieve(n)}");
}

// Approach 1: Basic Sieve of Eratosthenes
// Generates prime numbers up to n using the basic Sieve of Eratosthenes algorithm.
// It marks multiples of each prime number as non-prime.
List<int> sieveOfEratosthenes(int n) {
  List<bool> isPrime = List.filled(n + 1, true); // Initialize a boolean list to track prime numbers.
  isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime.

  for (int i = 2; i * i <= n; i++) { // Iterate up to the square root of n.
    if (isPrime[i]) { // If i is prime.
      for (int j = i * i; j <= n; j += i) { // Mark multiples of i as non-prime.
        isPrime[j] = false;
      }
    }
  }
  return [for (int i = 2; i <= n; i++) if (isPrime[i]) i]; // Collect the prime numbers.
}

// Approach 2: Optimized Sieve (Marking Multiples from Square Root)
// Generates prime numbers up to n using an optimized Sieve of Eratosthenes.
// It marks multiples starting from the square of each prime, reducing redundant operations.
List<int> optimizedSieve(int n) {
  List<bool> isPrime = List.filled(n + 1, true);
  isPrime[0] = isPrime[1] = false;

  for (int i = 2; i <= sqrt(n); i++) { // Iterate up to the square root of n.
    if (isPrime[i]) {
      for (int j = i * i; j <= n; j += i) { // Mark multiples of i starting from i * i.
        isPrime[j] = false;
      }
    }
  }
  return [for (int i = 2; i <= n; i++) if (isPrime[i]) i];
}

// Approach 3: Segmented Sieve Algorithm
// Generates prime numbers up to n using the segmented Sieve of Eratosthenes.
// It divides the range into segments to reduce memory usage.
List<int> segmentedSieve(int n) {
  int limit = sqrt(n).toInt() + 1; // Calculate the limit for the initial sieve.
  List<int> primes = sieveOfEratosthenes(limit); // Generate primes up to the limit.
  List<bool> isPrime = List.filled(n + 1, true); // Initialize the main sieve.

  for (int prime in primes) { // Iterate through the primes.
    int start = max(prime * prime, (n ~/ prime) * prime); // Calculate the starting point for marking multiples.
    for (int j = start; j <= n; j += prime) { // Mark multiples of the prime.
      isPrime[j] = false;
    }
  }
  return [for (int i = 2; i <= n; i++) if (isPrime[i]) i];
}

// Approach 4: Bitwise Sieve of Eratosthenes (Efficient Memory Usage)
// Generates prime numbers using a bitwise Sieve of Eratosthenes.
// It stores prime information using bits, significantly reducing memory usage.
List<int> bitwiseSieve(int n) {
  List<int> primes = [];
  List<int> sieve = List.filled((n >> 5) + 1, 0); // Initialize a bitwise sieve.

  for (int i = 2; i <= n; i++) {
    if ((sieve[i >> 5] & (1 << (i & 31))) == 0) { // Check if i is prime.
      primes.add(i);
      for (int j = i * i; j <= n; j += i) { // Mark multiples of i as non-prime.
        sieve[j >> 5] |= (1 << (j & 31)); // Set the corresponding bit to 1.
      }
    }
  }
  return primes;
}

// Approach 5: Wheel Factorization Optimized Sieve
// Generates prime numbers using a wheel factorization optimized Sieve of Eratosthenes.
// It uses a wheel to skip multiples of small primes, improving efficiency.
List<int> wheelFactorizationSieve(int n) {
  if (n < 2) return [];
  List<bool> isPrime = List.filled(n + 1, true);
  isPrime[0] = isPrime[1] = false;
  List<int> wheel = [2, 3, 5, 7]; // Initial wheel primes.

  for (int prime in wheel) {
    if (prime * prime > n) break;
    for (int j = prime * prime; j <= n; j += prime) { // Mark multiples of the primes in the wheel.
      isPrime[j] = false;
    }
  }
  return [for (int i = 2; i <= n; i++) if (isPrime[i]) i];
}