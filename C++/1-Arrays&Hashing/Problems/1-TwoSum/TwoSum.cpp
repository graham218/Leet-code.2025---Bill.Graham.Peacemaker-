#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // Required for std::sort

using namespace std;

// 1. Brute Force Approach
//    - Iterate through each element and check the sum with every other element.
//    - Time Complexity: O(n^2), Space Complexity: O(1)
vector<int> twoSum_BruteForce(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i + 1; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {}; // Return empty vector if no solution is found.  Good practice.
}

// 2. Hash Map Approach
//    - Store each number and its index in a hash map.
//    - For each number, check if (target - number) exists in the hash map.
//    - Time Complexity: O(n), Space Complexity: O(n)
vector<int> twoSum_HashMap(vector<int>& nums, int target) {
    unordered_map<int, int> numMap;
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], i};
        }
        numMap[nums[i]] = i;
    }
    return {};
}

// 3. Sorted Array and Two Pointers
//    - Sort the array.
//    - Use two pointers, one at the beginning and one at the end.
//    - Move pointers based on the sum of the elements they point to.
//    - Important:  This approach modifies the original array and doesn't return original indices.
//    - Time Complexity: O(n log n) for sorting, O(n) for two pointers, so O(n log n) overall
//    - Space Complexity: O(1) (or O(n) depending on the sorting algorithm implementation)
vector<int> twoSum_TwoPointers(vector<int> nums, int target) { // Pass by value to avoid modifying original
    sort(nums.begin(), nums.end()); // Sort the array
    int left = 0;
    int right = nums.size() - 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target) {
            //  Need to find the *values*, not the indices in the *sorted* array.
            //  The original indices are lost here.
            return {left, right}; //  Returning indices in the sorted array, NOT the original array.
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return {};
}

// 4.  HashMap with Early Exit
//     - Similar to the hash map approach, but checks for the complement *before* adding the current number to the map.
//     - This can be slightly more efficient in some cases.
//     - Time Complexity: O(n), Space Complexity: O(n)
vector<int> twoSum_HashMapEarlyExit(vector<int>& nums, int target) {
    unordered_map<int, int> numMap;
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        if (numMap.find(complement) != numMap.end()) {
            return {numMap[complement], i};
        }
        numMap[nums[i]] = i;
    }
    return {};
}

// 5. Using std::find (Less Efficient, Demonstrative)
//    - For each element, use std::find to search for the complement in the rest of the array.
//    - This is less efficient than the hash map approach but shows an alternative.
//    - Time Complexity: O(n^2) in the worst case (std::find is O(n) on average), Space Complexity: O(1)
vector<int> twoSum_Find(vector<int>& nums, int target) {
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        // std::find searches in the range [first, last).
        auto it = find(nums.begin() + i + 1, nums.end(), complement);
        if (it != nums.end()) {
            int j = distance(nums.begin(), it); // Get the index of the found element.
            return {i, j};
        }
    }
    return {};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    cout << "Input: nums = [";
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i < nums.size() - 1) {
            cout << ", ";
        }
    }
    cout << "], target = " << target << endl;

    cout << "Brute Force: ";
    vector<int> result1 = twoSum_BruteForce(nums, target);
    if (result1.empty()) cout << "No solution" << endl;
    else cout << "[" << result1[0] << ", " << result1[1] << "]" << endl;

    cout << "Hash Map: ";
    vector<int> result2 = twoSum_HashMap(nums, target);
     if (result2.empty()) cout << "No solution" << endl;
    else cout << "[" << result2[0] << ", " << result2[1] << "]" << endl;

    cout << "Two Pointers: ";
    vector<int> result3 = twoSum_TwoPointers(nums, target);
    if (result3.empty()) cout << "No solution" << endl;
    else cout << "[" << result3[0] << ", " << result3[1] << "]" << endl;

    cout << "Hash Map Early Exit: ";
    vector<int> result4 = twoSum_HashMapEarlyExit(nums, target);
    if (result4.empty()) cout << "No solution" << endl;
    else cout << "[" << result4[0] << ", " << result4[1] << "]" << endl;

    cout << "std::find: ";
    vector<int> result5 = twoSum_Find(nums, target);
    if (result5.empty()) cout << "No solution" << endl;
    else cout << "[" << result5[0] << ", " << result5[1] << "]" << endl;

    return 0;
}
