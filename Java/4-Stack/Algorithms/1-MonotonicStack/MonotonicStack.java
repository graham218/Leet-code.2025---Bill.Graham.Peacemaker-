import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.List;

/**
 * Monotonic Stack is a data structure that maintains a monotonic (either entirely
 * increasing or entirely decreasing) order of elements. It is useful for solving
 * problems that involve finding the next greater/smaller element for each element
 * in an array.
 *
 * Here are five different approaches to demonstrate the concept and variations of
 * Monotonic Stack:
 */
public class MonotonicStack {

    public static void main(String[] args) {
        int[] arr = { 4, 5, 2, 10, 8 };
        System.out.println("Input Array: " + Arrays.toString(arr));

        // 1. Next Greater Element (Using Monotonic Increasing Stack)
        int[] nextGreater = findNextGreaterElements(arr);
        System.out.println("1. Next Greater Elements: " + Arrays.toString(nextGreater));

        // 2. Next Smaller Element (Using Monotonic Decreasing Stack)
        int[] nextSmaller = findNextSmallerElements(arr);
        System.out.println("2. Next Smaller Elements: " + Arrays.toString(nextSmaller));

        // 3. Previous Greater Element (Variation of Monotonic Stack)
        int[] prevGreater = findPreviousGreaterElements(arr);
        System.out.println("3. Previous Greater Elements: " + Arrays.toString(prevGreater));

        // 4. Previous Smaller Element (Variation of Monotonic Stack)
        int[] prevSmaller = findPreviousSmallerElements(arr);
        System.out.println("4. Previous Smaller Elements: " + Arrays.toString(prevSmaller));

        // 5. Largest Rectangular Area in Histogram (Application of Monotonic Stack)
        int[] histogram = { 2, 1, 5, 6, 2, 3 };
        int maxArea = largestRectangleArea(histogram);
        System.out.println("5. Largest Rectangular Area in Histogram: " + maxArea);
    }

    /**
     * 1. Next Greater Element:
     * Finds the next greater element for each element in the input array.
     * Uses a monotonic decreasing stack.
     *
     * @param arr The input array.
     * @return An array where each element is the next greater element for the
     * corresponding element in the input array. If no greater element
     * exists, -1 is used.
     */
    public static int[] findNextGreaterElements(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Deque<Integer> stack = new ArrayDeque<>(); // Monotonic decreasing stack (stores indices)

        // Iterate from right to left
        for (int i = n - 1; i >= 0; i--) {
            // Pop elements from the stack which are smaller than the current element.
            while (!stack.isEmpty() && arr[stack.peek()] <= arr[i]) {
                stack.pop();
            }
            // If stack is empty, no greater element exists to the right
            result[i] = stack.isEmpty() ? -1 : arr[stack.peek()];
            stack.push(i); // Push the current element's index
        }
        return result;
    }

    /**
     * 2. Next Smaller Element:
     * Finds the next smaller element for each element in the input array.
     * Uses a monotonic increasing stack.
     *
     * @param arr The input array.
     * @return An array where each element is the next smaller element for the
     * corresponding element in the input array. If no smaller element
     * exists, -1 is used.
     */
    public static int[] findNextSmallerElements(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Deque<Integer> stack = new ArrayDeque<>(); // Monotonic increasing stack (stores indices)

        // Iterate from right to left
        for (int i = n - 1; i >= 0; i--) {
            // Pop elements from the stack which are greater than or equal to the current element.
            while (!stack.isEmpty() && arr[stack.peek()] >= arr[i]) {
                stack.pop();
            }
            // If stack is empty, no smaller element exists to the right
            result[i] = stack.isEmpty() ? -1 : arr[stack.peek()];
            stack.push(i); // Push the current element's index
        }
        return result;
    }

    /**
     * 3. Previous Greater Element:
     * Finds the previous greater element for each element in the input array.
     * Uses a monotonic decreasing stack.
     *
     * @param arr The input array.
     * @return An array where each element is the previous greater element for the
     * corresponding element in the input array. If no greater element
     * exists, -1 is used.
     */
    public static int[] findPreviousGreaterElements(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Deque<Integer> stack = new ArrayDeque<>(); // Monotonic decreasing stack (stores indices)

        // Iterate from left to right
        for (int i = 0; i < n; i++) {
            // Pop elements from the stack which are smaller than or equal to the current element.
            while (!stack.isEmpty() && arr[stack.peek()] <= arr[i]) {
                stack.pop();
            }
            // If stack is empty, no greater element exists to the left
            result[i] = stack.isEmpty() ? -1 : arr[stack.peek()];
            stack.push(i); // Push the current element's index
        }
        return result;
    }

    /**
     * 4. Previous Smaller Element:
     * Finds the previous smaller element for each element in the input array.
     * Uses a monotonic increasing stack.
     *
     * @param arr The input array.
     * @return An array where each element is the previous smaller element for the
     * corresponding element in the input array. If no smaller element
     * exists, -1 is used.
     */
    public static int[] findPreviousSmallerElements(int[] arr) {
        int n = arr.length;
        int[] result = new int[n];
        Deque<Integer> stack = new ArrayDeque<>(); // Monotonic increasing stack (stores indices)

        // Iterate from left to right
        for (int i = 0; i < n; i++) {
            // Pop elements from the stack which are greater than or equal to the current element
            while (!stack.isEmpty() && arr[stack.peek()] >= arr[i]) {
                stack.pop();
            }
            // If stack is empty, no smaller element exists to the left
            result[i] = stack.isEmpty() ? -1 : arr[stack.peek()];
            stack.push(i); // Push the current element's index
        }
        return result;
    }

    /**
     * 5. Largest Rectangular Area in a Histogram:
     * Finds the largest rectangular area in a histogram using a monotonic stack.
     * This is a classic application of the monotonic stack.
     *
     * @param heights The array of histogram heights.
     * @return The largest rectangular area in the histogram.
     */
    public static int largestRectangleArea(int[] heights) {
        int n = heights.length;
        int maxArea = 0;
        Deque<Integer> stack = new ArrayDeque<>(); // Monotonic increasing stack (stores indices)
        int i = 0;

        while (i < n || !stack.isEmpty()) {
            if (i < n && (stack.isEmpty() || heights[i] >= heights[stack.peek()])) {
                stack.push(i++); // Push the current index if it's greater or equal to the top of stack
            } else {
                // Calculate area when a smaller height is encountered or stack is empty
                int top = stack.pop();
                // width is i if stack is empty, otherwise the diff between current and top of stack.
                int width = stack.isEmpty() ? i : i - stack.peek() - 1;
                int area = heights[top] * width;
                maxArea = Math.max(maxArea, area);
            }
        }
        return maxArea;
    }
}
