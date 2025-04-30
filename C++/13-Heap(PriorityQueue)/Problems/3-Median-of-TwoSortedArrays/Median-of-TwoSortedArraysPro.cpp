#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <iomanip> // Required for std::setprecision

using namespace std;

// Function to print the array (for debugging purposes)
void printArray(const vector<int>& arr, const string& name) {
    cout << name << ": ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

// 1. Brute Force Approach: Merge and Sort
//   - Time Complexity: O(m + n) for merging, O((m + n) log (m + n)) for sorting
//   - Space Complexity: O(m + n) for the merged array
//   - Explanation: This is the most straightforward approach.  Merge the two sorted arrays into a single sorted array, and then find the median.  While simple, it's not the most efficient.
double findMedianSortedArrays_BruteForce(const vector<int>& nums1, const vector<int>& nums2) {
    vector<int> mergedArray;
    mergedArray.reserve(nums1.size() + nums2.size()); // Pre-allocate memory for efficiency

    // Merge the two sorted arrays
    int i = 0, j = 0;
    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] <= nums2[j]) {
            mergedArray.push_back(nums1[i++]);
        } else {
            mergedArray.push_back(nums2[j++]);
        }
    }
    while (i < nums1.size()) {
        mergedArray.push_back(nums1[i++]);
    }
    while (j < nums2.size()) {
        mergedArray.push_back(nums2[j++]);
    }

    // Sort the merged array (not needed because merge process already sorts)
    // sort(mergedArray.begin(), mergedArray.end());  // Redundant, already sorted

    int mergedSize = mergedArray.size();
    if (mergedSize % 2 == 0) {
        // Even number of elements: median is the average of the two middle elements
        return (double)(mergedArray[mergedSize / 2 - 1] + mergedArray[mergedSize / 2]) / 2.0;
    } else {
        // Odd number of elements: median is the middle element
        return (double)mergedArray[mergedSize / 2];
    }
}

// 2. Merge and Iterate Approach
//   - Time Complexity: O(m + n)
//   - Space Complexity: O(1) -  Uses a constant amount of extra space.
//   - Explanation:  Similar to the brute force approach, but instead of storing the entire merged array, we only keep track of the two middle elements (or one middle element if the total count is odd) as we iterate through the arrays. This significantly reduces the space complexity.
double findMedianSortedArrays_MergeIterate(const vector<int>& nums1, const vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    int total = m + n;
    int mid = total / 2;
    int i = 0, j = 0, count = 0;
    int first = 0, second = 0; // Store the two middle elements

    while (count <= mid) {
        second = first; // Keep track of the previous "first"
        if (i < m && j < n) {
            if (nums1[i] <= nums2[j]) {
                first = nums1[i++];
            } else {
                first = nums2[j++];
            }
        } else if (i < m) {
            first = nums1[i++];
        } else {
            first = nums2[j++];
        }
        count++;
    }

    if (total % 2 == 0) {
        return (double)(first + second) / 2.0;
    } else {
        return (double)first;
    }
}

// 3. Binary Search Approach
//   - Time Complexity: O(log(min(m, n)))
//   - Space Complexity: O(1)
//   - Explanation: This is the most efficient approach. It uses binary search to find the correct partition of the two arrays such that the median can be calculated from the elements around the partition.  It works by ensuring that the number of elements on the left side of the partition is equal to the number of elements on the right side.
double findMedianSortedArrays_BinarySearch(const vector<int>& nums1, const vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    // Ensure nums1 is the smaller array to optimize binary search
    if (m > n) {
        return findMedianSortedArrays_BinarySearch(nums2, nums1);
    }

    int low = 0, high = m;
    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = ((m + n + 1) / 2) - partitionX;

        // Get max/min elements for left and right sides.  Handle edge cases.
        int maxLeftX = (partitionX == 0) ? numeric_limits<int>::min() : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? numeric_limits<int>::max() : nums1[partitionX];
        int maxLeftY = (partitionY == 0) ? numeric_limits<int>::min() : nums2[partitionY - 1];
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
            // Move towards the left side of nums1
            high = partitionX - 1;
        } else {
            // Move towards the right side of nums1
            low = partitionX + 1;
        }
    }
    // If the input arrays are not sorted, the loop will exit and return 0.0
    return 0.0;
}

