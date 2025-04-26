#include <iostream>
#include <vector>
#include <algorithm> // Required for std::reverse
#include <limits>  // Required for numeric_limits

// Definition of a singly linked list node.  Using a struct for simplicity.
struct ListNode {
    int val;
    ListNode* next;
    // Constructor for the ListNode.  Allows for easy initialization.
    ListNode(int value) : val(value), next(nullptr) {}
};

// Function to create a linked list from a vector of integers.
// Useful for testing and converting data from other sources.
ListNode* createLinkedList(const std::vector<int>& data) {
    ListNode* head = nullptr; // Initialize head to null
    ListNode* tail = nullptr; // Initialize tail to null

    for (int value : data) {
        ListNode* newNode = new ListNode(value); // Create a new node for each value
        if (!head) { // If the list is empty
            head = newNode; //  set the new node to be the head
            tail = newNode; //  and the tail
        } else {
            tail->next = newNode; // Otherwise, add the new node to the end of the list
            tail = newNode;        // and update the tail
        }
    }
    return head; // Return the head of the created linked list
}

// Function to print the elements of a linked list.
// Useful for debugging and verifying the list's contents.
void printLinkedList(ListNode* head) {
    ListNode* current = head; // Start from the head of the list
    while (current) { // Iterate through the list until the current node is null
        std::cout << current->val << " -> "; // Print the value of the current node
        current = current->next;             // Move to the next node
    }
    std::cout << "nullptr" << std::endl; // Print "nullptr" to indicate the end of the list
}

// Function to delete a linked list and free the allocated memory.
// Essential to prevent memory leaks.
void deleteLinkedList(ListNode* head) {
    ListNode* current = head; // Start from the head
    ListNode* next = nullptr;  // Initialize next to null
    while (current) {       // Iterate through the list
        next = current->next; // Store the next node's address
        delete current;      // Delete the current node
        current = next;      // Move to the next node
    }
}

// 1.  Binary Search in a Sorted Linked List (Inefficient, but Demonstrates Concept)
//
//     * Concept:  While binary search is typically applied to arrays, this demonstrates the *idea*
//         on a linked list.  It's inefficient because accessing the middle element in a linked
//         list is O(n), unlike an array which is O(1).
//     * Real-world Use:  This is primarily an *educational* example.  In practice, if you have
//         a sorted linked list and need to do frequent searches, you'd likely convert it to a
//         sorted array (std::vector) first.  Or, consider using a different data structure
//         like a balanced tree (e.g., AVL tree, Red-Black tree) which supports efficient searching.
//
//     * Algorithm:
//         1.  Calculate the length of the linked list.
//         2.  Initialize `low` to 0 and `high` to length - 1.
//         3.  While `low` is less than or equal to `high`:
//             a.  Calculate `mid`.
//             b.  Traverse the linked list to the `mid`-th node.
//             c.  If the `mid`-th node's value is equal to the target, return the index `mid`.
//             d.  If the `mid`-th node's value is less than the target, set `low` to `mid` + 1.
//             e.  If the `mid`-th node's value is greater than the target, set `high` to `mid` - 1.
//         4.  If the target is not found, return -1.
int binarySearchLinkedList_Inefficient(ListNode* head, int target) {
    if (!head) return -1; // Handle empty list case.

    int length = 0;
    ListNode* current = head;
    while (current) { // Calculate the length of the linked list.
        length++;
        current = current->next;
    }

    int low = 0;
    int high = length - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // Calculate mid to avoid potential overflow
        current = head;
        for (int i = 0; i < mid; ++i) { // Traverse to the middle node.
            current = current->next;
        }

        if (current->val == target) {
            return mid; // Found the target, return the index.
        } else if (current->val < target) {
            low = mid + 1; // Target is in the right half.
        } else {
            high = mid - 1; // Target is in the left half.
        }
    }
    return -1; // Target not found.
}



// 2.  Reverse a Linked List (Iterative Approach)
//     * Concept:  Reverses the direction of the linked list by changing the `next` pointers
//         of each node.
//     * Real-world Use:  Common operation in data manipulation.  For example:
//         * Implementing a stack using a linked list (though a vector is usually preferred).
//         * Processing data in reverse order.
//         * Implementing undo/redo functionality.
//     * Algorithm:
//         1.  Initialize `prev` to nullptr, `current` to `head`, and `next` to nullptr.
//         2.  While `current` is not null:
//             a.  Store the next node in `next`.
//             b.  Change the `next` pointer of `current` to `prev`.
//             c.  Move `prev` to `current` and `current` to `next`.
//         3.  Set the `head` to `prev`.
//         4.  Return the new `head`.

ListNode* reverseLinkedList_Iterative(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    ListNode* next = nullptr;

    while (current) {
        next = current->next; // Store the next node
        current->next = prev; // Reverse the pointer
        prev = current;      // Move pointers forward
        current = next;
    }
    return prev; // prev is the new head
}

