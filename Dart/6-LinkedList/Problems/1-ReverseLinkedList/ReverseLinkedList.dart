void main() {
  // Create a sample linked list: 1 -> 2 -> 3 -> 4 -> 5
  ListNode? head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))));

  // Print the original linked list
  print("Original List: ");
  printList(head);

  // Reverse the list using the iterative approach
  head = reverseListIterative(head);
  print("\nReversed List (Iterative): ");
  printList(head);

  // Reverse the list back to its original order using the recursive approach
  head = reverseListRecursive(head);
  print("\nReversed List (Recursive): ");
  printList(head);

  // Reverse the list using a stack
  head = reverseListUsingStack(head);
  print("\nReversed List (Stack): ");
  printList(head);

  // Reverse the list by changing values (not recommended)
  head = reverseByChangingValues(head);
  print("\nReversed List (Changing Values): ");
  printList(head);

  // Reverse the list using two-pointer recursive approach
  head = reverseListTwoPointer(head);
  print("\nReversed List (Two-Pointer Recursive): ");
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

// Approach 1: Iterative Approach
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

// Approach 2: Recursive Approach
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

// Approach 3: Using Stack (Extra Space)
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

// Approach 4: Reversing by Changing Values (Not Recommended)
ListNode? reverseByChangingValues(ListNode? head) {
  if (head == null) return null;
  List<int> values = []; // Create a list to store node values
  ListNode? temp = head;

  // Store the values of the nodes in the list
  while (temp != null) {
    values.add(temp.val);
    temp = temp.next;
  }

  // Update the values of the nodes in reverse order
  temp = head;
  for (int i = values.length - 1; i >= 0; i--) {
    temp!.val = values[i];
    temp = temp.next;
  }

  return head;
}

// Approach 5: Two-Pointer Recursive
ListNode? reverseListTwoPointer(ListNode? head) {
  // Call the helper function to perform the recursive reversal
  return _reverse(null, head);
}

// Helper function for the two-pointer recursive approach
ListNode? _reverse(ListNode? prev, ListNode? current) {
  // Base case: if the current node is null, return the previous node
  if (current == null) return prev;

  // Store the next node
  ListNode? nextNode = current.next;

  // Reverse the pointer of the current node
  current.next = prev;

  // Recursively reverse the rest of the list
  return _reverse(current, nextNode);
}