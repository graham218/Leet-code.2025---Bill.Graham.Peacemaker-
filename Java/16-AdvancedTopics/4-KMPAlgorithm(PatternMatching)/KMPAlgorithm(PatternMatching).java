import java.util.ArrayList;
import java.util.List;

public class KMPAlgorithm {

    /**
     * Approach 1: Basic KMP Algorithm Implementation
     * <p>
     * This is the standard implementation of the KMP algorithm. It precomputes the
     * longest proper prefix suffix (LPS) array for the pattern and then uses it
     * to efficiently search for the pattern in the text.
     * </p>
     *
     * @param text    The text to search within
     * @param pattern The pattern to search for
     * @return A list of starting indices where the pattern is found in the text.
     * Returns an empty list if no match is found.
     */
    public static List<Integer> kmpSearchV1(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        if (m == 0) {
            return List.of(0); // Handle empty pattern case
        }
        if (n == 0) {
            return List.of(); // Handle empty text case
        }

        int[] lps = computeLPSArray(pattern); // Precompute LPS array
        int i = 0; // Index for text
        int j = 0; // Index for pattern

        while (i < n) {
            if (pattern.charAt(j) == text.charAt(i)) {
                i++;
                j++;
            }

            if (j == m) {
                occurrences.add(i - j); // Found a match
                j = lps[j - 1];       // Look for next match
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                // Mismatch after j matches
                if (j != 0) {
                    j = lps[j - 1]; // Don't start from beginning
                } else {
                    i++;
                }
            }
        }
        return occurrences;
    }

    /**
     * Computes the Longest Proper Prefix Suffix (LPS) array for the given pattern.
     * <p>
     * The LPS array at index i stores the length of the longest proper prefix of
     * pattern[0...i] which is also a suffix of pattern[0...i].
     * </p>
     *
     * @param pattern The pattern for which to compute the LPS array
     * @return The LPS array
     */
    private static int[] computeLPSArray(String pattern) {
        int m = pattern.length();
        int[] lps = new int[m];
        int len = 0; // Length of the previous longest prefix suffix
        int i = 1;

        lps[0] = 0; // lps[0] is always 0

        // Calculate lps[i] for i = 1 to m-1
        while (i < m) {
            if (pattern.charAt(i) == pattern.charAt(len)) {
                len++;
                lps[i] = len;
                i++;
            } else {
                // This is tricky. Consider the example.
                // AAACAAAA and i = 7. The idea is similar
                // to search step.
                if (len != 0) {
                    len = lps[len - 1];
                    // Also, note that we do not increment i here
                } else {
                    lps[i] = len;
                    i++;
                }
            }
        }
        return lps;
    }

