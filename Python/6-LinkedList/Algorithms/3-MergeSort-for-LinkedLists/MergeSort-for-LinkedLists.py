class ListNode:
    def __init__(self, val=0, next=None):
        """
        Initializes a ListNode with a value and a pointer to the next node.

        Args:
            val (int, optional): The value of the node. Defaults to 0.
            next (ListNode, optional): The next node in the linked list. Defaults to None.
        """
        self.val = val  # Store the value of the node
        self.next = next # Store the reference to the next node

# Approach 1: Merge Sort with Recursion
def merge_sort_recursive(head):
    """
    Sorts a linked list using the merge sort algorithm recursively.

    Args:
        head (ListNode): The head of the linked list to be sorted.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    # Base case: If the list is empty or has only one node, it's already sorted.
    if not head or not head.next:
        return head

    # 1. Split the list into two halves
    mid = get_middle(head)       # Find the middle node
    right = mid.next            # Get the head of the right sublist
    mid.next = None             # Disconnect the left sublist

    # 2. Recursively sort the two halves
    left_sorted = merge_sort_recursive(head)    # Sort the left sublist
    right_sorted = merge_sort_recursive(right)  # Sort the right sublist

    # 3. Merge the sorted halves
    return merge(left_sorted, right_sorted)  # Merge the sorted sublists and return the head of the merged list

def get_middle(head):
    """
    Finds the middle node of a linked list using the slow and fast pointer technique.

    Args:
        head (ListNode): The head of the linked list.

    Returns:
        ListNode: The middle node of the linked list.
    """
    # Handle empty list
    if not head:
        return None

    slow, fast = head, head  # Initialize slow and fast pointers to the head

    # Move slow one step and fast two steps until fast reaches the end
    while fast.next and fast.next.next:
        slow = slow.next       # Slow pointer moves one step at a time
        fast = fast.next.next  # Fast pointer moves two steps at a time
    return slow  # When fast reaches the end, slow is at the middle

def merge(left, right):
    """
    Merges two sorted linked lists into a single sorted linked list.

    Args:
        left (ListNode): The head of the first sorted linked list.
        right (ListNode): The head of the second sorted linked list.

    Returns:
        ListNode: The head of the merged sorted linked list.
    """
    dummy = ListNode()  # Create a dummy node to simplify the merging process
    tail = dummy        # Initialize tail to the dummy node

    # Compare nodes from both lists and add the smaller one to the merged list
    while left and right:
        if left.val < right.val:
            tail.next = left  # Append the smaller node to the merged list
            left = left.next
        else:
            tail.next = right # Append the smaller node to the merged list
            right = right.next
        tail = tail.next      # Move the tail pointer to the newly added node

    # Add the remaining nodes from either list (if any)
    tail.next = left or right  # Append the remaining nodes from either list
    return dummy.next          # Return the head of the merged list (excluding the dummy node)

# Approach 2: Iterative Merge Sort
def merge_sort_iterative(head):
    """
    Sorts a linked list using the merge sort algorithm iteratively.

    Args:
        head (ListNode): The head of the linked list to be sorted.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    if not head or not head.next:
        return head

    size = get_size(head)       # Get the length of the linked list
    dummy = ListNode(0, head) # Create a dummy node pointing to the head
    step = 1                  # Initialize the step size for merging

    # Iterate until the step size is greater than or equal to the size of the list
    while step < size:
        prev, curr = dummy, dummy.next # Initialize prev and curr pointers
        while curr:
            left = curr             # 'left' is the start of the first sublist
            right = split(left, step)  # Split the list into two sublists of size 'step'
            curr = split(right, step)  # 'curr' becomes the start of the next pair of sublists
            merged = merge(left, right) # Merge the two sublists
            prev.next = merged      # Connect the merged sublist to the sorted portion
            # Move 'prev' to the end of the merged sublist
            while prev.next:
                prev = prev.next
        step *= 2  # Double the step size for the next iteration

    return dummy.next # Return the head of the sorted list

def get_size(head):
    """
    Gets the number of nodes in a linked list.

    Args:
        head (ListNode): The head of the linked list.

    Returns:
        int: The number of nodes in the linked list.
    """
    count = 0
    while head:
        count += 1
        head = head.next
    return count

