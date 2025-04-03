import math

class SegmentTree:
    """
    Segment Tree for performing range queries (specifically, range sum queries)
    on an array.  This implementation uses 0-based indexing.

    Attributes:
        array (list): The input array for which the segment tree is built.
        tree (list): The segment tree itself.  It's an array where each
                      element represents the sum of a range in the input array.
        size (int): The number of elements in the input array.
    """

    def __init__(self, array):
        """
        Initializes the Segment Tree with the given array.

        Args:
            array (list): The input array of numbers.
        """
        self.array = array
        self.size = len(array)
        # Calculate the height of the segment tree.  The "+ 2" ensures
        # we have enough space even if the size is not a perfect power of 2.
        height = math.ceil(math.log2(self.size)) + 1
        # Calculate the maximum size of the segment tree.
        self.max_size = 2 * (2**height) - 1
        self.tree = [0] * self.max_size  # Initialize the tree with zeros.
        self._build_tree(0, 0, self.size - 1)  # Start building the tree.

    def _build_tree(self, node_index, start, end):
        """
        Recursively builds the segment tree.

        Args:
            node_index (int): Index of the current node in the segment tree.
            start (int): Starting index of the range in the input array
                           represented by this node.
            end (int): Ending index of the range in the input array
                         represented by this node.
        """
        if start == end:
            # Leaf node: store the value from the input array.
            self.tree[node_index] = self.array[start]
        else:
            # Internal node:  Calculate the middle point of the range.
            mid = (start + end) // 2
            # Recursively build the left and right subtrees.
            self._build_tree(2 * node_index + 1, start, mid)
            self._build_tree(2 * node_index + 2, mid + 1, end)
            # Store the sum of the left and right children.
            self.tree[node_index] = self.tree[2 * node_index + 1] + self.tree[2 * node_index + 2]

    def query(self, query_start, query_end):
        """
        Performs a range sum query on the array.

        Args:
            query_start (int): Starting index of the query range.
            query_end (int): Ending index of the query range.

        Returns:
            int: The sum of the elements in the input array within the
                 specified query range.  Returns 0 if the query range is invalid.
        """
        if query_start < 0 or query_end >= self.size or query_start > query_end:
            print("Invalid query range.")  # Added for error handling
            return 0  # Return 0 for invalid range
        return self._query_helper(0, 0, self.size - 1, query_start, query_end)

    def _query_helper(self, node_index, start, end, query_start, query_end):
        """
        Recursive helper function for performing the range sum query.

        Args:
            node_index (int): Index of the current node in the segment tree.
            start (int): Starting index of the range in the input array
                           represented by this node.
            end (int): Ending index of the range in the input array
                         represented by this node.
            query_start (int): Starting index of the query range.
            query_end (int): Ending index of the query range.

        Returns:
            int: The sum of the relevant elements.
        """
        if query_start <= start and query_end >= end:
            # The current segment is completely within the query range.
            return self.tree[node_index]
        if end < query_start or start > query_end:
            # The current segment is completely outside the query range.
            return 0
        # The current segment partially overlaps the query range.
        mid = (start + end) // 2
        # Recursively query the left and right subtrees.
        left_sum = self._query_helper(2 * node_index + 1, start, mid, query_start, query_end)
        right_sum = self._query_helper(2 * node_index + 2, mid + 1, end, query_start, query_end)
        return left_sum + right_sum

    def update(self, index, value):
        """
        Updates the value of an element in the input array and propagates
        the change to the segment tree.

        Args:
            index (int): Index of the element to update in the input array.
            value (int): The new value of the element.
        """
        if index < 0 or index >= self.size:
            print("Invalid update index.") # Added for error handling.
            return
        self.array[index] = value  # Update the original array
        self._update_helper(0, 0, self.size - 1, index, value)

    def _update_helper(self, node_index, start, end, index, value):
        """
        Recursive helper function to update the segment tree.

        Args:
            node_index (int): Index of the current node in the segment tree.
            start (int): Starting index of the range in the input array
                           represented by this node.
            end (int): Ending index of the range in the input array
                         represented by this node.
            index (int): Index of the element to update in the input array.
            value (int): The new value of the element.
        """
        if start == end:
            # Leaf node: update the value in the segment tree.
            self.tree[node_index] = value
        else:
            # Internal node:
            mid = (start + end) // 2
            # Recursively update the left or right subtree, depending on the index.
            if start <= index <= mid:
                self._update_helper(2 * node_index + 1, start, mid, index, value)
            else:
                self._update_helper(2 * node_index + 2, mid + 1, end, index, value)
            # Update the current node's value based on its children.
            self.tree[node_index] = self.tree[2 * node_index + 1] + self.tree[2 * node_index + 2]

    def __repr__(self):
        """
        Returns a string representation of the SegmentTree.  Useful for debugging.
        """
        return f"SegmentTree(array={self.array}, tree={self.tree[:2*self.size-1]})" # Limit size for large trees

def main():
    """
    Main function to demonstrate the usage of the SegmentTree class with
    a sample array and query/update operations.
    """
    # Example usage:
    arr = [1, 3, 5, 7, 9, 11]
    st = SegmentTree(arr)

    print("Original Array:", arr)
    print("Segment Tree:", st) # Print the segment tree

    # Range Sum Queries
    print("Sum of range [1, 3]:", st.query(1, 3))  # Expected: 3 + 5 + 7 = 15
    print("Sum of range [0, 2]:", st.query(0, 2))  # Expected: 1 + 3 + 5 = 9
    print("Sum of range [2, 5]:", st.query(2, 5))  # Expected: 5 + 7 + 9 + 11 = 32
    print("Sum of range [0, 5]:", st.query(0, 5))  # Expected: 1 + 3 + 5 + 7 + 9 + 11 = 36
    print("Sum of range [5, 5]:", st.query(5, 5))  # Expected: 11
    print("Sum of range [0, 0]:", st.query(0, 0))  # Expected: 1
    print("Sum of range [-1, 5]:", st.query(-1, 5)) # Invalid range test.
    print("Sum of range [0, 6]:", st.query(0, 6)) # Invalid range test.
    print("Sum of range [4, 2]:", st.query(4, 2)) # Invalid range test.

    # Update Operation
    print("\nUpdating element at index 1 to 10")
    st.update(1, 10)  # Update arr[1] from 3 to 10
    print("Modified Array:", st.array)
    print("Modified Segment Tree:", st)

    print("Sum of range [1, 3] after update:", st.query(1, 3))  # Expected: 10 + 5 + 7 = 22
    print("Sum of range [0, 5] after update:", st.query(0, 5)) # Expected 1 + 10 + 5 + 7 + 9 + 11 = 43

    # Further updates
    print("\nUpdating element at index 0 to 20")
    st.update(0, 20)
    print("Modified Array:", st.array)
    print("Modified Segment Tree:", st)

    print("Sum of range [0, 2]:", st.query(0, 2)) # Expected 20 + 10 + 5 = 35

    print("\nUpdating element at index 5 to 0")
    st.update(5, 0)
    print("Modified Array:", st.array)
    print("Modified Segment Tree:", st)
    print("Sum of range [4, 5]:", st.query(4, 5)) # Expected 9 + 0 = 9

if __name__ == "__main__":
    main()

