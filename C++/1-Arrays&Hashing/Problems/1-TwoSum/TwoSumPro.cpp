#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdexcept> // For exception handling

// 1. Brute Force Approach
//   - Simplest approach.
//   - Check every possible pair of numbers.
//   - Time Complexity: O(n^2), where n is the size of the input vector.
//   - Space Complexity: O(1).
//   - Real-world application: Useful for small datasets or when a very simple,
//     easily understandable solution is needed, such as in a simple data analysis
//     script for a small experiment.  It's often used as a baseline for
//     comparing the performance of more optimized algorithms.
std::vector<int> twoSumBruteForce(const std::vector<int>& nums, int target) {
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = i + 1; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) {
                return {static_cast<int>(i), static_cast<int>(j)}; // Cast size_t to int
            }
        }
    }
    return {}; // Return empty vector if no solution is found.  Good practice.
}

// 2. Hash Map Approach
//   - Efficient solution using a hash map.
//   - Store each number and its index in the hash map.
//   - For each number, check if its complement (target - number) exists in the hash map.
//   - Time Complexity: O(n) - average case for hash map operations.
//   - Space Complexity: O(n) - for storing the numbers in the hash map.
//   - Real-world application: This is very common in real-world applications.  For
//     example, it could be used in a web service that needs to quickly look up
//     pairs of values (e.g., finding matching product IDs, or processing financial
//     transactions).  Hash maps are highly optimized in modern libraries.
std::vector<int> twoSumHashMap(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> numMap;
    for (size_t i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], static_cast<int>(i)}; // Cast size_t to int
        }
        numMap[nums[i]] = static_cast<int>(i); // Cast size_t to int
    }
    return {}; // Return empty vector if no solution is found.
}

// 3. Sorted Array and Two Pointers
//   - Requires the input array to be sorted.
//   - Uses two pointers, one at the beginning and one at the end of the array.
//   - Move the pointers based on whether the sum of the numbers is less than or greater than the target.
//   - Time Complexity: O(n log n) for sorting + O(n) for the two-pointer traversal, so O(n log n).
//   - Space Complexity: O(1) if the sorting is done in place.  Otherwise, O(n) for a copy.
//   - Real-world application: Useful when the input array is already sorted or when
//     sorting is an acceptable preprocessing step.  For example, this approach
//     could be used in a system that processes sorted data, such as in some
//     types of database operations or in specific numerical algorithms.
std::vector<int> twoSumSortedArray(std::vector<int> nums, int target) {
    // Create a vector of pairs to store the original index with the value.
    std::vector<std::pair<int, int>> numsWithIndices;
    for (size_t i = 0; i < nums.size(); ++i) {
        numsWithIndices.push_back({nums[i], static_cast<int>(i)}); // Store value and original index
    }

    // Sort the vector of pairs based on the number.
    std::sort(numsWithIndices.begin(), numsWithIndices.end());

    int left = 0;
    int right = static_cast<int>(numsWithIndices.size()) - 1; // Cast size_t to int

    while (left < right) {
        int sum = numsWithIndices[left].first + numsWithIndices[right].first;
        if (sum == target) {
            // Return the original indices.
            return {numsWithIndices[left].second, numsWithIndices[right].second};
        } else if (sum < target) {
            ++left;
        } else {
            --right;
        }
    }
    return {};
}

