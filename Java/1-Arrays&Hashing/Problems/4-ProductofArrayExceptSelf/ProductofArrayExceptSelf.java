import java.util.Arrays;

public class ProductOfArrayExceptSelf {

    /**
     * Approach 1: Brute Force
     * - For each element nums[i], calculate the product of all other elements in the array.
     * - This approach has a time complexity of O(n^2) because of the nested loop.
     * - It's simple to understand but not efficient for large arrays.
     */
    public static int[] productExceptSelf_BruteForce(int[] nums) {
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

    /**
     * Approach 2: Using Division
     * - Calculate the product of all elements in the array.
     * - For each element nums[i], the result is the total product divided by nums[i].
     * - This approach has a time complexity of O(n), but it fails if the array contains zero.
     */
    public static int[] productExceptSelf_WithDivision(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        int totalProduct = 1;
        int zeroCount = 0;

        for (int num : nums) {
            if (num == 0) {
                zeroCount++;
            } else {
                totalProduct *= num;
            }
        }

        if (zeroCount > 1) {
            return result; // If more than one zero, the whole array will be zero
        }

        for (int i = 0; i < n; i++) {
            if (zeroCount == 0) {
                result[i] = totalProduct / nums[i];
            } else if (nums[i] == 0) {
                result[i] = totalProduct;
            } else {
                result[i] = 0;
            }
        }
        return result;
    }

    /**
     * Approach 3: Left and Right Products
     * - Create two arrays: leftProducts and rightProducts.
     * - leftProducts[i] stores the product of all elements to the left of nums[i].
     * - rightProducts[i] stores the product of all elements to the right of nums[i].
     * - The result for nums[i] is leftProducts[i] * rightProducts[i].
     * - This approach has a time complexity of O(n) and avoids division.
     */
    public static int[] productExceptSelf_LeftRightProducts(int[] nums) {
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

    /**
     * Approach 4: Optimized Left and Right Products (Single Pass)
     * - This is an optimized version of the previous approach.
     * - Instead of using two separate arrays for left and right products, we use only one result array.
     * - First, calculate the left products and store them in the result array.
     * - Then, calculate the right products and multiply them with the corresponding left products in the result array.
     * - This approach has a time complexity of O(n) and uses only one extra array.
     */
    public static int[] productExceptSelf_Optimized(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];

        // Calculate left products
        result[0] = 1;
        for (int i = 1; i < n; i++) {
            result[i] = result[i - 1] * nums[i - 1];
        }

        // Calculate right products and multiply with left products
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }
        return result;
    }

    /**
     * Approach 5: Using only one array.
     * - Similar to Approach 4, but even more optimized.
     * - Uses only the output array.
     */
    public static int[] productExceptSelf_SingleArray(int[] nums) {
        int n = nums.length;
        int[] output = new int[n];

        // Calculate left products
        output[0] = 1;
        for (int i = 1; i < n; i++) {
            output[i] = output[i - 1] * nums[i - 1];
        }

        // Calculate right products and multiply with left products
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            output[i] *= rightProduct;
            rightProduct *= nums[i];
        }

        return output;
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3, 4};

        System.out.println("Input Array: " + Arrays.toString(nums));

        // Brute Force Approach
        int[] result1 = productExceptSelf_BruteForce(nums);
        System.out.println("Product Except Self (Brute Force): " + Arrays.toString(result1));

        // With Division Approach
        int[] result2 = productExceptSelf_WithDivision(nums);
        System.out.println("Product Except Self (With Division): " + Arrays.toString(result2));

        // Left and Right Products Approach
        int[] result3 = productExceptSelf_LeftRightProducts(nums);
        System.out.println("Product Except Self (Left and Right Products): " + Arrays.toString(result3));

        // Optimized Left and Right Products Approach
        int[] result4 = productExceptSelf_Optimized(nums);
        System.out.println("Product Except Self (Optimized): " + Arrays.toString(result4));

        // Single Array
        int[] result5 = productExceptSelf_SingleArray(nums);
        System.out.println("Product Except Self (Single Array): " + Arrays.toString(result5));
    }
}

