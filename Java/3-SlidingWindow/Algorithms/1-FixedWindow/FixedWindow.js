/*
Sliding Window to Fixed Window Problem:

Given an array of integers and a window size 'k', find the maximum (or minimum, or sum) of each subarray of size 'k' as the window slides through the array.  This is a classic problem, and we'll explore several JavaScript approaches.

For this example, we'll focus on finding the maximum value within each fixed-size window.

Example:
  Array: [1, 3, -1, -3, 5, 3, 6, 7]
  Window Size (k): 3

  Expected Output (Maximums):
  [3, 3, 5, 5, 6, 7]

  Explanation:
  - [1, 3, -1] -> Max: 3
  - [3, -1, -3] -> Max: 3
  - [-1, -3, 5] -> Max: 5
  - [-3, 5, 3] -> Max: 5
  - [5, 3, 6] -> Max: 6
  - [3, 6, 7] -> Max: 7
*/

const array = [1, 3, -1, -3, 5, 3, 6, 7];
const windowSize = 3;

console.log(`Array: [${array}], Window Size: ${windowSize}`);

// ----------------------------------------------------------------------------------------------------
// 1. Brute Force Approach
//    - Iterate through the array, creating subarrays of size 'k', and find the maximum in each.
//    - Time Complexity: O(n*k), where n is the array length.
//    - Space Complexity: O(1)
// ----------------------------------------------------------------------------------------------------
function findMaxSlidingWindow_BruteForce(arr, k) {
  if (!arr || k <= 0 || k > arr.length) {
    return []; // Handle invalid input
  }

  const result = [];
  for (let i = 0; i <= arr.length - k; i++) {
    let max = arr[i];
    for (let j = i + 1; j < i + k; j++) {
      if (arr[j] > max) {
        max = arr[j];
      }
    }
    result.push(max);
  }
  return result;
}

console.log("1. Brute Force:", findMaxSlidingWindow_BruteForce(array, windowSize));

// ----------------------------------------------------------------------------------------------------
// 2. Optimized Brute Force (Slight Improvement)
//    - Similar to brute force, but avoids re-finding the max of most of the window.
//    - Time Complexity: O(n*k) in the worst case, but often faster than pure brute force.
//    - Space Complexity: O(1)
// ----------------------------------------------------------------------------------------------------
function findMaxSlidingWindow_OptimizedBruteForce(arr, k) {
    if (!arr || k <= 0 || k > arr.length) {
        return [];
    }

    const result = [];
    let max = -Infinity;

    for (let i = 0; i <= arr.length - k; i++) {
        if (i === 0) { // Calculate max for the first window
            max = arr[0];
            for (let j = 1; j < k; j++) {
                if (arr[j] > max) {
                    max = arr[j];
                }
            }
        } else {
            // Optimization: Check if the outgoing element was the previous max
            if (arr[i - 1] === max) {
                max = arr[i]; // Recalculate max for the new window
                 for (let j = i+1; j < i + k; j++) {
                    if (arr[j] > max) {
                        max = arr[j];
                    }
                }
            }
            else{
                if(arr[i+k-1] > max){
                    max = arr[i+k-1];
                }
            }
        }
        result.push(max);
    }
    return result;
}

console.log("2. Optimized Brute Force:", findMaxSlidingWindow_OptimizedBruteForce(array, windowSize));

// ----------------------------------------------------------------------------------------------------
// 3. Using a Deque (Double-Ended Queue)
//    - Efficiently track the maximum element in the window.
//    - Store indices of elements in the deque, not the elements themselves.
//    - Deque maintains elements in decreasing order.
//    - Time Complexity: O(n) - Each element is processed at most twice.
//    - Space Complexity: O(k) - Deque stores at most 'k' elements.
// ----------------------------------------------------------------------------------------------------
function findMaxSlidingWindow_Deque(arr, k) {
  if (!arr || k <= 0 || k > arr.length) {
    return [];
  }

  const result = [];
  const deque = []; // Stores indices

  for (let i = 0; i < arr.length; i++) {
    // Remove elements from the front of the deque that are outside the current window
    while (deque.length > 0 && deque[0] < i - k + 1) {
      deque.shift(); // Remove from the front
    }

    // Remove elements from the back of the deque that are smaller than the current element
    while (deque.length > 0 && arr[deque[deque.length - 1]] < arr[i]) {
      deque.pop(); // Remove from the back
    }

    // Add the current element's index to the back of the deque
    deque.push(i);

    // The front of the deque now holds the index of the maximum element in the current window
    if (i >= k - 1) {
      result.push(arr[deque[0]]);
    }
  }
  return result;
}

