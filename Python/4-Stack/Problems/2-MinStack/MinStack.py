'''
Min Stack - Five Different Approaches

Problem Statement:
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

Operations:
  - push(x) -- Push element x onto stack.
  - pop() -- Removes the element on top of the stack.
  - top() -- Get the top element.
  - getMin() -- Retrieve the minimum element in the stack.
'''

# 1. Using Two Stacks (Standard Approach - O(1) for all operations)
class MinStack:
    """
    Implements a Min Stack using two stacks: one to store the elements and another to store the minimums.
    This approach ensures that getMin() operation is always O(1).
    """
    def __init__(self):
        """
        Initializes the MinStack object.
        stack:  The main stack to store elements.
        min_stack: A stack to store the minimum elements encountered so far.
        """
        self.stack = []
        self.min_stack = []

    def push(self, x: int):
        """
        Pushes an element onto the stack.

        Args:
            x: The integer to push onto the stack.
        """
        self.stack.append(x)  # Push the element onto the main stack.
        if not self.min_stack or x <= self.min_stack[-1]:
            # If the min_stack is empty or the new element is less than or equal to the current minimum,
            # push it onto the min_stack as well.  We use <= to handle duplicate minimums.
            self.min_stack.append(x)

    def pop(self):
        """
        Removes the element on top of the stack.
        """
        if self.stack:  # Make sure the stack is not empty before popping.
            if self.stack[-1] == self.min_stack[-1]:
                # If the top element of the main stack is the same as the top element of the min_stack,
                # pop it from the min_stack as well.
                self.min_stack.pop()
            self.stack.pop()  # Pop from the main stack.

    def top(self):
        """
        Gets the top element of the stack.

        Returns:
            The top element of the stack, or None if the stack is empty.
        """
        return self.stack[-1] if self.stack else None  # Return the last element if stack is not empty else return None

    def getMin(self):
        """
        Retrieves the minimum element in the stack.

        Returns:
            The minimum element in the stack, or None if the stack is empty.
        """
        return self.min_stack[-1] if self.min_stack else None # Return the last element if min_stack is not empty else return None

# 2. Using a Single Stack with Tuples (Space Optimized - O(1) for all operations)
class MinStackTuple:
    """
    Implements a Min Stack using a single stack, where each element is a tuple containing the value and the current minimum.
    This approach optimizes space by avoiding the extra min_stack.
    """
    def __init__(self):
        """
        Initializes the MinStackTuple object.
        stack: The stack to store tuples of (value, minimum).
        """
        self.stack = []

    def push(self, x: int):
        """
        Pushes an element onto the stack.

        Args:
            x: The integer to push onto the stack.
        """
        min_val = x if not self.stack else min(x, self.stack[-1][1])
        # Determine the minimum value: either the new element or the previous minimum.
        self.stack.append((x, min_val))  # Push the element and the minimum value as a tuple.

    def pop(self):
        """
        Removes the element on top of the stack.
        """
        if self.stack:  # Make sure the stack is not empty.
            self.stack.pop()

    def top(self):
        """
        Gets the top element of the stack.

        Returns:
            The top element of the stack, or None if the stack is empty.
        """
        return self.stack[-1][0] if self.stack else None  # Return the value (first element of the tuple).

    def getMin(self):
        """
        Retrieves the minimum element in the stack.

        Returns:
            The minimum element in the stack, or None if the stack is empty.
        """
        return self.stack[-1][1] if self.stack else None  # Return the minimum value (second element of the tuple).

# 3. Using a Linked List (Alternative Approach - O(1) for all operations)
class Node:
    """
    Represents a node in the linked list used to implement the Min Stack.
    Each node stores its value, the minimum value seen so far, and a pointer to the next node.
    """
    def __init__(self, value: int, min_value: int, next_node=None):
        """
        Initializes a Node object.

        Args:
            value: The value of the node.
            min_value: The minimum value seen so far in the stack up to this node.
            next_node: A pointer to the next node in the list.
        """
        self.value = value
        self.min_value = min_value
        self.next = next_node

