#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <set>

using namespace std;

// Approach 1: Using a HashSet (unordered_set)
// - Time Complexity: O(n) - average case, O(n^2) worst case if there are many hash collisions
// - Space Complexity: O(n)
bool containsDuplicate_HashSet(const vector<int>& nums) {
    unordered_set<int> seen;
    for (int num : nums) {
        if (seen.find(num) != seen.end()) {
            return true; // Found a duplicate
        }
        seen.insert(num);
    }
    return false; // No duplicates found
}

// Approach 2: Using Sorting
// - Time Complexity: O(n log n)
// - Space Complexity: O(1) - if sort is done in place,  O(n) in the worst case for some sort implementations like merge sort.
bool containsDuplicate_Sorting(vector<int>& nums) {
    if (nums.empty()) return false;
    sort(nums.begin(), nums.end()); // Sort the array
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] == nums[i - 1]) {
            return true; // Found duplicates
        }
    }
    return false; // No duplicates
}

// Approach 3: Using a regular set
// - Time Complexity: O(n log n)
// - Space Complexity: O(n)
bool containsDuplicate_Set(const vector<int>& nums) {
    set<int> seen;
    for(int num : nums){
        if(seen.find(num) != seen.end()){
            return true;
        }
        seen.insert(num);
    }
    return false;
}

// Approach 4:  Brute Force (Nested Loops) - (Time Limit Exceeded on LeetCode)
// - Time Complexity: O(n^2)
// - Space Complexity: O(1)
bool containsDuplicate_BruteForce(const vector<int>& nums) {
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = i + 1; j < nums.size(); ++j) {
            if (nums[i] == nums[j]) {
                return true; // Found a duplicate
            }
        }
    }
    return false; // No duplicates
}

// Approach 5: Using std::adjacent_find after sorting
// - Time Complexity: O(n log n)
// - Space Complexity: O(1)  (if sort is in place), O(n) otherwise
bool containsDuplicate_AdjacentFind(vector<int>& nums) {
    if (nums.empty()) return false;
    sort(nums.begin(), nums.end());
    return adjacent_find(nums.begin(), nums.end()) != nums.end();
}

int main() {
    // Example usage
    vector<int> numbers1 = {1, 2, 3, 1};
    vector<int> numbers2 = {1, 2, 3, 4};
    vector<int> numbers3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};

    cout << "Test Case 1: {1, 2, 3, 1}\n";
    cout << "HashSet: " << (containsDuplicate_HashSet(numbers1) ? "true" : "false") << endl;
    cout << "Sorting: " << (containsDuplicate_Sorting(numbers1) ? "true" : "false") << endl;
    cout << "Set: " << (containsDuplicate_Set(numbers1) ? "true" : "false") << endl;
    cout << "Brute Force: " << (containsDuplicate_BruteForce(numbers1) ? "true" : "false") << endl;
    cout << "Adjacent Find: " << (containsDuplicate_AdjacentFind(numbers1) ? "true" : "false") << endl;


    cout << "\nTest Case 2: {1, 2, 3, 4}\n";
    cout << "HashSet: " << (containsDuplicate_HashSet(numbers2) ? "true" : "false") << endl;
    cout << "Sorting: " << (containsDuplicate_Sorting(numbers2) ? "true" : "false") << endl;
    cout << "Set: " << (containsDuplicate_Set(numbers2) ? "true" : "false") << endl;
    cout << "Brute Force: " << (containsDuplicate_BruteForce(numbers2) ? "true" : "false") << endl;
    cout << "Adjacent Find: " << (containsDuplicate_AdjacentFind(numbers2) ? "true" : "false") << endl;

    cout << "\nTest Case 3: {1, 1, 1, 3, 3, 4, 3, 2, 4, 2}\n";
    cout << "HashSet: " << (containsDuplicate_HashSet(numbers3) ? "true" : "false") << endl;
    cout << "Sorting: " << (containsDuplicate_Sorting(numbers3) ? "true" : "false") << endl;
    cout << "Set: " << (containsDuplicate_Set(numbers3) ? "true" : "false") << endl;
    cout << "Brute Force: " << (containsDuplicate_BruteForce(numbers3) ? "true" : "false") << endl;
    cout << "Adjacent Find: " << (containsDuplicate_AdjacentFind(numbers3) ? "true" : "false") << endl;

    return 0;
}
