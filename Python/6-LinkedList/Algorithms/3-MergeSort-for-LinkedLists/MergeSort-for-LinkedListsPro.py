class ListNode:
    def __init__(self, val=0, next=None):
        """
        Initializes a ListNode object.

        Args:
            val (int, optional): The value of the node. Defaults to 0.
            next (ListNode, optional): The next node in the linked list. Defaults to None.
        """
        self.val = val  # Store the value of the node
        self.next = next # Store the reference to the next node

# Approach 1: Merge Sort with Tail Recursion Optimization
def merge_sort_tail_recursion(head):
    """
    Sorts a linked list using the merge sort algorithm with tail recursion optimization.

    Tail recursion optimization can improve performance in some environments by
    reducing stack usage, but Python does not perform tail call optimization.
    The algorithm divides the list into smaller sublists, recursively sorts them,
    and then merges the sorted sublists.

    Args:
        head (ListNode): The head of the linked list to be sorted.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    def sort_list(node):
        """
        Recursively sorts the linked list using merge sort.

        Args:
            node (ListNode): The current node being processed.

        Returns:
            ListNode: The head of the sorted sublist.
        """
        if not node or not node.next:
            return node # Base case: If the list is empty or has one element, it's already sorted
        mid = get_middle(node) # Find the middle node of the list
        right = mid.next     # Split the list into two halves: left (node to mid) and right (mid.next to end)
        mid.next = None      # Disconnect the left half from the right half
        return merge(sort_list(node), sort_list(right)) # Recursively sort the two halves and merge them

    return sort_list(head) # Start the sorting process from the head of the list

# Approach 2: Bottom-Up Merge Sort with Space Optimization
def merge_sort_bottom_up(head):
    """
    Sorts a linked list using the bottom-up merge sort algorithm.

    This approach iteratively merges sublists of increasing size until the entire list is sorted.
    It's generally more space-efficient than the top-down merge sort (recursive) approach
    because it avoids the overhead of recursive function calls.

    Args:
        head (ListNode): The head of the linked list to be sorted.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    if not head or not head.next:
        return head # Base case: If the list is empty or has one element, it's already sorted

    dummy = ListNode(0) # Create a dummy node to simplify merging
    dummy.next = head  # Point the dummy node to the head of the list
    size = get_size(head) # Get the size of the linked list
    step = 1           # Initialize the step size to 1 (start with merging pairs of nodes)

    while step < size: # Iterate until the step size is greater than or equal to the size of the list
        prev, curr = dummy, dummy.next # Initialize pointers: prev to the dummy node, curr to the head
        while curr:
            left = curr       # 'left' points to the start of the first sublist
            right = split(left, step) # Split the list into two sublists of size 'step'
            curr = split(right, step)  # 'curr' points to the start of the next pair of sublists
            prev.next = merge(left, right) # Merge the two sublists and update the 'next' pointer of the previous node
            while prev.next:
                prev = prev.next # Move 'prev' to the end of the merged sublist
        step *= 2 # Double the step size for the next iteration (merge larger sublists)

    return dummy.next # Return the head of the sorted list (which is dummy.next)

# Approach 3: Merge Sort with Three-Way Partitioning
def merge_sort_three_way(head):
    """
    Sorts a linked list using merge sort with three-way partitioning.

    This approach divides the list into three parts, recursively sorts each part,
    and then merges the three sorted parts.  This can offer performance
    advantages in some cases, especially if the input data has many duplicate keys.

    Args:
        head (ListNode): The head of the linked list to be sorted.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    if not head or not head.next:
        return head # Base case: If the list is empty or has one element, it's already sorted

    part1, part2, part3 = split_three_way(head) # Split the list into three parts
    # Recursively sort the three parts and merge them
    return merge(merge(merge_sort_three_way(part1), merge_sort_three_way(part2)), merge_sort_three_way(part3))

# Approach 4: Merge Sort using Dummy Nodes for Efficient Merging
def merge_sort_dummy_nodes(head):
    """
    Sorts a linked list using merge sort with dummy nodes for merging.

    This approach uses a dummy node in the merge function, which can simplify
    the logic and potentially improve performance slightly by avoiding special
    case handling for the head of the merged list.

    Args:
        head (ListNode): The head of the linked list to be sorted.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    if not head or not head.next:
        return head # Base case: If the list is empty or has one element, it's already sorted

    mid = get_middle(head) # Find the middle of the list
    right = mid.next     # Split the list
    mid.next = None

    left_sorted = merge_sort_dummy_nodes(head) # Recursively sort the left half
    right_sorted = merge_sort_dummy_nodes(right) # Recursively sort the right half

    return merge_using_dummy_nodes(left_sorted, right_sorted) # Merge the sorted halves using a dummy node

