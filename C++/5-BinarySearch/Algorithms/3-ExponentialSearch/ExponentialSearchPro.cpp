#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits> // Required for numeric_limits

// Function to perform binary search
// Iterative approach
int binarySearchIterative(const std::vector<int>& arr, int target) {
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

// Function to perform binary search recursively
int binarySearchRecursiveHelper(const std::vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1; // Base case: target not found
    }

    int mid = left + (right - left) / 2; // Prevent potential overflow

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursiveHelper(arr, target, mid + 1, right); // Search right half
    } else {
        return binarySearchRecursiveHelper(arr, target, left, mid - 1); // Search left half
    }
}

int binarySearchRecursive(const std::vector<int>& arr, int target) {
    return binarySearchRecursiveHelper(arr, target, 0, arr.size() - 1);
}

// Function to perform exponential search
int exponentialSearch(const std::vector<int>& arr, int target) {
    if (arr.empty()) return -1;
    if (arr[0] == target) return 0; // Target found at the first element

    int bound = 1;
    while (bound < arr.size() && arr[bound] < target) {
        bound *= 2; // Exponentially increase the bound
    }

    // Perform binary search within the range [bound/2, min(bound, arr.size()-1)]
    int left = bound / 2;
    int right = std::min(bound, static_cast<int>(arr.size() - 1)); // Use std::min to prevent potential errors.

    // Using the iterative version of Binary Search
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Function to perform exponential search, using recursive binary search
int exponentialSearchRecursive(const std::vector<int>& arr, int target) {
    if (arr.empty()) return -1;
    if (arr[0] == target) return 0;

    int bound = 1;
    while (bound < arr.size() && arr[bound] < target)
        bound *= 2;

    int left = bound / 2;
    int right = std::min(bound, static_cast<int>(arr.size() - 1));
    return binarySearchRecursiveHelper(arr, target, left, right); // Use the recursive helper
}

// Function to perform binary search with optimization for large arrays
int binarySearchOptimized(const std::vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        // Use a more robust way to calculate mid, especially for large arrays to avoid overflow
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    std::vector<int> sortedArray = {2, 3, 4, 10, 40, 50, 60, 100, 200, 500, 1000, 2000, 3000};
    int targetElement = 100;

    // Binary Search - Iterative
    int result1 = binarySearchIterative(sortedArray, targetElement);
    if (result1 != -1) {
        std::cout << "Binary Search (Iterative): Element " << targetElement << " found at index " << result1 << std::endl;
    } else {
        std::cout << "Binary Search (Iterative): Element " << targetElement << " not found" << std::endl;
    }

    // Binary Search - Recursive
    int result2 = binarySearchRecursive(sortedArray, targetElement);
    if (result2 != -1) {
        std::cout << "Binary Search (Recursive): Element " << targetElement << " found at index " << result2 << std::endl;
    } else {
        std::cout << "Binary Search (Recursive): Element " << targetElement << " not found" << std::endl;
    }

    // Exponential Search - Iterative Binary Search
    int result3 = exponentialSearch(sortedArray, targetElement);
    if (result3 != -1) {
        std::cout << "Exponential Search: Element " << targetElement << " found at index " << result3 << std::endl;
    } else {
        std::cout << "Exponential Search: Element " << targetElement << " not found" << std::endl;
    }

    // Exponential Search - Recursive Binary Search
    int result4 = exponentialSearchRecursive(sortedArray, targetElement);
     if (result4 != -1) {
        std::cout << "Exponential Search (Recursive): Element " << targetElement << " found at index " << result4 << std::endl;
    } else {
        std::cout << "Exponential Search (Recursive): Element " << targetElement << " not found" << std::endl;
    }

    // Binary Search - Optimized
    int result5 = binarySearchOptimized(sortedArray, targetElement);
    if (result5 != -1) {
        std::cout << "Binary Search (Optimized): Element " << targetElement << " found at index " << result5 << std::endl;
    } else {
        std::cout << "Binary Search (Optimized): Element " << targetElement << " not found" << std::endl;
    }

    return 0;
}

/*
Explanation:

1. Binary Search (Iterative):
   - Implements the standard binary search algorithm using a while loop.
   - It repeatedly divides the search interval in half.
   - The mid-point is calculated as left + (right - left) / 2 to prevent potential overflow issues with large arrays.
   - Returns the index of the target element if found, otherwise returns -1.
   - Real-world application: Searching for a specific entry in a sorted database index.

2. Binary Search (Recursive):
    - Implements binary search using recursion.
    - The function calls itself with updated left and right bounds until the target is found or the search space is exhausted.
    - A helper function is used to maintain the left and right indices across recursive calls.
    - Real-world application: Implementing a recursive search in a file system or directory structure.

3. Exponential Search:
   - Designed for searching in unbounded sorted arrays.
   - It first finds a range where the target element might reside by exponentially increasing the bound.
   - Then, it performs a binary search within that range.
   - Uses the iterative `binarySearchIterative` function.
   - Real-world application: Searching for a value in a very large, potentially infinite, stream of sorted data (e.g., a sorted stream of log entries).

4. Exponential Search (Recursive Binary Search):
    - Same as the above Exponential Search, but uses the recursive version of binary search (`binarySearchRecursiveHelper`).
    - Demonstrates how to combine exponential search with a recursive binary search implementation.
    - Real-world application:  Similar to the iterative version, but the recursive approach might be preferred in certain recursive tree-like data structures.

5. Binary Search (Optimized):
   - This is an optimized version of the iterative binary search.
   - The key optimization is the calculation of the middle index:  `mid = low + (high - low) / 2;`
     This method is used to prevent integer overflow that could occur if `(low + high) / 2` is used when `low` and `high` are very large.
   -  Real-world application: High-performance searching in extremely large datasets, such as in scientific computing or financial data analysis.

Key Improvements and Best Practices:
- Overflow Prevention: The calculation of the middle index in binary search is changed to `left + (right - left) / 2` to prevent potential integer overflow when dealing with very large left and right indices.
- Use of std::min: In the exponential search, `std::min` is used to ensure that the right boundary of the binary search does not exceed the array size.  This adds robustness.
- Clarity and Comments: The code includes more detailed comments to explain the purpose and logic of each section, improving readability and maintainability.
- Robustness: The code handles the case of an empty input array in the exponential search.
- Consistent Naming:  Variables and function names are more descriptive and consistent.
*/
