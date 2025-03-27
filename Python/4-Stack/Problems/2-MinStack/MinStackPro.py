'''
Advanced Min Stack - Real-World Implementations (New Version)

Problem Statement:
Design a stack that supports push, pop, top, and retrieving the minimum element efficiently.

Operations:
  - push(x) -- Push element x onto stack.
  - pop() -- Removes the element on top of the stack.
  - top() -- Get the top element.
  - getMin() -- Retrieve the minimum element in the stack.

Each implementation mimics a real-world use case.
'''

from collections import deque
import heapq  # Import the heapq module for heap-based implementation.
import bisect # Import bisect

# 1. High-Frequency Trading System (Using Two Stacks - O(1) operations)
class MinStackTrading:
    """
    Implements a Min Stack for a high-frequency trading system.  In this scenario,
    efficiently tracking the minimum price or order value is crucial for making
    quick decisions.  Using two stacks provides O(1) time complexity for all operations,
    which is essential for minimizing latency in trading.
    """
    def __init__(self):
        """
        Initializes the MinStackTrading object.
        stack: The main stack to store trade prices or order values.
        min_stack: A stack to store the minimum prices/values encountered so far.
        """
        self.stack = []
        self.min_stack = []

    def push(self, x: int):
        """
        Pushes a trade price/value onto the stack.

        Args:
            x: The trade price or order value.
        """
        self.stack.append(x)
        # Maintain the min_stack to track the minimum price/value.
        self.min_stack.append(x if not self.min_stack else min(x, self.min_stack[-1]))

    def pop(self):
        """
        Pops a trade price/value from the stack.
        """
        if self.stack:
            self.stack.pop()
            self.min_stack.pop()  # Keep the min_stack synchronized with the main stack.

    def top(self):
        """
        Gets the top trade price/value.

        Returns:
            The top price/value, or None if the stack is empty.
        """
        return self.stack[-1] if self.stack else None

    def getMin(self):
        """
        Gets the minimum trade price/value.

        Returns:
            The minimum price/value, or None if the stack is empty.
        """
        return self.min_stack[-1] if self.min_stack else None

# 2. Banking Fraud Detection (Using Deque - O(1) operations)
class MinStackBanking:
    """
    Implements a Min Stack for a banking fraud detection system.  This can be used to track
    transaction amounts and quickly identify the smallest transaction within a recent window.
    A deque is used here, offering efficient push and pop operations from both ends,
    which can be useful for implementing a sliding window of transactions.
    """
    def __init__(self):
        """
        Initializes the MinStackBanking object.
        stack:  The main stack (a deque) to store transaction amounts.
        min_stack: A deque to store the minimum transaction amounts.
        """
        self.stack = deque()
        self.min_stack = deque()

    def push(self, x: int):
        """
        Pushes a transaction amount onto the stack.

        Args:
            x: The transaction amount.
        """
        self.stack.append(x)
        self.min_stack.append(x if not self.min_stack else min(x, self.min_stack[-1]))

    def pop(self):
        """
        Pops a transaction amount from the stack.
        """
        if self.stack:
            self.stack.pop()
            self.min_stack.pop()

    def top(self):
        """
        Gets the top transaction amount.

        Returns:
            The top amount, or None if the stack is empty.
        """
        return self.stack[-1] if self.stack else None

    def getMin(self):
        """
        Gets the minimum transaction amount.

        Returns:
            The minimum amount, or None if the stack is empty.
        """
        return self.min_stack[-1] if self.min_stack else None

# 3. Smart City Traffic Data Stack (Using Heap - O(logN) operations)
class MinStackTraffic:
    """
    Implements a Min Stack for a smart city traffic management system.  This can be used to
    track traffic density or flow rate, and efficiently retrieve the minimum value.  A heap
    is used here, which is very efficient for finding the minimum but less efficient for
    removing arbitrary elements.  This might be suitable if you frequently need the minimum
    but don't always remove elements in LIFO order.
    """
    def __init__(self):
        """
        Initializes the MinStackTraffic object.
        stack:  The main stack to store traffic data.
        min_heap: A min-heap to store traffic data, allowing for efficient retrieval of the minimum.
        """
        self.stack = []
        self.min_heap = []  # Use a list as the underlying storage for the heap.

    def push(self, x: int):
        """
        Pushes traffic data onto the stack.

        Args:
            x: The traffic data (e.g., density, flow rate).
        """
        self.stack.append(x)
        heapq.heappush(self.min_heap, x)  # Push the data onto the min-heap (O(logN)).

    def pop(self):
        """
        Pops traffic data from the stack.
        """
        if self.stack:
            x = self.stack.pop()
            self.min_heap.remove(x) # Remove the element from the heap (O(N) - inefficient).
            heapq.heapify(self.min_heap)  # Re-heapify the remaining elements (O(N)).

    def top(self):
        """
        Gets the top traffic data.

        Returns:
            The top data, or None if the stack is empty.
        """
        return self.stack[-1] if self.stack else None

    def getMin(self):
        """
        Gets the minimum traffic data.

        Returns:
            The minimum data, or None if the heap is empty.
        """
        return self.min_heap[0] if self.min_heap else None  # The minimum is always at the root of the min-heap (O(1)).

