/*
    Next Greater Element Problem:

    Given an array, find the next greater element (NGE) for each element. The next greater element for an element x is the first element to the right of x that is greater than x. If no such element exists, the NGE is -1.

    Here are five different approaches to solve this problem, along with real-world project implementation examples:
*/

// 1. Brute Force Approach
//    - Iterate through the array.
//    - For each element, iterate through the rest of the array to find the first greater element.
//
//    - Real-world example:  Analyzing website traffic logs.  For each page visit, find the next page visited by the same user that had a higher bounce rate.
//
function nextGreaterElement_BruteForce(arr) {
    const n = arr.length;
    const result = new Array(n).fill(-1);

    for (let i = 0; i < n; i++) {
        for (let j = i + 1; j < n; j++) {
            if (arr[j] > arr[i]) {
                result[i] = arr[j];
                break;
            }
        }
    }
    return result;
}

// 2. Stack Approach
//    - Use a stack to keep track of elements.
//    - Iterate through the array from right to left.
//    - For each element:
//        - Pop elements from the stack that are less than or equal to the current element.
//        - The next greater element is the top of the stack (or -1 if the stack is empty).
//        - Push the current element onto the stack.
//
//    - Real-world example:  Stock price analysis.  For each day's stock price, find the next day's price that is higher.
//
function nextGreaterElement_Stack(arr) {
    const n = arr.length;
    const result = new Array(n).fill(-1);
    const stack = [];

    for (let i = n - 1; i >= 0; i--) {
        while (stack.length > 0 && stack[stack.length - 1] <= arr[i]) {
            stack.pop();
        }
        result[i] = stack.length > 0 ? stack[stack.length - 1] : -1;
        stack.push(arr[i]);
    }
    return result;
}

// 3. Optimized Stack Approach (Iterate Once)
//   - Uses a stack, but iterates through the array only once.
//   - Iterate through the array.
//   - For each element:
//     - While the stack is not empty and the current element is greater than the element at the top of the stack:
//       - Pop the element from the stack.
//       - The current element is the NGE for the popped element.
//     - Push the current element's index onto the stack.
//   - After the loop, any elements remaining in the stack do not have an NGE in the array.
//
//   - Real-world example:  Finding trends in sensor data.  For each sensor reading, find the next reading that exceeds a threshold.
function nextGreaterElement_OptimizedStack(arr) {
    const n = arr.length;
    const result = new Array(n).fill(-1);
    const stack = [];

    for (let i = 0; i < n; i++) {
        while (stack.length > 0 && arr[i] > arr[stack[stack.length - 1]]) {
            const top = stack.pop();
            result[top] = arr[i];
        }
        stack.push(i);
    }
    return result;
}

// 4. Using a Map with Stack
//    - Use a stack to keep track of elements' indices.
//    - Use a Map to store the NGE for each element.
//    - Iterate through the array.
//    - For each element:
//        - Pop elements from the stack whose values are less than the current element.
//        - Store the current element as the NGE for the popped elements in the Map.
//        - Push the current element's index onto the stack.
//    - Iterate through the array and use the Map to populate the result array.
//
//    - Real-world example:  Compiler design.  For each variable declaration, find the next declaration of a variable with a larger scope.
//
function nextGreaterElement_MapAndStack(arr) {
    const n = arr.length;
    const result = new Array(n).fill(-1);
    const stack = [];
    const ngeMap = new Map();

    for (let i = 0; i < n; i++) {
        while (stack.length > 0 && arr[i] > arr[stack[stack.length - 1]]) {
            const top = stack.pop();
            ngeMap.set(top, arr[i]);
        }
        stack.push(i);
    }

    for (let i = 0; i < n; i++) {
        result[i] = ngeMap.get(i) || -1;
    }
    return result;
}

// 5. Circular Array Approach
//    - To find the next greater element in a circular array (where the last element's next is the first element),
//      we can effectively double the array by iterating twice.
//    - Use a stack to keep track of indices.
//    - Iterate through the doubled array (or iterate twice through the original).
//    - For each element:
//        - Pop elements from the stack whose values are less than the current element.
//        - Update the NGE for the popped elements.
//        - Push the current element's index onto the stack.  Use the modulo operator (%) to handle the circular indexing.
//
//    - Real-world example:  Analyzing server request patterns in a loop.  For each request, find the next request in the cycle that has a higher priority.
//
function nextGreaterElement_CircularArray(arr) {
    const n = arr.length;
    const result = new Array(n).fill(-1);
    const stack = [];

    for (let i = 0; i < 2 * n; i++) {
        while (stack.length > 0 && arr[i % n] > arr[stack[stack.length - 1]]) {
            const top = stack.pop();
            result[top] = arr[i % n];
        }
        stack.push(i % n);
    }
    return result;
}

// Example Usage and Output
const array = [4, 5, 2, 25, 7, 8, 1];
console.log("Original Array:", array);

console.log("\n1. Brute Force Approach:", nextGreaterElement_BruteForce(array));
console.log("   Expected Output:    [ 5, 25, 25, -1, 8, -1, -1 ]");

console.log("\n2. Stack Approach:", nextGreaterElement_Stack(array));
console.log("   Expected Output:    [ 5, 25, 25, -1, 8, -1, -1 ]");

console.log("\n3. Optimized Stack Approach:", nextGreaterElement_OptimizedStack(array));
console.log("   Expected Output:    [ 5, 25, 25, -1, 8, -1, -1 ]");

console.log("\n4. Map and Stack Approach:", nextGreaterElement_MapAndStack(array));
console.log("   Expected Output:    [ 5, 25, 25, -1, 8, -1, -1 ]");

const circularArray = [1, 2, 1];
console.log("\nOriginal Circular Array:", circularArray);
console.log("5. Circular Array Approach:", nextGreaterElement_CircularArray(circularArray));
console.log("   Expected Output:    [ 2, -1, 2 ]");
