/*
Largest Rectangle in Histogram: JavaScript Solutions

Problem:
Given an array of integers heights representing the histogram's bar heights where the width of each bar is 1, find the area of the largest rectangle in the histogram.

Constraints:
* 1 <= heights.length <= 10^5
* 0 <= heights[i] <= 10^4
*/

/**
 * Approach 1: Brute Force
 *
 * For each bar, consider it as the minimum height and expand left and right.
 * Calculate the area with this minimum height and update the maximum area.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
function largestRectangleAreaBruteForce(heights) {
    let maxArea = 0;
    const n = heights.length;

    for (let i = 0; i < n; i++) {
        let minHeight = heights[i];
        for (let j = i; j < n; j++) {
            minHeight = Math.min(minHeight, heights[j]);
            const width = j - i + 1;
            maxArea = Math.max(maxArea, minHeight * width);
        }
    }
    return maxArea;
}

/**
 * Approach 2: Divide and Conquer
 *
 * Recursively divide the histogram into subproblems.
 * The largest rectangle can be in the left subproblem, right subproblem,
 * or across the middle.
 *
 * Time Complexity: O(n log n) in average case, O(n^2) in worst case
 * Space Complexity: O(n log n)
 */
function largestRectangleAreaDivideAndConquer(heights, start, end) {
    if (start > end) {
        return 0;
    }

    if (start === end) {
        return heights[start];
    }

    let minIndex = start;
    for (let i = start + 1; i <= end; i++) {
        if (heights[i] < heights[minIndex]) {
            minIndex = i;
        }
    }

    const leftArea = largestRectangleAreaDivideAndConquer(heights, start, minIndex - 1);
    const rightArea = largestRectangleAreaDivideAndConquer(heights, minIndex + 1, end);
    const middleArea = heights[minIndex] * (end - start + 1);

    return Math.max(leftArea, rightArea, middleArea);
}

function largestRectangleAreaDivideAndConquerMain(heights) {
    return largestRectangleAreaDivideAndConquer(heights, 0, heights.length - 1);
}


/**
 * Approach 3: Stack
 *
 * Use a stack to keep track of increasing heights.
 * When a smaller height is encountered, calculate the area with the heights in the stack.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function largestRectangleAreaStack(heights) {
    const n = heights.length;
    const stack = [];
    let maxArea = 0;
    let i = 0;

    while (i < n || stack.length > 0) {
        if (i < n && (stack.length === 0 || heights[i] >= heights[stack[stack.length - 1]])) {
            stack.push(i);
            i++;
        } else {
            const top = stack.pop();
            const width = stack.length === 0 ? i : i - stack[stack.length - 1] - 1;
            const area = heights[top] * width;
            maxArea = Math.max(maxArea, area);
        }
    }
    return maxArea;
}

/**
 * Approach 4: Optimized Stack
 *
 * Similar to the previous stack approach, but adds 0 to the beginning and end
 * of the heights array to simplify the boundary conditions.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function largestRectangleAreaOptimizedStack(heights) {
    const n = heights.length;
    const modifiedHeights = [0, ...heights, 0]; // Add 0 at the beginning and end
    const stack = [];
    let maxArea = 0;

    for (let i = 0; i < modifiedHeights.length; i++) {
        while (stack.length > 0 && modifiedHeights[i] < modifiedHeights[stack[stack.length - 1]]) {
            const top = stack.pop();
            const width = i - stack[stack.length - 1] - 1;
            const area = modifiedHeights[top] * width;
            maxArea = Math.max(maxArea, area);
        }
        stack.push(i);
    }
    return maxArea;
}

/**
 * Approach 5: Monolithic Stack (Most Efficient)
 *
 * This approach uses a single pass and a stack to maintain indices of monotonically increasing heights.  It's the most efficient
 * and commonly used solution in real-world applications due to its optimal performance.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function largestRectangleAreaMonolithicStack(heights) {
    const n = heights.length;
    const stack = []; // Stack to store *indices* of bars, maintaining increasing height order.
    let maxArea = 0;

    for (let i = 0; i <= n; i++) {
        // Iterate through the heights, including a sentinel (virtual bar of height 0) at the end (i = n).
        // The sentinel ensures that all bars in the stack are processed.
        const currentHeight = i === n ? 0 : heights[i];

        // While the stack is not empty and the current height is *less* than the height of the bar at the
        // index at the top of the stack, we've found a potential right boundary for the rectangle
        // formed by the bar at the top of the stack.
        while (stack.length > 0 && currentHeight < heights[stack[stack.length - 1]]) {
            const topIndex = stack.pop(); // Get the index of the bar at the top of the stack.
            const barHeight = heights[topIndex]; // Height of the popped bar.

            // Calculate the width of the rectangle.
            // If the stack is empty, it means the popped bar extends to the beginning of the histogram.
            // Otherwise, the width is the distance between the current bar (i) and the bar at the
            // new top of the stack (exclusive).
            const width = stack.length === 0 ? i : i - stack[stack.length - 1] - 1;

            // Calculate the area of the rectangle.
            const area = barHeight * width;
            maxArea = Math.max(maxArea, area); // Update the maximum area found so far.
        }

        // Push the *index* of the current bar onto the stack.  This maintains the monotonically increasing
        // property of the stack.  If the current height is greater than or equal to the height of the bar
        // at the top of the stack, it means we can potentially expand the rectangle formed by the
        // current bar to the right.
        stack.push(i);
    }

    return maxArea;
}



// Example Usage and Verification
const heights = [2, 1, 5, 6, 2, 3];
console.log("Heights:", heights);

// Brute Force
const result1 = largestRectangleAreaBruteForce(heights);
console.log("Largest Rectangle Area (Brute Force):", result1); // Expected: 10

// Divide and Conquer
const result2 = largestRectangleAreaDivideAndConquerMain(heights);
console.log("Largest Rectangle Area (Divide and Conquer):", result2); // Expected: 10

// Stack
const result3 = largestRectangleAreaStack(heights);
console.log("Largest Rectangle Area (Stack):", result3); // Expected: 10

// Optimized Stack
const result4 = largestRectangleAreaOptimizedStack(heights);
console.log("Largest Rectangle Area (Optimized Stack):", result4); // Expected: 10

// Monolithic Stack
const result5 = largestRectangleAreaMonolithicStack(heights);
console.log("Largest Rectangle Area (Monolithic Stack):", result5); // Expected: 10
