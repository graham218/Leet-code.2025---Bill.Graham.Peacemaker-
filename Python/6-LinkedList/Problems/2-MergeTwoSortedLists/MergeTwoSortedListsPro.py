import tempfile  # Used for creating temporary files in the external storage merge approach.
import threading  # Used for implementing the multi-threaded merge approach.
import queue  # Used for implementing the stream processing merge approach.
import sqlite3 # Used for the database merge approach

class ListNode:
    """
    Represents a node in a singly linked list.

    Attributes:
        val: The value stored in the node.
        next: A reference to the next node in the list, or None if it's the last node.
    """
    def __init__(self, val=0, next=None):
        """
        Initializes a new ListNode.

        Args:
            val: The value to store in the node (default: 0).
            next: The next node in the linked list (default: None).
        """
        self.val = val  # Store the given value in the node.
        self.next = next  # Store the reference to the next node.

# Approach 1: Iterative Merge (Common Web Service Response Handling)
def mergeTwoLists_iterative(l1, l2):
    """
    Merges two sorted linked lists iteratively.  This is a very common
    and efficient approach, often used when merging data from
    web service responses, where you might get back paged and
    sorted data that needs to be combined.

    Args:
        l1: The head of the first sorted linked list.
        l2: The head of the second sorted linked list.

    Returns:
        The head of the merged sorted linked list.
    """
    dummy = ListNode()  # Create a dummy node to simplify the merging process.
    tail = dummy      # `tail` will point to the last node of the merged list so far.

    # Iterate as long as both lists have elements.
    while l1 and l2:
        if l1.val < l2.val:
            # If the current node in l1 has a smaller value, append it to the merged list.
            tail.next = l1  # Connect the current tail to the node from l1.
            l1 = l1.next    # Move to the next node in l1.
        else:
            # Otherwise, append the current node in l2 to the merged list.
            tail.next = l2  # Connect the current tail to the node from l2.
            l2 = l2.next    # Move to the next node in l2.
        tail = tail.next      # Move the tail pointer to the newly added node.

    # After one of the lists is exhausted, append the remaining part of the other list.
    tail.next = l1 or l2  #  This is a concise way to append either l1 or l2 (whichever is not None).

    return dummy.next  # Return the head of the merged list (excluding the dummy node).

# Approach 2: Recursive Merge (Used in Recursive Algorithms like Sorting in AI/ML)
def mergeTwoLists_recursive(l1, l2):
    """
    Merges two sorted linked lists recursively.  Recursive solutions
    can be very elegant and are sometimes used in AI/ML algorithms
    that process data recursively (e.g., merging sorted sub-sequences
    in a merge sort, which is used in some machine learning data
    preprocessing steps).

    Args:
        l1: The head of the first sorted linked list.
        l2: The head of the second sorted linked list.

    Returns:
        The head of the merged sorted linked list.
    """
    # Base case: If either list is empty, return the other list.
    if not l1 or not l2:
        return l1 or l2  # Returns the non-empty list, or None if both are empty.

    # Recursive step:
    if l1.val < l2.val:
        # If the current node in l1 has a smaller value:
        # 1. Recursively merge the rest of l1 with l2.
        # 2. Make the 'next' of current l1 point to the result of the recursive call.
        l1.next = mergeTwoLists_recursive(l1.next, l2)
        return l1  # Return the current l1 (which is now the head of the merged sublist).
    else:
        # If the current node in l2 has a smaller value:
        # 1. Recursively merge l1 with the rest of l2.
        # 2. Make the 'next' of current l2 point to the result of the recursive call.
        l2.next = mergeTwoLists_recursive(l1, l2.next)
        return l2  # Return the current l2.

# Approach 3: Multi-threaded Merge (Real-time Streaming Data Merge)
import threading

def mergeTwoLists_multithreaded(l1, l2):
    """
    Merges two sorted linked lists using a separate thread.  This
    approach can be beneficial in scenarios where you're dealing with
    real-time data streams (e.g., in financial applications) and
    want to perform the merge operation concurrently without
    blocking the main thread.  However, for small lists, the overhead
    of thread creation might outweigh the benefits.

    Args:
        l1: The head of the first sorted linked list.
        l2: The head of the second sorted linked list.

    Returns:
        The head of the merged sorted linked list.
    """
    result = [None]  # Use a list to store the result, as you can't directly
    # modify variables in the outer scope from within a thread.

    def merge():
        """
        Performs the merge operation in a separate thread.
        """
        result[0] = mergeTwoLists_iterative(l1, l2)  # Use the iterative merge.

    thread = threading.Thread(target=merge)  # Create a new thread.
    thread.start()             # Start the thread.
    thread.join()              # Wait for the thread to finish its execution.
    return result[0]           # Return the merged list from the result list.

