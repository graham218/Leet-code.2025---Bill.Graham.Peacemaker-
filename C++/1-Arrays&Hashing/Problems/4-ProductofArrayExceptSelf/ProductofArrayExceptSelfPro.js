/*
Problem:
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

Constraints:
-   2 <= nums.length <= 10^5
-   -30 <= nums[i] <= 30
-   The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

Examples:
Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]

Explanation:
We need to calculate the product of all elements in the array *except* the element at the current index.  This must be done efficiently, without using division.

Real-world Applications:
1.  **Data Analysis:** Calculating feature importance in machine learning.  If `nums` represents the impact of different factors, the result can show the combined impact of all other factors.
2.  **Financial Modeling:** Analyzing stock returns.  If `nums` holds daily returns, the result can show the cumulative effect of all other days' returns.
3.  **Error Calculation:** In some numerical algorithms, you might need to calculate the product of error terms, excluding the current term.
4.  **Image Processing:** Calculating pixel values based on neighboring pixels (though less direct).
5.  **Game Development:** Calculating influence of game objects, excluding the current object.
6.  **Network Reliability:** Determining the reliability of a network node, given the reliability of other nodes.
*/

/**
 * Approach 1: Brute Force
 *
 * Description:
 * The most straightforward approach. For each element in the input array `nums`,
 * calculate the product of all other elements by iterating through the array again,
 * skipping the current element.
 *
 * Time Complexity: O(n^2) - Nested loops, where n is the length of nums.
 * Space Complexity: O(n) - To store the result array.
 */
function productExceptSelf_bruteforce(nums) {
    const n = nums.length;
    const result = [];

    for (let i = 0; i < n; i++) {
        let product = 1;
        for (let j = 0; j < n; j++) {
            if (i !== j) {
                product *= nums[j];
            }
        }
        result[i] = product;
    }
    return result;
}

/**
 * Approach 2: Using Division
 *
 * Description:
 * Calculate the product of all elements in the array. Then, for each element,
 * divide the total product by that element to get the product of all other elements.
 *
 * Time Complexity: O(n) - One pass to calculate total product, one pass to calculate result.
 * Space Complexity: O(n) - To store the result array.
 *
 * Note: This approach is included for completeness but violates the problem constraint
 * of not using division.
 */
function productExceptSelf_division(nums) {
    const n = nums.length;
    const result = [];
    let totalProduct = 1;

    for (let i = 0; i < n; i++) {
        totalProduct *= nums[i];
    }

    for (let i = 0; i < n; i++) {
        result[i] = totalProduct / nums[i];
    }
    return result;
}

/**
 * Approach 3: Prefix and Suffix Products
 *
 * Description:
 * Calculate the product of all elements to the left (prefix products) and the product
 * of all elements to the right (suffix products) of each element.  Then, for each
 * element, the product of all other elements is the product of its left prefix
 * and right suffix.  This is the standard, efficient solution.
 *
 * Time Complexity: O(n) - Three passes through the array.
 * Space Complexity: O(n) - Two arrays of size n to store left and right products.
 */
function productExceptSelf_prefixSuffix(nums) {
    const n = nums.length;
    const leftProducts = [];
    const rightProducts = [];
    const result = [];

    // Calculate left products
    let leftProduct = 1;
    for (let i = 0; i < n; i++) {
        leftProducts[i] = leftProduct;
        leftProduct *= nums[i];
    }

    // Calculate right products
    let rightProduct = 1;
    for (let i = n - 1; i >= 0; i--) {
        rightProducts[i] = rightProduct;
        rightProduct *= nums[i];
    }

    // Calculate result
    for (let i = 0; i < n; i++) {
        result[i] = leftProducts[i] * rightProducts[i];
    }
    return result;
}

/**
 * Approach 4: Optimized Prefix and Suffix Products (Constant Space)
 *
 * Description:
 * An optimized version of the prefix and suffix products approach. Instead of using
 * two separate arrays for left and right products, we use only the result array
 * to store the left products.  We then calculate the right products and multiply
 * them into the result array in a single pass.  This reduces the space complexity
 * to O(1) (excluding the output array).
 *
 * Time Complexity: O(n) - Two passes through the array.
 * Space Complexity: O(1) -  The result array does not count towards extra space.
 */
