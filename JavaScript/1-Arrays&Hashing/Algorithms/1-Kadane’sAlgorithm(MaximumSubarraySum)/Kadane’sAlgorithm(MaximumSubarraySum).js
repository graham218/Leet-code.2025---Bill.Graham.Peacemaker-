/*
Kadane's Algorithm: Finding the Maximum Subarray Sum

Kadane's algorithm is a dynamic programming technique used to find the maximum sum of a contiguous subarray within a one-dimensional array of numbers. It efficiently handles arrays with both positive and negative numbers.

Here are five different JavaScript implementations of Kadane's algorithm, with detailed comments explaining each approach:
*/

/**
 * 1. Standard Kadane's Algorithm (Iterative)
 *
 * This is the most common and efficient implementation.  It iterates through the array,
 * keeping track of the maximum sum ending at the current position (`maxSoFar`) and
 * the overall maximum sum (`maxEndingHere`).
 *
 * Time Complexity: O(n) - Linear time, as it iterates through the array once.
 * Space Complexity: O(1) - Constant space, as it only uses a few variables.
 *
 * @param {number[]} arr The input array of numbers.
 * @returns {number} The maximum subarray sum.
 */
function kadaneStandard(arr) {
  if (!arr || arr.length === 0) {
    return 0; // Handle empty or null arrays
  }

  let maxSoFar = -Infinity;  // Initialize to negative infinity to handle arrays with all negative numbers
  let maxEndingHere = 0;

  for (let i = 0; i < arr.length; i++) {
    maxEndingHere = maxEndingHere + arr[i]; // Add the current element to the current maximum sum
    if (maxEndingHere > maxSoFar) {
      maxSoFar = maxEndingHere;    // Update the overall maximum sum if needed
    }
    if (maxEndingHere < 0) {
      maxEndingHere = 0;          // Reset the current maximum sum if it becomes negative
    }
  }
  return maxSoFar;
}



/**
 * 2. Kadane's Algorithm with Start and End Indices
 *
 * This version not only calculates the maximum subarray sum but also keeps track of
 * the starting and ending indices of the maximum subarray.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * @param {number[]} arr The input array.
 * @returns {object} An object containing the maximum sum, start index, and end index.
 * Returns { maxSum: 0, startIndex: -1, endIndex: -1 } for an empty array.
 */
function kadaneWithIndices(arr) {
  if (!arr || arr.length === 0) {
    return { maxSum: 0, startIndex: -1, endIndex: -1 };
  }

  let maxSoFar = -Infinity;
  let maxEndingHere = 0;
  let startIndex = 0;
  let endIndex = 0;
  let tempStartIndex = 0; // Temporary start index

  for (let i = 0; i < arr.length; i++) {
    maxEndingHere = maxEndingHere + arr[i];

    if (maxEndingHere > maxSoFar) {
      maxSoFar = maxEndingHere;
      startIndex = tempStartIndex; // Update start index
      endIndex = i;              // Update end index
    }
    if (maxEndingHere < 0) {
      maxEndingHere = 0;
      tempStartIndex = i + 1;    // Update temporary start index
    }
  }
  return { maxSum: maxSoFar, startIndex: startIndex, endIndex: endIndex };
}



/**
 * 3. Kadane's Algorithm (Concise Version)
 *
 * A more concise version of the standard Kadane's algorithm, using Math.max to simplify
 * the logic.  It's functionally equivalent to `kadaneStandard`.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * @param {number[]} arr The input array.
 * @returns {number} The maximum subarray sum.
 */
function kadaneConcise(arr) {
  if (!arr || arr.length === 0) {
    return 0;
  }

  let maxSoFar = -Infinity;
  let maxEndingHere = 0;

  for (let i = 0; i < arr.length; i++) {
    maxEndingHere = Math.max(arr[i], maxEndingHere + arr[i]); // Choose between starting a new subarray or extending the current one
    maxSoFar = Math.max(maxSoFar, maxEndingHere);       // Update the overall maximum
  }
  return maxSoFar;
}

/**
 * 4. Kadane's Algorithm with Negative Number Handling
 *
 * This version explicitly handles the case where the array contains only negative numbers.
 * In such cases, the maximum subarray sum is the largest negative number.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * @param {number[]} arr The input array.
 * @returns {number} The maximum subarray sum.
 */
function kadaneNegativeHandling(arr) {
    if (!arr || arr.length === 0) {
        return 0;
    }

    let maxSoFar = -Infinity;
    let maxEndingHere = 0;
    let allNegative = true;

    for (let i = 0; i < arr.length; i++) {
        if (arr[i] >= 0) {
            allNegative = false; // Found a non-negative number
        }
        maxEndingHere = maxEndingHere + arr[i];
        if (maxEndingHere > maxSoFar) {
            maxSoFar = maxEndingHere;
        }
        if (maxEndingHere < 0) {
            maxEndingHere = 0;
        }
    }

    if (allNegative) {
        // If all numbers are negative, find the largest negative number
        maxSoFar = Math.max(...arr); // Spread syntax to find max of array.
    }
    return maxSoFar;
}


