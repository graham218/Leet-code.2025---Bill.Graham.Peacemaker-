#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <stdexcept>
#include <optional> // Include for std::optional

// 1. Iterative Binary Search with Range Checking
//   - Includes checks for valid input ranges, crucial for robust applications.
//   - Returns a `std::optional` to handle the case where the element is not found,
//     avoiding the need for magic numbers like -1.  Requires C++17.  For C++11,
//     you would need to use pointers or exceptions.
template <typename T>
std::optional<size_t> binarySearchIterativeSafe(const std::vector<T>& arr, const T& target) {
    if (arr.empty()) {
        return {}; // Empty array, element cannot be found.
    }
    size_t left = 0;
    size_t right = arr.size() - 1;

    while (left <= right) {
        size_t mid = left + (right - left) / 2; // Use size_t for mid to match left/right

        if (arr[mid] == target) {
            return mid; // Return the index if found
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return {}; // Not found
}

// 2. Recursive Binary Search with Error Handling
//   - Uses exceptions to handle cases where the input is invalid.
//   - This is a common approach in production code for signaling errors.
template <typename T>
size_t binarySearchRecursiveSafeHelper(const std::vector<T>& arr, const T& target, size_t left, size_t right) {
    if (left > right) {
        throw std::out_of_range("Target not found in array"); // Use a standard exception
    }

    size_t mid = left + (right - left) / 2;

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target) {
        return binarySearchRecursiveSafeHelper(arr, target, mid + 1, right);
    } else {
        return binarySearchRecursiveSafeHelper(arr, target, left, mid - 1);
    }
}

template <typename T>
size_t binarySearchRecursiveSafe(const std::vector<T>& arr, const T& target) {
    if (arr.empty())
       throw std::invalid_argument("Empty vector");
    return binarySearchRecursiveSafeHelper(arr, target, 0, arr.size() - 1);
}

// 3. Binary Search for Custom Objects with Comparator
//   - Demonstrates binary search with a custom comparison function.
//   - This is essential for searching in sorted arrays of user-defined objects.
//   - Uses a function object (functor) for the comparison.
template <typename T, typename Compare>
std::optional<size_t> binarySearchCustom(const std::vector<T>& arr, const T& target, Compare compare) {
    if (arr.empty()) {
        return {};
    }
    size_t left = 0;
    size_t right = arr.size() - 1;

    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        int comparisonResult = compare(arr[mid], target);

        if (comparisonResult == 0) {
            return mid;
        } else if (comparisonResult < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return {};
}

// Example struct for demonstrating custom comparison.
struct Person {
    std::string name;
    int age;
};

// A functor for comparing Person objects by age.
struct ComparePersonAge {
    int operator()(const Person& a, const Person& b) const {
        if (a.age == b.age) return 0;
        return (a.age < b.age) ? -1 : 1;
    }
};

// 4. Binary Search with Logging
//   - Includes logging of the search process.  This can be invaluable for
//     debugging and auditing in production systems.
//   -  Uses std::cout for simplicity, but in a real application, a proper
//      logging library (e.g., spdlog) should be used.
template <typename T>
std::optional<size_t> binarySearchWithLogging(const std::vector<T>& arr, const T& target, const std::string& context) {
    if (arr.empty()) {
        std::cout << context << ": Array is empty" << std::endl;
        return {};
    }
    size_t left = 0;
    size_t right = arr.size() - 1;

    std::cout << context << ": Searching for " << target << " in array of size " << arr.size() << std::endl;
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        std::cout << context << ": Left: " << left << ", Right: " << right << ", Mid: " << mid << ", Value: " << arr[mid] << std::endl;

        if (arr[mid] == target) {
            std::cout << context << ": Found at index " << mid << std::endl;
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    std::cout << context << ": Not found" << std::endl;
    return {};
}

// 5.  Binary Search with Bounded Iteration
//    - Adds a maximum number of iterations to prevent infinite loops in cases where
//      the input data might be corrupted or the comparison is inconsistent.
//    -  This is a defensive programming technique.
template <typename T>
std::optional<size_t> binarySearchBounded(const std::vector<T>& arr, const T& target, size_t maxIterations) {
    if (arr.empty()) {
        return {};
    }
    size_t left = 0;
    size_t right = arr.size() - 1;
    size_t iterations = 0;

    while (left <= right && iterations < maxIterations) { // Check iteration count
        size_t mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
        iterations++;
    }
    if (iterations >= maxIterations) {
        std::cerr << "Warning: Maximum iterations reached.  Search may not have completed." << std::endl; // Use cerr for errors
    }
    return {}; // Not found or iteration limit reached
}

int main() {
    // Example usage
    std::vector<int> sortedArray = {2, 5, 7, 8, 11, 12, 13, 13, 13, 15};
    int targetValue = 13;

    // 1. Iterative Safe
    std::optional<size_t> index1 = binarySearchIterativeSafe(sortedArray, targetValue);
    if (index1.has_value()) {
        std::cout << "Iterative Safe: Target " << targetValue << " found at index: " << index1.value() << std::endl;
    } else {
        std::cout << "Iterative Safe: Target " << targetValue << " not found." << std::endl;
    }

    // 2. Recursive Safe
    try {
        size_t index2 = binarySearchRecursiveSafe(sortedArray, targetValue);
        std::cout << "Recursive Safe: Target " << targetValue << " found at index: " << index2 << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Recursive Safe: " << e.what() << std::endl; // Use cerr for error messages
    }

    // 3. Custom Comparator
    std::vector<Person> people = {
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 20},
        {"David", 30}
    };
    std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) { return a.age < b.age; }); // Sort by age

    Person targetPerson = {"", 30};
    std::optional<size_t> index3 = binarySearchCustom(people, targetPerson, ComparePersonAge());
    if (index3.has_value()) {
        std::cout << "Custom Comparator: Person with age " << targetPerson.age << " found at index: " << index3.value() << std::endl;
    } else {
        std::cout << "Custom Comparator: Person with age " << targetPerson.age << " not found." << std::endl;
    }

   // 4. Logging
    std::optional<size_t> index4 = binarySearchWithLogging(sortedArray, targetValue, "Search Context");
    if (index4.has_value()) {
        std::cout << "Logging: Target " << targetValue << " found at index: " << index4.value() << std::endl;
    } else {
        std::cout << "Logging: Target " << targetValue << " not found." << std::endl;
    }

    // 5. Bounded Iteration
    std::optional<size_t> index5 = binarySearchBounded(sortedArray, targetValue, 10); // Limit to 10 iterations
      if (index5.has_value()) {
        std::cout << "Bounded Iteration: Target " << targetValue << " found at index: " << index5.value() << std::endl;
    } else {
        std::cout << "Bounded Iteration: Target " << targetValue << " not found." << std::endl;
    }

    // Example of not found
    std::optional<size_t> notFoundIndex = binarySearchIterativeSafe(sortedArray, 99);
    if (notFoundIndex.has_value()) {
        std::cout << "Iterative Safe: Target 99 found at index: " << notFoundIndex.value() << std::endl;
    } else {
        std::cout << "Iterative Safe: Target 99 not found." << std::endl;
    }

    // Example of exception being thrown
    try{
        size_t invalidSearch = binarySearchRecursiveSafe(sortedArray, 99);
        std::cout << "Should not reach here" << std::endl;
    } catch(const std::out_of_range& e){
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
