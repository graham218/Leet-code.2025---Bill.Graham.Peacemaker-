class ListNode:
    def __init__(self, val=0, next=None):
        """
        Initializes a ListNode object.

        Args:
            val (int, optional): The value of the node. Defaults to 0.
            next (ListNode, optional): The next node in the linked list. Defaults to None.
        """
        self.val = val  # Store the value of the node
        self.next = next  # Store the reference to the next node

# Approach 1: Iterative Merge
# Time Complexity: O(m + n), Space Complexity: O(1)
def mergeTwoLists_iterative(l1, l2):
    """
    Merges two sorted linked lists iteratively.

    Args:
        l1 (ListNode): The head of the first sorted linked list.
        l2 (ListNode): The head of the second sorted linked list.

    Returns:
        ListNode: The head of the merged sorted linked list.
    """
    dummy = ListNode()  # Create a dummy node to simplify the merging process.
    tail = dummy  # Initialize a 'tail' pointer to the dummy node.  'tail' will track the end of the merged list.

    while l1 and l2:  # Iterate as long as both input lists have nodes.
        if l1.val < l2.val:  # Compare the values of the current nodes in l1 and l2.
            tail.next = l1  # If the current node in l1 has a smaller value, append it to the merged list.
            l1 = l1.next  # Move the l1 pointer to the next node in l1.
        else:
            tail.next = l2  # Otherwise, append the current node in l2 to the merged list.
            l2 = l2.next  # Move the l2 pointer to the next node in l2.
        tail = tail.next  # Move the 'tail' pointer to the newly added node in the merged list.

    # After the loop, one of the lists might have remaining nodes.  Append them to the merged list.
    tail.next = l1 or l2  # This is a concise way to append either l1 or l2 (or both if they are both empty, which is fine).

    return dummy.next  # Return the head of the merged list.  We return dummy.next because dummy is an empty node.

# Approach 2: Recursive Merge
# Time Complexity: O(m + n), Space Complexity: O(m + n) due to recursion depth
def mergeTwoLists_recursive(l1, l2):
    """
    Merges two sorted linked lists recursively.

    Args:
        l1 (ListNode): The head of the first sorted linked list.
        l2 (ListNode): The head of the second sorted linked list.

    Returns:
        ListNode: The head of the merged sorted linked list.
    """
    if not l1:  # Base case: If l1 is empty, return l2 (which might also be empty).
        return l2
    if not l2:  # Base case: If l2 is empty, return l1 (which might also be empty).
        return l1

    if l1.val < l2.val:  # Recursive step: If the current node in l1 has a smaller value:
        l1.next = mergeTwoLists_recursive(l1.next, l2)  # Recursively merge the rest of l1 with l2.
        return l1  # Return l1 as the head of the merged list.
    else:  # Otherwise, the current node in l2 has a smaller or equal value:
        l2.next = mergeTwoLists_recursive(l1, l2.next)  # Recursively merge l1 with the rest of l2.
        return l2  # Return l2 as the head of the merged list.

# Approach 3: Using a Min Heap (Priority Queue)
# Time Complexity: O((m + n) log (m + n)), Space Complexity: O(m + n)
import heapq  # Import the heapq module for min-heap operations.

def mergeTwoLists_heap(l1, l2):
    """
    Merges two sorted linked lists using a min heap (priority queue).

    Args:
        l1 (ListNode): The head of the first sorted linked list.
        l2 (ListNode): The head of the second sorted linked list.

    Returns:
        ListNode: The head of the merged sorted linked list.
    """
    heap = []  # Initialize an empty list to be used as a min-heap.
    while l1:  # Iterate through the first linked list.
        heapq.heappush(heap, (l1.val, l1))  # Push each node of l1 onto the heap, using the node's value as the priority.
        l1 = l1.next  # Move to the next node in l1.
    while l2:  # Iterate through the second linked list.
        heapq.heappush(heap, (l2.val, l2))  # Push each node of l2 onto the heap.
        l2 = l2.next  # Move to the next node in l2.

    dummy = ListNode()  # Create a dummy node for the merged list.
    tail = dummy  # Initialize the 'tail' pointer to the dummy node.

    while heap:  # Iterate while the heap is not empty.
        val, node = heapq.heappop(heap)  # Pop the node with the smallest value from the heap.
        tail.next = node  # Append the popped node to the merged list.
        tail = tail.next  # Move the 'tail' pointer to the newly added node.

    tail.next = None  # explicitly set the next pointer of the last node to None.
    return dummy.next  # Return the head of the merged list.

