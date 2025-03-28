class ListNode:
    def __init__(self, val=0, next=None):
        """
        Initializes a ListNode.

        Args:
            val: The value of the node (default: 0).
            next: The next node in the list (default: None).
        """
        self.val = val
        self.next = next

def create_linked_list(arr):
    """
    Creates a linked list from a Python list.

    Args:
        arr: The Python list to convert to a linked list.

    Returns:
        The head of the created linked list.  Returns None if the input array is empty.
    """
    if not arr:
        return None  # Handle empty array case
    head = ListNode(arr[0])  # Create the head node with the first element
    curr = head  # Initialize a pointer to the current node
    for i in range(1, len(arr)):
        curr.next = ListNode(arr[i])  # Create a new node and link it
        curr = curr.next  # Move the current pointer to the newly added node
    return head

def print_linked_list(head):
    """
    Prints the elements of a linked list.

    Args:
        head: The head of the linked list.
    """
    curr = head  # Start from the head
    while curr:
        print(curr.val, end=" -> ")  # Print the value of the current node
        curr = curr.next  # Move to the next node
    print("None")  # Print "None" to indicate the end of the list

# 1. Iterative Approach (Most Common)
def reverse_linked_list_iterative(head):
    """
    Reverses a linked list iteratively.

    Args:
        head: The head of the linked list.

    Returns:
        The head of the reversed linked list.
    """
    prev = None  # Initialize 'prev' to None (for the new tail)
    curr = head  # Initialize 'curr' to the head of the list
    while curr:
        next_node = curr.next  # Store the next node (before we change curr.next)
        curr.next = prev  # Reverse the pointer: curr.next now points to the previous node
        prev = curr  # Move 'prev' to the current node
        curr = next_node  # Move 'curr' to the next node
    return prev  # 'prev' will be the new head of the reversed list

# 2. Recursive Approach (Classic)
def reverse_linked_list_recursive(head):
    """
    Reverses a linked list recursively.

    Args:
        head: The head of the linked list.

    Returns:
        The head of the reversed linked list.
    """
    if not head or not head.next:
        return head  # Base case: empty list or single node list is already reversed
    new_head = reverse_linked_list_recursive(head.next)  # Recursively reverse the rest of the list
    head.next.next = head  # Make the next node point back to the current node
    head.next = None  # Set the original next pointer to None (important for the new tail)
    return new_head  # Return the new head of the reversed list

# 3. Using a Stack (For educational purposes, not usually optimal)
def reverse_linked_list_stack(head):
    """
    Reverses a linked list using a stack.

    Args:
        head: The head of the linked list.

    Returns:
        The head of the reversed linked list.
    """
    stack = []  # Create an empty stack
    curr = head  # Start from the head
    while curr:
        stack.append(curr)  # Push each node onto the stack
        curr = curr.next
    if not stack:
        return None  # Handle empty list
    new_head = stack.pop()  # The last node becomes the new head
    curr = new_head  # Start building the reversed list
    while stack:
        curr.next = stack.pop()  # Connect the current node to the top of the stack
        curr = curr.next  # Move to the next node
    curr.next = None  # Set the last node's next pointer to None
    return new_head

# 4. In-Place Iterative with Three Pointers (Optimized Iterative)
def reverse_linked_list_in_place(head):
    """
    Reverses a linked list in-place using three pointers.  This is an optimized iterative approach.

    Args:
        head: The head of the linked list.

    Returns:
        The head of the reversed linked list.
    """
    if not head:
        return None
    prev = None
    curr = head
    while curr:
        temp = curr.next  # Store the next node
        curr.next = prev  # Reverse the link
        prev = curr       # Move prev to the current node
        curr = temp      # Move curr to the next node
    return prev

# 5. Reverse in Groups of K (Real World: pagination style reversal)
def reverse_k_group(head, k):
    """
    Reverses the linked list in groups of k nodes.

    Args:
        head: The head of the linked list.
        k: The size of the group to reverse.

    Returns:
        The head of the modified linked list.
    """
    def reverse(head, k):
        """
        Helper function to reverse a group of k nodes.

        Args:
            head: The head of the group.
            k: The size of the group.

        Returns:
            A tuple containing the new head of the reversed group and the next node after the group.
        """
        prev, curr = None, head
        count = 0
        while curr and count < k:
            next_node = curr.next
            curr.next = prev
            prev = curr
            curr = next_node
            count += 1
        return prev, curr  # Returns the new head of the reversed group, and the node after the reversed group

    if not head:
        return None

    curr = head
    count = 0
    while curr and count < k:
        curr = curr.next
        count += 1

    if count < k:  # If there are fewer than k nodes, don't reverse
        return head

    reversed_head, next_group_head = reverse(head, k)  # Reverse the first k nodes
    head.next = reverse_k_group(next_group_head, k)  # Recursively reverse the remaining groups
    return reversed_head  # Return the new head of the list

# 6. Reverse a Sublist (Real world: specific portion of list needs reversal)
def reverse_between(head, left, right):
    """
    Reverses the nodes of a linked list from left to right (1-indexed).

    Args:
        head: The head of the linked list.
        left: The starting position of the sublist to reverse (1-indexed).
        right: The ending position of the sublist to reverse (1-indexed).

    Returns:
        The head of the modified linked list.
    """
    if not head:
        return None

    dummy = ListNode(0)  # Create a dummy node to handle the case where left = 1
    dummy.next = head
    prev = dummy  # 'prev' will be the node before the sublist to reverse

    for _ in range(left - 1):
        prev = prev.next  # Move 'prev' to the node before the sublist

    curr = prev.next  # 'curr' is the first node of the sublist
    tail = curr # keep track of the tail of the reversed sublist

    for _ in range(right - left):
        temp = curr.next      # Store the next node
        curr.next = temp.next # Adjust current node's next pointer
        temp.next = prev.next  # Insert the stored node before 'prev.next'
        prev.next = temp      # Update 'prev.next' to point to the inserted node

    return dummy.next  # Return the head of the modified list

# Example Usage
arr = [1, 2, 3, 4, 5]
head = create_linked_list(arr)
print("Original List:")
print_linked_list(head)

# Iterative Reverse
reversed_head_iterative = reverse_linked_list_iterative(create_linked_list(arr))
print("\nIterative Reversed List:")
print_linked_list(reversed_head_iterative)

# Recursive Reverse
reversed_head_recursive = reverse_linked_list_recursive(create_linked_list(arr))
print("\nRecursive Reversed List:")
print_linked_list(reversed_head_recursive)

# Stack Reverse
reversed_head_stack = reverse_linked_list_stack(create_linked_list(arr))
print("\nStack Reversed List:")
print_linked_list(reversed_head_stack)

# In-Place Reverse
reversed_head_in_place = reverse_linked_list_in_place(create_linked_list(arr))
print("\nIn-Place Reversed List:")
print_linked_list(reversed_head_in_place)

# Reverse K Group
head_k_group = create_linked_list([1, 2, 3, 4, 5, 6, 7, 8])
reversed_head_k_group = reverse_k_group(head_k_group, 3)
print("\nReversed K Group (K=3):")
print_linked_list(reversed_head_k_group)

# Reverse Between
head_between = create_linked_list([1, 2, 3, 4, 5])
reversed_head_between = reverse_between(head_between, 2, 4)
print("\nReversed Between (2, 4):")
print_linked_list(reversed_head_between)
