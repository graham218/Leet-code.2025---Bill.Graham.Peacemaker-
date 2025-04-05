/**
 * Kadane's Algorithm: Maximum Subarray Sum
 *
 * Problem:
 * Given an array of integers, find the contiguous subarray (containing at least one number)
 * which has the largest sum and return its sum.
 *
 * For example, given the array [-2, 1, -3, 4, -1, 2, 1, -5, 4], the contiguous subarray [4, -1, 2, 1]
 * has the largest sum = 6.
 */

/**
 * Approach 1: Basic Kadane's Algorithm
 *
 * Description:
 * This is the most straightforward implementation of Kadane's Algorithm.  It iterates through the
 * array, keeping track of the current maximum sum and the overall maximum sum.  If the current
 * sum becomes negative, it's reset to 0, as a negative sum cannot contribute to a larger
 * overall sum.
 *
 * Real-World Application:
 * - Stock Price Analysis: Finding the maximum profit over a period by identifying the
 * most profitable consecutive days.  The input array represents daily stock price changes.
 *
 * Example:
 * Input: [-2, 1, -3, 4, -1, 2, 1, -5, 4]
 * Output: 6
 */
function kadanesAlgorithmBasic(nums) {
  let maxSoFar = -Infinity;  // Initialize to negative infinity to handle arrays with all negative numbers
  let currentMax = 0;

  for (let i = 0; i < nums.length; i++) {
    currentMax += nums[i];
    if (currentMax > maxSoFar) {
      maxSoFar = currentMax;
    }
    if (currentMax < 0) {
      currentMax = 0;
    }
  }
  return maxSoFar;
}

/**
 * Approach 2: Kadane's Algorithm with Start and End Indices
 *
 * Description:
 * This variation of Kadane's Algorithm not only finds the maximum subarray sum but also
 * keeps track of the starting and ending indices of the maximum subarray.  This is useful
 * when you need to know the actual subarray that produces the maximum sum.
 *
 * Real-World Application:
 * - Finding the most profitable time range in a business:  Identifying the specific start
 * and end dates of a period with the highest revenue.
 *
 * Example:
 * Input: [-2, 1, -3, 4, -1, 2, 1, -5, 4]
 * Output: { maxSum: 6, startIndex: 3, endIndex: 6 }  (Subarray: [4, -1, 2, 1])
 */
function kadanesAlgorithmWithIndices(nums) {
  let maxSoFar = -Infinity;
  let currentMax = 0;
  let start = 0;
  let end = 0;
  let tempStart = 0;

  for (let i = 0; i < nums.length; i++) {
    currentMax += nums[i];
    if (currentMax > maxSoFar) {
      maxSoFar = currentMax;
      start = tempStart;
      end = i;
    }
    if (currentMax < 0) {
      currentMax = 0;
      tempStart = i + 1; // Start of a new potential subarray
    }
  }
  return { maxSum: maxSoFar, startIndex: start, endIndex: end };
}

/**
 * Approach 3: Kadane's Algorithm with Empty Array Handling
 *
 * Description:
 * This version explicitly handles the case where the input array is empty.  It returns 0
 * in this case, which is a reasonable default for the maximum sum of an empty subarray.
 *
 * Real-World Application:
 * - Data analysis where some datasets might be empty:  Ensuring your analysis code
 * doesn't crash or produce incorrect results when given empty input.
 *
 * Example:
 * Input: []
 * Output: 0
 */
function kadanesAlgorithmWithEmptyArray(nums) {
  if (nums.length === 0) {
    return 0;
  }
  let maxSoFar = -Infinity;
  let currentMax = 0;

  for (let i = 0; i < nums.length; i++) {
    currentMax += nums[i];
    if (currentMax > maxSoFar) {
      maxSoFar = currentMax;
    }
    if (currentMax < 0) {
      currentMax = 0;
    }
  }
  return maxSoFar;
}

/**
 * Approach 4: Kadane's Algorithm with All Negative Numbers
 *
 * Description:
 * This version handles the case where the input array contains only negative numbers.
 * In this scenario, the maximum subarray sum is the largest negative number.
 *
 * Real-World Application:
 * - Financial analysis of a consistently declining stock:  Determining the least negative
 * loss over a period.
 *
 * Example:
 * Input: [-2, -1, -3, -4, -1, -2, -1, -5, -4]
 * Output: -1
 */
function kadanesAlgorithmAllNegative(nums) {
  if (nums.length === 0) {
      return 0;
  }
  let maxSoFar = nums[0]; // Initialize with the first element
  let currentMax = nums[0];

  for (let i = 1; i < nums.length; i++) {
    currentMax = Math.max(nums[i], currentMax + nums[i]);
    maxSoFar = Math.max(maxSoFar, currentMax);
  }
  return maxSoFar;
}


/**
 * Approach 5: Kadane's Algorithm with Circular Array Handling
 *
 * Description:
 * This approach extends Kadane's Algorithm to handle circular arrays.  In a circular array,
 * the end of the array is considered to be connected to the beginning.  The maximum subarray
 * sum can either be a regular subarray or a subarray that wraps around.
 *
 * Real-World Application:
 * - Analyzing cyclical data, such as seasonal sales variations:  Finding the period with the
 * highest total sales, even if it spans across the year-end.
 *
 * Example:
 * Input: [1, -2, 3, -2, 2]  (Circular array: [1, -2, 3, -2, 2, 1, -2, 3, -2, 2, ...])
 * Output: 5  (Subarray: [2, 1, -5, 4, 1] wraps around to include the first element 1,  1 + 4)
 *
 * Explanation:
 * The maximum subarray sum in a circular array can be one of two cases:
 * 1. The maximum subarray is a normal subarray (not wrapping around).
 * 2. The maximum subarray wraps around.  In this case, the sum is equal to the total sum of the array minus the minimum subarray sum.
 */
