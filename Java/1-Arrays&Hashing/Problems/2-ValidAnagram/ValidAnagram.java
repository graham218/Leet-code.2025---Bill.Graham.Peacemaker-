import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class ValidAnagram {

    /**
     * Approach 1: Sorting
     * Check if two strings are anagrams by sorting them and comparing the sorted strings.
     * <p>
     * Time Complexity: O(n log n), where n is the length of the strings.
     * Space Complexity: O(n) in Java, due to the creation of new char arrays.  Some languages may sort in place.
     */
    public boolean isAnagram_Sorting(String s, String t) {
        if (s == null || t == null || s.length() != t.length()) { // Added null checks.
            return false;
        }
        char[] sChars = s.toCharArray();
        char[] tChars = t.toCharArray();
        Arrays.sort(sChars);
        Arrays.sort(tChars);
        return Arrays.equals(sChars, tChars);
    }

    /**
     * Approach 2: HashMap Counting
     * Use a HashMap to count the frequency of each character in the first string,
     * and then decrement the counts for each character in the second string.
     * If all counts are zero at the end, the strings are anagrams.
     * <p>
     * Time Complexity: O(n), where n is the length of the strings.
     * Space Complexity: O(n), in the worst case, if the strings have many unique characters.
     */
    public boolean isAnagram_HashMap(String s, String t) {
        if (s == null || t == null || s.length() != t.length()) { // Added null checks.
            return false;
        }
        Map<Character, Integer> charCounts = new HashMap<>();
        for (char c : s.toCharArray()) {
            charCounts.put(c, charCounts.getOrDefault(c, 0) + 1);
        }
        for (char c : t.toCharArray()) {
            Integer count = charCounts.get(c); // Changed to Integer to handle null
            if (count == null) {
                return false;
            }
            if (count == 1) {
                charCounts.remove(c);
            } else {
                charCounts.put(c, count - 1);
            }
        }
        return charCounts.isEmpty();
    }

    /**
     * Approach 3: Array Counting (Optimized for lowercase English letters)
     * Use an array of size 26 to count the frequency of each lowercase English letter.
     * This is more efficient than a HashMap because it avoids the overhead of hashing.
     * <p>
     * Time Complexity: O(n), where n is the length of the strings.
     * Space Complexity: O(1), because the array size is fixed (26).
     * Note: This method is only suitable for lowercase English letters.  It will produce
     * incorrect results or errors with other characters.
     */
    public boolean isAnagram_Array(String s, String t) {
        if (s == null || t == null || s.length() != t.length()) { // Added null checks.
            return false;
        }
        int[] charCounts = new int[26]; // Assuming lowercase English letters
        for (char c : s.toCharArray()) {
            if (c < 'a' || c > 'z') return false; // Added check for valid lowercase
            charCounts[c - 'a']++;
        }
        for (char c : t.toCharArray()) {
            if (c < 'a' || c > 'z') return false;  // Added check for valid lowercase
            charCounts[c - 'a']--;
            if (charCounts[c - 'a'] < 0) {
                return false;
            }
        }
        return true; // Simplified: No need to check the entire array.
    }

    /**
     * Approach 4:  Using only one Array (Slightly optimized Array Counting)
     * This approach uses only one array to store the difference in character counts
     * between the two strings.  It's slightly more efficient than the previous array method.
     * <p>
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     * Note: This method is only suitable for lowercase English letters.
     */
    public boolean isAnagram_SingleArray(String s, String t) {
        if (s == null || t == null || s.length() != t.length()) {  // Added null checks.
            return false;
        }
        int[] charCounts = new int[26];
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) < 'a' || s.charAt(i) > 'z' || t.charAt(i) < 'a' || t.charAt(i) > 'z')
                return false;
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

    /**
     * Approach 5:  Using code points to handle Unicode characters
     * This approach handles Unicode characters correctly by using code points.
     * It's more general than the previous array methods, which assume ASCII.
     * <p>
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public boolean isAnagram_Unicode(String s, String t) {
        if (s == null || t == null || s.length() != t.length()) { // Added null checks.
            return false;
        }
        Map<Integer, Integer> charCounts = new HashMap<>();
        for (int i = 0; i < s.length(); i++) {
            int codePoint = s.codePointAt(i);
            charCounts.put(codePoint, charCounts.getOrDefault(codePoint, 0) + 1);
            if (codePoint >= Character.MIN_SUPPLEMENTARY_CODE_POINT) {
                i++; // Skip the second char of a surrogate pair.
            }
        }
        for (int i = 0; i < t.length(); i++) {
            int codePoint = t.codePointAt(i);
            Integer count = charCounts.get(codePoint);  // Changed to Integer
            if (count == null) {
                return false;
            }
            if (count == 1) {
                charCounts.remove(codePoint);
            } else {
                charCounts.put(codePoint, count - 1);
            }
            if (codePoint >= Character.MIN_SUPPLEMENTARY_CODE_POINT) {
                i++;
            }
        }
        return charCounts.isEmpty();
    }

    public static void main(String[] args) {
        ValidAnagram solution = new ValidAnagram();
        String s1 = "anagram";
        String t1 = "nagaram";
        String s2 = "rat";
        String t2 = "car";
        String s3 = "你好世界";
        String t3 = "世界你好";
        String s4 = "test";
        String t4 = "tset";
        String s5 = "aA";
        String t5 = "Aa";

        // Test cases
        System.out.println("Test Case 1: s = " + s1 + ", t = " + t1);
        System.out.println("Sorting: " + solution.isAnagram_Sorting(s1, t1));
        System.out.println("HashMap: " + solution.isAnagram_HashMap(s1, t1));
        System.out.println("Array: " + solution.isAnagram_Array(s1, t1));
        System.out.println("Single Array: " + solution.isAnagram_SingleArray(s1, t1));
        System.out.println("Unicode: " + solution.isAnagram_Unicode(s1, t1));

        System.out.println("\nTest Case 2: s = " + s2 + ", t = " + t2);
        System.out.println("Sorting: " + solution.isAnagram_Sorting(s2, t2));
        System.out.println("HashMap: " + solution.isAnagram_HashMap(s2, t2));
        System.out.println("Array: " + solution.isAnagram_Array(s2, t2));
        System.out.println("Single Array: " + solution.isAnagram_SingleArray(s2, t2));
        System.out.println("Unicode: " + solution.isAnagram_Unicode(s2, t2));

        // Test case with Unicode characters
        System.out.println("\nTest Case 3: s = " + s3 + ", t = " + t3);
        System.out.println("Unicode: " + solution.isAnagram_Unicode(s3, t3));
        System.out.println("HashMap: " + solution.isAnagram_HashMap(s3, t3));
        System.out.println("Array: " + solution.isAnagram_Array(s3, t3));
        System.out.println("Single Array: " + solution.isAnagram_SingleArray(s3, t3));

        System.out.println("\nTest Case 4: s = " + s4 + ", t = " + t4);
        System.out.println("Sorting: " + solution.isAnagram_Sorting(s4, t4));
        System.out.println("HashMap: " + solution.isAnagram_HashMap(s4, t4));
        System.out.println("Unicode: " + solution.isAnagram_Unicode(s4, t4));

        System.out.println("\nTest Case 5: s = " + s5 + ", t = " + t5);
        System.out.println("Single Array: " + solution.isAnagram_SingleArray(s5, t5));
        System.out.println("Array: " + solution.isAnagram_Array(s5, t5));
    }
}
