class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def create_linked_list(arr):
    if not arr:
        return None
    head = ListNode(arr[0])
    curr = head
    for i in range(1, len(arr)):
        curr.next = ListNode(arr[i])
        curr = curr.next
    return head

def linked_list_to_list(head):
    result = []
    curr = head
    while curr:
        result.append(curr.val)
        curr = curr.next
    return result

def remove_nth_from_end(head, n):
    """
    1. Two-Pass Approach: Calculate length, then remove.
    """
    if not head:
        return None

    length = 0
    curr = head
    while curr:
        length += 1
        curr = curr.next

    if n > length:
        return head

    if n == length:
        return head.next

    curr = head
    for _ in range(length - n - 1):
        curr = curr.next

    curr.next = curr.next.next
    return head

def remove_nth_from_end_two_pointers(head, n):
    """
    2. Two-Pointer Approach: Single pass with two pointers.
    """
    dummy = ListNode(0)
    dummy.next = head
    fast = dummy
    slow = dummy

    for _ in range(n + 1):
        fast = fast.next

    while fast:
        fast = fast.next
        slow = slow.next

    slow.next = slow.next.next
    return dummy.next

def remove_nth_from_end_recursive(head, n):
    """
    3. Recursive Approach: Calculate length recursively.
    """
    def remove_recursive(node, n, count):
        if not node:
            return 0, None

        length, next_node = remove_recursive(node.next, n, count)
        length += 1

        if length == n + 1:
            return length, node.next

        node.next = next_node
        return length, node

    _, new_head = remove_recursive(head, n, [0])
    return new_head if _ != n else head.next

def remove_nth_from_end_stack(head, n):
    """
    4. Stack Approach: Store nodes in a stack, then remove.
    """
    stack = []
    curr = head
    while curr:
        stack.append(curr)
        curr = curr.next

    if n > len(stack):
        return head

    if n == len(stack):
        return head.next

    prev = stack[-n-1] if -n -1 >= -len(stack) else None

    if prev:
        prev.next = stack[-n].next
    else:
        return head.next

    return head

def remove_nth_from_end_reverse(head, n):
    """
    5. Reverse and Reverse Back Approach: Reverse, remove, reverse back.
    """
    def reverse_linked_list(node):
        prev, curr = None, node
        while curr:
            next_node = curr.next
            curr.next = prev
            prev = curr
            curr = next_node
        return prev

    reversed_head = reverse_linked_list(head)

    if n == 1:
        return reverse_linked_list(reversed_head.next)

    curr = reversed_head
    for _ in range(n - 2):
        curr = curr.next

    curr.next = curr.next.next

    return reverse_linked_list(reversed_head)

def remove_nth_from_end_dictionary(head,n):
    """
    6. Dictionary Approach: Store nodes with their index, then remove.
    """
    node_dict = {}
    curr = head
    index = 0
    while curr:
        node_dict[index] = curr
        curr = curr.next
        index+=1

    if n > index:
        return head
    if n == index:
        return head.next

    prev_node_index = index-n-1
    if prev_node_index >= 0:
        node_dict[prev_node_index].next = node_dict[index-n].next
    else:
        return head.next
    return head

# Example Usage and Testing
arr = [1, 2, 3, 4, 5]
head = create_linked_list(arr)
n = 2

# Test each approach
print("Original List:", linked_list_to_list(head))

head1 = create_linked_list(arr.copy())
result1 = remove_nth_from_end(head1, n)
print("Two-Pass:", linked_list_to_list(result1))

head2 = create_linked_list(arr.copy())
result2 = remove_nth_from_end_two_pointers(head2, n)
print("Two-Pointers:", linked_list_to_list(result2))

head3 = create_linked_list(arr.copy())
result3 = remove_nth_from_end_recursive(head3, n)
print("Recursive:", linked_list_to_list(result3))

head4 = create_linked_list(arr.copy())
result4 = remove_nth_from_end_stack(head4, n)
print("Stack:", linked_list_to_list(result4))

head5 = create_linked_list(arr.copy())
result5 = remove_nth_from_end_reverse(head5, n)
print("Reverse:", linked_list_to_list(result5))

head6 = create_linked_list(arr.copy())
result6 = remove_nth_from_end_dictionary(head6,n)
print("Dictionary:", linked_list_to_list(result6))