function kadanesAlgorithmCircular(nums) {
  if (nums.length === 0) {
    return 0;
  }

  let maxSoFar = -Infinity;
  let currentMax = 0;
  let minSoFar = Infinity;
  let currentMin = 0;
  let totalSum = 0;

  for (let i = 0; i < nums.length; i++) {
    // Calculate max sum
    currentMax = Math.max(nums[i], currentMax + nums[i]);
    maxSoFar = Math.max(maxSoFar, currentMax);

    // Calculate min sum
    currentMin = Math.min(nums[i], currentMin + nums[i]);
    minSoFar = Math.min(minSoFar, currentMin);

    totalSum += nums[i];
  }

  if (maxSoFar < 0) { // If all numbers are negative, return the largest negative number
    return maxSoFar;
  }

  // Calculate the maximum sum that wraps around
  const wrappedSum = totalSum - minSoFar;

  // Return the larger of the two sums: the regular max sum or the wrapped sum.
  return Math.max(maxSoFar, wrappedSum);
}


/**
 * Approach 6: Kadane's Algorithm with Visualization (Conceptual)
 *
 * Description:
 * This approach focuses on *how* you might visualize Kadane's Algorithm, rather than providing
 * a directly executable function.  In a real-world application, this would involve using a
 * charting library (like D3.js or Chart.js) to create an interactive visualization.
 *
 * Real-World Application:
 * - Creating a dashboard for monitoring real-time data streams:  Visualizing the maximum
 * cumulative value (e.g., website traffic, server load) over time, with clear
 * indicators of when the maximum subarray sum changes.
 *
 * Visualization Concepts:
 * 1. Input Array: Represent the input array as a series of bars or points on a graph.
 * 2. Current Maximum Sum:  Display a line or area chart that tracks the `currentMax` value
 * as the algorithm iterates.  This line would reset to 0 whenever `currentMax` becomes negative.
 * 3. Overall Maximum Sum:  Highlight the `maxSoFar` value with a horizontal line or a shaded
 * area, clearly indicating the largest sum encountered so far.
 * 4. Subarray Highlighting:  Dynamically highlight the subarray that contributes to the
 * `maxSoFar` at each step.  This could be done by changing the color or thickness of
 * the bars representing the subarray.
 * 5. Interactive Controls:  Add controls to step through the algorithm, pause, resume,
 * and reset, allowing users to see how the variables change with each iteration.
 *
 * Note: This is not a directly executable function.  It's a description of how to *visualize*
 * Kadane's Algorithm.  Implementing this would require a front-end framework and a
 * visualization library.
 */
function kadanesAlgorithmVisualization() {
  //  This function would *not* contain the core Kadane's logic.
  //  Instead, it would describe the steps involved in visualizing the algorithm.

  console.log("Kadane's Algorithm Visualization:");
  console.log("1. Represent the input array as bars or points on a graph.");
  console.log("2. Plot the 'currentMax' value as a line or area chart, resetting to 0 when negative.");
  console.log("3. Highlight the 'maxSoFar' value with a horizontal line or shaded area.");
  console.log("4. Dynamically highlight the subarray contributing to 'maxSoFar'.");
  console.log("5. Add interactive controls (step, pause, reset) to explore the algorithm.");
  console.log("   (Implementation requires a visualization library like D3.js or Chart.js)");
}



// Example Usage and Output
const array1 = [-2, 1, -3, 4, -1, 2, 1, -5, 4];
const array2 = [];
const array3 = [-2, -1, -3, -4, -1, -2, -1, -5, -4];
const array4 = [1, -2, 3, -2, 2];


console.log("Example Usage and Output:");
console.log("--------------------------");

console.log("Approach 1: Basic Kadane's Algorithm");
console.log("Input:", array1);
console.log("Output:", kadanesAlgorithmBasic(array1)); // Output: 6

console.log("\nApproach 2: Kadane's Algorithm with Start and End Indices");
console.log("Input:", array1);
const result2 = kadanesAlgorithmWithIndices(array1);
console.log("Output:", result2); // Output: { maxSum: 6, startIndex: 3, endIndex: 6 }

console.log("\nApproach 3: Kadane's Algorithm with Empty Array Handling");
console.log("Input:", array2);
console.log("Output:", kadanesAlgorithmWithEmptyArray(array2)); // Output: 0

console.log("\nApproach 4: Kadane's Algorithm with All Negative Numbers");
console.log("Input:", array3);
console.log("Output:", kadanesAlgorithmAllNegative(array3)); // Output: -1

console.log("\nApproach 5: Kadane's Algorithm with Circular Array Handling");
console.log("Input:", array4);
console.log("Output:", kadanesAlgorithmCircular(array4)); // Output: 5

console.log("\nApproach 6: Kadane's Algorithm with Visualization (Conceptual)");
kadanesAlgorithmVisualization(); // Output: (Conceptual description - see function definition)
