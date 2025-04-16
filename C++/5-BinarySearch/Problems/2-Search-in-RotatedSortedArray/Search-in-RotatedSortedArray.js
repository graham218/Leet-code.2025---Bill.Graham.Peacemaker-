/**
 * Binary Search in Rotated Sorted Array - 5 Approaches
 *
 * Problem:
 * Given a sorted array that has been rotated by some number of positions,
 * find the index of a target element in the rotated array.
 *
 * Example:
 * Input: rotatedArray = [4, 5, 6, 7, 0, 1, 2], target = 0
 * Output: 4
 *
 * Constraints:
 * - The array is sorted before rotation.
 * - The rotation is done in a circular fashion.
 * - Array may contain duplicates (for some approaches).
 */

/**
 * Approach 1: Linear Search (Brute Force)
 * - Iterate through the array and check each element.
 * - Time Complexity: O(n)
 * - Space Complexity: O(1)
 */
function searchRotatedArray_linearSearch(rotatedArray, target) {
    console.log("Approach 1: Linear Search");
    for (let i = 0; i < rotatedArray.length; i++) {
        if (rotatedArray[i] === target) {
            console.log("Index:", i);
            return i;
        }
    }
    console.log("Index:", -1);
    return -1;
}

/**
 * Approach 2: Binary Search with Rotation Detection
 * - Find the pivot (rotation point).
 * - Perform binary search in the appropriate sorted half.
 * - Time Complexity: O(log n)
 * - Space Complexity: O(1)
 */
function searchRotatedArray_binarySearch(rotatedArray, target) {
    console.log("Approach 2: Binary Search with Rotation Detection");
    let left = 0;
    let right = rotatedArray.length - 1;

    while (left <= right) {
        const mid = Math.floor((left + right) / 2);

        if (rotatedArray[mid] === target) {
            console.log("Index:", mid);
            return mid;
        }

        if (rotatedArray[left] <= rotatedArray[mid]) { // Left half is sorted
            if (rotatedArray[left] <= target && target <= rotatedArray[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else { // Right half is sorted
            if (rotatedArray[mid] <= target && target <= rotatedArray[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    console.log("Index:", -1);
    return -1;
}

/**
 * Approach 3: Recursive Binary Search
 * - Recursive version of the binary search approach.
 * - Time Complexity: O(log n)
 * - Space Complexity: O(log n) (due to call stack)
 */
function searchRotatedArray_recursiveBinarySearch(rotatedArray, target, left, right) {
    if (left > right) {
        console.log("Index:", -1);
        return -1;
    }

    const mid = Math.floor((left + right) / 2);

    if (rotatedArray[mid] === target) {
        console.log("Index:", mid);
        return mid;
    }

    if (rotatedArray[left] <= rotatedArray[mid]) {
        if (rotatedArray[left] <= target && target <= rotatedArray[mid]) {
            return searchRotatedArray_recursiveBinarySearch(rotatedArray, target, left, mid - 1);
        } else {
            return searchRotatedArray_recursiveBinarySearch(rotatedArray, target, mid + 1, right);
        }
    } else {
        if (rotatedArray[mid] <= target && target <= rotatedArray[right]) {
            return searchRotatedArray_recursiveBinarySearch(rotatedArray, target, mid + 1, right);
        } else {
            return searchRotatedArray_recursiveBinarySearch(rotatedArray, target, left, mid - 1);
        }
    }
}

/**
 * Approach 4: Using find() (ES6) - Not recommended for rotated array, but showing for completeness
 * -  Uses the find() method, which is essentially a linear search.
 * -  Time Complexity: O(n)
 * -  Space Complexity: O(1)
 */
function searchRotatedArray_find(rotatedArray, target) {
    console.log("Approach 4: Using find()");
    const index = rotatedArray.findIndex(element => element === target);
    console.log("Index:", index);
    return index;
}

/**
 * Approach 5: Modified Binary Search with Duplicates Handling
 * - Handles cases where the rotated array contains duplicate elements.
 * - Time Complexity: O(log n) in the average case, O(n) in the worst case (when many duplicates)
 * - Space Complexity: O(1)
 */
function searchRotatedArray_binarySearchWithDuplicates(rotatedArray, target) {
    console.log("Approach 5: Binary Search with Duplicates Handling");
    let left = 0;
    let right = rotatedArray.length - 1;

    while (left <= right) {
        const mid = Math.floor((left + right) / 2);

        if (rotatedArray[mid] === target) {
            console.log("Index:", mid);
            return mid;
        }

        if (rotatedArray[left] === rotatedArray[mid] && rotatedArray[mid] === rotatedArray[right]) {
            // Cannot determine which side is sorted, shrink the window
            left++;
            right--;
        } else if (rotatedArray[left] <= rotatedArray[mid]) { // Left side is sorted
            if (rotatedArray[left] <= target && target < rotatedArray[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else { // Right side is sorted
            if (rotatedArray[mid] < target && target <= rotatedArray[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    console.log("Index:", -1);
    return -1;
}

// Example Usage:
const rotatedArray = [4, 5, 6, 7, 0, 1, 2];
const target = 0;

searchRotatedArray_linearSearch(rotatedArray, target); // Output: 4
searchRotatedArray_binarySearch(rotatedArray, target); // Output: 4
searchRotatedArray_recursiveBinarySearch(rotatedArray, target, 0, rotatedArray.length - 1); // Output: 4
searchRotatedArray_find(rotatedArray, target); // Output: 4
const rotatedArrayWithDuplicates = [2, 5, 6, 0, 0, 1, 2];
searchRotatedArray_binarySearchWithDuplicates(rotatedArrayWithDuplicates, 0);
