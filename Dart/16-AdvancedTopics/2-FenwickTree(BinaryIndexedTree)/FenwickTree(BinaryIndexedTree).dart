import 'dart:math';

void main() {
  // Example usage for all implementations
  List<int> initialArray = [1, 3, 4, 8, 6, 1, 4, 2];
  int n = initialArray.length;

  // Approach 1: Using a class
  FenwickTreeClass tree1 = FenwickTreeClass(n);
  for (int i = 0; i < n; i++) {
    tree1.update(i, initialArray[i]);
  }
  print("Approach 1 - Class:");
  print("Sum of first 5 elements: ${tree1.query(4)}"); // Sum of elements from index 0 to 4
  tree1.update(3, 6); // Update element at index 3
  print("Sum of first 5 elements after update: ${tree1.query(4)}");
  print("Original Array: $initialArray");
  print("Tree: ${tree1.tree}");


  // Approach 2: Using functions
  List<int> tree2 = List.filled(n + 1, 0);
  for (int i = 0; i < n; i++) {
    updateFunc(tree2, i, initialArray[i]);
  }
  print("\nApproach 2 - Functions:");
  print("Sum of first 5 elements: ${queryFunc(tree2, 4)}");
  updateFunc(tree2, 3, 6);
  print("Sum of first 5 elements after update: ${queryFunc(tree2, 4)}");
  print("Original Array: $initialArray");
  print("Tree: $tree2");

  // Approach 3:  Optimized using bitwise operations and in-place array modification
  List<int> tree3 = List.filled(n + 1, 0);
  for (int i = 0; i < n; i++) {
    updateOptimized(tree3, i, initialArray[i]);
  }
  print("\nApproach 3 - Optimized:");
  print("Sum of first 5 elements: ${queryOptimized(tree3, 4)}");
  updateOptimized(tree3, 3, 6);
  print("Sum of first 5 elements after update: ${queryOptimized(tree3, 4)}");
  print("Original Array: $initialArray");
  print("Tree: $tree3");

  // Approach 4:  Fenwick Tree for Range Sum AND Point Updates
  FenwickTreeRange tree4 = FenwickTreeRange(initialArray);
  print("\nApproach 4 - Range Sum and Point Updates:");
  print("Sum of elements from index 1 to 5: ${tree4.rangeSum(1, 5)}"); // Sum from index 1 to 5 (inclusive)
  tree4.update(3, 10); // Update the element at index 3 to 10
  print("Sum of elements from index 1 to 5 after update: ${tree4.rangeSum(1, 5)}");
  print("Original Array: $initialArray");
  print("Tree: ${tree4.tree}");

  // Approach 5: Using Extension Methods
  List<int> tree5 = List.filled(n + 1, 0);
  for (int i = 0; i < n; i++) {
    tree5.updateExtension(i, initialArray[i]);
  }
  print("\nApproach 5 - Extension Methods:");
  print("Sum of first 5 elements: ${tree5.queryExtension(4)}");
  tree5.updateExtension(3, 6);
  print("Sum of first 5 elements after update: ${tree5.queryExtension(4)}");
  print("Original Array: $initialArray");
  print("Tree: $tree5");
}

// Approach 1: Using a class
class FenwickTreeClass {
  late List<int> tree;
  int n;

  FenwickTreeClass(this.n) {
    tree = List.filled(n + 1, 0);
  }

  void update(int index, int value) {
    index++; // Fenwick tree is 1-indexed
    while (index <= n) {
      tree[index] += value;
      index += (index & -index);
    }
  }

  int query(int index) {
    index++; // Fenwick tree is 1-indexed
    int sum = 0;
    while (index > 0) {
      sum += tree[index];
      index -= (index & -index);
    }
    return sum;
  }
}

// Approach 2: Using functions
void updateFunc(List<int> tree, int index, int value) {
  int n = tree.length - 1;
  index++;
  while (index <= n) {
    tree[index] += value;
    index += (index & -index);
  }
}

int queryFunc(List<int> tree, int index) {
  index++;
  int sum = 0;
  while (index > 0) {
    sum += tree[index];
    index -= (index & -index);
  }
  return sum;
}

// Approach 3: Optimized using bitwise operations and in-place array modification
void updateOptimized(List<int> tree, int index, int value) {
  int n = tree.length - 1;
  index++; // 1-based indexing for Fenwick Tree
  while (index <= n) {
    tree[index] += value;
    index += (index & -index); // Get the least significant bit and add it
  }
}

int queryOptimized(List<int> tree, int index) {
  index++; // 1-based indexing for Fenwick Tree
  int sum = 0;
  while (index > 0) {
    sum += tree[index];
    index -= (index & -index); // Get the least significant bit and subtract it
  }
  return sum;
}

// Approach 4: Fenwick Tree for Range Sum and Point Updates
class FenwickTreeRange {
  late List<int> tree;
  int n;
  late List<int> originalArray; // Keep a copy for range sum queries

  FenwickTreeRange(List<int> initialArray) : n = initialArray.length {
    // n = initialArray.length;  // Initialize n here.
    tree = List.filled(n + 1, 0);
    originalArray = List.from(initialArray); // Copy the original array
    for (int i = 0; i < n; i++) {
      update(i, initialArray[i]);
    }
  }

  void update(int index, int value) {
    int diff = value - originalArray[index];  // Calculate the difference
    originalArray[index] = value; //update the original array
    index++;
    while (index <= n) {
      tree[index] += diff;
      index += (index & -index);
    }
  }

  int query(int index) {
    index++;
    int sum = 0;
    while (index > 0) {
      sum += tree[index];
      index -= (index & -index);
    }
    return sum;
  }

  // Range sum query [left, right] (inclusive)
  int rangeSum(int left, int right) {
    return query(right) - query(left - 1);
  }
}

// Approach 5: Using Extension Methods
extension FenwickTreeExtension on List<int> {
  void updateExtension(int index, int value) {
    int n = this.length - 1;
    index++;
    while (index <= n) {
      this[index] += value;
      index += (index & -index);
    }
  }

  int queryExtension(int index) {
    index++;
    int sum = 0;
    while (index > 0) {
      sum += this[index];
      index -= (index & -index);
    }
    return sum;
  }
}
