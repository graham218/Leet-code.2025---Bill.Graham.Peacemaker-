#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <tuple>
#include <chrono>
#include <random>
#include <set>
#include <functional> // Include the functional header

using namespace std;
using namespace std::chrono;

// Function to generate random integers within a specified range
vector<int> generateRandomIntegers(int count, int minVal, int maxVal) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minVal, maxVal);
    vector<int> numbers(count);
    for (int i = 0; i < count; ++i) {
        numbers[i] = dist(gen);
    }
    return numbers;
}

// 1. Two Pointers Approach (Optimized)
//   - Time Complexity: O(n^2)
//   - Space Complexity: O(1) (excluding the output vector)
//   - Suitable for: General use when you need an efficient solution and modifying the input array is acceptable.
vector<vector<int>> threeSum_twoPointers(vector<int>& nums) {
    vector<vector<int>> result;
    int n = nums.size();
    if (n < 3) return result;

    sort(nums.begin(), nums.end()); // Crucial for the two-pointer approach

    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicate 'a'

        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                // Skip duplicate 'b' and 'c'
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return result;
}

// 2. Hashing Approach
//   - Time Complexity: O(n^2) on average, O(n^3) in the worst case
//   - Space Complexity: O(n)
//   - Suitable for: When you want to avoid sorting the input array, or when you need to quickly check for the existence of a third number.  Can be less efficient if there are many hash collisions.
vector<vector<int>> threeSum_hashing(vector<int>& nums) {
    vector<vector<int>> result;
    int n = nums.size();
    if (n < 3) return result;

    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            unordered_set<int> seen;
            for(int k = j + 1; k < n; ++k){
                int target = -(nums[i] + nums[j]);
                if (seen.find(target) != seen.end()) {
                    vector<int> triplet = {nums[i], nums[j], target};
                    sort(triplet.begin(), triplet.end()); // Ensure unique triplets are handled correctly
                    if (find(result.begin(), result.end(), triplet) == result.end()){ // avoid duplicates
                         result.push_back(triplet);
                    }
                }
                seen.insert(nums[k]);
            }
        }
    }
    return result;
}

// 3. Using set and tuple
//   - Time Complexity: O(n^2 log n)  due to the set insertion
//   - Space Complexity: O(n)
//   - Suitable for: When you need to ensure unique triplets and don't want to sort the input array.
vector<vector<int>> threeSum_setAndTuple(vector<int>& nums) {
    set<tuple<int, int, int>> uniqueTriplets;
    vector<vector<int>> result;
    int n = nums.size();
    if (n < 3) return result;

    for (int i = 0; i < n - 2; ++i) {
        unordered_set<int> seen;
        for (int j = i + 1; j < n; ++j) {
            int complement = -(nums[i] + nums[j]);
            if (seen.find(complement) != seen.end()) {
                int a = nums[i], b = nums[j], c = complement;
                // Ensure the triplet is ordered to handle duplicates correctly in the set.
                if (a > b) swap(a, b);
                if (a > c) swap(a, c);
                if (b > c) swap(b, c);
                uniqueTriplets.insert(make_tuple(a, b, c));
            }
            seen.insert(nums[j]);
        }
    }
    for (const auto& triplet : uniqueTriplets) {
        result.push_back({get<0>(triplet), get<1>(triplet), get<2>(triplet)});
    }
    return result;
}

// 4. Divide and Conquer Approach (Less practical for this problem, but shows the technique)
//   - Time Complexity: O(n^2 log n)
//   - Space Complexity: O(n log n)
//   - Suitable for: Demonstrating divide and conquer, but generally *not* recommended for the 3Sum problem due to its overhead.  Divide and conquer is better suited for problems that can be broken down into truly independent subproblems.
vector<vector<int>> threeSum_divideAndConquer(vector<int>& nums) {
    vector<vector<int>> result;
    int n = nums.size();
    if (n < 3) return result;

    sort(nums.begin(), nums.end()); // Sorting is still needed for the 2-sum part

    std::function<void(int, int)> solve = [&](int left, int right) { // Fix: Added std::
        if (right - left < 2) return; // Base case: less than 3 elements

        int mid = left + (right - left) / 2;
        solve(left, mid);
        solve(mid, right);

        // Find triplets that cross the midpoint
        for (int i = left; i < mid; ++i) {
            for (int j = mid; j < right; ++j) {
                int target = -(nums[i] + nums[j]);
                // Search for the third number in the entire range.
                for(int k = 0; k < n; ++k){
                    if(k != i && k != j && nums[k] == target){
                         vector<int> triplet = {nums[i], nums[j], target};
                         sort(triplet.begin(), triplet.end());
                         if (find(result.begin(), result.end(), triplet) == result.end()){
                            result.push_back(triplet);
                         }
                         break; // Important:  Once found, break to avoid duplicates
                    }
                }
            }
        }
    };
    solve(0, n);
    return result;
}

