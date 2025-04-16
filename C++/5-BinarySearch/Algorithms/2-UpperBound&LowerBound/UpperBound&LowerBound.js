// Binary Search: Upper Bound & Lower Bound in JavaScript

// Helper function to perform standard binary search (iterative)
function binarySearchIterative(arr, target) {
    let low = 0;
    let high = arr.length - 1;

    while (low <= high) {
        let mid = Math.floor((low + high) / 2);
        if (arr[mid] === target) {
            return mid; // Found the target
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Target not found
}

// 1. Lower Bound - Iterative Approach 1
function lowerBoundIterative1(arr, target) {
    let low = 0;
    let high = arr.length - 1;
    let result = -1;

    while (low <= high) {
        let mid = Math.floor((low + high) / 2);
        if (arr[mid] === target) {
            result = mid; // Found a match, but keep looking left
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

// 2. Lower Bound - Iterative Approach 2 (Slightly different logic)
function lowerBoundIterative2(arr, target) {
    let low = 0;
    let high = arr.length; // Note: high is one position past the last element.
    let result = -1;

    while (low < high) { // Changed condition to low < high
        let mid = Math.floor((low + high) / 2);
        if (arr[mid] >= target) { // Changed to >=
            result = mid;
            high = mid; // Important: high = mid, not mid - 1
        } else {
            low = mid + 1;
        }
    }
    return (result !== -1 && arr[result] === target) ? result : -1; // Post-check
}


// 3. Upper Bound - Iterative Approach 1
function upperBoundIterative1(arr, target) {
    let low = 0;
    let high = arr.length - 1;
    let result = -1;

    while (low <= high) {
        let mid = Math.floor((low + high) / 2);
        if (arr[mid] === target) {
            result = mid; // Found a match, keep looking right
            low = mid + 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

// 4. Upper Bound - Iterative Approach 2 (Slightly different)
function upperBoundIterative2(arr, target) {
    let low = 0;
    let high = arr.length; // Note: high is one position past the last element.
    let result = -1;

    while (low < high) { // Changed condition to low < high
        let mid = Math.floor((low + high) / 2);
        if (arr[mid] <= target) { // Changed to <=
            result = mid;
            low = mid + 1;
        } else {
            high = mid; // Important: high = mid
        }
    }
    return (result !== -1 && arr[result] === target) ? result : -1;
}

// 5. Lower and Upper Bound - Recursive Approach
function lowerAndUpperBoundRecursive(arr, target, low, high, findLower) {
    if (low > high) {
        return -1;
    }

    let mid = Math.floor((low + high) / 2);

    if (arr[mid] === target) {
        let result = mid;
        if (findLower) {
            // Find Lower Bound, continue searching in the left half.
            let lower = lowerAndUpperBoundRecursive(arr, target, low, mid - 1, findLower);
            return lower === -1 ? result : lower; // Return the leftmost index
        } else {
            // Find Upper Bound, continue searching in the right half.
             let upper = lowerAndUpperBoundRecursive(arr, target, mid + 1, high, findLower);
            return upper === -1 ? result : upper;
        }
    } else if (arr[mid] < target) {
        return lowerAndUpperBoundRecursive(arr, target, mid + 1, high, findLower);
    } else {
        return lowerAndUpperBoundRecursive(arr, target, low, mid - 1, findLower);
    }
}

// Wrapper functions for recursive approach
function lowerBoundRecursive(arr, target) {
    return lowerAndUpperBoundRecursive(arr, target, 0, arr.length - 1, true);
}

function upperBoundRecursive(arr, target) {
    return lowerAndUpperBoundRecursive(arr, target, 0, arr.length - 1, false);
}



// Example Usage and Output
const sortedArray = [2, 4, 4, 4, 6, 8, 8, 10, 12, 12];
const targetValue = 4;
const targetValueForUpper = 8;

console.log("Array:", sortedArray);
console.log("Target Value:", targetValue);
console.log("----------------------------------");
console.log("Binary Search (Iterative):", binarySearchIterative(sortedArray, targetValue));
console.log("----------------------------------");
console.log("Lower Bound (Iterative 1):", lowerBoundIterative1(sortedArray, targetValue));
console.log("Lower Bound (Iterative 2):", lowerBoundIterative2(sortedArray, targetValue));
console.log("Lower Bound (Recursive):", lowerBoundRecursive(sortedArray, targetValue));

console.log("----------------------------------");
console.log("Upper Bound (Iterative 1):", upperBoundIterative1(sortedArray, targetValueForUpper));
console.log("Upper Bound (Iterative 2):", upperBoundIterative2(sortedArray, targetValueForUpper));
console.log("Upper Bound (Recursive):", upperBoundRecursive(sortedArray, targetValueForUpper));
