import 'dart:collection';

class ListNode {
  int value;
  ListNode? next;

  ListNode(this.value, [this.next]);
}

void main() {
  // Example usage: Linked list with a cycle
  ListNode node1 = ListNode(1);
  ListNode node2 = ListNode(2);
  ListNode node3 = ListNode(3);
  ListNode node4 = ListNode(4);
  ListNode node5 = ListNode(5);

  node1.next = node2;
  node2.next = node3;
  node3.next = node4;
  node4.next = node5;
  node5.next = node3; // Creating a cycle: node5 points back to node3

  print("Cycle Detection: ${detectCycle(node1)}");
  print("Middle Node: ${findMiddle(node1)?.value}");
  print("Cycle Start Node: ${findCycleStart(node1)?.value}");
  print("Is Palindrome: ${isPalindrome(node1)}");
  print("3rd Node from End: ${findKthFromEnd(node1, 3)?.value}");

  // Test case for no cycle
  ListNode node6 = ListNode(6);
  ListNode node7 = ListNode(7);
  ListNode node8 = ListNode(8);
  node6.next = node7;
  node7.next = node8;

  print("\nNo Cycle Tests:");
  print("Cycle Detection: ${detectCycle(node6)}");
  print("Middle Node: ${findMiddle(node6)?.value}");
  print("Cycle Start Node: ${findCycleStart(node6)?.value}");
  print("Is Palindrome: ${isPalindrome(node6)}");
  print("2nd Node from End: ${findKthFromEnd(node6, 2)?.value}");

  // Test case for palindrome
  ListNode node9 = ListNode(1);
  ListNode node10 = ListNode(2);
  ListNode node11 = ListNode(1);
  node9.next = node10;
  node10.next = node11;

  print("\nPalindrome Test:");
  print("Is Palindrome: ${isPalindrome(node9)}");

  // Test case for Kth from end
  ListNode node12 = ListNode(1);

  print("\nKth from end test:");
  print("1st Node from End: ${findKthFromEnd(node12, 1)?.value}");
}

// Approach 1: Detecting a Cycle in a Linked List using Floyd’s Cycle Detection Algorithm
bool detectCycle(ListNode? head) {
  if (head == null) return false;
  ListNode? slow = head;
  ListNode? fast = head;

  while (fast != null && fast.next != null) {
    slow = slow!.next;
    fast = fast.next!.next;
    if (slow == fast) return true;
  }
  return false;
}

// Approach 2: Finding the Middle of a Linked List
ListNode? findMiddle(ListNode? head) {
  if (head == null) return null;
  ListNode? slow = head;
  ListNode? fast = head;

  while (fast != null && fast.next != null) {
    slow = slow!.next;
    fast = fast.next!.next;
  }
  return slow;
}

// Approach 3: Finding the Start of a Cycle
ListNode? findCycleStart(ListNode? head) {
  if (head == null) return null;
  ListNode? slow = head;
  ListNode? fast = head;
  bool cycleExists = false;

  while (fast != null && fast.next != null) {
    slow = slow!.next;
    fast = fast.next!.next;
    if (slow == fast) {
      cycleExists = true;
      break;
    }
  }

  if (!cycleExists) return null;

  slow = head;
  while (slow != fast) {
    slow = slow!.next;
    fast = fast!.next;
  }
  return slow;
}

// Approach 4: Checking if a Linked List is a Palindrome using Fast and Slow Pointers
bool isPalindrome(ListNode? head) {
  if (head == null || head.next == null) return true;
  ListNode? slow = head, fast = head;
  List<int> stack = [];

  while (fast != null && fast.next != null) {
    stack.add(slow!.value);
    slow = slow.next;
    fast = fast.next!.next;
  }

  if (fast != null) slow = slow!.next;

  while (slow != null) {
    if (stack.isEmpty || stack.removeLast() != slow.value) return false;
    slow = slow.next;
  }
  return true;
}

// Approach 5: Finding the Kth Node from the End
ListNode? findKthFromEnd(ListNode? head, int k) {
  if (head == null || k <= 0) return null;
  ListNode? slow = head, fast = head;

  // Move fast pointer k steps ahead
  for (int i = 0; i < k; i++) {
    if (fast == null) return null; // If k is greater than the length of the list
    fast = fast.next;
  }

  // Move both pointers until fast reaches the end
  while (fast != null) {
    slow = slow!.next;
    fast = fast.next;
  }
  return slow;
}