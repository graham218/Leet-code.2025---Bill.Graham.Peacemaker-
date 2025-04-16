/**
 * Dutch National Flag Algorithm (3-way Partitioning)
 *
 * This algorithm partitions an array into three sections based on a pivot value.  It's named after the Dutch flag, which has three colors: red, white, and blue.  We'll generalize this to 0, 1, and 2.
 *
 * Problem:
 * Given an array of integers, rearrange it such that all 0s come first, followed by all 1s, and then all 2s.
 *
 * Key Idea:
 * Maintain three pointers:
 * - `low`:  The end of the 0s section.
 * - `mid`: The current element being processed.
 * - `high`: The beginning of the 2s section.
 *
 * Invariant:
 * - arr[0...low-1] contains 0s.
 * - arr[low...mid-1] contains 1s.
 * - arr[high+1...n-1] contains 2s.
 *
 * Five Approaches with Real-World Project Implementations:
 *
 * 1. Single-Pass with Swaps (Most Efficient)
 * - This is the classic and most efficient approach.  It processes the array in a single pass using swaps.
 * - Real-world use case: Sorting network packets based on priority (0: low, 1: medium, 2: high).
 *
 * 2. Counting Sort (Not In-Place)
 * - This approach counts the occurrences of 0, 1, and 2, and then reconstructs the array.
 * - Real-world use case:  Sorting student grades (if grades are limited to a small set of discrete values).
 *
 * 3. Using JavaScript's `sort()` method (Simplest, but not optimal)
 * -  Leverages JavaScript's built-in sort function with a custom comparator.
 * - Real-world use case: Quick and dirty sorting for a small dataset where performance isn't critical.
 *
 * 4.  Two-Pass Approach
 * - First pass: moves all 0s to the beginning
 * - Second pass: moves all 2s to the end
 * - Real-world use case:  Preprocessing data for a machine learning algorithm that requires data to be in a specific order.
 *
 * 5. Recursive Approach
 * - A divide-and-conquer approach, similar to quicksort partitioning, applied to the 3-way partition.
 * - Real-world use case: Implementing a parallel sorting algorithm (less common for DNF, but illustrates recursion).
 */

/**
 * 1. Single-Pass with Swaps (Most Efficient)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function dutchNationalFlagSinglePass(arr) {
    let low = 0;
    let mid = 0;
    let high = arr.length - 1;

    while (mid <= high) {
        switch (arr[mid]) {
            case 0:
                [arr[low], arr[mid]] = [arr[mid], arr[low]]; // Swap arr[low] and arr[mid]
                low++;
                mid++;
                break;
            case 1:
                mid++;
                break;
            case 2:
                [arr[mid], arr[high]] = [arr[high], arr[mid]]; // Swap arr[mid] and arr[high]
                high--;
                break;
            default:
                // Handle invalid input (optional, for robustness)
                throw new Error("Invalid input: Array should only contain 0, 1, or 2.");
        }
    }
    return arr;
}

/**
 * 2. Counting Sort (Not In-Place)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)  (because we only use a fixed amount of extra space: counts for 0, 1, 2)
 */
function dutchNationalFlagCountingSort(arr) {
    let counts = [0, 0, 0]; // counts[0] = count of 0s, counts[1] = count of 1s, counts[2] = count of 2s

    // Count occurrences of each element
    for (let num of arr) {
        if (num === 0) {
            counts[0]++;
        } else if (num === 1) {
            counts[1]++;
        } else if (num === 2) {
            counts[2]++;
        } else {
             throw new Error("Invalid input: Array should only contain 0, 1, or 2.");
        }
    }

    // Reconstruct the array
    let index = 0;
    for (let i = 0; i < counts[0]; i++) {
        arr[index++] = 0;
    }
    for (let i = 0; i < counts[1]; i++) {
        arr[index++] = 1;
    }
    for (let i = 0; i < counts[2]; i++) {
        arr[index++] = 2;
    }
    return arr;
}

/**
 * 3. Using JavaScript's `sort()` method (Simplest, but not optimal)
 *
 * Time Complexity: O(n log n)  (due to the generic sort)
 * Space Complexity: O(log n)  (depending on the sorting algorithm implementation)
 */
function dutchNationalFlagSort(arr) {
    return arr.sort((a, b) => a - b);
}

