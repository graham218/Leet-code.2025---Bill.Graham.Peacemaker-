class ListNode {
  int value;
  ListNode? next;
  ListNode(this.value, [this.next]); // Constructor for ListNode
}

void main() {
  // Example Usage: Linked list with a cycle
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

  // Test and print results for each linked list operation
  print("Cycle Detection: ${detectCycle(node1)}"); // Detect cycle
  print("Middle Node: ${findMiddle(node1)?.value}"); // Find middle node
  print("Cycle Start Node: ${findCycleStart(node1)?.value}"); // Find cycle start
  print("Kth Node from End (3): ${findKthFromEnd(node1, 3)?.value}"); // Find 3rd from end
  print("Is Palindrome: ${isPalindrome(node1)}"); // Check if palindrome

  // No Cycle Test: Linked list without a cycle
  ListNode node6 = ListNode(6);
  ListNode node7 = ListNode(7);
  ListNode node8 = ListNode(8);
  node6.next = node7;
  node7.next = node8;

  print("\nNo Cycle Tests:");
  print("Cycle Detection: ${detectCycle(node6)}");
  print("Middle Node: ${findMiddle(node6)?.value}");
  print("Cycle Start Node: ${findCycleStart(node6)?.value}");
  print("Kth Node from End (2): ${findKthFromEnd(node6, 2)?.value}");
  print("Is Palindrome: ${isPalindrome(node6)}");

  // Palindrome Test: Linked list that is a palindrome
  ListNode node9 = ListNode(1);
  ListNode node10 = ListNode(2);
  ListNode node11 = ListNode(1);
  node9.next = node10;
  node10.next = node11;

  print("\nPalindrome Test:");
  print("Is Palindrome: ${isPalindrome(node9)}");

  // Kth from end test: Linked list with a single node
  ListNode node12 = ListNode(1);

  print("\nKth from end test:");
  print("1st Node from End: ${findKthFromEnd(node12, 1)?.value}");

  // Real-World Implementation Test: Network loop detection
  List<ListNode> routers = [node1, node6]; // List of routers (linked lists)
  detectNetworkLoop(routers); // Detect loops in network paths
}

// Approach 1: Detecting a Cycle using Floyd’s Algorithm (Tortoise and Hare)
// Uses two pointers, slow and fast, to detect a cycle.
// If a cycle exists, the fast pointer will eventually catch up to the slow pointer.
bool detectCycle(ListNode? head) {
  if (head == null) return false; // Empty list has no cycle
  ListNode? slow = head;
  ListNode? fast = head;

  while (fast != null && fast.next != null) {
    slow = slow!.next; // Move slow pointer one step
    fast = fast.next!.next; // Move fast pointer two steps
    if (slow == fast) return true; // Cycle detected
  }
  return false; // No cycle found
}

// Approach 2: Finding the Middle of a Linked List
// Uses two pointers, slow and fast, to find the middle node.
// The slow pointer moves one step, and the fast pointer moves two steps.
// When the fast pointer reaches the end, the slow pointer will be at the middle.
ListNode? findMiddle(ListNode? head) {
  if (head == null) return null; // Empty list has no middle
  ListNode? slow = head;
  ListNode? fast = head;

  while (fast != null && fast.next != null) {
    slow = slow!.next;
    fast = fast.next!.next;
  }
  return slow; // Middle node
}

// Approach 3: Detecting Start of Cycle
// Uses Floyd's algorithm to detect a cycle and then finds the start of the cycle.
// After detecting a cycle, moves one pointer to the head and moves both pointers one step at a time.
// The point where they meet is the start of the cycle.
ListNode? findCycleStart(ListNode? head) {
  if (head == null) return null; // Empty list has no cycle
  ListNode? slow = head;
  ListNode? fast = head;
  bool hasCycle = false;

  while (fast != null && fast.next != null) {
    slow = slow!.next;
    fast = fast.next!.next;
    if (slow == fast) {
      hasCycle = true;
      break;
    }
  }

  if (!hasCycle) return null; // No cycle found

  slow = head;
  while (slow != fast) {
    slow = slow!.next;
    fast = fast!.next;
  }
  return slow; // Start of cycle
}

// Approach 4: Finding Kth Node from End
// Uses two pointers, slow and fast, to find the kth node from the end.
// Moves the fast pointer k steps ahead and then moves both pointers together.
// When the fast pointer reaches the end, the slow pointer will be at the kth node from the end.
ListNode? findKthFromEnd(ListNode? head, int k) {
  if (head == null) return null; // Empty list
  ListNode? slow = head;
  ListNode? fast = head;

  for (int i = 0; i < k; i++) {
    if (fast == null) return null; // k is greater than list length
    fast = fast.next;
  }

  while (fast != null) {
    slow = slow!.next;
    fast = fast.next;
  }
  return slow; // Kth node from end
}

// Approach 5: Detecting if a Linked List is a Palindrome
// Uses fast and slow pointers to find the middle of the list.
// Uses a stack to store the first half of the list and then compares it with the second half.
bool isPalindrome(ListNode? head) {
  if (head == null || head.next == null) return true; // Empty or single node list is palindrome

  ListNode? slow = head;
  ListNode? fast = head;
  List<int> stack = []; // Using List as a stack

  while (fast != null && fast.next != null) {
    stack.add(slow!.value);
    slow = slow.next;
    fast = fast.next!.next;
  }

  if (fast != null) slow = slow!.next; // Odd number of nodes

  while (slow != null) {
    if (stack.removeLast() != slow.value) return false;
    slow = slow.next;
  }
  return true;
}

// Approach 6: Real-World Implementation - Packet Routing Loop Detection
// Checks for loops in network routing paths represented as linked lists.
// Uses the detectCycle function to check for loops in each router's path.
bool detectNetworkLoop(List<ListNode> routers) {
  for (var router in routers) {
    if (detectCycle(router)) {
      print("Network loop detected!");
      return true;
    }
  }
  print("No network loops detected.");
  return false;
}