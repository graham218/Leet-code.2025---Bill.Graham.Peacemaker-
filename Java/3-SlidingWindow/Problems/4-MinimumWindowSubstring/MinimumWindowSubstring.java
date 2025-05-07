import java.util.*;

public class MinimumWindowSubstring {

    /**
     * Approach 1: Brute Force
     * - Iterate through all possible substrings of `s`.
     * - For each substring, check if it contains all characters of `t`.
     * - Keep track of the smallest substring that satisfies the condition.
     *
     * Time Complexity: O(n^3), where n is the length of `s`.
     * Space Complexity: O(m), where m is the length of `t`.
     */
    public String minWindowBruteForce(String s, String t) {
        if (s == null || t == null || s.length() < t.length()) {
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

    private boolean containsAllChars(String sub, String t) {
        Map<Character, Integer> tMap = new HashMap<>();
        for (char c : t.toCharArray()) {
            tMap.put(c, tMap.getOrDefault(c, 0) + 1);
        }

        Map<Character, Integer> subMap = new HashMap<>();
        for (char c : sub.toCharArray()) {
            subMap.put(c, subMap.getOrDefault(c, 0) + 1);
        }

        for (char c : tMap.keySet()) {
            if (!subMap.containsKey(c) || subMap.get(c) < tMap.get(c)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Approach 2: Optimized Brute Force
     * - Similar to brute force, but optimizes the character checking.
     * - Instead of creating a new map for every substring, we maintain a single map
     * and update it as we go.
     *
     * Time Complexity: O(n^2 * m), where n is the length of `s` and m is the length of `t`.
     * Space Complexity: O(m), where m is the length of `t`.
     */
    public String minWindowOptimizedBruteForce(String s, String t) {
        if (s == null || t == null || s.length() < t.length()) {
            return "";
        }

        int minLength = Integer.MAX_VALUE;
        String minWindow = "";
        Map<Character, Integer> tMap = new HashMap<>();
        for (char c : t.toCharArray()) {
            tMap.put(c, tMap.getOrDefault(c, 0) + 1);
        }

        for (int i = 0; i < s.length(); i++) {
            for (int j = i; j < s.length(); j++) {
                String sub = s.substring(i, j + 1);
                if (containsAllCharsOptimized(sub, tMap)) {
                    if (sub.length() < minLength) {
                        minLength = sub.length();
                        minWindow = sub;
                    }
                }
            }
        }
        return minWindow;
    }

    private boolean containsAllCharsOptimized(String sub, Map<Character, Integer> tMap) {
        Map<Character, Integer> subMap = new HashMap<>();
        for (char c : sub.toCharArray()) {
            subMap.put(c, subMap.getOrDefault(c, 0) + 1);
        }

        for (Map.Entry<Character, Integer> entry : tMap.entrySet()) {
            char c = entry.getKey();
            int count = entry.getValue();
            if (!subMap.containsKey(c) || subMap.get(c) < count) {
                return false;
            }
        }
        return true;
    }

    /**
     * Approach 3: Sliding Window with HashMap
     * - Use a sliding window to efficiently find the minimum window.
     * - Maintain a HashMap to store the frequency of characters in `t`.
     * - Expand the window until it contains all characters of `t`.
     * - Shrink the window to find the minimum window.
     *
     * Time Complexity: O(n), where n is the length of `s`.
     * Space Complexity: O(m), where m is the length of `t`.
     */
    public String minWindowSlidingWindow(String s, String t) {
        if (s == null || t == null || s.length() < t.length()) {
            return "";
        }

        Map<Character, Integer> tMap = new HashMap<>();
        for (char c : t.toCharArray()) {
            tMap.put(c, tMap.getOrDefault(c, 0) + 1);
        }

        int left = 0, right = 0;
        int minLength = Integer.MAX_VALUE;
        String minWindow = "";
        int matched = 0; // Count of characters matched

        Map<Character, Integer> windowMap = new HashMap<>();
        while (right < s.length()) {
            char c = s.charAt(right);
            windowMap.put(c, windowMap.getOrDefault(c, 0) + 1);

            if (tMap.containsKey(c) && windowMap.get(c).intValue() == tMap.get(c).intValue()) {
                matched++;
            }

            while (left <= right && matched == tMap.size()) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    minWindow = s.substring(left, right + 1);
                }

                char leftChar = s.charAt(left);
                windowMap.put(leftChar, windowMap.get(leftChar) - 1);
                if (tMap.containsKey(leftChar) && windowMap.get(leftChar) < tMap.get(leftChar)) {
                    matched--;
                }
                left++;
            }
            right++;
        }
        return minWindow;
    }

    /**
     * Approach 4: Sliding Window with Array (Optimized)
     * - Similar to the sliding window approach, but uses an array instead of a HashMap
     * for faster character frequency tracking (assuming ASCII characters).
     * - This optimization can improve performance, especially for larger input strings.
     *
     * Time Complexity: O(n), where n is the length of `s`.
     * Space Complexity: O(1),  since the array size is fixed (256 for ASCII).
     */
    public String minWindowSlidingWindowArray(String s, String t) {
        if (s == null || t == null || s.length() < t.length()) {
            return "";
        }

        int[] tFreq = new int[256]; // Assuming ASCII characters
        for (char c : t.toCharArray()) {
            tFreq[c]++;
        }

        int left = 0, right = 0;
        int minLength = Integer.MAX_VALUE;
        String minWindow = "";
        int matched = 0;

        int[] windowFreq = new int[256];
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
     * Approach 5: Sliding Window Optimized Template
     * - Uses a template for the sliding window problem, further optimizing and
     * making the code more concise.
     * - This approach is very efficient and easy to understand.
     *
     * Time Complexity: O(n), where n is the length of `s`.
     * Space Complexity: O(m), where m is the length of `t`.
     */
    public String minWindowOptimizedTemplate(String s, String t) {
        if (s == null || t == null || s.length() < t.length()) {
            return "";
        }

        Map<Character, Integer> need = new HashMap<>();
        for (char c : t.toCharArray()) {
            need.put(c, need.getOrDefault(c, 0) + 1);
        }

        int left = 0, right = 0;
        int minLength = Integer.MAX_VALUE;
        String minWindow = "";
        int have = 0;

        while (right < s.length()) {
            char c = s.charAt(right);
            if (need.containsKey(c)) {
                need.put(c, need.get(c) - 1);
                if (need.get(c) >= 0) { // Important: Only increment 'have' if it's needed
                    have++;
                }
            }

            while (have == t.length()) {
                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    minWindow = s.substring(left, right + 1);
                }

                char leftChar = s.charAt(left);
                if (need.containsKey(leftChar)) {
                    need.put(leftChar, need.get(leftChar) + 1);
                    if (need.get(leftChar) > 0) { // Important: Only decrement 'have' if it breaks the condition
                        have--;
                    }
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

        System.out.println("Input: s = " + s + ", t = " + t);
        System.out.println("Brute Force: " + mws.minWindowBruteForce(s, t));
        System.out.println("Optimized Brute Force: " + mws.minWindowOptimizedBruteForce(s, t));
        System.out.println("Sliding Window with HashMap: " + mws.minWindowSlidingWindow(s, t));
        System.out.println("Sliding Window with Array: " + mws.minWindowSlidingWindowArray(s, t));
        System.out.println("Sliding Window Optimized Template: " + mws.minWindowOptimizedTemplate(s, t));
    }
}

