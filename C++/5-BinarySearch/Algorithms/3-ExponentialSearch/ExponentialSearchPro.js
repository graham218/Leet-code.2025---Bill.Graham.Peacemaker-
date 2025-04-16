// Binary Search & Exponential Search in JavaScript

/**
 * **Concept:**
 *
 * * **Binary Search:** A divide-and-conquer algorithm that efficiently searches for a target value within a sorted array. It repeatedly divides the search interval in half.
 * * **Exponential Search:** An extension of binary search that is useful for unbounded (infinite) arrays or very large arrays where the target is likely to be found closer to the beginning. It first finds a range where the target element might reside and then performs binary search within that range.
 *
 * **Why Combine Them?**
 *
 * Exponential search narrows down the search range for binary search, making the overall search more efficient, especially in large datasets.
 */

// Helper function for Binary Search
function binarySearch(arr, left, right, target) {
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);

        if (arr[mid] === target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

/**
 * 1. **Basic Exponential Search**
 * * Finds a suitable range for binary search by repeatedly doubling the index.
 * * Performs binary search on the found range.
 */
function exponentialSearchBasic(arr, target) {
    const n = arr.length;
    if (n === 0) return -1;

    if (arr[0] === target) return 0;

    let i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;
    }

    return binarySearch(arr, i / 2, Math.min(i, n - 1), target);
}

/**
 * 2. **Exponential Search with Optimized Range**
 * * Optimizes the range-finding step in exponential search.
 * * Improves efficiency by reducing the number of iterations in the initial loop.
 */
function exponentialSearchOptimized(arr, target) {
    const n = arr.length;
    if (n === 0) return -1;

    if (arr[0] === target) return 0;

    let i = 1;
    while (i < n && arr[i] < target) { // Changed condition to '< target'
        i *= 2;
    }
    // More precise range for binary search
    let left = i / 2;
    let right = Math.min(i, n -1);

    return binarySearch(arr, left, right, target);
}



/**
 * 3. **Exponential Search for Unbounded Arrays (Simulated)**
 * * Simulates an unbounded array using a function to access elements.
 * * Demonstrates how exponential search can be applied when the array size is unknown.
 */
function exponentialSearchUnbounded(getElement, target) {
    let i = 1;
    while (getElement(i) !== null && getElement(i) < target) {
        i *= 2;
    }
    const right = (getElement(i) === null) ? i/2 : i; //if element at i is null, target not found.
    return binarySearchSimulated(getElement, i / 2, right, target);
}

function binarySearchSimulated(getElement, left, right, target) {
     while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        const midValue = getElement(mid);

        if (midValue === null) {
            right = mid - 1; // Target is not in the valid range
        }
        else if (midValue === target) {
            return mid;
        } else if (midValue < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}


/**
 * 4. **Exponential Search with Early Termination**
 * * Adds a condition to terminate the search early if the target is found during the range-finding phase.
 */
function exponentialSearchEarlyTerminate(arr, target) {
    const n = arr.length;
    if (n === 0) return -1;

    if (arr[0] === target) return 0;

    let i = 1;
    while (i < n && arr[i] <= target) {
        if (arr[i] === target) { // Early termination if target is found
            return i;
        }
        i *= 2;
    }

    return binarySearch(arr, i / 2, Math.min(i, n - 1), target);
}

/**
 * 5. **Exponential Search with Iterative Binary Search**
 * * Implements binary search iteratively within the exponential search function for better performance in some environments.
 */
function exponentialSearchIterativeBinary(arr, target) {
    const n = arr.length;
    if (n === 0) return -1;
    if (arr[0] === target) return 0;

    let i = 1;
    while (i < n && arr[i] <= target)
        i = i*2;

    let left = i/2;
    let right = Math.min(i, n-1);

    while (left <= right) {
        let mid = Math.floor(left + (right - left)/2);
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}



// --- Example Usage and Output ---

const sortedArray = [2, 3, 4, 10, 40, 50, 60, 70, 80, 90, 100];
const targetValue = 70;

console.log("--- Binary Search & Exponential Search ---");
console.log("Sorted Array:", sortedArray);
console.log("Target Value:", targetValue);
console.log("\n--- Results ---");

// 1. Basic Exponential Search
const result1 = exponentialSearchBasic(sortedArray, targetValue);
console.log("1. Basic Exponential Search:", result1); // Output: 7

// 2. Optimized Exponential Search
const result2 = exponentialSearchOptimized(sortedArray, targetValue);
console.log("2. Optimized Exponential Search:", result2); // Output: 7

// 3. Exponential Search for Unbounded Arrays (Simulated)
const unboundedArray = (index) => {
    if (index >= sortedArray.length) return null;
    return sortedArray[index];
};
const result3 = exponentialSearchUnbounded(unboundedArray, targetValue);
console.log("3. Unbounded Array Search:", result3); // Output: 7

// 4. Exponential Search with Early Termination
const result4 = exponentialSearchEarlyTerminate(sortedArray, targetValue);
console.log("4. Early Termination Search:", result4); // Output: 7

// 5. Exponential Search with Iterative Binary Search
const result5 = exponentialSearchIterativeBinary(sortedArray, targetValue);
console.log("5. Iterative Binary Search:", result5); // Output: 7