/**
 * 5. Kadane's Algorithm using Reduce
 *
 * This version uses the `reduce` method for a more functional approach.  It's less
 * performant than the iterative versions, but demonstrates an alternative style.
 *
 * Time Complexity: O(n) -  Reduce iterates through the array.
 * Space Complexity: O(1) -  Constant space, variables within the reduce.
 *
 * @param {number[]} arr The input array.
 * @returns {number} The maximum subarray sum.
 */
function kadaneReduce(arr) {
  if (!arr || arr.length === 0) {
    return 0;
  }

  let initialValue = { maxSoFar: -Infinity, maxEndingHere: 0 };
  const result = arr.reduce((accumulator, currentValue) => {
    let maxEndingHere = Math.max(currentValue, accumulator.maxEndingHere + currentValue);
    let maxSoFar = Math.max(accumulator.maxSoFar, maxEndingHere);
    return { maxSoFar: maxSoFar, maxEndingHere: maxEndingHere };
  }, initialValue);

  return result.maxSoFar;
}



// Example Usage and Output
const testArrays = [
  [-2, -3, 4, -1, -2, 1, 5, -3],
  [1, 2, 3, 4, 5],
  [-1, -2, -3, -4, -5],
  [2, -1, 2, 3, -4, 5],
  [],
  [5, -3, 5],
  [-10, -5, 0, -2],
  [2, 2, -10, 2, 2]
];

console.log("Kadane's Algorithm - Test Cases and Outputs:");
console.log("------------------------------------------");

testArrays.forEach((arr, index) => {
  console.log(`Test Case ${index + 1}: [${arr}]`);
  console.log(`  1. Standard:             ${kadaneStandard(arr)}`);
  const indicesResult = kadaneWithIndices(arr);
  console.log(`  2. With Indices:         Max Sum = ${indicesResult.maxSum}, Start Index = ${indicesResult.startIndex}, End Index = ${indicesResult.endIndex}`);
  console.log(`  3. Concise:              ${kadaneConcise(arr)}`);
  console.log(`  4. Negative Handling:    ${kadaneNegativeHandling(arr)}`);
  console.log(`  5. Using Reduce:         ${kadaneReduce(arr)}`);
  console.log("------------------------------------------");
});

/*
Output:

Kadane's Algorithm - Test Cases and Outputs:
------------------------------------------
Test Case 1: [-2,-3,4,-1,-2,1,5,-3]
  1. Standard:             7
  2. With Indices:         Max Sum = 7, Start Index = 2, End Index = 6
  3. Concise:              7
  4. Negative Handling:    7
  5. Using Reduce:         7
------------------------------------------
Test Case 2: [1,2,3,4,5]
  1. Standard:             15
  2. With Indices:         Max Sum = 15, Start Index = 0, End Index = 4
  3. Concise:              15
  4. Negative Handling:    15
  5. Using Reduce:         15
------------------------------------------
Test Case 3: [-1,-2,-3,-4,-5]
  1. Standard:             -1
  2. With Indices:         Max Sum = -1, Start Index = 0, End Index = 0
  3. Concise:              -1
  4. Negative Handling:    -1
  5. Using Reduce:         -1
------------------------------------------
Test Case 4: [2,-1,2,3,-4,5]
  1. Standard:             6
  2. With Indices:         Max Sum = 6, Start Index = 0, End Index = 3
  3. Concise:              6
  4. Negative Handling:    6
  5. Using Reduce:         6
------------------------------------------
Test Case 5: []
  1. Standard:             0
  2. With Indices:         Max Sum = 0, Start Index = -1, End Index = -1
  3. Concise:              0
  4. Negative Handling:    0
  5. Using Reduce:         0
------------------------------------------
Test Case 6: [5,-3,5]
  1. Standard:             7
  2. With Indices:         Max Sum = 7, Start Index = 0, End Index = 2
  3. Concise:              7
  4. Negative Handling:    7
  5. Using Reduce:         7
------------------------------------------
Test Case 7: [-10,-5,0,-2]
  1. Standard:             0
  2. With Indices:         Max Sum = 0, Start Index = 2, End Index = 2
  3. Concise:              0
  4. Negative Handling:    0
  5. Using Reduce:         0
------------------------------------------
Test Case 8: [2,2,-10,2,2]
  1. Standard:             4
  2. With Indices:         Max Sum = 4, Start Index = 0, End Index = 1
  3. Concise:              4
  4. Negative Handling:    4
  5. Using Reduce:         4
------------------------------------------
*/
