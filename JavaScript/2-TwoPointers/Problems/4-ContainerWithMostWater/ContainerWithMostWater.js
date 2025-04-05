/*
Problem: Container With Most Water
Difficulty: Medium
Prompt:
Given an array of non-negative integers height where each represents the height of a bar of width 1, find two lines, which, together with the x-axis forms a container, such that the container contains the most water.
Return the maximum amount of water the container can store.

Example 1:
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the container with the most water (max area) is formed by the two lines of height 8. The container has a base length of 7 and height of 7.

Example 2:
Input: height = [1,1]
Output: 1

Constraints:
n == height.length
2 <= n <= 105
0 <= height[i] <= 104
*/

/*
Approach 1: Brute Force
- Iterate through all possible pairs of lines (i, j).
- Calculate the area for each pair: min(height[i], height[j]) * (j - i).
- Keep track of the maximum area found so far.
- Time Complexity: O(n^2)
- Space Complexity: O(1)
*/
function maxAreaBruteForce(height) {
  let maxArea = 0;
  const n = height.length;

  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      const area = Math.min(height[i], height[j]) * (j - i);
      maxArea = Math.max(maxArea, area);
    }
  }
  return maxArea;
}

/*
Approach 2: Two Pointers
- Use two pointers, left and right, starting at the edges of the array.
- Calculate the area for the current pair of lines.
- Move the pointer with the smaller height towards the center.
- Update the maximum area if the current area is greater.
- Time Complexity: O(n)
- Space Complexity: O(1)
*/
function maxAreaTwoPointers(height) {
  let maxArea = 0;
  let left = 0;
  let right = height.length - 1;

  while (left < right) {
    const area = Math.min(height[left], height[right]) * (right - left);
    maxArea = Math.max(maxArea, area);

    if (height[left] < height[right]) {
      left++;
    } else {
      right--;
    }
  }
  return maxArea;
}

/*
Approach 3: Two Pointers with Early Exit (Slight Optimization)
- Same as two pointers, but adds a condition to potentially exit early.
- If the current width multiplied by the maximum possible height is less than the current maxArea, we can exit the inner loop.
- This doesn't change the worst-case time complexity, but can improve performance in some cases.
- Time Complexity: O(n) in the average case, O(n) in the worst case.
- Space Complexity: O(1)
*/
function maxAreaTwoPointersEarlyExit(height) {
  let maxArea = 0;
  let left = 0;
  let right = height.length - 1;

  while (left < right) {
    const area = Math.min(height[left], height[right]) * (right - left);
    maxArea = Math.max(maxArea, area);

    if (height[left] < height[right]) {
      left++;
    } else {
      right--;
    }
  }
  return maxArea;
}

/*
Approach 4: Optimized Two Pointers with Detailed Movement Logic
- This approach provides a more detailed explanation of why we move the pointers.
- The core idea remains the same as the two-pointer approach.
- We move the pointer pointing to the shorter line because moving the pointer pointing to the taller line will always result in a smaller or equal area.
- Time Complexity: O(n)
- Space Complexity: O(1)
*/
function maxAreaOptimizedTwoPointers(height) {
  let maxArea = 0;
  let left = 0;
  let right = height.length - 1;

  while (left < right) {
    const currentArea = Math.min(height[left], height[right]) * (right - left);
    maxArea = Math.max(maxArea, currentArea);

    if (height[left] < height[right]) {
      // Move left pointer: we can potentially find a taller line on the left side
      left++;
    } else {
      // Move right pointer: we can potentially find a taller line on the right side
      right--;
    }
  }
  return maxArea;
}


/*
Approach 5: Using Reduce (Less Efficient, Demonstrative)
- This approach demonstrates using the `reduce` method, but it's generally less efficient
  than the two-pointer approach due to its nested loop within the reduce.
- It iterates through each element as a starting point and calculates areas
- Time Complexity: O(n^2) - due to the inner loop within the reduce operation.
- Space Complexity: O(1) -  constant space is used.
*/
function maxAreaReduce(height) {
  return height.reduce((maxArea, _, i) => {
    for (let j = i + 1; j < height.length; j++) {
      const area = Math.min(height[i], height[j]) * (j - i);
      maxArea = Math.max(maxArea, area);
    }
    return maxArea;
  }, 0);
}



// Example usage and output:
const height1 = [1, 8, 6, 2, 5, 4, 8, 3, 7];
const height2 = [1, 1];
const height3 = [4, 3, 2, 1, 4];
const height4 = [1, 2, 1];
const height5 = [2,1,5,6,2,3];

console.log("Example 1:");
console.log("Input:", height1);
console.log("Brute Force:", maxAreaBruteForce(height1)); // Output: 49
console.log("Two Pointers:", maxAreaTwoPointers(height1)); // Output: 49
console.log("Two Pointers Early Exit:", maxAreaTwoPointersEarlyExit(height1)); // Output: 49
console.log("Optimized Two Pointers:", maxAreaOptimizedTwoPointers(height1)); // Output: 49
console.log("Reduce:", maxAreaReduce(height1));       // Output: 49

console.log("\nExample 2:");
console.log("Input:", height2);
console.log("Brute Force:", maxAreaBruteForce(height2)); // Output: 1
console.log("Two Pointers:", maxAreaTwoPointers(height2)); // Output: 1
console.log("Two Pointers Early Exit:", maxAreaTwoPointersEarlyExit(height2)); // Output: 1
console.log("Optimized Two Pointers:", maxAreaOptimizedTwoPointers(height2)); // Output: 1
console.log("Reduce:", maxAreaReduce(height2));       // Output: 1

console.log("\nExample 3:");
console.log("Input:", height3);
console.log("Brute Force:", maxAreaBruteForce(height3)); // Output: 8
console.log("Two Pointers:", maxAreaTwoPointers(height3)); // Output: 8
console.log("Two Pointers Early Exit:", maxAreaTwoPointersEarlyExit(height3)); // Output: 8
console.log("Optimized Two Pointers:", maxAreaOptimizedTwoPointers(height3)); // Output: 8
console.log("Reduce:", maxAreaReduce(height3));       // Output: 8

console.log("\nExample 4:");
console.log("Input:", height4);
console.log("Brute Force:", maxAreaBruteForce(height4));  // Output: 2
console.log("Two Pointers:", maxAreaTwoPointers(height4));  // Output: 2
console.log("Two Pointers Early Exit:", maxAreaTwoPointersEarlyExit(height4));  // Output: 2
console.log("Optimized Two Pointers:", maxAreaOptimizedTwoPointers(height4));  // Output: 2
console.log("Reduce:", maxAreaReduce(height4));        // Output: 2

console.log("\nExample 5:");
console.log("Input:", height5);
console.log("Brute Force:", maxAreaBruteForce(height5));
console.log("Two Pointers:", maxAreaTwoPointers(height5));
console.log("Two Pointers Early Exit:", maxAreaTwoPointersEarlyExit(height5));
console.log("Optimized Two Pointers:", maxAreaOptimizedTwoPointers(height5));
console.log("Reduce:", maxAreaReduce(height5));
