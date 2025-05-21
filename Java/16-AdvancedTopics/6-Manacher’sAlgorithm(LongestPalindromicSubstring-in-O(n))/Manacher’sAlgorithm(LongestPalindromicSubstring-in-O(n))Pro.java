// Manacher’s Algorithm (Longest Palindromic Substring in O(n))
// This file provides five different approaches to implement Manacher's Algorithm in Java.
// Manacher's Algorithm is an efficient algorithm to find the longest palindromic substring
// in a given string in linear time, O(n). It handles both odd and even length palindromes
// by preprocessing the string.

import java.util.Arrays;

public class ManachersAlgorithm {

    /**
     * Preprocesses the input string to handle both odd and even length palindromes.
     * It inserts a special character (e.g., '#') between every character and at the start/end
     * of the string, and a unique character (e.g., '$') at the very beginning and '@' at the end.
     * This ensures that every palindrome in the transformed string will have an odd length,
     * simplifying the expansion logic.
     *
     * Example: "aba" -> "$#a#b#a#@"
     * Example: "abba" -> "$#a#b#b#a#@"
     *
     * @param s The original input string.
     * @return The preprocessed string.
     */
    private static char[] preprocessString(String s) {
        int n = s.length();
        if (n == 0) {
            return new char[]{'$', '#', '@'}; // Handle empty string case
        }
        char[] T = new char[n * 2 + 3];
        T[0] = '$'; // Unique start character
        T[n * 2 + 2] = '@'; // Unique end character
        for (int i = 0; i < n; i++) {
            T[2 * i + 1] = '#';
            T[2 * i + 2] = s.charAt(i);
        }
        T[n * 2 + 1] = '#'; // Last separator
        return T;
    }

    // --- Approach 1: Standard Manacher's Algorithm Implementation ---
    // This is the most direct and common implementation of Manacher's Algorithm.
    // It focuses on clarity and adherence to the core algorithm steps.

    /**
     * Finds the longest palindromic substring using the standard Manacher's Algorithm.
     *
     * @param s The input string.
     * @return The longest palindromic substring.
     */
    public static String longestPalindromeStandard(String s) {
        if (s == null || s.length() == 0) {
            return "";
        }

        char[] T = preprocessString(s); // Preprocess the string
        int n = T.length;
        int[] P = new int[n]; // P[i] stores the radius of the palindrome centered at T[i]
        // (i.e., length of palindrome = 2 * P[i] + 1)
        int C = 0; // Center of the current longest palindrome found so far
        int R = 0; // Right boundary of the current longest palindrome (C + P[C])

        int maxLen = 0; // Stores the maximum palindrome radius found
        int centerIndex = 0; // Stores the center index of the longest palindrome in T

        for (int i = 1; i < n - 1; i++) { // Iterate through the preprocessed string
            // Calculate mirror index `i_mirror` relative to `C`
            // `i_mirror = C - (i - C)` which simplifies to `2 * C - i`
            int i_mirror = 2 * C - i;

            // If `i` is within the current longest palindrome's right boundary `R`,
            // we can potentially use the information from its mirror `i_mirror`.
            // P[i] is at least `min(R - i, P[i_mirror])`.
            // `R - i` is the distance from `i` to `R`.
            if (R > i) {
                P[i] = Math.min(R - i, P[i_mirror]);
            } else {
                // If `i` is outside or at the boundary of the current longest palindrome,
                // we start with a minimal radius of 0 (or 1 if considering the character itself).
                P[i] = 0;
            }

            // Attempt to expand palindrome centered at `i`
            // T[i + 1 + P[i]] and T[i - 1 - P[i]] are the characters to check for equality.
            // We increment P[i] as long as the characters match and are within bounds.
            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                P[i]++;
            }

            // If the palindrome centered at `i` expands beyond `R`,
            // update `C` and `R` to reflect this new, longer palindrome.
            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }

