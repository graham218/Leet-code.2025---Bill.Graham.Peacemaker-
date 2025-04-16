/*
Problem:
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

Constraints:
-   2 <= nums.length <= 10^5
-   -30 <= nums[i] <= 30
-   The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

Example 1:
Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Example 2:
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
*/

/**
 * Approach 1: Brute Force
 *
 * For each element in the input array `nums`, calculate the product of all other elements
 * by iterating through the array again, skipping the current element.  This is straightforward
 * but inefficient due to nested loops.
 *
 * Time Complexity: O(n^2), where n is the length of the input array `nums`.
 * Space Complexity: O(n), to store the output array `result`.
 */
function productExceptSelfBruteForce(nums) {
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
 * Calculate the total product of all elements in the array. Then, for each element,
 * divide the total product by that element to get the product of all other elements.
 * This is more efficient than the brute force approach, but it has a critical limitation:
 * it cannot handle cases where the input array contains zero, due to division by zero.
 *
 * Time Complexity: O(n), where n is the length of the input array `nums`.
 * Space Complexity: O(n), to store the output array `result`.
 */
function productExceptSelfWithDivision(nums) {
    const n = nums.length;
    const result = [];
    let totalProduct = 1;

    for (let i = 0; i < n; i++) {
        totalProduct *= nums[i];
    }

    for (let i = 0; i < n; i++) {
        if (nums[i] !== 0) {
           result[i] = totalProduct / nums[i];
        }
        else{
            let product = 1;
             for (let j = 0; j < n; j++) {
                if (i !== j) {
                    product *= nums[j];
                }
            }
            result[i] = product;
        }
    }
    return result;
}



/**
 * Approach 3: Prefix and Suffix Products
 *
 * This is an optimized approach that avoids division and has a linear time complexity.
 * It works by calculating the prefix products (products of all elements to the left)
 * and suffix products (products of all elements to the right).  The product of the
 * prefix product up to the element *before* the current element and the suffix product
 * *after* the current element gives the desired result.
 *
 * Time Complexity: O(n), where n is the length of the input array `nums`.
 * Space Complexity: O(n), to store the `leftProducts` and `rightProducts` arrays.
 */
function productExceptSelfPrefixSuffix(nums) {
    const n = nums.length;
    const leftProducts = new Array(n);
    const rightProducts = new Array(n);
    const result = new Array(n);

    // Calculate left products
    leftProducts[0] = 1;
    for (let i = 1; i < n; i++) {
        leftProducts[i] = leftProducts[i - 1] * nums[i - 1];
    }

    // Calculate right products
    rightProducts[n - 1] = 1;
    for (let i = n - 2; i >= 0; i--) {
        rightProducts[i] = rightProducts[i + 1] * nums[i + 1];
    }

    // Calculate the final result
    for (let i = 0; i < n; i++) {
        result[i] = leftProducts[i] * rightProducts[i];
    }
    return result;
}

/**
 * Approach 4: Optimized Prefix and Suffix Products (Constant Space)
 *
 * This is a further optimization of the prefix and suffix products approach.  Instead of
 * using separate arrays for left and right products, it reuses the output array to store
 * the left products. This reduces the space complexity to O(1), excluding the output array.
 *
 * Time Complexity: O(n), where n is the length of the input array `nums`.
 * Space Complexity: O(1), excluding the output array.
 */
function productExceptSelfOptimized(nums) {
    const n = nums.length;
    const result = new Array(n);

    // Calculate left products and store in result array
    result[0] = 1;
    for (let i = 1; i < n; i++) {
        result[i] = result[i - 1] * nums[i - 1];
    }

    // Calculate right products and multiply with left products
    let rightProduct = 1;
    for (let i = n - 1; i >= 0; i--) {
        result[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    return result;
}

/**
 * Approach 5: Using Reduce and Map
 *
 * This approach uses JavaScript's reduce and map functions for a more functional style.
 * First, it calculates the total product using reduce.  Then, it uses map to create the
 * result array by dividing the total product by each element.  Like Approach 2, this
 * approach will fail if the array contains a zero.
 *
 * Time Complexity: O(n), where n is the length of the input array.
 * Space Complexity: O(n), for the result array.
 */
function productExceptSelfReduceMap(nums) {
    const totalProduct = nums.reduce((acc, num) => acc * num, 1);
    return nums.map(num => totalProduct / num);
}


// Example Usage and Output
const nums1 = [1, 2, 3, 4];
const nums2 = [-1, 1, 0, -3, 3];
const nums3 = [5, 2, 10, 3];
const nums4 = [1, 0, 4, 6];

console.log("Input: [1, 2, 3, 4]");
console.log("Brute Force:", productExceptSelfBruteForce(nums1));       // Output: [24, 12, 8, 6]
console.log("Division:", productExceptSelfWithDivision(nums1));          // Output: [24, 12, 8, 6]
console.log("Prefix/Suffix:", productExceptSelfPrefixSuffix(nums1));    // Output: [24, 12, 8, 6]
console.log("Optimized:", productExceptSelfOptimized(nums1));         // Output: [24, 12, 8, 6]
console.log("Reduce/Map:", productExceptSelfReduceMap(nums1));       // Output: [24, 12, 8, 6]

console.log("\nInput: [-1, 1, 0, -3, 3]");
console.log("Brute Force:", productExceptSelfBruteForce(nums2));       // Output: [0, 0, 9, 0, 0]
console.log("Division:", productExceptSelfWithDivision(nums2));          // Output: [0, 0, 9, 0, 0]
console.log("Prefix/Suffix:", productExceptSelfPrefixSuffix(nums2));    // Output: [0, 0, 9, 0, 0]
console.log("Optimized:", productExceptSelfOptimized(nums2));         // Output: [0, 0, 9, 0, 0]
console.log("Reduce/Map:", productExceptSelfReduceMap(nums2));       // Output: [-0, -0, 0, -0, -0]

console.log("\nInput: [5, 2, 10, 3]");
console.log("Brute Force:", productExceptSelfBruteForce(nums3));       // Output: [60, 300, 60, 100]
console.log("Division:", productExceptSelfWithDivision(nums3));          // Output: [60, 300, 60, 100]
console.log("Prefix/Suffix:", productExceptSelfPrefixSuffix(nums3));    // Output: [60, 300, 60, 100]
console.log("Optimized:", productExceptSelfOptimized(nums3));         // Output: [60, 300, 60, 100]
console.log("Reduce/Map:", productExceptSelfReduceMap(nums3));       // Output: [60, 300, 60, 100]

console.log("\nInput: [1, 0, 4, 6]");
console.log("Brute Force:", productExceptSelfBruteForce(nums4));       // Output: [0, 24, 0, 0]
console.log("Division:", productExceptSelfWithDivision(nums4));          // Output: [0, 24, 0, 0]
console.log("Prefix/Suffix:", productExceptSelfPrefixSuffix(nums4));    // Output: [0, 24, 0, 0]
console.log("Optimized:", productExceptSelfOptimized(nums4));         // Output: [0, 24, 0, 0]
console.log("Reduce/Map:", productExceptSelfReduceMap(nums4));       // Output: [0, Infinity, 0, 0]
