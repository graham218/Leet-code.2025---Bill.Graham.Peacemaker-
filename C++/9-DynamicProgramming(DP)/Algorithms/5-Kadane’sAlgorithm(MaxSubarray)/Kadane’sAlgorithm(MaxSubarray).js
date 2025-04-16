// Kadane's Algorithm - Finding the Maximum Subarray Sum

// 1. Kadane's Algorithm (Optimized)
function kadaneOptimized(arr) {
  let maxSoFar = -Infinity;
  let maxEndingHere = 0;

  for (let i = 0; i < arr.length; i++) {
    maxEndingHere = Math.max(arr[i], maxEndingHere + arr[i]);
    maxSoFar = Math.max(maxSoFar, maxEndingHere);
  }
  return maxSoFar;
}

// 2. Kadane's Algorithm (with Start and End Indices)
function kadaneWithIndices(arr) {
  let maxSoFar = -Infinity;
  let maxEndingHere = 0;
  let start = 0;
  let end = 0;
  let tempStart = 0;

  for (let i = 0; i < arr.length; i++) {
    if (arr[i] > maxEndingHere + arr[i]) { // Start a new subarray if current element is greater
      maxEndingHere = arr[i];
      tempStart = i; // Update start index
    } else {
      maxEndingHere += arr[i];
    }

    if (maxEndingHere > maxSoFar) { // Update maxSoFar and indices
      maxSoFar = maxEndingHere;
      start = tempStart;
      end = i;
    }
  }
  return { maxSum: maxSoFar, startIndex: start, endIndex: end };
}

// 3. Kadane's Algorithm (Handling All Negative Numbers)
function kadaneHandleNegative(arr) {
  let maxSoFar = -Infinity;
  let maxEndingHere = 0;
  let allNegative = true;

  for (let i = 0; i < arr.length; i++) {
    if (arr[i] >= 0) {
      allNegative = false;
    }
    maxEndingHere = Math.max(arr[i], maxEndingHere + arr[i]);
    maxSoFar = Math.max(maxSoFar, maxEndingHere);
  }

  if (allNegative) {
    // If all numbers are negative, return the largest negative number
    maxSoFar = arr.reduce((max, val) => Math.max(max, val), -Infinity);
  }
  return maxSoFar;
}

// 4. Kadane's Algorithm (Verbose Logging)
function kadaneVerbose(arr) {
    let maxSoFar = -Infinity;
    let maxEndingHere = 0;

    console.log("Kadane's Algorithm - Verbose Logging:");
    console.log("-------------------------------------");

    for (let i = 0; i < arr.length; i++) {
        console.log(`Iteration ${i}:`);
        console.log(`  Current element: ${arr[i]}`);
        console.log(`  maxEndingHere before: ${maxEndingHere}`);

        maxEndingHere = Math.max(arr[i], maxEndingHere + arr[i]);
        console.log(`  maxEndingHere after: ${maxEndingHere}`);

        maxSoFar = Math.max(maxSoFar, maxEndingHere);
        console.log(`  maxSoFar: ${maxSoFar}`);
        console.log("-------------------------------------");
    }
    return maxSoFar;
}

// 5. Kadane's Algorithm (Using Reduce)
function kadaneReduce(arr) {
  if (!arr || arr.length === 0) {
    return 0;
  }

  let maxSoFar = -Infinity;
  let maxEndingHere = 0;

  arr.forEach(num => {
    maxEndingHere = Math.max(num, maxEndingHere + num);
    maxSoFar = Math.max(maxSoFar, maxEndingHere);
  });
  return maxSoFar;
}
// Example Usage:
const array1 = [-2, 3, 2, -1, 4];
const array2 = [-1, -2, -3, -4, -5];
const array3 = [1, 2, 3, 4, 5];
const array4 = [-2, 1, -3, 4, -1, 2, 1, -5, 4];

console.log("Example Arrays:");
console.log("Array 1:", array1);
console.log("Array 2:", array2);
console.log("Array 3:", array3);
console.log("Array 4:", array4);
console.log("\n------------------------\n");

console.log("1. Kadane's Algorithm (Optimized):");
console.log("Max subarray sum (Array 1):", kadaneOptimized(array1)); // Output: 8
console.log("Max subarray sum (Array 2):", kadaneOptimized(array2)); // Output: -1
console.log("Max subarray sum (Array 3):", kadaneOptimized(array3)); // Output: 15
console.log("Max subarray sum (Array 4):", kadaneOptimized(array4)); // Output: 6

console.log("\n------------------------\n");

console.log("2. Kadane's Algorithm (with Start and End Indices):");
console.log("Max subarray (Array 1):", kadaneWithIndices(array1));
console.log("Max subarray (Array 2):", kadaneWithIndices(array2));
console.log("Max subarray (Array 3):", kadaneWithIndices(array3));
console.log("Max subarray (Array 4):", kadaneWithIndices(array4));

console.log("\n------------------------\n");

console.log("3. Kadane's Algorithm (Handling All Negative Numbers):");
console.log("Max subarray sum (Array 1):", kadaneHandleNegative(array1)); // Output: 8
console.log("Max subarray sum (Array 2):", kadaneHandleNegative(array2)); // Output: -1
console.log("Max subarray sum (Array 3):", kadaneHandleNegative(array3)); // Output: 15
console.log("Max subarray sum (Array 4):", kadaneHandleNegative(array4)); // Output: 6

console.log("\n------------------------\n");

console.log("4. Kadane's Algorithm (Verbose Logging):");
kadaneVerbose(array4); // Output: 6 (with detailed logs)

console.log("\n------------------------\n");

console.log("5. Kadane's Algorithm (Using Reduce):");
console.log("Max subarray sum (Array 1):", kadaneReduce(array1));
console.log("Max subarray sum (Array 2):", kadaneReduce(array2));
console.log("Max subarray sum (Array 3):", kadaneReduce(array3));
console.log("Max subarray sum (Array 4):", kadaneReduce(array4));
