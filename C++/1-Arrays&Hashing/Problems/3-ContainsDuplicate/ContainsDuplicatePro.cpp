#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>   // for std::accumulate
#include <map>
#include <climits> // Include climits for INT_MAX and INT_MIN

using namespace std;

// 1. Using std::unordered_set (Most Efficient for Average Case)
//
//   * Time Complexity: O(n) - average case, O(n^2) - worst case (rare with good hash functions)
//   * Space Complexity: O(n)
//   * Real-world Use Case: Detecting duplicate entries in a database table (e.g., user IDs),
//       checking for duplicate files in a directory,  optimizing data processing pipelines
//       by quickly identifying redundant computations.
bool containsDuplicate_unorderedSet(const vector<int>& nums) {
    unordered_set<int> seen;
    for (int num : nums) {
        if (seen.find(num) != seen.end()) {
            return true;
        }
        seen.insert(num);
    }
    return false;
}

// 2. Using Sorting (Efficient for Sorted or Nearly Sorted Data)
//
//   * Time Complexity: O(n log n) - general case (std::sort), O(n) - if the array is already sorted
//   * Space Complexity: O(1) - if using an in-place sort like std::sort (usually introsort, which is a hybrid of quicksort, heapsort, and insertion sort),  O(n) in the worst case.
//   * Real-world Use Case: Detecting duplicates in a sorted list of IDs,
//        checking for duplicate entries in a log file where entries are ordered by timestamp,
//        data validation after sorting a dataset.
bool containsDuplicate_sorting(vector<int> nums) { // Copy the vector to avoid modifying the original
    sort(nums.begin(), nums.end());
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] == nums[i - 1]) {
            return true;
        }
    }
    return false;
}

// 3. Using a Hash Map (For Counting Duplicates, More Versatile)
//
//   * Time Complexity: O(n)
//   * Space Complexity: O(n)
//   * Real-world Use Case: Counting the frequency of duplicate entries (e.g., word count in a document),
//       finding elements that appear more than once,  implementing caching mechanisms.
bool containsDuplicate_hashMap(const vector<int>& nums) {
    map<int, int> counts; // Use map for ordered keys, can use unordered_map for slightly better performance if order doesn't matter
    for (int num : nums) {
        counts[num]++;
        if (counts[num] > 1) {
            return true;
        }
    }
    return false;
}

// 4. Using Nested Loops (Brute Force -  Mostly for Educational Purposes, VERY INEFFICIENT)
//
//   * Time Complexity: O(n^2)
//   * Space Complexity: O(1)
//   * Real-world Use Case:  This approach is generally *not* suitable for real-world projects
//       due to its poor performance.  It might be used in very specific, constrained scenarios
//       where the input size is extremely small and performance is not critical, or as a
//       baseline for comparing the performance of other algorithms (e.g., in a benchmarking test).
bool containsDuplicate_nestedLoops(const vector<int>& nums) {
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = i + 1; j < nums.size(); ++j) {
            if (nums[i] == nums[j]) {
                return true;
            }
        }
    }
    return false;
}

// 5. Using std::accumulate and a set (Illustrative, Not Always Optimal)
//
//   * Time Complexity:  O(n) for accumulate, O(n) for set insertion, so effectively O(n)
//   * Space Complexity: O(n)
//   * Real-world use case: This approach is less common in typical production code.  It's primarily
//     used to demonstrate functional programming concepts or alternative ways to process data.
//     It could be adapted for scenarios where you need to perform a cumulative check for duplicates
//     while processing a stream of data, but more efficient methods (like the basic unordered_set)
//     are usually preferred.  It's included here for completeness and to show different C++ features.
bool containsDuplicate_accumulate(const vector<int>& nums) {
    unordered_set<int> seen;
    return accumulate(nums.begin(), nums.end(), false,
                           [&seen](bool hasDuplicate, int num) {
                               if (hasDuplicate) return true; // Short-circuit if duplicate already found
                               if (seen.find(num) != seen.end()) {
                                   return true;
                               }
                               seen.insert(num);
                               return false;
                           });
}

int main() {
    vector<int> numbers1 = {1, 2, 3, 1};
    vector<int> numbers2 = {1, 2, 3, 4};
    vector<int> numbers3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    vector<int> numbers4 = {1};
    vector<int> numbers5 = {INT_MAX, INT_MIN, 0, INT_MAX}; // Use INT_MAX and INT_MIN from climits

    cout << "Numbers 1: ";
    for (int num : numbers1) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Unordered Set: " << (containsDuplicate_unorderedSet(numbers1) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Sorting:       " << (containsDuplicate_sorting(numbers1) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Hash Map:      " << (containsDuplicate_hashMap(numbers1) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Nested Loops:  " << (containsDuplicate_nestedLoops(numbers1) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Accumulate:    " << (containsDuplicate_accumulate(numbers1) ? "Has duplicates" : "No duplicates") << endl;


    cout << "\nNumbers 2: ";
    for (int num : numbers2) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Unordered Set: " << (containsDuplicate_unorderedSet(numbers2) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Sorting:       " << (containsDuplicate_sorting(numbers2) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Hash Map:      " << (containsDuplicate_hashMap(numbers2) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Nested Loops:  " << (containsDuplicate_nestedLoops(numbers2) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Accumulate:    " << (containsDuplicate_accumulate(numbers2) ? "Has duplicates" : "No duplicates") << endl;

    cout << "\nNumbers 3: ";
    for (int num : numbers3) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Unordered Set: " << (containsDuplicate_unorderedSet(numbers3) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Sorting:       " << (containsDuplicate_sorting(numbers3) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Hash Map:      " << (containsDuplicate_hashMap(numbers3) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Nested Loops:  " << (containsDuplicate_nestedLoops(numbers3) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Accumulate:    " << (containsDuplicate_accumulate(numbers3) ? "Has duplicates" : "No duplicates") << endl;

    cout << "\nNumbers 4: ";
    for (int num : numbers4) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Unordered Set: " << (containsDuplicate_unorderedSet(numbers4) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Sorting:       " << (containsDuplicate_sorting(numbers4) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Hash Map:      " << (containsDuplicate_hashMap(numbers4) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Nested Loops:  " << (containsDuplicate_nestedLoops(numbers4) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Accumulate:    " << (containsDuplicate_accumulate(numbers4) ? "Has duplicates" : "No duplicates") << endl;

    cout << "\nNumbers 5: ";
    for (int num : numbers5) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Unordered Set: " << (containsDuplicate_unorderedSet(numbers5) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Sorting:       " << (containsDuplicate_sorting(numbers5) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Hash Map:      " << (containsDuplicate_hashMap(numbers5) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Nested Loops:  " << (containsDuplicate_nestedLoops(numbers5) ? "Has duplicates" : "No duplicates") << endl;
    cout << "Accumulate:    " << (containsDuplicate_accumulate(numbers5) ? "Has duplicates" : "No duplicates") << endl;

    return 0;
}