// 4. Using Binary Search (After Sorting)
//   - Sort the array.
//   - For each element, use binary search to find its complement.
//   - Time Complexity: O(n log n) for sorting + O(n log n) for the binary searches, so O(n log n).
//   - Space Complexity: O(1) if sorting is done in place.
//   - Real-world application: This approach is suitable when the array is already sorted
//     or when sorting is a reasonable preprocessing step.  Binary search is
//     efficient, making this approach useful in applications where quick lookups
//     are needed in a sorted dataset.
int binarySearch(const std::vector<int>& nums, int target, int excludeIndex) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1; // Cast size_t to int
    while (left <= right) {
        int mid = left + (right - left) / 2; // Prevent potential overflow
        if (mid == excludeIndex) { // Skip the excluded index.
           if (mid + 1 <= right) {
               left = mid + 1;
           } else {
               right = mid -1;
           }
           continue;
        }
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

std::vector<int> twoSumBinarySearch(std::vector<int> nums, int target) {
    // Create a vector of pairs to store the original index with the value.
    std::vector<std::pair<int, int>> numsWithIndices;
    for (size_t i = 0; i < nums.size(); ++i) {
        numsWithIndices.push_back({nums[i], static_cast<int>(i)}); // Store value and original index
    }

    // Sort the vector of pairs based on the number.
    std::sort(numsWithIndices.begin(), numsWithIndices.end());
    // Extract just the sorted numbers for binary search.
    std::vector<int> sortedNums;
    for (const auto& pair : numsWithIndices) {
        sortedNums.push_back(pair.first);
    }

    for (size_t i = 0; i < sortedNums.size(); ++i) {
        int complement = target - sortedNums[i];
        int complementIndex = binarySearch(sortedNums, complement, static_cast<int>(i)); // Cast size_t to int
        if (complementIndex != -1) {
             // Find original indices.
            int originalIndex1 = numsWithIndices[i].second;
            int originalIndex2 = numsWithIndices[complementIndex].second;
            if (originalIndex1 != originalIndex2)
                return {originalIndex1, originalIndex2};
        }
    }
    return {};
}

// 5. Optimized Hash Map Approach (Slightly different order)
//   -  Same time complexity as the previous hash map solution, but slightly
//      optimized for cases where the complement is found early in the array.
//   - Time Complexity: O(n)
//   - Space Complexity: O(n)
std::vector<int> twoSumOptimizedHashMap(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> numMap;
    for (size_t i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        // Check if complement exists *before* adding the current number.
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], static_cast<int>(i)};
        }
        numMap[nums[i]] = static_cast<int>(i);
    }
    return {};
}

int main() {
    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    // Brute Force
    std::cout << "Brute Force: ";
    std::vector<int> resultBruteForce = twoSumBruteForce(nums, target);
    if (!resultBruteForce.empty()) {
        std::cout << resultBruteForce[0] << ", " << resultBruteForce[1] << std::endl;
    } else {
        std::cout << "No solution found" << std::endl;
    }

    // Hash Map
    std::cout << "Hash Map: ";
    std::vector<int> resultHashMap = twoSumHashMap(nums, target);
    if (!resultHashMap.empty()) {
        std::cout << resultHashMap[0] << ", " << resultHashMap[1] << std::endl;
    } else {
        std::cout << "No solution found" << std::endl;
    }

    // Sorted Array and Two Pointers
    std::cout << "Sorted Array: ";
    std::vector<int> resultSortedArray = twoSumSortedArray(nums, target);
    if (!resultSortedArray.empty()) {
        std::cout << resultSortedArray[0] << ", " << resultSortedArray[1] << std::endl;
    } else {
        std::cout << "No solution found" << std::endl;
    }

    // Binary Search
    std::cout << "Binary Search: ";
    std::vector<int> resultBinarySearch = twoSumBinarySearch(nums, target);
    if (!resultBinarySearch.empty()) {
        std::cout << resultBinarySearch[0] << ", " << resultBinarySearch[1] << std::endl;
    } else {
        std::cout << "No solution found" << std::endl;
    }

    // Optimized Hash Map
    std::cout << "Optimized Hash Map: ";
    std::vector<int> resultOptimizedHashMap = twoSumOptimizedHashMap(nums, target);
    if (!resultOptimizedHashMap.empty()) {
        std::cout << resultOptimizedHashMap[0] << ", " << resultOptimizedHashMap[1] << std::endl;
    } else {
        std::cout << "No solution found" << std::endl;
    }

    return 0;
}
