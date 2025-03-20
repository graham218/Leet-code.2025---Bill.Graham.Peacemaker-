import 'dart:collection';

void main() {
  // Create a sample linked list: 1 -> 2 -> 3 -> 4 -> 5
  ListNode? head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))));

  // Print the original linked list
  print("Original List:");
  printList(head);

  // Reverse the list using the iterative approach
  head = reverseListIterative(head);
  print("\nReversed List (Iterative):");
  printList(head);

  // Reverse the list back to its original order using the recursive approach
  head = reverseListRecursive(head);
  print("\nReversed List (Recursive):");
  printList(head);

  // Reverse the list using a stack
  head = reverseListUsingStack(head);
  print("\nReversed List (Stack):");
  printList(head);

  // Reverse the list using a deque
  head = reverseListWithDeque(head);
  print("\nReversed List (Deque):");
  printList(head);

  // Reverse the list in place (using node swapping)
  head = reverseListInPlace(head);
  print("\nReversed List (In-Place Swapping):");
  printList(head);

  // Reverse the list using a functional programming style
  head = reverseListFunctional(head);
  print("\nReversed List (Functional Programming Style):");
  printList(head);
}

class ListNode {
  int val; // Value of the node
  ListNode? next; // Pointer to the next node
  ListNode(this.val, [this.next]); // Constructor to create a node
}

// Function to print the linked list
void printList(ListNode? head) {
  while (head != null) {
    print(head.val); // Print the node's value
    head = head.next; // Move to the next node
  }
}

// Approach 1: Iterative Approach (Best for Performance and Space Optimization)
ListNode? reverseListIterative(ListNode? head) {
  ListNode? prev = null; // Initialize the previous node to null
  ListNode? current = head; // Initialize the current node to the head
  while (current != null) {
    ListNode? nextNode = current.next; // Store the next node
    current.next = prev; // Reverse the pointer of the current node
    prev = current; // Move the previous pointer to the current node
    current = nextNode; // Move the current pointer to the next node
  }
  return prev; // Return the new head of the reversed list
}

// Approach 2: Recursive Approach (Elegant, but Uses More Stack Space)
ListNode? reverseListRecursive(ListNode? head) {
  // Base case: if the list is empty or has only one node, return the head
  if (head == null || head.next == null) return head;

  // Recursively reverse the rest of the list
  ListNode? newHead = reverseListRecursive(head.next);

  // Reverse the pointer of the current node
  head.next!.next = head;
  head.next = null;

  // Return the new head of the reversed list
  return newHead;
}

// Approach 3: Using Stack (Extra Space but Simple Implementation)
ListNode? reverseListUsingStack(ListNode? head) {
  if (head == null) return null;
  List<ListNode> stack = []; // Create a stack to store nodes

  // Push all nodes onto the stack
  while (head != null) {
    stack.add(head);
    head = head.next;
  }

  // Pop nodes from the stack and create the reversed list
  ListNode? newHead = stack.removeLast();
  ListNode? current = newHead;
  while (stack.isNotEmpty) {
    current!.next = stack.removeLast();
    current = current.next;
  }

  // Set the next pointer of the last node to null
  current!.next = null;

  return newHead;
}

// Approach 4: Using Double-ended Queue (Deque)
ListNode? reverseListWithDeque(ListNode? head) {
  if (head == null) return null;
  Queue<ListNode> deque = Queue<ListNode>(); // Create a deque to store nodes

  // Add nodes to the front of the deque
  while (head != null) {
    deque.addFirst(head); // Add to the front for reverse order
    head = head.next;
  }

  // Pop nodes from the front of the deque and create the reversed list
  ListNode? newHead = deque.removeFirst();
  ListNode? current = newHead;
  while (deque.isNotEmpty) {
    current!.next = deque.removeFirst();
    current = current.next;
  }

  // Set the next pointer of the last node to null
  current!.next = null;

  return newHead;
}

// Approach 5: In-Place Swapping (Using Node Swapping Instead of Re-linking)
ListNode? reverseListInPlace(ListNode? head) {
  // This approach is identical to the iterative approach, because in a singly linked list, reversing is done by relinking, not value swapping.
  // The label in-place swapping is a bit misleading in this context.
  ListNode? prev = null;
  ListNode? current = head;
  while (current != null) {
    ListNode? nextNode = current.next;
    current.next = prev;
    prev = current;
    current = nextNode;
  }
  return prev;
}

// Approach 6: Functional Programming Style (Using a Helper Function)
ListNode? reverseListFunctional(ListNode? head) {
  // Call the helper function to perform the recursive reversal
  return _reverseHelper(null, head);
}

ListNode? _reverseHelper(ListNode? prev, ListNode? current) {
  // Base case: if the current node is null, return the previous node
  if (current == null) return prev;

  // Recursively reverse the rest of the list
  // current.next?..next = prev; is a null safe cascade, and reverses the current Nodes next value.
  return _reverseHelper(current, current.next?..next = prev);
}