// Dart implementation for finding Upper Bound & Lower Bound using different approaches.
// Upper Bound: The smallest index where the element is greater than the target.
// Lower Bound: The smallest index where the element is greater than or equal to the target.

// 1. Iterative Binary Search - Lower Bound
int lowerBoundBinarySearch(List<int> arr, int target) {
  int left = 0, right = arr.length;
  while (left < right) {
    int mid = left + (right - left) ~/ 2;
    if (arr[mid] >= target) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left; // First position where arr[i] >= target
}

// 2. Iterative Binary Search - Upper Bound
int upperBoundBinarySearch(List<int> arr, int target) {
  int left = 0, right = arr.length;
  while (left < right) {
    int mid = left + (right - left) ~/ 2;
    if (arr[mid] > target) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left; // First position where arr[i] > target
}

// 3. Linear Search - Lower Bound
int lowerBoundLinear(List<int> arr, int target) {
  for (int i = 0; i < arr.length; i++) {
    if (arr[i] >= target) return i;
  }
  return arr.length;
}

// 4. Linear Search - Upper Bound
int upperBoundLinear(List<int> arr, int target) {
  for (int i = 0; i < arr.length; i++) {
    if (arr[i] > target) return i;
  }
  return arr.length;
}

// 5. Recursive Binary Search - Lower Bound
int lowerBoundRecursive(List<int> arr, int target, int left, int right) {
  if (left >= right) return left;
  int mid = left + (right - left) ~/ 2;
  if (arr[mid] >= target) {
    return lowerBoundRecursive(arr, target, left, mid);
  } else {
    return lowerBoundRecursive(arr, target, mid + 1, right);
  }
}

// 6. Recursive Binary Search - Upper Bound
int upperBoundRecursive(List<int> arr, int target, int left, int right) {
  if (left >= right) return left;
  int mid = left + (right - left) ~/ 2;
  if (arr[mid] > target) {
    return upperBoundRecursive(arr, target, left, mid);
  } else {
    return upperBoundRecursive(arr, target, mid + 1, right);
  }
}

// Test cases for Upper Bound & Lower Bound
void main() {
  List<int> numbers = [1, 2, 4, 4, 4, 5, 6, 8, 10];
  int target = 4;

  print("Lower Bound (Iterative Binary Search) of $target: ${lowerBoundBinarySearch(numbers, target)}");
  print("Upper Bound (Iterative Binary Search) of $target: ${upperBoundBinarySearch(numbers, target)}");
  print("Lower Bound (Linear) of $target: ${lowerBoundLinear(numbers, target)}");
  print("Upper Bound (Linear) of $target: ${upperBoundLinear(numbers, target)}");
  print("Lower Bound (Recursive Binary Search) of $target: ${lowerBoundRecursive(numbers, target, 0, numbers.length)}");
  print("Upper Bound (Recursive Binary Search) of $target: ${upperBoundRecursive(numbers, target, 0, numbers.length)}");

  target = 3;

  print("\nLower Bound (Iterative Binary Search) of $target: ${lowerBoundBinarySearch(numbers, target)}");
  print("Upper Bound (Iterative Binary Search) of $target: ${upperBoundBinarySearch(numbers, target)}");
  print("Lower Bound (Linear) of $target: ${lowerBoundLinear(numbers, target)}");
  print("Upper Bound (Linear) of $target: ${upperBoundLinear(numbers, target)}");
  print("Lower Bound (Recursive Binary Search) of $target: ${lowerBoundRecursive(numbers, target, 0, numbers.length)}");
  print("Upper Bound (Recursive Binary Search) of $target: ${upperBoundRecursive(numbers, target, 0, numbers.length)}");
}