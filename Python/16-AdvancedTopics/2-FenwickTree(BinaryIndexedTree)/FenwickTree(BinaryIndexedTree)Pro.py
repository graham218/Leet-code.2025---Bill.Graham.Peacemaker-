class FenwickTree:
    """
    Implementation of a Fenwick Tree (Binary Indexed Tree) for efficient prefix sum queries
    and updates on an array.

    A Fenwick Tree is a data structure that can:
        - Efficiently compute the prefix sum of an array in O(log n) time.
        - Update an element in the array in O(log n) time.

    It is particularly useful when you need to perform many prefix sum queries and updates
    on a mutable array.
    """

    def __init__(self, size_or_array):
        """
        Initializes the Fenwick Tree.

        Args:
            size_or_array: Either an integer representing the size of the array,
                           or a list/array of numbers to initialize the tree.
        """
        if isinstance(size_or_array, int):
            if size_or_array <= 0:
                raise ValueError("Size must be positive")
            self.size = size_or_array
            self.tree = [0] * (size_or_array + 1)  # 1-indexed array
            self.array = [0] * size_or_array # Keep original array, though not strictly needed.
        elif isinstance(size_or_array, list):
            self.array = size_or_array[:]  # Create a copy to avoid modifying the original list
            self.size = len(size_or_array)
            self.tree = [0] * (self.size + 1)  # 1-indexed array
            for i, val in enumerate(size_or_array):
                self._update(i + 1, val)  # Build the tree
        else:
            raise TypeError("size_or_array must be an integer or a list")

    def _update(self, index, value):
        """
        Updates the Fenwick Tree with the given value at the given index.  This is an internal
        method.  It assumes the index is 1-based.

        Args:
            index: The 1-based index to update.
            value: The value to add to the element at the index.
        """
        while index <= self.size:
            self.tree[index] += value
            index += index & -index  # Get the next index to update (remove lowest set bit)

    def update(self, index, value):
        """
        Updates the element at the given index in the original array and the Fenwick Tree.

        Args:
            index: The 0-based index to update.
            value: The new value for the element at the index.
        """
        if not 0 <= index < self.size:
            raise IndexError("Index out of bounds")
        delta = value - self.array[index] # Calculate the *difference*
        self.array[index] = value # Update the original array
        self._update(index + 1, delta)  # Update the Fenwick tree (using 1-based index)

    def prefix_sum(self, index):
        """
        Calculates the prefix sum up to the given index (inclusive).

        Args:
            index: The 0-based index up to which to calculate the prefix sum.

        Returns:
            The prefix sum up to the given index.
        """
        if not 0 <= index < self.size:
            raise IndexError("Index out of bounds")

        index += 1  # Convert to 1-based index for Fenwick Tree operations
        sum_val = 0
        while index > 0:
            sum_val += self.tree[index]
            index -= index & -index  # Get the next index to query (remove lowest set bit)
        return sum_val

    def range_sum(self, left, right):
        """
        Calculates the sum of the elements within the given range (inclusive).

        Args:
            left: The 0-based index of the left boundary of the range.
            right: The 0-based index of the right boundary of the range.

        Returns:
            The sum of the elements within the given range.
        """
        if not 0 <= left <= right < self.size:
            raise IndexError("Indices out of bounds")
        return self.prefix_sum(right) - self.prefix_sum(left - 1) if left > 0 else self.prefix_sum(right)

    def __str__(self):
        """
        Returns a string representation of the Fenwick Tree (for debugging purposes).
        """
        return f"FenwickTree(size={self.size}, tree={self.tree}, array={self.array})"

    def __repr__(self):
        """
        Official string representation for developers (useful in REPL).
        """
        return f"FenwickTree({self.array})" #  Use the array for unambiguous representation

# Example Usage
if __name__ == "__main__":
    # Example 1: Basic usage with a list
    data = [1, 3, 5, 2, 4, 6, 1, 3, 5, 2]
    ft = FenwickTree(data)
    print("Initial Fenwick Tree:", ft)  #  Prints the object, showing the array.
    print("Original Array:", ft.array)

    print("Prefix sum up to index 5:", ft.prefix_sum(5))  # Output: 21 (1+3+5+2+4+6)
    print("Range sum from index 2 to 7:", ft.range_sum(2, 7))  # Output: 21 (5+2+4+6+1+3)

    ft.update(3, 10)  # Update the value at index 3 (originally 2) to 10
    print("Updated Fenwick Tree:", ft)
    print("Updated Array:", ft.array)
    print("Prefix sum up to index 5 after update:", ft.prefix_sum(5))  # Output: 29 (1+3+5+10+4+6)
    print("Range sum from index 2 to 7 after update:", ft.range_sum(2, 7))

    # Example 2: Initialize with size and then update
    ft2 = FenwickTree(10)  # Create a Fenwick Tree of size 10
    for i in range(10):
        ft2.update(i, i + 1)  # Initialize with values 1 to 10
    print("\nFenwick Tree initialized with size and updated:", ft2)
    print("Prefix sum up to index 4:", ft2.prefix_sum(4))  # Output: 15 (1+2+3+4+5)

    # Example 3: Demonstrating error handling
    try:
        ft3 = FenwickTree(0)  # Invalid size
    except ValueError as e:
        print(f"\nError creating Fenwick Tree: {e}")

    try:
        ft.update(10, 5)  # Index out of bounds
    except IndexError as e:
        print(f"Error updating Fenwick Tree: {e}")

    try:
        ft.prefix_sum(10)  # Index out of bounds
    except IndexError as e:
        print(f"Error calculating prefix sum: {e}")

    try:
        ft.range_sum(8, 9)
        ft.range_sum(9, 8) # left > right
    except IndexError as e:
        print(f"Error calculating range sum: {e}")
