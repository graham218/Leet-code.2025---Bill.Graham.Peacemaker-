import java.util.ArrayDeque;
import java.util.Deque;
import java.util.stream.IntStream;
import java.util.Arrays;
import java.util.function.IntFunction;

public class LargestRectangleInHistogram {

    /**
     * Approach 1: Brute Force
     *
     * Description:
     * The most straightforward approach.  For each bar in the histogram, we consider it as the minimum height
     * of a potential rectangle and expand left and right as far as possible while the heights are greater
     * or equal to the current bar's height.  We calculate the area for each such rectangle and keep track of the maximum.
     *
     * Time Complexity: O(n^2), where n is the number of bars in the histogram.
     * Space Complexity: O(1)
     *
     * Real-world application:
     * -   Useful for a very small dataset or as a baseline for comparing the performance of more optimized algorithms.
     * -   Can be used in simple data analysis scripts where performance is not critical.
     *
     * @param heights The array of bar heights in the histogram.
     * @return The largest rectangular area in the histogram.
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
     * A divide-and-conquer approach.  We find the minimum height bar in the histogram.  The largest rectangle
     * must either:
     * 1.  Include the minimum height bar.
     * 2.  Be entirely to the left of the minimum height bar.
     * 3.  Be entirely to the right of the minimum height bar.
     * We recursively calculate the largest rectangle for the left and right sub-histograms and combine the results.
     *
     * Time Complexity: O(n log n) in the average case, O(n^2) in the worst case (when the array is sorted).
     * Space Complexity: O(n) due to the recursion stack.
     *
     * Real-world application:
     * -   Useful in scenarios where the input data can be effectively divided into subproblems, such as
     * parallel processing of large datasets.
     * -   Can be adapted for distributed computing environments.
     *
     * @param heights The array of bar heights in the histogram.
     * @return The largest rectangular area in the histogram.
     */
    public int largestRectangleAreaDivideAndConquer(int[] heights) {
        if (heights == null || heights.length == 0) {
            return 0;
        }
        return divideAndConquer(heights, 0, heights.length - 1);
    }

    private int divideAndConquer(int[] heights, int left, int right) {
        if (left > right) {
            return 0;
        }

        int minIndex = findMinIndex(heights, left, right); // Find index of the minimum height bar
        int currentArea = heights[minIndex] * (right - left + 1); // Area with the minimum bar

        // Recursively find the largest area in the left and right sub-histograms
        int leftArea = divideAndConquer(heights, left, minIndex - 1);
        int rightArea = divideAndConquer(heights, minIndex + 1, right);

        return Math.max(currentArea, Math.max(leftArea, rightArea)); // Return the maximum of the three areas
    }