// 4. Using Priority Queues (Max-Heap and Min-Heap)
//   - Time Complexity: O((m+n)log(m+n)).  Adding elements to heaps is log(n).
//   - Space Complexity: O(m + n) in the worst case, to store all elements in the heaps.
//   - Explanation: This approach uses two priority queues (heaps): a max-heap to store the left half of the merged array and a min-heap to store the right half.  This method maintains the property that all elements in the max-heap are less than or equal to all elements in the min-heap.
double findMedianSortedArrays_Heaps(const vector<int>& nums1, const vector<int>& nums2) {
    priority_queue<int> maxHeap; // Max-heap for the left part
    priority_queue<int, vector<int>, greater<int>> minHeap; // Min-heap for the right part

    // Insert elements from both arrays into the heaps
    for (int num : nums1) {
        maxHeap.push(num);
    }
    for (int num : nums2) {
        maxHeap.push(num);
    }

     // Rebalance the heaps
    while (maxHeap.size() > minHeap.size() + 1) {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
    }
    while (minHeap.size() > maxHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
    }

    // Calculate the median
    if ((maxHeap.size() + minHeap.size()) % 2 == 0) {
        return (double)(maxHeap.top() + minHeap.top()) / 2.0;
    } else {
        return (double)maxHeap.top();
    }
}

// 5. Recursive Approach (Divide and Conquer)
//   - Time Complexity: O(log(m + n)) on average, O(m + n) in the worst case
//   - Space Complexity: O(log(m + n)) for the recursion stack
//   - Explanation: This approach recursively divides the arrays to find the kth smallest element, where k is (m+n)/2.  It's based on the idea that the median is the kth smallest element.  This method can be tricky to implement correctly due to the recursive logic.
double findMedianSortedArrays_Recursive(const vector<int>& nums1, int start1, int end1,
                                            const vector<int>& nums2, int start2, int end2, int k) {
    // Handle base cases for recursion
    if (start1 > end1) {
        return (double)nums2[start2 + k - 1];
    }
    if (start2 > end2) {
        return (double)nums1[start1 + k - 1];
    }
    if (k == 1) {
        return min(nums1[start1], nums2[start2]);
    }

    int mid1 = (start1 + end1) / 2;
    int mid2 = (start2 + end2) / 2;

    // Handle cases where mid1 or mid2 goes out of bounds
    int len1 = end1 - start1 + 1;
    int len2 = end2 - start2 + 1;
    int val1 = (mid1 < start1 + len1) ? nums1[mid1] : numeric_limits<int>::max();
    int val2 = (mid2 < start2 + len2) ? nums2[mid2] : numeric_limits<int>::max();

    if (val1 <= val2) {
        if (k > (mid1 - start1) + (mid2 - start2) + 1) {
            return findMedianSortedArrays_Recursive(nums1, mid1 + 1, end1, nums2, start2, end2,
                                                    k - (mid1 - start1) - 1);
        } else {
            return findMedianSortedArrays_Recursive(nums1, start1, end1, nums2, start2, mid2 - 1, k);
        }
    } else {
        if (k > (mid1 - start1) + (mid2 - start2) + 1) {
            return findMedianSortedArrays_Recursive(nums1, start1, end1, nums2, mid2 + 1, end2,
                                                    k - (mid2 - start2) - 1);
        } else {
            return findMedianSortedArrays_Recursive(nums1, start1, mid1 - 1, nums2, start2, end2, k);
        }
    }
}

double findMedianSortedArrays_Recursive(const vector<int>& nums1, const vector<int>& nums2) {
    int m = nums1.size();
    int n = nums2.size();
    int total = m + n;
    if (total % 2 == 0) {
        return (findMedianSortedArrays_Recursive(nums1, 0, m - 1, nums2, 0, n - 1, total / 2) +
                findMedianSortedArrays_Recursive(nums1, 0, m - 1, nums2, 0, n - 1, total / 2 + 1)) / 2.0;
    } else {
        return findMedianSortedArrays_Recursive(nums1, 0, m - 1, nums2, 0, n - 1, total / 2 + 1);
    }
}

int main() {
    // Example usage
    vector<int> nums1 = {1, 3, 8, 9, 15};
    vector<int> nums2 = {7, 11, 18, 19, 21, 25};

    cout << fixed << setprecision(2); //  Control decimal precision for output

    cout << "Brute Force: " << findMedianSortedArrays_BruteForce(nums1, nums2) << endl;
    cout << "Merge and Iterate: " << findMedianSortedArrays_MergeIterate(nums1, nums2) << endl;
    cout << "Binary Search: " << findMedianSortedArrays_BinarySearch(nums1, nums2) << endl;
    cout << "Heaps: " << findMedianSortedArrays_Heaps(nums1, nums2) << endl;
    cout << "Recursive: " << findMedianSortedArrays_Recursive(nums1, nums2) << endl;

    return 0;
}
