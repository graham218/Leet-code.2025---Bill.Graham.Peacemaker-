/**
 * Sorting Algorithms: Merge Sort and Quick Sort in JavaScript
 *
 * This document provides implementations of two popular sorting algorithms: Merge Sort and Quick Sort.
 * Each algorithm is presented with multiple approaches to showcase different ways of implementation.
 *
 * 1. Merge Sort
 * - Recursive Top-Down Merge Sort
 * - Iterative Bottom-Up Merge Sort
 *
 * 2. Quick Sort
 * - Quick Sort with Last Element as Pivot
 * - Quick Sort with First Element as Pivot
 * - Quick Sort with Random Element as Pivot
 *
 * Each implementation includes detailed comments to explain the logic and steps involved.
 * Example outputs are provided to demonstrate the sorting process.
 */

// ====================
// 1. Merge Sort
// ====================

/**
 * 1.1 Recursive Top-Down Merge Sort
 *
 * - Divides the array into two halves recursively until the base case of single-element arrays is reached.
 * - Merges the sub-arrays in a sorted manner.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n) (due to auxiliary array)
 */
function mergeSortRecursive(arr) {
  // Base case: If the array has one or zero elements, it's already sorted.
  if (arr.length <= 1) {
    return arr;
  }

  // Find the middle point of the array.
  const mid = Math.floor(arr.length / 2);

  // Recursively sort the left and right halves.
  const left = mergeSortRecursive(arr.slice(0, mid));
  const right = mergeSortRecursive(arr.slice(mid));

  // Merge the sorted halves.
  return merge(left, right);
}

/**
 * Helper function to merge two sorted arrays.
 *
 * - Compares elements from both arrays and adds the smaller element to the result array.
 * - Continues until one of the arrays is exhausted.
 * - Adds the remaining elements from the non-empty array to the result.
 */
function merge(left, right) {
  let result = [];
  let i = 0;
  let j = 0;

  // Compare elements from both arrays and add the smaller one to the result.
  while (i < left.length && j < right.length) {
    if (left[i] <= right[j]) {
      result.push(left[i]);
      i++;
    } else {
      result.push(right[j]);
      j++;
    }
  }

  // Add the remaining elements from the left array (if any).
  while (i < left.length) {
    result.push(left[i]);
    i++;
  }

  // Add the remaining elements from the right array (if any).
  while (j < right.length) {
    result.push(right[j]);
    j++;
  }

  return result;
}

// Example usage of recursive Merge Sort:
const recursiveMergeSortArray = [5, 3, 1, 7, 9, 2, 8, 6, 4];
const sortedRecursiveMergeSortArray = mergeSortRecursive([...recursiveMergeSortArray]); //spread to avoid modifying original
console.log("Recursive Merge Sort:");
console.log("Original Array:", recursiveMergeSortArray);
console.log("Sorted Array:", sortedRecursiveMergeSortArray);
// Output:
// Recursive Merge Sort:
// Original Array: [ 5, 3, 1, 7, 9, 2, 8, 6, 4 ]
// Sorted Array: [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]

/**
 * 1.2 Iterative Bottom-Up Merge Sort
 *
 * - Starts by merging adjacent pairs of elements.
 * - Merges sorted pairs into larger sorted runs.
 * - Continues until the entire array is sorted.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n) (due to auxiliary array)
 */
function mergeSortIterative(arr) {
  const n = arr.length;
  // `size` represents the size of subarrays being merged
  for (let size = 1; size < n; size *= 2) {
    // Iterate through the array, merging subarrays of size `size`
    for (let leftStart = 0; leftStart < n - size; leftStart += 2 * size) {
      const mid = leftStart + size - 1;
      const rightEnd = Math.min(leftStart + 2 * size - 1, n - 1);
      // Merge the two subarrays: arr[leftStart...mid] and arr[mid+1...rightEnd]
      mergeIterative(arr, leftStart, mid, rightEnd);
    }
  }
  return arr;
}

