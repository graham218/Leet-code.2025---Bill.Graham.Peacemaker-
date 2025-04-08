// Binary Search Implementation in JavaScript

// 1. Iterative Binary Search
function iterativeBinarySearch(arr, target) {
  let low = 0;
  let high = arr.length - 1;

  while (low <= high) {
    const mid = Math.floor((low + high) / 2); // More robust against overflow
    const value = arr[mid];

    if (value === target) {
      return mid;
    } else if (value < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

// 2. Recursive Binary Search
function recursiveBinarySearch(arr, target, low, high) {
  if (low > high) {
    return -1;
  }

  const mid = Math.floor((low + high) / 2);
  const value = arr[mid];

  if (value === target) {
    return mid;
  } else if (value < target) {
    return recursiveBinarySearch(arr, target, mid + 1, high);
  } else {
    return recursiveBinarySearch(arr, target, low, mid - 1);
  }
}

// 3. Binary Search with Early Exit (Optimization)
function binarySearchEarlyExit(arr, target) {
    let low = 0;
    let high = arr.length - 1;

    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        const value = arr[mid];

        if (value === target) {
            return mid; // Found, exit early!
        } else if (value < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Not found
}

// 4. Binary Search for First Occurrence
function findFirstOccurrence(arr, target) {
  let low = 0;
  let high = arr.length - 1;
  let result = -1;

  while (low <= high) {
    const mid = Math.floor((low + high) / 2);
    const value = arr[mid];

    if (value === target) {
      result = mid;     // Found, but look for earlier
      high = mid - 1;   // Continue searching left
    } else if (value < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return result;
}

// 5. Binary Search for Last Occurrence
function findLastOccurrence(arr, target) {
    let low = 0;
    let high = arr.length - 1;
    let result = -1;

    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        const value = arr[mid];

        if (value === target) {
            result = mid;       // Found, but look for later
            low = mid + 1;     // Continue searching right
        } else if (value < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

// Example Usage and Output
const sortedArray = [2, 5, 7, 8, 11, 12, 13, 13, 13, 15, 18, 20];
const targetValue = 13;

console.log("Iterative Binary Search:", iterativeBinarySearch(sortedArray, targetValue)); // Output: 6
console.log("Recursive Binary Search:", recursiveBinarySearch(sortedArray, targetValue, 0, sortedArray.length - 1)); // Output: 6
console.log("Binary Search with Early Exit:", binarySearchEarlyExit(sortedArray, targetValue)); // Output: 6
console.log("First Occurrence of 13:", findFirstOccurrence(sortedArray, targetValue)); // Output: 6
console.log("Last Occurrence of 13:", findLastOccurrence(sortedArray, targetValue));   // Output: 8

// Example with a target not in the array
const notFoundTarget = 99;
console.log("Iterative Binary Search (Not Found):", iterativeBinarySearch(sortedArray, notFoundTarget)); // Output: -1
console.log("Recursive Binary Search (Not Found):", recursiveBinarySearch(sortedArray, notFoundTarget, 0, sortedArray.length - 1)); // Output: -1
console.log("Binary Search with Early Exit (Not Found):", binarySearchEarlyExit(sortedArray, notFoundTarget)); // Output: -1
console.log("First Occurrence of 99:", findFirstOccurrence(sortedArray, notFoundTarget)); // Output: -1
console.log("Last Occurrence of 99:", findLastOccurrence(sortedArray, notFoundTarget));     // Output: -1

// Example with empty array
const emptyArray = [];
const targetInEmpty = 5;
console.log("Iterative Binary Search (Empty Array):", iterativeBinarySearch(emptyArray, targetInEmpty));       // Output: -1
console.log("Recursive Binary Search (Empty Array):", recursiveBinarySearch(emptyArray, targetInEmpty, 0, emptyArray.length-1)); // Output: -1
console.log("Binary Search with Early Exit (Empty Array):", binarySearchEarlyExit(emptyArray, targetInEmpty));       // Output: -1
console.log("First Occurrence (Empty Array):", findFirstOccurrence(emptyArray, targetInEmpty));       // Output: -1
console.log("Last Occurrence (Empty Array):", findLastOccurrence(emptyArray, targetInEmpty));           // Output: -1

// Example with single element array
const singleElementArray = [5];
const targetInSingle = 5;
const targetNotInSingle = 10;
console.log("Iterative Binary Search (Single Element):", iterativeBinarySearch(singleElementArray, targetInSingle));       // Output: 0
console.log("Recursive Binary Search (Single Element):", recursiveBinarySearch(singleElementArray, targetInSingle, 0, singleElementArray.length-1)); // Output: 0
console.log("Binary Search with Early Exit (Single Element):", binarySearchEarlyExit(singleElementArray, targetInSingle));       // Output: 0
console.log("First Occurrence (Single Element):", findFirstOccurrence(singleElementArray, targetInSingle));       // Output: 0
console.log("Last Occurrence (Single Element):", findLastOccurrence(singleElementArray, targetInSingle));           // Output: 0

console.log("Iterative Binary Search (Single Element, Not Found):", iterativeBinarySearch(singleElementArray, targetNotInSingle));       // Output: -1
console.log("Recursive Binary Search (Single Element, Not Found):", recursiveBinarySearch(singleElementArray, targetNotInSingle, 0, singleElementArray.length-1)); // Output: -1
console.log("Binary Search with Early Exit (Single Element, Not Found):", binarySearchEarlyExit(singleElementArray, targetNotInSingle));       // Output: -1
console.log("First Occurrence (Single Element, Not Found):", findFirstOccurrence(singleElementArray, targetNotInSingle));       // Output: -1
console.log("Last Occurrence (Single Element, Not Found):", findLastOccurrence(singleElementArray, targetNotInSingle));           // Output: -1
