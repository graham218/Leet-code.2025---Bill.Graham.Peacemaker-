import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;
import java.util.HashMap;
import java.util.Map;

public class DailyTemperatures {

    /**
     * Approach 1: Monotonic Stack (Optimized)
     *
     * This is the most efficient approach.  It uses a stack to keep track of the
     * indices of temperatures in decreasing order.  For each temperature, we pop
     * the indices of any warmer temperatures from the stack and update their
     * waiting days.
     *
     * Time Complexity: O(N), where N is the length of the temperatures array. Each
     * index is pushed and popped at most once.
     * Space Complexity: O(N) in the worst case, when the temperatures are
     * monotonically decreasing.
     *
     * Real-world application: This approach is optimal for analyzing time-series
     * data where you need to find the next greater element, such as stock prices,
     * weather patterns, or signal processing.  It's efficient for large datasets.
     */
    public static int[] dailyTemperaturesMonotonicStack(int[] temperatures) {
        int n = temperatures.length;
        int[] result = new int[n];
        Deque<Integer> stack = new ArrayDeque<>(); // Stack of indices

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && temperatures[i] > temperatures[stack.peek()]) {
                int prevIndex = stack.pop();
                result[prevIndex] = i - prevIndex;
            }
            stack.push(i);
        }
        return result;
    }

    /**
     * Approach 2: Brute Force
     *
     * This is the most straightforward approach, but it's also the least efficient.
     * For each day, it iterates through the remaining days to find the next warmer
     * day.
     *
     * Time Complexity: O(N^2), where N is the length of the temperatures array.
     * Space Complexity: O(1).
     *
     * Real-world application: While inefficient for large datasets, this approach
     * is simple to understand and implement.  It might be used in a very small-scale
     * application or for testing purposes where performance is not critical.  For
     * example, in a simple script to process a very small amount of data.
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
        }
        return result;
    }

    /**
     * Approach 3: Using a HashMap (Less Efficient)
     *
     * This approach uses a HashMap to store the indices of temperatures.  It
     * iterates through the temperatures and checks the map for warmer temperatures.
     * This approach is less efficient than the Monotonic Stack approach because
     * lookups in the HashMap can be costly, and it doesn't guarantee a single pass.
     *
     * Time Complexity: O(N^2) in the worst case, where N is the length of the temperatures array.
     * Space Complexity: O(N), for storing the temperatures and their indices in the HashMap.
     *
     * Real-world application: This approach might be used if you need to store
     * additional information about the temperatures and their indices, but the
     * performance is not critical.  For example, in a data analysis script where
     * you need to perform other operations on the temperature data.  However, a
     * better approach would be to use a separate data structure along with the
     * Monotonic Stack approach.
     */
    public static int[] dailyTemperaturesHashMap(int[] temperatures) {
        int n = temperatures.length;
        int[] result = new int[n];
        Map<Integer, Integer> tempMap = new HashMap<>();

        for (int i = 0; i < n; i++) {
            tempMap.put(temperatures[i], i);
            for (int j = i + 1; j < n; j++) {
                if (temperatures[j] > temperatures[i]) {
                    result[i] = j - i;
                    break;
                }
            }
        }
        return result;
    }

    /**
     * Approach 4: Optimized Brute Force (Slight Improvement)
     *
     * This is a slight optimization of the brute force approach. Instead of
     * starting the inner loop from i+1, we can start from the next warmer day
     * we found for the previous day (if any). This can reduce the number of
     * iterations in some cases, but the worst-case time complexity remains O(N^2).
     *
     * Time Complexity: O(N^2) in the worst case, but can be faster than the basic
     * brute force in some cases.
     * Space Complexity: O(1).
     *
     * Real-world application: This approach is a minor optimization over the
     * brute-force method.  It might be useful in situations where you expect some
     * locality in the data, meaning that if day i's next warmer day is j, then
     * day i+1's next warmer day is likely to be near j.  However, for truly
     * random or decreasing temperature data, it offers little to no improvement.
     */
    public static int[] dailyTemperaturesOptimizedBruteForce(int[] temperatures) {
        int n = temperatures.length;
        int[] result = new int[n];
        int nextWarmest = 0; // Keep track of the next warmest day found so far

        for (int i = 0; i < n; i++) {
            nextWarmest = Math.max(i + 1, nextWarmest); // Start from the next day or the previous nextWarmest
            for (int j = nextWarmest; j < n; j++) {
                if (temperatures[j] > temperatures[i]) {
                    result[i] = j - i;
                    nextWarmest = j; // Update nextWarmest for the next iteration
                    break;
                }
            }
        }
        return result;
    }

    /**
     * Approach 5: Using a Stack (Less Optimized)
     *
     * This approach also uses a stack, but it's less optimized than the first
     * approach.  It stores both the temperature and the index in the stack,
     * which is not necessary.  It also iterates through the stack for each
     * temperature, which can lead to redundant comparisons.
     *
     * Time Complexity: O(N^2) in the worst case, where N is the length of the temperatures array.
     * Space Complexity: O(N), for the stack.
     *
     * Real-world application: This approach is less efficient than the Monotonic
     * Stack approach.  It might be used as a less optimal solution, perhaps in an
     * educational setting to illustrate the use of stacks, but it's not recommended
     * for production code.  The optimized Monotonic Stack approach is generally
     * preferred.
     */
    public static int[] dailyTemperaturesStack(int[] temperatures) {
        int n = temperatures.length;
        int[] result = new int[n];
        Deque<int[]> stack = new ArrayDeque<>(); // Stack of [temperature, index] pairs

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && temperatures[i] > stack.peek()[0]) {
                int[] prev = stack.pop();
                result[prev[1]] = i - prev[1];
            }
            stack.push(new int[]{temperatures[i], i});
        }
        return result;
    }

    public static void main(String[] args) {
        int[] temperatures = {73, 74, 75, 71, 69, 72, 76, 73};

        System.out.println("Temperatures: " + Arrays.toString(temperatures));

        // Test each approach
        int[] result1 = dailyTemperaturesMonotonicStack(temperatures);
        System.out.println("Monotonic Stack: " + Arrays.toString(result1)); // Expected: [1, 1, 4, 2, 1, 1, 0, 0]

        int[] result2 = dailyTemperaturesBruteForce(temperatures);
        System.out.println("Brute Force: " + Arrays.toString(result2));     // Expected: [1, 1, 4, 2, 1, 1, 0, 0]

        int[] result3 = dailyTemperaturesHashMap(temperatures);
        System.out.println("HashMap: " + Arrays.toString(result3));       // Expected: [1, 1, 4, 2, 1, 1, 0, 0]

        int[] result4 = dailyTemperaturesOptimizedBruteForce(temperatures);
        System.out.println("Optimized Brute Force: " + Arrays.toString(result4));  // Expected: [1, 1, 4, 2, 1, 1, 0, 0]

        int[] result5 = dailyTemperaturesStack(temperatures);
        System.out.println("Stack: " + Arrays.toString(result5));           // Expected: [1, 1, 4, 2, 1, 1, 0, 0]
    }
}

