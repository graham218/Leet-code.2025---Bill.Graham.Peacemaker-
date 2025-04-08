// Iterative Binary Search - Standard Approach
function binarySearchIterative(arr, target) {
  let low = 0;
  let high = arr.length - 1;

  while (low <= high) {
    const mid = Math.floor((low + high) / 2);

    if (arr[mid] === target) {
      return mid;
    } else if (arr[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

// Recursive Binary Search - Standard Approach
function binarySearchRecursive(arr, target, low, high) {
  if (low > high) {
    return -1;
  }

  const mid = Math.floor((low + high) / 2);

  if (arr[mid] === target) {
    return mid;
  } else if (arr[mid] < target) {
    return binarySearchRecursive(arr, target, mid + 1, high);
  } else {
    return binarySearchRecursive(arr, target, low, mid - 1);
  }
}

// Iterative Binary Search - Using bitwise right shift for mid calculation
function binarySearchIterativeBitwise(arr, target) {
    let low = 0;
    let high = arr.length - 1;

    while (low <= high) {
        // Use bitwise right shift (>>) for calculating mid.  Slightly more performant in *some* JS engines.
        const mid = (low + high) >>> 1;

        if (arr[mid] === target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Recursive Binary Search - Optimized mid calculation to prevent overflow
function binarySearchRecursiveOptimized(arr, target, low, high) {
  if (low > high) {
    return -1;
  }
  // Calculate mid to prevent potential overflow issues for very large arrays.
  const mid = low + Math.floor((high - low) / 2);

  if (arr[mid] === target) {
    return mid;
  } else if (arr[mid] < target) {
    return binarySearchRecursiveOptimized(arr, target, mid + 1, high);
  } else {
    return binarySearchRecursiveOptimized(arr, target, low, mid - 1);
  }
}

// Recursive Binary Search - ES6 Syntax with default parameters
const binarySearchRecursiveES6 = (arr, target, low = 0, high = arr.length - 1) => {
    if (low > high) return -1;
    const mid = low + Math.floor((high - low) / 2);
    if (arr[mid] === target) return mid;
    return arr[mid] < target
      ? binarySearchRecursiveES6(arr, target, mid + 1, high)
      : binarySearchRecursiveES6(arr, target, low, mid - 1);
};


// Example Usage and Output
const sortedArray = [2, 5, 8, 12, 16, 23, 38, 56, 72, 91];
const targetValue = 23;

console.log("Array:", sortedArray);
console.log("Target:", targetValue);
console.log("\n--- Binary Search Results ---");

// 1. Iterative Binary Search
const iterativeResult = binarySearchIterative(sortedArray, targetValue);
console.log("Iterative:", iterativeResult); // Output: 5

// 2. Recursive Binary Search
const recursiveResult = binarySearchRecursive(sortedArray, targetValue, 0, sortedArray.length - 1);
console.log("Recursive:", recursiveResult); // Output: 5

// 3. Iterative Binary Search (Bitwise)
const iterativeBitwiseResult = binarySearchIterativeBitwise(sortedArray, targetValue);
console.log("Iterative (Bitwise):", iterativeBitwiseResult);

// 4. Recursive Binary Search (Overflow Optimized)
const recursiveOptimizedResult = binarySearchRecursiveOptimized(sortedArray, targetValue, 0, sortedArray.length - 1);
console.log("Recursive (Optimized):", recursiveOptimizedResult);

// 5. Recursive Binary Search (ES6)
const recursiveES6Result = binarySearchRecursiveES6(sortedArray, targetValue);
console.log("Recursive (ES6):", recursiveES6Result);
