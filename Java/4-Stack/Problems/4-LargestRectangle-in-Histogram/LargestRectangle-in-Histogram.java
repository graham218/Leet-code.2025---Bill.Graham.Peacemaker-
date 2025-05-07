import java.util.ArrayDeque;
import java.util.Deque;
import java.util.LinkedList;
import java.util.Stack;

public class LargestRectangleInHistogram {

    /**
     * Approach 1: Brute Force
     *
     * Description:
     * For each bar in the histogram, consider it as the minimum height of a potential rectangle.
     * Expand to the left and right as far as possible, as long as the heights of the bars
     * are greater than or equal to the current bar's height. Calculate the area for each
     * such rectangle and keep track of the maximum area found.
     *
     * Time Complexity: O(n^2), where n is the number of bars in the histogram.
     * Space Complexity: O(1)
     */
    public int largestRectangleAreaBruteForce(int[] heights) {
        int maxArea = 0;
        int n = heights.length;

        for (int i = 0; i < n; i++) {
            int minHeight = heights[i];
            for (int j = i; j < n; j++) {
                minHeight = Math.min(minHeight, heights[j]); // Find the minimum height in the current range
                maxArea = Math.max(maxArea, minHeight * (j - i + 1)); // Calculate area and update maxArea
            }
        }
        return maxArea;
    }

    /**
     * Approach 2: Divide and Conquer
     *
     * Description:
     * Recursively divide the histogram into subproblems. For each subproblem, find the
     * minimum height bar. The maximum area rectangle can be formed by:
     * 1. The area of the rectangle with the minimum height bar.
     * 2. The maximum area in the left subproblem.
     * 3. The maximum area in the right subproblem.
     *
     * Time Complexity: O(n log n) in the average case, O(n^2) in the worst case.
     * Space Complexity: O(n) due to the recursion stack.
     */
    public int largestRectangleAreaDivideAndConquer(int[] heights) {
        if (heights == null || heights.length == 0) {
            return 0;
        }
        return divideAndConquer(heights, 0, heights.length - 1);
    }

    private int divideAndConquer(int[] heights, int start, int end) {
        if (start > end) {
            return 0;
        }

        int minIndex = findMinIndex(heights, start, end); // Find index of the minimum height bar
        int currentArea = heights[minIndex] * (end - start + 1); // Area with min height bar

        // Recursively find max area in left and right subproblems
        int leftArea = divideAndConquer(heights, start, minIndex - 1);
        int rightArea = divideAndConquer(heights, minIndex + 1, end);

        return Math.max(currentArea, Math.max(leftArea, rightArea)); // Return the maximum of the three areas
    }

    private int findMinIndex(int[] heights, int start, int end) {
        int minIndex = start;
        for (int i = start + 1; i <= end; i++) {
            if (heights[i] < heights[minIndex]) {
                minIndex = i;
            }
        }
        return minIndex;
    }

    /**
     * Approach 3: Stack
     *
     * Description:
     * Use a stack to keep track of the indices of the bars. The stack maintains the property
     * that the heights of the bars corresponding to the indices in the stack are
     * monotonically increasing. For each bar, if its height is less than the height of the
     * bar at the top of the stack, we pop the stack and calculate the area of the rectangle
     * with the popped bar as the minimum height.
     *
     * Time Complexity: O(n), where n is the number of bars in the histogram.
     * Space Complexity: O(n) for the stack.
     */
    public int largestRectangleAreaStack(int[] heights) {
        int maxArea = 0;
        int n = heights.length;
        Stack<Integer> stack = new Stack<>();
        int i = 0;

        while (i < n || !stack.isEmpty()) { // Iterate until all bars are processed and stack is empty
            if (i < n && (stack.isEmpty() || heights[i] >= heights[stack.peek()])) {
                stack.push(i++); // Push current bar's index if stack is empty or current bar is taller
            } else {
                int top = stack.pop(); // Pop the top of the stack
                // Calculate area with popped bar as minimum height
                int area = heights[top] * (stack.isEmpty() ? i : i - stack.peek() - 1);
                maxArea = Math.max(maxArea, area); // Update maxArea
            }
        }
        return maxArea;
    }

