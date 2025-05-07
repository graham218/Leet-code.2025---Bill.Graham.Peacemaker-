import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class ValidParentheses {

    /**
     * Approach 1: Stack - Basic Implementation
     *
     * This is the most common and straightforward approach.  It uses a stack to keep track of opening parentheses.
     * When a closing parenthesis is encountered, it checks if the stack's top contains the corresponding opening parenthesis.
     *
     * Time Complexity: O(n), where n is the length of the string.
     * Space Complexity: O(n), in the worst case (e.g., "(((((").
     */
    public static boolean isValid_stack(String s) {
        if (s == null || s.length() % 2 != 0) {
            return false; // Handle null or odd-length strings, which cannot be valid.
        }

        Deque<Character> stack = new ArrayDeque<>(); // Use ArrayDeque as a Stack (more efficient)

        for (char c : s.toCharArray()) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c); // Push opening parenthesis onto the stack.
            } else {
                if (stack.isEmpty()) {
                    return false; // Closing parenthesis without a matching opening one.
                }
                char top = stack.pop();
                if ((c == ')' && top != '(') ||
                        (c == ']' && top != '[') ||
                        (c == '}' && top != '{')) {
                    return false; // Mismatched parentheses.
                }
            }
        }
        return stack.isEmpty(); // The string is valid if the stack is empty at the end.
    }

    /**
     * Approach 2: Stack with HashMap for Matching
     *
     * This approach improves readability and maintainability by using a HashMap to store the mapping between
     * closing and opening parentheses.  This makes the matching logic cleaner.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public static boolean isValid_stack_map(String s) {
        if (s == null || s.length() % 2 != 0) {
            return false;
        }

        Deque<Character> stack = new ArrayDeque<>();
        Map<Character, Character> map = new HashMap<>();
        map.put(')', '(');
        map.put(']', '[');
        map.put('}', '{');

        for (char c : s.toCharArray()) {
            if (map.containsValue(c)) { // if c is an opening bracket
                stack.push(c);
            } else if (map.containsKey(c)) { // if c is a closing bracket
                if (stack.isEmpty() || stack.pop() != map.get(c)) {
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }

    /**
     * Approach 3: Stack - Optimized (Slightly More Efficient)
     *
     * This approach optimizes the basic stack approach slightly by avoiding unnecessary checks within the loop.
     * It checks for an empty stack and mismatched parentheses in a single condition.  This can be slightly faster
     * in some cases.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public static boolean isValid_stack_optimized(String s) {
        if (s == null || s.length() % 2 != 0) {
            return false;
        }

        Deque<Character> stack = new ArrayDeque<>();

        for (char c : s.toCharArray()) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c);
            } else {
                if (stack.isEmpty() ||
                        (c == ')' && stack.pop() != '(') ||
                        (c == ']' && stack.pop() != '[') ||
                        (c == '}' && stack.pop() != '{')) {
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }

    /**
     * Approach 4: Iterative Replacement (Less Efficient, Not Recommended)
     *
     * This approach repeatedly replaces matching pairs of parentheses ("()", "[]", "{}") with empty strings.
     * If the string becomes empty, it's valid.  This approach is generally *less efficient* than the stack-based
     * approaches, especially for large strings, because string replacement is an expensive operation.
     * It's included for demonstration purposes, but it's *not recommended* for real-world use.
     *
     * Time Complexity: O(n^2) in the worst case, where n is the length of the string.  Each replacement can take O(n),
     * and in the worst case, you might need to do n/2 replacements.
     * Space Complexity: O(1) (in-place replacement, but string operations can create temporary strings).
     */
    public static boolean isValid_replace(String s) {
        if (s == null) {
            return false;
        }

        while (s.contains("()") || s.contains("[]") || s.contains("{}")) {
            s = s.replace("()", "");
            s = s.replace("[]", "");
            s = s.replace("{}", "");
        }
        return s.isEmpty();
    }

    /**
     * Approach 5: Using a Stack and a Helper Function
     *
     * This approach uses a stack, similar to the first approach, but it introduces a helper function
     * `isMatchingPair` to check if two parentheses are a valid pair. This improves code organization
     * and readability, making the main function cleaner.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public static boolean isValid_stack_helper(String s) {
        if (s == null || s.length() % 2 != 0) {
            return false;
        }

        Deque<Character> stack = new ArrayDeque<>();

        for (char c : s.toCharArray()) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c);
            } else {
                if (stack.isEmpty() || !isMatchingPair(stack.pop(), c)) {
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }

    private static boolean isMatchingPair(char open, char close) {
        return (open == '(' && close == ')') ||
                (open == '[' && close == ']') ||
                (open == '{' && close == '}');
    }

    public static void main(String[] args) {
        String test1 = "()";
        String test2 = "()[]{}";
        String test3 = "(]";
        String test4 = "([)]";
        String test5 = "{[]}";
        String test6 = "(((";
        String test7 = ")))";
        String test8 = "(){}";
        String test9 = " "; // Test with space
        String test10 = null;

        // Test cases
        String[] tests = {test1, test2, test3, test4, test5, test6, test7, test8, test9, test10};

        System.out.println("--- Stack (Basic) ---");
        for (String test : tests) {
            System.out.println("\"" + test + "\": " + isValid_stack(test));
        }

        System.out.println("\n--- Stack with HashMap ---");
        for (String test : tests) {
            System.out.println("\"" + test + "\": " + isValid_stack_map(test));
        }

        System.out.println("\n--- Stack (Optimized) ---");
        for (String test : tests) {
            System.out.println("\"" + test + "\": " + isValid_stack_optimized(test));
        }

        System.out.println("\n--- Iterative Replacement (Not Recommended) ---");
        for (String test : tests) {
            System.out.println("\"" + test + "\": " + isValid_replace(test));
        }

        System.out.println("\n--- Stack with Helper Function ---");
        for (String test : tests) {
            System.out.println("\"" + test + "\": " + isValid_stack_helper(test));
        }
    }
}

