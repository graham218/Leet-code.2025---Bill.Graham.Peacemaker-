#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <functional> // Include for std::function

using namespace std;

// Approach 1: Brute Force
// Time Complexity: O(n^3)
// Space Complexity: O(1) (excluding the space for the result)
vector<vector<int>> threeSum_bruteForce(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> result_set; // Use a set to avoid duplicate triplets
    vector<vector<int>> result;

    if (n < 3) {
        return result; // Return empty result if there are less than 3 elements.
    }

    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    vector<int> triplet = {nums[i], nums[j], nums[k]};
                    sort(triplet.begin(), triplet.end()); // Sort to handle duplicates
                    result_set.insert(triplet);
                }
            }
        }
    }

    // Convert the set of triplets to a vector of vectors.
    for (const auto& triplet : result_set) {
        result.push_back(triplet);
    }
    return result;
}

// Approach 2: Using Sorting and Two Pointers
// Time Complexity: O(n^2)
// Space Complexity: O(1) (excluding the space for the result)
vector<vector<int>> threeSum_twoPointers(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;
    if (n < 3) return result;

    sort(nums.begin(), nums.end()); // Sort the array

    for (int i = 0; i < n - 2; ++i) {
        // Skip duplicate 'a' values
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        int left = i + 1;
        int right = n - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});

                // Skip duplicate 'b' and 'c' values
                while (left < right && nums[left] == nums[left + 1]) {
                    left++;
                }
                while (left < right && nums[right] == nums[right - 1]) {
                    right--;
                }
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

// Approach 3: Using Hashing (unordered_map)
// Time Complexity: O(n^2) on average, O(n^3) in the worst case
// Space Complexity: O(n)
vector<vector<int>> threeSum_hashing(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> result_set; // Use set to avoid duplicates
    vector<vector<int>> result;
    if (n < 3) return result;

    for (int i = 0; i < n - 2; ++i) {
        unordered_map<int, int> numMap; // Map to store numbers and their indices
        for (int j = i + 1; j < n; ++j) {
            int complement = -(nums[i] + nums[j]);
            if (numMap.find(complement) != numMap.end()) {
                vector<int> triplet = {nums[i], nums[j], complement};
                sort(triplet.begin(), triplet.end());
                result_set.insert(triplet);
            }
            numMap[nums[j]] = j;
        }
    }
      for (const auto& triplet : result_set) {
        result.push_back(triplet);
    }
    return result;
}

// Approach 4: Optimized Brute Force (Slightly better than pure brute force)
// Time Complexity: O(n^3)
// Space Complexity: O(1)
vector<vector<int>> threeSum_optimizedBruteForce(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> result_set;
    vector<vector<int>> result;

    if (n < 3) {
        return result;
    }

    sort(nums.begin(), nums.end()); // Sort to skip some duplicates

    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicate 'a'

        for (int j = i + 1; j < n - 1; ++j) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue; // Skip duplicate 'b'

            for (int k = j + 1; k < n; ++k) {
                if (k > j + 1 && nums[k] == nums[k - 1]) continue; // Skip duplicate 'c'
                if (nums[i] + nums[j] + nums[k] == 0) {
                    result_set.insert({nums[i], nums[j], nums[k]});
                }
            }
        }
    }
    for (const auto& triplet : result_set) {
        result.push_back(triplet);
    }
    return result;
}

// Approach 5: Using Recursion and Two Pointers
// Time Complexity: O(n^2)
// Space Complexity: O(n) due to recursion stack
vector<vector<int>> threeSum_recursive(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;
    if (n < 3) return result;

    sort(nums.begin(), nums.end());

    std::function<void(int, int, int)> findTriplets =  // Corrected declaration of findTriplets
        [&](int i, int left, int right) {
        if (left >= right) return;
        int sum = nums[i] + nums[left] + nums[right];
        if (sum == 0) {
            result.push_back({nums[i], nums[left], nums[right]});
            while (left < right && nums[left] == nums[left + 1]) left++;
            while (left < right && nums[right] == nums[right - 1]) right--;
            findTriplets(i, left + 1, right - 1);
        } else if (sum < 0) {
            findTriplets(i, left + 1, right);
        } else {
            findTriplets(i, left, right - 1);
        }
    };

    for (int i = 0; i < n - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        findTriplets(i, i + 1, n - 1);
    }
    return result;
}

int main() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};

    cout << "Input: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl << endl;

    cout << "Approach 1: Brute Force" << endl;
    vector<vector<int>> result1 = threeSum_bruteForce(nums);
    for (const auto& triplet : result1) {
        cout << "[";
        for (int val : triplet) {
            cout << val << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;

    cout << "Approach 2: Two Pointers" << endl;
    vector<vector<int>> result2 = threeSum_twoPointers(nums);
    for (const auto& triplet : result2) {
        cout << "[";
        for (int val : triplet) {
            cout << val << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;

    cout << "Approach 3: Hashing" << endl;
    vector<vector<int>> result3 = threeSum_hashing(nums);
    for (const auto& triplet : result3) {
        cout << "[";
        for (int val : triplet) {
            cout << val << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;

    cout << "Approach 4: Optimized Brute Force" << endl;
    vector<vector<int>> result4 = threeSum_optimizedBruteForce(nums);
    for (const auto& triplet : result4) {
        cout << "[";
        for (int val : triplet) {
            cout << val << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;

    cout << "Approach 5: Recursion and Two Pointers" << endl;
    vector<vector<int>> result5 = threeSum_recursive(nums);
    for (const auto& triplet : result5) {
        cout << "[";
        for (int val : triplet) {
            cout << val << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;

    return 0;
}
