class Customer {
  String name;
  int loyaltyPoints;

  Customer(this.name, this.loyaltyPoints);
}

class ListNode {
  Customer data; // Stores Customer object
  ListNode? next; // Pointer to the next node

  ListNode(this.data, [this.next]); // Constructor to create a node
}

class CustomerList {
  ListNode? head; // Head of the linked list

  // Adds a new customer to the beginning of the list
  void addCustomer(String name, int points) {
    ListNode newNode = ListNode(Customer(name, points)); // Create a new node with Customer data
    newNode.next = head; // Make the new node point to the current head
    head = newNode; // Update the head to the new node
  }

  // Recursive merge sort to sort the customer list by loyalty points (descending)
  ListNode? mergeSort(ListNode? head) {
    // Base case: if the list is empty or has only one node, it's already sorted
    if (head == null || head.next == null) return head;

    // Find the middle of the list
    ListNode? middle = getMiddle(head);
    // Get the node after the middle
    ListNode? nextToMiddle = middle?.next;
    // Split the list into two halves by setting middle.next to null
    middle?.next = null;

    // Recursively sort the left half
    ListNode? left = mergeSort(head);
    // Recursively sort the right half
    ListNode? right = mergeSort(nextToMiddle);

    // Merge the sorted halves
    return sortedMerge(left, right);
  }

  // Merges two sorted linked lists into a single sorted list
  ListNode? sortedMerge(ListNode? a, ListNode? b) {
    // Base cases: if either list is empty, return the other list
    if (a == null) return b;
    if (b == null) return a;

    // Compare loyalty points and merge accordingly (descending order)
    if (a.data.loyaltyPoints >= b.data.loyaltyPoints) {
      // If a's loyalty points are greater or equal, a comes first
      a.next = sortedMerge(a.next, b); // Recursively merge the rest of a with b
      return a; // Return the head of the merged list
    } else {
      // If b's loyalty points are greater, b comes first
      b.next = sortedMerge(a, b.next); // Recursively merge a with the rest of b
      return b; // Return the head of the merged list
    }
  }

  // Finds the middle node of the linked list using the slow and fast pointer approach
  ListNode? getMiddle(ListNode? head) {
    // If the list is empty, return null
    if (head == null) return head;
    ListNode? slow = head, fast = head; // Initialize slow and fast pointers

    // Move slow pointer one step and fast pointer two steps at a time
    while (fast?.next != null && fast?.next?.next != null) {
      slow = slow?.next;
      fast = fast?.next?.next;
    }
    // When fast reaches the end, slow points to the middle
    return slow;
  }

  // Prints the customer list
  void printCustomers() {
    ListNode? temp = head; // Start from the head
    while (temp != null) {
      // Print customer name and loyalty points
      print("${temp.data.name}: ${temp.data.loyaltyPoints} points");
      temp = temp.next; // Move to the next node
    }
  }
}

void main() {
  CustomerList customerList = CustomerList();
  customerList.addCustomer("Alice", 120);
  customerList.addCustomer("Bob", 200);
  customerList.addCustomer("Charlie", 90);
  customerList.addCustomer("Dave", 150);
  customerList.addCustomer("Eve", 300);

  print("Customers before sorting:");
  customerList.printCustomers();

  // Sort the customer list using merge sort
  customerList.head = customerList.mergeSort(customerList.head);

  print("\nCustomers after sorting (by loyalty points descending):");
  customerList.printCustomers();
}