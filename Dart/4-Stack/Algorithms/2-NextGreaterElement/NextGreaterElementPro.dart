/// Finds the next greater element for each element in a list.
///
/// This implementation provides multiple approaches, each with different
/// time and space complexities, suitable for various use cases.
///
/// main Function
void main() {
  List<int> nums = [4, 5, 2, 10, 8];
  print('Original List: $nums');
  print('Next Greater Element (Stack): ${nextGreaterElementStack(nums)}');
  print('Next Greater Element (Brute Force): ${nextGreaterElementBruteForce(nums)}');
  print('Next Greater Element (Circular): ${nextGreaterElementCircular(nums)}');
  print('Next Greater Element (HashMap): ${nextGreaterElementWithMap(nums)}');
  print('Next Greater Element (Two Pass): ${nextGreaterElementTwoPass(nums)}');
}

/// **Approach 1: Monotonic Stack (Optimized)**
///
/// Finds the next greater element using a monotonic stack.
///
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> nextGreaterElementStack(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, -1);
  List<int> stack = [];

  for (int i = 0; i < n; i++) {
    while (stack.isNotEmpty && nums[i] > nums[stack.last]) {
      int index = stack.removeLast();
      result[index] = nums[i];
    }
    stack.add(i);
  }
  return result;
}

/// **Approach 2: Brute Force (Naive)**
///
/// Finds the next greater element using nested loops.
///
/// Time Complexity: O(n^2)
/// Space Complexity: O(1)
List<int> nextGreaterElementBruteForce(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, -1);

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (nums[j] > nums[i]) {
        result[i] = nums[j];
        break;
      }
    }
  }
  return result;
}

/// **Approach 3: Circular Array (Monotonic Stack)**
///
/// Finds the next greater element in a circular array.
///
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> nextGreaterElementCircular(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, -1);
  List<int> stack = [];

  for (int i = 0; i < 2 * n; i++) {
    while (stack.isNotEmpty && nums[i % n] > nums[stack.last]) {
      int index = stack.removeLast();
      result[index] = nums[i % n];
    }
    if (i < n) {
      stack.add(i);
    }
  }
  return result;
}

/// **Approach 4: HashMap (Efficient)**
///
/// Finds the next greater element using a HashMap and monotonic stack.
///
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> nextGreaterElementWithMap(List<int> nums) {
  int n = nums.length;
  Map<int, int> ngeMap = {};
  List<int> stack = [];

  for (int num in nums.reversed) {
    while (stack.isNotEmpty && stack.last <= num) {
      stack.removeLast();
    }
    ngeMap[num] = stack.isNotEmpty ? stack.last : -1;
    stack.add(num);
  }
  return nums.map((num) => ngeMap[num]!).toList();
}

/// **Approach 5: Two-Pass Traversal (Optimized)**
///
/// Finds the next greater element using a two-pass traversal.
///
/// Time Complexity: O(n)
/// Space Complexity: O(n)
List<int> nextGreaterElementTwoPass(List<int> nums) {
  int n = nums.length;
  List<int> result = List.filled(n, -1);
  List<int> rightMax = List.filled(n, -1);

  for (int i = n - 2; i >= 0; i--) {
    int j = i + 1;
    while (j != -1 && nums[j] <= nums[i]) {
      j = rightMax[j];
    }
    rightMax[i] = j;
    if (j != -1) {
      result[i] = nums[j];
    }
  }
  return result;
}
