// Binary Search & Exponential Search Algorithms in JavaScript

/**
 * Binary Search: A classic divide-and-conquer algorithm for searching in sorted arrays.
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(1) - Iterative, O(log n) - Recursive (due to call stack)
 */
const binarySearch = (arr, target) => {
  let low = 0;
  let high = arr.length - 1;

  while (low <= high) {
    const mid = Math.floor((low + high) / 2); // Prevent potential overflow

    if (arr[mid] === target) {
      return mid; // Target found, return its index
    } else if (arr[mid] < target) {
      low = mid + 1; // Search in the right half
    } else {
      high = mid - 1; // Search in the left half
    }
  }

  return -1; // Target not found
};

/**
 * Exponential Search:  Useful for unbounded/infinite arrays.  It first finds a range
 * where the target *might* be, then performs Binary Search within that range.
 *
 * Time Complexity: O(log n) -  (O(log i) where i is the index of the first occurrence of x)
 * Space Complexity: O(1) - Iterative, O(log n) - Recursive (due to call stack in binarySearch)
 */
const exponentialSearch = (arr, target) => {
  const n = arr.length;

  // 1. Handle the edge case where the target is at the beginning of the array.
  if (n > 0 && arr[0] === target) {
    return 0;
  }

  // 2. Find a range (exponentially increasing) where the target *could* be.
  let i = 1;
  while (i < n && arr[i] <= target) {
    i = i * 2;
  }

  // 3. Perform Binary Search within the found range.  Crucially, we use Math.min
  //    to ensure we don't go out of bounds of the array.
  const left = i / 2; // Corrected: Start of the range
  const right = Math.min(i, n - 1); // Corrected: End of the range
  return binarySearch(arr.slice(left, right + 1), target); // Use slice
};

// --- Variations and Demonstrations ---

// Variation 1: Recursive Binary Search
const recursiveBinarySearch = (arr, target, low, high) => {
    if (low > high) {
        return -1;
    }

    const mid = Math.floor((low + high) / 2);

    if (arr[mid] === target) {
        return mid;
    } else if (arr[mid] < target) {
        return recursiveBinarySearch(arr, target, mid + 1, high);
    } else {
        return recursiveBinarySearch(arr, target, low, mid - 1);
    }
};

// Variation 2: Exponential Search with a slightly different Binary Search call
const exponentialSearchVariant = (arr, target) => {
    const n = arr.length;
      if (n > 0 && arr[0] === target)
        return 0;
    let i = 1;
    while (i < n && arr[i] <= target)
        i = i*2;
    // Pass the whole array, but limit the range using low and high
    return recursiveBinarySearch(arr, target, i/2, Math.min(i, n-1));
};

// Variation 3: Using a helper function for Binary Search in Exponential Search
const binarySearchHelper = (arr, target, low, high) => {
  while (low <= high) {
    const mid = Math.floor((low + high) / 2);
    if (arr[mid] === target) return mid;
    else if (arr[mid] < target) low = mid + 1;
    else high = mid - 1;
  }
  return -1;
};

const exponentialSearchWithHelper = (arr, target) => {
    const n = arr.length;
    if (n > 0 && arr[0] === target) return 0;
    let i = 1;
    while (i < n && arr[i] <= target) i *= 2;
    return binarySearchHelper(arr, target, i / 2, Math.min(i, n - 1));
};



// --- Example Usage and Output ---
const sortedArray = [3, 4, 5, 6, 11, 13, 15, 19, 22, 25, 28, 30, 32, 35, 38, 40, 43, 47, 50, 55, 60];
const targetValue = 22;

console.log("--- Binary Search ---");
console.log("Array:", sortedArray);
console.log("Target:", targetValue);
const binarySearchResult = binarySearch(sortedArray, targetValue);
console.log("Index of", targetValue, "in sortedArray (Iterative):", binarySearchResult);

const recursiveBinarySearchResult = recursiveBinarySearch(sortedArray, targetValue, 0, sortedArray.length - 1);
console.log("Index of", targetValue, "in sortedArray (Recursive):", recursiveBinarySearchResult);


console.log("\n--- Exponential Search ---");
console.log("Array:", sortedArray);
console.log("Target:", targetValue);
const exponentialSearchResult = exponentialSearch(sortedArray, targetValue);
console.log("Index of", targetValue, "in sortedArray (Exponential):", exponentialSearchResult);

const exponentialSearchVariantResult = exponentialSearchVariant(sortedArray, targetValue);
console.log("Index of", targetValue, "in sortedArray (Exponential Variant):", exponentialSearchVariantResult);

const exponentialSearchWithHelperResult = exponentialSearchWithHelper(sortedArray, targetValue);
console.log("Index of", targetValue, "in sortedArray (Exponential with Helper):", exponentialSearchWithHelperResult);


// Example where target is not in the array
const targetNotFound = 99;
console.log("\n--- Search for Value Not in Array ---");
console.log("Target:", targetNotFound);
const binarySearchNotFound = binarySearch(sortedArray, targetNotFound);
console.log("Binary Search Result (Not Found):", binarySearchNotFound);
const exponentialSearchNotFound = exponentialSearch(sortedArray, targetNotFound);
console.log("Exponential Search Result (Not Found):", exponentialSearchNotFound);
