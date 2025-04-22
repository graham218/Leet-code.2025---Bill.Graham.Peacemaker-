/*
    Bit Manipulation: Single Number

    Problem Statement:
    Given a non-empty array of integers nums, every element appears twice except
    for one. Find that single one.

    You must implement a solution with a linear runtime complexity and use
    only constant extra space.

    Constraints:
    1 <= nums.length <= 3 * 10^4
    -3 * 10^4 <= nums[i] <= 3 * 10^4
    Each element in nums appears twice except for one element which appears only once.
*/

// Approach 1: XOR Operation
// The XOR operation has the property that a ^ a = 0 and a ^ 0 = a.
// We can XOR all the numbers in the array. The duplicate numbers will cancel
// each other out, and the result will be the single number.
//
// Time Complexity: O(n)
// Space Complexity: O(1)
function singleNumberXOR(nums) {
    let result = 0;
    for (const num of nums) {
        result ^= num;
    }
    return result;
}

// Approach 2: Using a Set
// We can use a Set to keep track of the numbers we have seen.
// If we see a number for the first time, we add it to the Set.
// If we see a number again, we remove it from the Set.
// The only number left in the Set is the single number.
//
// Time Complexity: O(n)
// Space Complexity: O(n)
function singleNumberSet(nums) {
    const seen = new Set();
    for (const num of nums) {
        if (seen.has(num)) {
            seen.delete(num);
        } else {
            seen.add(num);
        }
    }
    return [...seen][0]; // Convert set to array and get the first element.
}

// Approach 3: Sum of Set - Sum of Array
//  1.  Create a set of the numbers.  This removes duplicates.
//  2.  Sum the numbers in the set.
//  3.  Sum the numbers in the original array.
//  4.  The single number is  (sumOfSet * 2) - sumOfArray
//
// Time Complexity: O(n)
// Space Complexity: O(n)
function singleNumberSum(nums) {
    const numSet = new Set(nums);
    let sumOfSet = 0;
    for (const num of numSet) {
        sumOfSet += num;
    }
    let sumOfArray = 0;
    for (const num of nums) {
        sumOfArray += num;
    }
    return (sumOfSet * 2) - sumOfArray;
}

// Approach 4: Using Reduce and Set (variation of Approach 2)
// This approach uses the reduce method along with a Set for a more concise
// implementation of the logic in Approach 2.
//
// Time Complexity: O(n)
// Space Complexity: O(n)
function singleNumberReduceSet(nums) {
    const seen = new Set();
    nums.reduce((_, num) => {
        if (seen.has(num)) {
            seen.delete(num);
        } else {
            seen.add(num);
        }
        return undefined; // reduce doesn't need a return value here.
    }, undefined); //initial value is not needed
    return [...seen][0];
}

// Approach 5: Bitwise XOR with Reduce
// This approach combines the bitwise XOR operation with the reduce method,
// providing a concise way to implement Approach 1.
//
// Time Complexity: O(n)
// Space Complexity: O(1)
function singleNumberXORReduce(nums) {
    return nums.reduce((acc, num) => acc ^ num, 0);
}

// Example Usage and Output
const nums = [2, 2, 1];
console.log("Input:", nums);
console.log("Single Number (XOR):", singleNumberXOR(nums));
console.log("Single Number (Set):", singleNumberSet(nums));
console.log("Single Number (Sum):", singleNumberSum(nums));
console.log("Single Number (Reduce & Set):", singleNumberReduceSet(nums));
console.log("Single Number (XOR & Reduce):", singleNumberXORReduce(nums));

const nums2 = [4, 1, 2, 1, 2];
console.log("\nInput:", nums2);
console.log("Single Number (XOR):", singleNumberXOR(nums2));
console.log("Single Number (Set):", singleNumberSet(nums2));
console.log("Single Number (Sum):", singleNumberSum(nums2));
console.log("Single Number (Reduce & Set):", singleNumberReduceSet(nums2));
console.log("Single Number (XOR & Reduce):", singleNumberXORReduce(nums2));

const nums3 = [1, 2, 3, 4, 5, 1, 2, 3, 4];
console.log("\nInput:", nums3);
console.log("Single Number (XOR):", singleNumberXOR(nums3));
console.log("Single Number (Set):", singleNumberSet(nums3));
console.log("Single Number (Sum):", singleNumberSum(nums3));
console.log("Single Number (Reduce & Set):", singleNumberReduceSet(nums3));
console.log("Single Number (XOR & Reduce):", singleNumberXORReduce(nums3));