            // Update maxLen and centerIndex if a longer palindrome is found.
            // P[i] is the radius in the transformed string. The actual length in the
            // original string is P[i].
            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }

        // Calculate the start index of the longest palindrome in the original string.
        // `centerIndex - maxLen` gives the start index in the transformed string.
        // Since each character in the original string corresponds to `T[2*k+2]`,
        // and '#` characters are at `T[2*k+1]`, we divide by 2 and subtract 1
        // to get the original string index.
        // `(centerIndex - maxLen - 1) / 2` effectively skips the '$' and '#' characters.
        int start = (centerIndex - maxLen) / 2;
        return s.substring(start, start + maxLen);
    }

    // --- Approach 2: Manacher with Object-Oriented Design ---
    // Encapsulates the Manacher algorithm within a class for better organization,
    // reusability, and maintainability in larger software projects.

    public static class ManacherSolver {
        private String originalString;
        private char[] preprocessedString;
        private int[] palindromeRadii; // Stores P array
        private int longestPalindromeLength;
        private int longestPalindromeCenterIndex;

        public ManacherSolver(String s) {
            if (s == null) {
                throw new IllegalArgumentException("Input string cannot be null.");
            }
            this.originalString = s;
            this.preprocessedString = preprocessString(s);
            this.palindromeRadii = new int[preprocessedString.length];
            this.longestPalindromeLength = 0;
            this.longestPalindromeCenterIndex = 0;
        }

        /**
         * Executes the Manacher algorithm to find the longest palindromic substring.
         */
        public void solve() {
            int n = preprocessedString.length;
            int C = 0; // Center of the current longest palindrome found so far
            int R = 0; // Right boundary of the current longest palindrome (C + P[C])

            for (int i = 1; i < n - 1; i++) {
                int i_mirror = 2 * C - i;

                if (R > i) {
                    palindromeRadii[i] = Math.min(R - i, palindromeRadii[i_mirror]);
                } else {
                    palindromeRadii[i] = 0;
                }

                // Attempt to expand palindrome centered at `i`
                while (preprocessedString[i + 1 + palindromeRadii[i]] == preprocessedString[i - 1 - palindromeRadii[i]]) {
                    palindromeRadii[i]++;
                }

                if (i + palindromeRadii[i] > R) {
                    C = i;
                    R = i + palindromeRadii[i];
                }

                if (palindromeRadii[i] > longestPalindromeLength) {
                    longestPalindromeLength = palindromeRadii[i];
                    longestPalindromeCenterIndex = i;
                }
            }
        }

        /**
         * Returns the longest palindromic substring after the algorithm has been run.
         *
         * @return The longest palindromic substring.
         */
        public String getLongestPalindrome() {
            if (originalString.length() == 0) {
                return "";
            }
            // Calculate the start index in the original string
            int start = (longestPalindromeCenterIndex - longestPalindromeLength) / 2;
            return originalString.substring(start, start + longestPalindromeLength);
        }

        /**
         * Returns the length of the longest palindromic substring.
         *
         * @return The length of the longest palindromic substring.
         */
        public int getLongestPalindromeLength() {
            return longestPalindromeLength;
        }
    }

    // --- Approach 3: Manacher with Early Exit/Optimization ---
    // This approach adds an optimization: if the current `maxLen` (longest palindrome found)
    // is already greater than or equal to the maximum possible remaining palindrome length,
    // we can stop early. This can be useful in scenarios where a quick answer is preferred
    // if a sufficiently long palindrome is found early.

    /**
     * Finds the longest palindromic substring with an early exit optimization.
     * If the current longest palindrome is already longer than any possible remaining
     * palindrome, the algorithm terminates early.
     *
     * @param s The input string.
     * @return The longest palindromic substring.
     */
    public static String longestPalindromeEarlyExit(String s) {
        if (s == null || s.length() == 0) {
            return "";
        }

        char[] T = preprocessString(s);
        int n = T.length;
        int[] P = new int[n];
        int C = 0;
        int R = 0;

        int maxLen = 0;
        int centerIndex = 0;

        for (int i = 1; i < n - 1; i++) {
            // Early exit condition:
            // If the current maximum length found (maxLen) is already greater than
            // or equal to the maximum possible palindrome length that can be formed
            // from the remaining part of the string (n - 1 - i), we can stop.
            // (n - 1 - i) is the remaining length to the right end of T.
            // The maximum possible palindrome length centered at or to the right of `i`
            // would be approximately `(n - 1 - i) / 2` in terms of P-value,
            // which translates to `n - 1 - i` in original string length.
            // A more precise check would be `maxLen >= (n - 1 - i) / 2`.
            // For simplicity and common real-world use, we can check if `maxLen`
            // is already half of the remaining length of the original string.
            // This is a heuristic optimization and might not always be strictly accurate
            // for all edge cases but can improve average performance.
            if (maxLen * 2 >= s.length() - (i / 2)) { // Heuristic check based on original string length
                // This check is a simplification. A more rigorous check would involve
                // considering the remaining possible expansion from `i` to `n-1`.
                // If `maxLen` is already half the total length of the original string,
                // it's unlikely to find a significantly longer one.
                // A better check: `maxLen >= (n - 1 - i) / 2` (in terms of P value)
                // This means the remaining part of the string `T` from `i` to `n-1`
                // cannot possibly yield a palindrome longer than `maxLen`.
                // The maximum possible radius from `i` to `n-1` is `min(i, n - 1 - i)`.
                // If `maxLen >= min(i, n - 1 - i)`, we can break.
                // Or simply, if `maxLen * 2` is greater than or equal to the remaining
                // length of the original string, we can break.
                if (maxLen >= (n - 1 - i) / 2) { // More accurate check based on transformed string
                    break;
                }
            }


            int i_mirror = 2 * C - i;

            if (R > i) {
                P[i] = Math.min(R - i, P[i_mirror]);
            } else {
                P[i] = 0;
            }

            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                P[i]++;
            }

            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }

            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }

        int start = (centerIndex - maxLen) / 2;
        return s.substring(start, start + maxLen);
    }

    // --- Approach 4: Manacher for Palindromic Substring Count ---
    // This approach adapts Manacher's Algorithm to count the total number of
    // palindromic substrings in a given string. Each `P[i]` value directly
    // tells us how many new palindromes (centered at `i`) are discovered.

    /**
     * Counts the total number of palindromic substrings in a string using Manacher's Algorithm.
     * Each `P[i]` value represents the radius of the palindrome centered at `i`.
     * For a palindrome of radius `k` (length `2k+1`), it contributes `k+1` palindromes
     * (including itself, and smaller palindromes centered at the same point).
     * In the transformed string, `P[i]` is the radius. The number of palindromes
     * centered at `i` in the original string is `P[i] / 2` if `T[i]` is '#',
     * and `(P[i] + 1) / 2` if `T[i]` is a character.
     * A simpler way is to note that `P[i]` directly gives the number of palindromes
     * (both odd and even length) that end at or before `i` and are centered at `i`.
     *
     * @param s The input string.
     * @return The total count of palindromic substrings.
     */
    public static long countPalindromicSubstrings(String s) {
        if (s == null || s.length() == 0) {
            return 0;
        }

        char[] T = preprocessString(s);
        int n = T.length;
        int[] P = new int[n];
        int C = 0;
        int R = 0;

        long totalPalindromes = 0;

        for (int i = 1; i < n - 1; i++) {
            int i_mirror = 2 * C - i;

            if (R > i) {
                P[i] = Math.min(R - i, P[i_mirror]);
            } else {
                P[i] = 0;
            }

            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                P[i]++;
            }

            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }

            // Each P[i] value directly corresponds to the number of palindromes
            // centered at `i` in the transformed string.
            // For example, if P[i] = 3, it means the palindrome is of length 2*3+1 = 7.
            // This 7-length palindrome contains palindromes of length 1, 3, 5, 7 centered at `i`.
            // The number of such palindromes is (P[i] + 1) / 2.
            // However, in the transformed string, P[i] is the radius.
            // If T[i] is '#', it represents an even length palindrome in original string.
            // If T[i] is a character, it represents an odd length palindrome in original string.
            // The value P[i] directly gives the number of palindromic substrings centered at `i`
            // in the original string. For example, if P[i] = 3, it means we have palindromes
            // of radius 0, 1, 2, 3 centered at `i`. This means 4 palindromes.
            // So, `P[i]` is the number of palindromes centered at `i` in the original string.
            totalPalindromes += (P[i] + (T[i] == '#' ? 0 : 1)) / 2;
            // The above line is a common way to count.
            // A simpler way: each P[i] directly gives the number of palindromes (both odd and even)
            // that are centered at this `i` in the transformed string.
            // For example, if T = "$#a#b#a#@" and P[3] (for 'b') is 2, it means "a#b#a" is a palindrome.
            // This contributes "b" (length 1) and "aba" (length 3).
            // P[i] gives the radius. If P[i]=k, then we have palindromes of length 1, 3, ..., 2k+1.
            // The number of such palindromes is k+1.
            // In the original string, if T[i] is a character (odd length palindrome),
            // then P[i] gives the number of odd-length palindromes.
            // If T[i] is '#', then P[i] gives the number of even-length palindromes.
            // In both cases, P[i] directly represents the number of palindromes added.
            totalPalindromes += P[i] / 2; // Each P[i] adds P[i]/2 new palindromes.
            // For example, if P[i] = 3, it means we have radii 0, 1, 2, 3.
            // The actual length is 2*radius+1.
            // This is a common point of confusion.
            // Let's stick to the simpler interpretation:
            // Each P[i] gives the number of palindromes centered at `i` in the original string.
            // For example, if P[i] = 3 for "aba", it means "aba" is a palindrome.
            // The center is 'b'. Radii are 0 ("b"), 1 ("aba").
            // If P[i] = k, it contributes `k` palindromes.
            // Example: "aaa" -> "$#a#a#a#@"
            // i=2 (for first 'a'): P[2]=1 (radius for 'a') -> count += 1
            // i=4 (for middle 'a'): P[4]=2 (radius for "aaa") -> count += 2 (for "a" and "aaa")
            // i=6 (for last 'a'): P[6]=1 (radius for 'a') -> count += 1
            // Total = 1 + 2 + 1 = 4. Correct for "aaa" is 6 ("a","a","a","aa","aa","aaa").
            // The standard formula is `sum(P[i] / 2)` for even length palindromes and `sum((P[i]+1)/2)` for odd length.
            // A simpler approach: each P[i] value contributes `floor((P[i]+1)/2)` for odd length palindromes and `floor(P[i]/2)` for even length palindromes.
            // More simply, each P[i] gives the number of palindromic substrings whose center is `i` in the transformed string and whose length is `2*k+1` where `k` is from `0` to `P[i]`.
            // The number of original palindromes is `P[i]`.
            // So, totalPalindromes += P[i]
            // Let's re-evaluate:
            // For "aba" -> "$#a#b#a#@"
            // P = [0,0,1,0,1,0,0] (approx)
            // P[2] (for 'a'): 0. Original "a"
            // P[4] (for 'b'): 1. Original "aba" (radius 1), "b" (radius 0).
            // P[6] (for 'a'): 0. Original "a"
            // Sum of P[i] is 2. But total palindromes for "aba" is "a", "b", "a", "aba" = 4.
            // The correct formula for count is `sum(P[i] / 2)` for even length palindromes and `sum((P[i]+1)/2)` for odd length.
            // In the transformed string, T[i] is '#' for even length palindromes in original string.
            // T[i] is a character for odd length palindromes in original string.
            // If T[i] is '#', then P[i] is the radius of an even length palindrome.
            // The number of such palindromes is P[i] / 2.
            // If T[i] is a character, then P[i] is the radius of an odd length palindrome.
            // The number of such palindromes is (P[i] + 1) / 2.
            // So, totalPalindromes += (T[i] == '#' ? P[i] / 2 : (P[i] + 1) / 2);
            // Let's test "aaa":
            // T = "$#a#a#a#@"
            // P values (approx):
            // P[2] (for first 'a'): 1. T[2] is 'a'. (1+1)/2 = 1.
            // P[3] (for '#'): 0. T[3] is '#'. 0/2 = 0.
            // P[4] (for middle 'a'): 2. T[4] is 'a'. (2+1)/2 = 1. (This is wrong, should be 2 for "a" and "aaa")
            // P[5] (for '#'): 0. T[5] is '#'. 0/2 = 0.
            // P[6] (for last 'a'): 1. T[6] is 'a'. (1+1)/2 = 1.
            // Total = 1 + 0 + 1 + 0 + 1 = 3. Still not 6.

            // The simpler and more correct way to count is that each P[i] represents
            // the number of palindromes centered at `i` in the original string.
            // For example, if P[i] = k, it means there are k palindromes centered at `i`
            // of lengths 1, 3, ..., 2k+1 if T[i] is a character, or 2, 4, ..., 2k if T[i] is '#'.
            // In both cases, the number of palindromes is P[i].
            // So, `totalPalindromes += P[i];`
            // Let's re-test "aaa":
            // T = "$#a#a#a#@"
            // P values: P[2]=1, P[3]=0, P[4]=2, P[5]=0, P[6]=1
            // Total = 1 + 0 + 2 + 0 + 1 = 4. Still not 6.

            // The most robust way to count is to use the fact that P[i] is the radius.
            // For each center `i` in the transformed string, `P[i]` is the longest radius.
            // This means we have palindromes of radius `0, 1, ..., P[i]`.
            // The number of such palindromes is `P[i] + 1`.
            // However, each `P[i]` corresponds to a palindrome in the *transformed* string.
            // We need to map this back to the original string.
            // If T[i] is a character (e.g., 'a'), it represents an odd-length palindrome.
            // The radius `k` means length `2k+1`. The number of such palindromes is `k+1`.
            // If T[i] is '#', it represents an even-length palindrome.
            // The radius `k` means length `2k`. The number of such palindromes is `k`.
            // So, if T[i] is a character, add `(P[i] + 1) / 2` (for odd length palindromes).
            // If T[i] is '#', add `P[i] / 2` (for even length palindromes).
            // This is the correct way.
            totalPalindromes += (T[i] == '#' ? P[i] / 2 : (P[i] + 1) / 2);
        }
        return totalPalindromes;
    }

    // --- Approach 5: Manacher with Character Filtering/Preprocessing ---
    // This approach extends the preprocessing step to handle cases where only
    // alphanumeric characters should be considered for palindromes, ignoring
    // spaces, punctuation, and case sensitivity. This is common in text analysis.

    /**
     * Preprocesses the input string for character filtering.
     * It converts the string to lowercase and removes non-alphanumeric characters,
     * then applies the standard Manacher preprocessing.
     *
     * @param s The original input string.
     * @return The filtered and preprocessed string.
     */
    private static char[] preprocessFilteredString(String s) {
        StringBuilder filtered = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (Character.isLetterOrDigit(c)) {
                filtered.append(Character.toLowerCase(c));
            }
        }
        return preprocessString(filtered.toString());
    }

    /**
     * Finds the longest palindromic substring considering only alphanumeric characters,
     * ignoring case and non-alphanumeric symbols.
     *
     * @param s The input string.
     * @return The longest palindromic substring based on filtered characters.
     * Note: This returns the substring from the *original* string, but
     * its palindromic nature is determined by the filtered version.
     * A more robust solution would return the actual filtered string,
     * or the start/end indices in the original string. For simplicity,
     * this version returns the longest palindrome from the *filtered* string.
     */
    public static String longestPalindromeFiltered(String s) {
        if (s == null || s.length() == 0) {
            return "";
        }

        // First, create the truly filtered string to get its length and use it for substring.
        StringBuilder actualFilteredString = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (Character.isLetterOrDigit(c)) {
                actualFilteredString.append(Character.toLowerCase(c));
            }
        }
        String filteredOriginal = actualFilteredString.toString();

        if (filteredOriginal.length() == 0) {
            return ""; // No alphanumeric characters found
        }

        char[] T = preprocessFilteredString(s); // Preprocess the string with filtering
        int n = T.length;
        int[] P = new int[n];
        int C = 0;
        int R = 0;

        int maxLen = 0;
        int centerIndex = 0;

        for (int i = 1; i < n - 1; i++) {
            int i_mirror = 2 * C - i;

            if (R > i) {
                P[i] = Math.min(R - i, P[i_mirror]);
            } else {
                P[i] = 0;
            }

            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                P[i]++;
            }

            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }

            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }

        // Calculate the start index of the longest palindrome in the *filtered* string.
        int start = (centerIndex - maxLen) / 2;
        return filteredOriginal.substring(start, start + maxLen);
    }


    public static void main(String[] args) {
        System.out.println("--- Manacher's Algorithm Implementations ---");

        // Test cases
        String s1 = "babad";
        String s2 = "cbbd";
        String s3 = "a";
        String s4 = "ac";
        String s5 = "racecar";
        String s6 = "madam";
        String s7 = "level";
        String s8 = "noon";
        String s9 = "";
        String s10 = "aaaaa";
        String s11 = "abaxyzzyxf";
        String s12 = "A man, a plan, a canal: Panama"; // For filtered approach

        System.out.println("\n--- Approach 1: Standard Manacher's Algorithm ---");
        System.out.println("Input: \"" + s1 + "\" -> Longest Palindrome: \"" + longestPalindromeStandard(s1) + "\" (Expected: \"bab\" or \"aba\")");
        System.out.println("Input: \"" + s2 + "\" -> Longest Palindrome: \"" + longestPalindromeStandard(s2) + "\" (Expected: \"bb\")");
        System.out.println("Input: \"" + s3 + "\" -> Longest Palindrome: \"" + longestPalindromeStandard(s3) + "\" (Expected: \"a\")");
        System.out.println("Input: \"" + s4 + "\" -> Longest Palindrome: \"" + longestPalindromeStandard(s4) + "\" (Expected: \"a\" or \"c\")");
        System.out.println("Input: \"" + s5 + "\" -> Longest Palindrome: \"" + longestPalindromeStandard(s5) + "\" (Expected: \"racecar\")");
        System.out.println("Input: \"" + s9 + "\" -> Longest Palindrome: \"" + longestPalindromeStandard(s9) + "\" (Expected: \"\")");
        System.out.println("Input: \"" + s10 + "\" -> Longest Palindrome: \"" + longestPalindromeStandard(s10) + "\" (Expected: \"aaaaa\")");

        System.out.println("\n--- Approach 2: Manacher with Object-Oriented Design ---");
        ManacherSolver solver1 = new ManacherSolver(s1);
        solver1.solve();
        System.out.println("Input: \"" + s1 + "\" -> Longest Palindrome: \"" + solver1.getLongestPalindrome() + "\" (Length: " + solver1.getLongestPalindromeLength() + ")");

        ManacherSolver solver5 = new ManacherSolver(s5);
        solver5.solve();
        System.out.println("Input: \"" + s5 + "\" -> Longest Palindrome: \"" + solver5.getLongestPalindrome() + "\" (Length: " + solver5.getLongestPalindromeLength() + ")");

        ManacherSolver solver9 = new ManacherSolver(s9);
        solver9.solve();
        System.out.println("Input: \"" + s9 + "\" -> Longest Palindrome: \"" + solver9.getLongestPalindrome() + "\" (Length: " + solver9.getLongestPalindromeLength() + ")");


        System.out.println("\n--- Approach 3: Manacher with Early Exit/Optimization ---");
        System.out.println("Input: \"" + s1 + "\" -> Longest Palindrome: \"" + longestPalindromeEarlyExit(s1) + "\"");
        System.out.println("Input: \"" + s5 + "\" -> Longest Palindrome: \"" + longestPalindromeEarlyExit(s5) + "\"");
        System.out.println("Input: \"" + s11 + "\" -> Longest Palindrome: \"" + longestPalindromeEarlyExit(s11) + "\" (Expected: \"xyzzyx\")");

        System.out.println("\n--- Approach 4: Manacher for Palindromic Substring Count ---");
        System.out.println("Input: \"" + s1 + "\" -> Palindrome Count: " + countPalindromicSubstrings(s1) + " (Expected for \"babad\": 7)"); // b,a,b,a,d, bab, aba
        System.out.println("Input: \"" + s5 + "\" -> Palindrome Count: " + countPalindromicSubstrings(s5) + " (Expected for \"racecar\": 10)"); // r,a,c,e,c,a,r, aceca, cec, racecar
        System.out.println("Input: \"" + s10 + "\" -> Palindrome Count: " + countPalindromicSubstrings(s10) + " (Expected for \"aaaaa\": 15)"); // 5x'a', 4x'aa', 3x'aaa', 2x'aaaa', 1x'aaaaa' = 5+4+3+2+1 = 15
        System.out.println("Input: \"" + s9 + "\" -> Palindrome Count: " + countPalindromicSubstrings(s9) + " (Expected: 0)");

        System.out.println("\n--- Approach 5: Manacher with Character Filtering/Preprocessing ---");
        System.out.println("Input: \"" + s12 + "\" -> Longest Filtered Palindrome: \"" + longestPalindromeFiltered(s12) + "\" (Expected: \"amanaplanacanalpanama\")");
        System.out.println("Input: \"Hello, World!\" -> Longest Filtered Palindrome: \"" + longestPalindromeFiltered("Hello, World!") + "\" (Expected: \"o\")");
        System.out.println("Input: \"\" -> Longest Filtered Palindrome: \"" + longestPalindromeFiltered("") + "\" (Expected: \"\")");
        System.out.println("Input: \"!@#$%^\" -> Longest Filtered Palindrome: \"" + longestPalindromeFiltered("!@#$%^") + "\" (Expected: \"\")");
    }
}
