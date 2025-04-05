/*
Problem: 3Sum

Given an array of integers, find all unique triplets (three numbers) in the array which gives the sum of zero.

Example:
Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

Constraints:
-   0 <= nums.length <= 3000
-   -10^5 <= nums[i] <= 10^5
*/

/**
 * Approach 1: Brute Force
 * -   Iterate through all possible combinations of three numbers using three nested loops.
 * -   Check if the sum of the three numbers is equal to zero.
 * -   If the sum is zero, add the triplet to the result array.
 * -   Use a Set to avoid duplicate triplets.
 *
 * Complexity:
 * -   Time: O(n^3), where n is the length of the array.
 * -   Space: O(k), where k is the number of unique triplets.  In the worst case, k could be O(n^3), but in practice, it's much smaller.
 */
function threeSumBruteForce(nums) {
    const result = new Set(); // Use a Set to store unique triplets
    const n = nums.length;

    for (let i = 0; i < n - 2; i++) {
        for (let j = i + 1; j < n - 1; j++) {
            for (let k = j + 1; k < n; k++) {
                if (nums[i] + nums[j] + nums[k] === 0) {
                    // Sort the triplet to ensure uniqueness in the Set.
                    const triplet = [nums[i], nums[j], nums[k]].sort((a, b) => a - b);
                    result.add(triplet.toString()); // Use toString() as key for Set
                }
            }
        }
    }
    // Convert the set entries back to arrays.
    return Array.from(result).map(s => s.split(',').map(Number));
}

/**
 * Approach 2: Brute Force with Deduplication
 * -   Same as Brute Force, but with added deduplication logic.
 * -   Sort the input array first.
 * -   Skip duplicate numbers in the outer loops.
 *
 * Complexity:
 * -   Time: O(n^3), where n is the length of the array.
 * -   Space: O(k), where k is the number of unique triplets.
 */
function threeSumBruteForceDeduplication(nums) {
    const result = [];
    const n = nums.length;

    nums.sort((a, b) => a - b); // Sort the array to easily skip duplicates

    for (let i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] === nums[i - 1]) continue; // Skip duplicate for i
        for (let j = i + 1; j < n - 1; j++) {
            if (j > i + 1 && nums[j] === nums[j - 1]) continue; // Skip duplicate for j
            for (let k = j + 1; k < n; k++) {
                if (k > j + 1 && nums[k] === nums[k - 1]) continue; // Skip duplicate for k
                if (nums[i] + nums[j] + nums[k] === 0) {
                    result.push([nums[i], nums[j], nums[k]]);
                }
            }
        }
    }
    return result;
}



/**
 * Approach 3: Two Pointers
 * -   Sort the input array.
 * -   Iterate through the array using a single pointer `i`.
 * -   For each element at `i`, use two pointers, `left` and `right`, to find the other two numbers.
 * -   Move `left` and `right` towards each other based on the sum of the three numbers.
 * -   Skip duplicate numbers.
 *
 * Complexity:
 * -   Time: O(n^2), where n is the length of the array.  Sorting takes O(n log n), but the nested loop dominates.
 * -   Space: O(k), where k is the number of unique triplets.
 */
function threeSumTwoPointers(nums) {
    const result = [];
    const n = nums.length;

    nums.sort((a, b) => a - b); // Sort the array

    for (let i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] === nums[i - 1]) continue; // Skip duplicate for i

        let left = i + 1;
        let right = n - 1;

        while (left < right) {
            const sum = nums[i] + nums[left] + nums[right];

            if (sum === 0) {
                result.push([nums[i], nums[left], nums[right]]);
                // Skip duplicates for left and right
                while (left < right && nums[left] === nums[left + 1]) left++;
                while (left < right && nums[right] === nums[right - 1]) right--;
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return result;
}

/**
 * Approach 4: Hash Set
 * -   Iterate through the array using a single pointer `i`.
 * -   For each element at `i`, iterate through the rest of the array using pointer `j`.
 * -   Calculate the third number needed to make the sum zero: `complement = -(nums[i] + nums[j])`.
 * -   Use a hash set to check if the complement exists in the remaining part of the array.
 * -   Use a Set to avoid duplicate triplets.
 *
 * Complexity:
 * -   Time: O(n^2), where n is the length of the array.
 * -   Space: O(n) in the worst case, for the hash set.
 */
function threeSumHashSet(nums) {
    const result = new Set();
    const n = nums.length;

    for (let i = 0; i < n - 2; i++) {
        const seen = new Set();
        for (let j = i + 1; j < n; j++) {
            const complement = -(nums[i] + nums[j]);
            if (seen.has(complement)) {
                const triplet = [nums[i], nums[j], complement].sort((a, b) => a - b);
                result.add(triplet.toString());
            }
            seen.add(nums[j]);
        }
    }
    return Array.from(result).map(s => s.split(',').map(Number));
}

/**
 * Approach 5: Optimized Two Pointers with Early Exit
 * -   Similar to the Two Pointers approach, but with an optimization:
 * -   If the smallest number at i is greater than 0, break the loop, because sum cannot be 0.
 * -   If the largest number at i is less than 0, continue to the next i.
 *
 * Complexity:
 * -   Time: O(n^2), where n is the length of the array.
 * -   Space: O(k), where k is the number of unique triplets.
 */
function threeSumOptimized(nums) {
    const result = [];
    const n = nums.length;

    nums.sort((a, b) => a - b);

    for (let i = 0; i < n - 2; i++) {
        if (nums[i] > 0) break; // Optimization: If nums[i] > 0, no solution exists
        if (i > 0 && nums[i] === nums[i - 1]) continue;

        let left = i + 1;
        let right = n - 1;

        while (left < right) {
            const sum = nums[i] + nums[left] + nums[right];

            if (sum === 0) {
                result.push([nums[i], nums[left], nums[right]]);
                while (left < right && nums[left] === nums[left + 1]) left++;
                while (left < right && nums[right] === nums[right - 1]) right--;
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return result;
}

// Example usage:
const nums = [-1, 0, 1, 2, -1, -4];

console.log("Approach 1: Brute Force:", threeSumBruteForce(nums));
console.log("Approach 2: Brute Force with Deduplication:", threeSumBruteForceDeduplication(nums));
console.log("Approach 3: Two Pointers:", threeSumTwoPointers(nums));
console.log("Approach 4: Hash Set:", threeSumHashSet(nums));
console.log("Approach 5: Optimized Two Pointers:", threeSumOptimized(nums));
