#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept> // For exception handling

// 1. Basic Binary Search (Iterative)
//   - Application: Searching in a sorted database index.
//   - Explanation: The most fundamental implementation.  Efficiently finds a target in a sorted range.
int binarySearchIterative(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // Prevent potential overflow

        if (arr[mid] == target) {
            return mid; // Found the target, return its index
        } else if (arr[mid] < target) {
            low = mid + 1; // Target is in the right half
        } else {
            high = mid - 1; // Target is in the left half
        }
    }
    return -1; // Target not found
}

// 2. Binary Search (Recursive)
//   - Application: Implementing a search function in a tree-like data structure (though not directly on the tree itself, but on a sorted array representing some property of the tree nodes).
//   - Explanation: A recursive version of binary search.  Can be more concise but may have higher overhead for very large arrays.
int binarySearchRecursiveHelper(const std::vector<int>& arr, int target, int low, int high) {
    if (low > high) {
        return -1; // Base case: target not found
    }

    int mid = low + (high - low) / 2;

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursiveHelper(arr, target, mid + 1, high); // Recursive call on right half
    } else {
        return binarySearchRecursiveHelper(arr, target, low, mid - 1); // Recursive call on left half
    }
}

int binarySearchRecursive(const std::vector<int>& arr, int target) {
    return binarySearchRecursiveHelper(arr, target, 0, arr.size() - 1);
}

// 3. Binary Search with Lower Bound
//   - Application: Finding the first occurrence of an element in a sorted array with duplicates.  Useful in time-series data analysis (e.g., finding the first timestamp of an event).
//   - Explanation: Returns the index of the first element that is not less than the target.
int binarySearchLowerBound(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    int result = -1; // Initialize result to -1 (not found)

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            result = mid;     // Found a match, but look for earlier occurrences
            high = mid - 1; // Continue searching in the left half
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

// 4. Binary Search with Upper Bound
//   - Application: Finding the last occurrence of an element in a sorted array with duplicates.  Useful in determining the end of a range of identical values.
//   - Explanation: Returns the index of the last element that is not greater than the target.
int binarySearchUpperBound(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            result = mid;    // Found a match, but look for later occurrences
            low = mid + 1; // Continue searching in the right half
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

// 5. Binary Search in Rotated Sorted Array
//   - Application: Searching in a sorted array that has been rotated (e.g., [4, 5, 6, 7, 0, 1, 2]).  This is common in certain search problems and interview questions.  Can be adapted for specialized database search scenarios.
//   - Explanation:  Handles the case where the sorted array has been rotated.  It finds the pivot point and then performs binary search in the appropriate half.
int binarySearchRotated(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[low] <= arr[mid]) { // Left half is sorted
            if (target >= arr[low] && target < arr[mid]) {
                high = mid - 1; // Target is in the sorted left half
            } else {
                low = mid + 1; // Target is in the unsorted right half
            }
        } else { // Right half is sorted
            if (target > arr[mid] && target <= arr[high]) {
                low = mid + 1; // Target is in the sorted right half
            } else {
                high = mid - 1; // Target is in the unsorted left half
            }
        }
    }
    return -1;
}

int main() {
    std::vector<int> sortedArray = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    std::vector<int> rotatedArray = {4, 5, 6, 7, 0, 1, 2};
    std::vector<int> duplicateArray = {1, 2, 2, 2, 3, 4, 4, 5};

    int target = 23;
    int targetRotated = 0;
    int targetDuplicate = 2;

    // Basic Binary Search
    int index = binarySearchIterative(sortedArray, target);
    if (index != -1) {
        std::cout << "Iterative: Target " << target << " found at index " << index << std::endl;
    } else {
        std::cout << "Iterative: Target " << target << " not found" << std::endl;
    }

    // Recursive Binary Search
    index = binarySearchRecursive(sortedArray, target);
    if (index != -1) {
        std::cout << "Recursive: Target " << target << " found at index " << index << std::endl;
    } else {
        std::cout << "Recursive: Target " << target << " not found" << std::endl;
    }

     // Lower Bound Binary Search
    int lowerBoundIndex = binarySearchLowerBound(duplicateArray, targetDuplicate);
    if (lowerBoundIndex != -1) {
        std::cout << "Lower Bound: Target " << targetDuplicate << " found at index " << lowerBoundIndex << std::endl;
    } else {
        std::cout << "Lower Bound: Target " << targetDuplicate << " not found" << std::endl;
    }

    // Upper Bound Binary Search
    int upperBoundIndex = binarySearchUpperBound(duplicateArray, targetDuplicate);
    if (upperBoundIndex != -1) {
        std::cout << "Upper Bound: Target " << targetDuplicate << " found at index " << upperBoundIndex << std::endl;
    } else {
        std::cout << "Upper Bound: Target " << targetDuplicate << " not found" << std::endl;
    }
    // Binary Search in Rotated Array
    index = binarySearchRotated(rotatedArray, targetRotated);
    if (index != -1) {
        std::cout << "Rotated Array: Target " << targetRotated << " found at index " << index << std::endl;
    } else {
        std::cout << "Rotated Array: Target " << targetRotated << " not found" << std::endl;
    }

    return 0;
}
