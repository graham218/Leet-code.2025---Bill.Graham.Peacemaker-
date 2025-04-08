/*
    Largest Rectangle in Histogram: 5 Approaches in JavaScript

    Problem:
    Given an array of integers heights representing the histogram's bar heights
    where the width of each bar is 1, find the area of the largest rectangle in the histogram.

    Constraints:
    - 1 <= heights.length <= 10^5
    - 0 <= heights[i] <= 10^4
*/

/**
 * Approach 1: Brute Force
 * For each bar, expand left and right to find the maximum width rectangle.
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
function largestRectangleAreaBruteForce(heights) {
    let maxArea = 0;
    const n = heights.length;

    for (let i = 0; i < n; i++) {
        let width = 1;
        let left = i - 1;
        let right = i + 1;

        // Expand left
        while (left >= 0 && heights[left] >= heights[i]) {
            width++;
            left--;
        }

        // Expand right
        while (right < n && heights[right] >= heights[i]) {
            width++;
            right++;
        }

        maxArea = Math.max(maxArea, heights[i] * width);
    }

    return maxArea;
}

/**
 * Approach 2: Divide and Conquer
 * Recursively divide the histogram and find the largest rectangle in each half.
 * The largest rectangle can also span across the two halves.
 * Time Complexity: O(n log n) in average case, O(n^2) in worst case (if the array is sorted)
 * Space Complexity: O(n) due to recursion stack
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
    const midArea = heights[minIndex] * (end - start + 1);

    return Math.max(leftArea, rightArea, midArea);
}

function largestRectangleAreaDivideAndConquerHelper(heights) {
    return largestRectangleAreaDivideAndConquer(heights, 0, heights.length - 1);
}


/**
 * Approach 3: Stack
 * Use a stack to keep track of increasing bar indices.
 * When a smaller bar is encountered, calculate the area with the previous bars in the stack.
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function largestRectangleAreaStack(heights) {
    let maxArea = 0;
    const n = heights.length;
    const stack = [];
    let i = 0;

    while (i < n || stack.length > 0) { // Corrected loop condition
        if (i < n && (stack.length === 0 || heights[i] >= heights[stack[stack.length - 1]])) {
            stack.push(i);
            i++;
        } else {
            const top = stack.pop();
            const width = stack.length === 0 ? i : i - stack[stack.length - 1] - 1;
            maxArea = Math.max(maxArea, heights[top] * width);
        }
    }
    return maxArea;
}

/**
 * Approach 4: Stack (Optimized)
 * Optimized version of the stack approach.  Append 0 to the heights array to ensure
 * all elements in the stack are processed.
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function largestRectangleAreaStackOptimized(heights) {
    let maxArea = 0;
    const n = heights.length;
    const stack = [];
    const modifiedHeights = [...heights, 0]; // Append 0 to handle remaining bars in stack

    for (let i = 0; i < modifiedHeights.length; i++) {
        while (stack.length > 0 && modifiedHeights[i] < modifiedHeights[stack[stack.length - 1]]) {
            const top = stack.pop();
            const width = stack.length === 0 ? i : i - stack[stack.length - 1] - 1;
            maxArea = Math.max(maxArea, modifiedHeights[top] * width);
        }
        stack.push(i);
    }

    return maxArea;
}

/**
 * Approach 5: Using Min-Left and Min-Right Arrays
 * Calculate the leftmost and rightmost boundaries for each bar that are greater or equal to the current bar.
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function largestRectangleAreaMinLeftRight(heights) {
    const n = heights.length;
    const left = new Array(n);
    const right = new Array(n);
    let maxArea = 0;

    // Calculate left boundaries
    left[0] = 0;
    for (let i = 1; i < n; i++) {
        let p = i - 1;
        while (p >= 0 && heights[p] >= heights[i]) {
            p = left[p] - 1;
        }
        left[i] = Math.max(0, p + 1); // Ensure left[i] is not negative
    }

    // Calculate right boundaries
    right[n - 1] = n - 1;
    for (let i = n - 2; i >= 0; i--) {
        let p = i + 1;
        while (p < n && heights[p] >= heights[i]) {
            p = right[p] + 1;
        }
        right[i] = Math.min(n - 1, p - 1); // Ensure right[i] is not out of bounds.
    }

    // Calculate max area
    for (let i = 0; i < n; i++) {
        maxArea = Math.max(maxArea, heights[i] * (right[i] - left[i] + 1));
    }
    return maxArea;
}



// Example Usage:
const heights = [2, 1, 5, 6, 2, 3];
console.log("Heights:", heights);

// Brute Force
console.log("Largest Rectangle Area (Brute Force):", largestRectangleAreaBruteForce(heights)); // Output: 10

// Divide and Conquer
console.log("Largest Rectangle Area (Divide and Conquer):", largestRectangleAreaDivideAndConquerHelper(heights)); // Output: 10

// Stack
console.log("Largest Rectangle Area (Stack):", largestRectangleAreaStack(heights)); // Output: 10

// Stack Optimized
console.log("Largest Rectangle Area (Stack Optimized):", largestRectangleAreaStackOptimized(heights)); // Output: 10

// Min-Left and Min-Right Arrays
console.log("Largest Rectangle Area (Min-Left/Right):", largestRectangleAreaMinLeftRight(heights)); // Output: 10
