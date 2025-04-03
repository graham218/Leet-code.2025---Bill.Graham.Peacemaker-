class FenwickTree:
    """
    Implementation of a Fenwick Tree (Binary Indexed Tree).

    A Fenwick Tree is a data structure that can efficiently update elements of an
    array and calculate the prefix sum of elements in an array.

    This implementation supports:
    - Construction from an initial array
    - Updating an element in the array
    - Querying the sum of a prefix of the array
    """

    def __init__(self, arr):
        """
        Initializes the Fenwick Tree with the given array.

        Args:
            arr (list): The input array.
        """
        self.size = len(arr)
        self.tree = [0] * (self.size + 1)  # 1-indexed
        self.array = list(arr) # Keep a copy of the original array
        self._build_tree()

    def _build_tree(self):
        """
        Builds the Fenwick Tree from the input array.
        """
        for i in range(self.size):
            self._update_tree(i + 1, self.array[i]) # Use the original array

    def _update_tree(self, index, value):
        """
        Updates the Fenwick Tree with the given value at the given index.

        Args:
            index (int): The index to update (1-indexed).
            value (int): The value to add to the element at the index.
        """
        while index <= self.size:
            self.tree[index] += value
            index += index & -index  # Get the next index to update

    def update(self, index, value):
        """
        Updates the element at the given index in the original array and the Fenwick Tree.

        Args:
            index (int): The index to update (0-indexed).
            value (int): The new value for the element at the index.
        """
        if not 0 <= index < self.size:
            raise IndexError("Index out of bounds")
        diff = value - self.array[index] # Calculate the difference
        self.array[index] = value # Update the original array
        self._update_tree(index + 1, diff)  # Update the tree with the difference

    def query(self, index):
        """
        Calculates the prefix sum up to the given index (inclusive).

        Args:
            index (int): The index up to which to calculate the sum (0-indexed).

        Returns:
            int: The prefix sum.
        """
        if not 0 <= index < self.size:
            raise IndexError("Index out of bounds")
        index += 1  # Convert to 1-based index
        sum_val = 0
        while index > 0:
            sum_val += self.tree[index]
            index -= index & -index  # Get the parent index
        return sum_val

    def range_query(self, left, right):
        """
        Calculates the sum of the elements within the given range (inclusive).

        Args:
            left (int): The left index of the range (0-indexed).
            right (int): The right index of the range (0-indexed).

        Returns:
            int: The sum of the elements in the range [left, right].
        """
        if not 0 <= left <= right < self.size:
            raise IndexError("Indices out of bounds")
        return self.query(right) - (self.query(left - 1) if left > 0 else 0)

    def __str__(self):
        """
        Returns a string representation of the Fenwick Tree.
        """
        return f"FenwickTree(size={self.size}, tree={self.tree}, array={self.array})"

    def __repr__(self):
        """
        Official string representation for developers.
        """
        return f"FenwickTree({self.array})"

def main():
    """
    Main function to demonstrate the usage of the Fenwick Tree.
    """
    initial_array = [1, 3, 5, 2, 4, 6, 1, 3, 5]
    ft = FenwickTree(initial_array)

    print("Initial array:", initial_array)
    print("Fenwick Tree:", ft)  # Print the Fenwick Tree object

    # Example queries
    print("\nPrefix sum up to index 5:", ft.query(5))  # Sum up to index 5 (0-indexed)
    print("Range sum from index 2 to 7:", ft.range_query(2, 7))  # Sum from index 2 to 7 (inclusive)

    # Example update
    ft.update(3, 10)  # Update element at index 3 to 10
    print("\nArray after update:", ft.array)
    print("Fenwick Tree after update:", ft)
    print("Prefix sum up to index 5 after update:", ft.query(5))  # Sum up to index 5 after update
    print("Range sum from index 2 to 7 after update:", ft.range_query(2, 7))

if __name__ == "__main__":
    main()
