import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

class Solution {

    /**
     * Approach 1: Brute Force (Checking every substring)
     * Time Complexity: O(n * m * m!), where n is the length of s2 and m is the length of s1.
     * Space Complexity: O(m), for the character array of s1.
     *
     * This approach generates all permutations of s1 and checks if any of them
     * are a substring of s2.  It's very inefficient due to the factorial
     * time complexity of generating permutations.  This will likely TLE for
     * larger input strings.
     */
    public boolean checkInclusion_BruteForce(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }
        char[] s1Arr = s1.toCharArray();
        Arrays.sort(s1Arr); // Sort s1 to easily compare permutations
        String sortedS1 = new String(s1Arr);

        for (int i = 0; i <= s2.length() - s1.length(); i++) {
            String sub = s2.substring(i, i + s1.length());
            char[] subArr = sub.toCharArray();
            Arrays.sort(subArr);
            String sortedSub = new String(subArr);
            if (sortedSub.equals(sortedS1)) {
                return true;
            }
        }
        return false;
    }


    /**
     * Approach 2: Using Character Frequency Array
     * Time Complexity: O(n + m), where n is the length of s2 and m is the length of s1.
     * Space Complexity: O(1),  The frequency arrays have a fixed size (26 for lowercase English letters).
     *
     * This approach uses two frequency arrays to store the character counts of s1
     * and the current window in s2. It efficiently checks if the character counts match.
     */
    public boolean checkInclusion_FrequencyArray(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }

        int[] s1Freq = new int[26];
        int[] s2Freq = new int[26];

        // Calculate frequency of characters in s1
        for (char c : s1.toCharArray()) {
            s1Freq[c - 'a']++;
        }

        // Initial frequency count for the first window in s2
        for (int i = 0; i < s1.length(); i++) {
            s2Freq[s2.charAt(i) - 'a']++;
        }

        // Sliding window: compare frequencies and update counts
        for (int i = 0; i <= s2.length() - s1.length(); i++) {
            if (Arrays.equals(s1Freq, s2Freq)) {
                return true;
            }
            if (i < s2.length() - s1.length()) {
                // Remove the character going out of the window
                s2Freq[s2.charAt(i) - 'a']--;
                // Add the character entering the window
                s2Freq[s2.charAt(i + s1.length()) - 'a']++;
            }
        }
        return false;
    }

    /**
     * Approach 3: Using HashMap
     * Time Complexity: O(n + m), where n is the length of s2 and m is the length of s1.
     * Space Complexity: O(m),  for the HashMap to store character frequencies of s1.
     *
     * This approach uses a HashMap to store the character frequencies of s1.
     * It maintains a sliding window in s2 and checks if the character frequencies
     * in the window match those of s1.
     */
    public boolean checkInclusion_HashMap(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }

        Map<Character, Integer> s1Map = new HashMap<>();
        Map<Character, Integer> s2Map = new HashMap<>();

        // Calculate frequency of characters in s1
        for (char c : s1.toCharArray()) {
            s1Map.put(c, s1Map.getOrDefault(c, 0) + 1);
        }

        // Initial frequency count for the first window in s2
        for (int i = 0; i < s1.length(); i++) {
            s2Map.put(s2.charAt(i), s2Map.getOrDefault(s2.charAt(i), 0) + 1);
        }

        // Sliding window: compare frequencies and update counts
        for (int i = 0; i <= s2.length() - s1.length(); i++) {
            if (s1Map.equals(s2Map)) {
                return true;
            }
            if (i < s2.length() - s1.length()) {
                // Remove the character going out of the window
                char charToRemove = s2.charAt(i);
                s2Map.put(charToRemove, s2Map.get(charToRemove) - 1);
                if (s2Map.get(charToRemove) == 0) {
                    s2Map.remove(charToRemove);
                }
                // Add the character entering the window
                char charToAdd = s2.charAt(i + s1.length());
                s2Map.put(charToAdd, s2Map.getOrDefault(charToAdd, 0) + 1);
            }
        }
        return false;
    }

    /**
     * Approach 4: Optimized Sliding Window with Frequency Array and Match Count
     * Time Complexity: O(n + m), where n is the length of s2 and m is the length of s1.
     * Space Complexity: O(1), for the frequency array (fixed size of 26).
     *
     * This is an optimized version of the frequency array approach.  It avoids
     * comparing the entire arrays in each iteration.  Instead, it maintains a
     * 'match' count of characters that have the same frequency in both s1 and the
     * current window of s2.
     */
    public boolean checkInclusion_Optimized(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }

        int[] s1Freq = new int[26];
        int[] s2Freq = new int[26];
        int match = 0;

        // Calculate frequency of characters in s1
        for (char c : s1.toCharArray()) {
            s1Freq[c - 'a']++;
        }

        // Initial frequency count for the first window in s2 and calculate initial match
        for (int i = 0; i < s1.length(); i++) {
            s2Freq[s2.charAt(i) - 'a']++;
            if (s1Freq[s2.charAt(i) - 'a'] == s2Freq[s2.charAt(i) - 'a']) {
                match++;
            }
        }

        // Sliding window: compare frequencies and update counts
        for (int i = 0; i <= s2.length() - s1.length(); i++) {
            if (match == 26) { // If all 26 characters match, we found a permutation
                return true;
            }
            if (i < s2.length() - s1.length()) {
                // Remove the character going out of the window
                char charToRemove = s2.charAt(i);
                s2Freq[charToRemove - 'a']--;
                if (s1Freq[charToRemove - 'a'] == s2Freq[charToRemove - 'a'] + 1) {
                    match--; // Was matching, now doesn't match
                } else if (s1Freq[charToRemove - 'a'] == s2Freq[charToRemove - 'a']) {
                    match++; // Was not matching, now matches
                }

                // Add the character entering the window
                char charToAdd = s2.charAt(i + s1.length());
                s2Freq[charToAdd - 'a']++;
                if (s1Freq[charToAdd - 'a'] == s2Freq[charToAdd - 'a'] - 1) {
                    match--;  // Was matching, now doesn't match
                } else if (s1Freq[charToAdd - 'a'] == s2Freq[charToAdd - 'a']) {
                    match++; // Was not matching, now matches
                }
            }
        }
        return false;
    }


    /**
     * Approach 5: Optimized Sliding Window with Early Exit
     * Time Complexity: O(n + m) in the average case, but can be O(n * m) in the worst case.
     * Space Complexity: O(1), for the frequency array (fixed size of 26).
     *
     * This approach optimizes the sliding window by checking for a mismatch as
     * soon as it occurs within the window.  If a mismatch is found, it immediately
     * slides the window, potentially avoiding unnecessary comparisons.  It's
     * generally faster in practice, especially when mismatches are common.
     */
    public boolean checkInclusion_EarlyExit(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }

        int[] s1Freq = new int[26];

        // Calculate frequency of characters in s1
        for (char c : s1.toCharArray()) {
            s1Freq[c - 'a']++;
        }

        for (int i = 0; i <= s2.length() - s1.length(); i++) {
            int[] s2Freq = new int[26];
            // Check for a potential match
            for (int j = 0; j < s1.length(); j++) {
                s2Freq[s2.charAt(i + j) - 'a']++;
            }
            if (Arrays.equals(s1Freq, s2Freq)) {
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        Solution solution = new Solution();

        // Test cases
        String s1 = "ab";
        String s2 = "eidbaooo";
        System.out.println("Test Case 1:");
        System.out.println("Input: s1 = " + s1 + ", s2 = " + s2);
        System.out.println("Brute Force: " + solution.checkInclusion_BruteForce(s1, s2)); // false
        System.out.println("Frequency Array: " + solution.checkInclusion_FrequencyArray(s1, s2)); // true
        System.out.println("HashMap: " + solution.checkInclusion_HashMap(s1, s2)); // true
        System.out.println("Optimized: " + solution.checkInclusion_Optimized(s1, s2)); // true
        System.out.println("Early Exit: " + solution.checkInclusion_EarlyExit(s1, s2)); // true


        s1 = "ab";
        s2 = "eidboaoo";
        System.out.println("\nTest Case 2:");
        System.out.println("Input: s1 = " + s1 + ", s2 = " + s2);
        System.out.println("Brute Force: " + solution.checkInclusion_BruteForce(s1, s2)); // false
        System.out.println("Frequency Array: " + solution.checkInclusion_FrequencyArray(s1, s2)); // false
        System.out.println("HashMap: " + solution.checkInclusion_HashMap(s1, s2)); // false
        System.out.println("Optimized: " + solution.checkInclusion_Optimized(s1, s2)); // false
        System.out.println("Early Exit: " + solution.checkInclusion_EarlyExit(s1, s2)); // false

        s1 = "hello";
        s2 = "ooolleoooleh";
        System.out.println("\nTest Case 3:");
        System.out.println("Input: s1 = " + s1 + ", s2 = " + s2);
        System.out.println("Brute Force: " + solution.checkInclusion_BruteForce(s1, s2));
        System.out.println("Frequency Array: " + solution.checkInclusion_FrequencyArray(s1, s2));
        System.out.println("HashMap: " + solution.checkInclusion_HashMap(s1, s2));
        System.out.println("Optimized: " + solution.checkInclusion_Optimized(s1, s2));
        System.out.println("Early Exit: " + solution.checkInclusion_EarlyExit(s1, s2));

        s1 = "abc";
        s2 = "ccccbbaaa";
        System.out.println("\nTest Case 4:");
        System.out.println("Input: s1 = " + s1 + ", s2 = " + s2);
        System.out.println("Brute Force: " + solution.checkInclusion_BruteForce(s1, s2));
        System.out.println("Frequency Array: " + solution.checkInclusion_FrequencyArray(s1, s2));
        System.out.println("HashMap: " + solution.checkInclusion_HashMap(s1, s2));
        System.out.println("Optimized: " + solution.checkInclusion_Optimized(s1, s2));
        System.out.println("Early Exit: " + solution.checkInclusion_EarlyExit(s1, s2));
    }
}