    private int findMinIndex(int[] heights, int left, int right) {
        int minIndex = left;
        for (int i = left + 1; i <= right; i++) {
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
     * The most efficient approach.  We use a stack to keep track of the indices of the bars.  The stack maintains the
     * property that the heights of the bars corresponding to the indices in the stack are increasing.
     * When we encounter a bar whose height is less than the height of the bar at the top of the stack, we pop the stack
     * and calculate the area of the rectangle with the popped bar as the minimum height.
     *
     * Time Complexity: O(n), where n is the number of bars in the histogram.
     * Space Complexity: O(n) for the stack.
     *
     * Real-world application:
     * -   This approach is highly optimized and suitable for real-time data processing, such as analyzing stock prices
     * or monitoring system performance metrics where identifying the largest rectangular area within a dataset
     * is crucial.
     * -   Used in applications requiring efficient processing of sequential data.
     *
     * @param heights The array of bar heights in the histogram.
     * @return The largest rectangular area in the histogram.
     */
    public int largestRectangleAreaStack(int[] heights) {
        int maxArea = 0;
        int n = heights.length;
        Deque<Integer> stack = new ArrayDeque<>(); // Use ArrayDeque as a stack (more efficient)
        int i = 0;

        while (i < n || !stack.isEmpty()) { // Iterate until all bars are processed and stack is empty.
            if (i < n && (stack.isEmpty() || heights[i] >= heights[stack.peek()])) {
                stack.push(i++); // Push the current bar's index onto the stack
            } else {
                int top = stack.pop(); // Pop the top of the stack
                // Calculate area with heights[top] as the smallest bar.
                int area = heights[top] * (stack.isEmpty() ? i : i - stack.peek() - 1);
                maxArea = Math.max(maxArea, area); // Update maxArea
            }
        }
        return maxArea;
    }

    /**
     * Approach 4: Stack (Optimized)
     *
     * Description:
     * An optimized version of the stack approach.  To avoid the extra check `i < n` in the loop,
     * we pad the input `heights` array with 0 at the beginning and end. This ensures that all bars
     * are eventually popped from the stack.
     *
     * Time Complexity: O(n), where n is the number of bars in the histogram.
     * Space Complexity: O(n) for the stack.
     *
     * Real-world application:
     * -   This optimized approach is suitable for high-performance applications where minimizing
     * micro-optimizations can lead to noticeable performance gains, such as in high-frequency trading
     * platforms or real-time data analysis systems.
     * -   Useful when dealing with a very large number of histograms.
     *
     * @param heights The array of bar heights in the histogram.
     * @return The largest rectangular area in the histogram.
     */
    public int largestRectangleAreaStackOptimized(int[] heights) {
        int maxArea = 0;
        int n = heights.length;
        int[] paddedHeights = new int[n + 2]; // Create a padded array
        System.arraycopy(heights, 0, paddedHeights, 1, n); // Copy original heights to the middle
        Deque<Integer> stack = new ArrayDeque<>();
        stack.push(0); // Push 0 at the beginning

        for (int i = 1; i <= n + 1; i++) { // Iterate through the padded array
            while (paddedHeights[i] < paddedHeights[stack.peek()]) {
                int top = stack.pop();
                int area = paddedHeights[top] * (i - stack.peek() - 1);
                maxArea = Math.max(maxArea, area);
            }
            stack.push(i);
        }
        return maxArea;
    }

    /**
     * Approach 5: Using Streams (Java 8 and above) - Not ideal for performance critical applications.
     *
     * Description:
     * This approach uses Java 8 streams for a more functional style.  It iterates through each bar and calculates the maximum
     * possible area with that bar as the minimum height.  While concise, this approach is generally less efficient than
     * the stack-based methods due to the overhead of stream operations.
     *
     * Time Complexity: O(n^2) in most practical scenarios due to the nested loops within the stream operations.
     * Space Complexity: O(n) in the worst case, due to the creation of streams and collections.
     *
     * Real-world application:
     * -   Useful for quick prototyping or in applications where code readability and conciseness are prioritized
     * over raw performance.  For example, in data analysis scripts or reporting tools.
     * -   Good for educational purposes to demonstrate functional programming concepts in Java.
     *
     * @param heights The array of bar heights in the histogram.
     * @return The largest rectangular area in the histogram.
     */
    public int largestRectangleAreaStreams(int[] heights) {
        if (heights == null || heights.length == 0) {
            return 0;
        }

        final int n = heights.length; // Make n final
        return IntStream.range(0, n)
                .map(i -> {
                    int minHeight = heights[i];
                    int area = IntStream.range(i, n)
                            .map(j -> {
                                // Calculate minHeight within the lambda
                                int currentMinHeight = heights[i];
                                for (int k = i; k <= j; k++) {
                                    currentMinHeight = Math.min(currentMinHeight, heights[k]);
                                }
                                return currentMinHeight * (j - i + 1);
                            })
                            .max()
                            .orElse(0);
                    return area;
                })
                .max()
                .orElse(0);
    }

    public static void main(String[] args) {
        int[] heights = {2, 1, 5, 6, 2, 3};
        LargestRectangleInHistogram calculator = new LargestRectangleInHistogram();

        System.out.println("Heights: " + Arrays.toString(heights));
        System.out.println("Largest Rectangle Area (Brute Force): " + calculator.largestRectangleAreaBruteForce(heights));
        System.out.println("Largest Rectangle Area (Divide and Conquer): " + calculator.largestRectangleAreaDivideAndConquer(heights));
        System.out.println("Largest Rectangle Area (Stack): " + calculator.largestRectangleAreaStack(heights));
        System.out.println("Largest Rectangle Area (Stack Optimized): " + calculator.largestRectangleAreaStackOptimized(heights));
        System.out.println("Largest Rectangle Area (Streams): " + calculator.largestRectangleAreaStreams(heights));

        // Example with another dataset
        int[] heights2 = {4, 2, 0, 3, 2, 5};
        System.out.println("\nHeights: " + Arrays.toString(heights2));
        System.out.println("Largest Rectangle Area (Brute Force): " + calculator.largestRectangleAreaBruteForce(heights2));
        System.out.println("Largest Rectangle Area (Divide and Conquer): " + calculator.largestRectangleAreaDivideAndConquer(heights2));
        System.out.println("Largest Rectangle Area (Stack): " + calculator.largestRectangleAreaStack(heights2));
        System.out.println("Largest Rectangle Area (Stack Optimized): " + calculator.largestRectangleAreaStackOptimized(heights2));
        System.out.println("Largest Rectangle Area (Streams): " + calculator.largestRectangleAreaStreams(heights2));

        // Example with monotonically increasing heights
        int[] heights3 = {1, 2, 3, 4, 5};
        System.out.println("\nHeights: " + Arrays.toString(heights3));
        System.out.println("Largest Rectangle Area (Brute Force): " + calculator.largestRectangleAreaBruteForce(heights3));
        System.out.println("Largest Rectangle Area (Divide and Conquer): " + calculator.largestRectangleAreaDivideAndConquer(heights3));
        System.out.println("Largest Rectangle Area (Stack): " + calculator.largestRectangleAreaStack(heights3));
        System.out.println("Largest Rectangle Area (Stack Optimized): " + calculator.largestRectangleAreaStackOptimized(heights3));
        System.out.println("Largest Rectangle Area (Streams): " + calculator.largestRectangleAreaStreams(heights3));

        // Example with monotonically decreasing heights
        int[] heights4 = {5, 4, 3, 2, 1};
        System.out.println("\nHeights: " + Arrays.toString(heights4));
        System.out.println("Largest Rectangle Area (Brute Force): " + calculator.largestRectangleAreaBruteForce(heights4));
        System.out.println("Largest Rectangle Area (Divide and Conquer): " + calculator.largestRectangleAreaDivideAndConquer(heights4));
        System.out.println("Largest Rectangle Area (Stack): " + calculator.largestRectangleAreaStack(heights4));
        System.out.println("Largest Rectangle Area (Stack Optimized): " + calculator.largestRectangleAreaStackOptimized(heights4));
        System.out.println("Largest Rectangle Area (Streams): " + calculator.largestRectangleAreaStreams(heights4));

        // Example with repeated heights
        int[] heights5 = {2, 2, 2, 2, 2};
        System.out.println("\nHeights: " + Arrays.toString(heights5));
        System.out.println("Largest Rectangle Area (Brute Force): " + calculator.largestRectangleAreaBruteForce(heights5));
        System.out.println("Largest Rectangle Area (Divide and Conquer): " + calculator.largestRectangleAreaDivideAndConquer(heights5));
        System.out.println("Largest Rectangle Area (Stack): " + calculator.largestRectangleAreaStack(heights5));
        System.out.println("Largest Rectangle Area (Stack Optimized): " + calculator.largestRectangleAreaStackOptimized(heights5));
        System.out.println("Largest Rectangle Area (Streams): " + calculator.largestRectangleAreaStreams(heights5));
    }
}

