# Solution for Finding Kth Smallest Element in a Sorted Matrix
# Implementing five different approaches

from typing import List
import heapq  # Import the heapq module for heap-based solutions
import bisect # Import bisect for binary search

def kth_smallest_heap(matrix: List[List[int]], k: int) -> int:
    """
    Using a Min-Heap to extract the kth smallest element.

    This function finds the k-th smallest element in a sorted matrix using a min-heap.
    It iterates through the matrix, pushing each element onto the heap.  Then, it
    pops the smallest element from the heap k-1 times, so the k-th smallest element
    remains at the top of the heap.  Finally, it pops and returns this element.

    Args:
        matrix (List[List[int]]): A list of lists representing the sorted matrix.
        k (int): The desired rank of the smallest element (e.g., k=1 for the smallest).

    Returns:
        int: The k-th smallest element in the matrix.

    Time Complexity: O(n*m log(n*m)), where n and m are the dimensions of the matrix.
    Space Complexity: O(n*m), to store all elements in the heap.
    """
    min_heap = []  # Initialize an empty list to use as a min-heap
    for row in matrix:
        for num in row:
            heapq.heappush(min_heap, num)  # Push each element onto the heap
    for _ in range(k - 1):
        heapq.heappop(min_heap)  # Remove the smallest k-1 times
    return heapq.heappop(min_heap)  # The next smallest is the kth smallest



def kth_smallest_binary_search(matrix: List[List[int]], k: int) -> int:
    """
    Using Binary Search on the value range.

    This function finds the k-th smallest element using binary search, but instead of
    searching for a specific value, it searches for the k-th smallest value within the
    range of possible values in the matrix.  It uses a helper function
    `count_less_equal` to count how many elements in the matrix are less than or
    equal to a given value.

    Args:
        matrix (List[List[int]]): A list of lists representing the sorted matrix.
        k (int): The desired rank of the smallest element.

    Returns:
        int: The k-th smallest element in the matrix.

    Time Complexity: O(n log(max_val - min_val)), where n is the dimension of the matrix,
                     and max_val and min_val are the maximum and minimum values in the matrix.
    Space Complexity: O(1), constant extra space.
    """
    n = len(matrix)
    # Initialize the search range: the smallest and largest elements in the matrix.
    low, high = matrix[0][0], matrix[-1][-1]

    def count_less_equal(mid):
        """
        Count numbers less than or equal to mid.

        This is a helper function that counts how many elements in the matrix are less
        than or equal to a given value `mid`.  It efficiently counts by iterating
        through the rows and using a pointer `j` to track the column.

        Args:
            mid (int): The value to compare against.

        Returns:
            int: The number of elements in the matrix less than or equal to `mid`.
        """
        count, j = 0, n - 1  # Initialize count and column pointer
        for i in range(n):
            while j >= 0 and matrix[i][j] > mid:
                j -= 1  # Move the column pointer leftward
            count += (j + 1)  # Add the number of elements <= mid in this row
        return count

    while low < high:
        mid = (low + high) // 2  # Calculate the middle value
        if count_less_equal(mid) < k:
            low = mid + 1  # If count is too small, search in the higher range
        else:
            high = mid      # Otherwise, search in the lower range
    return low  # The loop ends when low == high, which is the kth smallest value



def kth_smallest_flatten_sort(matrix: List[List[int]], k: int) -> int:
    """
    Flatten and sort the matrix.

    This function flattens the 2D matrix into a 1D list, sorts the list, and then
    returns the element at index k-1 (since the list is 0-indexed).  This is a
    simple approach, but it's not the most efficient for large matrices.

    Args:
        matrix (List[List[int]]): A list of lists representing the sorted matrix.
        k (int): The desired rank of the smallest element.

    Returns:
        int: The k-th smallest element in the matrix.

    Time Complexity: O(n*m log(n*m)), where n and m are the dimensions of the matrix, due to sorting.
    Space Complexity: O(n*m), to store all elements in the flattened list.
    """
    flat_list = [num for row in matrix for num in row]  # Flatten the matrix
    flat_list.sort()  # Sort the flattened list
    return flat_list[k - 1]  # Return the element at index k-1



def kth_smallest_row_binary_search(matrix: List[List[int]], k: int) -> int:
    """
    Using binary search on each row to find kth element.

    This function is similar to `kth_smallest_flatten_sort`, as it flattens the matrix
    and then sorts the flattened list.

    Args:
        matrix (List[List[int]]): A list of lists representing the sorted matrix.
        k (int): The desired rank of the smallest element.

    Returns:
        int: The k-th smallest element in the matrix.

    Time Complexity: O(n*m log(n*m)), where n and m are the dimensions of the matrix.
    Space Complexity: O(n*m), to store all elements in the flattened list.
    """
    sorted_list = []
    for row in matrix:
        sorted_list += row
    sorted_list.sort()
    return sorted_list[k - 1]



def kth_smallest_merge_sorted(matrix: List[List[int]], k: int) -> int:
    """
    Merge sorted rows using a heap.

    This function uses a min-heap to efficiently merge the sorted rows of the matrix.
    It starts by pushing the first element of each row onto the heap.  Then, it
    repeatedly pops the smallest element from the heap, increments the count, and
    pushes the next element from the same row onto the heap.  When the count reaches k,
    the popped element is the k-th smallest.

    Args:
        matrix (List[List[int]]): A list of lists representing the sorted matrix.
        k (int): The desired rank of the smallest element.

    Returns:
        int: The k-th smallest element in the matrix.

    Time Complexity: O(k log n), where n is the number of rows in the matrix.  If k is close to n*m,
                     the complexity approaches O(n*m log n).
    Space Complexity: O(n), to store at most n elements in the heap.
    """
    min_heap = []
    for i in range(len(matrix)):
        heapq.heappush(min_heap, (matrix[i][0], i, 0))  # (value, row_index, col_index)

    count, result = 0, 0
    while min_heap:
        result, r, c = heapq.heappop(min_heap)
        count += 1
        if count == k:
            return result
        if c + 1 < len(matrix[0]):
            heapq.heappush(min_heap, (matrix[r][c + 1], r, c + 1))
    return result



# Sample Test Case
matrix = [
    [1, 5, 9],
    [10, 11, 13],
    [12, 13, 15]
]
k = 8
print("Heap Approach:", kth_smallest_heap(matrix, k))
print("Binary Search Approach:", kth_smallest_binary_search(matrix, k))
print("Flatten & Sort Approach:", kth_smallest_flatten_sort(matrix, k))
print("Row Binary Search Approach:", kth_smallest_row_binary_search(matrix, k))
print("Merge Sorted Rows Approach:", kth_smallest_merge_sorted(matrix, k))
