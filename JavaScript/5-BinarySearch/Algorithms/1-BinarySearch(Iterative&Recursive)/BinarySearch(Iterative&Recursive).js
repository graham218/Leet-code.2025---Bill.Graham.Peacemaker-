// Binary Search - Iterative & Recursive Approaches

/**
 * Binary Search is an efficient algorithm for finding a target value within a sorted array.
 * It works by repeatedly dividing the search interval in half.
 */

const binarySearch = {

    /**
     * 1. Iterative Approach 1: Basic Iteration
     *
     * @param {number[]} arr - The sorted array to search in.
     * @param {number} target - The value to search for.
     * @returns {number} The index of the target value if found, otherwise -1.
     */
    iterative1: function(arr, target) {
        let low = 0;
        let high = arr.length - 1;

        while (low <= high) {
            const mid = Math.floor((low + high) / 2); // Calculate mid-point
            if (arr[mid] === target) {
                return mid; // Target found at mid
            } else if (arr[mid] < target) {
                low = mid + 1; // Target is in the right half
            } else {
                high = mid - 1; // Target is in the left half
            }
        }
        return -1; // Target not found
    },

    /**
     * 2. Iterative Approach 2: Using bitwise right shift for mid calculation
     * (Slightly more performant in some JS engines)
     *
     * @param {number[]} arr - The sorted array.
     * @param {number} target - The target value.
     * @returns {number} The index of the target or -1 if not found.
     */
    iterative2: function(arr, target) {
        let low = 0;
        let high = arr.length - 1;

        while (low <= high) {
            const mid = (low + high) >>> 1; // Bitwise right shift for division by 2
            if (arr[mid] === target) {
                return mid;
            } else if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    },

    /**
     * 3. Recursive Approach 1: Classic Recursion
     *
     * @param {number[]} arr - The sorted array.
     * @param {number} target - The target value.
     * @param {number} low - The starting index of the search interval.
     * @param {number} high - The ending index of the search interval.
     * @returns {number} The index of the target or -1 if not found.
     */
    recursive1: function(arr, target, low, high) {
        if (low > high) {
            return -1; // Base case: target not found
        }

        const mid = Math.floor((low + high) / 2);
        if (arr[mid] === target) {
            return mid; // Base case: target found
        } else if (arr[mid] < target) {
            return this.recursive1(arr, target, mid + 1, high); // Recursive call on right half
        } else {
            return this.recursive1(arr, target, low, mid - 1); // Recursive call on left half
        }
    },

    /**
     * 4. Recursive Approach 2: Simplified initial call
     * (Wraps the classic recursive approach for easier initial invocation)
     *
     * @param {number[]} arr - The sorted array.
     * @param {number} target - The target value.
     * @returns {number} The index of the target or -1 if not found.
     */
    recursive2: function(arr, target) {
        return this.recursive1(arr, target, 0, arr.length - 1);
    },

    /**
     * 5. Recursive Approach 3: Tail Recursion (Optimized - although JavaScript doesn't optimize tail calls)
     * Tail recursion is a form of recursion where the recursive call is the last operation
     * in the function.  Some languages can optimize this to avoid stack overflow.  JS doesn't, but the structure is shown.
     *
     * @param {number[]} arr - The sorted array.
     * @param {number} target - The target value.
     * @param {number} low - The starting index of the search interval.
     * @param {number} high - The ending index of the search interval.
     * @param {number} result - Accumulates the result (index or -1).
     * @returns {number} The index of the target or -1 if not found.
     */
    recursiveTail: function(arr, target, low, high, result) {
        if (low > high) {
            return result;
        }

        const mid = Math.floor((low + high) / 2);
        if (arr[mid] === target) {
            return mid;
        } else if (arr[mid] < target) {
            return this.recursiveTail(arr, target, mid + 1, high, result);
        } else {
            return this.recursiveTail(arr, target, low, mid - 1, result);
        }
    },
    /**
     * 5. Recursive Approach 3 (Continued): Tail Recursion Helper
     * This function helps to initiate the tail recursion with the appropriate initial values.
     * @param arr
     * @param target
     * @returns {number}
     */
    recursive3: function(arr, target) {
      return this.recursiveTail(arr, target, 0, arr.length - 1, -1);
    }
};

// Example Usage:
const sortedArray = [-1, 0, 3, 5, 9, 12];
const targetValue = 9;

console.log("Array: ", sortedArray);
console.log("Target: ", targetValue);

console.log("\n--- Binary Search Results ---");
console.log("1. Iterative 1:", binarySearch.iterative1(sortedArray, targetValue));
console.log("2. Iterative 2:", binarySearch.iterative2(sortedArray, targetValue));
console.log("3. Recursive 1:", binarySearch.recursive1(sortedArray, targetValue, 0, sortedArray.length - 1));
console.log("4. Recursive 2:", binarySearch.recursive2(sortedArray, targetValue));
console.log("5. Recursive 3 (Tail):", binarySearch.recursive3(sortedArray, targetValue));

// Example with target not in array
const targetNotFound = 7;
console.log("\n--- Target not found Example ---");
console.log("Array: ", sortedArray);
console.log("Target:", targetNotFound);
console.log("1. Iterative 1:", binarySearch.iterative1(sortedArray, targetNotFound));
console.log("2. Iterative 2:", binarySearch.iterative2(sortedArray, targetNotFound));
console.log("3. Recursive 1:", binarySearch.recursive1(sortedArray, targetNotFound, 0, sortedArray.length - 1));
console.log("4. Recursive 2:", binarySearch.recursive2(sortedArray, targetNotFound));
console.log("5. Recursive 3 (Tail):", binarySearch.recursive3(sortedArray, targetNotFound));