/**
 * 4. Two-Pass Approach
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function dutchNationalFlagTwoPass(arr) {
    let n = arr.length;

    // First pass: Move all 0s to the beginning
    let low = 0;
    for (let i = 0; i < n; i++) {
        if (arr[i] === 0) {
            [arr[low], arr[i]] = [arr[i], arr[low]];
            low++;
        }
    }

    // Second pass: Move all 2s to the end
    let high = n - 1;
    for (let i = n - 1; i >= low; i--) {
        if (arr[i] === 2) {
            [arr[high], arr[i]] = [arr[i], arr[high]];
            high--;
        }
    }
    return arr;
}

/**
 * 5. Recursive Approach
 *
 * Time Complexity: O(n) on average, O(n^2) worst case
 * Space Complexity: O(log n) on average, O(n) worst case (due to recursion)
 */
function dutchNationalFlagRecursive(arr, low, high) {
    if (low < high) {
        let pivot = arr[high]; // Choose the last element as the pivot
        let i = low - 1;

        for (let j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                [arr[i], arr[j]] = [arr[j], arr[i]];
            }
        }
        [arr[i + 1], arr[high]] = [arr[high], arr[i + 1]];
        let mid = i + 1;

        dutchNationalFlagRecursive(arr, low, mid - 1);  // Sort left partition
        dutchNationalFlagRecursive(arr, mid + 1, high); // Sort right partition, although it will only contain 2s.
    }
    return arr;
}



// Example Usage
let arr1 = [0, 1, 2, 0, 1, 2, 0, 1, 2];
let arr2 = [2, 0, 1, 2, 1, 0];
let arr3 = [1, 2, 0];
let arr4 = [0, 0, 0, 1, 1, 2, 2, 2];
let arr5 = [2, 2, 2, 1, 1, 0, 0, 0];

console.log("Original Array 1:", arr1);
console.log("Single Pass:", dutchNationalFlagSinglePass([...arr1])); // [ 0, 0, 0, 1, 1, 1, 2, 2, 2 ]
console.log("Counting Sort:", dutchNationalFlagCountingSort([...arr1])); // [ 0, 0, 0, 1, 1, 1, 2, 2, 2 ]
console.log("JS Sort:", dutchNationalFlagSort([...arr1]));       // [ 0, 0, 0, 1, 1, 1, 2, 2, 2 ]
console.log("Two Pass:", dutchNationalFlagTwoPass([...arr1]));       // [ 0, 0, 0, 1, 1, 1, 2, 2, 2 ]
console.log("Recursive:", dutchNationalFlagRecursive([...arr1], 0, arr1.length - 1));       // [ 0, 0, 0, 1, 1, 1, 2, 2, 2 ]


console.log("\nOriginal Array 2:", arr2);
console.log("Single Pass:", dutchNationalFlagSinglePass([...arr2])); // [ 0, 1, 2, 2, 1, 0 ] -> [0, 0, 1, 1, 2, 2]
console.log("Counting Sort:", dutchNationalFlagCountingSort([...arr2])); // [ 0, 0, 1, 1, 2, 2 ]
console.log("JS Sort:", dutchNationalFlagSort([...arr2]));       // [ 0, 0, 1, 1, 2, 2 ]
console.log("Two Pass:", dutchNationalFlagTwoPass([...arr2]));       // [ 0, 0, 1, 1, 2, 2 ]
console.log("Recursive:", dutchNationalFlagRecursive([...arr2], 0, arr2.length - 1));

console.log("\nOriginal Array 3:", arr3);
console.log("Single Pass:", dutchNationalFlagSinglePass([...arr3]));
console.log("Counting Sort:", dutchNationalFlagCountingSort([...arr3]));
console.log("JS Sort:", dutchNationalFlagSort([...arr3]));
console.log("Two Pass:", dutchNationalFlagTwoPass([...arr3]));
console.log("Recursive:", dutchNationalFlagRecursive([...arr3], 0, arr3.length - 1));

console.log("\nOriginal Array 4:", arr4);
console.log("Single Pass:", dutchNationalFlagSinglePass([...arr4]));
console.log("Counting Sort:", dutchNationalFlagCountingSort([...arr4]));
console.log("JS Sort:", dutchNationalFlagSort([...arr4]));
console.log("Two Pass:", dutchNationalFlagTwoPass([...arr4]));
console.log("Recursive:", dutchNationalFlagRecursive([...arr4], 0, arr4.length - 1));

console.log("\nOriginal Array 5:", arr5);
console.log("Single Pass:", dutchNationalFlagSinglePass([...arr5]));
console.log("Counting Sort:", dutchNationalFlagCountingSort([...arr5]));
console.log("JS Sort:", dutchNationalFlagSort([...arr5]));
console.log("Two Pass:", dutchNationalFlagTwoPass([...arr5]));
console.log("Recursive:", dutchNationalFlagRecursive([...arr5], 0, arr5.length - 1));
