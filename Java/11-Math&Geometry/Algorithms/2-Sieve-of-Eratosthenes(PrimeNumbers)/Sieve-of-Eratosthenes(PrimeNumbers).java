import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class SieveOfEratosthenes {

    public static void main(String[] args) {
        int n = 50; // Find primes up to 50

        System.out.println("Sieve of Eratosthenes - Approach 1: Basic Implementation");
        List<Integer> primes1 = sieveOfEratosthenesBasic(n);
        System.out.println(primes1);

        System.out.println("\nSieve of Eratosthenes - Approach 2: Optimized with Square Root");
        List<Integer> primes2 = sieveOfEratosthenesOptimized(n);
        System.out.println(primes2);

        System.out.println("\nSieve of Eratosthenes - Approach 3: Using Boolean Array");
        List<Integer> primes3 = sieveOfEratosthenesBooleanArray(n);
        System.out.println(primes3);

        System.out.println("\nSieve of Eratosthenes - Approach 4: Bitwise Optimization");
        List<Integer> primes4 = sieveOfEratosthenesBitwise(n);
        System.out.println(primes4);

        System.out.println("\nSieve of Eratosthenes - Approach 5: Using ArrayList as Sieve");
        List<Integer> primes5 = sieveOfEratosthenesListSieve(n);
        System.out.println(primes5);
    }

    // Approach 1: Basic Implementation
    // Finds all prime numbers up to a given limit n.
    // It iterates through numbers from 2 to n, and for each number, it checks if it's prime
    // by dividing it by all smaller numbers. If a number is prime, it's added to the result list.
    // Time Complexity: O(n^2) -  because of the nested loop.
    // Space Complexity: O(n) -  to store the primes in the worst case.
    public static List<Integer> sieveOfEratosthenesBasic(int n) {
        List<Integer> primes = new ArrayList<>();
        if (n < 2) {
            return primes; // No primes less than 2
        }

        for (int i = 2; i <= n; i++) {
            boolean isPrime = true;
            for (int j = 2; j < i; j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                primes.add(i);
            }
        }
        return primes;
    }

    // Approach 2: Optimized with Square Root
    // An optimization of the basic approach.  Instead of checking divisibility up to i,
    // it only checks up to the square root of i.  If a number i is not prime, it can be
    // factored into two numbers, at least one of which is <= sqrt(i).
    // Time Complexity: O(n * sqrt(n)) - Improved, but still not the most efficient.
    // Space Complexity: O(n) - To store the primes.
    public static List<Integer> sieveOfEratosthenesOptimized(int n) {
        List<Integer> primes = new ArrayList<>();
        if (n < 2) {
            return primes;
        }

        for (int i = 2; i <= n; i++) {
            boolean isPrime = true;
            for (int j = 2; j <= Math.sqrt(i); j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                primes.add(i);
            }
        }
        return primes;
    }

    // Approach 3: Using Boolean Array (Standard Sieve of Eratosthenes)
    // The classic implementation of the Sieve of Eratosthenes.
    // It creates a boolean array, initially marking all numbers as potentially prime.
    // Then, it iterates through the array, starting from 2.  If a number is marked as prime,
    // it marks all of its multiples as not prime.
    // Time Complexity: O(n log log n) -  The most efficient time complexity for this problem.
    // Space Complexity: O(n) -  for the boolean array.
    public static List<Integer> sieveOfEratosthenesBooleanArray(int n) {
        List<Integer> primes = new ArrayList<>();
        if (n < 2) {
            return primes;
        }

        boolean[] isPrime = new boolean[n + 1];
        Arrays.fill(isPrime, true); // Assume all numbers are prime initially

        isPrime[0] = isPrime[1] = false; // 0 and 1 are not prime

        for (int p = 2; p * p <= n; p++) {
            // If p is prime, mark all multiples of p as not prime
            if (isPrime[p]) {
                for (int i = p * p; i <= n; i += p) {
                    isPrime[i] = false;
                }
            }
        }

        // Collect the prime numbers
        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) {
                primes.add(i);
            }
        }
        return primes;
    }

    // Approach 4: Bitwise Optimization
    // Further optimization of the boolean array approach.  Instead of using a boolean array,
    // which uses 1 byte per element, it uses an integer array where each bit represents the
    // primality of a number.  This significantly reduces the space usage.
    // Time Complexity: O(n log log n) - Same as the standard Sieve.
    // Space Complexity: O(n/32) -  Significantly reduced due to bitwise operations.  Each integer can store 32 boolean values.
    public static List<Integer> sieveOfEratosthenesBitwise(int n) {
        List<Integer> primes = new ArrayList<>();
        if (n < 2) {
            return primes;
        }

        int[] isPrime = new int[(n / 32) + 1]; // Each int represents 32 numbers
        // (n/32) + 1  is the number of 32-bit integers needed to represent numbers up to n.

        // Function to set the bit representing the primality of a number
        // (num >> 5)  is equivalent to num / 32, determining the index of the integer in the isPrime array.
        // (1 << (num & 31)) creates a bitmask with a 1 at the position corresponding to num % 32,
        //  which is the bit position within that integer.
        //  The | operator sets that specific bit to 1, marking the number as prime.
        definePrime(isPrime, 2); // 2 is prime

        for (int p = 3; p <= n; p += 2) {
            if (isPrimeBit(isPrime, p)) {
                for (int i = p * p; i <= n; i += 2 * p) {
                    clearBit(isPrime, i); // Mark multiples of p as not prime
                }
            }
        }

        primes.add(2); // Add 2 to the result

        for (int i = 3; i <= n; i += 2) {
            if (isPrimeBit(isPrime, i)) {
                primes.add(i);
            }
        }
        return primes;
    }

    // Helper function to set a number as prime (set its corresponding bit)
    private static void definePrime(int[] isPrime, int num) {
        isPrime[num >> 5] |= (1 << (num & 31));
    }

    // Helper function to clear a number (mark as not prime)
    private static void clearBit(int[] isPrime, int num) {
        isPrime[num >> 5] &= ~(1 << (num & 31));
    }

    // Helper function to check if a number is marked as prime
    private static boolean isPrimeBit(int[] isPrime, int num) {
        return (isPrime[num >> 5] & (1 << (num & 31))) != 0;
    }

    // Approach 5: Using ArrayList as Sieve
    // This approach uses an ArrayList to represent the sieve.  The ArrayList initially contains
    // the numbers from 2 to n.  Then, it iterates through the list, removing multiples of each prime number.
    // This method can be less efficient for very large n due to the overhead of ArrayList operations
    // (removing elements).
    // Time Complexity:  O(n^2) in the worst case, but can be closer to O(n log log n) in practice,
    //                   especially with optimizations.  Removing elements from an ArrayList is O(n).
    // Space Complexity: O(n) -  for the ArrayList.
    public static List<Integer> sieveOfEratosthenesListSieve(int n) {
        List<Integer> numbers = new ArrayList<>();
        List<Integer> primes = new ArrayList<>();

        if (n < 2) return primes;

        // Initialize the list with numbers from 2 to n
        for (int i = 2; i <= n; i++) {
            numbers.add(i);
        }

        int p = 0; // Index of the current prime number
        while (p < numbers.size()) {
            int prime = numbers.get(p);
            primes.add(prime);

            // Remove multiples of the current prime.  Iterate *backwards* through the list
            // to avoid index out of bounds exceptions when removing elements.
            for (int i = numbers.size() - 1; i >= p; i--) {
                if (numbers.get(i) % prime == 0) {
                    numbers.remove(i);
                }
            }
            // p stays the same because after removing elements, the next number
            // will shift to the current index.
        }
        return primes;
    }
}

