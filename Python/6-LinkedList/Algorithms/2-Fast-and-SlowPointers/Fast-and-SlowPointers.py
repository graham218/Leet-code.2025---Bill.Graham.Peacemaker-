class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def create_linked_list(values):
    """
    Helper function to create a linked list from a list of values.
    """
    if not values:
        return None
    head = ListNode(values[0])
    curr = head
    for val in values[1:]:
        curr.next = ListNode(val)
        curr = curr.next
    return head

def print_linked_list(head):
    """
    Helper function to print the values of a linked list.
    """
    result = []
    curr = head
    while curr:
        result.append(curr.val)
        curr = curr.next
    print(result)

# 1. Detect a Cycle in a Linked List
def has_cycle(head):
    """
    Given the head of a linked list, determine if the linked list has a cycle.
    Uses the fast and slow pointer approach.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not head or not head.next:
        return False
    slow = head
    fast = head.next
    while slow and fast and fast.next:
        if slow == fast:
            return True
        slow = slow.next
        fast = fast.next.next
    return False

# 2. Find the Middle of a Linked List
def find_middle(head):
    """
    Given the head of a linked list, find the middle node of the linked list.
    If there are two middle nodes, return the second middle node.
    Uses the fast and slow pointer approach.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not head:
        return None
    slow = head
    fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    return slow

# 3. Find the Starting Point of a Cycle in a Linked List
def find_cycle_start(head):
    """
    Given the head of a linked list, find the node where the cycle begins.
    If there is no cycle, return None.
    Uses the fast and slow pointer approach.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not head or not head.next:
        return None
    slow = head
    fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            # Cycle detected, find the start
            slow2 = head
            while slow2 != slow:
                slow = slow.next
                slow2 = slow2.next
            return slow2
    return None

# 4. Check if a Linked List is a Palindrome
def is_palindrome(head):
    """
    Given the head of a singly linked list, determine if it is a palindrome.
    Uses the fast and slow pointer approach to find the middle, reverse the second half, and compare.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not head or not head.next:
        return True

    # Find the middle of the linked list
    slow = head
    fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next

    # Reverse the second half of the linked list
    prev = None
    curr = slow
    while curr:
        next_node = curr.next
        curr.next = prev
        prev = curr
        curr = next_node

    # Compare the first half and the reversed second half
    first_half = head
    second_half = prev  # prev is now the head of the reversed second half
    while second_half:
        if first_half.val != second_half.val:
            return False
        first_half = first_half.next
        second_half = second_half.next
    return True

# 5. Remove Nth Node From End of List
def remove_nth_from_end(head, n):
    """
    Given the head of a linked list, remove the nth node from the end of the list and return its head.
    Uses the fast and slow pointer approach.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not head:
        return None
    # Create a dummy node to handle the case where the head needs to be removed.
    dummy = ListNode(0)
    dummy.next = head
    slow = dummy
    fast = dummy
    # Move fast pointer n steps ahead
    for _ in range(n):
        if not fast:  # Handle cases where n is larger than the list length
            return None
        fast = fast.next

    # Move slow and fast pointers until fast reaches the end
    while fast and fast.next:
        slow = slow.next
        fast = fast.next

    # Remove the nth node from the end
    slow.next = slow.next.next

    return dummy.next
if __name__ == "__main__":
    # Test cases for each function
    print("1. Detect a Cycle in a Linked List")
    list1 = create_linked_list([1, 2, 3, 4, 5])
    print("List:", end=" ")
    print_linked_list(list1)
    print("Has cycle:", has_cycle(list1))  # Output: False

    list2 = create_linked_list([1, 2, 3, 4, 5])
    # Create a cycle: 5 -> 2
    list2.next.next.next.next.next = list2.next
    print("List with cycle:", end=" ")
    print("Cannot print due to cycle")
    print("Has cycle:", has_cycle(list2))  # Output: True

    print("\n2. Find the Middle of a Linked List")
    list3 = create_linked_list([1, 2, 3, 4, 5])
    print("List:", end=" ")
    print_linked_list(list3)
    middle3 = find_middle(list3)
    print("Middle node:", middle3.val if middle3 else None)  # Output: 3

    list4 = create_linked_list([1, 2, 3, 4, 5, 6])
    print("List:", end=" ")
    print_linked_list(list4)
    middle4 = find_middle(list4)
    print("Middle node:", middle4.val if middle4 else None)  # Output: 4

    print("\n3. Find the Starting Point of a Cycle in a Linked List")
    list5 = create_linked_list([1, 2, 3, 4, 5])
    print("List:", end=" ")
    print_linked_list(list5)
    print("Cycle start:", find_cycle_start(list5))  # Output: None

    list6 = create_linked_list([1, 2, 3, 4, 5])
    # Create a cycle: 5 -> 2
    list6.next.next.next.next.next = list6.next
    print("List with cycle:", end=" ")
    print("Cannot print due to cycle")
    cycle_start6 = find_cycle_start(list6)
    print("Cycle start:", cycle_start6.val if cycle_start6 else None)  # Output: 2

    print("\n4. Check if a Linked List is a Palindrome")
    list7 = create_linked_list([1, 2, 3, 2, 1])
    print("List:", end=" ")
    print_linked_list(list7)
    print("Is palindrome:", is_palindrome(list7))  # Output: True

    list8 = create_linked_list([1, 2, 3, 4, 5])
    print("List:", end=" ")
    print_linked_list(list8)
    print("Is palindrome:", is_palindrome(list8))  # Output: False

    print("\n5. Remove Nth Node From End of List")
    list9 = create_linked_list([1, 2, 3, 4, 5])
    print("List:", end=" ")
    print_linked_list(list9)
    n9 = 2
    new_head9 = remove_nth_from_end(list9, n9)
    print(f"Remove {n9}th node from end. New list:", end=" ")
    print_linked_list(new_head9)  # Output: [1, 2, 3, 5]

    list10 = create_linked_list([1, 2, 3, 4, 5])
    print("List:", end=" ")
    print_linked_list(list10)
    n10 = 5
    new_head10 = remove_nth_from_end(list10, n10)
    print(f"Remove {n10}th node from end. New list:", end=" ")
    print_linked_list(new_head10)  # Output: [2, 3, 4, 5]

    list11 = create_linked_list([1, 2])
    print("List:", end=" ")
    print_linked_list(list11)
    n11 = 1
    new_head11 = remove_nth_from_end(list11, n11)
    print(f"Remove {n11}th node from end. New list:", end=" ")
    print_linked_list(new_head11)
