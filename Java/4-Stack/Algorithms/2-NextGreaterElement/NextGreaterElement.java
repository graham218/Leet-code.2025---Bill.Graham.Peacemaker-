import java.util.Arrays;
import java.util.Stack;
import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.List;

public class NextGreaterElement {

    public static void main(String[] args) {
        int[] arr = {1, 3, 2, 4};
        int[] result;

        // Approach 1: Brute Force
        result = nextGreaterElementBruteForce(arr);
        System.out.println("Next Greater Element (Brute Force): " + Arrays.toString(result)); // Output: [3, 4, 4, -1]

        // Approach 2: Stack
        result = nextGreaterElementStack(arr);
        System.out.println("Next Greater Element (Stack): " + Arrays.toString(result)); // Output: [3, 4, 4, -1]

        // Approach 3: Stack with HashMap for mapping
        result = nextGreaterElementStackMap(arr);
        System.out.println("Next Greater Element (Stack with Map): " + Arrays.toString(result)); // Output: [3, 4, 4, -1]

        // Approach 4: Optimized Brute Force (Slight improvement, still O(n^2))
        result = nextGreaterElementOptimizedBruteForce(arr);
        System.out.println("Next Greater Element (Optimized Brute Force): " + Arrays.toString(result));

        // Approach 5: Using List and Stack
        List<Integer> resultList = nextGreaterElementsList(arr);
        System.out.println("Next Greater Element (List and Stack): " + resultList);
    }

    // Approach 1: Brute Force
    // - Time Complexity: O(n^2)
    // - Space Complexity: O(n)
    // - Description: For each element, iterate through the rest of the array to find the next greater element.
    public static int[] nextGreaterElementBruteForce(int[] arr) {
        int[] result = new int[arr.length];
        for (int i = 0; i < arr.length; i++) {
            result[i] = -1; // Default value if no greater element is found
            for (int j = i + 1; j < arr.length; j++) {
                if (arr[j] > arr[i]) {
                    result[i] = arr[j];
                    break; // Once we find the next greater, no need to continue
                }
            }
        }
        return result;
    }

    // Approach 2: Stack
    // - Time Complexity: O(n)
    // - Space Complexity: O(n) in the worst case (if the array is sorted in descending order)
    // - Description: Uses a stack to keep track of elements.  For each element, pop elements from the stack
    //              that are smaller than the current element (these are the next greater elements for the popped elements).
    public static int[] nextGreaterElementStack(int[] arr) {
        int[] result = new int[arr.length];
        Stack<Integer> stack = new Stack<>();
        for (int i = arr.length - 1; i >= 0; i--) { // Iterate from right to left
            while (!stack.isEmpty() && stack.peek() <= arr[i]) {
                stack.pop(); // Pop elements that are not greater than the current element
            }
            result[i] = stack.isEmpty() ? -1 : stack.peek(); // If stack is empty, no greater element
            stack.push(arr[i]); // Push the current element onto the stack
        }
        return result;
    }

    // Approach 3: Stack with HashMap for mapping
    // - Time Complexity: O(n)
    // - Space Complexity: O(n)
    // - Description: Similar to Approach 2, but uses a HashMap to store the mapping between an element and its next greater element.
    //              This can be useful if you need to quickly look up the next greater element for any number in the array.
    public static int[] nextGreaterElementStackMap(int[] arr) {
        int[] result = new int[arr.length];
        Stack<Integer> stack = new Stack<>();
        Map<Integer, Integer> map = new HashMap<>(); // Map to store element -> next greater element
        for (int i = arr.length - 1; i >= 0; i--) {
            while (!stack.isEmpty() && stack.peek() <= arr[i]) {
                stack.pop();
            }
            map.put(arr[i], stack.isEmpty() ? -1 : stack.peek()); // Store the mapping
            stack.push(arr[i]);
        }
        for (int i = 0; i < arr.length; i++) {
            result[i] = map.get(arr[i]); // Retrieve the result from the map
        }
        return result;
    }

    // Approach 4: Optimized Brute Force
    // - Time Complexity: O(n^2), but performs better than the basic brute force in some cases.
    // - Space Complexity: O(n)
    // - Description:  A slight optimization to the brute force approach.  It avoids unnecessary comparisons
    //                by keeping track of the maximum element seen so far. If the current element is greater
    //                than the maximum, we know the next greater element is -1 without checking the rest.
    public static int[] nextGreaterElementOptimizedBruteForce(int[] arr) {
        int[] result = new int[arr.length];
        int max = Integer.MIN_VALUE;

        for (int i = arr.length - 1; i >= 0; i--) {
            if (arr[i] > max) {
                max = arr[i];
                result[i] = -1;
            } else {
                result[i] = -1;
                for (int j = i + 1; j < arr.length; j++) {
                    if (arr[j] > arr[i]) {
                        result[i] = arr[j];
                        break;
                    }
                }
            }
        }
        return result;
    }

    // Approach 5: Using List and Stack
    // - Time Complexity: O(n)
    // - Space Complexity: O(n)
    public static List<Integer> nextGreaterElementsList(int[] arr) {
        List<Integer> result = new ArrayList<>();
        Stack<Integer> stack = new Stack<>();

        for (int i = arr.length - 1; i >= 0; i--) {
            while (!stack.isEmpty() && stack.peek() <= arr[i]) {
                stack.pop();
            }
            result.add(0, stack.isEmpty() ? -1 : stack.peek()); // Insert at the beginning to maintain order
            stack.push(arr[i]);
        }
        return result;
    }
}

