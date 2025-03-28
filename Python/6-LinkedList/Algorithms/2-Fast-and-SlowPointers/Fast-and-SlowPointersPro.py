import random
import time

class ListNode:
    """
    Node class for a singly linked list.
    """
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

def measure_execution_time(func, *args, **kwargs):
    """
    Helper function to measure the execution time of a function.
    """
    start_time = time.time()
    result = func(*args, **kwargs)
    end_time = time.time()
    execution_time = end_time - start_time
    return result, execution_time

# 1. Detect a Cycle in a Linked List (Real-world use case: Memory Leak Detection)
def has_cycle(head):
    """
    Detects if a linked list has a cycle.  This is crucial for detecting
    memory leaks in systems where linked lists are used to manage resources.
    If a cycle exists, it means a resource is not being properly released.

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

# 2. Find the Middle of a Linked List (Real-world use case: Efficient Data Access)
def find_middle(head):
    """
    Finds the middle node of a linked list.  This is useful in applications
    where data needs to be accessed or processed in the middle, such as in
    certain database operations or when implementing a linked list-based queue
    with priority.

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

# 3. Find the Starting Point of a Cycle in a Linked List (Real-world use case: Debugging Circular Dependencies)
def find_cycle_start(head):
    """
    Finds the starting point of a cycle in a linked list.  In complex systems,
    circular dependencies between objects can be represented as a linked list
    with a cycle.  This function helps pinpoint the start of the dependency loop,
    aiding in debugging.

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
            slow2 = head
            while slow2 != slow:
                slow = slow.next
                slow2 = slow2.next
            return slow2
    return None

# 4. Check if a Linked List is a Palindrome (Real-world use case: Data Validation)
def is_palindrome(head):
    """
    Checks if a linked list is a palindrome.  This can be used in data
    validation scenarios, such as verifying if a string of data read from
    a file or network is the same forwards and backward.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not head or not head.next:
        return True

    slow = head
    fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next

    prev = None
    curr = slow
    while curr:
        next_node = curr.next
        curr.next = prev
        prev = curr
        curr = next_node

    first_half = head
    second_half = prev
    while second_half:
        if first_half.val != second_half.val:
            return False
        first_half = first_half.next
        second_half = second_half.next
    return True

# 5. Remove Nth Node From End of List (Real-world use case: Log File Management)
def remove_nth_from_end(head, n):
    """
    Removes the nth node from the end of a linked list.  In log file management,
    where logs are often stored as linked lists, this function can be used to
    remove older entries (e.g., the oldest n entries) to maintain a certain log size.

    Time Complexity: O(n)
    Space Complexity: O(1)
    """
    if not head:
        return None
    dummy = ListNode(0)
    dummy.next = head
    slow = dummy
    fast = dummy
    for _ in range(n):
        if not fast:
            return None
        fast = fast.next

    while fast and fast.next:
        slow = slow.next
        fast = fast.next

    slow.next = slow.next.next
    return dummy.next

# 6.  Merge Two Sorted Linked Lists (Real-world use case:  Sorted Data Aggregation)
def merge_two_lists(list1, list2):
    """
    Merges two sorted linked lists into one sorted linked list.  This is a
    fundamental operation in data processing, such as merging sorted results
    from multiple database queries or combining sorted data streams.

    Time Complexity: O(m+n), where m and n are the lengths of the two lists.
    Space Complexity: O(1) - Iterative approach.
    """
    dummy = ListNode()
    tail = dummy

    while list1 and list2:
        if list1.val <= list2.val:
            tail.next = list1
            list1 = list1.next
        else:
            tail.next = list2
            list2 = list2.next
        tail = tail.next

    if list1:
        tail.next = list1
    elif list2:
        tail.next = list2

    return dummy.next
