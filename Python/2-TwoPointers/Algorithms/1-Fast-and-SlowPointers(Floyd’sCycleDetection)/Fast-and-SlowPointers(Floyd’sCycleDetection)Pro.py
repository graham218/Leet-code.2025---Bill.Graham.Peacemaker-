class ListNode:
    """
    Represents a node in a singly linked list.  A singly linked list is a data structure
    where each node points to the next node in the sequence.  The last node points to None.

    Attributes:
        val: The data value stored in this node.  This can be any data type (integer, string, object, etc.).
        next: A reference (pointer) to the next ListNode in the list.  If this is the last node, next is None.
    """
    def __init__(self, val=0, next=None):
        """
        Initializes a new ListNode object.  This constructor is called when you create a new node.

        Args:
            val: The value to be stored in this node.  Defaults to 0 if no value is provided.
            next: A reference to the next node in the list.  Defaults to None.
        """
        self.val = val  # Store the given value in the node's val attribute
        self.next = next # Store the reference to the next node in the node's next attribute.
        # If this is the last node, next will be None.

# Approach 1: Floyd’s Cycle Detection Algorithm (Tortoise and Hare)
def hasCycle_floyd(head):
    """
    Detects if a linked list contains a cycle using Floyd's "Tortoise and Hare" algorithm.
    This is an efficient algorithm that uses two pointers to traverse the list.

    A cycle exists if, starting from the head of the list, you can reach the same node again
    by following the 'next' pointers.

    Args:
        head: The head (starting) node of the linked list.

    Returns:
        True if the linked list contains a cycle, False otherwise.

    Algorithm:
        1. Initialize two pointers, 'slow' and 'fast', both starting at the head of the list.
        2. The 'slow' pointer moves one node at a time.
        3. The 'fast' pointer moves two nodes at a time.
        4. If there is a cycle, the 'fast' pointer will eventually catch up to the 'slow' pointer.
        5. If there is no cycle, the 'fast' pointer will reach the end of the list (None).
    """
    slow, fast = head, head  # Initialize both pointers to the head of the list.  If the list is empty (head is None),
    # this will be handled correctly by the while loop condition.
    while fast and fast.next:  # Continue the loop as long as 'fast' and 'fast.next' are not None.
        # This checks two things:
        #   - fast is not None:  Ensures we haven't reached the end of the list.
        #   - fast.next is not None: Ensures there's a node after 'fast' so we can move 'fast' by two.
        slow = slow.next      # Move the 'slow' pointer one step forward.
        fast = fast.next.next # Move the 'fast' pointer two steps forward.
        if slow == fast:      # If the 'slow' and 'fast' pointers meet at the same node,
            return True       # then there is a cycle in the linked list.
    return False            # If the loop finishes without the pointers meeting, there is no cycle.

# Approach 2: Hash Table Method
def hasCycle_hash_table(head):
    """
    Detects if a linked list contains a cycle using a hash table (set) to keep track of visited nodes.

    Args:
        head: The head (starting) node of the linked list.

    Returns:
        True if the linked list contains a cycle, False otherwise.

    Algorithm:
        1. Create an empty set (hash table) called 'seen_nodes' to store visited nodes.
        2. Iterate through the linked list, starting from the head.
        3. For each node:
            a. Check if the node is already in the 'seen_nodes' set.
            b. If the node is in the set, it means we have visited this node before, so there is a cycle.
            c. If the node is not in the set, add it to the set.
        4. If we reach the end of the list without finding a cycle, return False.
    """
    seen_nodes = set()  # Initialize an empty set to store references to visited nodes.  A set is used
    # because it provides fast membership checking (checking if an element is in the set).
    while head:         # Iterate through the linked list, starting from the head.  The loop continues as long as
        # 'head' is not None (i.e., we haven't reached the end of the list).
        if head in seen_nodes: # Check if the current node ('head') is already in the 'seen_nodes' set.
            return True       # If it is, we've encountered this node before, which means there's a cycle.
        seen_nodes.add(head) # If the node is not in 'seen_nodes', add it to the set so we can detect it
        # if we encounter it again later.
        head = head.next    # Move to the next node in the linked list.
    return False            # If the loop completes without finding a duplicate node, there is no cycle.

