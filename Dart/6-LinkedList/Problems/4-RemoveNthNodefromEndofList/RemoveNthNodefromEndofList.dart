class ListNode {
  int val;
  ListNode? next;
  ListNode(this.val, [this.next]);
}

void main() {
  ListNode head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))));
  int n = 2; // Remove the 2nd node from the end

  print("Original List:");
  printList(head);

  print("\nAfter Removing $n-th Node (Two-Pass Method):");
  printList(removeNthFromEndTwoPass(copyList(head), n));

  print("\nAfter Removing $n-th Node (One-Pass Method with Two Pointers):");
  printList(removeNthFromEndOnePass(copyList(head), n));

  print("\nAfter Removing $n-th Node (Stack Method):");
  printList(removeNthFromEndStack(copyList(head), n));

  print("\nAfter Removing $n-th Node (Recursive Approach):");
  printList(removeNthFromEndRecursive(copyList(head), n));

  print("\nAfter Removing $n-th Node (Dummy Node Approach):");
  printList(removeNthFromEndDummy(copyList(head), n));
}

void printList(ListNode? head) {
  while (head != null) {
    print(head.val);
    head = head.next;
  }
}

// Function to create a deep copy of the linked list
ListNode? copyList(ListNode? head) {
  if (head == null) return null;
  return ListNode(head.val, copyList(head.next));
}

// Approach 1: Two-Pass Method (Find Length and Remove)
// Explanation:
// - First pass: Calculate the length of the linked list.
// - Second pass: Traverse the list to the (length - n - 1)-th node.
// - Remove the next node (which is the n-th node from the end).
ListNode? removeNthFromEndTwoPass(ListNode? head, int n) {
  int length = 0;
  ListNode? temp = head;
  while (temp != null) {
    length++;
    temp = temp.next;
  }
  if (length == n) return head?.next; // If n is equal to the length, remove the head
  temp = head;
  for (int i = 0; i < length - n - 1; i++) {
    temp = temp?.next;
  }
  temp?.next = temp?.next?.next; // Remove the n-th node from the end
  return head;
}

// Approach 2: One-Pass Method (Two Pointers)
// Explanation:
// - Uses two pointers, first and second, with a gap of n nodes between them.
// - Moves both pointers simultaneously until the first pointer reaches the end.
// - The second pointer will then be pointing to the node before the n-th node from the end.
// - Remove the next node.
ListNode? removeNthFromEndOnePass(ListNode? head, int n) {
  ListNode dummy = ListNode(0, head); // Create a dummy node to handle the case of removing the head
  ListNode? first = dummy, second = dummy;
  for (int i = 0; i <= n; i++) first = first?.next; // Move the first pointer n+1 steps ahead
  while (first != null) {
    first = first.next;
    second = second?.next; // Move both pointers simultaneously
  }
  second?.next = second?.next?.next; // Remove the n-th node from the end
  return dummy.next;
}

// Approach 3: Using a Stack
// Explanation:
// - Push all nodes onto a stack.
// - Pop n nodes from the stack.
// - The next node to be popped is the node before the one to be removed.
// - Update the next pointer of the node before.
ListNode? removeNthFromEndStack(ListNode? head, int n) {
  List<ListNode?> stack = [];
  ListNode? temp = head;
  while (temp != null) {
    stack.add(temp);
    temp = temp.next;
  }
  for (int i = 0; i < n; i++) {
    stack.removeLast(); // Pop n nodes
  }
  if (stack.isEmpty) return head?.next; // If stack is empty, remove the head
  ListNode? prev = stack.last;
  prev?.next = prev.next?.next; // Remove the n-th node from the end
  return head;
}

// Approach 4: Recursive Approach
// Explanation:
// - Uses a recursive helper function to traverse the list.
// - The helper function returns the index of the current node from the end.
// - When the index is n + 1, it means the next node is the one to be removed.
int helper(ListNode? head, int n) {
  if (head == null) return 0;
  int index = 1 + helper(head.next, n); // Recursive call to get the index from the end
  if (index == n + 1) head.next = head.next?.next; // Remove the n-th node from the end
  return index;
}

ListNode? removeNthFromEndRecursive(ListNode? head, int n) {
  int index = helper(head, n);
  return index == n ? head?.next : head; // If index is n, remove the head
}

// Approach 5: Using a Dummy Node (Cleaner Code)
// Explanation:
// - Same as the one-pass method with two pointers, but uses a dummy node to simplify the code.
// - The dummy node handles the case of removing the head of the list.
ListNode? removeNthFromEndDummy(ListNode? head, int n) {
  ListNode dummy = ListNode(0, head);
  ListNode? first = dummy, second = dummy;
  for (int i = 0; i <= n; i++) first = first?.next;
  while (first != null) {
    first = first.next;
    second = second?.next;
  }
  second?.next = second?.next?.next;
  return dummy.next;
}