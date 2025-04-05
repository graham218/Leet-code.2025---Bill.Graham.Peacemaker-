/**
 * **Two Pointers: Container With Most Water**
 *
 * You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the ith line are `(i, 0)` and `(i, height[i])`.
 *
 * Find two lines that together with the x-axis form a container, such that the container contains the most water.
 *
 * Return the maximum amount of water the container can contain.
 *
 * You may not slant the container.
 *
 * **Example 1:**
 *
 * ```
 * Input: height = [1,8,6,2,5,4,8,3,7]
 * Output: 49
 * Explanation: The vertical lines are shown in the above visual representation. In this case, the container with the most water (blue section) is formed by lines at i = 1 and j = 8 (height[1] = 8, height[8] = 7). The base of the container is 8 (distance between the lines) and the height is 7 (the shorter line). The area is 8 * 7 = 56.  However, another container at i=2 and j=8 has area = 6 * 6 = 36. The max is 49.
 * ```
 *
 * **Example 2:**
 *
 * ```
 * Input: height = [1,1]
 * Output: 1
 * ```
 *
 * **Constraints:**
 *
 * -   `n == height.length`
 * -   `2 <= n <= 10^5`
 * -   `0 <= height[i] <= 10^4`
 */

/**
 * **1. Brute Force Approach**
 *
 * -   Iterate through all possible pairs of lines (i, j).
 * -   Calculate the area for each pair.
 * -   Keep track of the maximum area found so far.
 *
 * **Time Complexity:** O(n^2) - Nested loops iterate through all pairs.
 * **Space Complexity:** O(1) - Only a constant amount of extra space is used.
 *
 * **Real-world application:**
 * -   This approach is straightforward and can be used as a baseline for comparison with more optimized solutions.  It's simple to understand, which can be useful in educational settings or for quick, non-performance-critical tasks.  For example, you might use this in a very small data processing script where performance isn't a primary concern.
 */
function maxAreaBruteForce(height) { // Removed : number[]
    let maxArea = 0;
    const n = height.length;

    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            const width = j - i;
            const minHeight = Math.min(height[i], height[j]);
            const area = width * minHeight;
            maxArea = Math.max(maxArea, area);
        }
    }

    return maxArea;
}

/**
 * **2. Two Pointers Approach**
 *
 * -   Initialize two pointers, `left` at the start and `right` at the end of the array.
 * -   Calculate the area between the lines at `left` and `right`.
 * -   Move the pointer with the smaller height towards the center.
 * -   Update the maximum area if a larger area is found.
 * -   Repeat until the pointers meet.
 *
 * **Time Complexity:** O(n) - Single pass through the array.
 * **Space Complexity:** O(1) - Constant extra space.
 *
 * **Real-world application:**
 * -   This is the most common and efficient solution.  It's applicable in scenarios where you need to optimize resource allocation based on two constraints, such as maximizing the volume of a container with varying width and height, or optimizing bandwidth allocation between two servers with different capacities.
 */
