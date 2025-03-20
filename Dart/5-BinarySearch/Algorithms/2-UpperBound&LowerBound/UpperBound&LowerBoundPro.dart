// Dart implementation for finding Upper Bound & Lower Bound using 6 different approaches.
// Includes real-world use cases like database indexing, range searching, and pagination.

// 1. Iterative Binary Search - Lower Bound
// Finds the first position where arr[i] >= target
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
  return left;
}

// 2. Iterative Binary Search - Upper Bound
// Finds the first position where arr[i] > target
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
  return left;
}

// 3. Recursive Binary Search - Lower Bound
int lowerBoundRecursive(List<int> arr, int target, int left, int right) {
  if (left >= right) return left;
  int mid = left + (right - left) ~/ 2;
  if (arr[mid] >= target) {
    return lowerBoundRecursive(arr, target, left, mid);
  } else {
    return lowerBoundRecursive(arr, target, mid + 1, right);
  }
}

// 4. Recursive Binary Search - Upper Bound
int upperBoundRecursive(List<int> arr, int target, int left, int right) {
  if (left >= right) return left;
  int mid = left + (right - left) ~/ 2;
  if (arr[mid] > target) {
    return upperBoundRecursive(arr, target, left, mid);
  } else {
    return upperBoundRecursive(arr, target, mid + 1, right);
  }
}

// 5. Real-World Use Case: Finding the First Available ID in a Sorted Database
// Example: Finding the first available order ID in an ordered list
int findFirstAvailableID(List<int> orderIDs, int targetID) {
  return lowerBoundBinarySearch(orderIDs, targetID);
}

// 6. Real-World Use Case: Paginated Search - Finding Start Index of a Page
// Example: Finding where a specific search term should start displaying results in pagination
int findPaginationStartIndex(List<int> data, int searchKey) {
  return lowerBoundBinarySearch(data, searchKey);
}

// Test cases for Upper Bound & Lower Bound
void main() {
  List<int> numbers = [1, 2, 4, 4, 4, 5, 6, 8, 10];
  int target = 4;

  print("Lower Bound (Iterative Binary Search) of $target: ${lowerBoundBinarySearch(numbers, target)}");
  print("Upper Bound (Iterative Binary Search) of $target: ${upperBoundBinarySearch(numbers, target)}");
  print("Lower Bound (Recursive) of $target: ${lowerBoundRecursive(numbers, target, 0, numbers.length)}");
  print("Upper Bound (Recursive) of $target: ${upperBoundRecursive(numbers, target, 0, numbers.length)}");
  print("First Available Order ID for $target: ${findFirstAvailableID(numbers, target)}");
  print("Pagination Start Index for $target: ${findPaginationStartIndex(numbers, target)}");

  target = 3;

  print("\nLower Bound (Iterative Binary Search) of $target: ${lowerBoundBinarySearch(numbers, target)}");
  print("Upper Bound (Iterative Binary Search) of $target: ${upperBoundBinarySearch(numbers, target)}");
  print("Lower Bound (Recursive) of $target: ${lowerBoundRecursive(numbers, target, 0, numbers.length)}");
  print("Upper Bound (Recursive) of $target: ${upperBoundRecursive(numbers, target, 0, numbers.length)}");
  print("First Available Order ID for $target: ${findFirstAvailableID(numbers, target)}");
  print("Pagination Start Index for $target: ${findPaginationStartIndex(numbers, target)}");
}