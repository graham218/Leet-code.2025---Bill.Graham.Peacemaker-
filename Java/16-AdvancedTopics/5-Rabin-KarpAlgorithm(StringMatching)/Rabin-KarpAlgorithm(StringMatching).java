import java.util.ArrayList;
import java.util.List;

public class RabinKarp {

    // Prime number for hashing
    private static final int PRIME = 101;

    /**
     * Approach 1: Basic Rabin-Karp with single hash and modulo.
     * This method calculates the hash value for the pattern and the text substring,
     * and compares them.  It's the most straightforward implementation.
     *
     * @param text    The text string to search within.
     * @param pattern The pattern string to search for.
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> rabinKarpBasic(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        if (m > n) {
            return occurrences; // Pattern cannot be longer than text.
        }

        long patternHash = calculateHash(pattern);
        long textHash = calculateHash(text.substring(0, m));

        // Precompute the value of PRIME^(m-1) for efficient rolling hash calculation
        long h = 1;
        for (int i = 0; i < m - 1; i++) {
            h = (h * PRIME) ;
        }

        // Slide the window through the text
        for (int i = 0; i <= n - m; i++) {
            // Check if the hash values match
            if (patternHash == textHash) {
                // Verify character by character to avoid spurious hits (collisions)
                if (text.substring(i, i + m).equals(pattern)) {
                    occurrences.add(i);
                }
            }

            // Calculate the hash value for the next window of text.
            if (i < n - m) {
                textHash = (textHash - text.charAt(i) * h) ; // Remove the first character's hash
                textHash = (textHash * PRIME + text.charAt(i + m)) ; // Add the next character's hash
            }
        }
        return occurrences;
    }

    /**
     * Approach 2: Rabin-Karp with a larger prime number.
     * Uses a larger prime to reduce the probability of hash collisions.
     *
     * @param text    The text string to search within.
     * @param pattern The pattern string to search for.
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> rabinKarpLargePrime(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();
        final int LARGE_PRIME = 33554393; // A larger prime number

        if (m > n) {
            return occurrences;
        }

        long patternHash = calculateHash(pattern, LARGE_PRIME);
        long textHash = calculateHash(text.substring(0, m), LARGE_PRIME);

        long h = 1;
        for (int i = 0; i < m - 1; i++) {
            h = (h * PRIME) % LARGE_PRIME;
        }

        for (int i = 0; i <= n - m; i++) {
            if (patternHash == textHash) {
                if (text.substring(i, i + m).equals(pattern)) {
                    occurrences.add(i);
                }
            }
            if (i < n - m) {
                textHash = (textHash - (text.charAt(i) * h) % LARGE_PRIME + LARGE_PRIME) % LARGE_PRIME; // handle negative
                textHash = (textHash * PRIME + text.charAt(i + m)) % LARGE_PRIME;
            }
        }
        return occurrences;
    }

    /**
     * Approach 3: Rabin-Karp with double hashing.
     * Uses two different prime numbers to calculate two hash values.
     * This significantly reduces the chance of collision.
     *
     * @param text    The text string to search within.
     * @param pattern The pattern string to search for.
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> rabinKarpDoubleHash(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();
        final int PRIME2 = 3571; // Second prime number

        if (m > n) {
            return occurrences;
        }

        long patternHash1 = calculateHash(pattern, PRIME);
        long patternHash2 = calculateHash(pattern, PRIME2);
        long textHash1 = calculateHash(text.substring(0, m), PRIME);
        long textHash2 = calculateHash(text.substring(0, m), PRIME2);

        long h1 = 1;
        long h2 = 1;
        for (int i = 0; i < m - 1; i++) {
            h1 = (h1 * PRIME) ;
            h2 = (h2 * PRIME2) ;
        }

        for (int i = 0; i <= n - m; i++) {
            if (patternHash1 == textHash1 && patternHash2 == textHash2) {
                if (text.substring(i, i + m).equals(pattern)) {
                    occurrences.add(i);
                }
            }
            if (i < n - m) {
                textHash1 = (textHash1 - text.charAt(i) * h1) ;
                textHash1 = (textHash1 * PRIME + text.charAt(i + m)) ;

                textHash2 = (textHash2 - text.charAt(i) * h2) ;
                textHash2 = (textHash2 * PRIME2 + text.charAt(i + m)) ;
            }
        }
        return occurrences;
    }

    /**
     * Approach 4:  Using precomputed hashes for text substrings.
     * This approach precomputes the hash values for all possible substrings
     * of length m in the text, which can improve performance in some cases,
     * especially if the pattern is searched for multiple times.
     *
     * @param text    The text string to search within.
     * @param pattern The pattern string to search for.
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> rabinKarpPrecompute(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        if (m > n) {
            return occurrences;
        }

        long patternHash = calculateHash(pattern);
        long[] textHashes = new long[n - m + 1]; // Store hash values for all m-length substrings
        long h = 1;
        for (int i = 0; i < m - 1; i++) {
            h = (h * PRIME) ;
        }

        // Precompute hash values for all substrings of length m
        textHashes[0] = calculateHash(text.substring(0, m));
        for (int i = 1; i <= n - m; i++) {
            textHashes[i] = (textHashes[i - 1] - text.charAt(i - 1) * h) ;
            textHashes[i] = (textHashes[i] * PRIME + text.charAt(i + m - 1)) ;
        }

        // Search for the pattern
        for (int i = 0; i <= n - m; i++) {
            if (patternHash == textHashes[i]) {
                if (text.substring(i, i + m).equals(pattern)) {
                    occurrences.add(i);
                }
            }
        }
        return occurrences;
    }

    /**
     * Approach 5: Using Java's built-in String.indexOf() for comparison.
     * This is NOT the Rabin-Karp algorithm itself, but a simple approach for comparison.
     * It demonstrates the use of Java's built-in string matching for a sanity check and performance comparison.
     *
     * @param text    The text string to search within.
     * @param pattern The pattern string to search for.
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> rabinKarpIndexOf(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int index = text.indexOf(pattern);
        while (index >= 0) {
            occurrences.add(index);
            index = text.indexOf(pattern, index + 1); // Find the next occurrence
        }
        return occurrences;
    }
    /**
     * Helper function to calculate the hash value of a string.
     *
     * @param str The string for which to calculate the hash.
     * @return The hash value of the string.
     */
    private static long calculateHash(String str) {
        long hash = 0;
        for (int i = 0; i < str.length(); i++) {
            hash = (hash * PRIME + str.charAt(i));
        }
        return hash;
    }

