#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Approach 1: XOR (Exclusive OR)
// The XOR operation has the property that a ^ a = 0 and a ^ 0 = a.
// We can XOR all the numbers in the array. The duplicate numbers will cancel each other out,
// and the single number will remain.
int singleNumber_XOR(vector<int>& nums) {
    int result = 0;
    for (int num : nums) {
        result ^= num;
    }
    return result;
}

// Approach 2: Sum of Set - Sum of Array
// 1. Insert all unique elements into a set.
// 2. Calculate the sum of the elements in the set.
// 3. Multiply the sum of the set by 2 (because each unique element appears twice in the array, except the single number).
// 4. Calculate the sum of all elements in the array.
// 5. Subtract the sum of the array from twice the sum of the set.  This will give us the single number.
int singleNumber_SumSet(vector<int>& nums) {
    unordered_set<int> unique_nums(nums.begin(), nums.end()); // Store unique numbers
    long long sumOfSet = accumulate(unique_nums.begin(), unique_nums.end(), 0LL); // Sum of unique numbers. Use long long to prevent overflow
    long long sumOfArray = accumulate(nums.begin(), nums.end(), 0LL);           // Sum of all numbers. Use long long to prevent overflow
    return static_cast<int>(2 * sumOfSet - sumOfArray); // Cast back to int
}

// Approach 3: Using a Hash Set
// 1. Create an empty hash set.
// 2. Iterate through the array.
// 3. If the number is already in the set, remove it.
// 4. If the number is not in the set, add it.
// 5. The only number remaining in the set is the single number.
int singleNumber_HashSet(vector<int>& nums) {
    unordered_set<int> numSet;
    for (int num : nums) {
        if (numSet.find(num) != numSet.end()) { // If found
            numSet.erase(num);             // Remove it
        } else {
            numSet.insert(num);            // Otherwise insert
        }
    }
    return *numSet.begin(); // Return the first (and only) element.
}

// Approach 4: Using std::accumulate with a lambda (similar to XOR)
// This approach uses the std::accumulate function with a custom lambda function
// to perform the XOR operation on all elements of the vector.  It's functionally
// identical to the first approach, but demonstrates a different way to achieve it.
int singleNumber_Accumulate(vector<int>& nums) {
    return accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
}

// Approach 5: Sorting
// 1. Sort the array.
// 2. Iterate through the sorted array, comparing adjacent elements.
// 3. If two adjacent elements are different, the first one is the single number
//    (unless it's the last element, in which case it's the single number).
// This approach modifies the original array.
int singleNumber_Sort(vector<int>& nums) {
    if (nums.size() == 1) return nums[0]; //handle the single element case
    sort(nums.begin(), nums.end());
    for (size_t i = 0; i < nums.size() - 1; i += 2) {
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return nums.back(); // If the single number is the last element
}

int main() {
    vector<int> nums = {4, 1, 2, 1, 2};

    cout << "Input: [";
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i < nums.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    cout << "Single Number (XOR): " << singleNumber_XOR(nums) << endl;
    cout << "Single Number (Sum of Set): " << singleNumber_SumSet(nums) << endl;
    cout << "Single Number (Hash Set): " << singleNumber_HashSet(nums) << endl;
    cout << "Single Number (Accumulate): " << singleNumber_Accumulate(nums) << endl;
    cout << "Single Number (Sort): " << singleNumber_Sort(nums) << endl;

    return 0;
}
