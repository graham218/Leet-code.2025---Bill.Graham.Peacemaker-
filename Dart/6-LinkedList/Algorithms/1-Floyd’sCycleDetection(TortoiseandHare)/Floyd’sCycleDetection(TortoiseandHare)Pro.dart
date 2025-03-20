import 'dart:collection';

class ListNode {
  int value;
  ListNode? next;

  ListNode(this.value, [this.next]);
}

void main() {
  // Example usage: Detecting cycle in a linked list
  ListNode node1 = ListNode(1);
  ListNode node2 = ListNode(2);
  ListNode node3 = ListNode(3);
  ListNode node4 = ListNode(4);
  node1.next = node2;
  node2.next = node3;
  node3.next = node4;
  node4.next = node2; // Creating a cycle

  print("Floyd's Cycle Detection: ${hasCycleFloyd(node1)}");
  print("HashSet Cycle Detection: ${hasCycleHashSet(node1)}");
  print("Modify Node Cycle Detection: ${hasCycleModifyNode(node1)}");
  print("Incremental Speed Cycle Detection: ${hasCycleIncremental(node1)}");
  visitedNodes.clear(); // Reset visitedNodes for recursive test
  print("Recursive Cycle Detection: ${hasCycleRecursive(node1)}");
  print("Length Check Cycle Detection: ${hasCycleLengthCheck(node1)}");

  //Test case for no cycle
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
  visitedNodes.clear();
  print("Recursive Cycle Detection: ${hasCycleRecursive(node5)}");
  print("Length Check Cycle Detection: ${hasCycleLengthCheck(node5)}");

  // Real-world example
  List<ListNode> routers = [node1, node5]; // Example routers
  detectLoopInNetwork(routers);
}

// Approach 1: Floyd’s Cycle Detection (Tortoise and Hare Algorithm)
bool hasCycleFloyd(ListNode? head) {
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

// Approach 2: Using a HashSet to Store Visited Nodes
bool hasCycleHashSet(ListNode? head) {
  HashSet<ListNode> visited = HashSet();
  while (head != null) {
    if (visited.contains(head)) return true;
    visited.add(head);
    head = head.next;
  }
  return false;
}

// Approach 3: Modifying Node Values (Destructive Method)
bool hasCycleModifyNode(ListNode? head) {
  final int marker = -999999; // Using a named constant for clarity.
  while (head != null) {
    if (head.value == marker) return true; // Special marker for visited node
    head.value = marker;
    head = head.next;
  }
  return false;
}

// Approach 4: Two-Pointer Variation (Slow vs Fast with Different Speeds)
bool hasCycleIncremental(ListNode? head) {
  if (head == null) return false;
  ListNode? slow = head;
  ListNode? fast = head.next;

  while (fast != null && fast.next != null) {
    if (slow == fast) return true;
    slow = slow!.next;
    fast = fast.next!.next; // Fast pointer moves at 2x speed.
    if(fast?.next != null){
      fast = fast!.next; //fast pointer moves at 3x speed.
    }
  }
  return false;
}

// Approach 5: Recursive Cycle Detection
Set<ListNode> visitedNodes = {};
bool hasCycleRecursive(ListNode? head) {
  if (head == null) return false;
  if (visitedNodes.contains(head)) return true;
  visitedNodes.add(head);
  return hasCycleRecursive(head.next);
}

// Approach 6: Linked List Length with Reset Mechanism
bool hasCycleLengthCheck(ListNode? head) {
  int length = 0;
  while (head != null) {
    length++;
    if (length > 10000) return true; // Arbitrary high value to detect cycle
    head = head.next;
  }
  return false;
}

// Real-World Implementation: Network Packet Routing (Detecting Cycles in Packet Paths)
bool detectLoopInNetwork(List<ListNode> routers) {
  for (var router in routers) {
    if (hasCycleFloyd(router)) {
      print("Loop detected in network routing path!");
      return true;
    }
  }
  print("No loop detected in network routing path.");
  return false;
}