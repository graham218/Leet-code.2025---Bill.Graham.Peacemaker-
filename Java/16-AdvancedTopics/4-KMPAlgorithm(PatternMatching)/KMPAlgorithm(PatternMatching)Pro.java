import java.util.ArrayList;
import java.util.List;

public class KMP_Algorithm {

    /**
     * **1. Basic KMP Implementation (Substring Search)**
     *
     * * Finds all occurrences of a pattern string within a text string.
     * * Uses the standard KMP algorithm with a precomputed longest prefix suffix (LPS) array.
     * * Suitable for simple text search functionalities.
     *
     * @param text    The text string to search within.
     * @param pattern The pattern string to search for.
     * @return A list of starting indices of all occurrences of the pattern in the text.  Returns an empty list if no occurrences are found.
     */
    public static List<Integer> kmpSearch(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int[] lps = computeLPSArray(pattern); // Precompute the LPS array.
        int n = text.length();
        int m = pattern.length();
        int i = 0; // Index for text[]
        int j = 0; // Index for pattern[]

        while (i < n) {
            if (pattern.charAt(j) == text.charAt(i)) {
                j++;
                i++;
            }
            if (j == m) {
                occurrences.add(i - j); // Found a match, store the starting index.
                j = lps[j - 1];       // Look for the next possible match.
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                // Mismatch after j matches.
                if (j != 0) {
                    j = lps[j - 1]; // Don't start from the beginning of the pattern.
                } else {
                    i = i + 1;
                }
            }
        }
        return occurrences;
    }

    /**
     * Computes the Longest Prefix Suffix (LPS) array for a given pattern.
     * The LPS array is used to optimize the KMP search algorithm.
     *
     * @param pattern The pattern string.
     * @return The LPS array for the pattern.
     * lps[i] stores the length of the longest prefix of pattern[0...i]
     * that is also a suffix of pattern[0...i].
     */
    private static int[] computeLPSArray(String pattern) {
        int m = pattern.length();
        int[] lps = new int[m];
        int len = 0; // Length of the previous longest prefix suffix
        int i = 1;
        lps[0] = 0; // lps[0] is always 0

        // The loop calculates lps[i] for i = 1 to m-1
        while (i < m) {
            if (pattern.charAt(i) == pattern.charAt(len)) {
                len++;
                lps[i] = len;
                i++;
            } else { // (pattern[i] != pattern[len])
                if (len != 0) {
                    len = lps[len - 1]; // Also, note that here len = lps[len-1]
                    // This is tricky. Consider the example.
                    // AAACAAAA and i = 7. The idea is similar
                    // to search step.
                } else {
                    lps[i] = len;
                    i++;
                }
            }
        }
        return lps;
    }

