import java.util.Arrays;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.stream.Stream;

public class ContainerWithMostWater {

    /**
     * Main method to run the program and test the different approaches.
     *
     * @param args command line arguments (not used in this example)
     */
    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) { // Use try-with-resources to auto-close the scanner.

            System.out.println("Container With Most Water Problem");
            System.out.println("------------------------------------");
            System.out.println("Enter the heights of the container walls, separated by spaces:");
            System.out.println("Example: 1 8 6 2 5 4 8 3 7");

            String input = scanner.nextLine();
            int[] height = parseInput(input); // Moved input parsing to a separate method.

            if (height == null || height.length < 2) {
                System.out.println("Invalid input. Please provide at least two heights.");
                return; // Exit the program if the input is invalid.
            }

            // Create an instance of the class to access the methods.
            ContainerWithMostWater container = new ContainerWithMostWater();

            // Test and display results for each approach.  Added descriptive output.
            System.out.println("\nTesting different approaches:");
            System.out.println("------------------------------------");

            long startTime, endTime;
            double executionTime;

            startTime = System.nanoTime();
            int maxArea1 = container.maxAreaBruteForce(height);
            endTime = System.nanoTime();
            executionTime = (endTime - startTime) / 1e6; // Convert to milliseconds.
            System.out.println("1. Brute Force Approach: Max Area = " + maxArea1 + ", Time: " + executionTime + " ms");

            startTime = System.nanoTime();
            int maxArea2 = container.maxAreaTwoPointers(height);
            endTime = System.nanoTime();
            executionTime = (endTime - startTime) / 1e6;
            System.out.println("2. Two Pointers Approach: Max Area = " + maxArea2 + ", Time: " + executionTime + " ms");

            startTime = System.nanoTime();
            int maxArea3 = container.maxAreaOptimized(height);
            endTime = System.nanoTime();
            executionTime = (endTime - startTime) / 1e6;
            System.out.println("3. Optimized Approach: Max Area = " + maxArea3 + ", Time: " + executionTime + " ms");

            startTime = System.nanoTime();
            int maxArea4 = container.maxAreaLambda(height);
            endTime = System.nanoTime();
            executionTime = (endTime - startTime) / 1e6;
            System.out.println("4. Lambda Approach: Max Area = " + maxArea4 + ", Time: " + executionTime + " ms");

            startTime = System.nanoTime();
            int maxArea5 = container.maxAreaDivideAndConquer(height, 0, height.length - 1);
            endTime = System.nanoTime();
            executionTime = (endTime - startTime) / 1e6;
            System.out.println("5. Divide and Conquer Approach: Max Area = " + maxArea5 + ", Time: " + executionTime + " ms");

        } catch (InputMismatchException e) {
            System.out.println("Error: Invalid input. Please enter numbers only, separated by spaces.");
        } catch (Exception e) {
            System.out.println("An unexpected error occurred: " + e.getMessage()); // Catch other exceptions.
        }
        // Program execution completes here.  No need for a separate "exit message".
    }

    /**
     * Parses the input string into an integer array.
     * Handles potential errors in the input format.
     *
     * @param input the input string containing space-separated integers
     * @return an integer array representing the heights, or null if an error occurs
     */
    private static int[] parseInput(String input) {
        if (input == null || input.trim().isEmpty()) {
            return null; // Handle null or empty input
        }
        String[] numberStrings = input.trim().split("\\s+"); // Split by spaces, handle multiple spaces
        int[] numbers = new int[numberStrings.length];
        try {
            for (int i = 0; i < numberStrings.length; i++) {
                numbers[i] = Integer.parseInt(numberStrings[i].trim()); // Parse each number, handle extra spaces
            }
        } catch (NumberFormatException e) {
            return null; // Return null if any parsing fails
        }
        return numbers;
    }

    /**
     * 1. Brute Force Approach:
     * Calculates the maximum water that can be contained between any two lines.
     * It considers every possible pair of lines and calculates the area.
     *
     * Time Complexity: O(n^2) - nested loops iterate through all pairs.
     * Space Complexity: O(1) -  uses a constant amount of extra space.
     *
     * @param height array of integers representing the height of the lines
     * @return the maximum area of water that can be contained
     */
    public int maxAreaBruteForce(int[] height) {
        int maxArea = 0;
        for (int i = 0; i < height.length; i++) {
            for (int j = i + 1; j < height.length; j++) {
                int width = j - i;
                int minHeight = Math.min(height[i], height[j]);
                int area = width * minHeight;
                maxArea = Math.max(maxArea, area);
            }
        }
        return maxArea;
    }

    /**
     * 2. Two Pointers Approach:
     * Uses two pointers, one at the beginning and one at the end of the array.
     * It moves the pointer with the smaller height, as moving the taller pointer
     * will never increase the area.
     *
     * Time Complexity: O(n) - single pass through the array.
     * Space Complexity: O(1) - uses a constant amount of extra space.
     *
     * @param height array of integers representing the height of the lines
     * @return the maximum area of water that can be contained
     */
    public int maxAreaTwoPointers(int[] height) {
        int maxArea = 0;
        int left = 0;
        int right = height.length - 1;
        while (left < right) {
            int width = right - left;
            int minHeight = Math.min(height[left], height[right]);
            int area = width * minHeight;
            maxArea = Math.max(maxArea, area);
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return maxArea;
    }

    /**
     * 3. Optimized Approach (Same as Two Pointers):
     * This is essentially the same as the Two Pointers approach, but with more concise variable names.
     * It's included to explicitly show that the Two Pointers approach is the optimized solution.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     *
     * @param height array of integers representing the height of the lines
     * @return the maximum area of water that can be contained
     */
    public int maxAreaOptimized(int[] height) {
        int maxArea = 0;
        int left = 0;
        int right = height.length - 1;
        while (left < right) {
            int width = right - left;
            int h = Math.min(height[left], height[right]); // More concise variable name
            int area = width * h;
            maxArea = Math.max(maxArea, area);
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return maxArea;
    }

    /**
     * 4. Lambda Approach:
     * Uses Java 8 Streams and lambda expressions for a more functional approach.
     * This approach is NOT more efficient than the two-pointer approach, and is often less readable for this problem.
     * It's included as an example of using lambdas, not for performance.  It is generally less efficient due to the overhead of Streams.
     *
     * Time Complexity: O(n) in best/average case, but can be higher in worst case due to stream operations.
     * Space Complexity: O(n) in worst case due to stream operations.
     *
     * @param height array of integers representing the height of the lines
     * @return the maximum area of water that can be contained
     */
    public int maxAreaLambda(int[] height) {
        int[] left = {0};  // Use an array to make it effectively final for the lambda
        int[] right = {height.length - 1}; // Use an array to make it effectively final for the lambda
        int[] maxArea = {0};

        Stream.iterate(0, i -> i < height.length - 1 && left[0] < right[0], i -> 0) //iterate until left >= right
                .forEach(i -> {  // The loop variable 'i' is not actually used.
                    int width = right[0] - left[0];
                    int minHeight = Math.min(height[left[0]], height[right[0]]);
                    int area = width * minHeight;
                    maxArea[0] = Math.max(maxArea[0], area);
                    if (height[left[0]] < height[right[0]]) {
                        left[0]++;
                    } else {
                        right[0]--;
                    }
                });
        return maxArea[0];
    }



    /**
     * 5. Divide and Conquer Approach:
     * This approach recursively divides the problem into smaller subproblems.
     * It finds the maximum area in the left half, the right half, and the area
     * that crosses the midpoint.  While conceptually valid, Divide and Conquer is NOT an efficient
     * solution for this specific problem.  It has a higher time complexity than the Two Pointers approach
     * due to the overhead of recursion.
     *
     * Time Complexity: O(n log n) in the average case, but can be closer to O(n^2) in the worst case.
     * Space Complexity: O(log n) due to the recursive call stack.
     *
     * @param height array of integers representing the height of the lines
     * @param left  left index of the current subarray
     * @param right right index of the current subarray
     * @return the maximum area of water that can be contained
     */
    public int maxAreaDivideAndConquer(int[] height, int left, int right) {
        if (left >= right) {
            return 0; // Base case: no area if left and right meet.
        }
        int mid = left + (right - left) / 2; // prevent integer overflow
        int maxAreaLeft = maxAreaDivideAndConquer(height, left, mid);
        int maxAreaRight = maxAreaDivideAndConquer(height, mid + 1, right);
        int maxAreaCross = 0;
        int l = mid, r = mid + 1;

        int minHeight = Math.min(height[l], height[r]);
        maxAreaCross = (r - l) * minHeight;

        while (l > left || r < right) {
            if ((l > left && height[l - 1] > height[r]) || r == right) {
                l--;
                minHeight = Math.min(minHeight, height[l]);
            } else if (r < right) {
                r++;
                minHeight = Math.min(minHeight, height[r]);
            }
            maxAreaCross = Math.max(maxAreaCross, (r - l) * minHeight);
        }
        return Math.max(Math.max(maxAreaLeft, maxAreaRight), maxAreaCross);
    }
}

