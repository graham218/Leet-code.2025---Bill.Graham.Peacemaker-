#include <iostream>
#include <vector>
#include <algorithm> // Required for std::lower_bound, std::upper_bound (for approaches 4 and 5)
#include <cmath>   // Required for std::min

// Function to perform standard binary search
int binarySearchStandard(const std::vector<int>& arr, int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2; // Prevent potential overflow
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Target not found
}

// Function to perform exponential search
int exponentialSearch(const std::vector<int>& arr, int n, int target) {
    if (n == 0) return -1;
    if (arr[0] == target) return 0;

    int i = 1;
    while (i < n && arr[i] <= target) {
        i = i * 2;
    }
    // Call binary search for the range found.  Use min to handle cases
    // where i goes beyond the array bounds.
    return binarySearchStandard(arr, i / 2, std::min(i, n - 1), target);
}

// Approach 1: Standard Binary Search
int approach1(const std::vector<int>& arr, int target) {
    // Check for empty array
    if (arr.empty()) {
        return -1;
    }
    return binarySearchStandard(arr, 0, arr.size() - 1, target);
}

// Approach 2: Recursive Binary Search
int binarySearchRecursive(const std::vector<int>& arr, int low, int high, int target) {
    if (low > high) {
        return -1; // Base case: target not found
    }
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, mid + 1, high, target);
    } else {
        return binarySearchRecursive(arr, low, mid - 1, target);
    }
}

int approach2(const std::vector<int>& arr, int target) {
    if (arr.empty()) return -1;
    return binarySearchRecursive(arr, 0, arr.size() - 1, target);
}

// Approach 3: Using Exponential Search
int approach3(const std::vector<int>& arr, int target) {
    return exponentialSearch(arr, arr.size(), target);
}

// Approach 4: Using std::lower_bound (Binary Search variant)
int approach4(const std::vector<int>& arr, int target) {
    auto it = std::lower_bound(arr.begin(), arr.end(), target);
    if (it != arr.end() && *it == target) {
        return std::distance(arr.begin(), it); // Returns the index
    }
    return -1;
}

// Approach 5: Using std::upper_bound (Binary Search variant, finds last occurrence)
int approach5(const std::vector<int>& arr, int target) {
    auto it = std::upper_bound(arr.begin(), arr.end(), target);
    //check if target exists, and return last occurence
    if (it != arr.begin() && *(it-1) == target)
        return std::distance(arr.begin(), it - 1);
    return -1;
}

int main() {
    std::vector<int> arr = {2, 3, 4, 10, 40};
    int target = 10;

    std::cout << "Array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Target: " << target << std::endl;

    // Test each approach
    std::cout << "Approach 1 (Standard Binary Search): Index = " << approach1(arr, target) << std::endl;
    std::cout << "Approach 2 (Recursive Binary Search): Index = " << approach2(arr, target) << std::endl;
    std::cout << "Approach 3 (Exponential Search): Index = " << approach3(arr, target) << std::endl;
    std::cout << "Approach 4 (std::lower_bound): Index = " << approach4(arr, target) << std::endl;
    std::cout << "Approach 5 (std::upper_bound): Index = " << approach5(arr, target) << std::endl;

    // Test case where element is not present
    target = 5;
    std::cout << "\nTarget: " << target << std::endl;
    std::cout << "Approach 1 (Standard Binary Search): Index = " << approach1(arr, target) << std::endl;
    std::cout << "Approach 2 (Recursive Binary Search): Index = " << approach2(arr, target) << std::endl;
    std::cout << "Approach 3 (Exponential Search): Index = " << approach3(arr, target) << std::endl;
    std::cout << "Approach 4 (std::lower_bound): Index = " << approach4(arr, target) << std::endl;
    std::cout << "Approach 5 (std::upper_bound): Index = " << approach5(arr, target) << std::endl;

    // Test case with duplicate elements
    std::vector<int> arr2 = {2, 3, 4, 4, 4, 10, 40};
    target = 4;
    std::cout << "\nArray with duplicates: ";
     for (int num : arr2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Target: " << target << std::endl;
    std::cout << "Approach 1 (Standard Binary Search): Index = " << approach1(arr2, target) << std::endl;
    std::cout << "Approach 2 (Recursive Binary Search): Index = " << approach2(arr2, target) << std::endl;
    std::cout << "Approach 3 (Exponential Search): Index = " << approach3(arr2, target) << std::endl;
    std::cout << "Approach 4 (std::lower_bound): Index = " << approach4(arr2, target) << std::endl;
    std::cout << "Approach 5 (std::upper_bound): Index = " << approach5(arr2, target) << std::endl; //should return last occurence

    return 0;
}
