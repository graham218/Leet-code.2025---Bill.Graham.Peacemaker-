class ListNode:
    """
    Represents a node in a singly linked list.

    Attributes:
        val: The value stored in the node.
        next: A reference to the next node in the list.
    """
    def __init__(self, val=0):
        self.val = val
        self.next = None

def detect_cycle_floyd(head):
    """
    Detects if a linked list has a cycle using Floyd's cycle-finding algorithm (tortoise and hare).

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle is detected, False otherwise.

    Algorithm:
        - Uses two pointers, 'slow' and 'fast'.
        - 'slow' moves one step at a time, 'fast' moves two steps.
        - If there's a cycle, 'slow' and 'fast' will eventually meet.
    """
    slow, fast = head, head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            return True  # Cycle detected
    return False  # No cycle

def detect_cycle_set(head):
    """
    Detects if a linked list has a cycle using a set to store visited nodes.

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle is detected, False otherwise.

    Algorithm:
        - Iterates through the list, adding each node to a set.
        - If a node is encountered that's already in the set, a cycle exists.
    """
    visited = set()
    while head:
        if head in visited:
            return True  # Cycle detected
        visited.add(head)
        head = head.next
    return False  # No cycle

def detect_cycle_dict(head):
    """
    Detects if a linked list has a cycle using a dictionary to store visited nodes.
    This method uses the id of the node as the key.

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle is detected, False otherwise.

    Algorithm:
        - Iterates through the list, adding the id of each node to a dictionary.
        - If the id of a node is encountered that's already in the dictionary, a cycle exists.
    """
    visited = {}
    while head:
        if visited.get(id(head)):
            return True  # Cycle detected
        visited[id(head)] = True
        head = head.next
    return False  # No cycle

def detect_cycle_recursive(head, visited=None):
    """
    Detects if a linked list has a cycle using recursion and a set to store visited nodes.

    Args:
        head: The head node of the linked list.
        visited: A set to store visited nodes (used for recursion).

    Returns:
        True if a cycle is detected, False otherwise.

    Algorithm:
        - Uses recursion to traverse the list.
        - A set 'visited' keeps track of visited nodes.
        - If a node is encountered that's already in 'visited', a cycle exists.
    """
    if visited is None:
        visited = set()
    if head is None:
        return False  # End of list, no cycle
    if head in visited:
        return True  # Cycle detected
    visited.add(head)
    return detect_cycle_recursive(head.next, visited)

def detect_cycle_position_marker(head):
    """
    Detects if a linked list has a cycle by modifying the list itself.
    This method replaces each visited node's next pointer with a marker node.

    Args:
        head: The head node of the linked list.

    Returns:
        True if a cycle is detected, False otherwise.

    Algorithm:
        - Uses a marker node to track visited nodes.
        - For each node, if its next pointer points to the marker, a cycle exists.
        - Otherwise, the node's next pointer is set to the marker.
        -This approach modifies the original list.
    """
    marker = ListNode(-1)
    while head:
        if head.next == marker:
            return True  # Cycle detected
        next_node = head.next
        head.next = marker
        head = next_node
    return False  # No cycle

# Helper function to create a cycle for testing
def create_cycle(lst, pos):
    """
    Creates a linked list with a cycle for testing purposes.

    Args:
        lst: A list of values to create the linked list from.
        pos: The index of the node where the cycle starts (-1 for no cycle).

    Returns:
        The head node of the created linked list.
    """
    if not lst:
        return None
    head = ListNode(lst[0])
    nodes = [head]
    for val in lst[1:]:
        nodes.append(ListNode(val))
        nodes[-2].next = nodes[-1]
    if pos != -1:
        nodes[-1].next = nodes[pos]  # Create the cycle
    return head

# Test Cases
nodes = [3, 2, 0, -4]
head = create_cycle(nodes, 1)  # Create a cycle starting at the second node

print("Floyd’s Algorithm:", detect_cycle_floyd(head))
print("Set-based Approach:", detect_cycle_set(head))
print("Dictionary-based Approach:", detect_cycle_dict(head))
print("Recursive Approach:", detect_cycle_recursive(head))
print("Position Marker Approach:", detect_cycle_position_marker(head))