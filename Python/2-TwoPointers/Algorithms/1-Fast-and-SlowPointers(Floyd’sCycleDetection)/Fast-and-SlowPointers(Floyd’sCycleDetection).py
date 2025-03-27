class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val  # Store the value of the node
        self.next = next # Store the reference to the next node in the list

# Approach 1: Floyd’s Cycle Detection Algorithm (Tortoise and Hare)
def hasCycle_floyd(head):
    """
    Detects if a linked list has a cycle using Floyd's Tortoise and Hare algorithm.

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle is detected, False otherwise.
    """
    slow, fast = head, head # Initialize two pointers, slow and fast, to the head
    while fast and fast.next: # Iterate as long as fast and fast.next are not None
        slow = slow.next # Move slow one step
        fast = fast.next.next # Move fast two steps
        if slow == fast: # If slow and fast meet, a cycle exists
            return True  # Cycle detected
    return False  # No cycle

# Approach 2: Hash Set Method
def hasCycle_hashset(head):
    """
    Detects if a linked list has a cycle using a hash set.

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle is detected, False otherwise.
    """
    seen_nodes = set() # Initialize a set to store visited nodes
    while head: # Iterate through the linked list
        if head in seen_nodes: # If the current node is already in the set, a cycle exists
            return True  # Cycle detected
        seen_nodes.add(head) # Add the current node to the set
        head = head.next # Move to the next node
    return False  # No cycle

# Approach 3: Modifying Node Values (Not Recommended)
def hasCycle_modify_value(head):
    """
    Detects if a linked list has a cycle by modifying node values.
    This approach is generally not recommended as it modifies the original list.

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle is detected, False otherwise.
    """
    marker = object()  # Unique marker object to identify visited nodes
    while head: # Iterate through the linked list
        if head.val == marker: # If the current node's value is the marker, a cycle exists
            return True  # Cycle detected
        head.val = marker # Mark the current node by changing its value
        head = head.next # Move to the next node
    return False  # No cycle

# Approach 4: Using Two Pointers with Different Speeds
def hasCycle_different_speeds(head):
    """
    Detects if a linked list has a cycle using two pointers with different speeds.
    This variation moves the fast pointer slightly differently than Floyd's.

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle is detected, False otherwise.
    """
    slow, fast = head, head # Initialize two pointers, slow and fast, to the head
    while fast and fast.next: # Iterate as long as fast and fast.next are not None
        slow = slow.next # Move slow one step
        fast = fast.next.next # Move fast two steps
        if fast and fast.next: # move fast one more time if possible
            fast = fast.next
        if slow == fast: # If slow and fast meet, a cycle exists
            return True  # Cycle detected
    return False  # No cycle

# Approach 5: Counting Nodes in Cycle (After Detection)
def countCycleNodes(head):
    """
    Counts the number of nodes in a cycle, if one exists.

    Args:
        head: The head node of the linked list.

    Returns:
        The number of nodes in the cycle, or 0 if no cycle exists.
    """
    slow, fast = head, head # Initialize two pointers, slow and fast, to the head
    while fast and fast.next: # Iterate as long as fast and fast.next are not None
        slow = slow.next # Move slow one step
        fast = fast.next.next # Move fast two steps
        if slow == fast: # If slow and fast meet, a cycle exists
            # Cycle detected, count nodes
            count = 1 # Initialize the count to 1 (for the meeting point)
            current = slow.next # Start from the next node of the meeting point
            while current != slow: # Iterate until we reach the meeting point again
                count += 1 # Increment the count
                current = current.next # Move to the next node
            return count  # Return the cycle length
    return 0  # No cycle detected

# Test cases
def createLinkedListWithCycle():
    """Creates a linked list with a cycle for testing."""
    head = ListNode(1)
    second = ListNode(2)
    third = ListNode(3)
    fourth = ListNode(4)
    head.next = second
    second.next = third
    third.next = fourth
    fourth.next = second  # Creates a cycle
    return head

def createLinkedListWithoutCycle():
    """Creates a linked list without a cycle for testing."""
    head = ListNode(1)
    second = ListNode(2)
    third = ListNode(3)
    fourth = ListNode(4)
    head.next = second
    second.next = third
    third.next = fourth
    return head

# Run tests
cycle_list = createLinkedListWithCycle()
no_cycle_list = createLinkedListWithoutCycle()

print("Floyd’s Algorithm (With Cycle):", hasCycle_floyd(cycle_list))  # True
print("Floyd’s Algorithm (Without Cycle):", hasCycle_floyd(no_cycle_list))  # False

print("Hash Set Method (With Cycle):", hasCycle_hashset(cycle_list))  # True
print("Hash Set Method (Without Cycle):", hasCycle_hashset(no_cycle_list))  # False

print("Modify Node Values (With Cycle):", hasCycle_modify_value(cycle_list))  # True
print("Modify Node Values (Without Cycle):", hasCycle_modify_value(no_cycle_list))  # False

print("Two Pointers Different Speeds (With Cycle):", hasCycle_different_speeds(cycle_list))  # True
print("Two Pointers Different Speeds (Without Cycle):", hasCycle_different_speeds(no_cycle_list))  # False

print("Cycle Length (If Cycle Exists):", countCycleNodes(cycle_list))  # Expected: Cycle length
print("Cycle Length (No Cycle):", countCycleNodes(no_cycle_list))  # Expected: 0