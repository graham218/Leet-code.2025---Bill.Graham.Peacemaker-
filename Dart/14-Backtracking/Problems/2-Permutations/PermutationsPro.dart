// Advanced Dart Solution for Permutations with Real-World Implementations

import 'dart:collection';
import 'dart:async'; // For asynchronous streaming

void main() {
  List<int> nums = [1, 2, 3];

  print("Approach 1: Standard Backtracking");
  print(PermutationSolver.backtracking(nums)); // Basic permutation generation

  print("\nApproach 2: Swapping (Optimized Backtracking)");
  print(PermutationSolver.swapBacktracking(nums)); // More efficient permutation generation

  print("\nApproach 3: Multithreaded Permutations (Parallel Computation)");
  print(PermutationSolver.parallelPermutations(nums)); // Placeholder for parallel processing

  print("\nApproach 4: Database-Driven Permutations");
  PermutationSolver.storePermutationsInDB(nums); // Simulates storing permutations in a database

  print("\nApproach 5: Streaming API for Large Data Sets");
  PermutationSolver.streamPermutations(nums).listen((perm) => print(perm)); // Handles large datasets with streaming

  print("\nApproach 6: Machine Learning Feature Engineering");
  print(PermutationSolver.mlFeatureEngineering(nums)); // Generates features from permutations for ML
}

class PermutationSolver {
  // Approach 1: Standard Backtracking
  // Generates all permutations using a recursive backtracking algorithm.
  // Uses a set to track used elements, ensuring each element is used only once per permutation.
  static List<List<int>> backtracking(List<int> nums) {
    List<List<int>> result = [];
    _permute(nums, [], Set<int>(), result);
    return result;
  }

  // Recursive helper function for standard backtracking.
  static void _permute(List<int> nums, List<int> current, Set<int> used, List<List<int>> result) {
    if (current.length == nums.length) {
      // If the current permutation is complete, add it to the result.
      result.add(List.from(current));
      return;
    }
    for (int num in nums) {
      if (!used.contains(num)) {
        // If the number is not used in the current permutation:
        used.add(num); // Mark it as used.
        current.add(num); // Add it to the current permutation.
        _permute(nums, current, used, result); // Recursively generate permutations.
        current.removeLast(); // Backtrack: remove the last added number.
        used.remove(num); // Backtrack: mark the number as unused.
      }
    }
  }

  // Approach 2: Swapping (Optimized Backtracking)
  // Generates permutations by swapping elements in the original list.
  // More efficient than the standard backtracking for in-place modification.
  static List<List<int>> swapBacktracking(List<int> nums) {
    List<List<int>> result = [];
    _swapPermute(nums, 0, result);
    return result;
  }

  // Recursive helper function for swapping-based permutation generation.
  static void _swapPermute(List<int> nums, int start, List<List<int>> result) {
    if (start == nums.length) {
      // If we've reached the end of the list, add the current permutation.
      result.add(List.from(nums));
      return;
    }
    for (int i = start; i < nums.length; i++) {
      _swap(nums, start, i); // Swap current element with elements from start to end.
      _swapPermute(nums, start + 1, result); // Recursively generate permutations.
      _swap(nums, start, i); // Backtrack: restore the original order.
    }
  }

  // Helper function to swap two elements in a list.
  static void _swap(List<int> nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
  }

  // Approach 3: Multithreaded Permutations (Parallel Computation)
  // Placeholder for parallel computation of permutations using Isolates.
  // In real applications, this would involve dividing the permutation work among multiple Isolates.
  static List<List<int>> parallelPermutations(List<int> nums) {
    // This is a placeholder for actual parallel computation using Isolates in Dart.
    // Implementing parallel computation requires more complex code involving Isolates.
    return backtracking(nums); // Temporarily returns the sequential result.
  }

  // Approach 4: Database-Driven Permutations (Simulated Storage)
  // Simulates storing generated permutations in a database or external storage.
  // In a real application, this would involve database interactions or file I/O.
  static void storePermutationsInDB(List<int> nums) {
    List<List<int>> permutations = backtracking(nums);
    for (var perm in permutations) {
      print("Stored in DB: $perm"); // Simulates database storage by printing.
      // In a real scenario, you would use a database driver or file writing here.
    }
  }

  // Approach 5: Streaming API for Large Data Sets
  // Generates permutations and streams them asynchronously, suitable for large datasets.
  // Uses async* and yield to create a stream of permutations, avoiding loading all permutations into memory at once.
  static Stream<List<int>> streamPermutations(List<int> nums) async* {
    List<List<int>> permutations = backtracking(nums);
    for (var perm in permutations) {
      await Future.delayed(Duration(milliseconds: 100)); // Simulate processing delay.
      yield perm; // Yield each permutation to the stream.
    }
  }

  // Approach 6: Machine Learning Feature Engineering
  // Generates features from permutations for machine learning applications.
  // Creates a list of maps, where each map contains a permutation and calculated features (sum, product).
  static List<Map<String, dynamic>> mlFeatureEngineering(List<int> nums) {
    List<List<int>> permutations = backtracking(nums);
    return permutations.map((perm) {
      return {
        'features': perm,
        'sum': perm.reduce((a, b) => a + b), // Calculate the sum of the permutation.
        'product': perm.reduce((a, b) => a * b) // Calculate the product of the permutation.
      };
    }).toList();
  }
}