function mergeIterative(arr, leftStart, mid, rightEnd) {
  let i = leftStart;
  let j = mid + 1;
  let k = 0;
  const temp = []; // Temporary array to store the merged result

  // Compare elements from the two subarrays and add the smaller one to temp
  while (i <= mid && j <= rightEnd) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  // Copy the remaining elements from the left subarray (if any)
  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  // Copy the remaining elements from the right subarray (if any)
  while (j <= rightEnd) {
    temp[k++] = arr[j++];
  }

  // Copy the merged elements from temp back to the original array
  for (let p = 0; p < k; p++) {
    arr[leftStart + p] = temp[p];
  }
}
// Example usage of iterative Merge Sort:
const iterativeMergeSortArray = [5, 3, 1, 7, 9, 2, 8, 6, 4];
const sortedIterativeMergeSortArray = mergeSortIterative([...iterativeMergeSortArray]); //spread to avoid modifying original
console.log("\nIterative Merge Sort:");
console.log("Original Array:", iterativeMergeSortArray);
console.log("Sorted Array:", sortedIterativeMergeSortArray);
// Output:
// Iterative Merge Sort:
// Original Array: [ 5, 3, 1, 7, 9, 2, 8, 6, 4 ]
// Sorted Array: [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]


// ====================
// 2. Quick Sort
// ====================

/**
 * 2.1 Quick Sort with Last Element as Pivot
 *
 * - Selects the last element of the array as the pivot.
 * - Partitions the array into two sub-arrays: elements less than the pivot and elements greater than the pivot.
 * - Recursively sorts the sub-arrays.
 *
 * Time Complexity:
 * - Best and Average Case: O(n log n)
 * - Worst Case: O(n^2) (when the array is already sorted or reverse sorted)
 * Space Complexity: O(log n) (due to recursive calls)
 */
function quickSortLastPivot(arr, low, high) {
  if (low < high) {
    // Partition the array and get the pivot index.
    const pi = partitionLastPivot(arr, low, high);

    // Recursively sort the sub-arrays.
    quickSortLastPivot(arr, low, pi - 1);
    quickSortLastPivot(arr, pi + 1, high);
  }
}

/**
 * Helper function to partition the array.
 *
 * - Selects the last element as the pivot.
 * - Rearranges the array such that all elements less than the pivot are on the left,
 * and all elements greater than the pivot are on the right.
 * - Returns the index of the pivot element.
 */
function partitionLastPivot(arr, low, high) {
  const pivot = arr[high]; // Choose the last element as the pivot
  let i = low - 1; // Index of smaller element

  for (let j = low; j < high; j++) {
    // If the current element is smaller than or equal to the pivot
    if (arr[j] <= pivot) {
      i++; // Increment index of smaller element
      // Swap arr[i] and arr[j]
      [arr[i], arr[j]] = [arr[j], arr[i]];
    }
  }

  // Swap arr[i+1] and arr[high] (or pivot)
  [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]];

  return i + 1;
}

// Example usage of Quick Sort with last element as pivot:
const lastPivotQuickSortArray = [5, 3, 1, 7, 9, 2, 8, 6, 4];
quickSortLastPivot(lastPivotQuickSortArray, 0, lastPivotQuickSortArray.length - 1);
console.log("\nQuick Sort (Last Pivot):");
console.log("Sorted Array:", lastPivotQuickSortArray);
// Output:
// Quick Sort (Last Pivot):
// Sorted Array: [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]

/**
 * 2.2 Quick Sort with First Element as Pivot
 *
 * - Selects the first element of the array as the pivot.
 * - Partitions the array into two sub-arrays: elements less than the pivot and elements greater than the pivot.
 * - Recursively sorts the sub-arrays.
 *
 * Time Complexity:
 * - Best and Average Case: O(n log n)
 * - Worst Case: O(n^2) (when the array is already sorted or reverse sorted)
 * Space Complexity: O(log n) (due to recursive calls)
 */
