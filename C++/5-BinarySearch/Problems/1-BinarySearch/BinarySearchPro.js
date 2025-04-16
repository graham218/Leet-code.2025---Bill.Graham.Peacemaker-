// Binary Search Implementation in JavaScript with 5 Different Approaches

/**
 * Binary Search is an efficient algorithm for finding a target value within a sorted array.
 * It works by repeatedly dividing the search interval in half.
 */

// 1. Basic Binary Search (Iterative)
//    - Scenario: Searching for a specific product ID in a sorted list of product IDs in an e-commerce application.
//    - Returns: The index of the target value if found, otherwise -1.
function binarySearchIterative(sortedArray, target) {
  let low = 0;
  let high = sortedArray.length - 1;

  while (low <= high) {
    const mid = Math.floor((low + high) / 2); // Calculate midpoint
    const guess = sortedArray[mid];

    if (guess === target) {
      return mid; // Target found at index mid
    } else if (guess > target) {
      high = mid - 1; // Target is in the left half
    } else {
      low = mid + 1; // Target is in the right half
    }
  }

  return -1; // Target not found
}

// 2. Binary Search (Recursive)
//    - Scenario: Implementing a search functionality in a database index.
//    - Returns: The index of the target value if found, otherwise -1.
function binarySearchRecursive(sortedArray, target, low, high) {
  if (low > high) {
    return -1; // Base case: Target not found
  }

  const mid = Math.floor((low + high) / 2);
  const guess = sortedArray[mid];

  if (guess === target) {
    return mid; // Target found
  } else if (guess > target) {
    return binarySearchRecursive(sortedArray, target, low, mid - 1); // Search left half
  } else {
    return binarySearchRecursive(sortedArray, target, mid + 1, high); // Search right half
  }
}

// 3. Binary Search with Sorted Array (using a sorted array directly)
//      - Scenario:  Lookup of a specific value within a configuration file where keys are sorted.
//      - Returns:  The index of the target, or -1 if not found.
function binarySearchDirect(sortedArray, target) {
    let low = 0;
    let high = sortedArray.length - 1;

    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        const midValue = sortedArray[mid];

        if (midValue === target) {
            return mid;
        } else if (target < midValue) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

// 4. Binary Search to find the first occurrence of a target
//    - Scenario: Finding the first occurrence of a specific date in a sorted log file.
//    - Returns: The index of the first occurrence of the target, or -1 if not found.
function findFirstOccurrence(sortedArray, target) {
  let low = 0;
  let high = sortedArray.length - 1;
  let result = -1; // Initialize result to -1

  while (low <= high) {
    const mid = Math.floor((low + high) / 2);
    const guess = sortedArray[mid];

    if (guess === target) {
      result = mid;     // Found a match, but look for earlier ones
      high = mid - 1;   // Continue searching in the left half
    } else if (guess > target) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return result;
}

// 5. Binary Search to find the last occurrence of a target
//     - Scenario: Finding the last entry for a user ID in a sorted access log.
//     - Returns: The index of the last occurrence of the target, or -1 if not found.
function findLastOccurrence(sortedArray, target) {
    let low = 0;
    let high = sortedArray.length - 1;
    let result = -1;

    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        const guess = sortedArray[mid];

        if (guess === target) {
            result = mid;       // Found a match, look for later occurrences
            low = mid + 1;     // Search in the right half
        } else if (guess > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return result;
}

// --- Test Cases ---
const sortedArray = [2, 5, 7, 8, 11, 12, 13, 15, 17, 19, 23, 24, 29, 31];
const target = 13;

console.log("--- Binary Search Test Cases ---");
console.log("Sorted Array:", sortedArray);
console.log("Target Value:", target);
console.log("\n--- Results ---");

// 1. Basic Binary Search (Iterative)
const iterativeResult = binarySearchIterative(sortedArray, target);
console.log("1. Iterative Binary Search:", iterativeResult); // Expected: 6

// 2. Binary Search (Recursive)
const recursiveResult = binarySearchRecursive(sortedArray, target, 0, sortedArray.length - 1);
console.log("2. Recursive Binary Search:", recursiveResult); // Expected: 6

// 3. Binary Search with Sorted Array
const directResult = binarySearchDirect(sortedArray, target);
console.log("3. Direct Binary Search:", directResult); // Expected 6

// 4. Find First Occurrence
const firstOccurrenceArray = [2, 4, 6, 8, 8, 8, 10, 12, 14];
const firstOccurrenceTarget = 8;
const firstOccurrenceResult = findFirstOccurrence(firstOccurrenceArray, firstOccurrenceTarget);
console.log("\n4. Find First Occurrence:", firstOccurrenceResult); // Expected: 3
console.log("   Array:", firstOccurrenceArray, "Target:", firstOccurrenceTarget);

// 5. Find Last Occurrence
const lastOccurrenceArray = [2, 4, 6, 8, 8, 8, 10, 12, 14];
const lastOccurrenceTarget = 8;
const lastOccurrenceResult = findLastOccurrence(lastOccurrenceArray, lastOccurrenceTarget);
console.log("5. Find Last Occurrence:", lastOccurrenceResult); // Expected: 5
console.log("   Array:", lastOccurrenceArray, "Target:", lastOccurrenceTarget);

// Test case where the target is not in the array
const notFoundTarget = 20;
console.log("\n--- Target Not Found Test ---");
console.log("Target Value:", notFoundTarget);
console.log("1. Iterative Binary Search (Not Found):", binarySearchIterative(sortedArray, notFoundTarget)); // Expected: -1
console.log("2. Recursive Binary Search (Not Found):", binarySearchRecursive(sortedArray, notFoundTarget, 0, sortedArray.length - 1)); // Expected: -1
console.log("3. Direct Binary Search (Not Found):", binarySearchDirect(sortedArray, notFoundTarget)); // Expected: -1
console.log("4. First Occurrence (Not Found):", findFirstOccurrence(sortedArray, notFoundTarget));
console.log("5. Last Occurrence (Not Found):", findLastOccurrence(sortedArray, notFoundTarget));
