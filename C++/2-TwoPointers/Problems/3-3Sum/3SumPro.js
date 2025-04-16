/**
 * Five different approaches to solve the 3Sum problem in JavaScript,
 * with detailed comments explaining the logic and real-world project implementations.
 */

/**
 * 1. Brute Force Approach
 * - The most straightforward approach, but also the least efficient.
 * - It uses three nested loops to iterate through all possible combinations of three numbers.
 * - Time Complexity: O(n^3), where n is the length of the input array.
 * - Space Complexity: O(1) - Constant extra space.
 * - Real-world use case: Good for small datasets or for verifying the correctness of other, more optimized solutions.  For example, in a test suite, you might use this to generate expected outputs for a small set of inputs to compare against the output of a faster algorithm.
 */
function threeSumBruteForce(nums) {
    const result = [];
    const n = nums.length;

    // Iterate through all possible combinations of three numbers
    for (let i = 0; i < n - 2; i++) {
        for (let j = i + 1; j < n - 1; j++) {
            for (let k = j + 1; k < n; k++) {
                if (nums[i] + nums[j] + nums[k] === 0) {
                    // Sort the triplet to ensure uniqueness and proper comparison
                    const triplet = [nums[i], nums[j], nums[k]].sort((a, b) => a - b);
                    // Check for duplicates before adding to the result
                    if (!containsTriplet(result, triplet)) {
                        result.push(triplet);
                    }
                }
            }
        }
    }
    return result;
}

/**
 * Helper function to check if a triplet already exists in the result array.
 * @param {number[][]} result - The array of result triplets.
 * @param {number[]} triplet - The triplet to check for.
 * @returns {boolean} - True if the triplet exists, false otherwise.
 */
function containsTriplet(result, triplet) {
    for (const existingTriplet of result) {
        if (
            existingTriplet[0] === triplet[0] &&
            existingTriplet[1] === triplet[1] &&
            existingTriplet[2] === triplet[2]
        ) {
            return true;
        }
    }
    return false;
}

/**
 * 2. Hash Set Approach
 * - Uses a hash set to store the numbers encountered so far.
 * - For each pair (nums[i], nums[j]), it checks if the complement (-nums[i] - nums[j]) exists in the hash set.
 * - This reduces the time complexity compared to the brute-force approach.
 * - Time Complexity: O(n^2), where n is the length of the input array.
 * - Space Complexity: O(n) -  For the hash set.
 * - Real-world use case: Useful in scenarios where you need to quickly check for the existence of a specific value within a dataset.  For example, in a web application, you might use this to check if a user ID has already been registered, or in a network application, to detect duplicate packets.
 */
function threeSumHashSet(nums) {
    const result = [];
    const n = nums.length;

    for (let i = 0; i < n - 2; i++) {
        const seen = new Set();
        for (let j = i + 1; j < n; j++) {
            const complement = -nums[i] - nums[j];
            if (seen.has(complement)) {
                const triplet = [nums[i], nums[j], complement].sort((a, b) => a - b);
                if (!containsTriplet(result, triplet)) {
                    result.push(triplet);
                }
            }
            seen.add(nums[j]);
        }
    }
    return result;
}



/**
 * 3. Two Pointers Approach (Optimized)
 * - The most efficient approach for solving the 3Sum problem.
 * - First, it sorts the input array.
 * - Then, it iterates through the array, and for each element nums[i], it uses two pointers (left and right) to find the other two numbers that sum up to -nums[i].
 * - Time Complexity: O(n^2), where n is the length of the input array.  Sorting takes O(n log n), but the two-pointer iteration is O(n^2), so O(n^2) dominates.
 * - Space Complexity: O(1) - Constant extra space.  Sorting is often done in-place.
 * - Real-world use case: This is a classic algorithm optimization technique used in many problems involving sorted data.  For example, finding pairs of numbers that sum to a target in a sorted array, or in database query optimization.
 */
