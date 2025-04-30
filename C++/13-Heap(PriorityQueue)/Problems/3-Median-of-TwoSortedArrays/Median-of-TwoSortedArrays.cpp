#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>  // Required for numeric_limits

using namespace std;

// Function to calculate the median of a sorted vector
double getMedian(const vector<int>& arr) {
    int n = arr.size();
    if (n == 0) {
        return 0.0; // Handle empty array case
    }
    if (n % 2 == 0) {
        // Even number of elements: average of the two middle elements
        return (double)(arr[n / 2 - 1] + arr[n / 2]) / 2.0;
    } else {
        // Odd number of elements: the middle element
        return (double)arr[n / 2];
    }
}

// Approach 1: Merge and Find Median
// Time Complexity: O(m+n)
// Space Complexity: O(m+n)
double findMedianSortedArrays_Merge(const vector<int>& nums1, const vector<int>& nums2) {
    vector<int> merged;
    int i = 0, j = 0;
    int m = nums1.size(), n = nums2.size();

    // Merge the two sorted arrays into a single sorted array
    while (i < m && j < n) {
        if (nums1[i] <= nums2[j]) {
            merged.push_back(nums1[i++]);
        } else {
            merged.push_back(nums2[j++]);
        }
    }
    while (i < m) {
        merged.push_back(nums1[i++]);
    }
    while (j < n) {
        merged.push_back(nums2[j++]);
    }

    // Calculate the median of the merged array
    return getMedian(merged);
}

// Approach 2: Iterative Merge without Extra Space (Optimized Merge)
// Time Complexity: O(m+n)
// Space Complexity: O(1) - constant extra space
double findMedianSortedArrays_Iterative(const vector<int>& nums1, const vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    int total = m + n;
    int i = 0, j = 0;
    int mid1 = 0, mid2 = 0; // Store the two middle elements

    // Iterate until we reach the middle of the combined array
    for (int count = 0; count <= total / 2; count++) {
        mid2 = mid1; // Store the previous middle
        if (i < m && (j >= n || nums1[i] <= nums2[j])) {
            mid1 = nums1[i++];
        } else {
            mid1 = nums2[j++];
        }
    }

    // Calculate the median based on whether the total number of elements is even or odd
    if (total % 2 == 0) {
        return (double)(mid1 + mid2) / 2.0;
    } else {
        return (double)mid1;
    }
}

// Approach 3: Binary Search (Efficient)
// Time Complexity: O(log(min(m,n)))
// Space Complexity: O(1)
double findMedianSortedArrays_BinarySearch(const vector<int>& nums1, const vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    // Ensure nums1 is the smaller array to optimize binary search
    if (m > n) {
        return findMedianSortedArrays_BinarySearch(nums2, nums1);
    }

    int low = 0, high = m;
    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = ((m + n + 1) / 2) - partitionX;

        // Get the max/min elements for the partitions.  Handle edge cases.
        int maxLeftX = (partitionX == 0) ? numeric_limits<int>::lowest() : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? numeric_limits<int>::max() : nums1[partitionX];
        int maxLeftY = (partitionY == 0) ? numeric_limits<int>::lowest() : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? numeric_limits<int>::max() : nums2[partitionY];

        // Check if we have found the correct partition
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            // Calculate the median
            if ((m + n) % 2 == 0) {
                return (double)(max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
            } else {
                return (double)max(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            // Move towards the left in nums1
            high = partitionX - 1;
        } else {
            // Move towards the right in nums1
            low = partitionX + 1;
        }
    }
    // If the input arrays are not sorted, or any other invalid input,  we should handle it.
    return 0.0;
}

// Approach 4: Using Max Heap and Min Heap
// Time Complexity: O(log(min(m,n))) on average, O(m+n) worst case
// Space Complexity: O(m+n) in the worst case, O(min(m,n)) on average
double findMedianSortedArrays_Heaps(const vector<int>& nums1, const vector<int>& nums2) {
    priority_queue<int> maxHeap; // Stores the left part of the merged array
    priority_queue<int, vector<int>, greater<int>> minHeap; // Stores the right part

    for (int num : nums1) maxHeap.push(num);
    for (int num : nums2) maxHeap.push(num); //can be optimized to push only until size is half of combined array

    //Pop half of the elements to minHeap
     int total = nums1.size() + nums2.size();
     for(int i = 0; i < total/2; ++i){
        minHeap.push(maxHeap.top());
        maxHeap.pop();
     }
    // Calculate the median
    if (total % 2 == 0) {
        return (double)(maxHeap.top() + minHeap.top()) / 2.0;
    } else {
        return (double)maxHeap.top();
    }
}

// Approach 5: Using std::nth_element (Partial Sort)
// Time Complexity: O(m+n) on average, O(m*n) worst case
// Space Complexity: O(1)
double findMedianSortedArrays_NthElement(const vector<int>& nums1, const vector<int>& nums2) {
    vector<int> merged(nums1);
    merged.insert(merged.end(), nums2.begin(), nums2.end()); // O(m+n)

    int n = merged.size();
    if (n % 2 == 0) {
        // Use nth_element to find the two middle elements
        nth_element(merged.begin(), merged.begin() + n / 2 - 1, merged.end());
        nth_element(merged.begin(), merged.begin() + n / 2, merged.end());
        return (double)(merged[n / 2 - 1] + merged[n / 2]) / 2.0;
    } else {
        // Use nth_element to find the middle element
        nth_element(merged.begin(), merged.begin() + n / 2, merged.end());
        return (double)merged[n / 2];
    }
}

int main() {
    vector<int> nums1 = {1, 3, 8, 9, 15};
    vector<int> nums2 = {7, 11, 18, 19, 21, 25};

    cout << "Array 1: ";
    for (int num : nums1) cout << num << " ";
    cout << endl;
    cout << "Array 2: ";
    for (int num : nums2) cout << num << " ";
    cout << endl;

    cout << "Median (Merge): " << findMedianSortedArrays_Merge(nums1, nums2) << endl;
    cout << "Median (Iterative): " << findMedianSortedArrays_Iterative(nums1, nums2) << endl;
    cout << "Median (Binary Search): " << findMedianSortedArrays_BinarySearch(nums1, nums2) << endl;
    cout << "Median (Heaps): " << findMedianSortedArrays_Heaps(nums1, nums2) << endl;
    cout << "Median (Nth Element): " << findMedianSortedArrays_NthElement(nums1, nums2) << endl;

    return 0;
}
