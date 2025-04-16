/*
Dutch National Flag Algorithm (3-way partitioning)

Problem:
Given an array containing elements representing colors (0, 1, and 2), sort the array
in-place such that elements of the same color are adjacent, with the colors in the
order 0, 1, and 2.  This is analogous to sorting the colors of the Dutch
National Flag: red (0), white (1), and blue (2).

Constraints:
- The input array contains only the integers 0, 1, and 2.
- The sorting should be done in-place.
- The solution should be efficient (linear time complexity).

Example:
Input:  [2, 0, 2, 1, 1, 0]
Output: [0, 0, 1, 1, 2, 2]
*/

/**
 * Approach 1:  Using Three Pointers (Low, Mid, High)
 *
 * This is the classic and most efficient solution.  It uses three pointers:
 * - low:  Points to the beginning of the 0s section.
 * - mid:  Points to the current element being processed.
 * - high: Points to the end of the 2s section.
 *
 * The algorithm iterates through the array using the mid pointer and swaps
 * elements as needed to partition the array.
 *
 * Time Complexity:  O(n) - Linear, as it iterates through the array once.
 * Space Complexity: O(1) - Constant, as it uses only a few extra variables.
 */
function dutchNationalFlag1(arr) {
  let low = 0;
  let mid = 0;
  let high = arr.length - 1;

  while (mid <= high) {
    if (arr[mid] === 0) {
      // Swap arr[low] and arr[mid], and increment both low and mid.
      [arr[low], arr[mid]] = [arr[mid], arr[low]];
      low++;
      mid++;
    } else if (arr[mid] === 1) {
      // Increment mid only.
      mid++;
    } else {
      // Swap arr[mid] and arr[high], and decrement high.
      [arr[mid], arr[high]] = [arr[high], arr[mid]];
      high--;
      // Note: mid does not increment here because the swapped element
      // from high could be a 0, 1, or 2, and needs to be processed.
    }
  }
  return arr;
}

/**
 * Approach 2: Counting Sort (Not in-place)
 *
 * This approach counts the occurrences of 0, 1, and 2, and then overwrites the
 * original array with the sorted values.  While simple, it's not in-place.
 *
 * Time Complexity:  O(n) - Linear, as it iterates through the array twice.
 * Space Complexity: O(1) - Constant, as it uses a fixed number of counters.
 */
function dutchNationalFlag2(arr) {
  let count0 = 0;
  let count1 = 0;
  let count2 = 0;

  // Count the occurrences of each color.
  for (let i = 0; i < arr.length; i++) {
    if (arr[i] === 0) {
      count0++;
    } else if (arr[i] === 1) {
      count1++;
    } else {
      count2++;
    }
  }

  // Overwrite the array with the sorted colors.
  let index = 0;
  for (let i = 0; i < count0; i++) {
    arr[index++] = 0;
  }
  for (let i = 0; i < count1; i++) {
    arr[index++] = 1;
  }
  for (let i = 0; i < count2; i++) {
    arr[index++] = 2;
  }
  return arr;
}

/**
 * Approach 3: Using Array.prototype.sort (Incorrect for this specific problem)
 *
 * This approach uses the built-in `sort` method.  However, it's crucial to
 * provide a comparison function to ensure correct sorting of numbers.
 * If no comparison function is provided, the array elements are converted
 * to strings and sorted lexicographically, which would lead to an incorrect
 * result for this problem (e.g., [1, 2, 10] would be sorted as [1, 10, 2]).
 *
 * Time Complexity: O(n log n) - Typically, for most JavaScript implementations
 * Space Complexity: O(1) or O(n) - Depends on the implementation of the
 * sorting algorithm in the JavaScript engine.
 */
function dutchNationalFlag3(arr) {
  // Correctly sort the array using a comparison function.
  arr.sort((a, b) => a - b); // Sorts numerically
  return arr;
}

/**
 * Approach 4:  Single Pass, Two Pointers (Similar to Approach 1, but slightly different structure)
 *
 * This approach is also a single-pass, in-place solution, but it uses only two pointers.
 * It maintains the invariant that elements before `low` are 0s, and elements after
 * `high` are 2s.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
function dutchNationalFlag4(arr) {
    let low = 0;
    let high = arr.length - 1;
    let i = 0;

    while (i <= high) {
        if (arr[i] === 0) {
            [arr[i], arr[low]] = [arr[low], arr[i]];
            low++;
            i++;
        } else if (arr[i] === 2) {
            [arr[i], arr[high]] = [arr[high], arr[i]];
            high--;
            // i does not increment here, because we swapped with an unknown value from the right
        } else { // arr[i] === 1
            i++;
        }
    }
    return arr;
}

/**
 * Approach 5: Using filter and concat (Not in-place)
 *
 * This approach uses the filter method to create three separate arrays for 0s, 1s, and 2s.
 * Then, it concatenates the three arrays. This is not an in-place solution and
 * has a higher space complexity.
 *
 * Time Complexity: O(n) - Due to the filter and concat operations.
 * Space Complexity: O(n) -  Extra space is used to store the filtered arrays.
 */
function dutchNationalFlag5(arr) {
  const zeros = arr.filter(num => num === 0);
  const ones = arr.filter(num => num === 1);
  const twos = arr.filter(num => num === 2);
  return zeros.concat(ones, twos);
}



// Example Usage and Output:
const array = [2, 0, 2, 1, 1, 0, 2, 1, 0];

console.log("Original Array:", array);
console.log("Approach 1 (Three Pointers):", dutchNationalFlag1([...array])); // [0, 0, 0, 1, 1, 1, 2, 2, 2]
console.log("Approach 2 (Counting Sort):", dutchNationalFlag2([...array])); // [0, 0, 0, 1, 1, 1, 2, 2, 2]
console.log("Approach 3 (Array.sort):", dutchNationalFlag3([...array]));     // [0, 0, 0, 1, 1, 1, 2, 2, 2]
console.log("Approach 4 (Two Pointers):", dutchNationalFlag4([...array]));     // [0, 0, 0, 1, 1, 1, 2, 2, 2]
console.log("Approach 5 (Filter & Concat):", dutchNationalFlag5([...array])); // [0, 0, 0, 1, 1, 1, 2, 2, 2]