    /**
     * Helper function to calculate the hash value of a string with a specified prime.
     * Allows using different prime numbers for double hashing.
     *
     * @param str   The string for which to calculate the hash.
     * @param prime The prime number to use in the hash calculation.
     * @return The hash value of the string.
     */
    private static long calculateHash(String str, int prime) {
        long hash = 0;
        for (int i = 0; i < str.length(); i++) {
            hash = (hash * prime + str.charAt(i)) % prime;
        }
        return hash;
    }

    public static void main(String[] args) {
        String text = "ABABDABACDABABCABAB";
        String pattern = "ABABC";

        System.out.println("Text: " + text);
        System.out.println("Pattern: " + pattern);
        System.out.println();

        // Approach 1: Basic Rabin-Karp
        List<Integer> occurrences1 = rabinKarpBasic(text, pattern);
        System.out.println("Approach 1 (Basic): " + occurrences1); // Expected: [10]

        // Approach 2: Rabin-Karp with a larger prime
        List<Integer> occurrences2 = rabinKarpLargePrime(text, pattern);
        System.out.println("Approach 2 (Large Prime): " + occurrences2); // Expected: [10]

        // Approach 3: Rabin-Karp with double hashing
        List<Integer> occurrences3 = rabinKarpDoubleHash(text, pattern);
        System.out.println("Approach 3 (Double Hash): " + occurrences3); // Expected: [10]

        // Approach 4: Rabin-Karp with precomputed hashes
        List<Integer> occurrences4 = rabinKarpPrecompute(text, pattern);
        System.out.println("Approach 4 (Precompute): " + occurrences4); // Expected: [10]

        // Approach 5: Using Java's String.indexOf()
        List<Integer> occurrences5 = rabinKarpIndexOf(text, pattern);
        System.out.println("Approach 5 (indexOf): " + occurrences5); // Expected: [10]
    }
}
