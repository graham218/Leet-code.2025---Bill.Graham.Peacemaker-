#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional> // Required for std::greater

using namespace std;

// Function to find the Kth largest element in an array using a max-heap.
//
// Approach 1: Using Max Heap (Priority Queue)
//
// 1.  Build a max-heap from the input array.
// 2.  Extract the maximum element (k-1) times.
// 3.  The top element of the heap is now the Kth largest.
//
// Time Complexity: O(N + K log N), where N is the size of the array.  Building the heap is O(N), and extracting K elements is K log N.
// Space Complexity: O(N) for the heap.
int findKthLargestMaxHeap(vector<int>& nums, int k) {
    // Create a max heap (priority queue).
    priority_queue<int> maxHeap(nums.begin(), nums.end());

    // Extract the largest element k-1 times.
    for (int i = 0; i < k - 1; ++i) {
        maxHeap.pop();
    }

    // The top element is now the kth largest.
    return maxHeap.top();
}

// Function to find the Kth largest element using a min-heap.
//
// Approach 2: Using Min Heap
//
// 1.  Build a min-heap of size K with the first K elements of the array.
// 2.  For each remaining element in the array:
//     * If the element is greater than the root of the min-heap,
//         * Replace the root with the current element.
//         * Heapify the min-heap.
// 3.  The root of the min-heap is the Kth largest element.
//
// Time Complexity: O(K + (N-K) log K), where N is the size of the array.  Building initial heap is O(K), and processing the rest of the elements is (N-K)logK.
// Space Complexity: O(K) for the min-heap.
int findKthLargestMinHeap(vector<int>& nums, int k) {
    // Create a min heap.  std::greater<int> makes it a min-heap.
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Insert the first k elements into the min-heap.
    for (int i = 0; i < k; ++i) {
        minHeap.push(nums[i]);
    }

    // Process the remaining elements.
    for (int i = k; i < nums.size(); ++i) {
        if (nums[i] > minHeap.top()) {
            minHeap.pop();
            minHeap.push(nums[i]);
        }
    }

    // The top of the min-heap is the kth largest element.
    return minHeap.top();
}

// Function to find the Kth largest element using sorting.
//
// Approach 3: Using Sorting
//
// 1.  Sort the array in descending order.
// 2.  The element at index (k-1) is the Kth largest.
//
// Time Complexity: O(N log N), where N is the size of the array (due to sorting).
// Space Complexity: O(1) if an in-place sort is used (e.g., std::sort).  Otherwise, O(N) in some cases.
int findKthLargestSorting(vector<int>& nums, int k) {
    // Sort the array in descending order using std::sort with reverse iterators.
    sort(nums.rbegin(), nums.rend()); // Sort in descending order.
    // Alternatively:  sort(nums.begin(), nums.end(), greater<int>());

    // The kth largest element is at index k-1.
    return nums[k - 1];
}

// Function to find the Kth largest element using the nth_element algorithm.
//
// Approach 4: Using nth_element
//
// 1.  Use the std::nth_element algorithm to partially sort the array.
// 2.  nth_element rearranges the array such that the element at the kth position
//     would be the element in that position if the whole array were sorted.
//     Importantly, elements before the kth element are not guaranteed to be sorted,
//     nor are elements after it.
// 3.  The Kth largest element will be at nums.size() - k index.
//
// Time Complexity: O(N) on average, where N is the size of the array.
// Space Complexity: O(1)
int findKthLargestNthElement(vector<int>& nums, int k) {
    // nth_element rearranges the array so that the element at the position
    // (nums.size() - k) is the kth largest.
    nth_element(nums.begin(), nums.begin() + (nums.size() - k), nums.end());

    // The kth largest element is now at index nums.size() - k.
    return nums[nums.size() - k];
}

// Function to find the Kth largest element using QuickSelect (recursive).
//
// Approach 5: QuickSelect (Recursive)
//
// 1.  Choose a pivot element from the array.
// 2.  Partition the array into two sub-arrays: elements greater than the pivot
//     and elements less than or equal to the pivot.
// 3.  If the number of elements greater than the pivot is equal to k-1,
//     the pivot is the Kth largest element.
// 4.  If the number of elements greater than the pivot is greater than k-1,
//     recursively find the Kth largest element in the left sub-array.
// 5.  Otherwise, recursively find the (k - number of elements greater than pivot - 1)th
//     largest element in the right sub-array.
//
// Time Complexity: O(N) on average, but O(N^2) in the worst case.
// Space Complexity: O(log N) on average due to recursion, but O(N) in the worst case.

int quickSelect(vector<int>& nums, int left, int right, int k) {
    if (left == right) {
        return nums[left];
    }

    // Choose a pivot (here, the rightmost element).  Can choose randomly for better average case.
    int pivotIndex = right;
    int pivot = nums[pivotIndex];
    int partitionIndex = left; // Index to track the boundary

    // Partition the array
    for (int i = left; i < right; ++i) {
        if (nums[i] > pivot) {
            swap(nums[i], nums[partitionIndex]);
            partitionIndex++;
        }
    }
    swap(nums[partitionIndex], nums[right]); // Place pivot in its correct position.
    // partitionIndex is now the correct position of the pivot

    int numGreater = partitionIndex - left;

    if (numGreater == k - 1) {
        return nums[partitionIndex]; // Pivot is the kth largest
    } else if (numGreater >= k) {
        return quickSelect(nums, left, partitionIndex - 1, k); // Recurse left
    } else {
        return quickSelect(nums, partitionIndex + 1, right, k - numGreater - 1); // Recurse right
    }
}

int findKthLargestQuickSelect(vector<int>& nums, int k) {
    return quickSelect(nums, 0, nums.size() - 1, k);
}

int main() {
    vector<int> nums = {3, 1, 5, 6, 2, 4};
    int k = 3;

    cout << "Array: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    cout << "K = " << k << endl;

    cout << "\n--- Kth Largest Element ---" << endl;
    cout << "Max Heap: " << findKthLargestMaxHeap(nums, k) << endl;
    cout << "Min Heap: " << findKthLargestMinHeap(nums, k) << endl;
    cout << "Sorting: " << findKthLargestSorting(nums, k) << endl;
    cout << "Nth Element: " << findKthLargestNthElement(nums, k) << endl;
    cout << "QuickSelect: " << findKthLargestQuickSelect(nums, k) << endl;

    return 0;
}