def split(head, step):
    """
    Splits a linked list into two parts at the given step.

    Args:
        head (ListNode): The head of the linked list.
        step (int): The number of nodes to include in the first part.

    Returns:
        ListNode: The head of the second part of the linked list, or None if the first part has fewer than 'step' nodes.
    """
    if not head:
        return None

    # Move 'head' to the node just before the split point
    for _ in range(step - 1):
        if not head.next:
            break # Stop if we reach the end of the list
        head = head.next

    next_head = head.next # Store the head of the second part
    head.next = None      # Disconnect the two parts
    return next_head

# Approach 3: Merge Sort using Stack (Iterative)
def merge_sort_stack(head):
    """
    Sorts a linked list using a stack and iterative merging.

    Args:
        head (ListNode): The head of the linked list.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    if not head or not head.next:
        return head

    stack = []
    # Push each node as a single-node sorted list onto the stack
    while head:
        temp = head.next
        head.next = None  # Important: isolate each node
        stack.append(head)
        head = temp

    # Repeatedly merge pairs of lists from the stack until only one remains
    while len(stack) > 1:
        # pop 2 elements from the stack, merge them, and push back
        stack.append(merge(stack.pop(0), stack.pop(0)))

    return stack[0]  # The last element in the stack is the sorted list

# Approach 4: Merge Sort with Array Conversion
def merge_sort_array(head):
    """
    Sorts a linked list by converting it to an array, sorting the array, and then reconstructing the linked list.

    Args:
        head (ListNode): The head of the linked list.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    if not head or not head.next:
        return head

    nodes = []
    # Convert the linked list to an array of nodes
    while head:
        nodes.append(head)
        head = head.next

    # Sort the array of nodes based on their values
    nodes.sort(key=lambda node: node.val)

    # Reconstruct the linked list from the sorted array
    dummy = ListNode()
    tail = dummy
    for node in nodes:
        tail.next = node
        tail = node
    tail.next = None  # Ensure the last node's next is None

    return dummy.next

# Approach 5: Merge Sort using PriorityQueue
from queue import PriorityQueue

def merge_sort_pq(head):
    """
    Sorts a linked list using a priority queue.

    Args:
        head (ListNode): The head of the linked list.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    if not head or not head.next:
        return head

    pq = PriorityQueue()
    # Add each node to the priority queue with its value as the priority
    while head:
        pq.put((head.val, head))  # PriorityQueue sorts based on the first element of the tuple
        head = head.next

    # Create a new sorted linked list by extracting nodes from the priority queue
    dummy = ListNode()
    tail = dummy
    while not pq.empty():
        _, node = pq.get() # Get the node with the smallest value
        tail.next = node
        tail = node
    tail.next = None

    return dummy.next

# Helper Function to Print Linked List
def print_list(head):
    """
    Prints the values of a linked list in a readable format.

    Args:
        head (ListNode): The head of the linked list.
    """
    result = []
    while head:
        result.append(str(head.val))
        head = head.next
    print(" -> ".join(result))

# Test Cases
# Create a linked list: 4 -> 2 -> 1 -> 3
nodes = [ListNode(val) for val in [4, 2, 1, 3]]
for i in range(len(nodes) - 1):
    nodes[i].next = nodes[i + 1]

print("Original List:")
print_list(nodes[0])

sorted_head_recursive = merge_sort_recursive(nodes[0])
print("Sorted List (Recursive):")
print_list(sorted_head_recursive)

nodes = [ListNode(val) for val in [4, 2, 1, 3]]
for i in range(len(nodes) - 1):
    nodes[i].next = nodes[i + 1]

sorted_head_iterative = merge_sort_iterative(nodes[0])
print("Sorted List (Iterative):")
print_list(sorted_head_iterative)

nodes = [ListNode(val) for val in [4, 2, 1, 3]]
for i in range(len(nodes) - 1):
    nodes[i].next = nodes[i + 1]

sorted_head_stack = merge_sort_stack(nodes[0])
print("Sorted List (Stack):")
print_list(sorted_head_stack)

nodes = [ListNode(val) for val in [4, 2, 1, 3]]
for i in range(len(nodes) - 1):
    nodes[i].next = nodes[i + 1]

sorted_head_array = merge_sort_array(nodes[0])
print("Sorted List (Array Conversion):")
print_list(sorted_head_array)

nodes = [ListNode(val) for val in [4, 2, 1, 3]]
for i in range(len(nodes) - 1):
    nodes[i].next = nodes[i + 1]

sorted_head_pq = merge_sort_pq(nodes[0])
print("Sorted List (PriorityQueue):")
print_list(sorted_head_pq)
