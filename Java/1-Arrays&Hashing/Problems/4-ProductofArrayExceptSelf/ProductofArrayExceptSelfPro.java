import java.util.Arrays;

public class ProductOfArrayExceptSelf {

    /*
     * 1. Brute Force Approach
     *
     * -   Time Complexity: O(n^2)
     * -   Space Complexity: O(n) (for the result array)
     * -   Real-world Use Case: This approach is straightforward to understand
     * but inefficient for large datasets.  It might be used in a very
     * constrained environment where code simplicity is more important
     * than performance, and the input size is guaranteed to be small
     * (e.g., a small embedded system or a very limited-resource
     * scenario).  It's often used as a baseline for comparison with
     * more optimized solutions.
     */
    public static int[] productExceptSelfBruteForce(int[] nums) {
        if (nums == null || nums.length == 0) {
            return new int[0]; // Handle edge case: empty or null input
        }

        int n = nums.length;
        int[] result = new int[n];

        for (int i = 0; i < n; i++) {
            int product = 1;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    product *= nums[j];
                }
            }
            result[i] = product;
        }
        return result;
    }

    /*
     * 2. Left and Right Products Approach
     *
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(n) (for the left and right arrays)
     * -   Real-world Use Case: This is a classic approach that balances
     * performance and code clarity.  It's suitable for many
     * general-purpose applications where moderate memory usage is
     * acceptable.  For example, in a data processing pipeline where
     * you need to calculate this product as an intermediate step,
     * or in a business application where performance is important
     * but not absolutely critical.  It's also good for educational
     * purposes to illustrate the concept of prefix and suffix products.
     */
    public static int[] productExceptSelfLeftRight(int[] nums) {
        if (nums == null || nums.length == 0) {
            return new int[0];
        }

        int n = nums.length;
        int[] leftProducts = new int[n];
        int[] rightProducts = new int[n];
        int[] result = new int[n];

        // Calculate left products
        leftProducts[0] = 1;
        for (int i = 1; i < n; i++) {
            leftProducts[i] = leftProducts[i - 1] * nums[i - 1];
        }

        // Calculate right products
        rightProducts[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            rightProducts[i] = rightProducts[i + 1] * nums[i + 1];
        }

        // Calculate the final result
        for (int i = 0; i < n; i++) {
            result[i] = leftProducts[i] * rightProducts[i];
        }
        return result;
    }

    /*
     * 3. Optimized Left and Right Products Approach (Constant Space)
     *
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(1) (excluding the result array)
     * -   Real-world Use Case: This is the most efficient approach in
     * terms of space complexity.  It's ideal for applications where
     * memory is a critical constraint, such as in embedded systems,
     * mobile app development, or when dealing with very large datasets
     * where minimizing memory footprint is essential.  For example, if
     * you're processing sensor data on a low-power device or performing
     * calculations on a massive array in a memory-limited environment,
     * this approach would be preferred.
     */
    public static int[] productExceptSelfOptimized(int[] nums) {
        if (nums == null || nums.length == 0) {
            return new int[0];
        }

        int n = nums.length;
        int[] result = new int[n];

        // Calculate left products and store in result array
        result[0] = 1;
        for (int i = 1; i < n; i++) {
            result[i] = result[i - 1] * nums[i - 1];
        }

        // Calculate right products and multiply with left products
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] = result[i] * rightProduct;
            rightProduct *= nums[i];
        }
        return result;
    }

    /*
     * 4. Using Division (Less Robust)
     *
     * -   Time Complexity: O(n)
     * -   Space Complexity: O(n)
     * -   Real-world Use Case: This approach is generally *NOT* recommended
     * for real-world use due to its fragility with zero values.  However,
     * it can be used in specific scenarios where you have a *guarantee*
     * that the input array will *never* contain zero, and you need a
     * very concise solution.  For example, in a specialized scientific
     * computation where the input data is known to be non-zero by
     * definition.  Even then, it's crucial to include robust error
     * handling.
     */
    public static int[] productExceptSelfWithDivision(int[] nums) {
        if (nums == null || nums.length == 0) {
            return new int[0];
        }

        int n = nums.length;
        int[] result = new int[n];
        int totalProduct = 1;
        int zeroCount = 0;

        for (int num : nums) {
            if (num != 0) {
                totalProduct *= num;
            } else {
                zeroCount++;
            }
        }

        if (zeroCount > 1) {
            Arrays.fill(result, 0); // If more than one zero, the whole array is 0
            return result;
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] != 0) {
                result[i] = totalProduct / nums[i];
            } else {
                result[i] = totalProduct; // if there is one zero
            }
        }
        return result;
    }

    /*
     * 5. Using Java Streams (Functional Approach)
     *
     * -   Time Complexity: O(n) (due to the loop within the stream operation)
     * -   Space Complexity: O(n) (for the result array and intermediate lists)
     * -   Real-world Use Case:  This approach demonstrates a more modern,
     * functional style using Java Streams.  It can be more concise and
     * readable for developers familiar with functional programming.
     * It's suitable for applications where code clarity and maintainability
     * are prioritized, and the performance overhead of streams is
     * acceptable.  For example, in a microservice where you want to
     * write expressive code, or in a data transformation pipeline
     * using a functional programming paradigm.  However, be mindful
     * of potential performance implications with very large datasets.
     */
    public static int[] productExceptSelfStreams(int[] nums) {
        if (nums == null || nums.length == 0) {
            return new int[0];
        }

        int n = nums.length;
        int[] result = new int[n];

        for (int i = 0; i < n; i++) {
            final int currentIndex = i; // Need a final variable for the lambda
            result[i] = Arrays.stream(nums)
                    .filter(j -> j != currentIndex)
                    .reduce(1, (a, b) -> a * b);
        }
        return result;
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3, 4};

        System.out.println("Input: " + Arrays.toString(nums));

        System.out.println("Brute Force: " + Arrays.toString(productExceptSelfBruteForce(nums)));
        System.out.println("Left/Right Products: " + Arrays.toString(productExceptSelfLeftRight(nums)));
        System.out.println("Optimized: " + Arrays.toString(productExceptSelfOptimized(nums)));
        System.out.println("Division: " + Arrays.toString(productExceptSelfWithDivision(nums)));
        System.out.println("Streams: " + Arrays.toString(productExceptSelfStreams(nums)));

        int[] numsWithZero = {0, 2, 3, 4};
        System.out.println("\nInput with Zero: " + Arrays.toString(numsWithZero));
        System.out.println("Brute Force: " + Arrays.toString(productExceptSelfBruteForce(numsWithZero)));
        System.out.println("Left/Right Products: " + Arrays.toString(productExceptSelfLeftRight(numsWithZero)));
        System.out.println("Optimized: " + Arrays.toString(productExceptSelfOptimized(numsWithZero)));
        System.out.println("Division: " + Arrays.toString(productExceptSelfWithDivision(numsWithZero)));
        System.out.println("Streams: " + Arrays.toString(productExceptSelfStreams(numsWithZero)));

        int[] numsWithTwoZeros = {1, 0, 3, 0};
        System.out.println("\nInput with Two Zeros: " + Arrays.toString(numsWithTwoZeros));
        System.out.println("Brute Force: " + Arrays.toString(productExceptSelfBruteForce(numsWithTwoZeros)));
        System.out.println("Left/Right Products: " + Arrays.toString(productExceptSelfLeftRight(numsWithTwoZeros)));
        System.out.println("Optimized: " + Arrays.toString(productExceptSelfOptimized(numsWithTwoZeros)));
        System.out.println("Division: " + Arrays.toString(productExceptSelfWithDivision(numsWithTwoZeros)));
        System.out.println("Streams: " + Arrays.toString(productExceptSelfStreams(numsWithTwoZeros)));
    }
}