    /**
     * **2. KMP for Counting Occurrences**
     *
     * * Counts the number of times a pattern appears in a text.
     * * A variation of the basic KMP to provide a count instead of indices.
     * * Useful for applications like counting word frequencies.
     *
     * @param text    The text string to search within.
     * @param pattern The pattern string to search for.
     * @return The number of times the pattern occurs in the text.
     */
    public static int kmpCountOccurrences(String text, String pattern) {
        int count = 0;
        int[] lps = computeLPSArray(pattern);
        int n = text.length();
        int m = pattern.length();
        int i = 0;
        int j = 0;

        while (i < n) {
            if (pattern.charAt(j) == text.charAt(i)) {
                j++;
                i++;
            }
            if (j == m) {
                count++;            // Increment count when a match is found.
                j = lps[j - 1];     // Overlapping occurrences are possible.
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i = i + 1;
                }
            }
        }
        return count;
    }

    /**
     * **3. KMP for Finding the First Occurrence**
     *
     * * Finds the starting index of the *first* occurrence of a pattern.
     * * Optimized to stop searching after the first match is found.
     * * Useful when you only need to know if a pattern exists and where it starts.
     *
     * @param text    The text string to search within.
     * @param pattern The pattern string to search for.
     * @return The starting index of the first occurrence of the pattern in the text,
     * or -1 if the pattern is not found.
     */
    public static int kmpFindFirstOccurrence(String text, String pattern) {
        int[] lps = computeLPSArray(pattern);
        int n = text.length();
        int m = pattern.length();
        int i = 0;
        int j = 0;

        while (i < n) {
            if (pattern.charAt(j) == text.charAt(i)) {
                j++;
                i++;
            }
            if (j == m) {
                return i - j; // Return the starting index of the first match.
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i = i + 1;
                }
            }
        }
        return -1; // Pattern not found.
    }

    /**
     * **4. KMP with Overlapping Pattern Matching**
     *
     * * Finds all occurrences of a pattern string within a text string, including overlapping occurrences.
     * * Uses the standard KMP algorithm with a precomputed longest prefix suffix (LPS) array.
     * * Differs from standard KMP by not skipping after a full match, thus capturing overlaps.
     * * Suitable for scenarios where overlapping patterns are significant.
     *
     * @param text    The text string to search within.
     * @param pattern The pattern string to search for.
     * @return A list of starting indices of all occurrences of the pattern in the text, including overlaps.
     */
    public static List<Integer> kmpSearchWithOverlapping(String text, String pattern) {
        List<Integer> occurrences = new ArrayList<>();
        int[] lps = computeLPSArray(pattern);
        int n = text.length();
        int m = pattern.length();
        int i = 0;
        int j = 0;

        while (i < n) {
            if (pattern.charAt(j) == text.charAt(i)) {
                j++;
                i++;
            }
            if (j == m) {
                occurrences.add(i - j);
                j = lps[j - 1];  // Key difference:  Don't jump past the overlap
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i = i + 1;
                }
            }
        }
        return occurrences;
    }

    /**
     * **5. KMP for Replacing Occurrences**
     *
     * * Replaces all occurrences of a pattern in a text with a replacement string.
     * * Extends KMP to modify the text based on pattern matches.
     * * Useful for text editing or data transformation tasks.
     *
     * @param text        The text string to search and replace within.
     * @param pattern     The pattern string to search for.
     * @param replacement The string to replace the pattern with.
     * @return A new string with all occurrences of the pattern replaced.
     */
    public static String kmpReplaceAll(String text, String pattern, String replacement) {
        StringBuilder result = new StringBuilder();
        int[] lps = computeLPSArray(pattern);
        int n = text.length();
        int m = pattern.length();
        int i = 0;
        int j = 0;

        while (i < n) {
            if (pattern.charAt(j) == text.charAt(i)) {
                j++;
                i++;
            }
            if (j == m) {
                result.append(replacement); // Append the replacement string.
                j = lps[j - 1];       // Continue searching for more occurrences.
            } else if (i < n && pattern.charAt(j) != text.charAt(i)) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    result.append(text.charAt(i)); // Append the unmatched character.
                    i++;
                }
            }
        }
        return result.toString();
    }

    public static void main(String[] args) {
        String text = "ABABDABACDABABCABAB";
        String pattern = "ABABCABAB";

        // 1. Basic KMP Search
        System.out.println("1. Basic KMP Search:");
        List<Integer> occurrences = kmpSearch(text, pattern);
        System.out.println("Occurrences at indices: " + occurrences); // Output: [10]

        // 2. KMP for Counting Occurrences
        System.out.println("\n2. KMP for Counting Occurrences:");
        int count = kmpCountOccurrences(text, pattern);
        System.out.println("Count: " + count); // Output: 1

        // 3. KMP for Finding the First Occurrence
        System.out.println("\n3. KMP for Finding the First Occurrence:");
        int firstOccurrence = kmpFindFirstOccurrence(text, pattern);
        System.out.println("First occurrence at index: " + firstOccurrence); // Output: 10

        // 4. KMP with Overlapping Pattern Matching
        System.out.println("\n4. KMP with Overlapping Pattern Matching:");
        List<Integer> overlappingOccurrences = kmpSearchWithOverlapping(text, pattern);
        System.out.println("Overlapping Occurrences at indices: " + overlappingOccurrences);

        // 5. KMP for Replacing Occurrences
        System.out.println("\n5. KMP for Replacing Occurrences:");
        String replacedText = kmpReplaceAll(text, pattern, "XYZ");
        System.out.println("Replaced text: " + replacedText); // Output: ABABDABACDXYZ
        String text2 = "AAAAA";
        String pattern2 = "AA";
        List<Integer> occurrences2 = kmpSearchWithOverlapping(text2, pattern2);
        System.out.println("\nOverlapping Occurrences in AAAAA for AA: " + occurrences2); //prints 0,1,2,3
    }
}

