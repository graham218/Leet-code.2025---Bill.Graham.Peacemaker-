import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class ValidAnagram {

    /**
     * Approach 1: Sorting
     *
     * Description:
     * This method sorts both input strings and then compares them. If the sorted strings are equal,
     * the original strings are anagrams.
     *
     * Rationale:
     * Sorting provides a straightforward way to normalize the strings, making the comparison order-insensitive.
     *
     * Time Complexity: O(n log n), where n is the length of the strings.
     * Space Complexity: O(n) in Java, due to the toCharArray() method, and the space used by the sorting algorithm.  Some sorting algorithms may have O(log n) space complexity.
     *
     * Real-world considerations:
     * -  Simple to understand and implement.
     * -  Not the most efficient for very large strings due to the sorting step.
     * -  Good for cases where the input strings are not excessively long and efficiency is not the absolute top priority.
     * -  May not be suitable for performance-critical applications with very large inputs.
     */
    public boolean isAnagramSort(String s, String t) {
        if (s.length() != t.length()) {
            return false;
        }
        char[] sChars = s.toCharArray();
        char[] tChars = t.toCharArray();
        Arrays.sort(sChars);
        Arrays.sort(tChars);
        return Arrays.equals(sChars, tChars);
    }

    /**
     * Approach 2: Character Counting with HashMap
     *
     * Description:
     * This method uses a HashMap to count the frequency of each character in the first string.
     * Then, it iterates through the second string, decrementing the counts. If a count goes negative
     * or if the lengths don't match, the strings are not anagrams.
     *
     * Rationale:
     * HashMap provides efficient storage and retrieval of character frequencies.
     *
     * Time Complexity: O(n), where n is the length of the strings.
     * Space Complexity: O(1), because the size of the HashMap is limited by the size of the alphabet.  In the worst case, it's O(26) for lowercase English letters.
     *
     * Real-world considerations:
     * -  More efficient than sorting for larger strings.
     * -  Handles Unicode characters correctly.
     * -  Suitable for most real-world scenarios.
     * -  The most common and recommended approach.
     */
    public boolean isAnagramHashMap(String s, String t) {
        if (s.length() != t.length()) {
            return false;
        }
        Map<Character, Integer> charCountMap = new HashMap<>();
        for (char c : s.toCharArray()) {
            charCountMap.put(c, charCountMap.getOrDefault(c, 0) + 1);
        }
        for (char c : t.toCharArray()) {
            int count = charCountMap.getOrDefault(c, 0);
            if (count == 0) {
                return false;
            }
            charCountMap.put(c, count - 1);
        }
        // Important: Check if all counts are zero
        for (int count : charCountMap.values()) {
            if (count != 0) {
                return false;
            }
        }

        return true;
    }

    /**
     * Approach 3: Character Counting with Array
     *
     * Description:
     * This method uses an integer array to count the frequency of each character.  It assumes the input strings contain only lowercase English letters.
     *
     * Rationale:
     * Using an array is more efficient than a HashMap for character counting when the character set is limited and known.
     *
     * Time Complexity: O(n), where n is the length of the strings.
     * Space Complexity: O(1), because the size of the array is fixed (26 for lowercase English letters).
     *
     * Real-world considerations:
     * -  Most efficient in terms of speed and space, *if* the input is limited to lowercase English letters.
     * -  Not suitable for Unicode or a large character set.
     * -  Commonly used in competitive programming where performance is critical and input constraints are well-defined.
     * -  If you know your character set is restricted, this is the best approach.
     */
    public boolean isAnagramArray(String s, String t) {
        if (s.length() != t.length()) {
            return false;
        }
        int[] charCounts = new int[26]; // Assuming lowercase English letters
        for (char c : s.toCharArray()) {
            charCounts[c - 'a']++;
        }
        for (char c : t.toCharArray()) {
            charCounts[c - 'a']--;
            if (charCounts[c - 'a'] < 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * Approach 4: Using Java 8 Streams
     *
     * Description:
     * This approach uses Java 8 streams to count character frequencies and compare them.
     *
     * Rationale:
     * Demonstrates a more functional approach using streams.  Can be more concise for those familiar with streams.
     *
     * Time Complexity: O(n), where n is the length of the strings.
     * Space Complexity: O(n) in the worst case, due to the intermediate map created by groupingBy.
     *
     * Real-world considerations:
     * -  More concise for developers familiar with streams.
     * -  May be slightly less performant than the array method, but still generally efficient.
     * -  Good for modern Java projects where functional programming is preferred.
     */
    public boolean isAnagramStreams(String s, String t) {
        if (s.length() != t.length()) {
            return false;
        }
        Map<Integer, Long> sCounts = s.chars().boxed()
                .collect(java.util.stream.Collectors.groupingBy(k -> k, java.util.stream.Collectors.counting()));
        Map<Integer, Long> tCounts = t.chars().boxed()
                .collect(java.util.stream.Collectors.groupingBy(k -> k, java.util.stream.Collectors.counting()));
        return sCounts.equals(tCounts);
    }

    /**
     * Approach 5:  Optimized Character Counting with Single Array
     *
     * Description:
     * This approach uses a single integer array to count the character frequencies.  It increments the counts for the first string and decrements them for the second string.
     *
     * Rationale:
     * This is an optimized version of the character counting with an array.  It reduces space slightly compared to using two HashMaps or two arrays in some implementations, and is very efficient.
     *
     * Time Complexity: O(n), where n is the length of the strings.
     * Space Complexity: O(1), because the size of the array is fixed (26 for lowercase English letters).
     *
     * Real-world considerations:
     * -  Very efficient in terms of both time and space.
     * -  Assumes a limited character set (here, lowercase English letters).
     * -  A preferred approach when you need optimal performance and have a limited character set.
     */
    public boolean isAnagramOptimized(String s, String t) {
        if (s.length() != t.length()) {
            return false;
        }
        int[] charCounts = new int[26]; // Assuming lowercase English letters
        for (int i = 0; i < s.length(); i++) {
            charCounts[s.charAt(i) - 'a']++;
            charCounts[t.charAt(i) - 'a']--;
        }
        for (int count : charCounts) {
            if (count != 0) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        ValidAnagram solution = new ValidAnagram();

        String s1 = "anagram";
        String t1 = "nagaram";
        System.out.println("Approach 1 (Sorting): " + solution.isAnagramSort(s1, t1)); // true
        System.out.println("Approach 2 (HashMap): " + solution.isAnagramHashMap(s1, t1)); // true
        System.out.println("Approach 3 (Array): " + solution.isAnagramArray(s1, t1)); // true
        System.out.println("Approach 4 (Streams): " + solution.isAnagramStreams(s1, t1)); // true
        System.out.println("Approach 5 (Optimized): " + solution.isAnagramOptimized(s1, t1)); //true


        String s2 = "rat";
        String t2 = "car";
        System.out.println("Approach 1 (Sorting): " + solution.isAnagramSort(s2, t2)); // false
        System.out.println("Approach 2 (HashMap): " + solution.isAnagramHashMap(s2, t2)); // false
        System.out.println("Approach 3 (Array): " + solution.isAnagramArray(s2, t2)); // false
        System.out.println("Approach 4 (Streams): " + solution.isAnagramStreams(s2, t2)); // false
        System.out.println("Approach 5 (Optimized): " + solution.isAnagramOptimized(s2, t2)); // false

        String s3 = "你好世界";
        String t3 = "界世你好";
        System.out.println("Approach 2 (HashMap) with Unicode: " + solution.isAnagramHashMap(s3, t3)); // true, handles unicode.
        System.out.println("Approach 4 (Streams) with Unicode: " + solution.isAnagramStreams(s3, t3)); // true, handles unicode.

        //The array approaches will fail with the above example
        String s4 = "a";
        String t4 = "b";
        System.out.println("Approach 1 (Sorting): " + solution.isAnagramSort(s4, t4));
        System.out.println("Approach 2 (HashMap): " + solution.isAnagramHashMap(s4, t4));
        System.out.println("Approach 3 (Array): " + solution.isAnagramArray(s4, t4));
        System.out.println("Approach 4 (Streams): " + solution.isAnagramStreams(s4, t4));
        System.out.println("Approach 5 (Optimized): " + solution.isAnagramOptimized(s4, t4));
    }
}
