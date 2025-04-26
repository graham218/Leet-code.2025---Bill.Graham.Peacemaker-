#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept> // For exception handling

// Approach 1: Iterative Binary Search (Most Common, Efficient)
//   - Classic iterative approach.  Good balance of performance and code clarity.
//   - Best for general-purpose use where performance is important.
int searchRotatedIterative(const std::vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // Prevent potential overflow

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[low] <= nums[mid]) { // Left half is sorted
            if (nums[low] <= target && target < nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else { // Right half is sorted
            if (nums[mid] < target && target <= nums[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return -1;
}

// Approach 2: Recursive Binary Search
//   - Recursive implementation.  Can be more elegant for some, but may have
//     higher overhead due to function calls (stack usage).
//   - Suitable for situations where a recursive style is preferred and the
//     input size is not extremely large.
int searchRotatedRecursiveHelper(const std::vector<int>& nums, int target, int low, int high) {
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (nums[mid] == target) {
        return mid;
    }

    if (nums[low] <= nums[mid]) { // Left half is sorted
        if (nums[low] <= target && target < nums[mid]) {
            return searchRotatedRecursiveHelper(nums, target, low, mid - 1);
        } else {
            return searchRotatedRecursiveHelper(nums, target, mid + 1, high);
        }
    } else { // Right half is sorted
        if (nums[mid] < target && target <= nums[high]) {
            return searchRotatedRecursiveHelper(nums, target, mid + 1, high);
        } else {
            return searchRotatedRecursiveHelper(nums, target, low, mid - 1);
        }
    }
}

int searchRotatedRecursive(const std::vector<int>& nums, int target) {
    return searchRotatedRecursiveHelper(nums, target, 0, nums.size() - 1);
}

// Approach 3: Using std::rotate and std::binary_search (Less Efficient)
//   -  This approach uses the standard library functions `std::rotate` and
//      `std::binary_search`.  While it demonstrates using library functions,
//      it's generally *less* efficient than the specialized binary search
//      implementations because `std::rotate` has a linear time complexity in the worst case.
//   -  Good for educational purposes or when you want to quickly leverage
//      existing library functions, but performance is not critical.
int searchRotatedSTL(std::vector<int> nums, int target) { // Copy the vector (std::rotate modifies in-place)
    if (nums.empty()) return -1;

    int min_element_index = std::min_element(nums.begin(), nums.end()) - nums.begin(); //find the index of the minimum element
    std::rotate(nums.begin(), nums.begin() + min_element_index, nums.end()); // Rotate the vector

    auto it = std::binary_search(nums.begin(), nums.end(), target);
    if (it) {
        return std::lower_bound(nums.begin(), nums.end(), target) - nums.begin(); // Find the first occurrence
    }
    return -1;
}

// Approach 4: Handling Duplicates (Important for Real-World Data)
//   -  Handles cases where the rotated array contains duplicate elements.
//   -  The presence of duplicates makes it harder to determine which half
//      is sorted, requiring extra checks.
//   -  Crucial for real-world data where duplicates are common.
int searchRotatedDuplicates(const std::vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[low] == nums[mid] && nums[mid] == nums[high]) { // Handle duplicates
            low++;
            high--;
        } else if (nums[low] <= nums[mid]) { // Left half is sorted
            if (nums[low] <= target && target < nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else { // Right half is sorted
            if (nums[mid] < target && target <= nums[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return -1;
}

// Approach 5: Optimized with Early Exit (Slight Optimization)
//   -  Optimized version of the iterative approach with an early exit
//      condition.
//   -  In some cases, this can slightly improve performance by reducing
//      unnecessary iterations.
//   - Good where slight performance optimizations are needed
int searchRotatedOptimized(const std::vector<int>& nums, int target) {
    int low = 0;
    int high = nums.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[low] <= nums[mid]) { // Left half is sorted
            if (nums[low] == target) return low; // Early exit
            if (nums[mid] == target) return mid;
            if (nums[low] < target && target < nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else { // Right half is sorted
             if (nums[mid] == target) return mid;
             if (nums[high] == target) return high; // Early exit
            if (nums[mid] < target && target < nums[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    return -1;
}

int main() {
    std::vector<int> rotatedArray = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;

    std::cout << "Rotated Array: ";
    for (int num : rotatedArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Target: " << target << std::endl;

    // Test each approach and print the output
    std::cout << "\nApproach 1 (Iterative): Index = " << searchRotatedIterative(rotatedArray, target) << std::endl;
    std::cout << "Approach 2 (Recursive): Index = " << searchRotatedRecursive(rotatedArray, target) << std::endl;
    std::cout << "Approach 3 (STL): Index = " << searchRotatedSTL(rotatedArray, target) << std::endl;
    std::cout << "Approach 4 (Duplicates): Index = " << searchRotatedDuplicates({3, 1, 1, 3, 3, 3}, 1) << std::endl; // Example with duplicates
    std::cout << "Approach 5 (Optimized): Index = " << searchRotatedOptimized(rotatedArray, target) << std::endl;

    // Example where target is not found.
    target = 10;
    std::cout << "\nTarget (not found): " << target << std::endl;
    std::cout << "Approach 1 (Iterative): Index = " << searchRotatedIterative(rotatedArray, target) << std::endl;

    return 0;
}
