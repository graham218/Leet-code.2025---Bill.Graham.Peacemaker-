/**
 * Math & Geometry: Sieve of Eratosthenes (Prime Numbers)
 * ------------------------------------------------------
 * The Sieve of Eratosthenes is an ancient algorithm for finding all prime numbers up to any given integer.
 *
 * Problem:
 * Given an integer 'n', find all prime numbers less than or equal to 'n'.
 *
 * Input:
 * - n: An integer (n >= 2)
 *
 * Output:
 * - An array of prime numbers less than or equal to n.
 *
 * Approaches:
 * ----------------
 * 1.  Basic Sieve of Eratosthenes
 * 2.  Optimized Sieve (start marking from square of the number)
 * 3.  Sieve with Bitwise Operations (space optimization)
 * 4.  Segmented Sieve (for very large n)
 * 5.  Sieve with a Set (less efficient, for demonstration)
 *
 *
 * Example:
 * ----------
 * Input: 20
 * Output: [2, 3, 5, 7, 11, 13, 17, 19]
 *
 */

/**
 * 1. Basic Sieve of Eratosthenes
 * -----------------------------
 * - Create a boolean array `isPrime[n+1]` and initialize all entries as true.
 * - Start with p = 2 (the first prime number).
 * - Mark all multiples of p (starting from 2p) as false.
 * - Increment p to the next unmarked number (which is prime).
 * - Repeat until p*p > n.
 * - Collect all numbers i for which isPrime[i] is true.
 *
 * Time Complexity: O(n log log n)
 * Space Complexity: O(n)
 */
function sieveOfEratosthenesBasic(n) {
  if (n < 2) return [];

  const isPrime = new Array(n + 1).fill(true);
  isPrime[0] = isPrime[1] = false;

  for (let p = 2; p * p <= n; p++) {
    if (isPrime[p]) {
      for (let i = p * p; i <= n; i += p) {
        isPrime[i] = false;
      }
    }
  }

  const primes = [];
  for (let i = 2; i <= n; i++) {
    if (isPrime[i]) {
      primes.push(i);
    }
  }
  return primes;
}

/**
 * 2. Optimized Sieve of Eratosthenes
 * ---------------------------------
 * - Optimization: Start marking multiples of p from p*p instead of 2p.
 * - The smallest multiple of p that is greater than or equal to p*p is p*p.
 * - This optimization reduces the number of unnecessary iterations.
 *
 * Time Complexity: O(n log log n)
 * Space Complexity: O(n)
 */
function sieveOfEratosthenesOptimized(n) {
  if (n < 2) return [];

  const isPrime = new Array(n + 1).fill(true);
  isPrime[0] = isPrime[1] = false;

  for (let p = 2; p * p <= n; p++) {
    if (isPrime[p]) {
      for (let i = p * p; i <= n; i += p) { // Start from p*p
        isPrime[i] = false;
      }
    }
  }

  const primes = [];
  for (let i = 2; i <= n; i++) {
    if (isPrime[i]) {
      primes.push(i);
    }
  }
  return primes;
}

/**
 * 3. Sieve of Eratosthenes with Bitwise Operations
 * ----------------------------------------------
 * - Uses a bit array to store prime information, reducing space usage.
 * - Each bit represents the primality of a number.
 * - To get the primality of a number i, we check the i/8th byte, and the (i%8)th bit.
 *
 * Time Complexity: O(n log log n)
 * Space Complexity: O(n/8)  (More space-efficient)
 */