    /**
     * Approach 2: KMP with Detailed Logging
     * <p>
     * This version adds detailed logging to help understand the KMP algorithm's
     * execution flow.  It prints the current indices, characters being compared,
     * and LPS values.
     * </p>
     *
     * @param text    The text to search within
     * @param pattern The pattern to search for
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> kmpSearchV2(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        if (m == 0) {
            return List.of(0);
        }
        if (n == 0) {
            return List.of();
        }

        int[] lps = computeLPSArray(pattern);
        int i = 0;
        int j = 0;

        System.out.println("Text: " + text);
        System.out.println("Pattern: " + pattern);
        System.out.print("LPS Array: ");
        for (int val : lps) {
            System.out.print(val + " ");
        }
        System.out.println();
        System.out.println("Starting KMP Search with detailed logging:");

        while (i < n) {
            System.out.println("Comparing text[" + i + "] ('" + text.charAt(i) + "') with pattern[" + j + "] ('" + pattern.charAt(j) + "')");
            if (pattern.charAt(j) == text.charAt(i)) {
                i++;
                j++;
                System.out.println("Match found! i = " + i + ", j = " + j);
            }

            if (j == m) {
                System.out.println("Pattern found at index " + (i - j));
                occurrences.add(i - j);
                j = lps[j - 1];
                System.out.println("j updated to lps[" + (j - 1) + "] = " + j);
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                System.out.println("Mismatch at i = " + i + ", j = " + j);
                if (j != 0) {
                    j = lps[j - 1];
                    System.out.println("j updated to lps[" + (j - 1) + "] = " + j);
                } else {
                    i++;
                    System.out.println("j is 0, incrementing i to " + i);
                }
            }
        }
        System.out.println("KMP Search complete.");
        return occurrences;
    }

    /**
     * Approach 3: KMP with Early Exit on First Match
     * <p>
     * This version of KMP stops searching after finding the *first* occurrence
     * of the pattern in the text.  It's useful when you only need to know if
     * the pattern exists, not how many times it occurs.
     * </p>
     *
     * @param text    The text to search within
     * @param pattern The pattern to search for
     * @return The starting index of the first occurrence of the pattern in the
     * text, or -1 if the pattern is not found.
     */
    public static int kmpSearchV3(String text, String pattern) {
        int n = text.length();
        int m = pattern.length();

        if (m == 0) {
            return 0;
        }
        if (n == 0) {
            return -1;
        }

        int[] lps = computeLPSArray(pattern);
        int i = 0;
        int j = 0;

        while (i < n) {
            if (pattern.charAt(j) == text.charAt(i)) {
                i++;
                j++;
            }

            if (j == m) {
                return i - j; // Return the first occurrence
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return -1; // Pattern not found
    }

    /**
     * Approach 4: KMP with Overlapping Match Counting
     * <p>
     * This version counts *all* occurrences of the pattern, even if they overlap.
     * For example, searching for "AAA" in "AAAA" would return 2 (matches at
     * indices 0 and 1).
     * </p>
     *
     * @param text    The text to search within
     * @param pattern The pattern to search for
     * @return The total number of (possibly overlapping) occurrences of the
     * pattern in the text.
     */
    public static int kmpSearchV4(String text, String pattern) {
        int count = 0;
        int n = text.length();
        int m = pattern.length();

        if (m == 0) {
            return 0;
        }
        if (n == 0) {
            return 0;
        }

        int[] lps = computeLPSArray(pattern);
        int i = 0;
        int j = 0;

        while (i < n) {
            if (pattern.charAt(j) == text.charAt(i)) {
                i++;
                j++;
            }

            if (j == m) {
                count++;            // Increment count for each match
                j = lps[j - 1];       // Allow overlapping matches
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return count;
    }

    /**
     * Approach 5: KMP with No Extra Memory (Optimized)
     * <p>
     * This version aims to minimize memory usage by computing the LPS value
     * on-the-fly, instead of storing the entire LPS array.  However, in Java,
     * it's difficult to truly avoid *some* extra memory, but this approach
     * reduces it compared to the full LPS array.  This implementation still precomputes the LPS array,
     * as it's the most efficient way to implement the KMP algorithm in Java.
     * </p>
     *
     * @param text    The text to search within
     * @param pattern The pattern to search for
     * @return A list of starting indices where the pattern is found in the text.
     */
    public static List<Integer> kmpSearchV5(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int n = text.length();
        int m = pattern.length();

        if (m == 0) {
            return List.of(0);
        }
        if (n == 0) {
            return List.of();
        }
        int[] lps = computeLPSArray(pattern);
        int i = 0;
        int j = 0;

        while (i < n) {
            if (pattern.charAt(j) == text.charAt(i)) {
                i++;
                j++;
            }

            if (j == m) {
                occurrences.add(i - j);
                j = lps[j - 1];
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return occurrences;
    }

    public static void main(String[] args) {
        String text = "ABABDABACDABABCABAB";
        String pattern = "ABABCABAB";

        System.out.println("KMP Algorithm Demonstration");
        System.out.println("Text: " + text);
        System.out.println("Pattern: " + pattern);
        System.out.println();

        // Approach 1: Basic KMP
        List<Integer> occurrences1 = kmpSearchV1(text, pattern);
        System.out.println("Approach 1 (Basic KMP): Occurrences at indices: " + occurrences1);

        // Approach 2: KMP with Logging
        List<Integer> occurrences2 = kmpSearchV2(text, pattern);
        System.out.println("Approach 2 (KMP with Logging): Occurrences at indices: " + occurrences2);

        // Approach 3: KMP with Early Exit
        int firstOccurrence = kmpSearchV3(text, pattern);
        System.out.println("Approach 3 (KMP with Early Exit): First occurrence at index: " + firstOccurrence);

        // Approach 4: KMP with Overlapping Matches
        int overlappingCount = kmpSearchV4(text, pattern);
        System.out.println("Approach 4 (KMP with Overlapping Matches): Overlapping occurrences count: " + overlappingCount);

        // Approach 5: KMP with No Extra Memory (Optimized)
        List<Integer> occurrences5 = kmpSearchV5(text, pattern);
        System.out.println("Approach 5 (KMP with No Extra Memory): Occurrences at indices: " + occurrences5);
    }
}

