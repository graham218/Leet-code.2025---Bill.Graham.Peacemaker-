import 'dart:math';

void main() {
  List<int> nums = [1, 2, 3, 4];
  print(productExceptSelfBruteForce(nums)); // Output: [24, 12, 8, 6]
  print(productExceptSelfPrefixSuffix(nums)); // Output: [24, 12, 8, 6]
  print(productExceptSelfOptimized(nums)); // Output: [24, 12, 8, 6]
  print(productExceptSelfLogarithm(nums)); // Output: [24, 12, 8, 6]
  print(productExceptSelfFunctional(nums)); // Output: [24, 12, 8, 6]
}

// Approach 1: Brute Force
// Time Complexity: O(n^2), Space Complexity: O(1)
List<int> productExceptSelfBruteForce(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, 1);

  for (int i = 0; i < n; i++) {
    int product = 1;
    for (int j = 0; j < n; j++) {
      if (i != j) {
        product *= nums[j];
      }
    }
    result[i] = product;
  }
  return result;
}

// Approach 2: Prefix and Suffix Products
// Time Complexity: O(n), Space Complexity: O(n)
List<int> productExceptSelfPrefixSuffix(List<int> nums) {
  int n = nums.length;
  List<int> left = List.filled(n, 1);
  List<int> right = List.filled(n, 1);
  List<int> result = List.filled(n, 1);

  for (int i = 1; i < n; i++) {
    left[i] = left[i - 1] * nums[i - 1];
  }

  for (int i = n - 2; i >= 0; i--) {
    right[i] = right[i + 1] * nums[i + 1];
  }

  for (int i = 0; i < n; i++) {
    result[i] = left[i] * right[i];
  }
  return result;
}

// Approach 3: Optimized Space (Using result array)
// Time Complexity: O(n), Space Complexity: O(1)
List<int> productExceptSelfOptimized(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, 1);

  int leftProduct = 1;
  for (int i = 0; i < n; i++) {
    result[i] = leftProduct;
    leftProduct *= nums[i];
  }

  int rightProduct = 1;
  for (int i = n - 1; i >= 0; i--) {
    result[i] *= rightProduct;
    rightProduct *= nums[i];
  }

  return result;
}

// Approach 4: Logarithmic Properties (Handles zero cases separately)
// Time Complexity: O(n), Space Complexity: O(1)
List<int> productExceptSelfLogarithm(List<int> nums) {
  int n = nums.length;
  double logSum = 0;
  int zeroCount = nums.where((num) => num == 0).length;

  if (zeroCount > 1) return List.filled(n, 0);

  for (int num in nums) {
    if (num != 0) logSum += log(num.abs());
  }

  return nums.map((num) {
    if (num == 0) return exp(logSum).toInt();
    return (exp(logSum - log(num.abs())) * (num < 0 ? -1 : 1)).toInt();
  }).toList();
}

// Approach 5: Functional Programming (Using Dart's fold and map)
// Time Complexity: O(n), Space Complexity: O(n)
List<int> productExceptSelfFunctional(List<int> nums) {
  int totalProduct = nums.fold(1, (a, b) => a * (b == 0 ? 1 : b));
  int zeroCount = nums.where((num) => num == 0).length;

  return nums.map((num) {
    if (zeroCount > 1) return 0;
    if (zeroCount == 1) return num == 0 ? totalProduct : 0;
    return totalProduct ~/ num;
  }).toList();
}
