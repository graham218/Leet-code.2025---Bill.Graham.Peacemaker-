/*
Prefix Sum:

A prefix sum array (also known as cumulative sum array) is an array where each element at index i is the sum of all elements in the original array up to and including index i.  It's a useful technique for efficiently calculating sums of subarrays.

Here's a breakdown with five different approaches in JavaScript:
*/

// Approach 1: Iterative Prefix Sum (Basic)
// This is the most straightforward way to calculate the prefix sum.
function prefixSum_iterative(arr) {
  if (!arr || arr.length === 0) {
    return []; // Handle empty array case
  }

  const prefixSum = [];
  prefixSum[0] = arr[0]; // The first element is the same
  for (let i = 1; i < arr.length; i++) {
    prefixSum[i] = prefixSum[i - 1] + arr[i]; // Sum of previous prefix and current element
  }
  return prefixSum;
}

// Example Usage 1:
const arr1 = [1, 2, 3, 4, 5];
const result1 = prefixSum_iterative(arr1);
console.log("Approach 1 - Iterative:", result1); // Output: [1, 3, 6, 10, 15]

const arr1_empty = [];
const result1_empty = prefixSum_iterative(arr1_empty);
console.log("Approach 1 - Iterative (Empty Array):", result1_empty); // Output: []

const arr1_negative = [-1, -2, -3, -4, -5];
const result1_negative = prefixSum_iterative(arr1_negative);
console.log("Approach 1 - Iterative (Negative Numbers):", result1_negative); // Output: [-1, -3, -6, -10, -15]



// Approach 2: Iterative Prefix Sum (In-place - Modifies Original Array)
// This approach modifies the original array to store the prefix sums, saving space.
function prefixSum_inPlace(arr) {
  if (!arr || arr.length === 0) {
    return []; // Handle empty array
  }
  for (let i = 1; i < arr.length; i++) {
    arr[i] += arr[i - 1]; // Update each element with the sum of itself and the previous
  }
  return arr; // Return the modified array
}

// Example Usage 2:
const arr2 = [1, 2, 3, 4, 5];
const result2 = prefixSum_inPlace(arr2);
console.log("Approach 2 - In-place:", result2); // Output: [1, 3, 6, 10, 15]  (arr2 is now modified)

const arr2_empty = [];
const result2_empty = prefixSum_inPlace(arr2_empty);
console.log("Approach 2 - In-place (Empty Array):", result2_empty); // Output: []

const arr2_negative = [-1, -2, -3, -4, -5];
const result2_negative = prefixSum_inPlace(arr2_negative);
console.log("Approach 2 - In-place (Negative Numbers):", result2_negative); // Output: [-1, -3, -6, -10, -15]

// Approach 3: Using reduce()
//  The reduce method can be used to calculate the prefix sum, although it's less efficient than a simple loop.
function prefixSum_reduce(arr) {
    if (!arr || arr.length === 0) {
        return [];
    }
    let sum = 0;
    return arr.reduce((acc, val) => {
        sum += val;
        acc.push(sum);
        return acc;
    }, []);
}

// Example Usage 3:
const arr3 = [1, 2, 3, 4, 5];
const result3 = prefixSum_reduce(arr3);
console.log("Approach 3 - Reduce:", result3); // Output: [1, 3, 6, 10, 15]

const arr3_empty = [];
const result3_empty = prefixSum_reduce(arr3_empty);
console.log("Approach 3 - Reduce (Empty Array):", result3_empty); // Output: []

const arr3_negative = [-1, -2, -3, -4, -5];
const result3_negative = prefixSum_reduce(arr3_negative);
console.log("Approach 3 - Reduce (Negative Numbers):", result3_negative); // Output: [-1, -3, -6, -10, -15]


// Approach 4:  Functional approach with map() and scan() (simulated)
//  JavaScript doesn't have a built-in 'scan' function like some other languages, but we can simulate it.
//  This approach is more complex but demonstrates a functional style.
function prefixSum_functional(arr) {
  if (!arr || arr.length === 0) {
    return [];
  }

  let sum = 0;
  return arr.map(value => {
    sum += value;
    return sum;
  });
}

// Example Usage 4:
const arr4 = [1, 2, 3, 4, 5];
const result4 = prefixSum_functional(arr4);
console.log("Approach 4 - Functional:", result4); // Output: [1, 3, 6, 10, 15]

const arr4_empty = [];
const result4_empty = prefixSum_functional(arr4_empty);
console.log("Approach 4 - Functional (Empty Array):", result4_empty); // Output: []

const arr4_negative = [-1, -2, -3, -4, -5];
const result4_negative = prefixSum_functional(arr4_negative);
console.log("Approach 4 - Functional (Negative Numbers):", result4_negative);  // Output: [-1, -3, -6, -10, -15]


// Approach 5: Dynamic Programming
function prefixSum_dp(arr) {
  if (!arr || arr.length === 0) return [];

  const dp = new Array(arr.length);
  dp[0] = arr[0];

  for (let i = 1; i < arr.length; i++) {
    dp[i] = dp[i - 1] + arr[i];
  }
  return dp;
}

// Example Usage 5:
const arr5 = [1, 2, 3, 4, 5];
const result5 = prefixSum_dp(arr5);
console.log("Approach 5 - Dynamic Programming:", result5); // Output: [1, 3, 6, 10, 15]

const arr5_empty = [];
const result5_empty = prefixSum_dp(arr5_empty);
console.log("Approach 5 - Dynamic Programming (Empty Array):", result5_empty); // Output: []

const arr5_negative = [-1, -2, -3, -4, -5];
const result5_negative = prefixSum_dp(arr5_negative);
console.log("Approach 5 - Dynamic Programming (Negative Numbers):", result5_negative); // Output: [-1, -3, -6, -10, -15]
