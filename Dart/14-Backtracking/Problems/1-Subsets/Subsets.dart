// Dart solution for generating subsets using different approaches

void main() {
  List<int> nums = [1, 2, 3];

  print('Backtracking:');
  print(subsetsBacktracking(nums));

  print('Iterative:');
  print(subsetsIterative(nums));

  print('Bit Manipulation:');
  print(subsetsBitManipulation(nums));

  print('Recursive:');
  print(subsetsRecursive(nums));

  print('Cascading:');
  print(subsetsCascading(nums));
}

// Approach 1: Backtracking
// This approach uses a recursive function to explore all possible subsets.
// It builds subsets incrementally by adding or not adding each element.
List<List<int>> subsetsBacktracking(List<int> nums) {
  List<List<int>> result = [];
  // Recursive helper function to generate subsets.
  void backtrack(int start, List<int> subset) {
    // Add a copy of the current subset to the result.
    result.add(List.from(subset));
    // Iterate through the remaining elements.
    for (int i = start; i < nums.length; i++) {
      // Add the current element to the subset.
      subset.add(nums[i]);
      // Recursively explore subsets starting from the next element.
      backtrack(i + 1, subset);
      // Remove the last element to backtrack and explore other possibilities.
      subset.removeLast();
    }
  }
  // Start the backtracking process from the beginning.
  backtrack(0, []);
  return result;
}

// Approach 2: Iterative
// This approach builds subsets iteratively by adding each element to existing subsets.
List<List<int>> subsetsIterative(List<int> nums) {
  List<List<int>> result = [[]]; // Initialize with an empty subset.
  // Iterate through each number in the input list.
  for (int num in nums) {
    int size = result.length;
    // Iterate through the existing subsets.
    for (int i = 0; i < size; i++) {
      // Create a new subset by adding the current number to each existing subset.
      result.add([...result[i], num]);
    }
  }
  return result;
}

// Approach 3: Bit Manipulation
// This approach uses bit manipulation to generate all possible subsets.
// Each bit in a binary number represents the presence or absence of an element in a subset.
List<List<int>> subsetsBitManipulation(List<int> nums) {
  int n = nums.length;
  List<List<int>> result = [];
  // Iterate through all possible binary numbers from 0 to 2^n - 1.
  for (int i = 0; i < (1 << n); i++) {
    List<int> subset = [];
    // Iterate through each bit in the current binary number.
    for (int j = 0; j < n; j++) {
      // If the j-th bit is set, add the j-th element to the subset.
      if ((i & (1 << j)) != 0) {
        subset.add(nums[j]);
      }
    }
    // Add the generated subset to the result.
    result.add(subset);
  }
  return result;
}

// Approach 4: Recursive
// This approach recursively generates subsets by considering each element and either including or excluding it.
List<List<int>> subsetsRecursive(List<int> nums) {
  // Base case: if the input list is empty, return a list containing an empty subset.
  if (nums.isEmpty) return [[]];
  // Remove the first element from the list.
  int first = nums.removeAt(0);
  // Recursively generate subsets without the first element.
  List<List<int>> withoutFirst = subsetsRecursive(List.from(nums));
  // Generate subsets with the first element by adding it to each subset without it.
  List<List<int>> withFirst = withoutFirst.map((subset) => [first, ...subset]).toList();
  // Combine the subsets with and without the first element.
  return [...withoutFirst, ...withFirst];
}

// Approach 5: Cascading
// This approach builds subsets by iteratively adding each element to all existing subsets.
List<List<int>> subsetsCascading(List<int> nums) {
  List<List<int>> result = [[]]; // Initialize with an empty subset.
  // Iterate through each number in the input list.
  for (int num in nums) {
    // For each number add it to every existing subset, and then add those new subsets to the result.
    result.addAll(result.map((subset) => [...subset, num]).toList());
  }
  return result;
}