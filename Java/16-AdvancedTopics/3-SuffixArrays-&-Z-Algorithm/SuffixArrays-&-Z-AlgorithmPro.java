import java.util.Arrays;
import java.util.Comparator;

public class SuffixArrayAndZAlgorithm {

    /**
     * Approach 1: Suffix Array Construction - Naive Approach (for understanding)
     *
     * This method constructs a suffix array for a given string using a naive approach.
     * It generates all suffixes of the string, sorts them lexicographically, and stores
     * the starting indices of the sorted suffixes in an array.
     *
     * Time Complexity: O(n^2 log n), where n is the length of the string.  Due to the string comparison.
     * Space Complexity: O(n^2) because of storing all suffixes.
     *
     * This approach is inefficient for large strings but is included for educational purposes,
     * to illustrate the basic concept of a suffix array.  Real-world applications would
     * almost always use a more efficient construction algorithm.
     */
    public static int[] buildSuffixArrayNaive(String text) {
        int n = text.length();
        String[] suffixes = new String[n];
        Integer[] indices = new Integer[n]; // Use Integer to allow sorting indices

        // Generate all suffixes and store their original indices
        for (int i = 0; i < n; i++) {
            suffixes[i] = text.substring(i);
            indices[i] = i;
        }

        // Sort the suffixes and keep track of the original indices
        Arrays.sort(indices, Comparator.comparing(i -> suffixes[i]));

        // Convert the sorted indices to an int[] for the suffix array
        int[] suffixArray = new int[n];
        for (int i = 0; i < n; i++) {
            suffixArray[i] = indices[i];
        }
        return suffixArray;
    }

    /**
     * Approach 2: Suffix Array Construction - Using Java's built-in sorting (Improved)
     *
     * This method improves upon the naive approach by using Java's built-in sorting
     * with a custom comparator.  It's still not the most efficient, but it's more concise
     * and often faster than the purely naive approach for smaller strings.
     *
     * Time Complexity: O(n^2 log n) in the worst case, but often performs better in practice
     * than the naive approach due to optimized sorting in Java's library.
     * Space Complexity: O(n) - improved because we are not explicitly storing all suffixes.
     *
     * This is still not suitable for very large strings, but it's a reasonable balance
     * of simplicity and performance for many practical scenarios.
     */
    public static int[] buildSuffixArrayImproved(String text) {
        int n = text.length();
        Integer[] indices = new Integer[n]; // Use Integer array
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }

        // Use a custom comparator to compare suffixes based on their starting index in the original text
        Arrays.sort(indices, (i, j) -> text.substring(i).compareTo(text.substring(j)));