# Approach 4: Merge Using Database Transactions (Efficient SQL Merge Strategy)
def mergeTwoLists_database(l1, l2):
    """
    Merges two sorted linked lists using an in-memory SQLite database.
    This approach is useful when you have data already in a database
    or when you want to leverage the sorting capabilities of SQL
    for very large lists.  It simulates a database merge operation.

    Args:
        l1: The head of the first sorted linked list.
        l2: The head of the second sorted linked list.

    Returns:
        The head of the merged sorted linked list.
    """
    # Use sqlite3, which is built-in.  Connect to an in-memory database.
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()

    # Create a table to store the merged data.
    cursor.execute("CREATE TABLE merged (value INTEGER)")

    # Insert the values from the linked lists into the table.
    while l1:
        cursor.execute("INSERT INTO merged (value) VALUES (?)", (l1.val,))
        l1 = l1.next
    while l2:
        cursor.execute("INSERT INTO merged (value) VALUES (?)", (l2.val,))
        l2 = l2.next

    # Retrieve the sorted data from the table.
    cursor.execute("SELECT value FROM merged ORDER BY value ASC")
    rows = cursor.fetchall()  # Fetch all the sorted rows.
    conn.close()             # Close the database connection.

    # Convert the sorted rows back into a linked list.
    dummy = ListNode()
    tail = dummy
    for row in rows:
        tail.next = ListNode(row[0])  # row[0] contains the 'value' from the table.
        tail = tail.next
    return dummy.next

# Approach 5: Merge Using External Storage (Handling Large Files on Disk)
def mergeTwoLists_external_storage(l1, l2):
    """
    Merges two sorted linked lists by writing their contents to a temporary
    file and then reading the merged sorted data.  This is essential
    when dealing with datasets that are too large to fit into memory.
    It simulates a merge operation that might be done in a distributed
    file system or when processing very large log files.

    Args:
        l1: The head of the first sorted linked list.
        l2: The head of the second sorted linked list.

    Returns:
        The name of the temporary file containing the merged sorted data.
    """
    # Create a temporary file to store the merged data.
    with tempfile.NamedTemporaryFile(delete=False, mode="w", suffix=".txt") as f:
        file_name = f.name  # Get the name of the temporary file.
        # Write the sorted values from the linked lists to the file.
        while l1 and l2:
            if l1.val < l2.val:
                f.write(str(l1.val) + "\n")  # Write value followed by a newline.
                l1 = l1.next
            else:
                f.write(str(l2.val) + "\n")
                l2 = l2.next
        while l1:
            f.write(str(l1.val) + "\n")
            l1 = l1.next
        while l2:
            f.write(str(l2.val) + "\n")
            l2 = l2.next
    return file_name  # Return the name of the file.  The caller is responsible for reading it.

# Approach 6: Merge with Stream Processing (Real-time Data Aggregation)
def mergeTwoLists_stream_processing(l1, l2):
    """
    Merges two sorted linked lists using a priority queue (implemented with the
    'queue' module).  This approach is suitable for scenarios involving
    real-time data streams, where you need to merge sorted data as it arrives.
    It simulates merging data from sorted streams, maintaining sorted order.

    Args:
        l1: The head of the first sorted linked list.
        l2: The head of the second sorted linked list.

    Returns:
        The head of the merged sorted linked list.
    """
    stream_queue = queue.PriorityQueue()  # Create a priority queue.
    #  The queue will automatically sort the items.

    # Add the nodes from the linked lists to the priority queue.
    #  The priority queue stores tuples (value, node), and sorts based on the value.
    while l1:
        stream_queue.put((l1.val, l1))
        l1 = l1.next
    while l2:
        stream_queue.put((l2.val, l2))
        l2 = l2.next

    # Create a new linked list from the sorted nodes in the priority queue.
    dummy = ListNode()
    tail = dummy
    while not stream_queue.empty():
        val, node = stream_queue.get()  # Get the node with the smallest value.
        tail.next = node             # Append it to the merged list.
        tail = tail.next
    tail.next = None  # Ensure the last node's 'next' is None.
    return dummy.next

# Utility Functions
def create_linked_list(vals):
    """
    Creates a linked list from a list of values.

    Args:
        vals: A list of values to create the linked list from.

    Returns:
        The head of the created linked list.
    """
    dummy = ListNode()
    tail = dummy
    for val in vals:
        tail.next = ListNode(val)
        tail = tail.next
    return dummy.next

def print_linked_list(node):
    """
    Prints the values of a linked list in a readable format.

    Args:
        node: The head of the linked list to print.
    """
    values = []
    while node:
        values.append(str(node.val))
        node = node.next
    print(" -> ".join(values))

# Example Usage
l1 = create_linked_list([1, 3, 5])
l2 = create_linked_list([2, 4, 6])

print("Iterative Merge:")
print_linked_list(mergeTwoLists_iterative(l1, l2))

l1 = create_linked_list([1, 3, 5])
l2 = create_linked_list([2, 4, 6])
print("Recursive Merge:")
print_linked_list(mergeTwoLists_recursive(l1, l2))

l1 = create_linked_list([1, 3, 5])
l2 = create_linked_list([2, 4, 6])
print("Multi-threaded Merge:")
print_linked_list(mergeTwoLists_multithreaded(l1, l2))

l1 = create_linked_list([1, 3, 5])
l2 = create_linked_list([2, 4, 6])
print("Database Merge:")
print_linked_list(mergeTwoLists_database(l1, l2))

l1 = create_linked_list([1, 3, 5])
l2 = create_linked_list([2, 4, 6])
print("External Storage Merge (File Path):", mergeTwoLists_external_storage(l1, l2))

l1 = create_linked_list([1, 3, 5])
l2 = create_linked_list([2, 4, 6])
print("Stream Processing Merge:")
print_linked_list(mergeTwoLists_stream_processing(l1, l2))
