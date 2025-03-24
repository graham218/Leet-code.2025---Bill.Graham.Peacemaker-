// Dart Solution for generating permutations using Backtracking

void main() {
  List<int> nums = [1, 2, 3];

  print("Approach 1: Backtracking (Recursive DFS)");
  print(permutations(nums));

  print("\nApproach 2: Backtracking using Swaps");
  print(permutationsSwap(nums));

  print("\nApproach 3: Iterative using Insertion");
  print(permutationsInsert(nums));

  print("\nApproach 4: Heap's Algorithm (Recursive)");
  print(permutationsHeap(nums));

  print("\nApproach 5: Lexicographic Order (Next Permutation)");
  print(permutationsLexicographic(nums));
}

// Approach 1: Backtracking (Recursive DFS)
// This approach uses recursive depth-first search (DFS) to explore all possible permutations.
// It maintains a 'used' set to track which numbers have been included in the current permutation.
List<List<int>> permutations(List<int> nums) {
  List<List<int>> result = [];
  _backtrack(nums, [], result, Set<int>());
  return result;
}

// Recursive helper function for backtracking.
void _backtrack(List<int> nums, List<int> temp, List<List<int>> result, Set<int> used) {
  // If the temporary list 'temp' has the same length as the input 'nums', a complete permutation is found.
  if (temp.length == nums.length) {
    result.add(List.from(temp)); // Add a copy of the permutation to the result list.
    return;
  }
  // Iterate through each number in the input list.
  for (int num in nums) {
    // If the number has not been used in the current permutation.
    if (!used.contains(num)) {
      used.add(num); // Mark the number as used.
      temp.add(num); // Add the number to the current permutation.
      _backtrack(nums, temp, result, used); // Recursively call backtrack to explore further permutations.
      temp.removeLast(); // Remove the last added number to backtrack.
      used.remove(num); // Mark the number as unused.
    }
  }
}

// Approach 2: Backtracking using Swaps
// This approach generates permutations by swapping elements in the input list.
// It recursively calls itself to explore different swap combinations.
List<List<int>> permutationsSwap(List<int> nums) {
  List<List<int>> result = [];
  _permuteSwap(nums, 0, result);
  return result;
}

// Recursive helper function for permutation generation using swaps.
void _permuteSwap(List<int> nums, int start, List<List<int>> result) {
  // If 'start' reaches the end of the list, a complete permutation is found.
  if (start == nums.length) {
    result.add(List.from(nums)); // Add a copy of the permutation to the result list.
    return;
  }
  // Iterate through the remaining elements in the list.
  for (int i = start; i < nums.length; i++) {
    _swap(nums, start, i); // Swap the current element with the element at 'start'.
    _permuteSwap(nums, start + 1, result); // Recursively call permuteSwap to explore further permutations.
    _swap(nums, start, i); // Swap back to restore the original order for backtracking.
  }
}

// Helper function to swap two elements in a list.
void _swap(List<int> nums, int i, int j) {
  int temp = nums[i];
  nums[i] = nums[j];
  nums[j] = temp;
}

// Approach 3: Iterative using Insertion
// This approach iteratively generates permutations by inserting each number into all possible positions of the existing permutations.
List<List<int>> permutationsInsert(List<int> nums) {
  List<List<int>> result = [[]]; // Initialize with an empty list.
  for (int num in nums) {
    List<List<int>> newPerms = []; // List to store new permutations.
    for (List<int> perm in result) {
      for (int i = 0; i <= perm.length; i++) {
        List<int> newPerm = List.from(perm)..insert(i, num); // Insert the number at each possible position.
        newPerms.add(newPerm); // Add the new permutation to the list.
      }
    }
    result = newPerms; // Update the result list with the new permutations.
  }
  return result;
}

// Approach 4: Heap's Algorithm (Recursive)
// Heap's algorithm is a recursive algorithm for generating all permutations of a finite set.
// It minimizes swaps.
List<List<int>> permutationsHeap(List<int> nums) {
  List<List<int>> result = [];
  _heapPermute(nums, nums.length, result);
  return result;
}

// Recursive helper function for Heap's algorithm.
void _heapPermute(List<int> nums, int n, List<List<int>> result) {
  if (n == 1) {
    result.add(List.from(nums)); // Add a copy of the permutation to the result list.
    return;
  }
  for (int i = 0; i < n; i++) {
    _heapPermute(nums, n - 1, result); // Recursively call heapPermute to explore further permutations.
    _swap(nums, n % 2 == 0 ? i : 0, n - 1); // Swap elements based on Heap's algorithm logic.
  }
}

// Approach 5: Lexicographic Order (Next Permutation)
// This approach generates permutations in lexicographic order using the next permutation algorithm.
List<List<int>> permutationsLexicographic(List<int> nums) {
  nums.sort(); // Sort the input list to start with the smallest permutation.
  List<List<int>> result = [];
  do {
    result.add(List.from(nums)); // Add a copy of the current permutation to the result list.
  } while (_nextPermutation(nums)); // Continue until no more next permutations exist.
  return result;
}

// Helper function to find the next permutation in lexicographic order.
bool _nextPermutation(List<int> nums) {
  int i = nums.length - 2;
  // Find the largest index i such that nums[i] < nums[i + 1].
  while (i >= 0 && nums[i] >= nums[i + 1]) i--;
  if (i < 0) return false; // No more next permutations exist.
  int j = nums.length - 1;
  // Find the largest index j such that nums[j] > nums[i].
  while (nums[j] <= nums[i]) j--;
  _swap(nums, i, j); // Swap nums[i] and nums[j].
  // Reverse the subarray from nums[i + 1] to the end of the list.
  nums.setRange(i + 1, nums.length, nums.sublist(i + 1).reversed);
  return true; // Next permutation found.
}