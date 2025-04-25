#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <tuple>
#include <stdexcept>

// Function to find two numbers in a sorted array that add up to a target sum.
//
// Args:
//     numbers: A sorted vector of integers.
//     target: The target sum.
//     approach: An integer specifying the approach to use (1 to 5).
//
// Returns:
//     A tuple containing the indices (1-based) of the two numbers if found,
//     otherwise a tuple with (-1, -1).
//
// Throws:
//     std::invalid_argument: If the approach is invalid.
std::tuple<int, int> twoSum(const std::vector<int>& numbers, int target, int approach) {
    if (numbers.empty()) {
        return std::make_tuple(-1, -1);
    }

    switch (approach) {
        case 1: {
            // Approach 1: Two Pointers (Optimal for Sorted Array)
            // Time Complexity: O(n)
            // Space Complexity: O(1)
            int left = 0;
            int right = numbers.size() - 1;
            while (left < right) {
                int sum = numbers[left] + numbers[right];
                if (sum == target) {
                    return std::make_tuple(left + 1, right + 1); // 1-based indexing
                } else if (sum < target) {
                    left++; // Move left pointer to increase sum
                } else {
                    right--; // Move right pointer to decrease sum
                }
            }
            return std::make_tuple(-1, -1); // Not found
        }
        case 2: {
            // Approach 2: Binary Search
            // Time Complexity: O(n log n)
            // Space Complexity: O(1)
            for (int i = 0; i < numbers.size(); ++i) {
                int complement = target - numbers[i];
                // Use binary search to find the complement in the remaining part of the array
                int left = i + 1;
                int right = numbers.size() - 1;
                while (left <= right) {
                    int mid = left + (right - left) / 2; // Prevent overflow
                    if (numbers[mid] == complement) {
                        return std::make_tuple(i + 1, mid + 1); // 1-based indexing
                    } else if (numbers[mid] < complement) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
            }
            return std::make_tuple(-1, -1); // Not found
        }
        case 3: {
            // Approach 3: Hash Map (unordered_map)
            // Time Complexity: O(n) on average, O(n^2) worst-case
            // Space Complexity: O(n)
            std::unordered_map<int, int> numMap; // Key: number, Value: index
            for (int i = 0; i < numbers.size(); ++i) {
                int complement = target - numbers[i];
                if (numMap.find(complement) != numMap.end()) {
                    return std::make_tuple(numMap[complement] + 1, i + 1); // 1-based indexing
                }
                numMap[numbers[i]] = i;
            }
            return std::make_tuple(-1, -1); // Not found
        }
        case 4: {
            // Approach 4: Brute Force
            // Time Complexity: O(n^2)
            // Space Complexity: O(1)
            for (int i = 0; i < numbers.size(); ++i) {
                for (int j = i + 1; j < numbers.size(); ++j) {
                    if (numbers[i] + numbers[j] == target) {
                        return std::make_tuple(i + 1, j + 1); // 1-based indexing
                    }
                }
            }
            return std::make_tuple(-1, -1); // Not found
        }
        case 5: {
            // Approach 5: Using std::find (Illustrative, not optimal)
            // Time Complexity: O(n^2) in worst case.  std::find is O(n)
            // Space Complexity: O(1)
             for (int i = 0; i < numbers.size(); ++i) {
                int complement = target - numbers[i];
                //  std::find  iterates through the *entire* remaining portion.
                auto it = std::find(numbers.begin() + i + 1, numbers.end(), complement);
                if (it != numbers.end()) {
                    int j = std::distance(numbers.begin(), it); // Get the index
                    return std::make_tuple(i + 1, j + 1);
                }
             }
            return std::make_tuple(-1, -1);
        }
        default:
            throw std::invalid_argument("Invalid approach specified.  Choose 1-5.");
    }
}

int main() {
    // Example usage
    std::vector<int> numbers = {2, 7, 11, 15};
    int target = 9;

    // Test each approach
    for (int approach = 1; approach <= 5; ++approach) {
        std::tuple<int, int> result = twoSum(numbers, target, approach);
        int index1, index2;
        std::tie(index1, index2) = result; // Unpack the tuple

        std::cout << "Approach " << approach << ": ";
        if (index1 != -1 && index2 != -1) {
            std::cout << "Indices: " << index1 << ", " << index2 << std::endl;
        } else {
            std::cout << "No solution found." << std::endl;
        }
    }

    // Example with no solution
    std::vector<int> numbers2 = {2, 3, 4, 5};
    target = 12;
    std::tuple<int, int> result = twoSum(numbers2, target, 1); // Using approach 1
    int index1, index2;
    std::tie(index1, index2) = result;
    std::cout << "No Solution Example: Approach 1: ";
     if (index1 != -1 && index2 != -1) {
        std::cout << "Indices: " << index1 << ", " << index2 << std::endl;
    } else {
        std::cout << "No solution found." << std::endl;
    }
    // Example with an empty vector
    std::vector<int> numbers3 = {};
    target = 0;
    std::tuple<int, int> resultEmpty = twoSum(numbers3, target, 1);
    int index1Empty, index2Empty;
    std::tie(index1Empty, index2Empty) = resultEmpty;
    std::cout << "Empty Vector Example: Approach 1: ";
    if (index1Empty != -1 && index2Empty != -1) {
        std::cout << "Indices: " << index1Empty << ", " << index2Empty << std::endl;
    } else {
        std::cout << "No solution found." << std::endl;
    }

    // Example with duplicate numbers
    std::vector<int> numbers4 = {3, 3, 6, 15};
    target = 6;
    std::tuple<int, int> resultDuplicate = twoSum(numbers4, target, 1);
    int index1Duplicate, index2Duplicate;
    std::tie(index1Duplicate, index2Duplicate) = resultDuplicate;
    std::cout << "Duplicate Numbers Example: Approach 1: ";
    if (index1Duplicate != -1 && index2Duplicate != -1) {
        std::cout << "Indices: " << index1Duplicate << ", " << index2Duplicate << std::endl;
    } else {
        std::cout << "No solution found." << std::endl;
    }
    return 0;
}