    /**
     * Approach 4: Optimized Stack
     *
     * Description:
     * Similar to the Stack approach, but adds dummy bars with height 0 at the beginning and end
     * of the histogram. This simplifies the logic by ensuring that all bars are processed
     * and the stack is emptied at the end.  This avoids the extra check `i < n || !stack.isEmpty()`
     * in the while loop.
     *
     * Time Complexity: O(n), where n is the number of bars in the histogram.
     * Space Complexity: O(n) for the stack.
     */
    public int largestRectangleAreaOptimizedStack(int[] heights) {
        int maxArea = 0;
        int n = heights.length;
        int[] modifiedHeights = new int[n + 2]; // Create a new array with 0 padding
        System.arraycopy(heights, 0, modifiedHeights, 1, n); // Copy original heights to the new array
        Deque<Integer> stack = new ArrayDeque<>(); // Use ArrayDeque as a Stack
        // The stack will store indices of the modifiedHeights array.
        for (int i = 0; i < modifiedHeights.length; i++) {
            while (!stack.isEmpty() && modifiedHeights[i] < modifiedHeights[stack.peek()]) {
                int height = modifiedHeights[stack.pop()];
                int width = i - stack.peek() - 1;
                maxArea = Math.max(maxArea, height * width);
            }
            stack.push(i);
        }
        return maxArea;
    }

    /**
     * Approach 5: Using Left and Right Smaller Elements
     *
     * Description:
     * For each bar, find the index of the first smaller bar to its left and the first smaller
     * bar to its right.  Then calculate the area of the rectangle with that bar as the minimum
     * height. This approach pre-computes the left and right boundaries for each bar.
     *
     * Time Complexity: O(n), where n is the number of bars in the histogram.
     * Space Complexity: O(n) for the leftSmaller and rightSmaller arrays.
     */
    public int largestRectangleAreaLeftRight(int[] heights) {
        int n = heights.length;
        int[] leftSmaller = new int[n];  // Stores the index of the first smaller element on the left
        int[] rightSmaller = new int[n]; // Stores the index of the first smaller element on the right
        int maxArea = 0;

        // Calculate left smaller elements
        Deque<Integer> stack = new ArrayDeque<>();
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && heights[stack.peek()] >= heights[i]) {
                stack.pop();
            }
            leftSmaller[i] = stack.isEmpty() ? -1 : stack.peek();
            stack.push(i);
        }

        stack.clear(); // Clear the stack for calculating right smaller elements

        // Calculate right smaller elements
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && heights[stack.peek()] >= heights[i]) {
                stack.pop();
            }
            rightSmaller[i] = stack.isEmpty() ? n : stack.peek();
            stack.push(i);
        }

        // Calculate maximum area
        for (int i = 0; i < n; i++) {
            int width = rightSmaller[i] - leftSmaller[i] - 1;
            maxArea = Math.max(maxArea, heights[i] * width);
        }
        return maxArea;
    }

    public static void main(String[] args) {
        LargestRectangleInHistogram solution = new LargestRectangleInHistogram();
        int[] heights = {2, 1, 5, 6, 2, 3};

        // Test with different approaches
        System.out.println("Brute Force: " + solution.largestRectangleAreaBruteForce(heights)); // Output: 10
        System.out.println("Divide and Conquer: " + solution.largestRectangleAreaDivideAndConquer(heights)); // Output: 10
        System.out.println("Stack: " + solution.largestRectangleAreaStack(heights)); // Output: 10
        System.out.println("Optimized Stack: " + solution.largestRectangleAreaOptimizedStack(heights)); // Output: 10
        System.out.println("Left Right: " + solution.largestRectangleAreaLeftRight(heights)); // Output: 10

        int[] heights2 = {0, 9};
        System.out.println("Brute Force 2: " + solution.largestRectangleAreaBruteForce(heights2));
        System.out.println("Divide and Conquer 2: " + solution.largestRectangleAreaDivideAndConquer(heights2));
        System.out.println("Stack 2: " + solution.largestRectangleAreaStack(heights2));
        System.out.println("Optimized Stack 2: " + solution.largestRectangleAreaOptimizedStack(heights2));
        System.out.println("Left Right 2: " + solution.largestRectangleAreaLeftRight(heights2));
    }
}

