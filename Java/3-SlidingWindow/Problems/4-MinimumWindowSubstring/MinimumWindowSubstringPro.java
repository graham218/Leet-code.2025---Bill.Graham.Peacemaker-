import java.util.*;

public class MinimumWindowSubstring {

    /**
     * Approach 1: Brute Force (Basic Approach)
     * -   Iterates through all possible substrings of 's'.
     * -   For each substring, checks if it contains all characters of 't'.
     * -   Keeps track of the smallest substring that satisfies the condition.
     *
     * Time Complexity: O(n^3), where n is the length of 's'.  (Potentially O(n^2 * m) where m is length of t)
     * Space Complexity: O(m), where m is the length of 't'.
     *
     * This approach is very inefficient and is included for completeness and comparison.  It would *not* be used in a real-world application due to its poor performance.
     */
    public String minWindowBruteForce(String s, String t) {
        if (s == null || t == null || s.isEmpty() || t.isEmpty() || t.length() > s.length()) {
            return "";
        }

        int minLength = Integer.MAX_VALUE;
        String minWindow = "";

        for (int i = 0; i < s.length(); i++) {
            for (int j = i; j < s.length(); j++) {
                String sub = s.substring(i, j + 1);
                if (containsAllChars(sub, t)) {
                    if (sub.length() < minLength) {
                        minLength = sub.length();
                        minWindow = sub;
                    }
                }
            }
        }
        return minWindow;
    }

