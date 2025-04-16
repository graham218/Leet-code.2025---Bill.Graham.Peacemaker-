/**
 * House Robber Problem - 5 Dynamic Programming Approaches
 *
 * Problem Statement:
 * Given an array representing the amount of money in each house,
 * determine the maximum amount you can rob tonight without alerting
 * the police (you can't rob adjacent houses).
 */

const houseRobber = {
    // Test cases
    testCases: [
        [1, 2, 3, 1],
        [2, 7, 9, 3, 1],
        [2, 1, 1, 2],
        [5, 1, 2, 6, 3, 4, 7, 2],
        [100, 50, 400, 200, 100]
    ],

    // Approach 1: Recursive (Top-down) - Naive
    recursiveRob: function(nums, i = nums.length - 1) {
        if (i < 0) return 0;
        return Math.max(
            this.recursiveRob(nums, i - 1),
            this.recursiveRob(nums, i - 2) + nums[i]
        );
    },

    // Approach 2: Recursive with Memoization (Top-down)
    memoRob: function(nums) {
        const memo = new Array(nums.length).fill(-1);

        const robHelper = (i) => {
            if (i < 0) return 0;
            if (memo[i] >= 0) return memo[i];

            const result = Math.max(
                robHelper(i - 1),
                robHelper(i - 2) + nums[i]
            );
            memo[i] = result;
            return result;
        };

        return robHelper(nums.length - 1);
    },

    // Approach 3: Iterative with Tabulation (Bottom-up)
    iterativeRob: function(nums) {
        if (nums.length === 0) return 0;
        if (nums.length === 1) return nums[0];

        const dp = new Array(nums.length);
        dp[0] = nums[0];
        dp[1] = Math.max(nums[0], nums[1]);

        for (let i = 2; i < nums.length; i++) {
            dp[i] = Math.max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[nums.length - 1];
    },

    // Approach 4: Iterative with Constant Space (Optimized DP)
    optimizedRob: function(nums) {
        let prev1 = 0; // Represents dp[i-1]
        let prev2 = 0; // Represents dp[i-2]

        for (const num of nums) {
            const temp = prev1;
            prev1 = Math.max(prev1, prev2 + num);
            prev2 = temp;
        }

        return prev1;
    },

    // Approach 5: Dynamic Programming with even/odd positions
    evenOddRob: function(nums) {
        let even = 0;
        let odd = 0;

        for (let i = 0; i < nums.length; i++) {
            if (i % 2 === 0) {
                even = Math.max(even + nums[i], odd);
            } else {
                odd = Math.max(odd + nums[i], even);
            }
        }

        return Math.max(even, odd);
    },

    // Run all approaches and display results
    runAll: function() {
        console.log("House Robber - Dynamic Programming Approaches\n");
        console.log("Test Cases:", this.testCases, "\n");

        this.testCases.forEach((testCase, idx) => {
            console.log(`=== Test Case ${idx + 1}: [${testCase}] ===`);

            // Approach 1
            console.log("1. Recursive (Top-down):",
                this.recursiveRob(testCase));

            // Approach 2
            console.log("2. Memoization (Top-down):",
                this.memoRob(testCase));

            // Approach 3
            console.log("3. Iterative DP (Bottom-up):",
                this.iterativeRob(testCase));

            // Approach 4
            console.log("4. Optimized DP (Constant Space):",
                this.optimizedRob(testCase));

            // Approach 5
            console.log("5. Even/Odd Position DP:",
                this.evenOddRob(testCase));

            console.log(); // Add space between test cases
        });
    }
};

// Execute all approaches
houseRobber.runAll();