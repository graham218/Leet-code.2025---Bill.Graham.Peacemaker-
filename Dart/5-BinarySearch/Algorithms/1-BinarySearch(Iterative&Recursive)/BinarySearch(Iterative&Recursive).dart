// Binary Search Implementations in Dart

// 1. Iterative Binary Search
int binarySearchIterative(List<int> arr, int target) {
  int left = 0, right = arr.length - 1;
  while (left <= right) {
    int mid = left + (right - left) ~/ 2;
    if (arr[mid] == target) return mid; // Target found
    if (arr[mid] < target) {
      left = mid + 1; // Search right half
    } else {
      right = mid - 1; // Search left half
    }
  }
  return -1; // Target not found
}

// 2. Recursive Binary Search
int binarySearchRecursive(List<int> arr, int target, int left, int right) {
  if (left > right) return -1; // Base case: Not found
  int mid = left + (right - left) ~/ 2;
  if (arr[mid] == target) return mid;
  if (arr[mid] < target) {
    return binarySearchRecursive(arr, target, mid + 1, right); // Search right half
  } else {
    return binarySearchRecursive(arr, target, left, mid - 1); // Search left half
  }
}

// 3. Binary Search using List extension
extension BinarySearchExtension on List<int> {
  int binarySearch(int target) {
    int left = 0, right = this.length - 1;
    while (left <= right) {
      int mid = left + (right - left) ~/ 2;
      if (this[mid] == target) return mid;
      if (this[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return -1;
  }
}

// 4. Binary Search using Higher-Order Function
int binarySearchHOF(List<int> arr, int target) {
  int search(int left, int right) {
    if (left > right) return -1;
    int mid = left + (right - left) ~/ 2;
    if (arr[mid] == target) return mid;
    return arr[mid] < target ? search(mid + 1, right) : search(left, mid - 1);
  }
  return search(0, arr.length - 1);
}

// Test the implementations
void main() {
  List<int> numbers = [1, 3, 5, 7, 9, 11, 13];
  int target = 7;

  print("Iterative: ${binarySearchIterative(numbers, target)}");
  print("Recursive: ${binarySearchRecursive(numbers, target, 0, numbers.length - 1)}");
  print("Extension: ${numbers.binarySearch(target)}");
  print("Higher-Order Function: ${binarySearchHOF(numbers, target)}");
}