// 5. Binary Search Approach
//   - Time Complexity: O(n^2 log n)
//   - Space Complexity: O(1)
//   - Suitable for: When the input array is already sorted or sorting is acceptable, and you want to avoid extra space.
vector<vector<int>> threeSum_binarySearch(vector<int>& nums) {
    vector<vector<int>> result;
    int n = nums.size();
    if (n < 3) return result;

    sort(nums.begin(), nums.end()); // Sorting is essential for binary search

    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates

        for (int j = i + 1; j < n - 1; ++j) {
             if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            int target = -(nums[i] + nums[j]);

            // Use binary search to find the third number
            int left = j + 1;
            int right = n - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (nums[mid] == target) {
                    result.push_back({nums[i], nums[j], nums[mid]});
                    break; // Important: Break after finding a solution
                } else if (nums[mid] < target) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
    }
    return result;
}

// Function to print the result
void printResult(const vector<vector<int>>& result) {
    cout << "[\n";
    for (const auto& triplet : result) {
        cout << "  [" << triplet[0] << ", " << triplet[1] << ", " << triplet[2] << "],\n";
    }
    cout << "]\n";
}

int main() {
    // Example usage and testing
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    cout << "Input: [-1, 0, 1, 2, -1, -4]\n";

    // 1. Two Pointers Approach
    cout << "\n1. Two Pointers Approach:\n";
    vector<int> nums1 = nums; // Create a copy to avoid modifying the original
    auto start = high_resolution_clock::now();
    vector<vector<int>> result1 = threeSum_twoPointers(nums1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printResult(result1);
    cout << "Time taken: " << duration.count() << " microseconds\n";
     cout << "Modified Input: " << (nums1 == nums ? "No" : "Yes") << endl;


    // 2. Hashing Approach
    cout << "\n2. Hashing Approach:\n";
    vector<int> nums2 = nums;
    start = high_resolution_clock::now();
    vector<vector<int>> result2 = threeSum_hashing(nums2);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    printResult(result2);
    cout << "Time taken: " << duration.count() << " microseconds\n";
    cout << "Modified Input: " << (nums2 == nums ? "No" : "Yes") << endl;

    // 3. Set and Tuple Approach
    cout << "\n3. Set and Tuple Approach:\n";
    vector<int> nums3 = nums;
    start = high_resolution_clock::now();
    vector<vector<int>> result3 = threeSum_setAndTuple(nums3);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    printResult(result3);
    cout << "Time taken: " << duration.count() << " microseconds\n";
    cout << "Modified Input: " << (nums3 == nums ? "No" : "Yes") << endl;

    // 4. Divide and Conquer Approach (Less Efficient)
    cout << "\n4. Divide and Conquer Approach:\n";
    vector<int> nums4 = nums;
    start = high_resolution_clock::now();
    vector<vector<int>> result4 = threeSum_divideAndConquer(nums4);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    printResult(result4);
    cout << "Time taken: " << duration.count() << " microseconds\n";
    cout << "Modified Input: " << (nums4 == nums ? "No" : "Yes") << endl;

    // 5. Binary Search Approach
    cout << "\n5. Binary Search Approach:\n";
    vector<int> nums5 = nums;
    start = high_resolution_clock::now();
    vector<vector<int>> result5 = threeSum_binarySearch(nums5);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    printResult(result5);
    cout << "Time taken: " << duration.count() << " microseconds\n";
     cout << "Modified Input: " << (nums5 == nums ? "No" : "Yes") << endl;

    // Test with a larger random input
    int largeInputSize = 1000;
    vector<int> largeInput = generateRandomIntegers(largeInputSize, -500, 500);

    cout << "\nTesting with a large random input of size " << largeInputSize << ":\n";
    vector<int> nums6 = largeInput;
    start = high_resolution_clock::now();
    vector<vector<int>> result6 = threeSum_twoPointers(nums6); // Using the most efficient approach for large input
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken for Two Pointers Approach: " << duration.count() << " microseconds\n";
    cout << "Number of triplets found: " << result6.size() << endl;

    return 0;
}
