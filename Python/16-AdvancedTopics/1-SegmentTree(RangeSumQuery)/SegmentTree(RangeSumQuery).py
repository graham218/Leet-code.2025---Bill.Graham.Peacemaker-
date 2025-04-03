class SegmentTree:
    """
    Segment Tree for Range Sum Query
    """

    def __init__(self, arr):
        """
        Initializes the Segment Tree.

        Args:
            arr (list): The input array for which the segment tree is built.
        """
        self.arr = arr
        n = len(arr)
        # The segment tree array will have a size of at most 4*n.
        self.tree = [0] * (4 * n)  # Initialize the tree with zeros
        self.n = n
        if n > 0:
            self._build(0, 0, n - 1)  # Start building the tree

    def _build(self, node, start, end):
        """
        Recursively builds the segment tree.

        Args:
            node (int): The index of the current node in the segment tree.
            start (int): The starting index of the current segment in the input array.
            end (int): The ending index of the current segment in the input array.
        """
        if start == end:
            # If the segment contains only one element, store that element in the tree node.
            self.tree[node] = self.arr[start]
        else:
            # Calculate the middle index of the segment.
            mid = (start + end) // 2
            # Recursively build the left and right subtrees.
            self._build(2 * node + 1, start, mid)
            self._build(2 * node + 2, mid + 1, end)
            # The value of the current node is the sum of its children.
            self.tree[node] = self.tree[2 * node + 1] + self.tree[2 * node + 2]

    def query(self, left, right):
        """
        Performs a range sum query on the segment tree.

        Args:
            left (int): The starting index of the query range.
            right (int): The ending index of the query range.

        Returns:
            int: The sum of the elements in the query range.
        """
        if not (0 <= left <= right < self.n):
            return 0  # Handle invalid query range
        return self._query(0, 0, self.n - 1, left, right)

    def _query(self, node, start, end, left, right):
        """
        Recursively performs the range sum query.

        Args:
            node (int): The index of the current node in the segment tree.
            start (int): The starting index of the current segment in the input array.
            end (int): The ending index of the current segment in the input array.
            left (int): The starting index of the query range.
            right (int): The ending index of the query range.

        Returns:
            int: The sum of the elements in the query range.
        """
        if right < start or end < left:
            # If the query range does not overlap with the current segment, return 0.
            return 0
        if left <= start and end <= right:
            # If the query range completely covers the current segment, return the value of the current node.
            return self.tree[node]
        # Calculate the middle index of the segment.
        mid = (start + end) // 2
        # Recursively query the left and right subtrees.
        left_sum = self._query(2 * node + 1, start, mid, left, right)
        right_sum = self._query(2 * node + 2, mid + 1, end, left, right)
        # Return the sum of the results from the left and right subtrees.
        return left_sum + right_sum

    def update(self, index, val):
        """
        Updates the value of an element in the input array and updates the segment tree accordingly.

        Args:
            index (int): The index of the element to update.
            val (int): The new value of the element.
        """
        if not (0 <= index < self.n):
            return  # Handle invalid index
        self.arr[index] = val  # Update the original array
        self._update(0, 0, self.n - 1, index, val)

    def _update(self, node, start, end, index, val):
        """
        Recursively updates the segment tree.

        Args:
            node (int): The index of the current node in the segment tree.
            start (int): The starting index of the current segment in the input array.
            end (int): The ending index of the current segment in the input array.
            index (int): The index of the element to update.
            val (int): The new value of the element.
        """
        if start == end:
            # If the current segment contains only the element to update, update the value of the node.
            self.tree[node] = val
        else:
            # Calculate the middle index of the segment.
            mid = (start + end) // 2
            # Recursively update the left or right subtree, depending on which side the index is on.
            if start <= index <= mid:
                self._update(2 * node + 1, start, mid, index, val)
            else:
                self._update(2 * node + 2, mid + 1, end, index, val)
            # Update the value of the current node based on the updated children.
            self.tree[node] = self.tree[2 * node + 1] + self.tree[2 * node + 2]

def main():
    """
    Main function to demonstrate the usage of the SegmentTree class.
    """
    arr = [1, 3, 5, 7, 9, 11]  # Example input array
    st = SegmentTree(arr)  # Create a SegmentTree object

    # Perform some range sum queries
    print("Sum of range (1, 3):", st.query(1, 3))  # Expected output: 15 (3 + 5 + 7)
    print("Sum of range (0, 2):", st.query(0, 2))  # Expected output: 9 (1 + 3 + 5)
    print("Sum of range (2, 5):", st.query(2, 5))  # Expected output: 32 (5 + 7 + 9 + 11)

    # Update an element and perform a query
    st.update(1, 2)  # Update the element at index 1 to 2
    print("Sum of range (0, 2) after update:", st.query(0, 2))  # Expected output: 8 (1 + 2 + 5)

    # Example with negative numbers
    arr2 = [-1, 2, -3, 4, -5]
    st2 = SegmentTree(arr2)
    print("Sum of range (0, 4) for arr2:", st2.query(0, 4))  # Expected output: -3

    print("Sum of range (1, 3) for arr2:", st2.query(1, 3))
    st2.update(2, 5)
    print("Sum of range (0, 4) for arr2 after update:", st2.query(0, 4))

if __name__ == "__main__":
    main()