function quickSortFirstPivot(arr, low, high) {
  if (low < high) {
    // Partition the array and get the pivot index.
    const pi = partitionFirstPivot(arr, low, high);

    // Recursively sort the sub-arrays.
    quickSortFirstPivot(arr, low, pi - 1);
    quickSortFirstPivot(arr, pi + 1, high);
  }
}

/**
  * Helper function to partition the array.
  *
  * - Selects the first element as the pivot.
  * - Rearranges the array such that all elements less than the pivot are on the left,
  * and all elements greater than the pivot are on the right.
  * - Returns the index of the pivot element.
  */
function partitionFirstPivot(arr, low, high) {
  const pivot = arr[low]; // Choose the first element as the pivot
  let i = low;
  let j = high;

  while (i < j) {
      // Find element greater than pivot from the left
      while (i <= high && arr[i] <= pivot) {
          i++;
      }

      // Find element smaller than pivot from the right
      while (j >= low && arr[j] > pivot) {
          j--;
      }

      if (i < j) {
          // Swap arr[i] and arr[j]
          [arr[i], arr[j]] = [arr[j], arr[i]];
      }
  }
  // Swap arr[low] and arr[j]
  [arr[low], arr[j]] = [arr[j], arr[low]];
  return j;
}

// Example usage of Quick Sort with first element as pivot:
const firstPivotQuickSortArray = [5, 3, 1, 7, 9, 2, 8, 6, 4];
quickSortFirstPivot(firstPivotQuickSortArray, 0, firstPivotQuickSortArray.length - 1);
console.log("\nQuick Sort (First Pivot):");
console.log("Sorted Array:", firstPivotQuickSortArray);

// Output:
// Quick Sort (First Pivot):
// Sorted Array: [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]

/**
 * 2.3 Quick Sort with Random Element as Pivot
 *
 * - Selects a random element of the array as the pivot.
 * - Partitions the array into two sub-arrays: elements less than the pivot and elements greater than the pivot.
 * - Recursively sorts the sub-arrays.
 *
 * Time Complexity:
 * - Best and Average Case: O(n log n)
 * - Worst Case: O(n^2) (rare, but possible)
 * Space Complexity: O(log n) (due to recursive calls)
 */
function quickSortRandomPivot(arr, low, high) {
  if (low < high) {
    // Partition the array and get the pivot index.
    const pi = partitionRandomPivot(arr, low, high);

    // Recursively sort the sub-arrays.
    quickSortRandomPivot(arr, low, pi - 1);
    quickSortRandomPivot(arr, pi + 1, high);
  }
}

/**
 * Helper function to partition the array.
 *
 * - Selects a random element as the pivot.
 * - Rearranges the array such that all elements less than the pivot are on the left,
 * and all elements greater than the pivot are on the right.
 * - Returns the index of the pivot element.
 */
function partitionRandomPivot(arr, low, high) {
  // Generate a random index between low and high (inclusive).
  const randomIndex = Math.floor(Math.random() * (high - low + 1)) + low;

  // Swap the random element with the last element (for convenience).
  [arr[randomIndex], arr[high]] = [arr[high], arr[randomIndex]];

  const pivot = arr[high]; // Choose the random element (now at the end) as the pivot.
  let i = low - 1; // Index of smaller element

  for (let j = low; j < high; j++) {
    // If the current element is smaller than or equal to the pivot
    if (arr[j] <= pivot) {
      i++; // Increment index of smaller element
      // Swap arr[i] and arr[j]
      [arr[i], arr[j]] = [arr[j], arr[i]];
    }
  }

  // Swap arr[i+1] and arr[high] (or pivot)
  [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]];

  return i + 1;
}

// Example usage of Quick Sort with random element as pivot:
const randomPivotQuickSortArray = [5, 3, 1, 7, 9, 2, 8, 6, 4];
quickSortRandomPivot(randomPivotQuickSortArray, 0, randomPivotQuickSortArray.length - 1);
console.log("\nQuick Sort (Random Pivot):");
console.log("Sorted Array:", randomPivotQuickSortArray);
// Output:
// Quick Sort (Random Pivot):
// Sorted Array: [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ]
