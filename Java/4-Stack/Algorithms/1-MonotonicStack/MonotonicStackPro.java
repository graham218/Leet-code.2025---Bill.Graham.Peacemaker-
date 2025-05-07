import java.util.ArrayDeque;
import java.util.Deque;
import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

public class MonotonicStack {

    /**
     * **Approach 1: Next Greater Element (Basic Monotonic Stack)**
     * * **Real-world application:** Finding stock price peaks for analysis.
     * * **Description:** This method calculates the next greater element for each element in the input array.
     * A decreasing monotonic stack is used.
     *
     * @param arr The input array of integers.
     * @return An array where each element is the next greater element to the right in the input array.
     * Returns -1 if no greater element exists.
     */
    public static int[] nextGreaterElement(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Arrays.fill(result, -1); // Initialize result array with -1
        Deque<Integer> stack = new ArrayDeque<>(); // Use ArrayDeque as a stack (faster than Stack class)

        for (int i = 0; i < n; i++) {
            // Maintain a decreasing monotonic stack.
            while (!stack.isEmpty() && arr[i] > arr[stack.peek()]) {
                int index = stack.pop();
                result[index] = arr[i]; // Found the next greater element
            }
            stack.push(i); // Push the *index*, not the value
        }
        return result;
    }

    /**
     * **Approach 2: Previous Smaller Element**
     * * **Real-world application:** Finding the previous dip in sensor data.
     * * **Description:** Calculates the previous smaller element for each element in the input array.
     * An increasing monotonic stack is used.
     *
     * @param arr The input array of integers.
     * @return An array where each element is the previous smaller element to the left in the input array.
     * Returns -1 if no smaller element exists.
     */
    public static int[] previousSmallerElement(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Arrays.fill(result, -1);
        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            // Maintain an increasing monotonic stack
            while (!stack.isEmpty() && arr[i] < arr[stack.peek()]) {
                stack.pop();
            }
            if (!stack.isEmpty()) {
                result[i] = arr[stack.peek()]; // Found previous smaller element
            }
            stack.push(i);
        }
        return result;
    }

    /**
     * **Approach 3: Largest Rectangle in Histogram**
     * * **Real-world application:** Optimizing billboard size in advertising.
     * * **Description:** Given an array of histogram bar heights, find the largest rectangular area possible.
     * This uses a monotonic stack to efficiently find the left and right boundaries
     * for each bar where it is the minimum height.
     *
     * @param heights The input array of histogram bar heights.
     * @return The largest rectangular area.
     */
    public static int largestRectangleArea(int[] heights) {
        int n = heights.length;
        int maxArea = 0;
        Deque<Integer> stack = new ArrayDeque<>();
        int[] left = new int[n];  // left[i] stores the index of the first bar *smaller* than heights[i] to the left
        int[] right = new int[n]; // right[i] stores the index of the first bar *smaller* than heights[i] to the right

        // Calculate left boundaries using a monotonic increasing stack
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && heights[stack.peek()] >= heights[i]) {
                stack.pop();
            }
            left[i] = stack.isEmpty() ? 0 : stack.peek() + 1;
            stack.push(i);
        }

        stack.clear(); // Clear the stack for the next calculation

        // Calculate right boundaries using a monotonic increasing stack
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && heights[stack.peek()] >= heights[i]) {
                stack.pop();
            }
            right[i] = stack.isEmpty() ? n : stack.peek();
            stack.push(i);
        }

        // Calculate the area for each bar and update maxArea
        for (int i = 0; i < n; i++) {
            int width = right[i] - left[i];
            int area = heights[i] * width;
            maxArea = Math.max(maxArea, area);
        }
        return maxArea;
    }

    /**
     * **Approach 4: Stock Span Problem**
     * * **Real-world application:** Analyzing stock price trends over a period.
     * * **Description:** Given a series of daily stock prices, calculate the span for each day.
     * The span of the stock's price today is defined as the maximum number of consecutive days
     * (up to today) for which the price of the stock on the current day was greater than or equal to its price on the given day.
     * Uses a decreasing monotonic stack.
     *
     * @param prices The array of stock prices for each day.
     * @return An array of spans for each day.
     */
    public static int[] stockSpan(int[] prices) {
        int n = prices.length;
        int[] span = new int[n];
        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            int price = prices[i];
            // Maintain a decreasing monotonic stack of *indices*
            while (!stack.isEmpty() && price >= prices[stack.peek()]) {
                stack.pop();
            }
            span[i] = stack.isEmpty() ? i + 1 : i - stack.peek();
            stack.push(i);
        }
        return span;
    }

    /**
     * **Approach 5: Remove K Digits**
     * * **Real-world application:** Optimizing numerical values in financial systems.
     * * **Description:** Given a non-negative integer represented as a string, remove k digits
     * such that the new number is the smallest possible.  Uses a monotonic increasing stack.
     *
     * @param num The string representation of the non-negative integer.
     * @param k   The number of digits to remove.
     * @return The string representation of the smallest possible number after removing k digits.
     */
    public static String removeKDigits(String num, int k) {
        if (k == num.length()) {
            return "0";
        }

        Deque<Character> stack = new ArrayDeque<>();
        for (char digit : num.toCharArray()) {
            // Maintain a monotonic increasing stack
            while (k > 0 && !stack.isEmpty() && digit < stack.peekLast()) {
                stack.removeLast(); // Use removeLast() for Deque
                k--;
            }
            stack.addLast(digit); // Use addLast() for Deque
        }

        // If we haven't removed enough digits, remove from the tail
        while (k > 0) {
            stack.removeLast();
            k--;
        }

        // Build the result string, skipping leading zeros
        StringBuilder result = new StringBuilder();
        boolean leadingZero = true;
        for (char digit : stack) {
            if (leadingZero && digit == '0') {
                continue;
            }
            leadingZero = false;
            result.append(digit);
        }

        return result.length() == 0 ? "0" : result.toString();
    }

    public static void main(String[] args) {
        // Example Usage (Added more test cases)
        System.out.println("--- Next Greater Element ---");
        System.out.println(Arrays.toString(nextGreaterElement(new int[]{4, 5, 2, 25, 7, 8, 20}))); // [5, 25, 25, -1, 8, 20, -1]
        System.out.println(Arrays.toString(nextGreaterElement(new int[]{1, 3, 2, 4}))); // [3, 4, 4, -1]
        System.out.println(Arrays.toString(nextGreaterElement(new int[]{5, 4, 3, 2, 1}))); // [-1, -1, -1, -1, -1]

        System.out.println("\n--- Previous Smaller Element ---");
        System.out.println(Arrays.toString(previousSmallerElement(new int[]{4, 5, 2, 25, 7, 8, 20}))); // [-1, 4, -1, 2, 2, 7, 8]
        System.out.println(Arrays.toString(previousSmallerElement(new int[]{1, 3, 2, 4}))); // [-1, 1, 1, 2]
        System.out.println(Arrays.toString(previousSmallerElement(new int[]{5, 4, 3, 2, 1}))); // [-1, -1, -1, -1, -1]

        System.out.println("\n--- Largest Rectangle Area ---");
        System.out.println(largestRectangleArea(new int[]{2, 1, 5, 6, 2, 3})); // 10
        System.out.println(largestRectangleArea(new int[]{2, 4})); // 4
        System.out.println(largestRectangleArea(new int[]{0, 0, 0, 0, 0})); //0

        System.out.println("\n--- Stock Span ---");
        System.out.println(Arrays.toString(stockSpan(new int[]{100, 80, 60, 70, 60, 75, 85}))); // [1, 1, 1, 2, 1, 4, 6]
        System.out.println(Arrays.toString(stockSpan(new int[]{10, 4, 5, 90, 120, 80}))); // [1, 1, 2, 4, 5, 1]
        System.out.println(Arrays.toString(stockSpan(new int[]{1,2,3,4,5}))); // [1, 2, 3, 4, 5]

        System.out.println("\n--- Remove K Digits ---");
        System.out.println(removeKDigits("1432219", 3)); // "1219"
        System.out.println(removeKDigits("10200", 1)); // "200"
        System.out.println(removeKDigits("10", 2));   // "0"
        System.out.println(removeKDigits("1111111", 3)); // "1111"
        System.out.println(removeKDigits("1231234", 3)); // "11234"
        System.out.println(removeKDigits("987654321", 5)); // 4321
        System.out.println(removeKDigits("123456789", 5)); // 1234
    }
}

