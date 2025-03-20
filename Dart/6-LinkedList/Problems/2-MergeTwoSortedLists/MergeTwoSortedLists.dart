import 'package:collection/collection.dart';

class ListNode {
  int val;
  ListNode? next;
  ListNode(this.val, [this.next]);
}

void main() {
  // Create two sample sorted linked lists
  ListNode? l1 = ListNode(1, ListNode(3, ListNode(5)));
  ListNode? l2 = ListNode(2, ListNode(4, ListNode(6)));

  // Print the merged lists using different approaches
  print("Merged List (Iterative):");
  printList(mergeTwoListsIterative(copyList(l1), copyList(l2)));

  print("\nMerged List (Recursive):");
  printList(mergeTwoListsRecursive(copyList(l1), copyList(l2)));

  print("\nMerged List (Using List Sorting):");
  printList(mergeTwoListsUsingList(copyList(l1), copyList(l2)));

  print("\nMerged List (Using Priority Queue):");
  printList(mergeTwoListsWithPriorityQueue(copyList(l1), copyList(l2)));

  print("\nMerged List (In-Place Merging):");
  printList(mergeTwoListsInPlace(copyList(l1), copyList(l2)));
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

// Approach 1: Iterative Merge
ListNode? mergeTwoListsIterative(ListNode? l1, ListNode? l2) {
  // Create a dummy node to simplify the merging process
  ListNode dummy = ListNode(0);
  // Initialize a tail pointer to the dummy node
  ListNode tail = dummy;

  // Iterate while both lists have nodes
  while (l1 != null && l2 != null) {
    // Compare the values of the current nodes
    if (l1.val < l2.val) {
      // If l1's value is smaller, append l1 to the merged list
      tail.next = l1;
      l1 = l1.next;
    } else {
      // Otherwise, append l2 to the merged list
      tail.next = l2;
      l2 = l2.next;
    }
    // Move the tail pointer to the newly added node
    tail = tail.next!;
  }
  // Append the remaining nodes from either list (if any)
  tail.next = l1 ?? l2;
  // Return the head of the merged list (skipping the dummy node)
  return dummy.next;
}

// Approach 2: Recursive Merge
ListNode? mergeTwoListsRecursive(ListNode? l1, ListNode? l2) {
  // Base case: if either list is empty, return the other list
  if (l1 == null) return l2;
  if (l2 == null) return l1;

  // Recursively merge the lists
  if (l1.val < l2.val) {
    // If l1's value is smaller, recursively merge l1.next with l2
    l1.next = mergeTwoListsRecursive(l1.next, l2);
    return l1;
  } else {
    // Otherwise, recursively merge l1 with l2.next
    l2.next = mergeTwoListsRecursive(l1, l2.next);
    return l2;
  }
}

// Approach 3: Using a List
ListNode? mergeTwoListsUsingList(ListNode? l1, ListNode? l2) {
  // Create a list to store the values of both lists
  List<int> values = [];
  // Add values from l1 to the list
  while (l1 != null) {
    values.add(l1.val);
    l1 = l1.next;
  }
  // Add values from l2 to the list
  while (l2 != null) {
    values.add(l2.val);
    l2 = l2.next;
  }
  // Sort the list of values
  values.sort();

  // Create a new linked list from the sorted values
  ListNode? dummy = ListNode(0);
  ListNode? current = dummy;
  for (int val in values) {
    current!.next = ListNode(val);
    current = current.next;
  }
  // Return the head of the new linked list
  return dummy.next;
}

// Approach 4: Using a Priority Queue
ListNode? mergeTwoListsWithPriorityQueue(ListNode? l1, ListNode? l2) {
  // Create a priority queue to store the nodes
  HeapPriorityQueue<ListNode> pq = HeapPriorityQueue((a, b) => a.val.compareTo(b.val));
  // Add nodes from l1 to the priority queue
  if (l1 != null) pq.add(l1);
  // Add nodes from l2 to the priority queue
  if (l2 != null) pq.add(l2);

  // Create a dummy node and a current pointer
  ListNode? dummy = ListNode(0);
  ListNode? current = dummy;

  // Extract nodes from the priority queue and create the merged list
  while (pq.isNotEmpty) {
    ListNode node = pq.removeFirst();
    current!.next = node;
    current = current.next;
    // Add the next node of the extracted node to the priority queue (if it exists)
    if (node.next != null) pq.add(node.next!);
  }
  // Return the head of the merged list
  return dummy.next;
}

// Approach 5: In-Place Merging
ListNode? mergeTwoListsInPlace(ListNode? l1, ListNode? l2) {
  // Handle base cases
  if (l1 == null) return l2;
  if (l2 == null) return l1;

  // Ensure l1 starts with the smaller value
  if (l1.val > l2.val) {
    ListNode? temp = l1;
    l1 = l2;
    l2 = temp;
  }

  // Store the head of the merged list
  ListNode? head = l1;
  // Iterate while both lists have nodes
  while (l1 != null && l2 != null) {
    ListNode? temp = null;
    // Move l1 until its value is greater than l2's value
    while (l1 != null && l1.val <= l2.val) {
      temp = l1;
      l1 = l1.next;
    }
    // Insert l2 into the merged list
    temp!.next = l2;

    // Swap l1 and l2 to continue merging
    ListNode? swap = l1;
    l1 = l2;
    l2 = swap;
  }
  // Return the head of the merged list
  return head;
}