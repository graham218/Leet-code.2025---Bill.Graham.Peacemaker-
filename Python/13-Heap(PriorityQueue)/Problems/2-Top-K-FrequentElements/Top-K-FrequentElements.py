from collections import Counter
import heapq
import random
import statistics

def top_k_frequent_counter_heap(nums, k):
    """
    Approach 1: Using Counter and Heap (Priority Queue)

    1.  Count the frequency of each element using Counter.
    2.  Create a min-heap (priority queue) to store the k most frequent elements.
    3.  Iterate through the frequencies and push (-frequency, element) onto the heap.  We use negative frequency because heapq is a min-heap, and we want to prioritize larger frequencies.
    4.  If the heap size exceeds k, pop the smallest element (least frequent).
    5.  Extract the elements from the heap (in any order).

    Time Complexity: O(N log k), where N is the number of elements in nums.
    Space Complexity: O(N + k), for the counter and the heap.
    """
    counts = Counter(nums)  # O(N)
    heap = []
    for num, freq in counts.items(): # O(N)
        heapq.heappush(heap, (-freq, num)) # O(logk) * N
        if len(heap) > k:
            heapq.heappop(heap) # O(logk)
    # The heap now contains the k most frequent elements.
    # We extract them.  The order is *not* guaranteed to be sorted by frequency.
    result = [num for _, num in heap] # O(k)
    print(f"Top {k} frequent elements (Counter + Heap): {result}")
    return result

def top_k_frequent_bucket_sort(nums, k):
    """
    Approach 2: Bucket Sort

    1.  Count the frequency of each element using Counter.
    2.  Create a list of buckets where the index represents the frequency and the value is a list of elements with that frequency.
    3.  Iterate through the frequency counts and place each number in its corresponding bucket.
    4.  Iterate through the buckets in reverse order (from highest frequency to lowest).
    5.  Add elements from the buckets to the result list until we have k elements.

    Time Complexity: O(N), where N is the number of elements in nums.  This is because the outer loop iterates at most N times (the maximum frequency of an element), and the inner loop iterates a maximum of k times.
    Space Complexity: O(N), for the counter and the buckets list.
    """
    counts = Counter(nums)  # O(N)
    buckets = [[] for _ in range(len(nums) + 1)]  # O(N)
    for num, freq in counts.items(): # O(N)
        buckets[freq].append(num)
    result = []
    for i in range(len(buckets) - 1, 0, -1): # O(N)
        for num in buckets[i]:
            result.append(num)
            if len(result) == k:
                print(f"Top {k} frequent elements (Bucket Sort): {result}")
                return result
    return result

def top_k_frequent_sorted(nums, k):
    """
    Approach 3: Using Sorted and Counter

    1. Count frequency of each element using Counter.
    2. Sort the (element, frequency) pairs in descending order of frequency.
    3. Take the first k elements.

    Time Complexity: O(N log N), where N is the number of elements in `nums`.
    Space Complexity: O(N)
    """
    counts = Counter(nums) # O(N)
    sorted_counts = sorted(counts.items(), key=lambda item: item[1], reverse=True) # O(NlogN)
    result = [num for num, _ in sorted_counts[:k]] # O(k)
    print(f"Top {k} frequent elements (Sorted): {result}")
    return result

def top_k_frequent_nlargest(nums, k):
    """
    Approach 4: Using nlargest from heapq

    1. Count frequency of each element using Counter.
    2. Use nlargest to get the k largest elements from the counter.

    Time Complexity: O(N log k), where N is the number of elements in `nums`.
    Space Complexity: O(N)
    """
    counts = Counter(nums) # O(N)
    result = heapq.nlargest(k, counts, key=counts.get) # O(N log k)
    print(f"Top {k} frequent elements (nlargest): {result}")
    return result

def top_k_frequent_quickselect(nums, k):
    """
    Approach 5: Quickselect (Partial Sort)

    1. Count the frequency of each element using Counter.
    2. Convert the counter to a list of (element, frequency) pairs.
    3. Use the quickselect algorithm to partially sort the list such that the k-th most frequent element is at the correct position.
    4. The first k elements in the partially sorted list are the top k frequent elements.

    Time Complexity:
        - Average case: O(N), where N is the number of elements in nums.
        - Worst case: O(N^2), but this is rare with randomized pivot selection.
    Space Complexity: O(N)
    """
    counts = Counter(nums) # O(N)
    unique_counts = list(counts.items()) # O(N)

    def partition(left, right, pivot_index):
        pivot_freq = unique_counts[pivot_index][1]
        # Move pivot to the end
        unique_counts[pivot_index], unique_counts[right] = unique_counts[right], unique_counts[pivot_index]

        # all elements with frequency > pivot_freq are moved to the left
        store_index = left
        for i in range(left, right):
            if unique_counts[i][1] > pivot_freq:
                unique_counts[store_index], unique_counts[i] = unique_counts[i], unique_counts[store_index]
                store_index += 1

        # Move pivot to its final place
        unique_counts[right], unique_counts[store_index] = unique_counts[store_index], unique_counts[right]

        return store_index

    def quickselect(left, right, k_smallest):
        """
        Selects the k-th largest element (k_smallest from the right).
        """
        if left == right:
            return unique_counts[left]

        # Select a random pivot_index
        pivot_index = random.randint(left, right)

        # Find the pivot position in the sorted list
        pivot_index = partition(left, right, pivot_index)

        # The pivot is in its final sorted position
        if k_smallest == pivot_index:
            return unique_counts[k_smallest]
        elif k_smallest < pivot_index:
            # Go left
            return quickselect(left, pivot_index - 1, k_smallest)
        else:
            # Go right
            return quickselect(pivot_index + 1, right, k_smallest)

    # Find the (k-1)-th largest frequency element.  We use k-1 because the list is 0-indexed.
    quickselect(0, len(unique_counts) - 1, k - 1)
    # The first k elements are the k most frequent ones.
    result = [num for num, _ in unique_counts[:k]] # O(k)
    print(f"Top {k} frequent elements (Quickselect): {result}")
    return result

if __name__ == "__main__":
    nums = [1, 1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5]
    k = 3
    print(f"Input list: {nums}, k = {k}")
    top_k_frequent_counter_heap(nums.copy(), k)
    top_k_frequent_bucket_sort(nums.copy(), k)
    top_k_frequent_sorted(nums.copy(), k)
    top_k_frequent_nlargest(nums.copy(), k)
    top_k_frequent_quickselect(nums.copy(), k)

    nums2 = [1, 2, 2, 3, 3, 3]
    k = 2
    print(f"\nInput list: {nums2}, k = {k}")
    top_k_frequent_counter_heap(nums2.copy(), k)
    top_k_frequent_bucket_sort(nums2.copy(), k)
    top_k_frequent_sorted(nums2.copy(), k)
    top_k_frequent_nlargest(nums2.copy(), k)
    top_k_frequent_quickselect(nums2.copy(), k)

    nums3 = [1]
    k = 1
    print(f"\nInput list: {nums3}, k = {k}")
    top_k_frequent_counter_heap(nums3.copy(), k)
    top_k_frequent_bucket_sort(nums3.copy(), k)
    top_k_frequent_sorted(nums3.copy(), k)
    top_k_frequent_nlargest(nums3.copy(), k)
    top_k_frequent_quickselect(nums3.copy(), k)
