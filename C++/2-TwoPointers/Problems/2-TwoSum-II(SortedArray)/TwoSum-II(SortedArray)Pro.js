/**
 * Given a 1-indexed array of integers numbers that is sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
 * Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
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
 * Input: numbers = [-1,0], target = -1
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
 * Approach 1: Two Pointers (Most Efficient)
 *
 * This is the classic and most efficient solution for this problem, leveraging the sorted nature of the input array.
 *
 * Time Complexity: O(n), where n is the length of the input array.
 * Space Complexity: O(1),  constant extra space.
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

    // The problem statement guarantees a solution exists, so this return is technically unreachable.
    return [-1, -1];
}

/**
 * Approach 2: Binary Search
 *
 * This approach iterates through the array, and for each element, uses binary search to find the complement
 * (the number needed to reach the target).  While not as efficient as the two-pointer approach, it's a good
 * illustration of using binary search in a problem like this.
 *
 * Time Complexity: O(n log n), where n is the length of the input array (n for the loop, log n for binary search).
 * Space Complexity: O(1), constant extra space.
 */
function twoSumBinarySearch(numbers, target) {
    for (let i = 0; i < numbers.length; i++) {
        const complement = target - numbers[i];
        let low = i + 1; // Search in the rest of the array
        let high = numbers.length - 1;

        while (low <= high) {
            const mid = Math.floor((low + high) / 2);
            if (numbers[mid] === complement) {
                return [i + 1, mid + 1];
            } else if (numbers[mid] < complement) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return [-1, -1]; //Should not reach here, but good to have.
}


/**
 * Approach 3: Using a Map (Hash Map)
 *
 * This approach uses a hash map to store each number and its index.  Then, for each number, it checks if its
 * complement exists in the map.  This is a common approach for solving two-sum problems, though it's not
 * the most efficient here because the array is sorted.
 *
 * Time Complexity: O(n), where n is the length of the input array.
 * Space Complexity: O(n), in the worst case, we store all elements of the array in the map.
 */
function twoSumMap(numbers, target) {
    const numMap = new Map();

    for (let i = 0; i < numbers.length; i++) {
        const complement = target - numbers[i];
        if (numMap.has(complement)) {
            return [numMap.get(complement) + 1, i + 1];
        }
        numMap.set(numbers[i], i);
    }

    return [-1, -1]; //Should not reach here
}

/**
 * Approach 4: Recursive Binary Search
 *
 * This approach uses recursion for the binary search part.  It's functionally equivalent to the iterative
 * binary search approach, but implemented recursively.
 *
 * Time Complexity: O(n log n), where n is the length of the input array.
 * Space Complexity: O(log n) due to the recursive call stack.
 */

function twoSumRecursiveBinarySearch(numbers, target) {
  function binarySearch(arr, low, high, complement) {
    if (low > high) {
      return -1;
    }
    const mid = Math.floor((low + high) / 2);
    if (arr[mid] === complement) {
      return mid;
    } else if (arr[mid] < complement) {
      return binarySearch(arr, low, mid - 1, complement);
    } else {
      return binarySearch(arr, mid + 1, high, complement);
    }
  }

  for (let i = 0; i < numbers.length; i++) {
    const complement = target - numbers[i];
    const complementIndex = binarySearch(numbers, i + 1, numbers.length - 1, complement);
    if (complementIndex !== -1) {
      return [i + 1, complementIndex + 1];
    }
  }
  return [-1, -1];
}

/**
 * Approach 5: Using Reduce
 *
 * This approach uses the reduce method to iterate through the array. For each element, it searches for its complement in the rest of the array.
 * This is less efficient, but demonstrates using reduce for this kind of problem.
 *
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 */
function twoSumReduce(numbers, target) {
    let result = [-1, -1];
    numbers.reduce((_, num, index) => {
        if (result[0] !== -1) return; // Stop if solution found
        for (let j = index + 1; j < numbers.length; j++) {
            if (numbers[j] === target - num) {
                result = [index + 1, j + 1];
                return;
            }
        }
    }, 0);
    return result;
}

/**
 * Approach 6:  Two Pointers with Early Exit
 *
 * This is a variation of the two-pointer approach, but it adds an early exit condition.
 * If the current sum is greater than the target AND the smallest number is greater than 0,
 * it breaks the loop because the array is sorted, and all subsequent sums will also be greater
 * than the target.
 *
 * Time Complexity: O(n) in the average case, but can be less if the early exit is triggered.
 * Space Complexity: O(1)
 */
function twoSumTwoPointersEarlyExit(numbers, target) {
    let left = 0;
    let right = numbers.length - 1;

    while (left < right) {
        const sum = numbers[left] + numbers[right];

        if (sum === target) {
            return [left + 1, right + 1];
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
        if (sum > target && numbers[left] > 0) {
            break; // Early exit: No solution possible with current left
        }
    }

    return [-1, -1];
}



// Example Usage and Output
const numbers1 = [2, 7, 11, 15];
const target1 = 9;
console.log("Example 1:");
console.log("Two Pointers:", twoSumTwoPointers(numbers1, target1)); // Output: [ 1, 2 ]
console.log("Binary Search:", twoSumBinarySearch(numbers1, target1)); // Output: [ 1, 2 ]
console.log("Map:", twoSumMap(numbers1, target1));             // Output: [ 1, 2 ]
console.log("Recursive Binary Search:", twoSumRecursiveBinarySearch(numbers1, target1)); // Output: [ 1, 2 ]
console.log("Reduce:", twoSumReduce(numbers1, target1));                   // Output: [ 1, 2 ]
console.log("Two Pointers Early Exit:", twoSumTwoPointersEarlyExit(numbers1, target1)); // Output: [ 1, 2 ]


const numbers2 = [2, 3, 4];
const target2 = 6;
console.log("\nExample 2:");
console.log("Two Pointers:", twoSumTwoPointers(numbers2, target2)); // Output: [ 1, 3 ]
console.log("Binary Search:", twoSumBinarySearch(numbers2, target2)); // Output: [ 1, 3 ]
console.log("Map:", twoSumMap(numbers2, target2));             // Output: [ 1, 3 ]
console.log("Recursive Binary Search:", twoSumRecursiveBinarySearch(numbers2, target2)); // Output: [ 1, 3 ]
console.log("Reduce:", twoSumReduce(numbers2, target2));                   // Output: [ 1, 3 ]
console.log("Two Pointers Early Exit:", twoSumTwoPointersEarlyExit(numbers2, target2)); // Output: [ 1, 3 ]

const numbers3 = [-1, 0];
const target3 = -1;
console.log("\nExample 3:");
console.log("Two Pointers:", twoSumTwoPointers(numbers3, target3)); // Output: [ 1, 2 ]
console.log("Binary Search:", twoSumBinarySearch(numbers3, target3)); // Output: [ 1, 2 ]
console.log("Map:", twoSumMap(numbers3, target3));             // Output: [ 1, 2 ]
console.log("Recursive Binary Search:", twoSumRecursiveBinarySearch(numbers3, target3)); // Output: [ 1, 2 ]
console.log("Reduce:", twoSumReduce(numbers3, target3));                   // Output: [ 1, 2 ]
console.log("Two Pointers Early Exit:", twoSumTwoPointersEarlyExit(numbers3, target3)); // Output: [ 1, 2 ]

const numbers4 = [5,25,75];
const target4 = 100;
console.log("\nExample 4:");
console.log("Two Pointers:", twoSumTwoPointers(numbers4, target4));
console.log("Binary Search:", twoSumBinarySearch(numbers4, target4));
console.log("Map:", twoSumMap(numbers4, target4));
console.log("Recursive Binary Search:", twoSumRecursiveBinarySearch(numbers4, target4));
console.log("Reduce:", twoSumReduce(numbers4, target4));
console.log("Two Pointers Early Exit:", twoSumTwoPointersEarlyExit(numbers4, target4));
