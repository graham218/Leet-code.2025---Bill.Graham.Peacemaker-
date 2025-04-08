/**
 * Binary Search in Rotated Sorted Array - 5 Approaches
 *
 * Problem:
 * Given a sorted array that has been rotated by some number of positions,
 * find the index of a target value in the array.
 *
 * For example, the array [4, 5, 6, 7, 0, 1, 2] is a rotated sorted array.
 *
 */

/**
 * Helper function to perform standard binary search in a sorted array.
 * @param {number[]} arr The sorted array.
 * @param {number} target The target value to search for.
 * @param {number} low The starting index of the search range.
 * @param {number} high The ending index of the search range.
 * @returns {number} The index of the target value, or -1 if not found.
 */
function binarySearch(arr, target, low, high) {
    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        if (arr[mid] === target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Approach 1: Find Rotation Point and then Binary Search
//
// 1. Find the rotation point (the index of the smallest element).
// 2. Perform binary search in the left and right subarrays.
//
// Real-world application:
// -   Searching for a specific version of a software in a version-controlled
//     and rotated release history.  The rotation point is the point where
//     the version numbers "wrap around".
//
function searchRotatedArray_Approach1(nums, target) {
    if (!nums || nums.length === 0) {
        return -1;
    }

    const findRotationPoint = (arr) => {
        let low = 0;
        let high = arr.length - 1;
        while (low < high) {
            const mid = Math.floor((low + high) / 2);
            if (arr[mid] > arr[high]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    };

    const rotationPoint = findRotationPoint(nums);
    // console.log("Rotation Point:", rotationPoint); // Debugging
    const leftSearch = binarySearch(nums, target, 0, rotationPoint - 1);
    const rightSearch = binarySearch(nums, target, rotationPoint, nums.length - 1);

    if (leftSearch !== -1) {
        return leftSearch;
    } else {
        return rightSearch;
    }
}

// Approach 2: Modified Binary Search (Most Efficient)
//
// Perform binary search with modifications to handle the rotated array.
// Determine which half of the array is sorted and adjust the search range accordingly.
//
// Real-world application:
// -   Searching for a track in a rotated playlist.  The playlist is sorted,
//     but the starting point is arbitrary.  This approach is efficient
//     because it doesn't require a separate step to find the rotation point.
//
function searchRotatedArray_Approach2(nums, target) {
    if (!nums || nums.length === 0) {
        return -1;
    }

    let low = 0;
    let high = nums.length - 1;

    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        if (nums[mid] === target) {
            return mid;
        }

        if (nums[low] <= nums[mid]) { // Left half is sorted
            if (target >= nums[low] && target < nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else { // Right half is sorted
            if (target > nums[mid] && target <= nums[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return -1;
}

// Approach 3: Using indexOf (Simplest, but not optimal)
//
//  Use the built-in `indexOf` method. This is the simplest approach, but it
//  does not take advantage of the sorted nature of the array, so it has
//  linear time complexity.
//
// Real-world application:
// -   Quickly checking if an item exists in a database table where the order
//     is not guaranteed or indexed in a way that's relevant.  This is a
//     "brute force" approach, but it's simple and works.
function searchRotatedArray_Approach3(nums, target) {
    if (!nums || nums.length === 0) {
        return -1;
    }
    return nums.indexOf(target);
}

// Approach 4:  Iterative Linear Search
//
// Iterate through the array and compare each element to the target.
// This is a basic approach with linear time complexity.
//
// Real-world application:
// -   Searching for a physical book in a library shelf that is not perfectly
//     sorted.  You have to manually check each book until you find the one
//     you're looking for.
function searchRotatedArray_Approach4(nums, target) {
    if (!nums || nums.length === 0) {
        return -1;
    }
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] === target) {
            return i;
        }
    }
    return -1;
}

// Approach 5: Using Array.find()
//
// Use the `find()` method to locate the target.  This is similar to
// `indexOf` in that it doesn't leverage the sorted property.
//
// Real-world application:
// -   Searching for a specific product in a list of items retrieved from an
//     unsorted API response.  You need to find the product, but the order
//     from the API is not guaranteed.
function searchRotatedArray_Approach5(nums, target) {
    if (!nums || nums.length === 0) {
        return -1;
    }
    const found = nums.find(num => num === target);
    if (found === undefined) {
        return -1;
    }
    return nums.indexOf(found);
}

// Example usage and testing:
const rotatedArray = [4, 5, 6, 7, 0, 1, 2];
const target = 0;

console.log("Input Array:", rotatedArray);
console.log("Target Value:", target);
console.log("\n--- Results ---");

console.log("Approach 1 (Find Rotation Point):", searchRotatedArray_Approach1(rotatedArray, target));
console.log("Approach 2 (Modified Binary Search):", searchRotatedArray_Approach2(rotatedArray, target));
console.log("Approach 3 (Using indexOf):", searchRotatedArray_Approach3(rotatedArray, target));
console.log("Approach 4 (Iterative Linear Search):", searchRotatedArray_Approach4(rotatedArray, target));
console.log("Approach 5 (Using Array.find()):", searchRotatedArray_Approach5(rotatedArray, target));

// Additional test cases
console.log("\n--- Additional Test Cases ---");
const testCases = [
    { array: [4, 5, 6, 7, 0, 1, 2], target: 0, expected: 4 },
    { array: [4, 5, 6, 7, 0, 1, 2], target: 3, expected: -1 },
    { array: [1], target: 1, expected: 0 },
    { array: [1], target: 0, expected: -1 },
    { array: [3, 1], target: 1, expected: 1 },
    { array: [5, 1, 3], target: 3, expected: 2 },
    { array: [1, 3, 5], target: 1, expected: 0 }, // No rotation
    { array: [1, 3, 5], target: 3, expected: 1 }, // No rotation
    { array: [1, 3, 5], target: 5, expected: 2 }, // No rotation
    { array: [1, 3, 5], target: 0, expected: -1 },
    { array: [1, 3, 5], target: 6, expected: -1 },
    { array: [], target: 5, expected: -1 }, // Empty array
    { array: [1, 2, 3, 4, 5, 6, 7], target: 5, expected: 4}, //sorted array
    { array: [7, 1, 2, 3, 4, 5, 6], target: 1, expected: 1}, //rotated, target at the start of sorted part
    { array: [7, 1, 2, 3, 4, 5, 6], target: 7, expected: 0}, //rotated, target at the rotation point
    { array: [7, 1, 2, 3, 4, 5, 6], target: 6, expected: 6}, //rotated, target at the end
];

testCases.forEach((testCase, index) => {
    const { array, target, expected } = testCase;
    const result = searchRotatedArray_Approach2(array, target); // Using the most efficient approach
    console.log(`\nTest Case ${index + 1}:`);
    console.log("Array:", array, "Target:", target, "Expected:", expected, "Result:", result);
    if (result === expected) {
        console.log("Test Passed");
    } else {
        console.error("Test Failed");
    }
});
