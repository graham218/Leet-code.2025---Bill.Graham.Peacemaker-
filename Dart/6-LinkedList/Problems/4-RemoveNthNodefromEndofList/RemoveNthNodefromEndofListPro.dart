class ListNode {
  int val;
  ListNode? next;
  ListNode(this.val, [this.next]);
}

void main() {
  ListNode head = ListNode(100, ListNode(200, ListNode(300, ListNode(400, ListNode(500)))));
  int n = 2; // Remove the 2nd node from the end

  print("Original Linked List:");
  printList(head);

  print("\nAfter Removing $n-th Node (Two-Pass Method):");
  printList(removeNthFromEndTwoPass(copyList(head), n));

  print("\nAfter Removing $n-th Node (One-Pass with Two Pointers):");
  printList(removeNthFromEndOnePass(copyList(head), n));

  print("\nAfter Removing $n-th Node (Using Stack):");
  printList(removeNthFromEndStack(copyList(head), n));

  print("\nAfter Removing $n-th Node (Recursive Method):");
  printList(removeNthFromEndRecursive(copyList(head), n));

  print("\nAfter Removing $n-th Node (Dummy Node Approach):");
  printList(removeNthFromEndDummy(copyList(head), n));

  print("\nAfter Removing $n-th Node (Optimized Fast & Slow Pointer):");
  printList(removeNthFromEndFastSlow(copyList(head), n));
}

// Function to print the linked list
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

// Approach 1: Two-Pass Method (Find Length, Then Remove)
// Explanation:
// - First pass: Calculate the length of the linked list.
// - Second pass: Traverse to the (length - n - 1)-th node and remove the next node.
ListNode? removeNthFromEndTwoPass(ListNode? head, int n) {
  int length = 0;
  ListNode? temp = head;
  while (temp != null) {
    length++;
    temp = temp.next;
  }
  if (length == n) return head?.next; // If n == length, remove the head
  temp = head;
  for (int i = 0; i < length - n - 1; i++) {
    temp = temp?.next; // Traverse to the (length - n - 1)-th node
  }
  temp?.next = temp?.next?.next; // Remove the n-th node from the end
  return head;
}

// Approach 2: One-Pass Method (Two Pointers)
// Explanation:
// - Uses two pointers, 'first' and 'second', with a gap of 'n' nodes.
// - Moves 'first' 'n' nodes ahead, then moves both pointers until 'first' reaches the end.
// - 'second' will then be pointing to the node before the n-th node from the end.
ListNode? removeNthFromEndOnePass(ListNode? head, int n) {
  ListNode dummy = ListNode(0, head); // Dummy node to handle edge case of removing the head
  ListNode? first = dummy, second = dummy;
  for (int i = 0; i <= n; i++) first = first?.next; // Move 'first' 'n' nodes ahead
  while (first != null) {
    first = first.next;
    second = second?.next; // Move both pointers simultaneously
  }
  second?.next = second?.next?.next; // Remove the n-th node from the end
  return dummy.next;
}

// Approach 3: Using a Stack (Stores Nodes, Then Removes the Target)
// Explanation:
// - Push all nodes onto a stack.
// - Pop 'n' nodes from the stack.
// - The next node on the stack is the node before the one to be removed.
ListNode? removeNthFromEndStack(ListNode? head, int n) {
  List<ListNode?> stack = [];
  ListNode? temp = head;
  while (temp != null) {
    stack.add(temp);
    temp = temp.next;
  }
  for (int i = 0; i < n; i++) {
    stack.removeLast(); // Pop 'n' nodes
  }
  if (stack.isEmpty) return head?.next; // If stack is empty, remove the head
  ListNode? prev = stack.last;
  prev?.next = prev.next?.next; // Remove the n-th node from the end
  return head;
}

// Approach 4: Recursive Solution
// Explanation:
// - Recursive function returns the index from the end.
// - When the index is 'n + 1', remove the next node.
int helper(ListNode? head, int n) {
  if (head == null) return 0;
  int index = 1 + helper(head.next, n); // Recursive call
  if (index == n + 1) head.next = head.next?.next; // Remove the n-th node from the end
  return index;
}

ListNode? removeNthFromEndRecursive(ListNode? head, int n) {
  int index = helper(head, n);
  return index == n ? head?.next : head; // If index is 'n', remove the head
}

// Approach 5: Dummy Node Approach (Simplifies Edge Cases)
// Explanation:
// - Same as the one-pass method with two pointers, but uses a dummy node for cleaner code.
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

// Approach 6: Optimized Fast & Slow Pointer Method
// Explanation:
// - Uses 'fast' and 'slow' pointers.
// - Moves 'fast' 'n' nodes ahead.
// - If 'fast' becomes null, remove the head.
// - Moves both pointers until 'fast' reaches the end.
// - 'slow' will be pointing to the node before the one to be removed.
ListNode? removeNthFromEndFastSlow(ListNode? head, int n) {
  if (head == null) return null;
  ListNode? fast = head, slow = head, prev = null; //prev keeps track of the element prior to slow.
  for (int i = 0; i < n; i++) {
    fast = fast?.next; // Move 'fast' 'n' nodes ahead
  }
  if (fast == null) return head.next; // If 'fast' is null, remove the head
  while (fast?.next != null) {
    fast = fast?.next;
    prev = slow; //save slow into previous
    slow = slow?.next; // Move both pointers simultaneously
  }
  prev?.next = slow?.next; // Remove the n-th node from the end
  return head;
}