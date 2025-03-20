import 'dart:collection';

class ListNode {
  int val;
  ListNode? next;
  ListNode(this.val, [this.next]);
}

void main() {
  // Creating a linked list with a cycle
  ListNode head = ListNode(3);
  head.next = ListNode(2);
  head.next!.next = ListNode(0);
  head.next!.next!.next = ListNode(-4, head.next); // Cycle here

  print("Detect Cycle (Floyd's Algorithm): ${hasCycleFloyd(head)}");
  print("Detect Cycle (HashSet Storage): ${hasCycleHashSet(head)}");
  print("Detect Cycle (Two-Pointer Optimization): ${hasCycleTwoPointer(head)}");
  print("Detect Cycle (Node Marking): ${hasCycleMarking(head)}");
  print("Detect Cycle (Cycle Length Calculation): ${hasCycleLength(head)}");
  print("Detect Cycle (Reverse Linked List Technique): ${hasCycleReverse(head)}");
}

// Approach 1: Floyd’s Cycle Detection Algorithm (Tortoise and Hare)
// Explanation:
// - Uses two pointers, slow and fast.
// - Slow moves one step at a time, fast moves two steps.
// - If there's a cycle, the fast pointer will eventually catch up to the slow pointer.
// - If there's no cycle, the fast pointer will reach the end of the list (null).
bool hasCycleFloyd(ListNode? head) {
  ListNode? slow = head, fast = head;
  while (fast != null && fast.next != null) {
    slow = slow?.next; // Slow pointer moves one step
    fast = fast.next?.next; // Fast pointer moves two steps
    if (slow == fast) return true; // Cycle detected if pointers meet
  }
  return false; // No cycle found
}

// Approach 2: Using HashSet to Store Visited Nodes
// Explanation:
// - Uses a HashSet to store visited nodes.
// - Iterates through the list, adding each node to the set.
// - If a node is already in the set, it means a cycle is present.
bool hasCycleHashSet(ListNode? head) {
  HashSet<ListNode> visited = HashSet<ListNode>();
  while (head != null) {
    if (visited.contains(head)) return true; // Cycle detected if node is already visited
    visited.add(head); // Add node to the visited set
    head = head.next; // Move to the next node
  }
  return false; // No cycle found
}

// Approach 3: Two-Pointer Optimization (Fast-Slow Pointers)
// Explanation:
// - Similar to Floyd's Algorithm, but initializes fast pointer to head.next.
// - This avoids the initial check of slow == fast when both are at head.
// - Otherwise, the logic is the same: slow moves one step, fast moves two steps.
bool hasCycleTwoPointer(ListNode? head) {
  if (head == null || head.next == null) return false; // No cycle if list is empty or has only one node
  ListNode? slow = head, fast = head.next; // Initialize fast pointer to head.next
  while (fast != null && fast.next != null) {
    if (slow == fast) return true; // Cycle detected if pointers meet
    slow = slow?.next; // Slow pointer moves one step
    fast = fast.next?.next; // Fast pointer moves two steps
  }
  return false; // No cycle found
}

// Approach 4: Marking Nodes with a Special Value (Destructive Method)
// Explanation:
// - Modifies the linked list by marking visited nodes with a special value (999999 in this case).
// - If a node with the special value is encountered, it means a cycle is present.
// - This method modifies the original list, which might not be desirable in all cases.
bool hasCycleMarking(ListNode? head) {
  while (head != null) {
    if (head.val == 999999) return true; // Cycle detected if node is marked
    head.val = 999999; // Mark the node
    head = head.next; // Move to the next node
  }
  return false; // No cycle found
}

// Approach 5: Detect Cycle by Finding Cycle Length
// Explanation:
// - Uses Floyd's Algorithm to detect a cycle.
// - If a cycle is found, calculates the length of the cycle.
// - Starts from the meeting point of slow and fast pointers and counts the nodes until it returns to the meeting point.
bool hasCycleLength(ListNode? head) {
  ListNode? slow = head, fast = head;
  while (fast != null && fast.next != null) {
    slow = slow?.next; // Slow pointer moves one step
    fast = fast.next?.next; // Fast pointer moves two steps
    if (slow == fast) {
      int length = 1; // Initialize cycle length
      ListNode? temp = slow?.next; // Start from the next node of the meeting point
      while (temp != null && temp != slow) {
        length++; // Increment cycle length
        temp = temp.next; // Move to the next node
      }
      print("Cycle Length: $length"); // Print the cycle length
      return true; // Cycle found
    }
  }
  return false; // No cycle found
}

// Approach 6: Reversing the Linked List (If Cycle Exists, Head Remains Unchanged)
// Explanation:
// - Reverses the linked list.
// - If there's a cycle, the head of the original list will be encountered during reversal.
// - If there's no cycle, the reversal will complete without encountering the original head.
// - This method also modifies the linked list.
bool hasCycleReverse(ListNode? head) {
  ListNode? prev = null;
  ListNode? current = head;
  while (current != null) {
    ListNode? nextNode = current.next; // Store the next node
    current.next = prev; // Reverse the pointer
    prev = current; // Move prev to the current node
    current = nextNode; // Move current to the next node
    if (current == head) return true; // Cycle detected if the original head is encountered
  }
  return false; // No cycle found
}