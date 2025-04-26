#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <limits> // Required for numeric_limits

// *************************************************************************************************
// 1. Lower Bound using Standard Library (std::lower_bound)
//
//   - Uses the C++ standard library's `std::lower_bound` function.
//   - Returns an iterator to the first element in the range [first, last) which is
//     not less than (i.e., greater than or equal to) val.
//   - Real-world application: Finding the starting index of a sorted range of products
//     in a database where the price is greater than or equal to a given value.
// *************************************************************************************************
int lowerBoundSTL(const std::vector<int>& arr, int target) {
    auto it = std::lower_bound(arr.begin(), arr.end(), target);
    if (it != arr.end()) {
        return std::distance(arr.begin(), it); // Convert iterator to index
    }
    return -1; // Target not found (or greater than all elements)
}

// *************************************************************************************************
// 2. Upper Bound using Standard Library (std::upper_bound)
//
//   - Uses the C++ standard library's `std::upper_bound` function.
//   - Returns an iterator to the first element in the range [first, last) which is
//     greater than val.
//   - Real-world application: Finding the ending index (exclusive) of a sorted range
//     of products in a database where the price is less than a given value.  Useful
//     for determining the number of products within a price range.
// *************************************************************************************************
int upperBoundSTL(const std::vector<int>& arr, int target) {
    auto it = std::upper_bound(arr.begin(), arr.end(), target);
    if (it != arr.end()) {
        return std::distance(arr.begin(), it);
    }
    return -1; // Target not found (or greater than all elements)
}

// *************************************************************************************************
// 3. Lower Bound (Iterative Binary Search)
//
//   - Implements lower bound using a manual iterative binary search.
//   - This is a fundamental implementation, useful for understanding the algorithm.
//   - Real-world application: Implementing a custom search in a memory-constrained
//     embedded system where using the standard library is not feasible.  Also,
//     good for interview questions!
// *************************************************************************************************
int lowerBoundIterative(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size(); // Important: right is one past the end
    int result = -1;

    while (left < right) {
        int mid = left + (right - left) / 2; // Prevent potential overflow
        if (arr[mid] >= target) {
            result = mid;     // Potential lower bound, try to find a tighter one
            right = mid;     // Search in the left half
        } else {
            left = mid + 1; // Search in the right half
        }
    }
    return result;
}

