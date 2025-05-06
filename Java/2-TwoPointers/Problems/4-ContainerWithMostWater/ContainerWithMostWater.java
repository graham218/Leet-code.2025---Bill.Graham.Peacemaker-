import java.util.Arrays; // Import for Arrays.toString, used in testing

public class ContainerWithMostWater {

    /**
     * **Approach 1: Brute Force**
     *
     * * **Concept:** Calculate the area for every possible pair of lines and find the maximum.
     * * **Time Complexity:** O(n^2), where n is the length of the height array.
     * * **Space Complexity:** O(1), constant extra space.
     *
     * @param height Array representing the height of each line.
     * @return The maximum water that can be contained.
     */
    public static int maxAreaBruteForce(int[] height) {
        int maxArea = 0;
        int n = height.length;

        // Iterate through all possible pairs of lines
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Calculate the width and the height of the container
                int width = j - i;
                int containerHeight = Math.min(height[i], height[j]);
                // Calculate the area of the current container
                int area = width * containerHeight;
                // Update maxArea if the current area is greater
                maxArea = Math.max(maxArea, area);
            }
        }
        return maxArea;
    }

    /**
     * **Approach 2: Optimized Brute Force (Slight Improvement)**
     *
     * * **Concept:** Similar to brute force, but with a minor optimization to avoid redundant calculations
     * * **Time Complexity:** O(n^2), where n is the length of the height array.
     * * **Space Complexity:** O(1), constant extra space.
     *
     * @param height Array representing the height of each line.
     * @return The maximum water that can be contained.
     */
    public static int maxAreaOptimizedBruteForce(int[] height) {
        int maxArea = 0;
        int n = height.length;

        for (int i = 0; i < n; i++) {
            // Optimization: Start j from the end and move towards i
            for (int j = n - 1; j > i; j--) {
                int width = j - i;
                int containerHeight = Math.min(height[i], height[j]);
                int area = width * containerHeight;
                maxArea = Math.max(maxArea, area);
                //Potentially skip some iterations.
                if(containerHeight * (n-1) < maxArea){
                    break;
                }
            }
        }
        return maxArea;
    }

    /**
     * **Approach 3: Two Pointers**
     *
     * * **Concept:** Use two pointers, one at the start and one at the end of the array.  Move the pointer with the smaller height towards the other pointer.
     * * **Time Complexity:** O(n), where n is the length of the height array.
     * * **Space Complexity:** O(1), constant extra space.
     *
     * @param height Array representing the height of each line.
     * @return The maximum water that can be contained.
     */
    public static int maxAreaTwoPointers(int[] height) {
        int maxArea = 0;
        int left = 0;
        int right = height.length - 1;

        // Move pointers until they meet
        while (left < right) {
            // Calculate the width and height
            int width = right - left;
            int containerHeight = Math.min(height[left], height[right]);
            int area = width * containerHeight;
            maxArea = Math.max(maxArea, area);

            // Move the pointer with the smaller height
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return maxArea;
    }

    /**
     * **Approach 4: Two Pointers (Slightly Different)**
     *
     * * **Concept:** Similar to the standard two-pointer approach, but with a more concise way to express the pointer movement.
     * * **Time Complexity:** O(n), where n is the length of the height array.
     * * **Space Complexity:** O(1), constant extra space.
     *
     * @param height Array representing the height of each line.
     * @return The maximum water that can be contained.
     */
    public static int maxAreaTwoPointersConcise(int[] height) {
        int maxArea = 0;
        int left = 0;
        int right = height.length - 1;

        while (left < right) {
            maxArea = Math.max(maxArea, Math.min(height[left], height[right]) * (right - left));
            if (height[left] < height[right])
                left++;
            else
                right--;
        }
        return maxArea;
    }

    /**
     * **Approach 5:  Precomputed Areas (for demonstration - not efficient)**
     *
     * * **Concept:** Precompute all possible areas and then find the maximum.  This is inefficient and mainly for illustration.
     * * **Time Complexity:** O(n^2), where n is the length of the height array.
     * * **Space Complexity:** O(n^2), to store all possible areas.
     *
     * @param height Array representing the height of each line.
     * @return The maximum water that can be contained.
     */
    public static int maxAreaPrecomputed(int[] height) {
        int n = height.length;
        int[][] areas = new int[n][n]; // Store areas[i][j] = area between i and j
        int maxArea = 0;

        // Calculate and store all possible areas
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                areas[i][j] = Math.min(height[i], height[j]) * (j - i);
                maxArea = Math.max(maxArea, areas[i][j]);
            }
        }
        return maxArea;
    }

    public static void main(String[] args) {
        // Example usage of the different approaches
        int[] height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        //int[] height = {1,1};
        //int[] height = {4,3,2,1,4};

        System.out.println("Input Array: " + Arrays.toString(height));
        System.out.println("Max Area (Brute Force): " + maxAreaBruteForce(height));
        System.out.println("Max Area (Optimized Brute Force): " + maxAreaOptimizedBruteForce(height));
        System.out.println("Max Area (Two Pointers): " + maxAreaTwoPointers(height));
        System.out.println("Max Area (Two Pointers Concise): " + maxAreaTwoPointersConcise(height));
        System.out.println("Max Area (Precomputed Areas): " + maxAreaPrecomputed(height));
    }
}
