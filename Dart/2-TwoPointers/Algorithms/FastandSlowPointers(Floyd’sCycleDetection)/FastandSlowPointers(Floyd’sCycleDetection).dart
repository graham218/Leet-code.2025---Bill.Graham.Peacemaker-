class ListNode {
  int value;
  ListNode? next;
  ListNode(this.value, [this.next]);
}

// Approach 1: Floyd’s Cycle Detection Algorithm (Fast and Slow Pointers)
bool hasCycleFloyd(ListNode? head) {
  ListNode? slow = head, fast = head;
  while (fast != null && fast.next != null) {
    slow = slow?.next;
    fast = fast.next?.next;
    if (slow == fast) return true;
  }
  return false;
}

// Approach 2: Hash Set (Detecting visited nodes)
bool hasCycleSet(ListNode? head) {
  Set<ListNode> visited = {};
  while (head != null) {
    if (visited.contains(head)) return true;
    visited.add(head);
    head = head.next;
  }
  return false;
}

// Approach 3: Modifying Node Structure (Marking nodes)
bool hasCycleMarking(ListNode? head) {
  while (head != null) {
    if (head.value == -999999) return true;
    head.value = -999999; // Mark the node
    head = head.next;
  }
  return false;
}

// Approach 4: Using Length Calculation
bool hasCycleLength(ListNode? head) {
  ListNode? slow = head, fast = head;
  while (fast != null && fast.next != null) {
    slow = slow?.next;
    fast = fast.next?.next;
    if (slow == fast) {
      int cycleLength = 1;
      ListNode? temp = slow?.next;
      while (temp != slow) {
        cycleLength++;
        temp = temp?.next;
      }
      return cycleLength > 0;
    }
  }
  return false;
}

// Approach 5: Recursive Detection with Set
bool hasCycleRecursive(ListNode? head, {Set<ListNode> visited = const {}}) {
  if (head == null) return false;
  if (visited.contains(head)) return true;
  return hasCycleRecursive(head.next, visited: {...visited, head});
}

// Main function to test the implementations
void main() {
  // Creating a cycle in a linked list for testing
  ListNode node1 = ListNode(1);
  ListNode node2 = ListNode(2);
  ListNode node3 = ListNode(3);
  ListNode node4 = ListNode(4);
  node1.next = node2;
  node2.next = node3;
  node3.next = node4;
  node4.next = node2; // Creating a cycle

  print("Floyd's Cycle Detection: \${hasCycleFloyd(node1)}");
  print("Hash Set Detection: \${hasCycleSet(node1)}");
  print("Node Marking Detection: \${hasCycleMarking(node1)}");
  print("Length Calculation Detection: \${hasCycleLength(node1)}");
  print("Recursive Detection: \${hasCycleRecursive(node1)}");
}
