class ListNode:
    """
    Definition for singly-linked list.
    Each node has a value (`val`) and a pointer to the next node (`next`).
    """
    def __init__(self, val=0, next=None):
        """
        Initializes a new ListNode.

        Args:
            val (int, optional): The value of the node. Defaults to 0.
            next (ListNode, optional): The next node in the list. Defaults to None.
        """
        self.val = val
        self.next = next

# 1. Iterative Approach
# Time Complexity: O(n), Space Complexity: O(1)
def reverse_list_iterative(head):
    """
    Reverses a singly linked list iteratively.

    This function reverses the linked list by changing the direction of the
    pointers of each node. It uses three pointers: `prev`, `current`, and
    `next_node`.

    Args:
        head (ListNode): The head of the linked list to be reversed.

    Returns:
        ListNode: The new head of the reversed linked list.

    Algorithm:
        1. Initialize `prev` to None, `current` to head.
        2. Iterate through the list while `current` is not None:
            a. Store the next node in `next_node`.
            b. Change the `next` pointer of `current` to point to `prev`.
            c. Move `prev` to `current`.
            d. Move `current` to `next_node`.
        3. `prev` will be the new head of the reversed list.
    """
    prev = None  # Initialize previous node to None
    current = head  # Initialize current node to the head
    while current:
        next_node = current.next  # Store the next node
        current.next = prev  # Reverse the link: point current.next to prev
        prev = current  # Move prev to the current node
        current = next_node  # Move current to the next node
    return prev  # prev is the new head of the reversed list

# 2. Recursive Approach
# Time Complexity: O(n), Space Complexity: O(n) (recursive call stack)
def reverse_list_recursive(head):
    """
    Reverses a singly linked list recursively.

    This function reverses the linked list using recursion.  The base case is
    when the list is empty or has only one node.  The recursive step reverses
    the rest of the list and then attaches the current node to the end of the
    reversed part.

    Args:
        head (ListNode): The head of the linked list to be reversed.

    Returns:
        ListNode: The new head of the reversed linked list.

    Algorithm:
        1. Base case: If the list is empty (not head) or has one node (not head.next),
           return the head.
        2. Recursively call the function on the rest of the list (head.next).  This
           will eventually return the new head of the reversed sublist.
        3. Modify pointers:
            a. head.next.next should point to head.
            b. head.next should point to None.
        4. Return the new head obtained from the recursive call.
    """
    if not head or not head.next:  # Base case: empty or single-node list
        return head
    new_head = reverse_list_recursive(head.next)  # Recursive call on the rest
    head.next.next = head  # Reverse the pointer: next node's next points to current
    head.next = None  # Set the original next pointer to None
    return new_head  # Return the new head from the recursion

# 3. Using a Stack
# Time Complexity: O(n), Space Complexity: O(n)
def reverse_list_stack(head):
    """
    Reverses a singly linked list using a stack.

    This function uses a stack to store the nodes of the linked list and then
    reconstructs the list in reverse order.

    Args:
        head (ListNode): The head of the linked list to be reversed.

    Returns:
        ListNode: The new head of the reversed linked list.

    Algorithm:
        1. Create an empty stack.
        2. Iterate through the linked list and push each node onto the stack.
        3. If the stack is empty (original list was empty), return None.
        4. Pop the first node from the stack, which becomes the new head.
        5. While the stack is not empty:
            a. Pop a node from the stack.
            b. Set the `next` pointer of the current node to the popped node.
            c. Move the `current` pointer to the popped node.
        6. Set the `next` pointer of the last node to None.
        7. Return the new head.
    """
    stack = []  # Initialize an empty stack
    current = head
    while current:
        stack.append(current)  # Push each node onto the stack
        current = current.next

    if not stack:  # Handle empty list case
        return None

    new_head = stack.pop()  # The first popped node is the new head
    current = new_head
    while stack:
        node = stack.pop()  # Pop a node from the stack
        current.next = node  # Connect the current node to the popped node
        current = node  # Move current to the popped node
    current.next = None  # Set the last node's next to None
    return new_head

# 4. In-Place Reversal using Three-Pointer Technique
# Time Complexity: O(n), Space Complexity: O(1)
def reverse_list_three_pointer(head):
    """
    Reverses a singly linked list in-place using three pointers.

    This function reverses the linked list by changing the direction of the
    pointers of each node, similar to the iterative approach, but with slightly
    different variable names for clarity.

    Args:
        head (ListNode): The head of the linked list to be reversed.

    Returns:
        ListNode: The new head of the reversed linked list.

    Algorithm:
        1. Initialize `prev` to None, `current` to head.
        2. Iterate through the list while `current` is not None:
            a. Store the next node in `next_node`.
            b. Change the `next` pointer of `current` to point to `prev`.
            c. Move `prev` to `current`.
            d. Move `current` to `next_node`.
        3. `prev` will be the new head of the reversed list.
    """
    prev, current = None, head  # Initialize prev and current pointers
    while current:
        next_node = current.next  # Store the next node
        current.next = prev  # Reverse the pointer
        prev = current  # Move prev forward
        current = next_node  # Move current forward
    return prev  # prev is the new head

# 5. Using Array Conversion
# Time Complexity: O(n), Space Complexity: O(n)
def reverse_list_array(head):
    """
    Reverses a singly linked list by converting it to an array.

    This function converts the linked list to an array, reverses the array, and
    then updates the values of the nodes in the linked list based on the
    reversed array.  This approach does not change the structure of the linked list,
    but it changes the values within the nodes.

    Args:
        head (ListNode): The head of the linked list to be reversed.

    Returns:
        ListNode: The head of the modified linked list (with reversed values).

    Algorithm:
        1. Create an empty array `values`.
        2. Iterate through the linked list and append the value of each node to `values`.
        3. Iterate through the linked list again, and for each node, set its value
           to the corresponding value from the reversed `values` array.
        4. Return the original head of the linked list (the values have been modified).
    """
    values = []  # Initialize an empty array to store node values
    current = head
    while current:
        values.append(current.val)  # Append each node's value to the array
        current = current.next

    current = head  # Reset current to the head
    for val in reversed(values):  # Iterate through the reversed array
        current.val = val  # Update the node's value
        current = current.next
    return head  # Return the head (the list structure is the same, but values are reversed)

# Helper function to print linked list
def print_list(head):
    """
    Prints the values of a linked list in sequential order.

    Args:
        head (ListNode): The head of the linked list to be printed.
    """
    current = head
    while current:
        print(current.val, end=" -> ")  # Print the value of the current node
        current = current.next  # Move to the next node
    print("None")  # Print "None" to indicate the end of the list

# Creating a sample linked list: 1 -> 2 -> 3 -> 4 -> 5
head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))

# Testing different approaches
print("Original Linked List:")
print_list(head)

print("\nReversed (Iterative):")
print_list(reverse_list_iterative(head))

# Recreating linked list for fresh testing
head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
print("\nReversed (Recursive):")
print_list(reverse_list_recursive(head))

head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
print("\nReversed (Stack):")
print_list(reverse_list_stack(head))

head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
print("\nReversed (Three-Pointer):")
print_list(reverse_list_three_pointer(head))

head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
print("\nReversed (Array Conversion):")
print_list(reverse_list_array(head))