# Approach 5: Merge Sort using Slow and Fast Pointer Adjustments
def merge_sort_slow_fast_pointer(head):
    """
    Sorts a linked list using merge sort and slow/fast pointers for finding the middle.

    This approach explicitly uses slow and fast pointers to find the middle node
    of the list.  This is a common technique for linked list problems.

    Args:
        head (ListNode): The head of the linked list to be sorted.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    if not head or not head.next:
        return head # Base case

    slow, fast = head, head.next # Initialize slow and fast pointers
    while fast and fast.next:    # Fast pointer moves twice as fast as slow pointer
        slow = slow.next
        fast = fast.next.next  # Corrected to fast.next.next

    right = slow.next # 'right' is the head of the second half
    slow.next = None  # Split the list into two halves

    return merge(merge_sort_slow_fast_pointer(head), merge_sort_slow_fast_pointer(right)) # Recursive sort and merge

# Approach 6: Merge Sort with Direct In-Place Rewiring
def merge_sort_in_place(head):
    """
    Sorts a linked list using a merge sort algorithm that attempts to minimize
    extra space by performing the merge operation "in-place" (i.e., by rewiring
    the existing nodes without creating new nodes).  This approach modifies the
    original linked list.

    Note: While the merge operation attempts to be in-place, the recursive calls
    themselves still use stack space.  True in-place merge sort for a linked list
    is quite complex.

    Args:
        head (ListNode): The head of the linked list to be sorted.

    Returns:
        ListNode: The head of the sorted linked list.
    """
    if not head or not head.next:
        return head # Base case

    mid = get_middle(head) # Find the middle
    right = mid.next     # Split the list
    mid.next = None

    left_sorted = merge_sort_in_place(head)  # Recursive sort
    right_sorted = merge_sort_in_place(right) # Recursive sort

    return merge_in_place(left_sorted, right_sorted) # Merge the sorted lists in-place

# Helper Functions

def get_middle(head):
    """
    Finds the middle node of a linked list using the slow and fast pointer technique.

    Args:
        head (ListNode): The head of the linked list.

    Returns:
        ListNode: The middle node of the linked list.
    """
    slow, fast = head, head # Initialize slow and fast pointers to the head
    while fast.next and fast.next.next: # Fast pointer moves twice as fast as slow pointer
        slow = slow.next
        fast = fast.next.next
    return slow # When fast reaches the end, slow is at the middle

def merge(left, right):
    """
    Merges two sorted linked lists into a single sorted linked list.

    Args:
        left (ListNode): The head of the first sorted linked list.
        right (ListNode): The head of the second sorted linked list.

    Returns:
        ListNode: The head of the merged sorted linked list.
    """
    dummy = ListNode() # Create a dummy node to simplify the merging process
    tail = dummy       # 'tail' points to the last node of the merged list so far
    while left and right: # Iterate while both lists have elements
        if left.val < right.val:
            tail.next, left = left, left.next # If the current node in 'left' is smaller, append it to the merged list
        else:
            tail.next, right = right, right.next # Otherwise, append the current node in 'right'
        tail = tail.next # Move 'tail' to the newly added node
    tail.next = left or right # Append the remaining nodes from either list (if any)
    return dummy.next     # Return the head of the merged list (excluding the dummy node)

def split(head, step):
    """
    Splits a linked list into two parts.  The first part contains 'step' nodes,
    and the second part contains the remaining nodes.

    Args:
        head (ListNode): The head of the linked list to be split.
        step (int): The number of nodes in the first part.

    Returns:
        ListNode: The head of the second part of the linked list.
    """
    if not head:
        return None # If the list is empty, return None
    for _ in range(step - 1): # Iterate 'step - 1' times
        if not head.next: # If we reach the end of the list before completing 'step' iterations
            break       # Exit the loop
        head = head.next # Move to the next node
    next_head = head.next # 'next_head' is the start of the second part
    head.next = None      # Terminate the first part
    return next_head     # Return the head of the second part

def split_three_way(head):
    """
    Splits a linked list into three parts.

    The list is divided into three parts based on the slow and fast pointer technique.
    It's designed to partition the list into roughly three equal parts.

    Args:
        head (ListNode): The head of the linked list.

    Returns:
        tuple: A tuple containing the heads of the three parts (part1, part2, part3).
               If the list has fewer than two nodes, it returns (head, None, None).
    """
    if not head or not head.next:
        return head, None, None # Base case: handle empty or single-node lists

    slow1, slow2, fast = head, head, head # Initialize three pointers
    while fast and fast.next:            # Fast pointer moves twice as fast
        slow2 = slow1
        slow1 = slow1.next
        fast = fast.next.next
    mid = slow1.next      # 'mid' is the start of the third part
    slow1.next = None     # Terminate the second part
    slow2.next = None     # Terminate the first part
    return head, slow1, mid # Return the heads of the three parts

def merge_using_dummy_nodes(left, right):
    """
    Merges two sorted linked lists using a dummy node.

    This function is similar to the 'merge' function, but it uses a dummy node
    to simplify the logic.

    Args:
        left (ListNode): The head of the first sorted linked list.
        right (ListNode): The head of the second sorted linked list.

    Returns:
        ListNode: The head of the merged sorted linked list.
    """
    dummy = ListNode() # Create a dummy node
    tail = dummy       # 'tail' pointer
    while left and right:
        tail.next, left = (left, left.next) if left.val < right.val else (right, right.next) # concise if else
        tail = tail.next
    tail.next = left or right
    return dummy.next

def merge_in_place(left, right):
    """
    Merges two sorted linked lists in-place (i.e., without creating new nodes).

    This function modifies the 'next' pointers of the existing nodes to merge
    the two lists. It assumes that both input lists are already sorted.

    Args:
        left (ListNode): The head of the first sorted linked list.
        right (ListNode): The head of the second sorted linked list.

    Returns:
        ListNode: The head of the merged sorted linked list.
    """
    if not left:
        return right # If the left list is empty, return the right list
    if not right:
        return left # If the right list is empty, return the left list

    if left.val > right.val: # Ensure 'left' starts with the smaller value
        left, right = right, left

    head = left # 'head' will be the head of the merged list
    while left.next and right:
        if left.next.val > right.val: # If the next node in 'left' is greater than the current node in 'right'
            temp = right.next
            right.next = left.next
            left.next = right
            right = temp
        left = left.next
    if right: # If there are remaining nodes in 'right', append them to 'left'
        left.next = right
    return head

def get_size(head):
    """
    Calculates the number of nodes in a linked list.

    Args:
        head (ListNode): The head of the linked list.

    Returns:
        int: The number of nodes in the linked list.
    """
    count = 0      # Initialize a counter
    while head:     # Iterate through the list
        count += 1 # Increment the counter for each node
        head = head.next # Move to the next node
    return count    # Return the final count

def print_list(head):
    """
    Prints the values of the nodes in a linked list in a readable format.

    Args:
        head (ListNode): The head of the linked list.

    Returns:
        str: A string representation of the linked list.
    """
    result = [] # Initialize an empty list to store the node values
    while head:    # Iterate through the list
        result.append(str(head.val)) # Convert the node value to a string and append it to the list
        head = head.next       # Move to the next node
    return " -> ".join(result) # Join the node values with " -> " and return the resulting string

# Test Cases
def test_merge_sorts():
    """
    Tests the different merge sort implementations with a sample linked list.
    """
    # Create a sample linked list: 7 -> 3 -> 5 -> 1 -> 9 -> 2 -> 6
    nodes = [ListNode(val) for val in [7, 3, 5, 1, 9, 2, 6]]
    for i in range(len(nodes) - 1):
        nodes[i].next = nodes[i + 1]

    print("Original List:", print_list(nodes[0])) # Print the original list
    print("Sorted (Tail Recursion):", print_list(merge_sort_tail_recursion(nodes[0]))) #test and print
    print("Sorted (Bottom-Up):", print_list(merge_sort_bottom_up(nodes[0])))  #test and print
    print("Sorted (Three-Way Partitioning):", print_list(merge_sort_three_way(nodes[0]))) #test and print
    print("Sorted (Dummy Nodes):", print_list(merge_sort_dummy_nodes(nodes[0]))) #test and print
    print("Sorted (Slow-Fast Pointer):", print_list(merge_sort_slow_fast_pointer(nodes[0]))) #test and print
    print("Sorted (In-Place Rewiring):", print_list(merge_sort_in_place(nodes[0]))) #test and print

test_merge_sorts() # Run the test cases