function threeSumTwoPointers(nums) {
    const result = [];
    const n = nums.length;

    // Sort the array in ascending order.  This is crucial for the two-pointer approach.
    nums.sort((a, b) => a - b);

    for (let i = 0; i < n - 2; i++) {
        // Skip duplicate numbers for the first element
        if (i > 0 && nums[i] === nums[i - 1]) {
            continue;
        }

        let left = i + 1;
        let right = n - 1;

        while (left < right) {
            const sum = nums[i] + nums[left] + nums[right];
            if (sum === 0) {
                result.push([nums[i], nums[left], nums[right]]);
                // Skip duplicate numbers for the second and third elements
                while (left < right && nums[left] === nums[left + 1]) {
                    left++;
                }
                while (left < right && nums[right] === nums[right - 1]) {
                    right--;
                }
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
 * 4. Using a Map to Store Complements
 * - This approach pre-calculates and stores the complements of pairs of numbers in a map.
 * - It iterates through the array, and for each number, checks if its complement exists in the map.
 * - Time Complexity: O(n^2) in the worst case.
 * - Space Complexity: O(n^2) in the worst case.
 * - Real world use case: Useful when you need to find complementary pairs or triplets within a dataset, and you want to avoid redundant calculations. For example, in e-commerce, you might use this to find products that are frequently bought together.
 */
function threeSumWithMap(nums) {
    const result = [];
    const n = nums.length;
    const complementsMap = new Map();

    // Precalculate and store complements
    for (let i = 0; i < n - 1; i++) {
        for (let j = i + 1; j < n; j++) {
            const complement = -nums[i] - nums[j];
            if (!complementsMap.has(complement)) {
                complementsMap.set(complement, []);
            }
            complementsMap.get(complement).push([i, j]);
        }
    }

    for (let k = 0; k < n; k++) {
        if (complementsMap.has(nums[k])) {
            for (const [i, j] of complementsMap.get(nums[k])) {
                if (i !== k && j !== k) {
                    const triplet = [nums[i], nums[j], nums[k]].sort((a, b) => a - b);
                    if (!containsTriplet(result, triplet)) {
                        result.push(triplet);
                    }
                }
            }
        }
    }
    return result;
}

/**
 * 5. Recursive Approach with Backtracking
 * - This approach uses recursion and backtracking to explore all possible combinations of three numbers.
 * - It's generally less efficient than the two-pointer approach, but demonstrates a different problem-solving technique.
 * - Time Complexity: O(n^3) in the worst case, due to exploring all combinations.
 * - Space Complexity: O(n)  due to the depth of the recursion.
 * - Real-world use case:  Backtracking is a powerful technique for solving problems that involve searching for combinations or permutations.  Examples include solving Sudoku puzzles, generating all possible paths in a maze, or in AI, for exploring possible moves in a game.
 */
function threeSumRecursive(nums) {
    const result = [];
    const n = nums.length;
    const currentTriplet = [];

    // Sort for easier duplicate handling
    nums.sort((a, b) => a - b);

    function backtrack(index) {
        if (currentTriplet.length === 3) {
            if (currentTriplet.reduce((sum, num) => sum + num, 0) === 0) {
                // Make a copy before pushing to the result
                result.push([...currentTriplet]);
            }
            return;
        }

        if (index >= n) {
            return;
        }

        // Include the current number
        currentTriplet.push(nums[index]);
        backtrack(index + 1);
        currentTriplet.pop(); // Backtrack: Remove the last number

        // Skip duplicates
        while (index + 1 < n && nums[index] === nums[index + 1]) {
            index++;
        }
        // Exclude the current number
        backtrack(index + 1);
    }

    backtrack(0);
    return result;
}



// Example Usage and Output
const nums = [-1, 0, 1, 2, -1, -4];

console.log("Input: ", nums);
console.log("\n1. Brute Force Approach:");
console.log(threeSumBruteForce(nums)); // Output: [ [ -1, -1, 2 ], [ -1, 0, 1 ] ]

console.log("\n2. Hash Set Approach:");
console.log(threeSumHashSet(nums)); // Output: [ [ -1, -1, 2 ], [ -1, 0, 1 ] ]

console.log("\n3. Two Pointers Approach (Optimized):");
console.log(threeSumTwoPointers(nums)); // Output: [ [ -1, -1, 2 ], [ -1, 0, 1 ] ]

console.log("\n4. Using a Map to Store Complements:");
console.log(threeSumWithMap(nums)); // Output: [ [ -1, -1, 2 ], [ -1, 0, 1 ] ]

console.log("\n5. Recursive Approach with Backtracking:");
console.log(threeSumRecursive(nums)); // Output: [ [ -1, -1, 2 ], [ -1, 0, 1 ] ]
