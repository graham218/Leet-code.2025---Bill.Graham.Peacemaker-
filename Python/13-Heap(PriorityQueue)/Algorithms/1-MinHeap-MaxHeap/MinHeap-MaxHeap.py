import heapq  # Python's built-in heap implementation
import time

class Heap:
    """
    This class provides a basic implementation of a Min Heap and Max Heap.
    It includes methods for insertion, extraction, and heapifying a list.
    """

    def __init__(self, heap_type="min"):
        """
        Initializes the Heap object.
        Args:
            heap_type (str):  "min" for Min Heap, "max" for Max Heap.  Defaults to "min".
        """
        if heap_type not in ("min", "max"):
            raise ValueError("heap_type must be 'min' or 'max'")
        self.heap_type = heap_type
        self.data = []  # List to store the heap elements
        self.size = 0  # Current number of elements in the heap

    def __len__(self):
        """
        Returns the number of elements in the heap.  (Allows using len(my_heap))
        """
        return self.size

    def _compare(self, a, b):
        """
        Compares two elements based on the heap type.
        Args:
            a: The first element.
            b: The second element.
        Returns:
            bool: True if a should be considered "smaller" (for min heap)
                  or "larger" (for max heap) than b, False otherwise.
        """
        if self.heap_type == "min":
            return a < b
        else:  # max heap
            return a > b

    def _swap(self, i, j):
        """
        Swaps the elements at indices i and j in the heap's data list.
        Args:
            i: The index of the first element.
            j: The index of the second element.
        """
        self.data[i], self.data[j] = self.data[j], self.data[i]

    def _parent(self, index):
        """
        Calculates the index of the parent node.
        Args:
            index: The index of the child node.
        Returns:
            int: The index of the parent node.
        """
        return (index - 1) // 2

    def _left_child(self, index):
        """
        Calculates the index of the left child node.
        Args:
            index: The index of the parent node.
        Returns:
            int: The index of the left child node.
        """
        return 2 * index + 1

    def _right_child(self, index):
        """
        Calculates the index of the right child node.
        Args:
            index: The index of the parent node.
        Returns:
            int: The index of the right child node.
        """
        return 2 * index + 2

    def _heapify_up(self, index):
        """
        Performs the heapify-up operation, moving a node up the tree
        to its correct position.  Used after insertion.
        Args:
            index: The index of the node to heapify up.
        """
        while index > 0 and self._compare(self.data[index], self.data[self._parent(index)]):
            self._swap(index, self._parent(index))
            index = self._parent(index)

    def _heapify_down(self, index):
        """
        Performs the heapify-down operation, moving a node down the tree
        to its correct position.  Used after extraction (removing the root).
        Args:
            index: The index of the node to heapify down.
        """
        left = self._left_child(index)
        right = self._right_child(index)
        largest = index  # or smallest, depending on heap type

        if left < self.size and self._compare(self.data[left], self.data[largest]):
            largest = left
        if right < self.size and self._compare(self.data[right], self.data[largest]):
            largest = right

        if largest != index:
            self._swap(index, largest)
            self._heapify_down(largest)

    def insert(self, value):
        """
        Inserts a new value into the heap.
        Args:
            value: The value to insert.
        """
        self.data.append(value)
        self.size += 1
        self._heapify_up(self.size - 1)

    def extract(self):
        """
        Extracts (removes and returns) the root element from the heap
        (which is the minimum element in a Min Heap, or the maximum
        element in a Max Heap).
        Returns:
            The root element of the heap, or None if the heap is empty.
        """
        if self.size == 0:
            return None  # Handle empty heap case
        if self.size == 1:
            self.size -= 1
            return self.data.pop()

        root = self.data[0]
        self.data[0] = self.data[self.size - 1]  # Move last element to root
        self.data.pop()
        self.size -= 1
        self._heapify_down(0)  # Restore heap property
        return root

    def peek(self):
        """
        Returns the root element of the heap without removing it.
        Returns:
            The root element, or None if the heap is empty.
        """
        if self.size == 0:
            return None
        return self.data[0]

    def display(self):
        """
        Prints the elements of the heap in their current order.  This is
        for debugging and visualization, and does *not* represent the
        sorted order.
        """
        print(f"{self.heap_type.title()} Heap: {self.data[:self.size]}")

    def heapify(self, arr):
        """
        Initializes the heap from an existing list (array).  This is a
        more efficient way to build a heap than inserting elements one by one.
        Args:
           arr:  The list to heapify.
        """
        self.data = arr[:]  # Important: create a *copy* of the list.
        self.size = len(arr)
        # Start from the last non-leaf node and heapify downwards.
        for i in range(self.size // 2 - 1, -1, -1):
            self._heapify_down(i)
        # added return self
        return self

def heap_sort(arr, order="asc"):
    """
    Sorts a list using the Heap Sort algorithm.
    Args:
        arr (list): The list to be sorted.
        order (str): "asc" for ascending, "desc" for descending.
    Returns:
        list: The sorted list.
    """
    if order not in ("asc", "desc"):
        raise ValueError("order must be 'asc' or 'desc'")

    n = len(arr)
    if order == "asc":
        heap = Heap("min")  # Use Min Heap for ascending order
    else:
        heap = Heap("max")  # Use Max Heap for descending order

    heap.heapify(arr)  # Efficiently build the heap
    sorted_arr = []
    for _ in range(n):
        sorted_arr.append(heap.extract())  # Extract elements in sorted order
    return sorted_arr

def main():
    """
    Main function to demonstrate the usage of the Heap class and heap sort.
    """
    print("--- Heap Implementation Demonstration ---")

    # 1. Using the Heap class (Min Heap)
    print("\n1. Using the Heap class (Min Heap):")
    min_heap = Heap("min")
    min_heap.insert(5)
    min_heap.insert(3)
    min_heap.insert(7)
    min_heap.insert(1)
    min_heap.insert(9)
    min_heap.display()  # Output: Min Heap: [1, 3, 5, 7, 9]
    print("Peek:", min_heap.peek())  # Output: Peek: 1
    print("Extract:", min_heap.extract())  # Output: Extract: 1
    min_heap.display()  # Output: Min Heap: [3, 5, 7, 9]

    # 2. Using the Heap class (Max Heap)
    print("\n2. Using the Heap class (Max Heap):")
    max_heap = Heap("max")
    max_heap.insert(5)
    max_heap.insert(3)
    max_heap.insert(7)
    max_heap.insert(1)
    max_heap.insert(9)
    max_heap.display()  # Output: Max Heap: [9, 7, 5, 1, 3]
    print("Peek:", max_heap.peek())  # Output: Peek: 9
    print("Extract:", max_heap.extract())  # Output: Extract: 9
    max_heap.display()  # Output: Max Heap: [7, 5, 3, 1]

    # 3. Heapify an existing list (Min Heap)
    print("\n3. Heapify an existing list (Min Heap):")
    my_list = [5, 3, 7, 1, 9]
    min_heap2 = Heap("min")
    min_heap2.heapify(my_list)
    min_heap2.display()  # Output: Min Heap: [1, 3, 5, 7, 9]

    # 4. Heap Sort (Ascending Order)
    print("\n4. Heap Sort (Ascending Order):")
    unsorted_list = [5, 3, 7, 1, 9, 2, 8, 4, 6, 0]
    sorted_list_asc = heap_sort(unsorted_list, "asc")
    print("Unsorted List:", unsorted_list)
    print("Sorted List (Ascending):", sorted_list_asc)  # Output: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

    # 5. Heap Sort (Descending Order)
    print("\n5. Heap Sort (Descending Order):")
    unsorted_list = [5, 3, 7, 1, 9, 2, 8, 4, 6, 0]
    sorted_list_desc = heap_sort(unsorted_list, "desc")
    print("Unsorted List:", unsorted_list)
    print("Sorted List (Descending):", sorted_list_desc)  # Output: [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]

    # 6. Using Python's built-in heapq (Min Heap) - Demonstration
    print("\n6. Using Python's built-in heapq (Min Heap):")
    my_list = [5, 3, 7, 1, 9]
    print("Original list:", my_list)
    heapq.heapify(my_list)  # In-place heapify
    print("Heapified list (using heapq):", my_list)  # Output: [1, 3, 5, 7, 9]

    # Push and pop elements
    heapq.heappush(my_list, 2)
    print("List after pushing 2:", my_list) # Output: [1, 2, 5, 7, 9, 3]
    print("Popped element:", heapq.heappop(my_list))  # Output: 1
    print("List after popping:", my_list) #  Output: [2, 3, 5, 7, 9]

if __name__ == "__main__":
    main()