    /**
     * Helper function for Brute Force approach to check if a substring contains all characters of t
     */
    private boolean containsAllChars(String sub, String t) {
        HashMap<Character, Integer> tFreq = new HashMap<>();
        for (char c : t.toCharArray()) {
            tFreq.put(c, tFreq.getOrDefault(c, 0) + 1);
        }

        HashMap<Character, Integer> subFreq = new HashMap<>();
        for (char c : sub.toCharArray()) {
            subFreq.put(c, subFreq.getOrDefault(c, 0) + 1);
        }

        for (char c : tFreq.keySet()) {
            if (!subFreq.containsKey(c) || subFreq.get(c) < tFreq.get(c)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Approach 2: Sliding Window with HashMap (Optimized)
     * -   Uses a sliding window technique to efficiently find the minimum window.
     * -   A HashMap is used to store the frequency of characters in 't'.
     * -   Another HashMap tracks the frequency of characters in the current window.
     * -   The window expands until it contains all characters of 't', then contracts to find the minimum window.
     *
     * Time Complexity: O(n), where n is the length of 's'.
     * Space Complexity: O(m), where m is the length of 't' (for the HashMaps).
     *
     * This is a standard, efficient approach suitable for most real-world scenarios.
     */
    public String minWindowSlidingWindow(String s, String t) {
        if (s == null || t == null || s.isEmpty() || t.isEmpty() || t.length() > s.length()) {
            return "";
        }

        Map<Character, Integer> tFreq = new HashMap<>();
        for (char c : t.toCharArray()) {
            tFreq.put(c, tFreq.getOrDefault(c, 0) + 1);
        }

        Map<Character, Integer> windowFreq = new HashMap<>();
        int left = 0, right = 0;
        int minLength = Integer.MAX_VALUE;
        String minWindow = "";
        int matched = 0; // Count of characters matched

        while (right < s.length()) {
            char c = s.charAt(right);
            windowFreq.put(c, windowFreq.getOrDefault(c, 0) + 1);

            if (tFreq.containsKey(c) && windowFreq.get(c).intValue() == tFreq.get(c).intValue()) { // Use intValue() for comparison
                matched++;
            }

            while (left <= right && matched == tFreq.size()) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    minWindow = s.substring(left, right + 1);
                }

                char leftChar = s.charAt(left);
                windowFreq.put(leftChar, windowFreq.get(leftChar) - 1);
                if (tFreq.containsKey(leftChar) && windowFreq.get(leftChar) < tFreq.get(leftChar)) {
                    matched--;
                }
                left++;
            }
            right++;
        }
        return minWindow;
    }

    /**
     * Approach 3: Sliding Window with Array (Optimized - for ASCII)
     * -   Similar to the sliding window approach, but uses arrays instead of HashMaps for frequency counting.
     * -   This optimization is valid if the character set is limited, such as ASCII (0-255).
     * -   Using arrays can be slightly faster than HashMaps in some cases due to reduced overhead.
     *
     * Time Complexity: O(n), where n is the length of 's'.
     * Space Complexity: O(1),  (256 for ASCII character set).
     *
     * This approach is suitable when you know the character set is limited and performance is critical.
     */
    public String minWindowSlidingWindowArray(String s, String t) {
        if (s == null || t == null || s.isEmpty() || t.isEmpty() || t.length() > s.length()) {
            return "";
        }

        int[] tFreq = new int[256]; // Assuming ASCII character set
        for (char c : t.toCharArray()) {
            tFreq[c]++;
        }

        int[] windowFreq = new int[256];
        int left = 0, right = 0;
        int minLength = Integer.MAX_VALUE;
        String minWindow = "";
        int matched = 0;

        while (right < s.length()) {
            char c = s.charAt(right);
            windowFreq[c]++;

            if (tFreq[c] != 0 && windowFreq[c] == tFreq[c]) {
                matched++;
            }

            while (left <= right && matched == t.length()) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    minWindow = s.substring(left, right + 1);
                }

                char leftChar = s.charAt(left);
                windowFreq[leftChar]--;
                if (tFreq[leftChar] != 0 && windowFreq[leftChar] < tFreq[leftChar]) {
                    matched--;
                }
                left++;
            }
            right++;
        }
        return minWindow;
    }

    /**
     * Approach 4: Optimized Sliding Window with Template (for reusability)
     * -   This approach encapsulates the sliding window logic into a reusable template.
     * -   The core logic is the same as Approach 2, but it's structured for better code organization and potential extension.
     * -   This pattern is useful if you have multiple sliding window problems to solve.
     */
    public String minWindowSlidingWindowTemplate(String s, String t) {
        if (s == null || t == null || s.isEmpty() || t.isEmpty() || t.length() > s.length()) {
            return "";
        }

        Map<Character, Integer> tFreq = new HashMap<>();
        for (char c : t.toCharArray()) {
            tFreq.put(c, tFreq.getOrDefault(c, 0) + 1);
        }

        return slidingWindowTemplate(s, tFreq);
    }

    private String slidingWindowTemplate(String s, Map<Character, Integer> targetFreq) {
        Map<Character, Integer> windowFreq = new HashMap<>();
        int left = 0, right = 0;
        int minLength = Integer.MAX_VALUE;
        String minWindow = "";
        int matched = 0;

        while (right < s.length()) {
            char c = s.charAt(right);
            windowFreq.put(c, windowFreq.getOrDefault(c, 0) + 1);

            if (targetFreq.containsKey(c) && windowFreq.get(c).intValue() == targetFreq.get(c).intValue()) {
                matched++;
            }

            while (left <= right && matched == targetFreq.size()) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    minWindow = s.substring(left, right + 1);
                }

                char leftChar = s.charAt(left);
                windowFreq.put(leftChar, windowFreq.get(leftChar) - 1);
                if (targetFreq.containsKey(leftChar) && windowFreq.get(leftChar) < targetFreq.get(leftChar)) {
                    matched--;
                }
                left++;
            }
            right++;
        }
        return minWindow;
    }

    /**
     * Approach 5:  Sliding Window with Frequency Array and Early Exit
     * - Uses a frequency array (for ASCII chars) like Approach 3 for efficiency.
     * - Includes an "early exit" optimization: if a window is found with the same length as t, it's the shortest possible.
     * - This can provide a small performance boost in some cases.
     */
    public String minWindowSlidingWindowEarlyExit(String s, String t) {
        if (s == null || t == null || s.isEmpty() || t.isEmpty() || t.length() > s.length()) {
            return "";
        }

        int[] tFreq = new int[256];
        for (char c : t.toCharArray()) {
            tFreq[c]++;
        }

        int[] windowFreq = new int[256];
        int left = 0, right = 0;
        int minLength = Integer.MAX_VALUE;
        String minWindow = "";
        int matched = 0;

        while (right < s.length()) {
            char c = s.charAt(right);
            windowFreq[c]++;

            if (tFreq[c] != 0 && windowFreq[c] == tFreq[c]) {
                matched++;
            }

            while (left <= right && matched == t.length()) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    minWindow = s.substring(left, right + 1);
                    if (minLength == t.length()) { // Early exit optimization
                        return minWindow;
                    }
                }

                char leftChar = s.charAt(left);
                windowFreq[leftChar]--;
                if (tFreq[leftChar] != 0 && windowFreq[leftChar] < tFreq[leftChar]) {
                    matched--;
                }
                left++;
            }
            right++;
        }
        return minWindow;
    }

    public static void main(String[] args) {
        MinimumWindowSubstring mws = new MinimumWindowSubstring();
        String s = "ADOBECODEBANC";
        String t = "ABC";

        System.out.println("Input s: " + s);
        System.out.println("Input t: " + t);
        System.out.println();

        // Brute Force (inefficient)
        String result1 = mws.minWindowBruteForce(s, t);
        System.out.println("Brute Force: " + result1);

        // Sliding Window with HashMap
        String result2 = mws.minWindowSlidingWindow(s, t);
        System.out.println("Sliding Window (HashMap): " + result2);

        // Sliding Window with Array (for ASCII)
        String result3 = mws.minWindowSlidingWindowArray(s, t);
        System.out.println("Sliding Window (Array): " + result3);

        // Sliding Window with Template
        String result4 = mws.minWindowSlidingWindowTemplate(s, t);
        System.out.println("Sliding Window (Template): " + result4);

        // Sliding Window with Early Exit
        String result5 = mws.minWindowSlidingWindowEarlyExit(s, t);
        System.out.println("Sliding Window (Early Exit): " + result5);
    }
}

