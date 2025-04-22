/*
Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
You must implement a solution with a linear runtime complexity and use only constant extra space.

Example 1:
Input: nums = [2,2,1]
Output: 1

Example 2:
Input: nums = [4,1,2,1,2]
Output: 4

Example 3:
Input: nums = [1]
Output: 1
*/

/**
 * Approach 1: Using XOR (Bitwise Exclusive OR)
 * The XOR operation has the property that a ^ a = 0 and a ^ 0 = a.
 * We can XOR all the numbers in the array. The duplicate numbers will cancel each other out,
 * and the result will be the single number.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function singleNumberXOR(nums) {
    let result = 0;
    for (const num of nums) {
        result ^= num;
    }
    return result;
}

/**
 * Approach 2: Using a Set
 * We can use a Set to keep track of the numbers we have seen.
 * If we see a number for the first time, we add it to the Set.
 * If we see it again, we remove it from the Set.
 * The only number left in the Set will be the single number.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function singleNumberSet(nums) {
    const set = new Set();
    for (const num of nums) {
        if (set.has(num)) {
            set.delete(num);
        } else {
            set.add(num);
        }
    }
    return [...set][0]; // Convert set to array and get the first element.
}

/**
 * Approach 3: Using an Object (Hash Map)
 * We can use an object (hash map) to count the occurrences of each number.
 * Then, we iterate through the object and find the number with a count of 1.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function singleNumberObject(nums) {
    const counts = {};
    for (const num of nums) {
        counts[num] = (counts[num] || 0) + 1;
    }
    for (const num in counts) {
        if (counts[num] === 1) {
            return parseInt(num); // Convert the string key back to a number.
        }
    }
    return undefined; // Or throw an error, depending on the desired behavior.
}

/**
 * Approach 4: Using Reduce and XOR
 * This is a variation of the XOR approach, but using the reduce method.
 * It's more concise.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function singleNumberReduce(nums) {
    return nums.reduce((acc, curr) => acc ^ curr, 0);
}

/**
 * Approach 5: Using Bitwise Operations (Sum of Bits) - More Complex
 * This approach is more complex and less intuitive, but it's another way to solve the problem
 * using bitwise operations. It works by summing the bits at each position across all numbers.
 * The sum modulo 2 will give the bits of the single number.
 *
 * Time Complexity: O(n * k), where k is the number of bits in the largest number.
 * Space Complexity: O(1)
 */
function singleNumberBitwiseSum(nums) {
    let result = 0;
    const maxBits = 32; // Assuming 32-bit integers

    for (let i = 0; i < maxBits; i++) {
        let sum = 0;
        for (const num of nums) {
            // Check if the i-th bit is set in the current number
            if ((num >> i) & 1) {
                sum++;
            }
        }
        // If the sum of the i-th bits is odd, the i-th bit of the single number is set
        if (sum % 2 !== 0) {
            result |= (1 << i); // Set the i-th bit in the result
        }
    }
    return result;
}

// Example usage and output
const nums1 = [2, 2, 1];
const nums2 = [4, 1, 2, 1, 2];
const nums3 = [1];

console.log("Input: [2, 2, 1]");
console.log("Approach 1 (XOR):", singleNumberXOR(nums1));       // Output: 1
console.log("Approach 2 (Set):", singleNumberSet(nums1));       // Output: 1
console.log("Approach 3 (Object):", singleNumberObject(nums1));    // Output: 1
console.log("Approach 4 (Reduce):", singleNumberReduce(nums1));    // Output: 1
console.log("Approach 5 (Bitwise Sum):", singleNumberBitwiseSum(nums1)); // Output: 1
console.log("\n");

console.log("Input: [4, 1, 2, 1, 2]");
console.log("Approach 1 (XOR):", singleNumberXOR(nums2));       // Output: 4
console.log("Approach 2 (Set):", singleNumberSet(nums2));       // Output: 4
console.log("Approach 3 (Object):", singleNumberObject(nums2));    // Output: 4
console.log("Approach 4 (Reduce):", singleNumberReduce(nums2));    // Output: 4
console.log("Approach 5 (Bitwise Sum):", singleNumberBitwiseSum(nums2)); // Output: 4
console.log("\n");

console.log("Input: [1]");
console.log("Approach 1 (XOR):", singleNumberXOR(nums3));       // Output: 1
console.log("Approach 2 (Set):", singleNumberSet(nums3));       // Output: 1
console.log("Approach 3 (Object):", singleNumberObject(nums3));    // Output: 1
console.log("Approach 4 (Reduce):", singleNumberReduce(nums3));    // Output: 1
console.log("Approach 5 (Bitwise Sum):", singleNumberBitwiseSum(nums3)); // Output: 1
