import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class ValidParentheses {

    public static void main(String[] args) {
        String test1 = "()";
        String test2 = "()[]{}";
        String test3 = "(]";
        String test4 = "([)]";
        String test5 = "{[]}";
        String test6 = ""; // Empty string
        String test7 = null; // Null string

        // Test cases for each solution
        System.out.println("Test Cases for Valid Parentheses:");
        System.out.println("Input: \"" + test1 + "\"");
        System.out.println("1. Stack Approach: " + isValidStack(test1));
        System.out.println("2. Stack with HashMap: " + isValidStackMap(test1));
        System.out.println("3. Deque Approach: " + isValidDeque(test1));
        System.out.println("4. Optimized Stack Approach: " + isValidStackOptimized(test1));
        System.out.println("5. Iterative Counting (Not Recommended): " + isValidCount(test1)); //Added for completeness, but not recommended

        System.out.println("\nInput: \"" + test2 + "\"");
        System.out.println("1. Stack Approach: " + isValidStack(test2));
        System.out.println("2. Stack with HashMap: " + isValidStackMap(test2));
        System.out.println("3. Deque Approach: " + isValidDeque(test2));
        System.out.println("4. Optimized Stack Approach: " + isValidStackOptimized(test2));
        System.out.println("5. Iterative Counting (Not Recommended): " + isValidCount(test2));

        System.out.println("\nInput: \"" + test3 + "\"");
        System.out.println("1. Stack Approach: " + isValidStack(test3));
        System.out.println("2. Stack with HashMap: " + isValidStackMap(test3));
        System.out.println("3. Deque Approach: " + isValidDeque(test3));
        System.out.println("4. Optimized Stack Approach: " + isValidStackOptimized(test3));
        System.out.println("5. Iterative Counting (Not Recommended): " + isValidCount(test3));

        System.out.println("\nInput: \"" + test4 + "\"");
        System.out.println("1. Stack Approach: " + isValidStack(test4));
        System.out.println("2. Stack with HashMap: " + isValidStackMap(test4));
        System.out.println("3. Deque Approach: " + isValidDeque(test4));
        System.out.println("4. Optimized Stack Approach: " + isValidStackOptimized(test4));
        System.out.println("5. Iterative Counting (Not Recommended): " + isValidCount(test4));

        System.out.println("\nInput: \"" + test5 + "\"");
        System.out.println("1. Stack Approach: " + isValidStack(test5));
        System.out.println("2. Stack with HashMap: " + isValidStackMap(test5));
        System.out.println("3. Deque Approach: " + isValidDeque(test5));
        System.out.println("4. Optimized Stack Approach: " + isValidStackOptimized(test5));
        System.out.println("5. Iterative Counting (Not Recommended): " + isValidCount(test5));

        System.out.println("\nInput: \"" + test6 + "\" (Empty String)");
        System.out.println("1. Stack Approach: " + isValidStack(test6));
        System.out.println("2. Stack with HashMap: " + isValidStackMap(test6));
        System.out.println("3. Deque Approach: " + isValidDeque(test6));
        System.out.println("4. Optimized Stack Approach: " + isValidStackOptimized(test6));
        System.out.println("5. Iterative Counting (Not Recommended): " + isValidCount(test6));

        System.out.println("\nInput: \"" + test7 + "\" (Null String)");
        System.out.println("1. Stack Approach: " + isValidStack(test7));
        System.out.println("2. Stack with HashMap: " + isValidStackMap(test7));
        System.out.println("3. Deque Approach: " + isValidDeque(test7));
        System.out.println("4. Optimized Stack Approach: " + isValidStackOptimized(test7));
        System.out.println("5. Iterative Counting (Not Recommended): " + isValidCount(test7));
    }

    /**
     * 1. Stack Approach:
     * Uses a stack to keep track of opening brackets.  When a closing bracket is
     * encountered, it checks if the stack's top element is the matching opening
     * bracket.
     *
     * Time Complexity: O(n) - where n is the length of the string.
     * Space Complexity: O(n) - in the worst case, all characters are opening brackets.
     */
    public static boolean isValidStack(String s) {
        if (s == null || s.length() == 0) {
            return true; // Empty string is considered valid
        }

        Stack<Character> stack = new Stack<>();

        for (char c : s.toCharArray()) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c); // Push opening bracket onto the stack
            } else if (c == ')' || c == ']' || c == '}') {
                if (stack.isEmpty()) {
                    return false; // No matching opening bracket
                }
                char top = stack.pop();
                if ((c == ')' && top != '(') ||
                        (c == ']' && top != '[') ||
                        (c == '}' && top != '{')) {
                    return false; // Mismatched brackets
                }
            }
        }
        return stack.isEmpty(); // Stack should be empty if all brackets are matched
    }

    /**
     * 2. Stack with HashMap:
     * Similar to the first approach, but uses a HashMap to store the mapping
     * between closing and opening brackets.  This can make the code slightly
     * more readable and easier to maintain.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public static boolean isValidStackMap(String s) {
        if (s == null || s.length() == 0) {
            return true;
        }

        Stack<Character> stack = new Stack<>();
        Map<Character, Character> map = new HashMap<>();
        map.put(')', '(');
        map.put(']', '[');
        map.put('}', '{');

        for (char c : s.toCharArray()) {
            if (map.containsValue(c)) { // If it is an opening bracket
                stack.push(c);
            } else if (map.containsKey(c)) { // If it is a closing bracket
                if (stack.isEmpty() || stack.pop() != map.get(c)) {
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }

    /**
     * 3. Deque Approach:
     * Uses a Deque (ArrayDeque) instead of a Stack.  A Deque can be used as a Stack,
     * and in some cases, it might offer better performance.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    public static boolean isValidDeque(String s) {
        if (s == null || s.length() == 0) {
            return true;
        }

        Deque<Character> deque = new ArrayDeque<>(); // Use ArrayDeque as a Stack
        for (char c : s.toCharArray()) {
            if (c == '(' || c == '[' || c == '{') {
                deque.push(c);
            } else if (c == ')' || c == ']' || c == '}') {
                if (deque.isEmpty()) {
                    return false;
                }
                char top = deque.pop();
                if ((c == ')' && top != '(') ||
                        (c == ']' && top != '[') ||
                        (c == '}' && top != '{')) {
                    return false;
                }
            }
        }
        return deque.isEmpty();
    }

    /**
     * 4. Optimized Stack Approach:
     * This approach optimizes the first stack approach by pushing the *expected*
     * closing bracket onto the stack instead of the opening bracket. This can
     * simplify the logic inside the loop.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n) -  In the worst case, all characters are opening brackets.
     */
    public static boolean isValidStackOptimized(String s) {
        if (s == null || s.length() == 0) {
            return true;
        }

        Stack<Character> stack = new Stack<>();

        for (char c : s.toCharArray()) {
            if (c == '(') {
                stack.push(')'); // Push the expected closing parenthesis
            } else if (c == '[') {
                stack.push(']');
            } else if (c == '{') {
                stack.push('}');
            } else if (stack.isEmpty() || stack.pop() != c) {
                // If it's a closing bracket, check if the stack is empty
                // or if the top of the stack doesn't match.
                return false;
            }
        }
        return stack.isEmpty();
    }

    /**
     * 5. Iterative Counting (Not Recommended):
     * This approach attempts to solve the problem by counting the occurrences of
     * each type of bracket.  However, this method is flawed because it doesn't
     * guarantee the correct order of brackets.  For example, it would incorrectly
     * validate "[(])".  It's included here for demonstration of an incorrect approach.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1) -  Uses a constant amount of extra space.
     *
     * Note: This method is INCORRECT and should not be used in practice.
     */
    public static boolean isValidCount(String s) {
        if (s == null) {
            return true; //handles null
        }
        int count1 = 0, count2 = 0, count3 = 0;
        for (char c : s.toCharArray()) {
            if (c == '(') count1++;
            else if (c == ')') count1--;
            else if (c == '[') count2++;
            else if (c == ']') count2--;
            else if (c == '{') count3++;
            else if (c == '}') count3--;
        }
        return count1 == 0 && count2 == 0 && count3 == 0;
    }
}