function productExceptSelf_optimized(nums) {
    const n = nums.length;
    const result = [];

    // Calculate left products and store in result array
    let leftProduct = 1;
    for (let i = 0; i < n; i++) {
        result[i] = leftProduct;
        leftProduct *= nums[i];
    }

    // Calculate right products and multiply with left products in result array
    let rightProduct = 1;
    for (let i = n - 1; i >= 0; i--) {
        result[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    return result;
}

/**
 * Approach 5: Functional Approach using Reduce and Map
 *
 * Description:
 * This approach uses `reduce` to calculate the prefix and suffix products,
 * and `map` to combine them.  It's a more functional style, but can be less
 * readable for those not familiar with functional programming.
 *
 * Time Complexity: O(n) -  Due to the reduce and map operations.
 * Space Complexity: O(n) -  Temporary arrays are created during the reductions.
 */
function productExceptSelf_functional(nums) {
    const n = nums.length;

    // Calculate prefix products using reduce
    const prefixProducts = nums.reduce((acc, num, i) => {
        acc[i] = i === 0 ? 1 : acc[i - 1] * nums[i - 1];
        return acc;
    }, []);

    // Calculate suffix products using reduce
    const suffixProducts = nums.reduceRight((acc, num, i) => {
        acc[i] = i === n - 1 ? 1 : acc[i + 1] * nums[i + 1];
        return acc;
    }, []);

    // Calculate the final result using map
    const result = prefixProducts.map((prefix, i) => prefix * suffixProducts[i]);
    return result;
}

/**
 * Approach 6: Iterative with Early Product Calculation
 *
 * Description: This approach calculates the product of elements *before* the current index,
 * and the product of elements *after* the current index in the same loop.  It's similar
 * to the optimized approach, but combines the loops for a slightly different
 * perspective on the iteration.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)  (excluding the output array)
 */
function productExceptSelf_iterative(nums) {
    const n = nums.length;
    const result = new Array(n).fill(1); // Initialize result array with 1s.

    let prefixProduct = 1;
    let suffixProduct = 1;

    for (let i = 0; i < n; i++) {
        // Calculate product of elements *before* i
        result[i] *= prefixProduct;
        prefixProduct *= nums[i];

        // Calculate product of elements *after* i
        result[n - 1 - i] *= suffixProduct;
        suffixProduct *= nums[n - 1 - i];
    }
    return result;
}

// Example Usage and Output
const nums1 = [1, 2, 3, 4];
const nums2 = [-1, 1, 0, -3, 3];

console.log("Input: [1,2,3,4]");
console.log("Brute Force:", productExceptSelf_bruteforce(nums1));       // Output: [24, 12, 8, 6]
console.log("Division:", productExceptSelf_division(nums1));           // Output: [24, 12, 8, 6]  (Violates constraint)
console.log("Prefix/Suffix:", productExceptSelf_prefixSuffix(nums1));   // Output: [24, 12, 8, 6]
console.log("Optimized:", productExceptSelf_optimized(nums1));         // Output: [24, 12, 8, 6]
console.log("Functional:", productExceptSelf_functional(nums1));       // Output: [24, 12, 8, 6]
console.log("Iterative:", productExceptSelf_iterative(nums1));         // Output: [24, 12, 8, 6]

console.log("\nInput: [-1,1,0,-3,3]");
console.log("Brute Force:", productExceptSelf_bruteforce(nums2));       // Output: [0, 0, 9, 0, 0]
console.log("Division:", productExceptSelf_division(nums2));           // Output: [0, 0, 9, 0, 0]  (Violates constraint)
console.log("Prefix/Suffix:", productExceptSelf_prefixSuffix(nums2));   // Output: [0, 0, 9, 0, 0]
console.log("Optimized:", productExceptSelf_optimized(nums2));         // Output: [0, 0, 9, 0, 0]
console.log("Functional:", productExceptSelf_functional(nums2));       // Output: [0, 0, 9, 0, 0]
console.log("Iterative:", productExceptSelf_iterative(nums2));         // Output: [0, 0, 9, 0, 0]
