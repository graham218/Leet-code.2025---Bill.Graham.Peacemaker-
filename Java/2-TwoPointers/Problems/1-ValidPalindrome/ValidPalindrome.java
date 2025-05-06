import java.util.Locale;

public class ValidPalindrome {

    public static void main(String[] args) {
        String testString1 = "A man, a plan, a canal: Panama";
        String testString2 = "race a car";
        String testString3 = " ";
        String testString4 = "Madam, I'm Adam!";
        String testString5 = "121";

        // Test cases for each approach
        System.out.println("Test Cases for Valid Palindrome:");
        System.out.println("String 1: " + testString1);
        System.out.println("String 2: " + testString2);
        System.out.println("String 3: " + testString3);
        System.out.println("String 4: " + testString4);
        System.out.println("String 5: " + testString5);
        System.out.println("\nResults:");

        // Approach 1: Using StringBuilder (Two Pointers)
        System.out.println("\nApproach 1: Using StringBuilder (Two Pointers)");
        System.out.println("String 1: " + isPalindrome1(testString1));
        System.out.println("String 2: " + isPalindrome1(testString2));
        System.out.println("String 3: " + isPalindrome1(testString3));
        System.out.println("String 4: " + isPalindrome1(testString4));
        System.out.println("String 5: " + isPalindrome1(testString5));


        // Approach 2: Using Two Pointers (Optimized)
        System.out.println("\nApproach 2: Using Two Pointers (Optimized)");
        System.out.println("String 1: " + isPalindrome2(testString1));
        System.out.println("String 2: " + isPalindrome2(testString2));
        System.out.println("String 3: " + isPalindrome2(testString3));
        System.out.println("String 4: " + isPalindrome2(testString4));
        System.out.println("String 5: " + isPalindrome2(testString5));

        // Approach 3: Using Recursion
        System.out.println("\nApproach 3: Using Recursion");
        System.out.println("String 1: " + isPalindrome3(testString1));
        System.out.println("String 2: " + isPalindrome3(testString2));
        System.out.println("String 3: " + isPalindrome3(testString3));
        System.out.println("String 4: " + isPalindrome3(testString4));
        System.out.println("String 5: " + isPalindrome3(testString5));

        // Approach 4: Using Regular Expression and StringBuilder
        System.out.println("\nApproach 4: Using Regular Expression and StringBuilder");
        System.out.println("String 1: " + isPalindrome4(testString1));
        System.out.println("String 2: " + isPalindrome4(testString2));
        System.out.println("String 3: " + isPalindrome4(testString3));
        System.out.println("String 4: " + isPalindrome4(testString4));
        System.out.println("String 5: " + isPalindrome4(testString5));

        // Approach 5: Using Character.isLetterOrDigit and Two Pointers
        System.out.println("\nApproach 5: Using Character.isLetterOrDigit and Two Pointers");
        System.out.println("String 1: " + isPalindrome5(testString1));
        System.out.println("String 2: " + isPalindrome5(testString2));
        System.out.println("String 3: " + isPalindrome5(testString3));
        System.out.println("String 4: " + isPalindrome5(testString4));
        System.out.println("String 5: " + isPalindrome5(testString5));
    }

    /**
     * Approach 1: Using StringBuilder (Two Pointers)
     *
     * - Filters out non-alphanumeric characters and converts the string to lowercase.
     * - Uses StringBuilder to create a reversed version of the filtered string.
     * - Compares the filtered string with its reversed version.
     *
     * Time Complexity: O(n), where n is the length of the string.
     * Space Complexity: O(n), for the StringBuilder.
     */
    public static boolean isPalindrome1(String s) {
        if (s == null) {
            return true; // Handle null input as a special case.
        }
        StringBuilder filteredString = new StringBuilder();
        for (char c : s.toCharArray()) {
            if (Character.isLetterOrDigit(c)) {
                filteredString.append(Character.toLowerCase(c));
            }
        }
        String reversedString = filteredString.reverse().toString();
        return filteredString.toString().equals(reversedString);
    }

