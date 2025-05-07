import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class ValidParentheses {

    /**
     * Approach 1: Stack - Most efficient and standard approach
     * Time Complexity: O(n), where n is the length of the string.
     * Space Complexity: O(n) in the worst case, when the string contains only one type of parenthesis.
     *
     * @param s The input string containing parentheses.
     * @return true if the parentheses are valid, false otherwise.
     */
    public static boolean isValid_stack(String s) {
        // Use a Stack to keep track of opening parentheses.
        Deque<Character> stack = new ArrayDeque<>(); // Use ArrayDeque as a Stack (faster than Stack class)

        // Iterate through each character in the string.
        for (char c : s.toCharArray()) {
            if (c == '(' || c == '[' || c == '{') {
                // If it's an opening parenthesis, push it onto the stack.
                stack.push(c);
            } else {
                // If it's a closing parenthesis, check if the stack is empty.
                if (stack.isEmpty()) {
                    return false; // No corresponding opening parenthesis.
                }

                // Pop the top element from the stack.
                char top = stack.pop();

                // Check if the popped opening parenthesis matches the closing parenthesis.
                if ((c == ')' && top != '(') ||
                        (c == ']' && top != '[') ||
                        (c == '}' && top != '{')) {
                    return false; // Mismatched parentheses.
                }
            }
        }

        // After processing the entire string, the stack should be empty if all parentheses are valid.
        return stack.isEmpty();
    }

    /**
     * Approach 2: Using a Map and Stack
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     * Uses a map to store the mapping of closing to opening brackets.
     */
    public static boolean isValid_mapAndStack(String s) {
        // Create a map to store the mapping between closing and opening parentheses.
        Map<Character, Character> map = new HashMap<>();
        map.put(')', '(');
        map.put(']', '[');
        map.put('}', '{');

        // Use a stack to store opening parentheses.
        Deque<Character> stack = new ArrayDeque<>();

        for (char c : s.toCharArray()) {
            if (map.containsKey(c)) { // If it is a closing bracket.
                char topElement = stack.isEmpty() ? '#' : stack.pop(); // Use '#' for empty stack
                if (topElement != map.get(c)) {
                    return false;
                }
            } else { // If it is an opening bracket
                stack.push(c);
            }
        }
        return stack.isEmpty();
    }

    /**
     * Approach 3: Iterative Replacement (Less efficient, for demonstration)
     * Time Complexity: O(n^2) in the worst case, where n is the length of the string.  Repeatedly scanning and replacing.
     * Space Complexity: O(1) - modifies the input string in place (sort of).  StringBuilder creates new strings.
     * This approach repeatedly replaces matching pairs until no more replacements can be made.
     * It's less efficient due to the repeated string operations.
     */
    public static boolean isValid_replacement(String s) {
        // Use StringBuilder for efficient string manipulation.
        StringBuilder sb = new StringBuilder(s);
        int prevLength = 0;

        // Iterate as long as the string is changing (meaning we're still finding pairs to remove)
        while (sb.length() != prevLength) {
            prevLength = sb.length(); // Keep track of the previous length
            sb.replace(0, sb.length(), sb.toString().replace("()", "").replace("[]", "").replace("{}", ""));
        }

        // The string is valid if it's empty after all replacements.
        return sb.length() == 0;
    }

    /**
     * Approach 4: Recursive Replacement (Also less efficient, for demonstration)
     * Time Complexity: O(n^2) in the worst case.  Similar to iterative replacement, but recursive.
     * Space Complexity: O(n) due to the recursive call stack.
     * This approach recursively removes matching pairs of parentheses.  It's less efficient.
     */
    public static boolean isValid_recursive(String s) {
        // Base case: empty string is valid.
        if (s.isEmpty()) {
            return true;
        }

        // Recursive step: remove matching pairs and check the result.
        String replaced = s.replace("()", "").replace("[]", "").replace("{}", "");
        if (replaced.equals(s)) {
            return false; // No replacements were made, so it's invalid.
        }

        return isValid_recursive(replaced); // Recurse with the reduced string.
    }

    /**
     * Approach 5:  Two Pointers (Not suitable for this problem, demonstration only)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     * This approach is shown for demonstration, but it's *not* suitable for the general valid parentheses problem
     * because it only checks for one type of parenthesis and assumes a simple alternating pattern.
     * It will not work for cases like "(){}" or "[(])".
     */
    public static boolean isValid_twoPointers(String s) {
        int left = 0;
        int right = s.length() - 1;
        int count = 0;

        while (left < right) {
            if (s.charAt(left) == '(') {
                count++;
            } else {
                return false; // Invalid if the first char isn't '('
            }
            if (s.charAt(right) == ')') {
                count--;
            } else {
                return false; // Invalid if the last char isn't ')'
            }
            left++;
            right--;
        }
        return count == 0 && left >= right;
    }

    public static void main(String[] args) {
        // Test cases
        String test1 = "()";
        String test2 = "()[]{}";
        String test3 = "(]";
        String test4 = "([)]";
        String test5 = "{[]}";
        String test6 = "(((";
        String test7 = ")))";
        String test8 = "(){}";
        String test9 = "[(])";

        // Test all the methods.
        System.out.println("Test Cases for Valid Parentheses:");
        System.out.println("----------------------------------");

        System.out.println("Test Case 1: " + test1);
        System.out.println("Stack: " + isValid_stack(test1));
        System.out.println("Map and Stack: " + isValid_mapAndStack(test1));
        System.out.println("Replacement: " + isValid_replacement(test1));
        System.out.println("Recursive: " + isValid_recursive(test1));
        System.out.println("Two Pointers: " + isValid_twoPointers(test1)); //won't work correctly.

        System.out.println("\nTest Case 2: " + test2);
        System.out.println("Stack: " + isValid_stack(test2));
        System.out.println("Map and Stack: " + isValid_mapAndStack(test2));
        System.out.println("Replacement: " + isValid_replacement(test2));
        System.out.println("Recursive: " + isValid_recursive(test2));
        System.out.println("Two Pointers: " + isValid_twoPointers(test2));  //won't work correctly.

        System.out.println("\nTest Case 3: " + test3);
        System.out.println("Stack: " + isValid_stack(test3));
        System.out.println("Map and Stack: " + isValid_mapAndStack(test3));
        System.out.println("Replacement: " + isValid_replacement(test3));
        System.out.println("Recursive: " + isValid_recursive(test3));
        System.out.println("Two Pointers: " + isValid_twoPointers(test3)); //won't work correctly.

        System.out.println("\nTest Case 4: " + test4);
        System.out.println("Stack: " + isValid_stack(test4));
        System.out.println("Map and Stack: " + isValid_mapAndStack(test4));
        System.out.println("Replacement: " + isValid_replacement(test4));
        System.out.println("Recursive: " + isValid_recursive(test4));
        System.out.println("Two Pointers: " + isValid_twoPointers(test4)); //won't work correctly.

        System.out.println("\nTest Case 5: " + test5);
        System.out.println("Stack: " + isValid_stack(test5));
        System.out.println("Map and Stack: " + isValid_mapAndStack(test5));
        System.out.println("Replacement: " + isValid_replacement(test5));
        System.out.println("Recursive: " + isValid_recursive(test5));
        System.out.println("Two Pointers: " + isValid_twoPointers(test5)); //won't work correctly.

        System.out.println("\nTest Case 6: " + test6);
        System.out.println("Stack: " + isValid_stack(test6));
        System.out.println("Map and Stack: " + isValid_mapAndStack(test6));
        System.out.println("Replacement: " + isValid_replacement(test6));
        System.out.println("Recursive: " + isValid_recursive(test6));
        System.out.println("Two Pointers: " + isValid_twoPointers(test6)); //won't work correctly.

        System.out.println("\nTest Case 7: " + test7);
        System.out.println("Stack: " + isValid_stack(test7));
        System.out.println("Map and Stack: " + isValid_mapAndStack(test7));
        System.out.println("Replacement: " + isValid_replacement(test7));
        System.out.println("Recursive: " + isValid_recursive(test7));
        System.out.println("Two Pointers: " + isValid_twoPointers(test7)); //won't work correctly.

        System.out.println("\nTest Case 8: " + test8);
        System.out.println("Stack: " + isValid_stack(test8));
        System.out.println("Map and Stack: " + isValid_mapAndStack(test8));
        System.out.println("Replacement: " + isValid_replacement(test8));
        System.out.println("Recursive: " + isValid_recursive(test8));
        System.out.println("Two Pointers: " + isValid_twoPointers(test8)); //won't work correctly.

        System.out.println("\nTest Case 9: " + test9);
        System.out.println("Stack: " + isValid_stack(test9));
        System.out.println("Map and Stack: " + isValid_mapAndStack(test9));
        System.out.println("Replacement: " + isValid_replacement(test9));
        System.out.println("Recursive: " + isValid_recursive(test9));
        System.out.println("Two Pointers: " + isValid_twoPointers(test9)); //won't work correctly.
    }
}