# Approach 3: Timestamp Method
def hasCycle_timestamp(head):
    """
    Detects if a linked list contains a cycle by adding a 'timestamp' attribute to each node as we visit it.
    This method modifies the original linked list by adding an attribute to the nodes.

    Args:
        head: The head (starting) node of the linked list.

    Returns:
        True if the linked list contains a cycle, False otherwise.

    Algorithm:
        1. Initialize a 'timestamp' counter to 1.
        2. Iterate through the linked list, starting from the head.
        3. For each node:
            a. Check if the node already has a 'timestamp' attribute.
            b. If it does, it means we have visited this node before, so there is a cycle.
            c. If it doesn't, add a 'timestamp' attribute to the node with the current 'timestamp' value.
            d. Increment the 'timestamp' counter.
        4. If we reach the end of the list without finding a node with a timestamp, return False.

    Note: This method modifies the original linked list by adding an attribute to each node.
          This might not be desirable in all situations.  It's generally better to avoid modifying
          the input data structure unless you are sure it's safe and intended.
    """
    timestamp = 1  # Initialize the timestamp counter.  We start at 1, but any starting value would work.
    while head:     # Iterate through the linked list.  The loop continues as long as 'head' is not None.
        if hasattr(head, 'timestamp'): # Check if the current node ('head') already has a 'timestamp' attribute.
            return True             # If it does, it means we've visited this node before, so there's a cycle.
        head.timestamp = timestamp # If the node doesn't have a timestamp, add the 'timestamp' attribute to the node
        # and assign it the current timestamp value.
        timestamp += 1             # Increment the timestamp counter so the next node gets a different timestamp.
        head = head.next            # Move to the next node in the linked list.
    return False                    # If the loop finishes without finding a previously timestamped node, there is no cycle.

# Approach 4: Cycle Start Detection
def detectCycleStart(head):
    """
    Finds the starting node of a cycle in a linked list, if a cycle exists.  It uses Floyd's algorithm.

    Args:
        head: The head (starting) node of the linked list.

    Returns:
        The starting node of the cycle if a cycle exists, None otherwise.

    Algorithm:
        1. Use Floyd's cycle detection algorithm (slow and fast pointers) to find the meeting point of the two pointers.
        2. If there is no cycle (the fast pointer reaches the end of the list), return None.
        3. If there is a cycle, reset the 'slow' pointer to the head of the list.
        4. Move both the 'slow' and 'fast' pointers one step at a time.
        5. The point where they meet again is the start of the cycle.

    Explanation:
    Let:
        - X be the distance from the head of the list to the start of the cycle.
        - Y be the distance from the start of the cycle to the meeting point of the slow and fast pointers.
        - Z be the distance from the meeting point back to the start of the cycle.

    When the slow and fast pointers meet:
        - The slow pointer has traveled X + Y.
        - The fast pointer has traveled X + Y + n(Y + Z), where n is the number of times the fast pointer has gone
          around the cycle.

    Since the fast pointer travels twice as fast as the slow pointer:
        2(X + Y) = X + Y + n(Y + Z)
        X + Y = n(Y + Z)
        X = n(Y + Z) - Y
        X = (n - 1)(Y + Z) + Z

    This means that the distance from the head to the start of the cycle (X) is equal to the distance from the
    meeting point to the start of the cycle (Z), plus some multiple of the cycle length (Y + Z).
    Therefore, if we reset the slow pointer to the head and move both pointers one step at a time, they will meet
    at the start of the cycle.
    """
    slow, fast = head, head  # Initialize slow and fast pointers to the head.
    while fast and fast.next: # Use Floyd's algorithm to find the meeting point.
        slow = slow.next
        fast = fast.next.next
        if slow == fast:      # If they meet, we've found a cycle.
            break
    else:                   # This 'else' block is executed if the 'while' loop finishes without the 'if' condition
        # ever being true.  In this case, it means the fast pointer reached the end of the list
        # (no cycle), so we return None.
        return None         # No cycle found.

    slow = head             # Reset the slow pointer to the head of the list.
    while slow != fast:     # Move both pointers one step at a time until they meet.
        slow = slow.next
        fast = fast.next
    return slow             # The meeting point is the start of the cycle.