class MinStackLinkedList:
    """
    Implements a Min Stack using a singly linked list.  The head of the list represents the top of the stack.
    """
    def __init__(self):
        """
        Initializes the MinStackLinkedList object.
        head: The head of the linked list (top of the stack).
        """
        self.head = None

    def push(self, x: int):
        """
        Pushes an element onto the stack.

        Args:
            x: The integer to push onto the stack.
        """
        if not self.head:
            # If the list is empty, the new node is both the top and the minimum.
            self.head = Node(x, x)
        else:
            # Otherwise, create a new node, with its min value being the min of the new value and the current min,
            # and make it the new head.
            self.head = Node(x, min(x, self.head.min_value), self.head)

    def pop(self):
        """
        Removes the element on top of the stack.
        """
        if self.head:  # Make sure the list is not empty.
            self.head = self.head.next  # Move the head to the next node.

    def top(self):
        """
        Gets the top element of the stack.

        Returns:
            The top element of the stack, or None if the stack is empty.
        """
        return self.head.value if self.head else None  # Return the value of the head node.

    def getMin(self):
        """
        Retrieves the minimum element in the stack.

        Returns:
            The minimum element in the stack, or None if the stack is empty.
        """
        return self.head.min_value if self.head else None  # Return the minimum value stored in the head node.

# 4. Using Deque (Efficient Pop/Push Operations - O(1) for all operations)
from collections import deque

class MinStackDeque:
    """
    Implements a Min Stack using deques (double-ended queues) for both the main stack and the minimum stack.
    A deque provides O(1) time complexity for both push and pop operations from both ends,
    making it suitable for stack implementation.  This is very similar to the Two Stacks approach.
    """
    def __init__(self):
        """
        Initializes the MinStackDeque object.
        stack:  The main stack (a deque) to store elements.
        min_stack: A deque to store the minimum elements.
        """
        self.stack = deque()
        self.min_stack = deque()

    def push(self, x: int):
        """
        Pushes an element onto the stack.

        Args:
            x: The integer to push onto the stack.
        """
        self.stack.append(x)
        if not self.min_stack or x <= self.min_stack[-1]:
            self.min_stack.append(x)

    def pop(self):
        """
        Removes the element on top of the stack.
        """
        if self.stack:
            if self.stack[-1] == self.min_stack[-1]:
                self.min_stack.pop()
            self.stack.pop()

    def top(self):
        """
        Gets the top element of the stack.

        Returns:
            The top element of the stack, or None if the stack is empty.
        """
        return self.stack[-1] if self.stack else None

    def getMin(self):
        """
        Retrieves the minimum element in the stack.

        Returns:
            The minimum element in the stack, or None if the stack is empty.
        """
        return self.min_stack[-1] if self.min_stack else None

# 5. Using a Sorted List (Efficient Minimum Retrieval - O(1) for getMin, O(logN) for push/pop)
import bisect  # Import the bisect module for sorted list operations.

class MinStackSortedList:
    """
    Implements a Min Stack using a standard list for the stack and a sorted list (maintained using the bisect module)
    to keep track of the minimum elements.  This approach provides O(1) getMin() but O(logN) push() and pop().
    """
    def __init__(self):
        """
        Initializes the MinStackSortedList object.
        stack:  The main stack to store elements.
        sorted_list: A sorted list to store all elements, allowing for O(1) minimum retrieval.
        """
        self.stack = []
        self.sorted_list = []

    def push(self, x: int):
        """
        Pushes an element onto the stack.

        Args:
            x: The integer to push onto the stack.
        """
        self.stack.append(x)
        bisect.insort(self.sorted_list, x)  # Insert x into the sorted list while maintaining sorted order (O(logN)).

    def pop(self):
        """
        Removes the element on top of the stack.
        """
        if self.stack:
            x = self.stack.pop()  # Pop from the main stack.
            self.sorted_list.remove(x)  # Remove x from the sorted list (O(N) in worst case, but closer to O(logN) on average).

    def top(self):
        """
        Gets the top element of the stack.

        Returns:
            The top element of the stack, or None if the stack is empty.
        """
        return self.stack[-1] if self.stack else None

    def getMin(self):
        """
        Retrieves the minimum element in the stack.

        Returns:
            The minimum element in the stack, or None if the stack is empty.
        """
        return self.sorted_list[0] if self.sorted_list else None  # The first element of the sorted list is always the minimum.

# Test Cases
stacks = [MinStack(), MinStackTuple(), MinStackLinkedList(), MinStackDeque(), MinStackSortedList()]

for i, stack in enumerate(stacks):
    print(f"\nTesting Approach {i + 1}:")
    stack.push(5)
    stack.push(2)
    stack.push(8)
    stack.push(1)
    print(f"Top Element: {stack.top()}")
    print(f"Minimum Element: {stack.getMin()}")
    stack.pop()
    print(f"Minimum after one pop: {stack.getMin()}")
