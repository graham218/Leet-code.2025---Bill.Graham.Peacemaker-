import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

public class DailyTemperatures {

    /**
     * Approach 1: Brute Force
     * -   For each day, iterate through the following days to find the next warmer day.
     * -   Time Complexity: O(n^2)
     * -   Space Complexity: O(n) (for the result array)
     */
    public static int[] dailyTemperaturesBruteForce(int[] temperatures) {
        int n = temperatures.length;
        int[] result = new int[n];

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (temperatures[j] > temperatures[i]) {
                    result[i] = j - i;
                    break;
                }
            }
            // If no warmer day is found, result[i] remains 0
        }
        return result;
    }

    /**
     * Approach 2: Stack (Optimized)
     * -   Use a stack to keep track of the indices of days with decreasing temperatures.
     * -   When a warmer day is encountered, pop the days with lower temperatures from the stack.
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(n) (for the stack and result array)
     */
    public static int[] dailyTemperaturesStack(int[] temperatures) {
        int n = temperatures.length;
        int[] result = new int[n];
        Deque<Integer> stack = new ArrayDeque<>(); // Stack to store indices

        for (int i = 0; i < n; i++) {
            // While the stack is not empty and the current day is warmer than the day at the top of the stack
            while (!stack.isEmpty() && temperatures[i] > temperatures[stack.peek()]) {
                int prevIndex = stack.pop(); // Get the index of the previous day
                result[prevIndex] = i - prevIndex; // Calculate the difference (days until warmer)
            }
            stack.push(i); // Push the current day's index onto the stack
        }
        return result;
    }

    /**
     * Approach 3: Optimized Stack (Slightly More Efficient)
     * - Similar to Approach 2, but avoids some redundant stack operations.
     * - Time Complexity: O(n)
     * - Space Complexity: O(n)
     */
    public static int[] dailyTemperaturesOptimizedStack(int[] temperatures) {
        int n = temperatures.length;
        int[] result = new int[n];
        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = n - 1; i >= 0; i--) { // Iterate from right to left
            while (!stack.isEmpty() && temperatures[i] >= temperatures[stack.peek()]) {
                stack.pop();
            }
            result[i] = stack.isEmpty() ? 0 : stack.peek() - i;
            stack.push(i);
        }
        return result;
    }

    /**
     * Approach 4: Using Next Array
     * - Create a 'next' array to store the index of the next warmer day for each temperature.
     * - Iterate through temperatures and update the 'next' array.
     * - Then, calculate the result using the 'next' array.
     * - Time Complexity: O(n * W), where W is the range of temperatures (at most 100, so it's closer to O(n))
     * - Space Complexity: O(n + W)  (O(n) for result and next, O(W) for the next warmer day indexes)
     */
    public static int[] dailyTemperaturesNextArray(int[] temperatures) {
        int n = temperatures.length;
        int[] result = new int[n];
        int[] next = new int[101]; // Array to store the next warmer day's index for each temperature (0 to 100)
        Arrays.fill(next, -1);    // Initialize with -1 (no warmer day found yet)

        for (int i = n - 1; i >= 0; i--) {
            int temp = temperatures[i];
            int warmerIndex = Integer.MAX_VALUE;

            // Find the minimum index of the next warmer day
            for (int t = temp + 1; t <= 100; t++) {
                if (next[t] != -1) {
                    warmerIndex = Math.min(warmerIndex, next[t]);
                }
            }

            if (warmerIndex != Integer.MAX_VALUE) {
                result[i] = warmerIndex - i;
            }
            next[temp] = i; // Store the index of the current day for its temperature
        }
        return result;
    }

    /**
     * Approach 5: Monotonic Stack (Most Efficient)
     * - A variation of the stack approach, emphasizing the monotonic property.
     * - This approach maintains a monotonically decreasing stack of indices.
     * - Time Complexity: O(n)
     * - Space Complexity: O(n)
     */
    public static int[] dailyTemperaturesMonotonicStack(int[] temperatures) {
        int n = temperatures.length;
        int[] result = new int[n];
        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && temperatures[i] > temperatures[stack.peek()]) {
                int index = stack.pop();
                result[index] = i - index;
            }
            stack.push(i);
        }
        return result;
    }

    public static void main(String[] args) {
        int[] temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

        System.out.println("Input Temperatures: " + Arrays.toString(temperatures));

        // Brute Force Approach
        int[] result1 = dailyTemperaturesBruteForce(temperatures);
        System.out.println("Brute Force: " + Arrays.toString(result1));

        // Stack Approach
        int[] result2 = dailyTemperaturesStack(temperatures);
        System.out.println("Stack: " + Arrays.toString(result2));

        // Optimized Stack Approach
        int[] result3 = dailyTemperaturesOptimizedStack(temperatures);
        System.out.println("Optimized Stack: " + Arrays.toString(result3));

        // Next Array Approach
        int[] result4 = dailyTemperaturesNextArray(temperatures);
        System.out.println("Next Array: " + Arrays.toString(result4));

        // Monotonic Stack Approach
        int[] result5 = dailyTemperaturesMonotonicStack(temperatures);
        System.out.println("Monotonic Stack: " + Arrays.toString(result5));
    }
}

