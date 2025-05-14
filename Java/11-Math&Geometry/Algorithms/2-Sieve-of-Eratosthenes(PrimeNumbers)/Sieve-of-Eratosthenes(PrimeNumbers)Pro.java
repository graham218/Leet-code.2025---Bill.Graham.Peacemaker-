import java.util.ArrayList;
import java.util.Arrays;
import java.util.BitSet;
import java.util.List;

public class SieveOfEratosthenes {

    /**
     * 1. Basic Sieve of Eratosthenes Algorithm
     *
     * * Finds all prime numbers up to a given limit.
     * * Uses a boolean array to mark numbers as prime or composite.
     * * Starts with 2, and iteratively marks multiples of each prime number as composite.
     *
     * Real-world application:
     * * Generating prime number tables for cryptographic applications (e.g., key generation in RSA).
     * * Used as a building block in more complex number theory algorithms.
     *
     * @param limit The upper limit for finding prime numbers.
     * @return A list of prime numbers up to the limit.
     */
    public static List<Integer> basicSieve(int limit) {
        // Handle edge cases
        if (limit < 2) {
            return new ArrayList<>();
        }

        // Create a boolean array "isPrime[i]" that will store true if i is prime
        boolean[] isPrime = new boolean[limit + 1];
        Arrays.fill(isPrime, true); // Assume all numbers are prime initially
        isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime

        // Iterate from 2 to the square root of the limit
        for (int p = 2; p * p <= limit; p++) {
            // If p is prime, then mark all multiples of p as composite
            if (isPrime[p]) {
                for (int i = p * p; i <= limit; i += p) {
                    isPrime[i] = false;
                }
            }
        }

        // Collect all prime numbers
        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= limit; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
        }
        return primes;
    }

    /**
     * 2. Sieve with Optimized Space using BitSet
     *
     * * Improves space efficiency by using a BitSet instead of a boolean array.
     * * A BitSet stores each boolean value using a single bit, reducing memory usage.
     * * Useful when dealing with very large limits.
     *
     * Real-world application:
     * * Large-scale prime number calculations in research projects (e.g., distribution of primes).
     * * Memory-constrained environments where finding primes is necessary.
     *
     * @param limit The upper limit for finding prime numbers.
     * @return A list of prime numbers up to the limit.
     */
    public static List<Integer> optimizedSpaceSieve(int limit) {
        // Handle edge cases
        if (limit < 2) {
            return new ArrayList<>();
        }

        // Use BitSet to store prime numbers (more space-efficient)
        BitSet isPrime = new BitSet(limit + 1);
        isPrime.set(2, limit + 1); // Initially set all bits from 2 to limit as true
        isPrime.clear(0); // 0 is not prime
        isPrime.clear(1); // 1 is not prime

        // Iterate from 2 to the square root of the limit
        for (int p = 2; p * p <= limit; p++) {
            // If p is prime, then mark all multiples of p as composite
            if (isPrime.get(p)) {
                for (int i = p * p; i <= limit; i += p) {
                    isPrime.clear(i);
                }
            }
        }

        // Collect all prime numbers
        List<Integer> primes = new ArrayList<>();
        for (int i = 2; i <= limit; i++) {
            if (isPrime.get(i)) {
                primes.add(i);
            }
        }
        return primes;
    }


    /**
     * 3. Sieve with Wheel Factorization (Wheel 6)
     *
     * * Further optimizes the Sieve by eliminating multiples of 2 and 3 upfront.
     * * Uses a "wheel" to skip unnecessary checks, improving performance.  Wheel 6 skips multiples of 2 and 3.
     * * The idea is that all primes greater than 3 are of the form 6k ± 1.
     *
     * Real-world application:
     * * High-performance prime number generation for specialized hardware.
     * * Optimizing prime number sieves in number theory research.
     *
     * @param limit The upper limit for finding prime numbers.
     * @return A list of prime numbers up to the limit.
     */
    public static List<Integer> wheelFactorizationSieve(int limit) {
        // Handle edge cases
        if (limit < 2) {
            return new ArrayList<>();
        }

        // Use BitSet for efficient storage
        BitSet isPrime = new BitSet(limit + 1);
        isPrime.set(2); // 2 is prime
        isPrime.set(3); // 3 is prime

        // Initialize primes of the form 6k+1 and 6k-1
        for (int i = 5; i <= limit; i += 6) {
            isPrime.set(i);     // 6k + 1
            if (i + 2 <= limit) {
                isPrime.set(i + 2); // 6k - 1
            }
        }
        // Optimized loop, starting from 5 and incrementing by 6.
        for (int p = 5; p * p <= limit; p += 6) {
            if (isPrime.get(p)) {
                for (int i = p * p; i <= limit; i += p) {
                    isPrime.clear(i);
                }
                for (int i = p * (p + 2); i <= limit; i += p) { //optimized for wheel 6
                    isPrime.clear(i);
                }
            }
            if (isPrime.get(p+2))
            {
                for (int i = (p+2) * (p+2); i <= limit; i += (p+2))
                {
                    isPrime.clear(i);
                }
                for (int i = (p+2) * (p + 4); i <= limit; i += (p+2)) { //optimized for wheel 6
                    isPrime.clear(i);
                }
            }
        }

        List<Integer> primes = new ArrayList<>();
        primes.add(2);
        primes.add(3);
        for (int i = 5; i <= limit; i++) {
            if (isPrime.get(i)) {
                primes.add(i);
            }
        }
        return primes;
    }

    /**
     * 4. Segmented Sieve of Eratosthenes
     *
     * * Divides the range [2, limit] into smaller segments to reduce memory usage.
     * * Useful when the limit is very large and the entire sieve array cannot fit in memory.
     * * First, find primes up to the square root of the limit.
     * * Then, process the remaining segments using those primes.
     *
     * Real-world application:
     * * Finding primes in extremely large ranges, such as in distributed computing.
     * * Applications where memory is a major constraint.
     *
     * @param limit The upper limit for finding prime numbers.
     * @return A list of prime numbers up to the limit.
     */
    public static List<Integer> segmentedSieve(int limit) {
        // Handle edge cases
        if (limit < 2) {
            return new ArrayList<>();
        }

        int segmentSize = (int) Math.sqrt(limit);
        List<Integer> primes = new ArrayList<>();

        // 1. Find primes up to the square root of the limit
        List<Integer> basePrimes = basicSieve(segmentSize);

        // 2. Process segments
        int low = segmentSize;
        int high = 2 * segmentSize;

        while (low < limit) {
            if (high > limit) {
                high = limit;
            }

            boolean[] isPrime = new boolean[segmentSize + 1]; // size of segment
            Arrays.fill(isPrime, true);

            // Use base primes to mark numbers in the current segment
            for (int prime : basePrimes) {
                int firstMultiple = (int) Math.ceil((double) low / prime) * prime;
                if(firstMultiple < low) firstMultiple += prime; // added this line
                for (int j = firstMultiple - low; j <= high - low; j += prime) {
                    isPrime[j] = false;
                }
            }

            // Collect primes from the current segment
            for (int i = 0; i <= high - low; i++) {
                if (isPrime[i]) {
                    primes.add(low + i);
                }
            }

            low = high;
            high += segmentSize;
        }
        //Add primes smaller than segment size.
        List<Integer> result = new ArrayList<>();
        for(int p: primes){
            if(p <= limit){
                result.add(p);
            }
        }
        return result;
    }

    /**
     * 5. Sieve of Atkin
     *
     * * A modern, faster algorithm for finding prime numbers up to a given limit.
     * * Uses a different approach than the Sieve of Eratosthenes.
     * * It's more complex but generally more efficient, especially for large limits.
     * * The algorithm marks numbers as prime if they satisfy certain quadratic equations.
     *
     * Real-world application:
     * * Cryptographic applications requiring very fast prime number generation.
     * * Number theory research and advanced prime number calculations.
     *
     * @param limit The upper limit for finding prime numbers.
     * @return A list of prime numbers up to the limit.
     */
    public static List<Integer> sieveOfAtkin(int limit) {
        // Handle edge cases
        if (limit < 2) {
            return new ArrayList<>();
        }

        // Initialize the result list
        List<Integer> primes = new ArrayList<>();

        // 1. Initialize a boolean array, initially all set to false.
        boolean[] isPrime = new boolean[limit + 1];

        // 2. Mark that 2 and 3 are prime
        if (limit > 2)
            isPrime[2] = true;
        if (limit > 3)
            isPrime[3] = true;

        // 3. Main loop to mark potential primes
        for (int x = 1; x * x <= limit; x++) {
            for (int y = 1; y * y <= limit; y++) {
                // n = (4 * x * x) + (y * y)
                int n = (4 * x * x) + (y * y);
                if (n <= limit && (n % 12 == 1 || n % 12 == 5))
                    isPrime[n] ^= true; // Toggle the bit

                // n = (3 * x * x) + (y * y)
                n = (3 * x * x) + (y * y);
                if (n <= limit && n % 12 == 7)
                    isPrime[n] ^= true;

                // n = (3 * x * x) - (y * y)
                n = (3 * x * x) - (y * y);
                if (x > y && n <= limit && n % 12 == 11)
                    isPrime[n] ^= true;
            }
        }

        // 4. Eliminate squares of primes
        for (int r = 5; r * r <= limit; r++) {
            if (isPrime[r]) {
                for (int i = r * r; i <= limit; i += r * r)
                    isPrime[i] = false;
            }
        }

        // 5. Collect the primes
        primes.add(2);
        primes.add(3);
        for (int i = 5; i <= limit; i++)
            if (isPrime[i])
                primes.add(i);
        return primes;
    }

    public static void main(String[] args) {
        int limit = 100;

        System.out.println("Basic Sieve:");
        System.out.println(basicSieve(limit));

        System.out.println("\nOptimized Space Sieve:");
        System.out.println(optimizedSpaceSieve(limit));

        System.out.println("\nWheel Factorization Sieve:");
        System.out.println(wheelFactorizationSieve(limit));

        System.out.println("\nSegmented Sieve:");
        System.out.println(segmentedSieve(limit));

        System.out.println("\nSieve of Atkin:");
        System.out.println(sieveOfAtkin(limit));
    }
}