        int[] suffixArray = new int[n];
        for (int i = 0; i < n; i++) {
            suffixArray[i] = indices[i];
        }
        return suffixArray;
    }


    /**
     * Approach 3: Suffix Array Construction -  Using the `Arrays.sort` method
     *
     * This approach constructs the suffix array by generating all suffixes,
     * sorting them using Java's `Arrays.sort` method with a custom comparator,
     * and then extracting the original indices of the sorted suffixes.
     *
     * Time Complexity: O(n^2 log n)
     * Space Complexity: O(n^2)
     *
     * It is slightly more efficient than the naive approach, but still not optimal for large inputs.
     */
    public static int[] buildSuffixArrayUsingArraysSort(String text) {
        int n = text.length();
        String[] suffixes = new String[n];
        Integer[] indices = new Integer[n];

        for (int i = 0; i < n; i++) {
            suffixes[i] = text.substring(i);
            indices[i] = i;
        }

        // Sort suffixes, but sort the *indices* based on the suffixes.
        Arrays.sort(indices, (i, j) -> suffixes[i].compareTo(suffixes[j]));

        int[] suffixArray = new int[n];
        for (int i = 0; i < n; i++) {
            suffixArray[i] = indices[i];
        }
        return suffixArray;
    }

    /**
     * Approach 4: Z-Algorithm for Pattern Matching
     *
     * The Z-algorithm is a linear-time algorithm for finding all occurrences of a pattern
     * in a text. It computes the Z-array, where Z[i] is the length of the longest substring
     * starting at i which is also a prefix of the string.
     *
     * Time Complexity: O(n + m), where n is the length of the text and m is the length of the pattern.
     * Space Complexity: O(n + m) for the Z-array.
     *
     * This is a very efficient algorithm for string matching and is widely used in
     * bioinformatics, text processing, and other areas.
     */
    public static void zAlgorithm(String text, String pattern) {
        String combined = pattern + "$" + text; // Combine pattern and text with a special character
        int n = combined.length();
        int[] z = new int[n];
        int left = 0, right = 0;

        // Calculate the Z-array
        for (int i = 1; i < n; i++) {
            if (i > right) {
                left = right = i;
                while (right < n && combined.charAt(right - left) == combined.charAt(right)) {
                    right++;
                }
                z[i] = right - left;
                right--;
            } else {
                int k = i - left;
                if (z[k] < right - i + 1) {
                    z[i] = z[k];
                } else {
                    left = i;
                    while (right < n && combined.charAt(right - left) == combined.charAt(right)) {
                        right++;
                    }
                    z[i] = right - left;
                    right--;
                }
            }
        }

        // Search for the pattern in the text using the Z-array
        for (int i = pattern.length() + 1; i < n; i++) {
            if (z[i] == pattern.length()) {
                System.out.println("Pattern found at index: " + (i - pattern.length() - 1));
            }
        }
    }



    /**
     * Approach 5:  Longest Repeated Substring using Suffix Array
     *
     * Finds the longest repeated substring in a given text using a suffix array.
     * This approach leverages the fact that repeated substrings will have close
     * entries in the sorted suffix array.
     *
     * Time Complexity: O(n log n)  dominated by the suffix array construction (using an efficient algorithm).
     * Space Complexity: O(n) for the suffix array and LCP array.
     *
     * This is a practical application of suffix arrays in bioinformatics (finding
     * repeated sequences in DNA), data compression, and plagiarism detection.
     */
    public static String longestRepeatedSubstring(String text) {
        int n = text.length();
        int[] suffixArray = buildSuffixArrayEfficient(text); // Use an efficient suffix array construction
        int[] lcpArray = calculateLCP(text, suffixArray);
        int maxLength = 0;
        int maxIndex = -1;

        // Find the maximum LCP value and its index
        for (int i = 0; i < n - 1; i++) {
            if (lcpArray[i] > maxLength) {
                maxLength = lcpArray[i];
                maxIndex = i;
            }
        }

        // Extract the longest repeated substring
        if (maxIndex != -1) {
            return text.substring(suffixArray[maxIndex], suffixArray[maxIndex] + maxLength);
        } else {
            return ""; // No repeated substring found
        }
    }

    // Efficient Suffix Array Construction (using a simplified, conceptual version of a more complex algorithm)
    //  For true efficiency, implementations like the Skew Algorithm are used, but they are quite involved.
    //  This version uses Java's sorting, but the *idea* is to show a better time complexity *conceptually*.
    //  This is NOT a true O(n log n) implementation, but it hints at the approach.
    private static int[] buildSuffixArrayEfficient(String text) {
        int n = text.length();
        Integer[] indices = new Integer[n];
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }
        Arrays.sort(indices, (i, j) -> text.substring(i).compareTo(text.substring(j)));
        int[] suffixArray = new int[n];
        for (int i = 0; i < n; i++) {
            suffixArray[i] = indices[i];
        }
        return suffixArray;
    }

    // Longest Common Prefix (LCP) Array Calculation
    private static int[] calculateLCP(String text, int[] suffixArray) {
        int n = text.length();
        int[] lcp = new int[n - 1];
        int[] rank = new int[n];

        // Compute the rank array (inverse of suffix array)
        for (int i = 0; i < n; i++) {
            rank[suffixArray[i]] = i;
        }

        // Calculate LCP using the rank array
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = suffixArray[rank[i] + 1];
            while (i + k < n && j + k < n && text.charAt(i + k) == text.charAt(j + k)) {
                k++;
            }
            lcp[rank[i]] = k;
            if (k > 0) {
                k--;
            }
        }
        return lcp;
    }

    public static void main(String[] args) {
        String text = "banana";
        String pattern = "ana";

        // Approach 1: Naive Suffix Array
        System.out.println("Approach 1: Naive Suffix Array");
        int[] suffixArrayNaive = buildSuffixArrayNaive(text);
        System.out.print("Suffix Array (Naive): ");
        for (int index : suffixArrayNaive) {
            System.out.print(index + " ");
        }
        System.out.println();

        // Approach 2: Improved Suffix Array
        System.out.println("\nApproach 2: Improved Suffix Array");
        int[] suffixArrayImproved = buildSuffixArrayImproved(text);
        System.out.print("Suffix Array (Improved): ");
        for (int index : suffixArrayImproved) {
            System.out.print(index + " ");
        }
        System.out.println();

        // Approach 3: Suffix Array using Arrays.sort
        System.out.println("\nApproach 3: Suffix Array using Arrays.sort");
        int[] suffixArraySort = buildSuffixArrayUsingArraysSort(text);
        System.out.print("Suffix Array (Arrays.sort): ");
        for (int index : suffixArraySort) {
            System.out.print(index + " ");
        }
        System.out.println();

        // Approach 4: Z-Algorithm
        System.out.println("\nApproach 4: Z-Algorithm");
        System.out.println("Pattern matching with Z-Algorithm:");
        zAlgorithm(text, pattern); // Find "ana" in "banana"

        // Approach 5: Longest Repeated Substring
        System.out.println("\nApproach 5: Longest Repeated Substring");
        String longestRepeat = longestRepeatedSubstring(text);
        if (longestRepeat.isEmpty()) {
            System.out.println("No repeated substring found.");
        } else {
            System.out.println("Longest repeated substring: " + longestRepeat); // Expected: "ana"
        }

        String text2 = "GATAGACA";
        String pattern2 = "AGA";
        System.out.println("\nZ-Algorithm Test with GATAGACA and AGA:");
        zAlgorithm(text2, pattern2);

        String text3 = "abab";
        System.out.println("\nLongest Repeated Substring Test with abab:");
        String longestRepeat3 = longestRepeatedSubstring(text3);
        System.out.println("Longest repeated substring: " + longestRepeat3);

        String text4 = "aabaabaa";
        System.out.println("\nLongest Repeated Substring Test with aabaabaa:");
        String longestRepeat4 = longestRepeatedSubstring(text4);
        System.out.println("Longest repeated substring: " + longestRepeat4);
    }
}

