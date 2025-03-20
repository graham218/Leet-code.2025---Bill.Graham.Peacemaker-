import 'dart:collection';

class ListNode {
  int value;
  ListNode? next;

  ListNode(this.value, [this.next]); // Constructor for ListNode
}

void main() {
  // Example usage: Create a linked list with a cycle
  ListNode node1 = ListNode(1);
  ListNode node2 = ListNode(2);
  ListNode node3 = ListNode(3);
  ListNode node4 = ListNode(4);
  node1.next = node2;
  node2.next = node3;
  node3.next = node4;
  node4.next = node2; // Creating a cycle: node4 points back to node2

  // Test and print results for each cycle detection method
  print("Floyd's Cycle Detection: ${hasCycleFloyd(node1)}");
  print("HashSet Cycle Detection: ${hasCycleHashSet(node1)}");
  print("Modify Node Cycle Detection: ${hasCycleModifyNode(node1)}");
  print("Incremental Speed Cycle Detection: ${hasCycleIncremental(node1)}");
  visitedNodes.clear(); // Reset visitedNodes for recursive test
  print("Recursive Cycle Detection: ${hasCycleRecursive(node1)}");

  // Test case for a linked list with no cycle
  ListNode node5 = ListNode(5);
  ListNode node6 = ListNode(6);
  ListNode node7 = ListNode(7);
  node5.next = node6;
  node6.next = node7;

  print("\nNo Cycle Tests:");
  print("Floyd's Cycle Detection: ${hasCycleFloyd(node5)}");
  print("HashSet Cycle Detection: ${hasCycleHashSet(node5)}");
  print("Modify Node Cycle Detection: ${hasCycleModifyNode(node5)}");
  print("Incremental Speed Cycle Detection: ${hasCycleIncremental(node5)}");
  visitedNodes.clear(); // Reset visitedNodes for recursive test
  print("Recursive Cycle Detection: ${hasCycleRecursive(node5)}");
}

// Approach 1: Floyd’s Cycle Detection (Tortoise and Hare)
// Uses two pointers, slow and fast, moving at different speeds.
// If a cycle exists, the fast pointer will eventually catch up to the slow pointer.
bool hasCycleFloyd(ListNode? head) {
  if (head == null) return false; // Empty list has no cycle
  ListNode? slow = head;
  ListNode? fast = head;

  while (fast != null && fast.next != null) {
    slow = slow!.next; // Move slow pointer by 1 step
    fast = fast.next!.next; // Move fast pointer by 2 steps
    if (slow == fast) return true; // If they meet, cycle exists
  }
  return false; // No cycle found
}

// Approach 2: Using HashSet to store visited nodes
// Keeps track of visited nodes using a HashSet.
// If a node is visited again, a cycle exists.
bool hasCycleHashSet(ListNode? head) {
  HashSet<ListNode> visited = HashSet();
  while (head != null) {
    if (visited.contains(head)) return true; // Cycle detected
    visited.add(head); // Add node to visited set
    head = head.next; // Move to the next node
  }
  return false; // No cycle found
}

// Approach 3: Modifying Node Values (Destructive Method)
// Modifies the value of visited nodes to a unique marker value.
// If a node with the marker value is encountered, a cycle exists.
bool hasCycleModifyNode(ListNode? head) {
  final int marker = -1000000000; // Large negative number as a marker
  while (head != null) {
    if (head.value == marker) return true; // Cycle detected
    head.value = marker; // Mark node as visited
    head = head.next; // Move to the next node
  }
  return false; // No cycle found
}

// Approach 4: Two-Pointer Variation (Incremental Speed)
// Similar to Floyd's, but the fast pointer moves at incremental speeds (2x, 3x).
// This variation can be faster in some cases.
bool hasCycleIncremental(ListNode? head) {
  if (head == null) return false; // Empty list has no cycle
  ListNode? slow = head;
  ListNode? fast = head.next;

  while (fast != null && fast.next != null) {
    if (slow == fast) return true; // Cycle detected
    slow = slow!.next;
    fast = fast.next!.next; // Fast pointer moves at 2x speed.
    if(fast?.next != null){
      fast = fast!.next; //fast moves at 3x speed.
    }
  }
  return false; // No cycle found
}

// Approach 5: Recursive Cycle Detection
// Uses recursion and a HashSet to keep track of visited nodes.
// If a node is visited again, a cycle exists.
Set<ListNode> visitedNodes = {};
bool hasCycleRecursive(ListNode? head) {
  if (head == null) return false; // Base case: end of list
  if (visitedNodes.contains(head)) return true; // Cycle detected
  visitedNodes.add(head); // Add node to visited set
  return hasCycleRecursive(head.next); // Recursive call
}