function sieveOfEratosthenesBitwise(n) {
  if (n < 2) return [];

  const size = Math.floor((n + 1) / 8) + 1; // Size in bytes
  const isPrime = new Uint8Array(size); // Use Uint8Array for byte-level access

  // Helper functions for bit manipulation
  const setBit = (arr, i) => {
    const byteIndex = Math.floor(i / 8);
    const bitIndex = i % 8;
    arr[byteIndex] |= (1 << bitIndex); // Set the bit to 1
  };

  const getBit = (arr, i) => {
    const byteIndex = Math.floor(i / 8);
    const bitIndex = i % 8;
    return (arr[byteIndex] & (1 << bitIndex)) !== 0; // Check if the bit is 1
  };

  // Initialize all bits to 1 (prime)
  for (let i = 0; i < size; i++) {
    isPrime[i] = 0xff; // Set all bits to 1 (255 in decimal)
  }

  setBit(isPrime, 0); // 0 is not prime
  setBit(isPrime, 1); // 1 is not prime

  for (let p = 2; p * p <= n; p++) {
    if (getBit(isPrime, p)) {
      for (let i = p * p; i <= n; i += p) {
        setBit(isPrime, i);
      }
    }
  }

  const primes = [];
  for (let i = 2; i <= n; i++) {
    if (getBit(isPrime, i)) {
      primes.push(i);
    }
  }
  return primes;
}

/**
 * 4. Segmented Sieve of Eratosthenes
 * ----------------------------------
 * - Useful for very large values of n where the basic sieve would require too much memory.
 * - Divides the range [0, n] into smaller segments.
 * - Computes primes for each segment separately.
 * - 1. Calculate primes for the range [0, sqrt(n)] using a basic sieve.
 * - 2. For each segment [low, high]:
 * -    - Create a boolean array `isPrime[high-low+1]`.
 * -    - Iterate through the primes found in step 1.
 * -    - Mark multiples of those primes within the current segment.
 * -    - Collect the primes from the segment.
 *
 * Time Complexity: O(n log log n)
 * Space Complexity: O(sqrt(n))  (Reduced memory footprint)
 */
function segmentedSieve(n) {
  if (n < 2) return [];

  const limit = Math.floor(Math.sqrt(n));
  const primesLimit = sieveOfEratosthenesBasic(limit); // Primes up to sqrt(n)

  const segmentSize = 100000; // Adjust segment size as needed
  let low = limit + 1;
  let high = low + segmentSize - 1;

  const primes = [...primesLimit]; // Start with primes <= sqrt(n)

  while (low <= n) {
    if (high > n) high = n;

    const isPrime = new Array(high - low + 1).fill(true);

    for (const p of primesLimit) {
      const firstMultiple = Math.ceil(low / p) * p;
      let i = firstMultiple - low;
      for (; i <= high - low; i += p) {
        isPrime[i] = false;
      }
    }

    for (let i = 0; i <= high - low; i++) {
      if (isPrime[i]) {
        primes.push(low + i);
      }
    }

    low = high + 1;
    high = low + segmentSize - 1;
  }
  return primes;
}


/**
 * 5. Sieve of Eratosthenes with a Set
 * ----------------------------------
 * - Uses a Set to keep track of non-prime numbers.
 * - Not as efficient as the array-based approaches, but demonstrates an alternative.
 * - Initialize a Set with numbers from 2 to n.
 * - Iterate from 2 to sqrt(n).
 * - For each prime number p, remove its multiples from the Set.
 * - The remaining numbers in the Set are the primes.
 *
 * Time Complexity: O(n log log n) - but with higher constant factors due to Set operations.
 * Space Complexity: O(n)
 */
function sieveOfEratosthenesWithSet(n) {
  if (n < 2) return [];

  const numbers = new Set();
  for (let i = 2; i <= n; i++) {
    numbers.add(i);
  }

  for (let p = 2; p * p <= n; p++) {
    if (numbers.has(p)) {
      for (let i = p * p; i <= n; i += p) {
        numbers.delete(i);
      }
    }
  }

  return Array.from(numbers);
}



// Example Usage and Output
const n = 20;

console.log(`\nSieve of Eratosthenes (n = ${n})`);
console.log("----------------------------------");

console.log("\n1. Basic Sieve:");
console.log(sieveOfEratosthenesBasic(n));

console.log("\n2. Optimized Sieve:");
console.log(sieveOfEratosthenesOptimized(n));

console.log("\n3. Bitwise Sieve:");
console.log(sieveOfEratosthenesBitwise(n));

console.log("\n4. Segmented Sieve:");
console.log(segmentedSieve(n));

console.log("\n5. Sieve with Set:");
console.log(sieveOfEratosthenesWithSet(n));
