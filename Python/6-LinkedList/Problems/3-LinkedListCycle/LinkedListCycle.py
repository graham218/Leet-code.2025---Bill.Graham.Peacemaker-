class ListNode:
    def __init__(self, x):
        """
        Represents a node in a singly linked list.
        :param x: The value stored in the node.
        """
        self.val = x
        self.next = None

def create_linked_list(nodes):
    """
    Creates a linked list from a list of values.

    Args:
        nodes (list): A list of values for the nodes.

    Returns:
        ListNode: The head of the linked list.
    """
    if not nodes:
        return None
    head = ListNode(nodes[0])
    current = head
    for i in range(1, len(nodes)):
        current.next = ListNode(nodes[i])
        current = current.next
    return head

def create_cyclic_linked_list(nodes, pos):
    """
    Creates a linked list with a cycle.

    Args:
        nodes (list): A list of values for the nodes.
        pos (int): The index of the node where the cycle starts (0-indexed).

    Returns:
        ListNode: The head of the linked list with a cycle.  Returns None if pos is invalid.
    """
    if not nodes:
        return None
    head = ListNode(nodes[0])
    current = head
    cycle_start = None
    for i in range(1, len(nodes)):
        current.next = ListNode(nodes[i])
        current = current.next
        if i == pos:
            cycle_start = current
    if pos != -1 and cycle_start is not None:
        current.next = cycle_start  # Create the cycle
    return head

def display_linked_list(head, max_nodes=20):
    """
    Displays the values of a linked list, stopping at a maximum number of nodes to avoid infinite loops.

    Args:
        head (ListNode): The head of the linked list.
        max_nodes (int, optional): The maximum number of nodes to display. Defaults to 20.
    """
    current = head
    count = 0
    nodes = []
    while current and count < max_nodes:
        nodes.append(str(current.val))
        current = current.next
        count += 1
        if current == head:  # Detect a full cycle back to the head
            nodes.append("...")
            break
    if current and count >= max_nodes:
        nodes.append("...")  # Indicate list was truncated
    print(" -> ".join(nodes))

def has_cycle_approach1(head):
    """
    Approach 1: Using a set to store visited nodes.

    Time Complexity: O(n), where n is the number of nodes in the linked list.
    Space Complexity: O(n), for the set.
    """
    if not head:
        return False
    visited = set()
    current = head
    while current:
        if current in visited:
            return True
        visited.add(current)
        current = current.next
    return False

def has_cycle_approach2(head):
    """
    Approach 2: Floyd's Cycle Detection Algorithm (Tortoise and Hare).
    This is the most efficient and commonly used approach.

    Time Complexity: O(n), where n is the number of nodes in the linked list.
    Space Complexity: O(1), constant space.
    """
    if not head or not head.next:
        return False
    slow = head
    fast = head.next
    while fast and fast.next:
        if slow == fast:
            return True
        slow = slow.next
        fast = fast.next.next
    return False

def has_cycle_approach3(head):
    """
    Approach 3: Modifying the linked list (adding a visited flag).
    This approach modifies the original linked list, which might not be desirable.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not head:
        return False

    current = head
    while current:
        if hasattr(current, 'visited'):
            return True
        else:
            current.visited = True #Add an attribute
            current = current.next
    return False

def has_cycle_approach4(head):
    """
     Approach 4: Using a dictionary to store node pointers and their counts.
     Detects a cycle if any node is visited more than once.

     Time Complexity: O(n)
     Space Complexity: O(n)
    """
    if not head:
        return False

    node_dict = {}
    current = head
    while current:
        if current in node_dict:
            node_dict[current] += 1
            if node_dict[current] > 1:
                return True
        else:
            node_dict[current] = 1
        current = current.next
    return False

def has_cycle_approach5(head):
    """
    Approach 5: Using a long and short pointer with a counter.  This approach is similar to Approach 2,
    but adds a counter to limit the number of steps, preventing an infinite loop in some cases
    if the cycle is incorrectly formed.

    Time Complexity: O(n) in a correct linked list.  Could be higher if the cycle is broken.
    Space Complexity: O(1)
    """
    if not head or not head.next:
        return False

    short_ptr = head
    long_ptr = head.next
    counter = 0
    max_count = 10000 # Set a maximum limit
    while long_ptr and long_ptr.next and counter < max_count:
        if short_ptr == long_ptr:
            return True
        short_ptr = short_ptr.next
        long_ptr = long_ptr.next.next
        counter += 1
    return False

if __name__ == "__main__":
    # Test cases
    test_cases = [
        ([], -1),
        ([1], -1),
        ([1, 2, 3, 4, 5], -1),
        ([1, 2, 3, 4, 5], 2),
        ([1, 2], 0),
        ([1, 2], 1),
        ([1,2,3,4,5,6,7,8,9,10], 5), # Longer list
    ]

    for nodes, cycle_pos in test_cases:
        print(f"\nTest Case: List = {nodes}, Cycle Start Position = {cycle_pos}")
        head = create_cyclic_linked_list(nodes, cycle_pos)
        display_linked_list(head)

        if cycle_pos == -1:
            print("  List has no cycle.")
        else:
            print("  List has a cycle.")

        # Test each approach
        print(f"  Approach 1 (Set):             {'Cycle' if has_cycle_approach1(head) else 'No Cycle'}")
        print(f"  Approach 2 (Floyd's):         {'Cycle' if has_cycle_approach2(head) else 'No Cycle'}")
        print(f"  Approach 3 (Modify List):     {'Cycle' if has_cycle_approach3(head) else 'No Cycle'}")
        print(f"  Approach 4 (Dictionary):      {'Cycle' if has_cycle_approach4(head) else 'No Cycle'}")
        print(f"  Approach 5 (Counter):         {'Cycle' if has_cycle_approach5(head) else 'No Cycle'}")

        # Display the list again, in case an approach modified it.
        head = create_cyclic_linked_list(nodes, cycle_pos) #Recreate
        display_linked_list(head)
