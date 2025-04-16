/**
 * Binary Search - Find Minimum in Rotated Sorted Array
 *
 * Problem:
 *
 * Given a sorted array that has been rotated n number of times, find the minimum element in it.
 *
 * Example:
 *
 * Input: arr[] = {5, 6, 1, 2, 3, 4}
 * Output: 1
 *
 * Input: arr[] = {1, 2, 3, 4}
 * Output: 1
 *
 * Input: arr[] = {3, 4, 5, 1, 2}
 * Output: 1
 *
 *
 * Constraints:
 *
 * -   The array is sorted but rotated.
 * -   The array has at least one element.
 * -   All elements are unique.
 *
 *
 * Follow-up:
 *
 * -   What is the time complexity of your solution?
 * -   Can you solve it in O(log n) time complexity?
 *
 */

/**
 * Approach 1: Linear Search
 *
 * -   Iterate through the array and find the minimum element.
 *
 * Time Complexity: O(n)
 * Auxiliary Space: O(1)
 */
function findMinLinearSearch(arr) {
  let min = arr[0];
  for (let i = 1; i < arr.length; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
  }
  return min;
}

/**
 * Approach 2: Using Math.min()
 *
 * -   Use the spread operator to expand the array and find the minimum element using Math.min().
 *
 * Time Complexity: O(n)
 * Auxiliary Space: O(1)
 */
function findMinMathMin(arr) {
  return Math.min(...arr);
}

/**
 * Approach 3: Binary Search - Iterative
 *
 * -   Use binary search to find the minimum element.
 * -   The minimum element is the only element whose previous element is greater than itself.
 * -   If the middle element is greater than the last element, then the minimum element is in the right half.
 * -   If the middle element is less than the last element, then the minimum element is in the left half.
 *
 * Time Complexity: O(log n)
 * Auxiliary Space: O(1)
 */
function findMinBinarySearchIterative(arr) {
  let low = 0;
  let high = arr.length - 1;

  while (low < high) {
    let mid = Math.floor((low + high) / 2);

    if (arr[mid] > arr[high]) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return arr[low];
}

/**
 * Approach 4: Binary Search - Recursive
 *
 * -   Use binary search recursively to find the minimum element.
 *
 * Time Complexity: O(log n)
 * Auxiliary Space: O(log n) (due to recursion stack)
 */
function findMinBinarySearchRecursive(arr, low, high) {
  if (low >= high) {
    return arr[low];
  }

  let mid = Math.floor((low + high) / 2);

  if (arr[mid] > arr[high]) {
    return findMinBinarySearchRecursive(arr, mid + 1, high);
  } else {
    return findMinBinarySearchRecursive(arr, low, mid);
  }
}

/**
 * Approach 5: Optimized Binary Search
 *
 * - A further optimized version of the iterative binary search.
 * - Handles cases where the array is not rotated at all.
 *
 * Time Complexity: O(log n)
 * Auxiliary Space: O(1)
 */
function findMinOptimized(arr) {
    let low = 0;
    let high = arr.length - 1;

    // Handle the case where the array is not rotated
    if (arr[low] <= arr[high]) {
        return arr[low];
    }

    while (low < high) {
        let mid = Math.floor((low + high) / 2);

        if (arr[mid] > arr[mid + 1]) {
            return arr[mid + 1];
        }
        if (arr[mid - 1] > arr[mid]) {
            return arr[mid];
        }

        if (arr[mid] > arr[low]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; //Should not reach here, but added for safety.
}

// Example usage:
const arr1 = [5, 6, 1, 2, 3, 4];
const arr2 = [1, 2, 3, 4];
const arr3 = [3, 4, 5, 1, 2];
const arr4 = [10, 20, 30, 40, 50, 5, 6, 7];
const arr5 = [2, 1];
const arr6 = [2, 3, 4, 5, 6, 7, 8, 9, 10, 1];

console.log("Array 1:", arr1);
console.log("Linear Search:", findMinLinearSearch(arr1)); // Output: 1
console.log("Math.min():", findMinMathMin(arr1)); // Output: 1
console.log("Binary Search Iterative:", findMinBinarySearchIterative(arr1)); // Output: 1
console.log("Binary Search Recursive:", findMinBinarySearchRecursive(arr1, 0, arr1.length - 1)); // Output: 1
console.log("Optimized Binary Search:", findMinOptimized(arr1)); // Output: 1
console.log("\n");

console.log("Array 2:", arr2);
console.log("Linear Search:", findMinLinearSearch(arr2)); // Output: 1
console.log("Math.min():", findMinMathMin(arr2)); // Output: 1
console.log("Binary Search Iterative:", findMinBinarySearchIterative(arr2)); // Output: 1
console.log("Binary Search Recursive:", findMinBinarySearchRecursive(arr2, 0, arr2.length - 1)); // Output: 1
console.log("Optimized Binary Search:", findMinOptimized(arr2)); // Output: 1
console.log("\n");

console.log("Array 3:", arr3);
console.log("Linear Search:", findMinLinearSearch(arr3)); // Output: 1
console.log("Math.min():", findMinMathMin(arr3)); // Output: 1
console.log("Binary Search Iterative:", findMinBinarySearchIterative(arr3)); // Output: 1
console.log("Binary Search Recursive:", findMinBinarySearchRecursive(arr3, 0, arr3.length - 1)); // Output: 1
console.log("Optimized Binary Search:", findMinOptimized(arr3)); // Output: 1
console.log("\n");

console.log("Array 4:", arr4);
console.log("Linear Search:", findMinLinearSearch(arr4));
console.log("Math.min():", findMinMathMin(arr4));
console.log("Binary Search Iterative:", findMinBinarySearchIterative(arr4));
console.log("Binary Search Recursive:", findMinBinarySearchRecursive(arr4, 0, arr4.length - 1));
console.log("Optimized Binary Search:", findMinOptimized(arr4));
console.log("\n");

console.log("Array 5:", arr5);
console.log("Linear Search:", findMinLinearSearch(arr5));
console.log("Math.min():", findMinMathMin(arr5));
console.log("Binary Search Iterative:", findMinBinarySearchIterative(arr5));
console.log("Binary Search Recursive:", findMinBinarySearchRecursive(arr5, 0, arr5.length - 1));
console.log("Optimized Binary Search:", findMinOptimized(arr5));
console.log("\n");

console.log("Array 6:", arr6);
console.log("Linear Search:", findMinLinearSearch(arr6));
console.log("Math.min():", findMinMathMin(arr6));
console.log("Binary Search Iterative:", findMinBinarySearchIterative(arr6));
console.log("Binary Search Recursive:", findMinBinarySearchRecursive(arr6, 0, arr6.length - 1));
console.log("Optimized Binary Search:", findMinOptimized(arr6));
console.log("\n");
