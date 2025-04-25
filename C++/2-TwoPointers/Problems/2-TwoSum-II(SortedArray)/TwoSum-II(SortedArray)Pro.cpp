#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <tuple>
#include <stdexcept> // For exception handling

// ----------------------------------------------------------------------------
// Approach 1: Two Pointers (Optimal for Sorted Arrays)
// ----------------------------------------------------------------------------
//
// * Core Idea: Since the array is sorted, we can use two pointers,
//     one at the beginning and one at the end.  We move them towards
//     each other based on whether the sum is too small or too large.
// * Time Complexity: O(n), where n is the length of the array.
// * Space Complexity: O(1).
// * Real-world application:  This is the most efficient general
//     solution when you know the input array is sorted.  Often used
//     in database query optimization, and in processing sorted data
//     from external sensors.
//
std::pair<int, int> twoSum_twoPointers(const std::vector<int>& numbers, int target) {
    int left = 0;
    int right = numbers.size() - 1;

    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) {
            return {left + 1, right + 1}; // +1 because the problem asks for 1-based indexing
        } else if (sum < target) {
            left++; // Move left pointer to increase the sum
        } else {
            right--; // Move right pointer to decrease the sum
        }
    }

    // No solution found.  Returning {-1, -1} is common, but
    //  throwing an exception might be better in some application scenarios.
    return {-1, -1};
    // Or:  throw std::runtime_error("No two sum solution found");
}

// ----------------------------------------------------------------------------
// Approach 2: Binary Search (for one element at a time)
// ----------------------------------------------------------------------------
//
// * Core Idea: Iterate through the array. For each element, use binary
//     search to find the complement (target - element) in the rest of
//     the array.
// * Time Complexity: O(n log n), where n is the length of the array.
// * Space Complexity: O(1).
// * Real-world application: Good when the array is very large,
//    and you want to reduce the number of comparisons for each element.
//    Useful in search engines, and large-scale data analysis.
//
int binarySearch(const std::vector<int>& numbers, int target, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2; // Prevent overflow
        if (numbers[mid] == target) {
            return mid;
        } else if (numbers[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; // Not found
}

std::pair<int, int> twoSum_binarySearch(const std::vector<int>& numbers, int target) {
    for (int i = 0; i < numbers.size(); ++i) {
        int complement = target - numbers[i];
        int complementIndex = binarySearch(numbers, complement, i + 1, numbers.size() - 1); // Search in the rest of the array
        if (complementIndex != -1) {
            return {i + 1, complementIndex + 1};
        }
    }
    return {-1, -1};
}

// ----------------------------------------------------------------------------
// Approach 3: Hash Map (for unsorted arrays, but works here too)
// ----------------------------------------------------------------------------
//
// * Core Idea:  Store each number and its index in a hash map.
//     For each number, check if its complement (target - number)
//     is already in the hash map.
// * Time Complexity: O(n) on average, where n is the length of the array.
// * Space Complexity: O(n).
// * Real-world application:  This is very good for *unsorted* arrays.  Although
//     the problem specifies a sorted array, this method is more general.
//     Hash tables are used extensively in databases (indexing), compilers
//     (symbol tables), and network routing.
//
std::pair<int, int> twoSum_hashTable(const std::vector<int>& numbers, int target) {
    std::unordered_map<int, int> numMap; // Key: number, Value: index (1-based)
    for (int i = 0; i < numbers.size(); ++i) {
        int complement = target - numbers[i];
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], i + 1}; // Found the pair
        }
        numMap[numbers[i]] = i + 1; // Store the number and its index
    }
    return {-1, -1};
}

// ----------------------------------------------------------------------------
// Approach 4: Using STL's `find` (Less Efficient, Demonstrative)
// ----------------------------------------------------------------------------
//
// * Core Idea: Iterate through the array.  For each element, use
//     the `std::find` algorithm to search for the complement in the
//     rest of the array.
// * Time Complexity: O(n^2) in the worst case.  `std::find` is linear.
// * Space Complexity: O(1).
// * Real-world application:  This is *not* a good approach for performance-critical
//    code.  It's mainly for demonstration or very small datasets where
//    code simplicity is more important than raw speed.  Avoid in large systems.
//
std::pair<int, int> twoSum_stlFind(const std::vector<int>& numbers, int target) {
    for (int i = 0; i < numbers.size(); ++i) {
        int complement = target - numbers[i];
        // std::find returns an iterator to the first element equal to value,
        // or last if no such element is found.
        auto it = std::find(numbers.begin() + i + 1, numbers.end(), complement);
        if (it != numbers.end()) {
            int complementIndex = std::distance(numbers.begin(), it); // Get the index
            return {i + 1, complementIndex + 1};
        }
    }
    return {-1, -1};
}

// ----------------------------------------------------------------------------
// Approach 5:  Brute Force (for comparison and educational purposes)
// ----------------------------------------------------------------------------
//
// * Core Idea:  Try every possible pair of numbers in the array.
// * Time Complexity: O(n^2), where n is the length of the array.
// * Space Complexity: O(1).
// * Real-world application:  This is the *least* efficient approach.  It's
//     only useful for very small datasets or for establishing a baseline
//     for comparing the performance of other algorithms.  Never use this
//     in production code for any significant amount of data.
//
std::pair<int, int> twoSum_bruteForce(const std::vector<int>& numbers, int target) {
    for (int i = 0; i < numbers.size(); ++i) {
        for (int j = i + 1; j < numbers.size(); ++j) {
            if (numbers[i] + numbers[j] == target) {
                return {i + 1, j + 1};
            }
        }
    }
    return {-1, -1};
}

// ----------------------------------------------------------------------------
// Main function to test the implementations
// ----------------------------------------------------------------------------
//
int main() {
    std::vector<int> numbers = {2, 7, 11, 15};
    int target = 9;

    // Use a tuple to store the function and its name, for easier iteration.
    std::tuple<std::pair<int, int> (*)(const std::vector<int>&, int), std::string> functions[] = {
        {twoSum_twoPointers, "Two Pointers"},
        {twoSum_binarySearch, "Binary Search"},
        {twoSum_hashTable, "Hash Table"},
        {twoSum_stlFind, "STL find"},
        {twoSum_bruteForce, "Brute Force"}
    };

    // Iterate through the functions, calling each one and printing the results.
    for (const auto& [func, name] : functions) {
        try {
            std::pair<int, int> result = func(numbers, target);
            std::cout << "Approach: " << name << std::endl;
            std::cout << "Indices: " << result.first << ", " << result.second << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "Approach: " << name << std::endl;
            std::cerr << "Error: " << e.what() << std::endl; // Output the error message
        }
        std::cout << "------------------------" << std::endl;
    }

    // Example with a negative number and a zero
    std::vector<int> numbers2 = {-1, 0};
    int target2 = -1;
    std::pair<int, int> result2 = twoSum_twoPointers(numbers2, target2);
    std::cout << "Two Pointers with negative number and zero: " << result2.first << ", " << result2.second << std::endl;

    // Example where no solution exists.  The Two Pointers approach
    // will return {-1, -1} in this case.
    std::vector<int> numbers3 = {2, 7, 11, 15};
    int target3 = 20;
    std::pair<int, int> result3 = twoSum_twoPointers(numbers3, target3);
    std::cout << "Two Pointers with no solution: " << result3.first << ", " << result3.second << std::endl;

    return 0;
}