// 3.  Reverse a Linked List (Recursive Approach)
//     * Concept:  Reverses the linked list using recursion.  Can be more elegant for some,
//         but may use more stack space.
//     * Real-world Use:
//         * Demonstrates a different problem-solving approach (recursion).
//         * Can be used in situations where a recursive solution is more natural.
//     * Algorithm:
//         1.  Base case: If the list is empty or has only one node, return the head.
//         2.  Recursively reverse the rest of the list (from the second node onwards).
//         3.  Let `reversedHead` be the head of the reversed sublist.
//         4.  Find the tail of the reversed sublist (which is the original second node).
//         5.  Make the original head point to the tail of the reversed sublist.
//         6.  Make the original head's next pointer point to null.
//         7.  Return `reversedHead`.
ListNode* reverseLinkedList_Recursive(ListNode* head) {
    if (!head || !head->next) {
        return head; // Base case: empty or single node list is already reversed
    }

    ListNode* reversedHead = reverseLinkedList_Recursive(head->next); // Recursive call

    // head->next is now the last node of the reversed list.  Make it point back to head.
    head->next->next = head;
    head->next = nullptr; // Set head's next to null, making it the new tail.

    return reversedHead; // Return the new head of the reversed list
}

// 4. Find Middle Node of a Linked List
//    * Concept:  Finds the middle node of a linked list.
//    * Real-world Use:
//        * Useful in various linked list algorithms, such as finding the middle
//          for merge sort, or for certain geometric problems.
//    * Algorithm:
//        1. Use the "tortoise and hare" approach (fast and slow pointers).
//        2. Initialize two pointers, `slow` and `fast`, to the head of the list.
//        3. Move `slow` one step at a time, and `fast` two steps at a time.
//        4. When `fast` reaches the end of the list, `slow` will be at the middle node.
//        5. Handle edge cases: empty list, list with one node, list with two nodes.

ListNode* findMiddleNode(ListNode* head) {
    if (!head) return nullptr;       // Empty list
    if (!head->next) return head;  // Single node list

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;       // Move slow pointer one step
        fast = fast->next->next; // Move fast pointer two steps
    }
    return slow; // Slow pointer is now at the middle node
}

// 5. Detect a Cycle in a Linked List
//    * Concept: Detects if a linked list has a cycle (i.e., a node's next pointer points
//      to an earlier node in the list, creating a loop).
//    * Real-world Use:
//       * Crucial in memory management (detecting circular references).
//       * Detecting loops in data structures.
//       * Used in some graph algorithms.
//    * Algorithm:
//       1. Use Floyd's Cycle-Finding Algorithm ("tortoise and hare").
//       2. Initialize two pointers, `slow` and `fast`, to the head of the list.
//       3. Move `slow` one step at a time, and `fast` two steps at a time.
//       4. If there is a cycle, `slow` and `fast` will eventually meet.
//       5. If there is no cycle, `fast` will reach the end of the list (nullptr).

bool hasCycle(ListNode* head) {
    if (!head || !head->next) return false; // No cycle if list is empty or has one node

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true; // Cycle detected
        }
    }
    return false; // No cycle
}

int main() {
    // Example Usage of the functions
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    ListNode* head = createLinkedList(data);

    std::cout << "Original Linked List: ";
    printLinkedList(head);

    // Example of Binary Search (Inefficient)
    std::cout << "\nBinary Search (Inefficient):" << std::endl;
    std::cout << "Index of 5: " << binarySearchLinkedList_Inefficient(head, 5) << std::endl; // Expected: 4
    std::cout << "Index of 10: " << binarySearchLinkedList_Inefficient(head, 10) << std::endl; // Expected 9
    std::cout << "Index of 11: " << binarySearchLinkedList_Inefficient(head, 11) << std::endl; // Expected -1

    // Example of Reverse Linked List (Iterative)
    ListNode* reversedHeadIterative = reverseLinkedList_Iterative(head); // head is now invalid
    std::cout << "\nReversed Linked List (Iterative): ";
    printLinkedList(reversedHeadIterative);

     //Recreate the linked list
    head = createLinkedList(data);
    // Example of Reverse Linked List (Recursive)
    ListNode* reversedHeadRecursive = reverseLinkedList_Recursive(head); // head is now invalid
    std::cout << "Reversed Linked List (Recursive): ";
    printLinkedList(reversedHeadRecursive);

    // Example of Find Middle Node
    head = createLinkedList(data);
    ListNode* middleNode = findMiddleNode(head);
    std::cout << "\nMiddle Node: " << middleNode->val << std::endl; // Expected: 5 or 6 depending on definition

    // Example of Cycle Detection
    std::cout << "\nCycle Detection: " << (hasCycle(head) ? "Has Cycle" : "No Cycle") << std::endl; // Expected: No Cycle

    // Create a cycle for testing hasCycle
    ListNode* tail = head;
    while(tail->next){
        tail = tail->next;
    }
    tail->next = head->next->next; //create a cycle
    std::cout << "Cycle Detection: " << (hasCycle(head) ? "Has Cycle" : "No Cycle") << std::endl; // Expected: Has Cycle
    tail->next = nullptr; //remove the cycle

    deleteLinkedList(head); // Clean up the linked list.  Important!
    return 0;
}