    /**
     * Approach 2: Using Two Pointers (Optimized)
     *
     * - Uses two pointers, one starting from the beginning and the other from the end.
     * - Iterates through the string, comparing characters at the two pointer positions.
     * - Skips non-alphanumeric characters.
     * - More efficient as it avoids creating new strings.
     *
     * Time Complexity: O(n), where n is the length of the string.
     * Space Complexity: O(1), constant space.
     */
    public static boolean isPalindrome2(String s) {
        if (s == null) {
            return true;
        }
        int left = 0;
        int right = s.length() - 1;
        while (left < right) {
            while (left < right && !Character.isLetterOrDigit(s.charAt(left))) {
                left++;
            }
            while (left < right && !Character.isLetterOrDigit(s.charAt(right))) {
                right--;
            }
            if (left < right && Character.toLowerCase(s.charAt(left)) != Character.toLowerCase(s.charAt(right))) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    /**
     * Approach 3: Using Recursion
     *
     * - Recursively checks if the substring is a palindrome.
     * - Skips non-alphanumeric characters using helper methods.
     * - Base case: If the substring has 0 or 1 character, it's a palindrome.
     *
     * Time Complexity: O(n), where n is the length of the string.
     * Space Complexity: O(n), due to the recursion stack.
     */
    public static boolean isPalindrome3(String s) {
        if (s == null) {
            return true;
        }
        String filteredString = "";
        for(char c: s.toCharArray()){
            if(Character.isLetterOrDigit(c)){
                filteredString += c;
            }
        }
        filteredString = filteredString.toLowerCase();
        return isPalindromeRecursive(filteredString, 0, filteredString.length() - 1);
    }

    private static boolean isPalindromeRecursive(String s, int left, int right) {
        if (left >= right) {
            return true;
        }
        if (s.charAt(left) != s.charAt(right)) {
            return false;
        }
        return isPalindromeRecursive(s, left + 1, right - 1);
    }



    /**
     * Approach 4: Using Regular Expression and StringBuilder
     *
     * - Uses a regular expression to remove non-alphanumeric characters.
     * - Converts the string to lowercase.
     * - Uses StringBuilder to reverse the cleaned string and compare.
     *
     * Time Complexity: O(n), where n is the length of the string.
     * Space Complexity: O(n), for the StringBuilder.
     */
    public static boolean isPalindrome4(String s) {
        if (s == null) {
            return true;
        }
        String cleanedString = s.toLowerCase().replaceAll("[^a-z0-9]", "");
        String reversedString = new StringBuilder(cleanedString).reverse().toString();
        return cleanedString.equals(reversedString);
    }

    /**
     * Approach 5: Using Character.isLetterOrDigit and Two Pointers
     *
     * - This is a refined version of the two-pointer approach.
     * - It directly uses Character.isLetterOrDigit to check characters.
     * - It converts characters to lowercase for comparison.
     * - Efficient and avoids unnecessary string creation.
     *
     * Time Complexity: O(n), where n is the length of the string.
     * Space Complexity: O(1), constant space.
     */
    public static boolean isPalindrome5(String s) {
        if (s == null) {
            return true;
        }
        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            // Move left pointer to the next alphanumeric character
            while (left < right && !Character.isLetterOrDigit(s.charAt(left))) {
                left++;
            }
            // Move right pointer to the previous alphanumeric character
            while (left < right && !Character.isLetterOrDigit(s.charAt(right))) {
                right--;
            }
            // Compare characters at both pointers (case-insensitive)
            if (left < right && Character.toLowerCase(s.charAt(left)) != Character.toLowerCase(s.charAt(right))) {
                return false; // If characters don't match, it's not a palindrome
            }
            // Move pointers towards the center
            left++;
            right--;
        }
        return true; // If the loop finishes without finding a mismatch, it's a palindrome
    }
}

