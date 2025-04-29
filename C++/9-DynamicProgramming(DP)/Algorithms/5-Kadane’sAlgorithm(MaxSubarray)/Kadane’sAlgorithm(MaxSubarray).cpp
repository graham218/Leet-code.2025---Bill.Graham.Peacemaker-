#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> // For INT_MIN

using namespace std;

// 1. Kadane's Algorithm (Standard) - Most efficient and common
//   - Time Complexity: O(n)
//   - Space Complexity: O(1)
int kadaneStandard(const vector<int>& nums) {
    int maxSoFar = INT_MIN; // Initialize with the smallest possible integer
    int maxEndingHere = 0;

    for (int num : nums) {
        maxEndingHere = max(num, maxEndingHere + num); // 핵심
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

// 2. Kadane's Algorithm with Start and End Index Tracking
//   - Time Complexity: O(n)
//   - Space Complexity: O(1)
//   - Tracks the start and end indices of the maximum subarray.
pair<int, pair<int, int>> kadaneWithIndex(const vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    int start = 0;
    int end = 0;
    int currentStart = 0;

    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > maxEndingHere + nums[i]) {
            maxEndingHere = nums[i];
            currentStart = i; // Start a new subarray
        } else {
            maxEndingHere += nums[i];
        }

        if (maxEndingHere > maxSoFar) {
            maxSoFar = maxEndingHere;
            start = currentStart;
            end = i;
        }
    }
    return {maxSoFar, {start, end}};
}

// 3. Kadane's Algorithm (Verbose) - Detailed explanation within the loop
//   - Time Complexity: O(n)
//   - Space Complexity: O(1)
int kadaneVerbose(const vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;

    for (int i = 0; i < nums.size(); ++i) {
        int num = nums[i];
        // 핵심 아이디어:
        // 1. 현재 원소가 양수일 경우, 이전까지의 합에 더하는 것이 이득일 수 있다.
        // 2. 현재 원소가 음수일 경우, 이전까지의 합이 음수라면, 새로운 시작점을 찾는 것이 더 나을 수 있다.
        // maxEndingHere는 현재 위치에서 끝나는 최대 부분 배열의 합을 저장한다.
        maxEndingHere = max(num, maxEndingHere + num);

        // maxSoFar는 지금까지 찾은 최대 부분 배열의 합을 저장한다.
        maxSoFar = max(maxSoFar, maxEndingHere);

        cout << "i: " << i << ", num: " << num << ", maxEndingHere: " << maxEndingHere << ", maxSoFar: " << maxSoFar << endl;
    }
    return maxSoFar;
}

// 4. Kadane's Algorithm with Negative Number Handling
//   - Time Complexity: O(n)
//   - Space Complexity: O(1)
//   - Handles arrays where all numbers might be negative.
int kadaneNegative(const vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    bool allNegative = true;

    for (int num : nums) {
        if (num > 0) {
            allNegative = false; // 배열에 양수가 하나라도 있으면 false
            break;
        }
    }

    if (allNegative) {
        // If all numbers are negative, return the largest negative number
        for (int num : nums) {
            maxSoFar = max(maxSoFar, num);
        }
        return maxSoFar;
    } else {
        // Otherwise, apply standard Kadane's algorithm
        for (int num : nums) {
            maxEndingHere = max(num, maxEndingHere + num);
            maxSoFar = max(maxSoFar, maxEndingHere);
        }
        return maxSoFar;
    }
}

// 5. Kadane's Algorithm (Divide and Conquer - for comparison, not as efficient)
//   - Time Complexity: O(n log n) - Divide and Conquer generally has this complexity
//   - Space Complexity: O(log n) - Due to the recursion stack
int maxCrossingSum(const vector<int>& nums, int low, int mid, int high) {
    // Include elements on the left of mid.
    int sum = 0;
    int leftSum = INT_MIN;
    for (int i = mid; i >= low; i--) {
        sum = sum + nums[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    // Include elements on the right of mid
    sum = 0;
    int rightSum = INT_MIN;
    for (int i = mid + 1; i <= high; i++) {
        sum = sum + nums[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    // Return sum of the two parts
    return leftSum + rightSum;
}

// Recursive function to find the maximum subarray sum using divide and conquer
int maxSubarraySum(const vector<int>& nums, int low, int high) {
    if (low == high)
        return nums[low];

    int mid = (low + high) / 2;

    // Return the maximum of the following three sums:
    // 1. Maximum subarray sum in the left half
    // 2. Maximum subarray sum in the right half
    // 3. Maximum subarray sum that crosses the midpoint
    return max(max(maxSubarraySum(nums, low, mid),
                       maxSubarraySum(nums, mid + 1, high)),
                   maxCrossingSum(nums, low, mid, high));
}

int kadaneDivideAndConquer(const vector<int>& nums) {
    if (nums.empty()) return 0;
    return maxSubarraySum(nums, 0, nums.size() - 1);
}

int main() {
    vector<int> nums1 = {-2, -3, 4, -1, -2, 1, 5, -3};
    vector<int> nums2 = {1, 2, 3, 4, 5};
    vector<int> nums3 = {-1, -2, -3, -4, -5};
    vector<int> nums4 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    vector<int> nums5 = {5, 4, -1, 7, 8};

    cout << "Kadane's Algorithm (Standard):" << endl;
    cout << "Max subarray sum for nums1: " << kadaneStandard(nums1) << endl; // Output: 7
    cout << "Max subarray sum for nums2: " << kadaneStandard(nums2) << endl; // Output: 15
    cout << "Max subarray sum for nums3: " << kadaneStandard(nums3) << endl; // Output: -1
    cout << "Max subarray sum for nums4: " << kadaneStandard(nums4) << endl; // Output: 6
    cout << "Max subarray sum for nums5: " << kadaneStandard(nums5) << endl; // Output: 23

    cout << "\nKadane's Algorithm with Index Tracking:" << endl;
    pair<int, pair<int, int>> result1 = kadaneWithIndex(nums1);
    cout << "Max subarray sum for nums1: " << result1.first << ", Start index: " << result1.second.first << ", End index: " << result1.second.second << endl; // Output: 7, 2, 6

    cout << "\nKadane's Algorithm (Verbose):" << endl;
    cout << "Max subarray sum for nums1: " << kadaneVerbose(nums1) << endl; // Output: 7

    cout << "\nKadane's Algorithm with Negative Number Handling:" << endl;
    cout << "Max subarray sum for nums1: " << kadaneNegative(nums1) << endl; // Output: 7
    cout << "Max subarray sum for nums3: " << kadaneNegative(nums3) << endl; // Output: -1

    cout << "\nKadane's Algorithm (Divide and Conquer):" << endl;
    cout << "Max subarray sum for nums1: " << kadaneDivideAndConquer(nums1) << endl; // Output: 7
    cout << "Max subarray sum for nums2: " << kadaneDivideAndConquer(nums2) << endl; // Output: 15

    return 0;
}

