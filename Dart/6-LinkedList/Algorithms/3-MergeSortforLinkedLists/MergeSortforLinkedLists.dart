class ListNode {
  int val;
  ListNode? next;

  ListNode(this.val, [this.next]);
}

class LinkedList {
  ListNode? head;

  void push(int val) {
    ListNode newNode = ListNode(val);
    newNode.next = head;
    head = newNode;
  }

  // Approach 1: Standard Merge Sort (Recursive)
  ListNode? mergeSort(ListNode? head) {
    if (head == null || head.next == null) return head;

    ListNode? middle = getMiddle(head);
    ListNode? nextToMiddle = middle?.next;
    middle?.next = null;

    ListNode? left = mergeSort(head);
    ListNode? right = mergeSort(nextToMiddle);

    return sortedMerge(left, right);
  }

  // Merges two sorted linked lists
  ListNode? sortedMerge(ListNode? a, ListNode? b) {
    if (a == null) return b;
    if (b == null) return a;

    if (a.val <= b.val) {
      a.next = sortedMerge(a.next, b);
      return a;
    } else {
      b.next = sortedMerge(a, b.next);
      return b;
    }
  }

  // Finds the middle of the linked list
  ListNode? getMiddle(ListNode? head) {
    if (head == null) return head;
    ListNode? slow = head, fast = head;

    while (fast?.next != null && fast?.next?.next != null) {
      slow = slow?.next;
      fast = fast?.next?.next;
    }
    return slow;
  }

  // Approach 3: Bottom-Up Merge Sort (Fixed)
  ListNode? mergeSortBottomUp(ListNode? head) {
    if (head == null || head.next == null) return head;

    int length = getLength(head);
    ListNode dummy = ListNode(0, head);
    ListNode? curr;
    ListNode? tail;

    for (int size = 1; size < length; size *= 2) {
      curr = dummy.next;
      tail = dummy;

      while (curr != null) {
        ListNode? left = curr;
        ListNode? right = split(left, size);
        curr = split(right, size);
        tail!.next = sortedMerge(left, right);
        while (tail?.next != null) {
          tail = tail?.next;
        }
      }
    }
    return dummy.next;
  }

  int getLength(ListNode? head) {
    int length = 0;
    while (head != null) {
      length++;
      head = head.next;
    }
    return length;
  }

  ListNode? split(ListNode? head, int size) {
    while (head != null && --size > 0) {
      head = head.next;
    }
    ListNode? rest = head?.next;
    if (head != null) head.next = null;
    return rest;
  }

  void printList(ListNode? node) {
    while (node != null) {
      print('${node.val} '); // Add a space for better readability
      node = node.next;
    }
    print(''); // Add a newline after printing the list
  }
}

void main() {
  LinkedList list = LinkedList();
  list.push(15);
  list.push(10);
  list.push(5);
  list.push(20);
  list.push(3);
  list.push(2);

  print("Linked List before sorting:");
  list.printList(list.head);

  list.head = list.mergeSortBottomUp(list.head); // Changed to Bottom-Up

  print("\nLinked List after sorting:");
  list.printList(list.head);
}