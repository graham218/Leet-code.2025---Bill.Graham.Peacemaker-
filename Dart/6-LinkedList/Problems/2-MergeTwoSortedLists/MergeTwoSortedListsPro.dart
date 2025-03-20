import 'package:collection/collection.dart';

// Definition of a singly-linked list node.
class ListNode {
  int val;
  ListNode? next;
  ListNode(this.val, [this.next]);
}

void main() {
  // Create two sample sorted linked lists for merging.
  ListNode? l1 = ListNode(1, ListNode(3, ListNode(5)));
  ListNode? l2 = ListNode(2, ListNode(4, ListNode(6)));

  // Print the merged lists using different approaches, making sure to copy the lists each time.
  print("Merged List (Iterative):");
  printList(mergeListsIterative(copyList(l1), copyList(l2)));

  print("\nMerged List (Recursive):");
  printList(mergeListsRecursive(copyList(l1), copyList(l2)));

  print("\nMerged List (Using Min Heap):");
  printList(mergeListsMinHeap(copyList(l1), copyList(l2)));

  print("\nMerged List (Using Merge Sort Technique):");
  printList(mergeListsMergeSort(copyList(l1), copyList(l2)));

  print("\nMerged List (Using Streams - Real-World Use Case):");
  mergeListsStream(copyList(l1), copyList(l2)).listen((val) => print(val));

  // Example of Merging Multiple Lists:
  ListNode? l3 = ListNode(1, ListNode(4, ListNode(7)));
  ListNode? l4 = ListNode(2, ListNode(5, ListNode(8)));
  ListNode? l5 = ListNode(3, ListNode(6, ListNode(9)));

  List<ListNode?> listOfLists = [copyList(l3), copyList(l4), copyList(l5)];
  print("\nMerged List (Multiple Lists using Min Heap):");
  printList(mergeKLists(listOfLists));
}

// Function to print the linked list.
void printList(ListNode? head) {
  while (head != null) {
    print(head.val);
    head = head.next;
  }
}

// Function to create a deep copy of the linked list.
ListNode? copyList(ListNode? head) {
  if (head == null) return null;
  return ListNode(head.val, copyList(head.next));
}

// Iterative Approach for merging two sorted lists.
ListNode? mergeListsIterative(ListNode? l1, ListNode? l2) {
  // Create a dummy node to simplify the merging process.
  ListNode dummy = ListNode(0);
  // Initialize a tail pointer to the dummy node.
  ListNode tail = dummy;

  // Iterate while both lists have nodes.
  while (l1 != null && l2 != null) {
    // Compare the values of the current nodes.
    if (l1.val < l2.val) {
      // If l1's value is smaller, append l1 to the merged list.
      tail.next = l1;
      l1 = l1.next;
    } else {
      // Otherwise, append l2 to the merged list.
      tail.next = l2;
      l2 = l2.next;
    }
    // Move the tail pointer to the newly added node.
    tail = tail.next!;
  }
  // Append the remaining nodes from either list (if any).
  tail.next = l1 ?? l2;
  // Return the head of the merged list (skipping the dummy node).
  return dummy.next;
}

// Recursive Approach for merging two sorted lists.
ListNode? mergeListsRecursive(ListNode? l1, ListNode? l2) {
  // Base case: if either list is empty, return the other list.
  if (l1 == null) return l2;
  if (l2 == null) return l1;

  // Recursively merge the lists.
  if (l1.val < l2.val) {
    // If l1's value is smaller, recursively merge l1.next with l2.
    l1.next = mergeListsRecursive(l1.next, l2);
    return l1;
  } else {
    // Otherwise, recursively merge l1 with l2.next.
    l2.next = mergeListsRecursive(l1, l2.next);
    return l2;
  }
}

// Min Heap Approach for merging two sorted lists.
ListNode? mergeListsMinHeap(ListNode? l1, ListNode? l2) {
  // Create a priority queue to store the nodes.
  HeapPriorityQueue<ListNode> pq = HeapPriorityQueue((a, b) => a.val.compareTo(b.val));
  // Add nodes from l1 to the priority queue.
  if (l1 != null) pq.add(l1);
  // Add nodes from l2 to the priority queue.
  if (l2 != null) pq.add(l2);

  // Create a dummy node and a current pointer.
  ListNode? dummy = ListNode(0);
  ListNode? current = dummy;

  // Extract nodes from the priority queue and create the merged list.
  while (pq.isNotEmpty) {
    ListNode node = pq.removeFirst();
    current!.next = node;
    current = current.next;
    // Add the next node of the extracted node to the priority queue (if it exists).
    if (node.next != null) pq.add(node.next!);
  }
  // Return the head of the merged list.
  return dummy.next;
}

// Merge Sort Technique Approach for merging two sorted lists.
ListNode? mergeListsMergeSort(ListNode? l1, ListNode? l2) {
  // Handle base cases.
  if (l1 == null) return l2;
  if (l2 == null) return l1;

  // Create a list of the two lists.
  List<ListNode?> lists = [l1, l2];
  // Sort the list of lists based on the value of the first node.
  lists.sort((a, b) => a!.val.compareTo(b!.val));

  // Create a dummy node and a current pointer.
  ListNode dummy = ListNode(0);
  ListNode current = dummy;
  // Iterate through the sorted list of lists.
  for (var list in lists) {
    // Iterate through each list.
    while (list != null) {
      // Append the node to the merged list.
      current.next = list;
      current = current.next!;
      list = list.next;
    }
  }
  // Return the head of the merged list.
  return dummy.next;
}

// Streaming Approach for merging two sorted lists (Real-Time Processing).
Stream<int> mergeListsStream(ListNode? l1, ListNode? l2) async* {
  // Iterate while both lists have nodes.
  while (l1 != null && l2 != null) {
    // Compare the values of the current nodes.
    if (l1.val < l2.val) {
      // If l1's value is smaller, yield l1's value.
      yield l1.val;
      l1 = l1.next;
    } else {
      // Otherwise, yield l2's value.
      yield l2.val;
      l2 = l2.next;
    }
  }
  // Yield the remaining values from l1 (if any).
  while (l1 != null) {
    yield l1.val;
    l1 = l1.next;
  }
  // Yield the remaining values from l2 (if any).
  while (l2 != null) {
    yield l2.val;
    l2 = l2.next;
  }
}

// Function to merge k sorted linked lists using a min-heap.
ListNode? mergeKLists(List<ListNode?> lists) {
  // Create a priority queue to store the nodes.
  HeapPriorityQueue<ListNode> pq = HeapPriorityQueue((a, b) => a.val.compareTo(b.val));
  // Add the head nodes of all lists to the priority queue.
  for (var list in lists) {
    if (list != null) pq.add(list);
  }

  // Create a dummy node and a current pointer.
  ListNode? dummy = ListNode(0);
  ListNode? current = dummy;

  // Extract nodes from the priority queue and create the merged list.
  while (pq.isNotEmpty) {
    ListNode node = pq.removeFirst();
    current!.next = node;
    current = current.next;
    // Add the next node of the extracted node to the priority queue (if it exists).
    if (node.next != null) pq.add(node.next!);
  }
  // Return the head of the merged list.
  return dummy.next;
}