/*
Backtracking: Permutations

Given an array of distinct integers, return all possible permutations.

Example:
Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
*/

/**
 * Approach 1: Recursive with Swapping
 * - Time Complexity: O(n!)
 * - Space Complexity: O(n) - due to the recursion depth
 */
function permute1(nums) {
  const result = [];

  function permuteHelper(arr, l, r) {
    if (l === r) {
      result.push([...arr]); // Push a copy to avoid modification
      return;
    }

    for (let i = l; i <= r; i++) {
      [arr[l], arr[i]] = [arr[i], arr[l]]; // Swap
      permuteHelper(arr, l + 1, r);
      [arr[l], arr[i]] = [arr[i], arr[l]]; // Backtrack (swap back)
    }
  }

  permuteHelper(nums, 0, nums.length - 1);
  return result;
}

/**
 * Approach 2: Recursive with Choosing
 * - Time Complexity: O(n!)
 * - Space Complexity: O(n^2) -  O(n) for recursion, O(n) for the chosen array
 */
function permute2(nums) {
  const result = [];

  function permuteHelper(arr, chosen) {
    if (arr.length === 0) {
      result.push(chosen);
      return;
    }

    for (let i = 0; i < arr.length; i++) {
      const num = arr[i];
      const remaining = arr.slice(0, i).concat(arr.slice(i + 1));
      permuteHelper(remaining, chosen.concat([num]));
    }
  }

  permuteHelper(nums, []);
  return result;
}

/**
 * Approach 3: Iterative with Insertion
 * - Time Complexity: O(n!)
 * - Space Complexity: O(n!) -  due to the number of permutations stored.
 */
function permute3(nums) {
  const result = [];
  if (nums.length === 0) return [[]]; // Base case: empty array

  result.push([nums[0]]); // Start with the first element

  for (let i = 1; i < nums.length; i++) {
    const num = nums[i];
    const prevPermutations = result.slice(); // Important: Iterate over a copy
    result.length = 0; // Clear the result array

    for (const permutation of prevPermutations) {
      for (let j = 0; j <= permutation.length; j++) {
        const newPermutation = [...permutation.slice(0, j), num, ...permutation.slice(j)];
        result.push(newPermutation);
      }
    }
  }
  return result;
}

/**
 * Approach 4: Using a Generator (ES6)
 * - Time Complexity: O(n!) - conceptually
 * - Space Complexity: O(n) -  due to recursion depth in generator
 */
function* permute4Generator(arr, l, r) {
    if (l === r) {
        yield [...arr];
        return;
    }
    for (let i = l; i <= r; i++) {
        [arr[l], arr[i]] = [arr[i], arr[l]];
        yield* permute4Generator(arr, l + 1, r);
        [arr[l], arr[i]] = [arr[i], arr[l]];
    }
}

function permute4(nums) {
    const result = [];
    for (const p of permute4Generator(nums, 0, nums.length - 1)) {
        result.push(p);
    }
    return result;
}


/**
 * Approach 5: Using reduce
 * - Time Complexity: O(n!)
 * - Space Complexity: O(n!)
 */
function permute5(nums) {
  if (!nums.length) return [[]];

  return nums.reduce((perms, item, index) => {
    const rest = nums.slice(0, index).concat(nums.slice(index + 1));
    const nextPerms = permute5(rest);
    const newPerms = nextPerms.map(p => [item, ...p]);
    return perms.concat(newPerms);
  }, []);
}



// Example usage:
const input = [1, 2, 3];

console.log("Input:", input);
console.log("\nApproach 1: Recursive with Swapping");
console.log(permute1(input));

console.log("\nApproach 2: Recursive with Choosing");
console.log(permute2(input));

console.log("\nApproach 3: Iterative with Insertion");
console.log(permute3(input));

console.log("\nApproach 4: Using a Generator (ES6)");
console.log(permute4(input));

console.log("\nApproach 5: Using reduce");
console.log(permute5(input));
