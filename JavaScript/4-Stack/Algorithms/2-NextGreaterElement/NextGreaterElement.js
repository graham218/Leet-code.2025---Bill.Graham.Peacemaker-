/*
    Problem:
    Given an array, find the next greater element for each element in the array.
    The next greater element for an element x is the first element to the right of x
    that is greater than x. If no such element exists, return -1.

    Example:
    Input: [4, 5, 2, 25]
    Output: [5, 25, 25, -1]

    Explanation:
    For 4, the next greater element is 5.
    For 5, the next greater element is 25.
    For 2, the next greater element is 25.
    For 25, there is no greater element to its right, so the next greater element is -1.
*/

/**
 * Approach 1: Brute Force
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n) - for the result array
 */
function nextGreaterElementBruteForce(arr) {
    const n = arr.length;
    const result = new Array(n).fill(-1); // Initialize result array with -1

    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            if (arr[j] > arr[i]) {
                result[i] = arr[j];
                break; // Found the next greater, move to the next element
            }
        }
    }

    return result;
}

/**
 * Approach 2: Stack
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n) - for the stack and the result array
 */
function nextGreaterElementStack(arr) {
    const n = arr.length;
    const result = new Array(n).fill(-1);
    const stack = []; // Stack to store indices

    for (let i = n - 1; i >= 0; i--) {
        // While the stack is not empty and the current element is greater than
        // the element at the top of the stack, pop elements from the stack.
        while (stack.length > 0 && arr[i] >= arr[stack[stack.length - 1]]) {
            stack.pop();
        }

        // If the stack is not empty, the top element is the next greater element.
        if (stack.length > 0) {
            result[i] = arr[stack[stack.length - 1]];
        }

        stack.push(i); // Push the current element's index onto the stack
    }

    return result;
}

/**
 * Approach 3: Optimized Stack (Slightly more efficient)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function nextGreaterElementOptimizedStack(arr) {
    const n = arr.length;
    const result = new Array(n).fill(-1);
    const stack = [];

    for (let i = 0; i < n; i++) {
        while (stack.length > 0 && arr[i] > arr[stack[stack.length - 1]]) {
            const poppedIndex = stack.pop();
            result[poppedIndex] = arr[i];
        }
        stack.push(i);
    }
    return result;
}

/**
 * Approach 4: Using a Map with Stack
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function nextGreaterElementMap(arr) {
    const n = arr.length;
    const ngeMap = new Map();
    const stack = [];
    const result = new Array(n).fill(-1);

    for (let i = n - 1; i >= 0; i--) {
        while (stack.length > 0 && arr[i] >= arr[stack[stack.length - 1]]) {
            stack.pop();
        }
        ngeMap.set(i, stack.length > 0 ? arr[stack[stack.length - 1]] : -1);
        stack.push(i);
    }

    for (let i = 0; i < n; i++) {
        result[i] = ngeMap.get(i);
    }
    return result;
}


/**
 * Approach 5: Circular Array (if the input is considered circular)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function nextGreaterElementCircular(arr) {
    const n = arr.length;
    const result = new Array(n).fill(-1);
    const stack = [];

    for (let i = 2 * n - 1; i >= 0; i--) {
        while (stack.length > 0 && arr[i % n] >= arr[stack[stack.length - 1] % n]) {
            stack.pop();
        }
        result[i % n] = stack.length > 0 ? arr[stack[stack.length - 1] % n] : -1;
        stack.push(i);
    }
    return result;
}

// Example Usage:
const array = [4, 5, 2, 25];
console.log("Input Array:", array);

console.log("Brute Force:", nextGreaterElementBruteForce(array));
console.log("Stack:", nextGreaterElementStack(array));
console.log("Optimized Stack:", nextGreaterElementOptimizedStack(array));
console.log("Map:", nextGreaterElementMap(array));
console.log("Circular Array:", nextGreaterElementCircular(array)); // Added circular array example

const circularArray = [1, 2, 3, 4, 3];
console.log("Circular Array Input:", circularArray);
console.log("Circular Array Output:", nextGreaterElementCircular(circularArray));
