import 'dart:collection';

class ListNode {
  int val;
  ListNode? next;
  ListNode(this.val, [this.next]);
}

void main() {
  // Creating a linked list with a cycle: 3 -> 2 -> 0 -> -4 -> 2 (cycle back to 2)
  ListNode head = ListNode(3);
  head.next = ListNode(2);
  head.next!.next = ListNode(0);
  head.next!.next!.next = ListNode(-4, head.next); // Cycle here, -4 points back to 2

  // Testing different cycle detection algorithms
  print("Detect Cycle (Floyd's Cycle Detection): ${hasCycleFloyd(head)}");
  print("Detect Cycle (HashSet): ${hasCycleHashSet(head)}");
  print("Detect Cycle (Two-Pointer Optimization): ${hasCycleTwoPointer(head)}");
  print("Detect Cycle (Node Marking): ${hasCycleMarking(head)}");
  print("Detect Cycle (Length Calculation Approach): ${hasCycleLength(head)}");
}

// Approach 1: Floyd’s Cycle Detection (Tortoise and Hare Algorithm)
// Explanation:
// - Uses two pointers, 'slow' and 'fast'.
// - 'slow' moves one step at a time, 'fast' moves two steps.
// - If there's a cycle, 'fast' will eventually catch up to 'slow'.
// - If 'fast' reaches null, there's no cycle.
bool hasCycleFloyd(ListNode? head) {
  ListNode? slow = head, fast = head;
  while (fast != null && fast.next != null) {
    slow = slow?.next; // Move slow one step
    fast = fast.next?.next; // Move fast two steps
    if (slow == fast) return true; // Cycle detected
  }
  return false; // No cycle found
}

// Approach 2: Using HashSet to Store Visited Nodes
// Explanation:
// - Uses a HashSet to keep track of visited nodes.
// - If a node is visited again, it means there's a cycle.
// - Uses extra space for the HashSet.
bool hasCycleHashSet(ListNode? head) {
  HashSet<ListNode> visited = HashSet<ListNode>();
  while (head != null) {
    if (visited.contains(head)) return true; // Cycle detected
    visited.add(head); // Mark node as visited
    head = head.next;
  }
  return false; // No cycle found
}

// Approach 3: Two-Pointer Optimization (Check for nulls early)
// Explanation:
// - Similar to Floyd's algorithm, but checks for nulls at the beginning.
// - Slightly optimizes the code by preventing unnecessary null checks inside the loop.
bool hasCycleTwoPointer(ListNode? head) {
  if (head == null || head.next == null) return false; // Early null check
  ListNode? slow = head, fast = head.next; // fast starts one step ahead
  while (fast != null && fast.next != null) {
    if (slow == fast) return true; // Cycle detected
    slow = slow?.next;
    fast = fast.next?.next;
  }
  return false; // No cycle found
}

// Approach 4: Marking Nodes with a Special Value
// Explanation:
// - Modifies the 'val' of visited nodes to a special marker value (999999).
// - If a node with the marker value is encountered, it means there's a cycle.
// - Modifies the original linked list.
bool hasCycleMarking(ListNode? head) {
  while (head != null) {
    if (head.val == 999999) return true; // Cycle detected
    head.val = 999999; // Mark node as visited
    head = head.next;
  }
  return false; // No cycle found
}

// Approach 5: Detect Cycle by Finding Length of Cycle
// Explanation:
// - Uses Floyd's algorithm to detect the cycle.
// - If a cycle is detected, it calculates the length of the cycle.
// - Useful if you need to know the length of the cycle.
bool hasCycleLength(ListNode? head) {
  ListNode? slow = head, fast = head;
  while (fast != null && fast.next != null) {
    slow = slow?.next;
    fast = fast.next?.next;
    if (slow == fast) {
      // Cycle detected, calculate cycle length
      int length = 1;
      ListNode? temp = slow?.next;
      while (temp != null && temp != slow) {
        length++;
        temp = temp.next;
      }
      print("Cycle Length: $length"); // Print the cycle length
      return true;
    }
  }
  return false; // No cycle found
}