console.log("3. Deque:", findMaxSlidingWindow_Deque(array, windowSize));

// ----------------------------------------------------------------------------------------------------
// 4. Using a Priority Queue (Max Heap)
//     - Use a max heap to store the elements of the current window.
//     - The root of the heap will always be the maximum element.
//     - In JavaScript, we can implement a max heap using an array and helper functions.
//     - Time Complexity: O(n log k) -  n is the length of the array, k is the window size
//     - Space Complexity: O(k) - The heap stores at most k elements.
// ----------------------------------------------------------------------------------------------------

function findMaxSlidingWindow_PriorityQueue(arr, k) {
  if (!arr || k <= 0 || k > arr.length) {
    return [];
  }

  const result = [];
  const heap = []; // Max heap (implemented as an array)

  // Helper functions for max heap operations
  const getParent = (i) => Math.floor((i - 1) / 2);
  const getLeftChild = (i) => 2 * i + 1;
  const getRightChild = (i) => 2 * i + 2;

  const swap = (arr, i, j) => {
    [arr[i], arr[j]] = [arr[j], arr[i]];
  };

  const heapifyUp = (arr, i) => {
    while (i > 0 && arr[i] > arr[getParent(i)]) {
      swap(arr, i, getParent(i));
      i = getParent(i);
    }
  };

  const heapifyDown = (arr, i, heapSize) => {
    let largest = i;
    const left = getLeftChild(i);
    const right = getRightChild(i);

    if (left < heapSize && arr[left] > arr[largest]) {
      largest = left;
    }
    if (right < heapSize && arr[right] > arr[largest]) {
      largest = right;
    }

    if (largest !== i) {
      swap(arr, i, largest);
      heapifyDown(arr, largest, heapSize);
    }
  };

  const insert = (arr, val) => {
    arr.push(val);
    heapifyUp(arr, arr.length - 1);
  };

  const extractMax = (arr, heapSize) => {
    const max = arr[0];
    arr[0] = arr[heapSize - 1];
    arr.pop();
    heapifyDown(arr, 0, heapSize-1);
    return max;
  };

  for (let i = 0; i < arr.length; i++) {
    insert(heap, arr[i]); // Insert into the heap

    if (i >= k - 1) {
        // Ensure the heap only contains elements from the current window
        while(heap.length > k){
            // remove the element that is out of the window.
            let elementToRemove = arr[i-k];
            let indexToRemove = heap.indexOf(elementToRemove);

            if(indexToRemove !== -1){ // Check if the element is in the heap
               heap.splice(indexToRemove, 1); // Remove it.
               let tempHeap = [...heap]; // copy the heap
               heap.length = 0; // clear the heap
                //rebuild the heap.
               for(let j=0; j< tempHeap.length; j++){
                   insert(heap, tempHeap[j]);
               }
            }
        }
      result.push(heap[0]); // Get the maximum (root of the heap)
    }
  }
  return result;
}

console.log("4. Priority Queue:", findMaxSlidingWindow_PriorityQueue(array, windowSize));

// ----------------------------------------------------------------------------------------------------
// 5. Dynamic Programming (Not ideal for fixed window, but shown for completeness)
//    -  While DP isn't the most efficient or intuitive approach for a fixed-size sliding window,
//       it can be adapted.  It's generally better suited for problems where the window size varies.
//    -  We can precompute maximums of sub-arrays and use that information.
//    -  Time Complexity: O(n*k) or potentially O(n + k) with optimization, but harder to achieve.
//    -  Space Complexity: O(n)
// ----------------------------------------------------------------------------------------------------
function findMaxSlidingWindow_DP(arr, k) {
    if (!arr || k <= 0 || k > arr.length) {
        return [];
    }

    const n = arr.length;
    const maxValues = [];  // Store maximum of subarrays ending at each index
    const result = [];

    // Calculate maximum of subarrays of size k ending at each index
    for (let i = 0; i < n; i++) {
        if (i < k - 1) {
            maxValues[i] = -Infinity; // Or any very small number
            for(let j = 0; j <= i; j++){
               maxValues[i] = Math.max(maxValues[i], arr[j]);
            }

        } else {
            maxValues[i] = arr[i];
            for (let j = i - k + 1; j < i; j++) {
                maxValues[i] = Math.max(maxValues[i], arr[j]);
            }
        }
    }

    // Extract the maximums for each sliding window
    for (let i = k - 1; i < n; i++) {
        result.push(maxValues[i]);
    }
    return result;
}

console.log("5. Dynamic Programming:", findMaxSlidingWindow_DP(array, windowSize));