if __name__ == "__main__":
    # Test cases with more descriptive outputs and timing
    print("1. Detect a Cycle in a Linked List (Memory Leak Detection)")
    list1 = create_linked_list([1, 2, 3, 4, 5])
    print("List:", end=" ")
    print_linked_list(list1)
    result, time1 = measure_execution_time(has_cycle, list1)
    print(f"Has cycle: {result}, Time: {time1:.6f} seconds")

    list2 = create_linked_list([1, 2, 3, 4, 5])
    list2.next.next.next.next.next = list2.next
    print("List with cycle:", end=" ")
    print("Cannot print due to cycle")
    result, time2 = measure_execution_time(has_cycle, list2)
    print(f"Has cycle: {result}, Time: {time2:.6f} seconds")

    print("\n2. Find the Middle of a Linked List (Efficient Data Access)")
    list3 = create_linked_list([1, 2, 3, 4, 5])
    print("List:", end=" ")
    print_linked_list(list3)
    middle3, time3 = measure_execution_time(find_middle, list3)
    print(f"Middle node: {middle3.val if middle3 else None}, Time: {time3:.6f} seconds")

    list4 = create_linked_list([1, 2, 3, 4, 5, 6, 7, 8])
    print("List:", end=" ")
    print_linked_list(list4)
    middle4, time4 = measure_execution_time(find_middle, list4)
    print(f"Middle node: {middle4.val if middle4 else None}, Time: {time4:.6f} seconds")

    print("\n3. Find the Starting Point of a Cycle (Debugging Circular Dependencies)")
    list5 = create_linked_list([1, 2, 3, 4, 5])
    print("List:", end=" ")
    print_linked_list(list5)
    cycle_start5, time5 = measure_execution_time(find_cycle_start, list5)
    print(f"Cycle start: {cycle_start5.val if cycle_start5 else None}, Time: {time5:.6f} seconds")

    list6 = create_linked_list([1, 2, 3, 4, 5])
    list6.next.next.next.next.next = list6.next
    print("List with cycle:", end=" ")
    print("Cannot print due to cycle")
    cycle_start6, time6 = measure_execution_time(find_cycle_start, list6)
    print(f"Cycle start: {cycle_start6.val if cycle_start6 else None}, Time: {time6:.6f} seconds")

    print("\n4. Check if a Linked List is a Palindrome (Data Validation)")
    list7 = create_linked_list([1, 2, 3, 2, 1])
    print("List:", end=" ")
    print_linked_list(list7)
    result7, time7 = measure_execution_time(is_palindrome, list7)
    print(f"Is palindrome: {result7}, Time: {time7:.6f} seconds")

    list8 = create_linked_list([1, 2, 3, 4, 5])
    print("List:", end=" ")
    print_linked_list(list8)
    result8, time8 = measure_execution_time(is_palindrome, list8)
    print(f"Is palindrome: {result8}, Time: {time8:.6f} seconds")

    print("\n5. Remove Nth Node From End of List (Log File Management)")
    list9 = create_linked_list([1, 2, 3, 4, 5])
    print("Original List:", end=" ")
    print_linked_list(list9)
    n9 = 2
    new_head9, time9 = measure_execution_time(remove_nth_from_end, list9, n9)
    print(f"Remove {n9}th node from end. New list:", end=" ")
    print_linked_list(new_head9)
    print(f"Time: {time9:.6f} seconds")

    list10 = create_linked_list([1, 2, 3, 4, 5])
    print("Original List:", end=" ")
    print_linked_list(list10)
    n10 = 5
    new_head10, time10 = measure_execution_time(remove_nth_from_end, list10, n10)
    print(f"Remove {n10}th node from end. New list:", end=" ")
    print_linked_list(new_head10)
    print(f"Time: {time10:.6f} seconds")

    print("\n6. Merge Two Sorted Linked Lists (Sorted Data Aggregation)")
    list11 = create_linked_list([1, 3, 5, 7])
    list12 = create_linked_list([2, 4, 6, 8])
    print("List 1:", end=" ")
    print_linked_list(list11)
    print("List 2:", end=" ")
    print_linked_list(list12)
    merged_list, time11 = measure_execution_time(merge_two_lists, list11, list12)
    print("Merged List:", end=" ")
    print_linked_list(merged_list)
    print(f"Time: {time11:.6f} seconds")
