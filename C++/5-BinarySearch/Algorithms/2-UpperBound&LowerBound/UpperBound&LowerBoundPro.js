// Binary Search: Upper Bound & Lower Bound

/*
    Problem:
    Given a sorted array of integers, find the lower and upper bounds of a target value.
    -   Lower bound: The index of the first occurrence of the target value.
    -   Upper bound: The index of the last occurrence of the target value.

    If the target value is not found, return -1 for both.

    Constraints:
    -   The input array is sorted in ascending order.
    -   The array may contain duplicate elements.
    -   Time complexity should be O(log n).
*/

// Helper function to create test arrays
function createTestArray(size, maxValue, allowDuplicates = true) {
    const arr = [];
    let prev = 0;
    for (let i = 0; i < size; i++) {
        if (allowDuplicates) {
            const increment = Math.floor(Math.random() * (maxValue / size)) + 1;
            prev += increment;
        } else {
            prev += Math.floor(maxValue / size) + 1;
        }
        arr.push(prev);
    }
    return arr;
}

// 1. Iterative Binary Search with Separate Functions

function lowerBoundIterative(arr, target) {
    let low = 0;
    let high = arr.length - 1;
    let result = -1;

    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        if (arr[mid] === target) {
            result = mid;       // Found a match, look for earlier one
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

function upperBoundIterative(arr, target) {
    let low = 0;
    let high = arr.length - 1;
    let result = -1;

    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        if (arr[mid] === target) {
            result = mid;       // Found a match, look for later one
            low = mid + 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

function binarySearchBoundsIterative(arr, target) {
    const lower = lowerBoundIterative(arr, target);
    const upper = upperBoundIterative(arr, target);
    return [lower, upper];
}



// 2. Iterative Binary Search - Combined Function
function binarySearchBoundsIterativeCombined(arr, target) {
    let lower = -1;
    let upper = -1;
    let low, high, mid;

    // Find Lower Bound
    low = 0;
    high = arr.length - 1;
    while (low <= high) {
        mid = Math.floor((low + high) / 2);
        if (arr[mid] === target) {
            lower = mid;
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // Find Upper Bound
    low = 0;
    high = arr.length - 1;
    while (low <= high) {
        mid = Math.floor((low + high) / 2);
        if (arr[mid] === target) {
            upper = mid;
            low = mid + 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return [lower, upper];
}



// 3. Recursive Binary Search

function binarySearchBoundsRecursive(arr, target, low = 0, high = arr.length - 1, lower = -1, upper = -1, findLower = true) {
    if (low > high) {
        return [lower, upper];
    }

    const mid = Math.floor((low + high) / 2);
    if (arr[mid] === target) {
        if (findLower) {
            lower = mid;
            return binarySearchBoundsRecursive(arr, target, low, mid - 1, lower, upper, true); // Search left for lower
        } else {
            upper = mid;
            return binarySearchBoundsRecursive(arr, target, mid + 1, high, lower, upper, false); // Search right for upper
        }
    } else if (arr[mid] < target) {
        return binarySearchBoundsRecursive(arr, target, mid + 1, high, lower, upper, findLower);
    } else {
        return binarySearchBoundsRecursive(arr, target, low, mid - 1, lower, upper, findLower);
    }
}

function getLowerAndUpperBounds(arr, target) {
    const lower = binarySearchBoundsRecursive(arr, target, 0, arr.length - 1, -1, -1, true)[0];
    const upper = binarySearchBoundsRecursive(arr, target, 0, arr.length - 1, -1, -1, false)[1];
    return [lower, upper];
}



// 4. Using built-in methods (for demonstration - not truly O(log n))
function binarySearchBoundsBuiltIn(arr, target) {
    let lower = arr.indexOf(target);  //  O(n) in worst case
    let upper = arr.lastIndexOf(target); // O(n) in worst case
    return [lower, upper];
}

// 5. Optimized Iterative Approach (Most Efficient)
function binarySearchBoundsOptimized(arr, target) {
    let lower = -1;
    let upper = -1;
    let low = 0;
    let high = arr.length - 1;

    // Find Lower Bound
    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        if (arr[mid] >= target) { // Changed to >=
            if (arr[mid] === target) lower = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    // Reset for Upper Bound
    low = 0;
    high = arr.length - 1;
    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        if (arr[mid] <= target) { // Changed to <=
            if (arr[mid] === target) upper = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return [lower, upper];
}



// --- Test Cases ---
const testArray1 = [2, 5, 5, 5, 6, 6, 8, 9, 9, 9];
const target1 = 5;
const target2 = 6;
const target3 = 7;
const target4 = 9;
const target5 = 2;

const testArray2 = createTestArray(20, 100, true); // Allow Duplicates
const target6 = testArray2[Math.floor(testArray2.length / 3)]; // Pick a target within the array
const target7 = 101; // Target not in array

const testArray3 = [7];
const target8 = 7;

const testArray4 = createTestArray(20, 100, false); // No Duplicates
const target9 = testArray4[Math.floor(testArray4.length/2)];

console.log("--- Test Cases ---");
console.log("Test Array 1:", testArray1);
console.log("Target 1 (5):", target1);
console.log("Target 2 (6):", target2);
console.log("Target 3 (7):", target3);
console.log("Target 4 (9):", target4);
console.log("Target 5 (2):", target5);
console.log("Test Array 2 (Duplicates):", testArray2);
console.log("Target 6 (Existing):", target6);
console.log("Target 7 (Not found):", target7);
console.log("Test Array 3 (Single Element):", testArray3);
console.log("Target 8 (Single Element):", target8);
console.log("Test Array 4 (No Duplicates):", testArray4);
console.log("Target 9 (No Duplicates):", target9);


console.log("\n--- Results ---");
console.log("\n1. Iterative with Separate Functions:");
console.log("Test Case 1:", binarySearchBoundsIterative(testArray1, target1)); // [1, 3]
console.log("Test Case 2:", binarySearchBoundsIterative(testArray1, target2)); // [4, 5]
console.log("Test Case 3:", binarySearchBoundsIterative(testArray1, target3)); // [-1, -1]
console.log("Test Case 4:", binarySearchBoundsIterative(testArray1, target4)); // [7, 9]
console.log("Test Case 5:", binarySearchBoundsIterative(testArray1, target5)); // [0, 0]
console.log("Test Case 6 (Random Array):", binarySearchBoundsIterative(testArray2, target6));
console.log("Test Case 7 (Not Found):", binarySearchBoundsIterative(testArray2, target7));
console.log("Test Case 8 (Single Element):", binarySearchBoundsIterative(testArray3, target8));
console.log("Test Case 9 (No Duplicates):", binarySearchBoundsIterative(testArray4, target9));


console.log("\n2. Iterative Combined Function:");
console.log("Test Case 1:", binarySearchBoundsIterativeCombined(testArray1, target1));
console.log("Test Case 2:", binarySearchBoundsIterativeCombined(testArray1, target2));
console.log("Test Case 3:", binarySearchBoundsIterativeCombined(testArray1, target3));
console.log("Test Case 4:", binarySearchBoundsIterativeCombined(testArray1, target4));
console.log("Test Case 5:", binarySearchBoundsIterativeCombined(testArray1, target5));
console.log("Test Case 6:", binarySearchBoundsIterativeCombined(testArray2, target6));
console.log("Test Case 7:", binarySearchBoundsIterativeCombined(testArray2, target7));
console.log("Test Case 8:", binarySearchBoundsIterativeCombined(testArray3, target8));
console.log("Test Case 9:", binarySearchBoundsIterativeCombined(testArray4, target9));


console.log("\n3. Recursive:");
console.log("Test Case 1:", getLowerAndUpperBounds(testArray1, target1));
console.log("Test Case 2:", getLowerAndUpperBounds(testArray1, target2));
console.log("Test Case 3:", getLowerAndUpperBounds(testArray1, target3));
console.log("Test Case 4:", getLowerAndUpperBounds(testArray1, target4));
console.log("Test Case 5:", getLowerAndUpperBounds(testArray1, target5));
console.log("Test Case 6:", getLowerAndUpperBounds(testArray2, target6));
console.log("Test Case 7:", getLowerAndUpperBounds(testArray2, target7));
console.log("Test Case 8:", getLowerAndUpperBounds(testArray3, target8));
console.log("Test Case 9:", getLowerAndUpperBounds(testArray4, target9));


console.log("\n4. Using Built-in Methods (indexOf/lastIndexOf):");
console.log("Test Case 1:", binarySearchBoundsBuiltIn(testArray1, target1));
console.log("Test Case 2:", binarySearchBoundsBuiltIn(testArray1, target2));
console.log("Test Case 3:", binarySearchBoundsBuiltIn(testArray1, target3));
console.log("Test Case 4:", binarySearchBoundsBuiltIn(testArray1, target4));
console.log("Test Case 5:", binarySearchBoundsBuiltIn(testArray1, target5));
console.log("Test Case 6:", binarySearchBoundsBuiltIn(testArray2, target6));
console.log("Test Case 7:", binarySearchBoundsBuiltIn(testArray2, target7));
console.log("Test Case 8:", binarySearchBoundsBuiltIn(testArray3, target8));
console.log("Test Case 9:", binarySearchBoundsBuiltIn(testArray4, target9));

console.log("\n5. Optimized Iterative Approach:");
console.log("Test Case 1:", binarySearchBoundsOptimized(testArray1, target1));
console.log("Test Case 2:", binarySearchBoundsOptimized(testArray1, target2));
console.log("Test Case 3:", binarySearchBoundsOptimized(testArray1, target3));
console.log("Test Case 4:", binarySearchBoundsOptimized(testArray1, target4));
console.log("Test Case 5:", binarySearchBoundsOptimized(testArray1, target5));
console.log("Test Case 6:", binarySearchBoundsOptimized(testArray2, target6));
console.log("Test Case 7:", binarySearchBoundsOptimized(testArray2, target7));
console.log("Test Case 8:", binarySearchBoundsOptimized(testArray3, target8));
console.log("Test Case 9:", binarySearchBoundsOptimized(testArray4, target9));
