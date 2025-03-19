import 'dart:collection';

class ListNode {
  int value;
  ListNode? next;
  ListNode(this.value, [this.next]);
}

class LinkedList {
  ListNode? head;

  void append(int value) {
    if (head == null) {
      head = ListNode(value);
      return;
    }
    ListNode current = head!;
    while (current.next != null) {
      current = current.next!;
    }
    current.next = ListNode(value);
  }

  void createCycle(int position) {
    if (head == null) return;
    ListNode? cycleNode;
    ListNode? tail = head;
    int index = 0;
    while (tail!.next != null) {
      if (index == position) {
        cycleNode = tail;
      }
      tail = tail.next;
      index++;
    }
    tail.next = cycleNode;
  }
}

// Approach 1: Floyd’s Cycle Detection Algorithm (Fast and Slow Pointers)
bool detectCycleFloyd(ListNode? head) {
  ListNode? slow = head, fast = head;
  while (fast != null && fast.next != null) {
    slow = slow?.next;
    fast = fast.next?.next;
    if (slow == fast) return true;
  }
  return false;
}

// Approach 2: Hash Set-based Cycle Detection
bool detectCycleWithHashSet(ListNode? head) {
  HashSet<ListNode> visited = HashSet();
  while (head != null) {
    if (visited.contains(head)) return true;
    visited.add(head);
    head = head.next;
  }
  return false;
}

// Approach 3: Cycle detection with visited set.
bool detectCycleWithVisitedSet(ListNode? head) {
  HashSet<ListNode> visited = HashSet();
  while (head != null) {
    if (visited.contains(head)) return true;
    visited.add(head);
    head = head.next;
  }
  return false;
}

// Approach 4: Cycle Detection with a Counter (Cycle Length Calculation)
bool detectCycleWithCounter(ListNode? head) {
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
      print("Cycle Length: $cycleLength");
      return true;
    }
  }
  return false;
}

// Approach 5: Recursive Cycle Detection with Set
bool detectCycleRecursive(ListNode? head, {Set<ListNode> visited = const {}}) {
  if (head == null) return false;
  if (visited.contains(head)) return true;
  return detectCycleRecursive(head.next, visited: {...visited, head});
}

// Main function to test all implementations
void main() {
  LinkedList list = LinkedList();
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.createCycle(1);

  print("Floyd's Cycle Detection: ${detectCycleFloyd(list.head)}");
  print("Hash Set Cycle Detection: ${detectCycleWithHashSet(list.head)}");
  print("Visited Set Cycle Detection: ${detectCycleWithVisitedSet(list.head)}");
  print("Cycle Length Detection: ${detectCycleWithCounter(list.head)}");
  print("Recursive Cycle Detection: ${detectCycleRecursive(list.head)}");
}