# Approach 5: Reference Count Method
def hasCycle_reference_count(head):
    """
    Detects if a linked list contains a cycle by checking the reference count of each node using sys.getrefcount().
    This method is generally NOT recommended because Python's garbage collection can affect the reference counts,
    making this method unreliable in many cases.

    Args:
        head: The head (starting) node of the linked list.

    Returns:
        True if the linked list contains a cycle, False otherwise.

    Algorithm:
        1. Iterate through the linked list.
        2. For each node, get its reference count using sys.getrefcount().
        3. If the reference count is greater than 2, it suggests a cycle.  (A node in a cycle will be referenced
           by at least two other nodes, and potentially by a variable in the current scope).
        4. If we reach the end of the list without finding a node with a reference count greater than 2, return False.

    Warning: This method is unreliable due to Python's garbage collection.  Garbage collection can change
             reference counts, leading to false positives or negatives.  Use Floyd's algorithm or the hash table
             method instead.
    """
    import sys  # Import the 'sys' module to use sys.getrefcount().
    while head:
        if sys.getrefcount(head) > 2: # Check if the reference count of the current node is greater than 2.
            return True             # If it is, we assume there's a cycle.
        head = head.next            # Move to the next node.
    return False                    # If the loop finishes without finding a node with a high reference count,
    # we assume there is no cycle.

# Approach 6: Length of Cycle Detection
def countCycleNodes(head):
    """
    Counts the number of nodes in a cycle in a linked list, if a cycle exists.  It uses Floyd's algorithm
    to find the meeting point, and then traverses the cycle to count the nodes.

    Args:
        head: The head (starting) node of the linked list.

    Returns:
        The number of nodes in the cycle if a cycle exists, 0 otherwise.
    """
    slow, fast = head, head # Initialize slow and fast pointers for Floyd's algorithm.
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:  # If they meet, we've found a cycle.
            count = 1     # Initialize the cycle length to 1 (we've found one node in the cycle).
            current = slow.next # Start counting from the node *after* the meeting point.
            while current != slow: # Continue counting until we get back to the meeting point.
                count += 1
                current = current.next
            return count  # Return the total count of nodes in the cycle.
    return 0                # If the loop finishes without finding a meeting point, there is no cycle, so return 0.

# Test Cases
def createLinkedListWithCycle():
    """
    Creates a linked list with a cycle for testing purposes.  The cycle is created by making the
    'next' pointer of the fourth node point back to the second node.

    The created linked list looks like this:
    1 -> 2 -> 3 -> 4
         ^         |
         |_________|
    """
    head = ListNode(1)
    second = ListNode(2)
    third = ListNode(3)
    fourth = ListNode(4)
    head.next = second
    second.next = third
    third.next = fourth
    fourth.next = second  # Creates a cycle: 4 points back to 2.
    return head

def createLinkedListWithoutCycle():
    """
    Creates a linked list without a cycle for testing purposes.  This is a simple linear linked list.

    The created linked list looks like this:
    1 -> 2 -> 3 -> 4 -> None
    """
    head = ListNode(1)
    second = ListNode(2)
    third = ListNode(3)
    fourth = ListNode(4)
    head.next = second
    second.next = third
    third.next = fourth
    return head

# Running Tests
cycle_list = createLinkedListWithCycle()      # Create a linked list *with* a cycle.
no_cycle_list = createLinkedListWithoutCycle()  # Create a linked list *without* a cycle.

print("Floyd’s Algorithm (With Cycle):", hasCycle_floyd(cycle_list))
print("Floyd’s Algorithm (Without Cycle):", hasCycle_floyd(no_cycle_list))

print("Hash Table Method (With Cycle):", hasCycle_hash_table(cycle_list))
print("Hash Table Method (Without Cycle):", hasCycle_hash_table(no_cycle_list))

print("Timestamp Method (With Cycle):", hasCycle_timestamp(cycle_list))
print("Timestamp Method (Without Cycle):", hasCycle_timestamp(no_cycle_list))

cycle_start = detectCycleStart(cycle_list)
print("Cycle Start Node (If Exists):", cycle_start.val if cycle_start else "No Cycle") # Print the value of the
# starting node, or "No Cycle"

print("Reference Count Method (With Cycle):", hasCycle_reference_count(cycle_list))
print("Reference Count Method (Without Cycle):", hasCycle_reference_count(no_cycle_list))

print("Cycle Length (If Exists):", countCycleNodes(cycle_list))
print("Cycle Length (No Cycle):", countCycleNodes(no_cycle_list))
