#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional> // Required for std::greater

// Function to find the Kth largest element using a max-heap (priority queue)
// Time Complexity: O(N log K), where N is the size of the array.
// Space Complexity: O(K) for the heap.
int findKthLargestUsingMaxHeap(std::vector<int>& nums, int k) {
    // Create a max-heap (priority queue)
    std::priority_queue<int> maxHeap(nums.begin(), nums.end());

    // Pop the top k-1 elements.  The kth element from the top will be the kth largest.
    for (int i = 0; i < k - 1; ++i) {
        maxHeap.pop();
    }
    return maxHeap.top();
}

// Function to find the Kth largest element using a min-heap (priority queue)
// Time Complexity: O(N log K), where N is the size of the array.
// Space Complexity: O(K) for the heap.
int findKthLargestUsingMinHeap(std::vector<int>& nums, int k) {
    // Create a min-heap (priority queue)
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    // Iterate through the array.
    for (int num : nums) {
        // Push the current element into the min-heap.
        minHeap.push(num);
        // If the size of the min-heap exceeds k, pop the smallest element.
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    // The top element of the min-heap is the kth largest element.
    return minHeap.top();
}

// Function to find the Kth largest element using sorting
// Time Complexity: O(N log N), where N is the size of the array.
// Space Complexity: O(1) in-place sort,  O(N) for std::sort in worst case.
int findKthLargestUsingSorting(std::vector<int>& nums, int k) {
    // Sort the array in descending order.  We can use std::sort and reverse iterators.
    std::sort(nums.rbegin(), nums.rend()); // Sort in descending order
    // The kth largest element is at index k-1.
    return nums[k - 1];
}

// Function to find the Kth largest element using the nth_element algorithm (modified)
// Time Complexity: Average case O(N), Worst case O(N^2)
// Space Complexity: O(1)
int findKthLargestUsingNthElement(std::vector<int>& nums, int k) {
    // nth_element rearranges the array such that the element at the kth position
    // (counting from 0) is the element that would be at the kth position in a sorted array.
    // In this case, we want the (n-k)th smallest element.
    std::nth_element(nums.begin(), nums.begin() + (nums.size() - k), nums.end());
    return nums[nums.size() - k];
}

// Function to find the Kth largest element using QuickSelect (Recursive)
// Average Time Complexity: O(N), Worst Case Time Complexity: O(N^2)
// Space Complexity: O(log N) average, O(N) worst case (due to recursion)
int quickSelect(std::vector<int>& nums, int left, int right, int k) {
    if (left == right) {
        return nums[left];
    }

    // Choose a pivot (here, we choose the rightmost element)
    int pivotIndex = right;
    int pivot = nums[pivotIndex];
    int i = left; // Index for elements smaller than the pivot

    // Partition the array
    for (int j = left; j < right; ++j) {
        if (nums[j] > pivot) { // Corrected comparison to find kth *largest*
            std::swap(nums[i], nums[j]);
            i++;
        }
    }
    std::swap(nums[i], nums[right]); // Place pivot in its correct position
    pivotIndex = i;

    // Calculate the rank of the pivot
    int rank = pivotIndex - left + 1;

    if (rank == k) {
        return nums[pivotIndex];
    } else if (rank > k) {
        return quickSelect(nums, left, pivotIndex - 1, k);
    } else {
        return quickSelect(nums, pivotIndex + 1, right, k - rank);
    }
}

int findKthLargestUsingQuickSelect(std::vector<int>& nums, int k) {
    return quickSelect(nums, 0, nums.size() - 1, k);
}

int main() {
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int k = 5;

    std::cout << "Array: ";
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "K = " << k << std::endl;

    // Find the Kth largest element using different methods and print the results.
    std::cout << "Kth largest element using Max Heap: " << findKthLargestUsingMaxHeap(nums, k) << std::endl;
    std::cout << "Kth largest element using Min Heap: " << findKthLargestUsingMinHeap(nums, k) << std::endl;
    std::cout << "Kth largest element using Sorting: " << findKthLargestUsingSorting(nums, k) << std::endl;
    std::cout << "Kth largest element using Nth Element: " << findKthLargestUsingNthElement(nums, k) << std::endl;
    std::cout << "Kth largest element using QuickSelect: " << findKthLargestUsingQuickSelect(nums, k) << std::endl;

    return 0;
}