// *************************************************************************************************
// 4. Upper Bound (Iterative Binary Search)
//
//   - Implements upper bound using a manual iterative binary search.
//   - Mirrors the lower bound implementation but with a slightly different condition.
//   - Real-world application:  Finding the insertion point in a sorted array to
//     maintain sorted order *after* insertion.
// *************************************************************************************************
int upperBoundIterative(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size(); // Important: right is one past the end
    int result = -1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > target) { // Key difference: > instead of >=
            result = mid;
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

// *************************************************************************************************
// 5. Lower Bound with Duplicates Handling (Finds the *first* occurrence)
//
//   - Handles the case where the target value may appear multiple times in the array.
//   - Ensures that the *lowest* index of the target value is returned.
//   - Real-world application: Finding the first occurrence of a specific log entry
//     in a sorted log file, where entries may be duplicated.
// *************************************************************************************************
int lowerBoundFirstOccurrence(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();
    int result = -1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;      // Found a match, but check for earlier occurrences
            right = mid;      // Continue searching in the left half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return result;
}

// *************************************************************************************************
// 6. Upper Bound with Duplicates Handling (Finds the *last* occurrence)
//    This was added as an extra, beyond the original 5.
//
//   - Handles the case where the target value may appear multiple times.
//   - Ensures that the *highest* index of the target value is returned.
//   - Real world application: Find the last entry of a stock trade.
// *************************************************************************************************
int upperBoundLastOccurrence(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();
    int result = -1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1; // Look for later occurrences.
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return result; // returns the last index, or -1 if not found
}

// *************************************************************************************************
// 7.  Count occurrences of target (using lower/upper bound)
//      This was added as an extra, beyond the original 5.
//
//   - Uses lower and upper bound to count the number of times a target value
//     appears in the sorted array.
//   - Real-world application: Counting the number of orders for a specific product
//     in an order database.
// *************************************************************************************************
int countOccurrences(const std::vector<int>& arr, int target) {
    int lower = lowerBoundFirstOccurrence(arr, target);
    int upper = upperBoundLastOccurrence(arr, target);
    if (lower == -1) {
        return 0; // Target not found
    }
    return upper - lower + 1;
}

// *************************************************************************************************
// Main function to demonstrate the different implementations
// *************************************************************************************************
int main() {
    std::vector<int> sortedArray = {2, 5, 5, 5, 6, 6, 8, 9, 9, 10};
    int targetValue = 5;

    std::cout << "Sorted Array: ";
    for (int num : sortedArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Target Value: " << targetValue << std::endl;
    std::cout << std::endl;

    // 1. Lower Bound using STL
    int lowerBound1 = lowerBoundSTL(sortedArray, targetValue);
    std::cout << "1. Lower Bound (STL): " << (lowerBound1 != -1 ? std::to_string(lowerBound1) : "Not Found") << std::endl;
    if (lowerBound1 != -1) {
        assert(sortedArray[lowerBound1] >= targetValue);
    }

    // 2. Upper Bound using STL
    int upperBound1 = upperBoundSTL(sortedArray, targetValue);
    std::cout << "2. Upper Bound (STL): " << (upperBound1 != -1 ? std::to_string(upperBound1) : "Not Found") << std::endl;
     if (upperBound1 != -1) {
        assert(sortedArray[upperBound1] > targetValue);
    }

    // 3. Lower Bound (Iterative)
    int lowerBound2 = lowerBoundIterative(sortedArray, targetValue);
    std::cout << "3. Lower Bound (Iterative): " << (lowerBound2 != -1 ? std::to_string(lowerBound2) : "Not Found") << std::endl;
    if (lowerBound2 != -1) {
        assert(sortedArray[lowerBound2] >= targetValue);
    }

    // 4. Upper Bound (Iterative)
    int upperBound2 = upperBoundIterative(sortedArray, targetValue);
    std::cout << "4. Upper Bound (Iterative): " << (upperBound2 != -1 ? std::to_string(upperBound2) : "Not Found") << std::endl;
    if (upperBound2 != -1) {
        assert(sortedArray[upperBound2] > targetValue);
    }
    // 5. Lower Bound First Occurrence
    int lowerBoundFirst = lowerBoundFirstOccurrence(sortedArray, targetValue);
    std::cout << "5. Lower Bound (First Occurrence): " << (lowerBoundFirst != -1 ? std::to_string(lowerBoundFirst) : "Not Found") << std::endl;
    if (lowerBoundFirst != -1) {
         assert(sortedArray[lowerBoundFirst] == targetValue);
         if (lowerBoundFirst > 0) {
            assert(sortedArray[lowerBoundFirst-1] < targetValue);
         }
    }

    // 6. Upper Bound Last Occurrence
    int upperBoundLast = upperBoundLastOccurrence(sortedArray, targetValue);
    std::cout << "6. Upper Bound (Last Occurrence): " << (upperBoundLast != -1 ? std::to_string(upperBoundLast) : "Not Found") << std::endl;
    if (upperBoundLast != -1){
        assert(sortedArray[upperBoundLast] == targetValue);
        if(upperBoundLast < sortedArray.size() - 1){
             assert(sortedArray[upperBoundLast + 1] > targetValue);
        }

    }
    // 7. Count Occurrences
    int count = countOccurrences(sortedArray, targetValue);
    std::cout << "7. Count Occurrences: " << count << std::endl;
    if (count > 0) {
        assert(lowerBoundFirstOccurrence(sortedArray, targetValue) != -1);
        assert(upperBoundLastOccurrence(sortedArray, targetValue) != -1);
    }

    // Test case where the target is not in the array
    targetValue = 7;
    std::cout << "\nTesting with target value " << targetValue << std::endl;
    std::cout << "1. Lower Bound (STL): " << (lowerBoundSTL(sortedArray, targetValue) != -1 ? std::to_string(lowerBoundSTL(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "2. Upper Bound (STL): " << (upperBoundSTL(sortedArray, targetValue) != -1 ? std::to_string(upperBoundSTL(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "3. Lower Bound (Iterative): " << (lowerBoundIterative(sortedArray, targetValue) != -1 ? std::to_string(lowerBoundIterative(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "4. Upper Bound (Iterative): " << (upperBoundIterative(sortedArray, targetValue) != -1 ? std::to_string(upperBoundIterative(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "5. Lower Bound (First Occurrence): " << (lowerBoundFirstOccurrence(sortedArray, targetValue) != -1 ? std::to_string(lowerBoundFirstOccurrence(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "6. Upper Bound (Last Occurrence): " << (upperBoundLastOccurrence(sortedArray, targetValue) != -1 ? std::to_string(upperBoundLastOccurrence(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "7. Count Occurrences: " << countOccurrences(sortedArray, targetValue) << std::endl;

    // Test case where the target is smaller than all elements
    targetValue = 1;
    std::cout << "\nTesting with target value " << targetValue << std::endl;
    std::cout << "1. Lower Bound (STL): " << (lowerBoundSTL(sortedArray, targetValue) != -1 ? std::to_string(lowerBoundSTL(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "2. Upper Bound (STL): " << (upperBoundSTL(sortedArray, targetValue) != -1 ? std::to_string(upperBoundSTL(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "3. Lower Bound (Iterative): " << (lowerBoundIterative(sortedArray, targetValue) != -1 ? std::to_string(lowerBoundIterative(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "4. Upper Bound (Iterative): " << (upperBoundIterative(sortedArray, targetValue) != -1 ? std::to_string(upperBoundIterative(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "5. Lower Bound (First Occurrence): " << (lowerBoundFirstOccurrence(sortedArray, targetValue) != -1 ? std::to_string(lowerBoundFirstOccurrence(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "6. Upper Bound (Last Occurrence): " << (upperBoundLastOccurrence(sortedArray, targetValue) != -1 ? std::to_string(upperBoundLastOccurrence(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "7. Count Occurrences: " << countOccurrences(sortedArray, targetValue) << std::endl;

    // Test case where the target is larger than all elements
    targetValue = 11;
    std::cout << "\nTesting with target value " << targetValue << std::endl;
    std::cout << "1. Lower Bound (STL): " << (lowerBoundSTL(sortedArray, targetValue) != -1 ? std::to_string(lowerBoundSTL(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "2. Upper Bound (STL): " << (upperBoundSTL(sortedArray, targetValue) != -1 ? std::to_string(upperBoundSTL(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "3. Lower Bound (Iterative): " << (lowerBoundIterative(sortedArray, targetValue) != -1 ? std::to_string(lowerBoundIterative(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "4. Upper Bound (Iterative): " << (upperBoundIterative(sortedArray, targetValue) != -1 ? std::to_string(upperBoundIterative(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "5. Lower Bound (First Occurrence): " << (lowerBoundFirstOccurrence(sortedArray, targetValue) != -1 ? std::to_string(lowerBoundFirstOccurrence(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "6. Upper Bound (Last Occurrence): " << (upperBoundLastOccurrence(sortedArray, targetValue) != -1 ? std::to_string(upperBoundLastOccurrence(sortedArray, targetValue)) : "Not Found") << std::endl;
    std::cout << "7. Count Occurrences: " << countOccurrences(sortedArray, targetValue) << std::endl;

    return 0;
}

