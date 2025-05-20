import java.util.ArrayList;
import java.util.List;

public class RabinKarp {

    // Prime number for hash calculation (common practice)
    private static final int PRIME = 101;

    // 1. Basic Rabin-Karp Algorithm
    //   - Computes hash for pattern and text substrings, compares hashes.
    //   - Handles hash collisions by character-by-character comparison.
    //   - Good for understanding the core concept.
    //   - Not the most efficient for very long texts or patterns due to potential collisions.
    /**
     * Basic Rabin-Karp algorithm for string matching.
     *
     * @param text    The text to search within.
     * @param pattern The pattern to search for.
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> basicRabinKarp(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        if (m > n) {
            return occurrences; // Pattern cannot be longer than text.
        }

        long patternHash = calculateHash(pattern);
        long textHash = calculateHash(text.substring(0, m));

        for (int i = 0; i <= n - m; i++) {
            if (patternHash == textHash) {
                // Check for actual match to avoid false positives due to hash collision
                if (text.substring(i, i + m).equals(pattern)) {
                    occurrences.add(i);
                }
            }
            if (i < n - m) {
                // Rolling hash: Remove the first character's hash, add the next character's hash.
                textHash = recalculateHash(text, i, i + m, textHash, m);
            }
        }
        return occurrences;
    }

    // 2. Rabin-Karp with Larger Prime
    //   - Uses a larger prime number to reduce hash collisions.
    //   - Improves the efficiency and accuracy compared to the basic version.
    //   - Suitable for scenarios where collision reduction is important.
    private static final int LARGE_PRIME = 33554393; // A large prime number
    /**
     * Rabin-Karp algorithm with a larger prime number to reduce collisions.
     *
     * @param text    The text to search within.
     * @param pattern The pattern to search for.
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> rabinKarpLargePrime(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        if (m > n) {
            return occurrences;
        }

        long patternHash = calculateHash(pattern, LARGE_PRIME);
        long textHash = calculateHash(text.substring(0, m), LARGE_PRIME);

        for (int i = 0; i <= n - m; i++) {
            if (patternHash == textHash) {
                if (text.substring(i, i + m).equals(pattern)) {
                    occurrences.add(i);
                }
            }
            if (i < n - m) {
                textHash = recalculateHash(text, i, i + m, textHash, m, LARGE_PRIME);
            }
        }
        return occurrences;
    }

    // 3. Rabin-Karp with Modulo and Larger Range
    //   - Uses modulo operator to keep hash values within a manageable range.
    //   - Helps prevent integer overflow issues with very long texts or patterns.
    //   - Essential for handling large input sizes efficiently.
    private static final long MOD = 1000000007; // Modulo value to prevent overflow

    /**
     * Rabin-Karp algorithm with modulo operator to prevent overflow.
     *
     * @param text    The text to search within.
     * @param pattern The pattern to search for.
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> rabinKarpWithModulo(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        if (m > n) {
            return occurrences;
        }

        long patternHash = calculateHashWithModulo(pattern);
        long textHash = calculateHashWithModulo(text.substring(0, m));
        long h = 1; // h is used to calculate the hash of the first character in the window

        for (int i = 0; i < m - 1; i++) {
            h = (h * PRIME) % MOD;
        }

        for (int i = 0; i <= n - m; i++) {
            if (patternHash == textHash) {
                if (text.substring(i, i + m).equals(pattern)) {
                    occurrences.add(i);
                }
            }
            if (i < n - m) {
                // Rolling hash with modulo
                textHash = (textHash - (text.charAt(i) * h) % MOD + MOD) % MOD; // Ensure positive
                textHash = (textHash * PRIME + text.charAt(i + m)) % MOD;
            }
        }
        return occurrences;
    }

    // 4. Optimized Rabin-Karp with Precomputed Powers
    //    - Precomputes the powers of the prime number to optimize hash recalculation.
    //    - Avoids redundant calculations in the rolling hash step.
    //    - Improves performance, especially for longer patterns.
    /**
     * Optimized Rabin-Karp algorithm with precomputed powers of the prime number.
     *
     * @param text    The text to search within.
     * @param pattern The pattern to search for.
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> optimizedRabinKarp(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        if (m > n) {
            return occurrences;
        }

        long patternHash = calculateHashWithModulo(pattern);
        long textHash = calculateHashWithModulo(text.substring(0, m));
        long[] primePowers = new long[m];  // Array to store powers of PRIME
        primePowers[0] = 1;
        for (int i = 1; i < m; i++) {
            primePowers[i] = (primePowers[i - 1] * PRIME) % MOD;
        }

        for (int i = 0; i <= n - m; i++) {
            if (patternHash == textHash) {
                if (text.substring(i, i + m).equals(pattern)) {
                    occurrences.add(i);
                }
            }
            if (i < n - m) {
                // Use precomputed powers for efficient rolling hash
                textHash = (textHash - (text.charAt(i) * primePowers[m - 1]) % MOD + MOD) % MOD;
                textHash = (textHash * PRIME + text.charAt(i + m)) % MOD;
            }
        }
        return occurrences;
    }

    // 5. Rabin-Karp with Multiple Hashes
    //    - Uses multiple hash functions to significantly reduce the probability of hash collisions.
    //    - Offers the highest level of accuracy, practically eliminating false positives.
    //    - Useful in critical applications where false positives are unacceptable.
    private static final int SECOND_PRIME = 103; // Second prime number for the second hash function

    /**
     * Rabin-Karp algorithm with multiple hash functions to minimize collisions.
     *
     * @param text    The text to search within.
     * @param pattern The pattern to search for.
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> rabinKarpMultipleHashes(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();
        if (m > n) {
            return occurrences;
        }

        long patternHash1 = calculateHashWithModulo(pattern, PRIME);
        long patternHash2 = calculateHashWithModulo(pattern, SECOND_PRIME);
        long textHash1 = calculateHashWithModulo(text.substring(0, m), PRIME);
        long textHash2 = calculateHashWithModulo(text.substring(0, m), SECOND_PRIME);

        long h1 = 1;
        long h2 = 1;
        for (int i = 0; i < m - 1; i++) {
            h1 = (h1 * PRIME) % MOD;
            h2 = (h2 * SECOND_PRIME) % MOD;
        }

        for (int i = 0; i <= n - m; i++) {
            if (patternHash1 == textHash1 && patternHash2 == textHash2) {
                if (text.substring(i, i + m).equals(pattern)) {
                    occurrences.add(i);
                }
            }
            if (i < n - m) {
                // Rolling hash for both hash functions
                textHash1 = (textHash1 - (text.charAt(i) * h1) % MOD + MOD) % MOD;
                textHash1 = (textHash1 * PRIME + text.charAt(i + m)) % MOD;

                textHash2 = (textHash2 - (text.charAt(i) * h2) % MOD + MOD) % MOD;
                textHash2 = (textHash2 * SECOND_PRIME + text.charAt(i + m)) % MOD;
            }
        }
        return occurrences;
    }
    // Helper function to calculate the hash value of a string.
    private static long calculateHash(String str) {
        long hash = 0;
        for (int i = 0; i < str.length(); i++) {
            hash = (hash * PRIME + str.charAt(i));
        }
        return hash;
    }
    // Helper function to calculate the hash value of a string, with a specified prime.

    private static long calculateHash(String str, int prime) {
        long hash = 0;
        for (int i = 0; i < str.length(); i++) {
            hash = (hash * prime + str.charAt(i));
        }
        return hash;
    }

    // Helper function to recalculate the hash value for the next substring.
    private static long recalculateHash(String text, int oldIndex, int newIndex, long oldHash, int patternLength) {
        long newHash = oldHash - text.charAt(oldIndex) * (long) Math.pow(PRIME, patternLength - 1);
        newHash = newHash * PRIME + text.charAt(newIndex);
        return newHash;
    }

    // Helper function to recalculate the hash value for the next substring, with a specified prime.
    private static long recalculateHash(String text, int oldIndex, int newIndex, long oldHash, int patternLength, int prime) {
        long newHash = oldHash - text.charAt(oldIndex) * (long) Math.pow(prime, patternLength - 1);
        newHash = newHash * prime + text.charAt(newIndex);
        return newHash;
    }

    // Helper function to calculate hash with modulo operation.
    private static long calculateHashWithModulo(String str) {
        long hash = 0;
        for (int i = 0; i < str.length(); i++) {
            hash = (hash * PRIME + str.charAt(i)) % MOD;
        }
        return hash;
    }

    // Helper function to calculate hash with modulo operation and specified prime.
    private static long calculateHashWithModulo(String str, int prime) {
        long hash = 0;
        for (int i = 0; i < str.length(); i++) {
            hash = (hash * prime + str.charAt(i)) % MOD;
        }
        return hash;
    }

    public static void main(String[] args) {
        String text = "ABABDABACDABABCABAB";
        String pattern = "ABABC";

        System.out.println("Text: " + text);
        System.out.println("Pattern: " + pattern);
        System.out.println();

        // Basic Rabin-Karp
        List<Integer> basicOccurrences = basicRabinKarp(text, pattern);
        System.out.println("Basic Rabin-Karp: " + basicOccurrences);

        // Rabin-Karp with Larger Prime
        List<Integer> largePrimeOccurrences = rabinKarpLargePrime(text, pattern);
        System.out.println("Rabin-Karp with Larger Prime: " + largePrimeOccurrences);

        // Rabin-Karp with Modulo
        List<Integer> moduloOccurrences = rabinKarpWithModulo(text, pattern);
        System.out.println("Rabin-Karp with Modulo: " + moduloOccurrences);

        // Optimized Rabin-Karp
        List<Integer> optimizedOccurrences = optimizedRabinKarp(text, pattern);
        System.out.println("Optimized Rabin-Karp: " + optimizedOccurrences);

        // Rabin-Karp with Multiple Hashes
        List<Integer> multiHashOccurrences = rabinKarpMultipleHashes(text, pattern);
        System.out.println("Rabin-Karp with Multiple Hashes: " + multiHashOccurrences);
    }
}