# Approach 4: Merge Sort Style (Divide and Conquer)
# Time Complexity: O(N log K), Space Complexity: O(1)  where N is the total number of nodes and K is the number of lists
def mergeTwoLists_divide_and_conquer(lists):
    """
    Merges k sorted linked lists using a divide and conquer approach.
    This approach is more general and can merge k lists, not just 2.
    It uses the iterative mergeTwoLists function.

    Args:
        lists (list): A list of sorted linked lists.

    Returns:
        ListNode: The head of the merged sorted linked list.
    """
    if not lists:  # Handle the case where the input list of lists is empty.
        return None

    while len(lists) > 1:  # Continue merging until only one list remains.
        new_lists = []  # Create a list to store the merged sublists.
        for i in range(0, len(lists), 2):  # Iterate through the lists in pairs.
            l1 = lists[i]  # Get the first list in the pair.
            l2 = lists[i + 1] if i + 1 < len(lists) else None  # Get the second list, or None if there's no second list.
            merged_list = mergeTwoLists_iterative(l1, l2) # Use the iterative merge function
            new_lists.append(merged_list)  # Append the merged list to the new list.
        lists = new_lists  # Update the lists to be the new_lists for the next iteration.

    return lists[0]  # Return the last remaining list, which is the fully merged list.

# Approach 5: Flatten and Sort
# Time Complexity: O((m + n) log (m + n)), Space Complexity: O(m + n)
def mergeTwoLists_flatten_and_sort(l1, l2):
    """
    Merges two sorted linked lists by flattening them into a single list,
    sorting the list, and then creating a new sorted linked list.

    Args:
        l1 (ListNode): The head of the first sorted linked list.
        l2 (ListNode): The head of the second sorted linked list.

    Returns:
        ListNode: The head of the merged sorted linked list.
    """
    nodes = []  # Initialize an empty list to store the values of all nodes.

    while l1:  # Iterate through the first linked list.
        nodes.append(l1.val)  # Append the value of each node to the 'nodes' list.
        l1 = l1.next  # Move to the next node in l1.

    while l2:  # Iterate through the second linked list.
        nodes.append(l2.val)  # Append the value of each node to the 'nodes' list.
        l2 = l2.next  # Move to the next node in l2.

    nodes.sort()  # Sort the 'nodes' list in ascending order.

    dummy = ListNode()  # Create a dummy node for the new merged linked list.
    tail = dummy  # Initialize the 'tail' pointer to the dummy node.

    for val in nodes:  # Iterate through the sorted values in the 'nodes' list.
        tail.next = ListNode(val)  # Create a new node with the value and append it to the merged list.
        tail = tail.next  # Move the 'tail' pointer to the newly added node.

    return dummy.next  # Return the head of the new merged linked list.

# Utility function to create a linked list from a list
def create_linked_list(vals):
    """
    Creates a linked list from a Python list of values.

    Args:
        vals (list): A list of integer values.

    Returns:
        ListNode: The head of the created linked list.
    """
    dummy = ListNode()  # Create a dummy node.
    tail = dummy  # Initialize a 'tail' pointer.
    for val in vals:  # Iterate through the input list of values.
        tail.next = ListNode(val)  # Create a new node with the value and append it to the list.
        tail = tail.next  # Move the tail pointer to the newly added node
    return dummy.next  # Return the head of the linked list.

# Utility function to print a linked list
def print_linked_list(node):
    """
    Prints the values of a linked list in a readable format.

    Args:
        node (ListNode): The head of the linked list to print.
    """
    values = []
    while node:  # Iterate through the linked list.
        values.append(str(node.val))  # Convert the node's value to a string and append it to the list.
        node = node.next  # Move to the next node.
    print(" -> ".join(values))  # Print the values, joined by " -> ".

# Example Usage
l1 = create_linked_list([1, 3, 5])  # Create the first sorted linked list: 1 -> 3 -> 5
l2 = create_linked_list([2, 4, 6])  # Create the second sorted linked list: 2 -> 4 -> 6

print("Iterative Merge:")
print_linked_list(mergeTwoLists_iterative(l1, l2))  # Merge and print using the iterative approach.

l1 = create_linked_list([1, 3, 5])
l2 = create_linked_list([2, 4, 6])
print("Recursive Merge:")
print_linked_list(mergeTwoLists_recursive(l1, l2))  # Merge and print using the recursive approach.

l1 = create_linked_list([1, 3, 5])
l2 = create_linked_list([2, 4, 6])
print("Heap Merge:")
print_linked_list(mergeTwoLists_heap(l1, l2))  # Merge and print using the heap-based approach.

l1 = create_linked_list([1, 3, 5])
l2 = create_linked_list([2, 4, 6])
print("Divide and Conquer Merge:")
print_linked_list(mergeTwoLists_divide_and_conquer([l1, l2]))  # Merge and print using divide and conquer

l1 = create_linked_list([1, 3, 5])
l2 = create_linked_list([2, 4, 6])
print("Flatten and Sort Merge:")
print_linked_list(mergeTwoLists_flatten_and_sort(l1, l2))  # Merge and print using the flatten and sort approach.
