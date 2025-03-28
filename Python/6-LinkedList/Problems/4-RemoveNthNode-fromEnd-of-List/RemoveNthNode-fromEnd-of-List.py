class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# Approach 1: Two-Pointer Technique (Optimal Solution)
def removeNthFromEnd_two_pointers(head, n):
    """Removes the nth node from the end using the two-pointer method."""
    dummy = ListNode(0, head)
    first = second = dummy
    for _ in range(n + 1):
        first = first.next
    while first:
        first, second = first.next, second.next
    second.next = second.next.next
    return dummy.next

# Approach 2: Compute Length First (Iterative Approach)
def removeNthFromEnd_length(head, n):
    """First computes the length of the list, then removes the nth node from the end."""
    dummy = ListNode(0, head)
    length, current = 0, head
    while current:
        length += 1
        current = current.next
    current = dummy
    for _ in range(length - n):
        current = current.next
    current.next = current.next.next
    return dummy.next

# Approach 3: Stack-Based Approach (Using Extra Space)
def removeNthFromEnd_stack(head, n):
    """Uses a stack to store nodes, then finds and removes the nth node from the end."""
    dummy = ListNode(0, head)
    stack = []
    current = dummy
    while current:
        stack.append(current)
        current = current.next
    for _ in range(n):
        stack.pop()
    prev = stack[-1]
    prev.next = prev.next.next
    return dummy.next

# Approach 4: Recursive Approach (Recursive Backtracking)
def removeNthFromEnd_recursive(head, n):
    """Uses recursion to reach the end and remove the nth node."""
    def helper(node, n):
        if not node:
            return 0, node
        count, node.next = helper(node.next, n)
        return count + 1, (node if count + 1 != n else node.next)

    _, new_head = helper(head, n)
    return new_head

# Approach 5: Modify List Using Sentinel Nodes (Alternative Dummy Node Approach)
def removeNthFromEnd_sentinel(head, n):
    """Uses a sentinel node to simplify edge cases like removing the head."""
    sentinel = ListNode(0, head)
    slow, fast = sentinel, sentinel
    for _ in range(n + 1):
        fast = fast.next
    while fast:
        slow, fast = slow.next, fast.next
    slow.next = slow.next.next
    return sentinel.next

# Utility Functions
def create_linked_list(vals):
    """Creates a linked list from a list of values."""
    dummy = ListNode()
    tail = dummy
    for val in vals:
        tail.next = ListNode(val)
        tail = tail.next
    return dummy.next

def print_linked_list(head):
    """Prints a linked list in a readable format."""
    values = []
    while head:
        values.append(str(head.val))
        head = head.next
    print(" -> ".join(values) if values else "Empty List")

# Example Usage
values = [1, 2, 3, 4, 5]
n = 2
head = create_linked_list(values)
print("Two-Pointer Approach:")
print_linked_list(removeNthFromEnd_two_pointers(head, n))

head = create_linked_list(values)
print("Length-Based Approach:")
print_linked_list(removeNthFromEnd_length(head, n))

head = create_linked_list(values)
print("Stack-Based Approach:")
print_linked_list(removeNthFromEnd_stack(head, n))

head = create_linked_list(values)
print("Recursive Approach:")
print_linked_list(removeNthFromEnd_recursive(head, n))

head = create_linked_list(values)
print("Sentinel Node Approach:")
print_linked_list(removeNthFromEnd_sentinel(head, n))
