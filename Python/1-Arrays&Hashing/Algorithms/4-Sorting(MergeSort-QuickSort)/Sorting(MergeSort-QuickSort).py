"""
Problem: Sorting an Array using Different Approaches
Sorting is a fundamental operation in computer science and is used to organize data for efficient searching, retrieval, and manipulation.
Here, we implement five different sorting algorithms:

1. Merge Sort (Divide and Conquer)
2. Quick Sort (Divide and Conquer, In-Place)
3. Heap Sort (Heap Data Structure)
4. Bubble Sort (Basic Iterative Method)
5. Counting Sort (Non-Comparison Based Sorting for Bounded Integers)
"""

def merge_sort(arr):
    """
    Approach 1: Merge Sort
    Uses Divide and Conquer to recursively split and merge sorted subarrays.

    Algorithm:
    1. Base Case: If the array has 0 or 1 element, it is already sorted, so return it.
    2. Divide: Find the middle point of the array and divide it into two halves: left and right subarrays.
    3. Conquer: Recursively sort the left and right subarrays using merge_sort.
    4. Combine: Merge the sorted left and right subarrays into a single sorted array.

    Time Complexity: O(n log n) - due to the balanced division of the array and linear merging.
    Space Complexity: O(n) -  extra space is used for creating left and right subarrays and the merged result.  Merge operation requires temporary arrays.
    """
    if len(arr) <= 1:
        return arr  # Base case: already sorted
    mid = len(arr) // 2  # Find the middle point
    left = merge_sort(arr[:mid])  # Recursively sort the left half
    right = merge_sort(arr[mid:])  # Recursively sort the right half
    return merge(left, right)  # Merge the sorted halves

def merge(left, right):
    """
    Helper function for merge sort to merge two sorted arrays.

    Algorithm:
    1. Initialize an empty result array.
    2. Initialize pointers i and j to the start of the left and right arrays, respectively.
    3. Compare elements at left[i] and right[j]:
       - If left[i] is smaller, append it to the result and increment i.
       - Otherwise, append right[j] to the result and increment j.
    4. Append any remaining elements from the left or right array to the result.
    5. Return the merged sorted array.

    Time Complexity: O(n) - where n is the total number of elements in the two arrays.
    Space Complexity: O(n) -  for the 'result' list.
    """
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])  # Append remaining elements from left
    result.extend(right[j:])  # Append remaining elements from right
    return result

