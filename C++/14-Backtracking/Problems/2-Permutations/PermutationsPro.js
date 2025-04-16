/*
Backtracking: Permutations - 5 Approaches with Real-World Project Implementations
*/

/**
 * 1. Backtracking with Swapping (Most Common)
 *
 * -   Concept:  Recursively swap elements to generate permutations.
 * -   Real-World:  Generating test cases for software.  If you have a system that needs to be tested with various combinations of inputs, this approach can be used to create those combinations.
 *
 * -   Example:  Testing different configurations of a web server (e.g., database connections, caching settings).
 */
function permutationsSwap(arr, l, r, results = []) {
    if (l === r) {
        results.push([...arr]); // Push a copy to avoid modification issues
    } else {
        for (let i = l; i <= r; i++) {
            [arr[l], arr[i]] = [arr[i], arr[l]]; // Swap
            permutationsSwap(arr, l + 1, r, results); // Recurse
            [arr[l], arr[i]] = [arr[i], arr[l]]; // Backtrack (undo swap)
        }
    }
    return results;
}

function testPermutationsSwap() {
    const arr = [1, 2, 3];
    const results = permutationsSwap(arr, 0, arr.length - 1);
    console.log("1. Permutations (Swap):", results);
}



/**
 * 2. Backtracking with Insertion
 *
 * -   Concept:  Recursively insert elements at all possible positions in the existing permutations.
 * -   Real-World:  Generating different orderings of playlist songs.  A music player application might use this to allow users to shuffle or create custom song orders.
 *
 * -   Example:  Creating all possible play orders for a set of songs in a music app.
 */
function permutationsInsert(arr) {
    if (arr.length === 0) {
        return [[]];
    }

    const first = arr[0];
    const rest = arr.slice(1);
    const permutationsOfRest = permutationsInsert(rest);
    const result = [];

    for (const permutation of permutationsOfRest) {
        for (let i = 0; i <= permutation.length; i++) {
            const newPermutation = [...permutation.slice(0, i), first, ...permutation.slice(i)];
            result.push(newPermutation);
        }
    }
    return result;
}

function testPermutationsInsert() {
    const arr = [1, 2, 3];
    const results = permutationsInsert(arr);
    console.log("2. Permutations (Insert):", results);
}



/**
 * 3. Backtracking with Selection (Iterative)
 *
 * - Concept: Iteratively build permutations by selecting elements one by one.
 * - Real-world: Generating possible combinations for a lock code.
 *
 * - Example: Trying every possible combination for a 4-digit PIN.
 */
function permutationsSelectIterative(arr) {
  const n = arr.length;
  const result = [];
  const permutations = [[]]; // Start with an empty permutation

  for (let i = 0; i < n; i++) {
    const nextPermutations = [];
    for (const permutation of permutations) {
      for (let j = 0; j <= permutation.length; j++) {
        const newPermutation = [...permutation.slice(0, j), arr[i], ...permutation.slice(j)];
        nextPermutations.push(newPermutation);
      }
    }
    permutations.length = 0; // Clear the array,
    permutations.push(...nextPermutations);
  }
  result.push(...permutations);
  return result;
}

function testPermutationsSelectIterative() {
    const arr = [1, 2, 3];
    const results = permutationsSelectIterative(arr);
    console.log("3. Permutations (Iterative Selection):", results);
}



/**
 * 4. Backtracking with Bitmasking
 *
 * -   Concept:  Use bit manipulation to track which elements have been included in the current permutation.
 * -   Real-World:  Optimizing route planning.  Although more complex algorithms are usually used, the core idea of exploring different orderings of locations can be related to permutation generation.
 *
 * -   Example:  Finding all possible routes to visit a set of cities.  (Simplified version)
 */
function permutationsBitmask(arr) {
    const n = arr.length;
    const result = [];
    const permutations = [];
    const used = new Array(n).fill(false);

    function generatePermutation(currentPermutation) {
        if (currentPermutation.length === n) {
            result.push([...currentPermutation]);
            return;
        }

        for (let i = 0; i < n; i++) {
            if (!used[i]) {
                used[i] = true;
                currentPermutation.push(arr[i]);
                generatePermutation(currentPermutation);
                currentPermutation.pop();
                used[i] = false; // Backtrack
            }
        }
    }

    generatePermutation([]);
    return result;
}

function testPermutationsBitmask() {
    const arr = [1, 2, 3];
    const results = permutationsBitmask(arr);
    console.log("4. Permutations (Bitmask):", results);
}



/**
 * 5. Using Library Function (for comparison and convenience)
 *
 * -   Concept:  Use a library function (if available) to generate permutations.  This is often the most efficient and concise way to do it in practice.
 * -   Real-World:  Any application where you need permutations, but you don't want to write the algorithm yourself.  This could be in data analysis, scientific computing, or any kind of combinatorial problem.
 *
 * -   Example:  Generating all possible combinations for a statistical analysis.
 */
function permutationsLibrary(arr) {
  if (!arr || arr.length === 0) {
    return [[]];
  }

  const result = [];

  function permute(arr, l, r) {
    if (l === r) {
      result.push([...arr]);
    } else {
      for (let i = l; i <= r; i++) {
        [arr[l], arr[i]] = [arr[i], arr[l]];
        permute(arr, l + 1, r);
        [arr[l], arr[i]] = [arr[i], arr[l]]; // backtrack
      }
    }
  }
  permute(arr, 0, arr.length - 1);
  return result;
}


function testPermutationsLibrary() {
    const arr = [1, 2, 3];
    const results = permutationsLibrary(arr);
    console.log("5. Permutations (Library):", results);
}

// Run the tests
testPermutationsSwap();
testPermutationsInsert();
testPermutationsSelectIterative();
testPermutationsBitmask();
testPermutationsLibrary();
