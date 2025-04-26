#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> // Include for std::function

// 1. Iterative Binary Search (Basic)
//   - Uses a while loop to repeatedly divide the search space in half.
//   - Compares the target value with the middle element.
//   - Adjusts the left or right boundary based on the comparison.
int binarySearchIterativeBasic(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; // Prevent potential overflow

        if (arr[mid] == target) {
            return mid; // Target found at index mid
        } else if (arr[mid] < target) {
            left = mid + 1; // Target is in the right half
        } else {
            right = mid - 1; // Target is in the left half
        }
    }
    return -1; // Target not found
}

// 2. Recursive Binary Search (Basic)
//   - Implements the binary search logic using recursion.
//   - Divides the search space in half in each recursive call.
//   - Base case: left > right (target not found)
int binarySearchRecursiveBasicHelper(const std::vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1; // Base case: Target not found
    }

    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursiveBasicHelper(arr, target, mid + 1, right); // Recursive call on right half
    } else {
        return binarySearchRecursiveBasicHelper(arr, target, left, mid - 1); // Recursive call on left half
    }
}

int binarySearchRecursiveBasic(const std::vector<int>& arr, int target) {
    return binarySearchRecursiveBasicHelper(arr, target, 0, arr.size() - 1);
}

// 3. Iterative Binary Search (Handling Duplicates - Find First Occurrence)
//   - Modified to find the *first* occurrence of the target value in a sorted array with duplicates.
//   - When a match is found, it continues to search the left half for an earlier occurrence.
int binarySearchIterativeFirst(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1; // Initialize result to -1 (not found)

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            result = mid;       // Store the index, but keep searching left
            right = mid - 1;    // Search for earlier occurrence
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result; // Returns the leftmost occurrence, or -1 if not found
}

// 4. Recursive Binary Search (Handling Duplicates - Find Last Occurrence)
// - Modified to find the *last* occurrence of the target.
// - When a match is found, it continues to search the right half.
int binarySearchRecursiveLastHelper(const std::vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1;
    }

    int mid = left + (right - left) / 2;
    int result;

    if (arr[mid] == target) {
        result = mid;
        int rightResult = binarySearchRecursiveLastHelper(arr, target, mid + 1, right);
        if (rightResult != -1)
            return rightResult;
        else
            return result;
    } else if (arr[mid] < target) {
        return binarySearchRecursiveLastHelper(arr, target, mid + 1, right);
    } else {
        return binarySearchRecursiveLastHelper(arr, target, left, mid - 1);
    }
}

int binarySearchRecursiveLast(const std::vector<int>& arr, int target) {
    return binarySearchRecursiveLastHelper(arr, target, 0, arr.size() - 1);
}

// 5. Iterative Binary Search (with Custom Comparison Function)
//    - Demonstrates using a custom comparison function for more flexibility.
//    -  Useful when searching in a sorted array of custom objects, or when the sorting order is not the default.
int binarySearchIterativeCustomCompare(const std::vector<int>& arr, int target,
                                       std::function<int(int, int)> compare) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int comparisonResult = compare(arr[mid], target);

        if (comparisonResult == 0) {
            return mid;
        } else if (comparisonResult < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    // Example usage
    std::vector<int> sortedArray = {2, 5, 7, 8, 11, 12, 13, 13, 13, 15};
    int targetValue = 13;

    // 1. Basic Iterative
    int index1 = binarySearchIterativeBasic(sortedArray, targetValue);
    std::cout << "Iterative Basic: Target " << targetValue << " found at index: " << index1 << std::endl;

    // 2. Basic Recursive
    int index2 = binarySearchRecursiveBasic(sortedArray, targetValue);
    std::cout << "Recursive Basic: Target " << targetValue << " found at index: " << index2 << std::endl;

     // 3. Iterative - First Occurrence
    int index3 = binarySearchIterativeFirst(sortedArray, targetValue);
    std::cout << "Iterative First Occurrence: Target " << targetValue << " found at index: " << index3 << std::endl;

    // 4. Recursive - Last Occurrence
    int index4 = binarySearchRecursiveLast(sortedArray, targetValue);
    std::cout << "Recursive Last Occurrence: Target " << targetValue << " found at index: " << index4 << std::endl;

    // 5. Iterative with Custom Comparison
    //    - Example:  Search, but treat even numbers as smaller for the search
    int index5 = binarySearchIterativeCustomCompare(sortedArray, targetValue,
                                                  std::function<int(int, int)>([](int a, int b) {
                                                      if (a == b) return 0;
                                                      if ((a % 2 == 0) && (b % 2 != 0)) return -1; // Even is "smaller"
                                                      if ((a % 2 != 0) && (b % 2 == 0)) return 1;  // Odd is "larger"
                                                      return (a < b) ? -1 : 1; // Otherwise, normal comparison
                                                  }));
    std::cout << "Iterative Custom Compare: Target " << targetValue << " found at index: " << index5 << std::endl;

    // Example when the target is not in the array
    int notFoundTarget = 99;
    int notFoundIndex = binarySearchIterativeBasic(sortedArray, notFoundTarget);
    std::cout << "Iterative Basic: Target " << notFoundTarget << " found at index: " << notFoundIndex << std::endl;

    return 0;
}