function maxAreaTwoPointers(height) { // Removed : number[]
    let maxArea = 0;
    let left = 0;
    let right = height.length - 1;

    while (left < right) {
        const width = right - left;
        const minHeight = Math.min(height[left], height[right]);
        const area = width * minHeight;
        maxArea = Math.max(maxArea, area);

        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return maxArea;
}

/**
 * **3. Optimized Two Pointers with Early Exit**
 *
 * -   Same as the Two Pointers approach, but adds an early exit condition.
 * -   If the current area is greater than the maximum possible area (based on the maximum possible height and width), the loop can be terminated.
 * -  This optimization is based on the idea that the maximum possible area is limited by the container's width and the maximum height in the array.
 *
 * **Time Complexity:** O(n) in the average case, but can be less if the early exit is triggered.  Worst case is still O(n).
 * **Space Complexity:** O(1)
 *
 * **Real-world application:**
 * -   This optimization is useful when dealing with datasets where you can quickly determine an upper bound on the solution.  For example, in a real-time system monitoring water levels in a series of interconnected tanks, if you need to find the maximum possible water that can be contained, and you have a good estimate of the maximum level and distance, you can use this optimization to avoid unnecessary calculations.
 */
function maxAreaOptimized(height) { // Removed : number[]
    let maxArea = 0;
    let left = 0;
    let right = height.length - 1;
    const maxHeight = Math.max(...height); // Find max height.

    while (left < right) {
        const width = right - left;
        const minHeight = Math.min(height[left], height[right]);
        const area = width * minHeight;
        maxArea = Math.max(maxArea, area);

        // Early exit condition:
        if (area > width * maxHeight) { // max possible area
            break;
        }

        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return maxArea;
}

/**
 * **4. Two Pointers with Skip Logic**
 *
 * - Similar to the two-pointer approach, but instead of simply moving the pointer, it skips over smaller heights.
 * - If the current height at a pointer is smaller than the previous height, move the pointer until you find a larger height.
 *
 * **Time Complexity:** O(n) in the average case, but can be less if there are many smaller heights. Worst case is O(n).
 * **Space Complexity:** O(1)
 *
 * **Real-world application:**
 * -  This approach is beneficial in scenarios where the input data has regions of consistently low values.  For instance, imagine optimizing the flow of goods between warehouses along a transportation route with varying capacities. If you encounter a series of warehouses with very low capacity, you can quickly skip them to find more significant bottlenecks or storage opportunities.
 */
function maxAreaSkipPointers(height) { // Removed : number[]
    let maxArea = 0;
    let left = 0;
    let right = height.length - 1;

    while (left < right) {
        const width = right - left;
        const minHeight = Math.min(height[left], height[right]);
        const area = width * minHeight;
        maxArea = Math.max(maxArea, area);

        if (height[left] < height[right]) {
            const currentLeftHeight = height[left];
            while (left < right && height[left] <= currentLeftHeight) {
                left++;
            }
        } else {
            const currentRightHeight = height[right];
            while (left < right && height[right] <= currentRightHeight) {
                right--;
            }
        }
    }

    return maxArea;
}

/**
 * **5. Divide and Conquer Approach**
 *
 * -   Recursively divide the problem into smaller subproblems.
 * -   Find the maximum area in the left half, the right half, and the area formed by the tallest lines crossing the midpoint.
 * -   Combine the results to get the overall maximum area.
 *
 * **Time Complexity:** O(n log n) - Due to the divide-and-conquer nature.
 * **Space Complexity:** O(log n) -  Due to the recursive call stack.
 *
 * **Real-world application:**
 * -   While less efficient than the two-pointer approach for this specific problem, divide and conquer is a powerful paradigm for solving many other problems.  For example, in parallel processing, you could divide the task of optimizing container loading across multiple processors, each handling a subset of containers, and then combine the results to find the global optimum.
 */

function maxAreaDivideAndConquer(height) { // Removed : number[]
    function findMaxArea(left, right) { // Removed : number, : number
        if (left >= right) {
            return 0;
        }

        const mid = Math.floor((left + right) / 2);
        const maxAreaLeft = findMaxArea(left, mid);
        const maxAreaRight = findMaxArea(mid + 1, right);

        let maxCrossingArea = 0;
        let l = mid, r = mid + 1;
        let minHeight = Math.min(height[l], height[r]);
        maxCrossingArea = Math.max(maxCrossingArea, minHeight);

        while (l > left || r < right) {
            if ((l > left && height[l - 1] > height[r + 1]) || r === right) {
                l--;
                minHeight = Math.min(minHeight, height[l]);
            } else {
                r++;
                minHeight = Math.min(minHeight, height[r]);
            }
            maxCrossingArea = Math.max(maxCrossingArea, minHeight * (r - l));
        }
        return Math.max(maxAreaLeft, maxAreaRight, maxCrossingArea);
    }
    return findMaxArea(0, height.length - 1);
}

/**
 * **6. Dynamic Programming (DP) Approach**
 *
 * -   Create a DP table where `dp[i]` stores the maximum area considering the lines from index 0 to `i`.
 * -   Iterate through the array, and for each index `i`, iterate from 0 to `i` to find the maximum area.
 * -   Although DP *can* be used, it's not efficient for this problem as it doesn't exploit the problem's characteristics effectively.
 *
 * **Time Complexity:** O(n^2)
 * **Space Complexity:** O(n)
 *
 * **Real-world application:**
 * -   While not optimal here, DP is crucial for problems with overlapping subproblems.  For instance, in supply chain optimization, you might use DP to determine the optimal sequence of shipments to minimize costs, where the cost of shipping to a particular location depends on the costs of shipping to previous locations.  In this specific Container problem, DP is less suitable because the subproblems (finding the maximum area up to a certain index) don't have the overlapping nature that DP excels at exploiting, and the two-pointer approach is more direct and efficient.
 */
function maxAreaDP(height) { // Removed : number[]
    const n = height.length;
    const dp = new Array(n).fill(0);

    for (let i = 1; i < n; i++) {
        for (let j = 0; j < i; j++) {
            const width = i - j;
            const minHeight = Math.min(height[i], height[j]);
            dp[i] = Math.max(dp[i], width * minHeight);
        }
        dp[i] = Math.max(dp[i], dp[i - 1]); // Ensure dp[i] is at least as large as dp[i-1]
    }
    return dp[n - 1];
}

// Example usage:
const height1 = [1, 8, 6, 2, 5, 4, 8, 3, 7];
const height2 = [1, 1];
const height3 = [4, 3, 2, 1, 4];
const height4 = [1, 2, 1];

console.log("Brute Force:");
console.log(maxAreaBruteForce(height1));
console.log(maxAreaBruteForce(height2));
console.log(maxAreaBruteForce(height3));
console.log(maxAreaBruteForce(height4));


console.log("\nTwo Pointers:");
console.log(maxAreaTwoPointers(height1));
console.log(maxAreaTwoPointers(height2));
console.log(maxAreaTwoPointers(height3));
console.log(maxAreaTwoPointers(height4));


console.log("\nOptimized Two Pointers:");
console.log(maxAreaOptimized(height1));
console.log(maxAreaOptimized(height2));
console.log(maxAreaOptimized(height3));
console.log(maxAreaOptimized(height4));


console.log("\nSkip Pointers:");
console.log(maxAreaSkipPointers(height1));
console.log(maxAreaSkipPointers(height2));
console.log(maxAreaSkipPointers(height3));
console.log(maxAreaSkipPointers(height4));

console.log("\nDivide and Conquer:");
console.log(maxAreaDivideAndConquer(height1));
console.log(maxAreaDivideAndConquer(height2));
console.log(maxAreaDivideAndConquer(height3));
console.log(maxAreaDivideAndConquer(height4));

console.log("\nDynamic Programming:");
console.log(maxAreaDP(height1));
console.log(maxAreaDP(height2));
console.log(maxAreaDP(height3));
console.log(maxAreaDP(height4));
