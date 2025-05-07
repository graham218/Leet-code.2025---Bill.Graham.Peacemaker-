import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class NextGreaterElement {

    public static void main(String[] args) {
        int[] arr = {4, 6, 3, 2, 8, 1};
        int[] nextGreaterElement;

        // Approach 1: Brute Force
        nextGreaterElement = nextGreaterElementBruteForce(arr);
        System.out.println("Next Greater Element (Brute Force): " + Arrays.toString(nextGreaterElement)); // Output: [6, 8, 8, 8, -1, -1]

        // Approach 2: Stack
        nextGreaterElement = nextGreaterElementStack(arr);
        System.out.println("Next Greater Element (Stack): " + Arrays.toString(nextGreaterElement)); // Output: [6, 8, 8, 8, -1, -1]

        // Approach 3: Optimized Stack (Handles Duplicates)
        nextGreaterElement = nextGreaterElementOptimizedStack(arr);
        System.out.println("Next Greater Element (Optimized Stack): " + Arrays.toString(nextGreaterElement));

        // Approach 4: Using HashMap for mapping (for finding NGE of specific elements)
        int[] resultWithMap = nextGreaterElementWithMap(arr);
        System.out.println("Next Greater Element (HashMap): " + Arrays.toString(resultWithMap));

        // Approach 5: Circular Array
        int[] circularArray = {1, 5, 3, 6, 4};
        nextGreaterElement = nextGreaterElementCircular(circularArray);
        System.out.println("Next Greater Element (Circular Array): " + Arrays.toString(nextGreaterElement)); //Output: [5, 6, 6, -1, 5]
    }

    /**
     * Approach 1: Brute Force
     * -   Time Complexity: O(n^2)
     * -   Space Complexity: O(n)
     * -   Real-world application: Simple data analysis where you need to compare each data point with every other data point.  For example, finding the next higher stock price for each day in a short time frame.
     *
     * @param arr The input array.
     * @return An array where each element is the next greater element in the input array.
     */
    public static int[] nextGreaterElementBruteForce(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            result[i] = -1; // Default value if no greater element is found
            for (int j = i + 1; j < n; j++) {
                if (arr[j] > arr[i]) {
                    result[i] = arr[j];
                    break;
                }
            }
        }
        return result;
    }

    /**
     * Approach 2: Stack
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(n)
     * -   Real-world application: Processing real-time data streams, such as stock prices or sensor readings, where you need to efficiently track the next significant event.  For example, in a stock market analysis, identify the next peak price after each day.
     *
     * @param arr The input array.
     * @return An array where each element is the next greater element in the input array.
     */
    public static int[] nextGreaterElementStack(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Arrays.fill(result, -1); // Initialize result array with -1
        Stack<Integer> stack = new Stack<>();

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && arr[i] > arr[stack.peek()]) {
                result[stack.pop()] = arr[i];
            }
            stack.push(i);
        }
        return result;
    }

    /**
     * Approach 3: Optimized Stack (Handles Duplicates)
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(n)
     * -   Real-world application: Analyzing data with duplicate values, such as website traffic logs or sales data, where you need to find the next greater event, even if duplicates exist.  For example, finding the next higher sales amount for each transaction, even if some transactions have the same amount.
     *
     * @param arr The input array.
     * @return An array where each element is the next greater element in the input array.
     */
    public static int[] nextGreaterElementOptimizedStack(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Arrays.fill(result, -1);
        Stack<Integer> stack = new Stack<>();

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && arr[i] > arr[stack.peek()]) {
                result[stack.pop()] = arr[i];
            }
            // Important: Push the *index*, not the value.  This allows us to handle duplicates correctly.
            stack.push(i);
        }
        return result;
    }

    /**
     * Approach 4: Using HashMap for mapping (for finding NGE of specific elements)
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(n)
     * -   Real-world application:  Useful when you need to quickly look up the next greater element for specific values, rather than for every element in the array.  For example, in a system that monitors stock prices, you might want to quickly find the next higher price for a specific set of target stocks.
     *
     * @param arr The input array.
     * @return A Map where key is the element and value is the next greater element.
     */
    public static int[] nextGreaterElementWithMap(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Arrays.fill(result, -1);
        Stack<Integer> stack = new Stack<>();
        Map<Integer, Integer> ngeMap = new HashMap<>(); // Map to store element and its NGE

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && arr[i] > arr[stack.peek()]) {
                int poppedIndex = stack.pop();
                ngeMap.put(arr[poppedIndex], arr[i]); // Store the mapping
                result[poppedIndex] = arr[i];
            }
            stack.push(i);
        }

        return result;
    }

    /**
     * Approach 5: Circular Array
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(n)
     * -   Real-world application: Analyzing cyclic data, such as server activity logs or network traffic patterns, where the last element is considered to be adjacent to the first element. For example, finding the next peak server load in a 24-hour cycle.
     *
     * @param arr The input circular array.
     * @return An array where each element is the next greater element in the circular input array.
     */
    public static int[] nextGreaterElementCircular(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Arrays.fill(result, -1);
        Stack<Integer> stack = new Stack<>();

        for (int i = 0; i < 2 * n; i++) { // Iterate twice to simulate circular array
            int index = i % n; // Get the actual index in the array
            while (!stack.isEmpty() && arr[index] > arr[stack.peek()]) {
                result[stack.pop()] = arr[index];
            }
            if (i < n) { // Push only the first 'n' indices
                stack.push(index);
            }
        }
        return result;
    }
}

