#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <set> // For std::set (Approach 5)

using namespace std;

// Approach 1: Using unordered_set for membership test
bool containsElement_unordered_set(const vector<int>& arr, int target) {
    // Create an unordered_set from the vector.  This is efficient for lookups.
    unordered_set<int> numSet(arr.begin(), arr.end());

    // Check if the target element is in the set.
    return numSet.find(target) != numSet.end();
}

// Approach 2: Using unordered_map for counting occurrences
unordered_map<int, int> countOccurrences_unordered_map(const vector<int>& arr) {
    // Create an unordered_map to store the frequency of each element.
    unordered_map<int, int> counts;

    // Iterate through the array and update the counts.
    for (int num : arr) {
        counts[num]++;
    }
    return counts;
}

// Approach 3: Find common elements between two vectors using unordered_set
vector<int> findCommonElements_unordered_set(const vector<int>& arr1, const vector<int>& arr2) {
    // Store elements of arr1 in a set for efficient lookup.
    unordered_set<int> set1(arr1.begin(), arr1.end());
    vector<int> commonElements;

    // Iterate through arr2 and check if each element is in set1.
    for (int num : arr2) {
        if (set1.find(num) != set1.end()) {
            commonElements.push_back(num);
            set1.erase(num); //prevent duplicates in result if arr2 has duplicate common elements
        }
    }
    return commonElements;
}

// Approach 4: Check for duplicates in a vector using unordered_set
bool hasDuplicates_unordered_set(const vector<int>& arr) {
    // Use a set to keep track of seen elements.
    unordered_set<int> seen;

    // Iterate through the array.
    for (int num : arr) {
        // If the element is already in the set, it's a duplicate.
        if (seen.find(num) != seen.end()) {
            return true;
        }
        // Otherwise, add the element to the set.
        seen.insert(num);
    }
    // If the loop finishes without finding a duplicate, return false.
    return false;
}

// Approach 5: Using std::set for sorted unique elements
vector<int> getUniqueSorted_set(const vector<int>& arr) {
    // Create a std::set, which automatically stores elements in sorted order and only keeps unique elements.
    set<int> uniqueSortedSet(arr.begin(), arr.end());

    // Convert the set to a vector for easier use.
    vector<int> result(uniqueSortedSet.begin(), uniqueSortedSet.end());
    return result;
}

int main() {
    // Example usage of the functions.
    vector<int> numbers = {1, 5, 2, 8, 5, 9, 2, 10};
    vector<int> numbers2 = {2, 5, 11, 15, 5};
    int target = 5;

    // Approach 1: Check if 'numbers' contains 'target'.
    cout << "Approach 1: Contains " << target << "? "
              << (containsElement_unordered_set(numbers, target) ? "Yes" : "No") << endl;

    // Approach 2: Count occurrences of each number in 'numbers'.
    cout << "Approach 2: Occurrences: " << endl;
    unordered_map<int, int> counts = countOccurrences_unordered_map(numbers);
    for (const auto& pair : counts) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Approach 3: Find common elements between 'numbers' and 'numbers2'.
    cout << "Approach 3: Common elements: ";
    vector<int> commonElements = findCommonElements_unordered_set(numbers, numbers2);
    for (int num : commonElements) {
        cout << num << " ";
    }
    cout << endl;

    // Approach 4: Check if 'numbers' has duplicates.
    cout << "Approach 4: Has duplicates? "
              << (hasDuplicates_unordered_set(numbers) ? "Yes" : "No") << endl;

     // Approach 5: Get unique sorted elements from 'numbers'.
    cout << "Approach 5: Unique sorted elements: ";
    vector<int> uniqueSorted = getUniqueSorted_set(numbers);
    for (int num : uniqueSorted) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