# 4. IoT Sensor Monitoring Stack (Using Tuples - O(1) operations)
class MinStackIoT:
    """
    Implements a Min Stack for an IoT sensor monitoring system.  This can be used to track
    sensor readings (e.g., temperature, humidity) and efficiently retrieve the minimum reading.
    Using tuples within a single stack optimizes space, which can be important for
    resource-constrained IoT devices.
    """
    def __init__(self):
        """
        Initializes the MinStackIoT object.
        stack: The stack to store tuples of (sensor reading, minimum reading).
        """
        self.stack = []

    def push(self, x: int):
        """
        Pushes a sensor reading onto the stack.

        Args:
            x: The sensor reading.
        """
        min_val = x if not self.stack else min(x, self.stack[-1][1])
        # Store the current reading and the minimum reading seen so far.
        self.stack.append((x, min_val))

    def pop(self):
        """
        Pops a sensor reading from the stack.
        """
        if self.stack:
            self.stack.pop()

    def top(self):
        """
        Gets the top sensor reading.

        Returns:
            The top reading, or None if the stack is empty.
        """
        return self.stack[-1][0] if self.stack else None  # Return the first element of the tuple (the reading).

    def getMin(self):
        """
        Gets the minimum sensor reading.

        Returns:
            The minimum reading, or None if the stack is empty.
        """
        return self.stack[-1][1] if self.stack else None  # Return the second element of the tuple (the minimum).

# 5. Healthcare Record System (Using Linked List - O(1) operations)
class Node:
    """
    Represents a node in the linked list used for the MinStackHealthcare implementation.
    Each node stores a patient's vital sign, the minimum vital sign seen so far,
    and a pointer to the next node.
    """
    def __init__(self, value: int, min_value: int, next_node=None):
        """
        Initializes a Node object.

        Args:
            value: The vital sign value.
            min_value: The minimum vital sign value seen so far.
            next_node: Pointer to the next node.
        """
        self.value = value
        self.min_value = min_value
        self.next = next_node

class MinStackHealthcare:
    """
    Implements a Min Stack for a healthcare record system using a linked list.  This can be used
    to track patients' vital signs (e.g., heart rate, blood pressure) and efficiently retrieve
    the minimum value.  A linked list is suitable for scenarios where data is frequently
    added and removed.
    """
    def __init__(self):
        """
        Initializes the MinStackHealthcare object.
        head: The head of the linked list.
        """
        self.head = None

    def push(self, x: int):
        """
        Pushes a patient's vital sign onto the stack.

        Args:
            x: The vital sign value.
        """
        if not self.head:
            # If the list is empty, the new node is both the top and the minimum.
            self.head = Node(x, x)
        else:
            # Create a new node and make it the new head, updating the minimum value.
            self.head = Node(x, min(x, self.head.min_value), self.head)

    def pop(self):
        """
        Pops a patient's vital sign from the stack.
        """
        if self.head:
            self.head = self.head.next  # Remove the top node.

    def top(self):
        """
        Gets the top vital sign value.

        Returns:
            The top value, or None if the stack is empty.
        """
        return self.head.value if self.head else None

    def getMin(self):
        """
        Gets the minimum vital sign value.

        Returns:
            The minimum value, or None if the stack is empty.
        """
        return self.head.min_value if self.head else None

# 6. Blockchain Transaction Stack (Using Sorted List - O(1) getMin, O(logN) push/pop)
import bisect

class MinStackBlockchain:
    """
    Implements a Min Stack for tracking blockchain transactions.  This can be used to
    efficiently retrieve the minimum transaction amount.  A sorted list is used to maintain
    the minimum, providing O(1) getMin() but O(logN) push() and pop() operations. This is efficient
    for applications that require frequent minimum retrieval.
    """
    def __init__(self):
        """
        Initializes the MinStackBlockchain object.
        stack:  The main stack to store transaction amounts.
        sorted_list: A sorted list to store transaction amounts for efficient minimum retrieval.
        """
        self.stack = []
        self.sorted_list = []

    def push(self, x: int):
        """
        Pushes a transaction amount onto the stack.

        Args:
            x: The transaction amount.
        """
        self.stack.append(x)
        bisect.insort(self.sorted_list, x)  # Insert into sorted list (O(logN)).

    def pop(self):
        """
        Pops a transaction amount from the stack.
        """
        if self.stack:
            x = self.stack.pop()
            self.sorted_list.remove(x)  # Remove from sorted list (O(N) in worst case, closer to O(logN) on average).

    def top(self):
        """
        Gets the top transaction amount.

        Returns:
            The top amount, or None if the stack is empty.
        """
        return self.stack[-1] if self.stack else None

    def getMin(self):
        """
        Gets the minimum transaction amount.

        Returns:
            The minimum amount, or None if the stack is empty.
        """
        return self.sorted_list[0] if self.sorted_list else None  # The first element is always the minimum.

# Test Cases
stacks = [MinStackTrading(), MinStackBanking(), MinStackTraffic(), MinStackIoT(), MinStackHealthcare(), MinStackBlockchain()]

for i, stack in enumerate(stacks):
    print(f"\nTesting Approach {i + 1}:")
    stack.push(15)
    stack.push(8)
    stack.push(25)
    stack.push(3)
    print(f"Top Element: {stack.top()}")
    print(f"Minimum Element: {stack.getMin()}")
    stack.pop()
    print(f"Minimum after one pop: {stack.getMin()}")
