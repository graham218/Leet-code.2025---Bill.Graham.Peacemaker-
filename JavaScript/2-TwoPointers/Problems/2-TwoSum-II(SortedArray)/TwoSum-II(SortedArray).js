/**
 * Two Sum II - Sorted Array
 *
 * Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
 *
 * Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
 *
 * The tests are generated such that there is exactly one solution. You may not use the same element twice.
 *
 *
 * Example 1:
 *
 * Input: numbers = [2,7,11,15], target = 9
 * Output: [1,2]
 * Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
 *
 * Example 2:
 *
 * Input: numbers = [2,3,4], target = 6
 * Output: [1,3]
 * Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].
 *
 * Example 3:
 *
 * Input: numbers = [ -1, 0], target = -1
 * Output: [1,2]
 * Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].
 *
 *
 * Constraints:
 *
 * 2 <= numbers.length <= 3 * 104
 * -1000 <= numbers[i] <= 1000
 * numbers is sorted in non-decreasing order.
 * -1000 <= target <= 1000
 * The tests are generated such that there is exactly one solution.
 */

/**
 * Approach 1: Two Pointers
 *
 * This is the most efficient approach, leveraging the sorted nature of the input array.
 * We initialize two pointers, one at the beginning (left) and one at the end (right) of the array.
 * We then iterate, adjusting the pointers based on whether the sum of the numbers at the pointers is less than, equal to, or greater than the target.
 *
 * Time Complexity: O(n), where n is the length of the input array.
 * Space Complexity: O(1), constant extra space.
 */
function twoSumTwoPointers(numbers, target) {
  let left = 0;
  let right = numbers.length - 1;

  while (left < right) {
    const sum = numbers[left] + numbers[right];

    if (sum === target) {
      return [left + 1, right + 1]; // Add 1 to convert from 0-based to 1-based indexing
    } else if (sum < target) {
      left++; // Move left pointer to increase the sum
    } else {
      right--; // Move right pointer to decrease the sum
    }
  }

  // The problem states there is always a solution, so this line should never be reached.
  return [];
}

/**
 * Approach 2: Binary Search
 *
 * For each element in the array, we can use binary search to find the complement (the number needed to reach the target).
 *
 * Time Complexity: O(n log n), where n is the length of the input array (n iterations, each with log n binary search).
 * Space Complexity: O(1), constant extra space.
 */
function twoSumBinarySearch(numbers, target) {
  for (let i = 0; i < numbers.length; i++) {
    const complement = target - numbers[i];
    let left = i + 1; // Start search after the current index to avoid using the same element twice
    let right = numbers.length - 1;

    while (left <= right) {
      const mid = Math.floor((left + right) / 2);

      if (numbers[mid] === complement) {
        return [i + 1, mid + 1]; // Add 1 to convert to 1-based indexing
      } else if (numbers[mid] < complement) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
  }

  // The problem states there is always a solution, so this line should never be reached.
  return [];
}

/**
 * Approach 3: Hash Map (Not Optimal for Sorted Array, but Included for Completeness)
 *
 * We can use a hash map (object in JavaScript) to store each number and its index.
 * Then, for each number, we check if its complement exists in the hash map.
 *
 * Time Complexity: O(n) in average case, O(n^2) in worst case.  While the lookups in a hash map are typically O(1),
 * in the worst case (hash collisions), they can degrade to O(n).
 * Space Complexity: O(n), to store the numbers and their indices in the hash map.
 */
function twoSumHashMap(numbers, target) {
  const numMap = {};

  for (let i = 0; i < numbers.length; i++) {
    const complement = target - numbers[i];
    if (numMap[complement] !== undefined) {
      // Important:  The problem requires us to return 1-based indices.
      // i is already 0-based, and numMap stores 0-based indices.
      // So we add 1 to both.  Also, the problem statement guarantees
      // that the complement's index will be *different* from i.
      return [numMap[complement] + 1, i + 1];
    }
    numMap[numbers[i]] = i;
  }

  return []; //Should not reach here, as problem guarantees a solution
}

/**
 * Approach 4:  Recursive Binary Search
 *
 * This approach uses recursion with binary search.  For each number, it recursively searches for its complement.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(log n)  due to the recursive call stack.
 */
function twoSumRecursiveBinarySearch(numbers, target) {

    function binarySearch(arr, low, high, val) {
        if (low > high) {
            return -1;
        }
        const mid = Math.floor((low + high) / 2);
        if (arr[mid] === val) {
            return mid;
        } else if (arr[mid] < val) {
            return binarySearch(arr, mid + 1, high, val);
        } else {
            return binarySearch(arr, low, mid - 1, val);
        }
    }
  for (let i = 0; i < numbers.length; i++) {
    const complement = target - numbers[i];
    const complementIndex = binarySearch(numbers, i + 1, numbers.length - 1, complement);
    if (complementIndex !== -1) {
      return [i + 1, complementIndex + 1];
    }
  }
  return []; //Should not reach here
}

/**
 * Approach 5: Using Array.prototype.find() with index search
 *
 * This approach iterates through the array and uses the find() method
 * to locate the complement of the current number.
 *
 * Time Complexity: O(n^2) in the worst case.  find() itself is O(n), and it's inside a loop.
 * Space Complexity: O(1)
 */
function twoSumFind(numbers, target) {
  for (let i = 0; i < numbers.length; i++) {
    const complement = target - numbers[i];
    const complementIndex = numbers.slice(i + 1).findIndex(num => num === complement);
    if (complementIndex !== -1) {
      return [i + 1, i + 1 + complementIndex + 1]; // Adjust index for the slice
    }
  }
  return [];
}



// Example Usage and Output
const numbers1 = [2, 7, 11, 15];
const target1 = 9;
console.log("Example 1 - Two Pointers:", twoSumTwoPointers(numbers1, target1));       // Output: [1, 2]
console.log("Example 1 - Binary Search:", twoSumBinarySearch(numbers1, target1));     // Output: [1, 2]
console.log("Example 1 - Hash Map:", twoSumHashMap(numbers1, target1));           // Output: [1, 2]
console.log("Example 1 - Recursive Binary Search:", twoSumRecursiveBinarySearch(numbers1, target1)); // Output: [1, 2]
console.log("Example 1 - Find:", twoSumFind(numbers1, target1)); // Output: [1, 2]


const numbers2 = [2, 3, 4];
const target2 = 6;
console.log("Example 2 - Two Pointers:", twoSumTwoPointers(numbers2, target2));       // Output: [1, 3]
console.log("Example 2 - Binary Search:", twoSumBinarySearch(numbers2, target2));     // Output: [1, 3]
console.log("Example 2 - Hash Map:", twoSumHashMap(numbers2, target2));           // Output: [1, 3]
console.log("Example 2 - Recursive Binary Search:", twoSumRecursiveBinarySearch(numbers2, target2)); // Output: [1, 3]
console.log("Example 2 - Find:", twoSumFind(numbers2, target2)); // Output: [1, 3]

const numbers3 = [-1, 0];
const target3 = -1;
console.log("Example 3 - Two Pointers:", twoSumTwoPointers(numbers3, target3));       // Output: [1, 2]
console.log("Example 3 - Binary Search:", twoSumBinarySearch(numbers3, target3));     // Output: [1, 2]
console.log("Example 3 - Hash Map:", twoSumHashMap(numbers3, target3));           // Output: [1, 2]
console.log("Example 3 - Recursive Binary Search:", twoSumRecursiveBinarySearch(numbers3, target3)); // Output: [1, 2]
console.log("Example 3 - Find:", twoSumFind(numbers3, target3)); // Output: [1, 2]