def quick_sort(arr):
    """
    Approach 2: Quick Sort
    Uses Divide and Conquer to sort elements by partitioning around a pivot.

    Algorithm:
    1. Base Case: If the array has 0 or 1 element, it is already sorted, so return it.
    2. Choose Pivot: Select a pivot element from the array (e.g., the middle element).
    3. Partition: Partition the array into three sub-arrays:
       - 'left': elements less than the pivot.
       - 'middle': elements equal to the pivot.
       - 'right': elements greater than the pivot.
    4. Recursively sort the 'left' and 'right' sub-arrays using quick_sort.
    5. Combine: Concatenate the sorted 'left', 'middle', and 'right' sub-arrays.

    Time Complexity:
    - Average Case: O(n log n) - due to balanced partitioning.
    - Worst Case: O(n^2) - occurs when the pivot is consistently the smallest or largest element.
    Space Complexity: O(log n) -  due to the recursive calls.  In-place partitioning is possible, but the recursive call stack grows.
    """
    if len(arr) <= 1:
        return arr  # Base case: already sorted
    pivot = arr[len(arr) // 2]  # Choose the middle element as the pivot
    left = [x for x in arr if x < pivot]  # Elements less than the pivot
    middle = [x for x in arr if x == pivot]  # Elements equal to the pivot
    right = [x for x in arr if x > pivot]  # Elements greater than the pivot
    return quick_sort(left) + middle + quick_sort(right)  # Recursively sort and combine

def heap_sort(arr):
    """
    Approach 3: Heap Sort
    Uses a binary heap data structure to sort elements.

    Algorithm:
    1. Build Max Heap: Convert the input array into a max heap.  A max heap is a complete binary tree where the value of each node is greater than or equal to the value of its children.
    2. Extract and Sort: Repeatedly extract the maximum element (root of the max heap) and place it at the end of the sorted portion of the array.
    3. Heapify: After each extraction, heapify the remaining elements to maintain the max heap property.

    Time Complexity: O(n log n) - building the heap is O(n), and extracting elements and heapifying is O(log n) for each of the n elements.
    Space Complexity: O(1) -  Heap sort is an in-place sorting algorithm.
    """
    def heapify(arr, n, i):
        """
        Maintains the max heap property of a subtree rooted at index i.

        Algorithm:
        1. Initialize largest as i (root of the subtree).
        2. Calculate the indices of the left and right children.
        3. Compare the root with its children:
           - If a child is larger than the root, update largest to the child's index.
        4. If largest is not the root, swap the root with the largest child and recursively heapify the affected subtree.

        Time Complexity: O(log n) -  Height of the binary heap.
        Space Complexity: O(1) -  Uses constant extra space.
        """
        largest = i  # Initialize largest as root
        left = 2 * i + 1  # Left child
        right = 2 * i + 2  # Right child

        # Check if left child exists and is greater than root
        if left < n and arr[left] > arr[largest]:
            largest = left

        # Check if right child exists and is greater than largest so far
        if right < n and arr[right] > arr[largest]:
            largest = right

        # If largest is not root
        if largest != i:
            arr[i], arr[largest] = arr[largest], arr[i]  # Swap
            heapify(arr, n, largest)  # Recursively heapify the affected sub-tree

    n = len(arr)

    # Build max heap
    for i in range(n // 2 - 1, -1, -1):  # Start from the last non-leaf node
        heapify(arr, n, i)

    # Extract elements from the heap one by one
    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]  # Swap current root with end
        heapify(arr, i, 0)  # Heapify the reduced heap
    return arr

def bubble_sort(arr):
    """
    Approach 4: Bubble Sort
    Repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order.

    Algorithm:
    1. Iterate through the array n times (where n is the length of the array).
    2. In each iteration, compare adjacent elements.
    3. If two adjacent elements are in the wrong order (i.e., the left element is greater than the right element), swap them.
    4. After each pass, the largest unsorted element "bubbles up" to its correct position at the end of the unsorted portion of the array.
    5. The process is repeated until the entire array is sorted.

    Time Complexity:
    - Worst and Average Case: O(n^2) -  Nested loops, where each loop iterates up to n times.
    - Best Case: O(n) - If the array is already sorted, only one pass is needed.
    Space Complexity: O(1) -  Bubble sort is an in-place sorting algorithm.
    """
    n = len(arr)
    for i in range(n):  # Iterate through the array
        for j in range(0, n - i - 1):  # Last i elements are already sorted
            # Swap if the element found is greater than the next element
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr

def counting_sort(arr):
    """
    Approach 5: Counting Sort
    A non-comparison sorting algorithm that sorts integers by counting the occurrences of each unique element.
    It is efficient for sorting integers with a known and relatively small range.

    Algorithm:
    1. Find Range: Determine the minimum and maximum values in the input array.
    2. Create Count Array: Create a count array of size (max - min + 1) to store the frequency of each element.
    3. Count Occurrences: Iterate through the input array and update the count array.  For each element, increment the count at the index corresponding to its value (offset by the minimum value).
    4. Generate Sorted Array: Iterate through the count array.  For each element in the count array, add the corresponding value to the sorted array, repeating it the number of times indicated by the count.

    Time Complexity: O(n + k) - where n is the number of elements in the input array, and k is the range of the input values (max - min + 1).
    Space Complexity: O(k) -  for the 'count' array.
    """
    if not arr:
        return [] # handles the edge case of an empty array
    min_val, max_val = min(arr), max(arr)  # Find min and max values
    count = [0] * (max_val - min_val + 1)  # Create count array
    # Store the count of each element
    for num in arr:
        count[num - min_val] += 1
    sorted_arr = []
    # Generate the sorted array
    for i, freq in enumerate(count):
        sorted_arr.extend([i + min_val] * freq)  # Add each element 'freq' times
    return sorted_arr

# Example usage:
arr = [5, 3, 8, 6, 2, 7, 4, 1]
print("Original Array:", arr)
print("Merge Sort:", merge_sort(arr[:])) # Pass a copy to avoid modifying the original
print("Quick Sort:", quick_sort(arr[:])) # Pass a copy to avoid modifying the original
print("Heap Sort:", heap_sort(arr[:]))  # Pass a copy to avoid in-place modifications
print("Bubble Sort:", bubble_sort(arr[:])) # Pass a copy to avoid modifying the original
print("Counting Sort:", counting_sort(arr[:])) # Pass a copy to avoid modifying the original
