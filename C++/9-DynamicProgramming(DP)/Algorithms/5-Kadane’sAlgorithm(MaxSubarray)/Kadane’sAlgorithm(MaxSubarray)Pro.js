/*
Kadane's Algorithm: Finding the Maximum Subarray Sum

Kadane's algorithm is used to find the maximum sum of a contiguous subarray within a one-dimensional array of numbers. It works by iterating through the array, keeping track of the current maximum sum and the overall maximum sum.

Here are five different approaches to implementing Kadane's algorithm, each with a real-world project implementation scenario:
*/

// 1. Basic Kadane's Algorithm
//    - Project Application: Stock Price Analysis
//    - Description: Find the maximum profit that can be made by buying and selling a stock once.  The input array represents the daily stock prices.
function kadaneBasic(arr) {
  let maxSoFar = 0;
  let currentMax = 0;

  for (let i = 0; i < arr.length; i++) {
    currentMax = Math.max(0, currentMax + arr[i]);
    maxSoFar = Math.max(maxSoFar, currentMax);
  }
  return maxSoFar;
}

// 2. Kadane's Algorithm with Start and End Index Tracking
//    - Project Application: Finding the most profitable time period.
//    - Description:  In addition to the maximum sum, track the start and end indices of the subarray that yields this maximum sum.
function kadaneWithIndex(arr) {
    let maxSoFar = -Infinity;
    let currentMax = 0;
    let start = 0;
    let end = 0;
    let tempStart = 0;

    for (let i = 0; i < arr.length; i++) {
        if (currentMax + arr[i] > arr[i]) {
            currentMax += arr[i];
        } else {
            currentMax = arr[i];
            tempStart = i; // Start a new subarray from here
        }

        if (currentMax > maxSoFar) {
            maxSoFar = currentMax;
            start = tempStart;
            end = i;
        }
    }
    return { maxSum: maxSoFar, startIndex: start, endIndex: end };
}

// 3. Kadane's Algorithm with Negative Numbers Only Handling
//    - Project Application: Analyzing financial losses.
//    - Description:  Handles arrays where all numbers are negative.  In this case, the algorithm returns the largest negative number (least loss).
function kadaneNegative(arr) {
  let maxSoFar = arr[0]; // Initialize with the first element
  let currentMax = arr[0];

  for (let i = 1; i < arr.length; i++) {
    currentMax = Math.max(arr[i], currentMax + arr[i]);
    maxSoFar = Math.max(maxSoFar, currentMax);
  }
  return maxSoFar;
}

// 4. Kadane's Algorithm with Circular Array Handling
//    - Project Application: Maximum profit in a circular market.
//    - Description:  Handles circular arrays, where the end of the array is considered adjacent to the beginning.
//    - Explanation:
//      The maximum subarray sum in a circular array can be either:
//      1. The maximum subarray sum in the non-circular case.
//      2. The total sum of the array minus the minimum subarray sum.
function kadaneCircular(arr) {
    let maxSoFar = kadaneBasic(arr); // Max sum in non-circular case
    let totalSum = 0;
    let minSoFar = 0;
    let currentMin = 0;

    for (let i = 0; i < arr.length; i++) {
        totalSum += arr[i];
        currentMin = Math.min(arr[i], currentMin + arr[i]);
        minSoFar = Math.min(minSoFar, currentMin);
    }

    if (maxSoFar > 0) { // Important check: If all numbers are negative, return the non-circular max
        return Math.max(maxSoFar, totalSum - minSoFar);
    } else {
        return maxSoFar;
    }
}


// 5. Kadane's Algorithm with 2D Array (for rows)
//    - Project Application: Image Processing - finding the brightest horizontal strip in an image.
//    - Description:  Finds the maximum subarray sum for each row in a 2D array.
function kadane2DRows(matrix) {
  const rowMaxes = [];
  for (let i = 0; i < matrix.length; i++) {
    rowMaxes.push(kadaneBasic(matrix[i])); // Apply 1D Kadane's to each row
  }
  return rowMaxes;
}



// Example Usage and Output
const stockPrices = [100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94];
console.log("1. Stock Price Analysis (Basic Kadane's):", kadaneBasic(stockPrices));
// Expected output: 23 (buy at 85, sell at 106)

const stockPricesWithIndex = [100, 113, 110, 85, 105, 102, 86, 63, 81, 101, 94, 106, 101, 79, 94];
const resultWithIndex = kadaneWithIndex(stockPricesWithIndex);
console.log("2. Profitable Period (Kadane's with Index):", resultWithIndex);
// Expected output: { maxSum: 23, startIndex: 3, endIndex: 11 }

const negativeNumbers = [-2, -3, -4, -1, -5, -3];
console.log("3. Financial Loss Analysis (Negative Numbers):", kadaneNegative(negativeNumbers));
// Expected output: -1

const circularArray = [10, -5, 4, -6, 10, -5];
console.log("4. Circular Market Profit (Circular Array):", kadaneCircular(circularArray));
// Expected output: 20

const imageMatrix = [
  [1, 2, -1, -4, -20],
  [-3, 4, -2, 6, -8],
  [10, -1, 8, -2, 3],
  [-1, -2, -3, -4, -5],
];
console.log("5. Image Brightness Analysis (2D Array - Rows):", kadane2DRows(imageMatrix));
// Expected output: [ 3, 8, 18, -1 ]
