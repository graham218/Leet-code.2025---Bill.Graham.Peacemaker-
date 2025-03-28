class ListNode:
    def __init__(self, value=0, next=None):
        """
        Initializes a ListNode object.

        Args:
            value: The value to store in the node (default: 0).
            next:  A reference to the next node in the list (default: None).
                   If None, this is the last node.
        """
        self.value = value  # Store the data
        self.next = next    # Store the reference to the next node

# Floyd’s Cycle Detection Algorithm (Tortoise and Hare)
def detect_cycle_floyd(head):
    """
    Detects if a linked list has a cycle using Floyd's Tortoise and Hare algorithm.

    This algorithm uses two pointers, 'slow' and 'fast'.  The slow pointer moves one
    node at a time, while the fast pointer moves two nodes at a time.  If there's a
    cycle, the two pointers will eventually meet.

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle exists, False otherwise.
    """
    if not head:  # Empty list cannot have a cycle
        return False

    slow, fast = head, head  # Initialize both pointers to the head
    # Iterate until fast reaches the end of the list or a cycle is found
    while fast and fast.next:
        slow = slow.next       # Slow pointer moves one step
        fast = fast.next.next  # Fast pointer moves two steps
        if slow == fast:
            return True  # Cycle detected: slow and fast pointers meet
    return False  # No cycle: fast pointer reached the end of the list

# HashSet Approach
def detect_cycle_hashset(head):
    """
    Detects if a linked list has a cycle using a HashSet (set in Python).

    This approach keeps track of visited nodes in a set. If a node is visited again,
    it means there's a cycle.

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle exists, False otherwise.
    """
    visited = set()  # Create an empty set to store visited nodes
    current = head   # Start at the head of the list
    while current:
        if current in visited:
            return True  # Cycle detected: current node is already in the visited set
        visited.add(current)  # Add the current node to the visited set
        current = current.next  # Move to the next node
    return False  # No cycle: the loop finished without finding a duplicate node

# Modify Node Structure (Flagging Nodes)
def detect_cycle_flagging(head):
    """
    Detects if a linked list has a cycle by modifying the node structure.

    This method changes the 'next' pointer of each visited node to a special 'marker'
    node. If we encounter a node whose 'next' pointer is the marker, we've found a cycle.
    WARNING: This modifies the original linked list.

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle exists, False otherwise.
    """
    if not head:
        return False
    marker = ListNode("marker")  # Create a marker node
    current = head             # Start at the head
    while current:
        if current.next == marker:
            return True  # Cycle detected: next pointer points to the marker
        temp = current.next  # Store the next node
        current.next = marker  # Change next pointer to the marker
        current = temp         # Move to the next node (which is now stored in temp)
    return False  # No cycle: the loop finished without finding the marker

# Using Length of Loop (Mathematical Approach)
def detect_cycle_length(head):
    """
    Detects a cycle and returns the length of the cycle if found.

    This approach first uses the slow/fast pointer method to detect a cycle. If a cycle
    is found, it calculates the length of the cycle.

    Args:
        head: The head node of the linked list.

    Returns:
        The length of the cycle if found, 0 otherwise (if no cycle).
    """
    slow, fast = head, head  # Initialize slow and fast pointers
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            return cycle_length(slow)  # Call cycle_length to get the length
    return 0  # No cycle

def cycle_length(node):
    """
    Calculates the length of a cycle in a linked list, given a node within the cycle.

    Args:
        node: A node that is part of the cycle.

    Returns:
        The length of the cycle.
    """
    temp = node
    length = 1  # Initialize length to 1 (we've already seen one node)
    while temp.next != node:  # Iterate until we get back to the starting node
        temp = temp.next
        length += 1
    return length

# Using Two Pointers (Variation with Entry Detection)
def detect_cycle_entry(head):
    """
    Detects a cycle and finds the entry point of the cycle.

    This method uses the slow/fast pointer approach.  If a cycle is detected, it finds
    the node where the cycle begins.

    Args:
        head: The head node of the linked list.

    Returns:
        The entry node of the cycle if found, None otherwise.
    """
    if not head:
        return None
    slow, fast = head, head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            break # Exit the loop when slow and fast meet
    else:
        return None  # No cycle: fast reached the end without meeting slow

    slow = head       # Reset slow to the head
    while slow != fast: # Move both pointers one step at a time until they meet
        slow = slow.next
        fast = fast.next
    return slow  # The meeting point is the entry point of the cycle

# Recursive Approach (Less Common)
def detect_cycle_recursive(node, visited=set()):
    """
    Detects a cycle in a linked list using recursion.

    This approach recursively traverses the list, keeping track of visited nodes in a set.
    If a node is visited again, it indicates a cycle.

    Args:
        node:    The current node being visited.
        visited: A set of already visited nodes (default: an empty set).

    Returns:
        True if a cycle exists, False otherwise.
    """
    if node is None:
        return False  # Base case: end of the list, no cycle
    if node in visited:
        return True  # Cycle detected: current node was already visited
    visited.add(node)  # Add the current node to the visited set
    return detect_cycle_recursive(node.next, visited)  # Recursive call for the next node

# Helper function to create a linked list with a cycle for testing
def create_cycle_list(values, cycle_pos):
    """
    Creates a linked list, optionally with a cycle, for testing purposes.

    Args:
        values:     A list of values to create the linked list nodes with.
        cycle_pos:  The position (0-based index) in the list where the cycle should start.
                    If -1, no cycle is created.

    Returns:
        The head node of the created linked list.
    """
    if not values:
        return None  # Empty list
    head = ListNode(values[0])  # Create the head node
    current = head
    nodes = [head]  # Store all created nodes in a list
    for val in values[1:]:
        new_node = ListNode(val)
        nodes.append(new_node)
        current.next = new_node
        current = new_node

    if cycle_pos != -1:
        current.next = nodes[cycle_pos]  # Create the cycle
    return head

# Test Cases
values = [1, 2, 3, 4, 5]
cycle_head = create_cycle_list(values, 2)  # Create a list with a cycle starting at node with value 3
non_cycle_head = create_cycle_list(values, -1) # Create a list without a cycle

print("Floyd’s Cycle Detection:", detect_cycle_floyd(cycle_head))
print("HashSet Approach:", detect_cycle_hashset(cycle_head))
print("Flagging Approach:", detect_cycle_flagging(cycle_head))
print("Cycle Length:", detect_cycle_length(cycle_head))
entry_node = detect_cycle_entry(cycle_head)
print("Cycle Entry Node:", entry_node.value if entry_node else None)
print("Recursive Detection:", detect_cycle_recursive(cycle_head))
