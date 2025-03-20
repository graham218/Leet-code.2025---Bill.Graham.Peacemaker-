// Advanced Binary Search Implementations in Dart
// This implementation includes real-world applications of binary search
// with detailed explanations for each approach.

// 1. Iterative Binary Search (Standard Implementation)
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

// 3. Binary Search for First Occurrence (Useful in log-based systems)
int binarySearchFirstOccurrence(List<int> arr, int target) {
  int left = 0, right = arr.length - 1, result = -1;
  while (left <= right) {
    int mid = left + (right - left) ~/ 2;
    if (arr[mid] == target) {
      result = mid; // Store result and continue searching left
      right = mid - 1;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return result;
}

// 4. Binary Search for Last Occurrence (Useful for range-based queries)
int binarySearchLastOccurrence(List<int> arr, int target) {
  int left = 0, right = arr.length - 1, result = -1;
  while (left <= right) {
    int mid = left + (right - left) ~/ 2;
    if (arr[mid] == target) {
      result = mid; // Store result and continue searching right
      left = mid + 1;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return result;
}

// 5. Binary Search for Insertion Position (Used in ranking systems)
int binarySearchInsertPosition(List<int> arr, int target) {
  int left = 0, right = arr.length;
  while (left < right) {
    int mid = left + (right - left) ~/ 2;
    if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left; // Position where target should be inserted
}

// 6. Binary Search on Real-World Dataset (Simulating a Database Search)
String searchUserById(List<Map<String, dynamic>> users, int targetId) {
  int left = 0, right = users.length - 1;
  while (left <= right) {
    int mid = left + (right - left) ~/ 2;
    if (users[mid]['id'] == targetId) {
      return "User Found: ${users[mid]['name']}";
    } else if (users[mid]['id'] < targetId) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return "User not found";
}

// Test the implementations
void main() {
  List<int> numbers = [1, 3, 3, 5, 7, 7, 7, 9, 11, 13];
  int target = 7;

  List<Map<String, dynamic>> users = [
    {'id': 101, 'name': 'Alice'},
    {'id': 202, 'name': 'Bob'},
    {'id': 303, 'name': 'Charlie'},
    {'id': 404, 'name': 'David'},
  ];

  print("Iterative: ${binarySearchIterative(numbers, target)}");
  print("Recursive: ${binarySearchRecursive(numbers, target, 0, numbers.length - 1)}");
  print("First Occurrence: ${binarySearchFirstOccurrence(numbers, target)}");
  print("Last Occurrence: ${binarySearchLastOccurrence(numbers, target)}");
  print("Insert Position: ${binarySearchInsertPosition(numbers, target)}");
  print("Database Search: ${searchUserById(users, 303)}");
}
