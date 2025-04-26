#include <iostream>
#include <vector>
#include <algorithm> // Required for std::reverse

// Definition of a singly linked list node.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to create a linked list from a vector.
ListNode* createLinkedList(const std::vector<int>& arr) {
    if (arr.empty()) {
        return nullptr;
    }
    ListNode* head = new ListNode(arr[0]);
    ListNode* current = head;
    for (size_t i = 1; i < arr.size(); ++i) {
        current->next = new ListNode(arr[i]);
        current = current->next;
    }
    return head;
}

// Function to print a linked list.
void printLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->val << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Function to delete a linked list to free memory.  Important to prevent memory leaks.
void deleteLinkedList(ListNode* head) {
    ListNode* current = head;
    ListNode* next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

// 1. Binary Search in a Sorted Linked List (Inefficient - Direct Traversal)
//    -  Conceptually applies binary search, but linked lists don't allow direct access.
//    -  Time Complexity: O(n) -  Still linear, not truly binary search.
//    -  Space Complexity: O(1) - Constant extra space.
int binarySearchLinkedList_Approach1(ListNode* head, int target) {
    int index = 0;
    ListNode* current = head;
    while (current != nullptr) {
        if (current->val == target) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; // Target not found.
}

// 2. Binary Search in Sorted Vector (Efficient)
//    - Convert the linked list to a vector, then perform standard binary search.
//    - Time Complexity: O(n) to convert to vector, O(log n) for binary search.  Total: O(n).
//    - Space Complexity: O(n) -  Space for the vector.
int binarySearchLinkedList_Approach2(ListNode* head, int target) {
    std::vector<int> values;
    ListNode* current = head;
    while (current != nullptr) {
        values.push_back(current->val);
        current = current->next;
    }

    int left = 0;
    int right = values.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2; // Prevent potential overflow
        if (values[mid] == target) {
            return mid;
        } else if (values[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// 3. Reverse Linked List (Iterative)
//    - Standard iterative linked list reversal.
//    - Time Complexity: O(n)
//    - Space Complexity: O(1)
ListNode* reverseLinkedList_Iterative(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* current = head;
    ListNode* next;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

// 4. Reverse Linked List (Recursive)
//    - Recursive approach to linked list reversal.
//    - Time Complexity: O(n)
//    - Space Complexity: O(n) -  Due to the call stack.
ListNode* reverseLinkedList_Recursive(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode* newHead = reverseLinkedList_Recursive(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

// 5. Reverse Linked List (Using std::reverse - Not Recommended for interview, good for understanding)
//    - Uses the std::reverse algorithm from the C++ standard library.  Demonstrates using existing tools.
//    - Time Complexity: O(n) -  std::reverse is generally linear.
//    - Space Complexity: O(n) -  Requires converting to a vector.
ListNode* reverseLinkedList_STL(ListNode* head) {
     if (!head) return nullptr;

     std::vector<int> values;
     ListNode* curr = head;
     while (curr) {
         values.push_back(curr->val);
         curr = curr->next;
     }

     std::reverse(values.begin(), values.end()); // Use the std::reverse

     curr = head;
     for (int val : values) { // Copy the reversed values back into the linked list.
         curr->val = val;
         curr = curr->next;
     }
     return head;
}

int main() {
    // Example usage:
    std::vector<int> arr = {1, 2, 3, 4, 5};
    ListNode* head = createLinkedList(arr);

    std::cout << "Original Linked List: ";
    printLinkedList(head);

    int target = 3;
    std::cout << "Binary Search (Approach 1 - Direct Traversal): Index of " << target << " is "
              << binarySearchLinkedList_Approach1(head, target) << std::endl; // Should be 2

    std::cout << "Binary Search (Approach 2 - Vector): Index of " << target << " is "
              << binarySearchLinkedList_Approach2(head, target) << std::endl;

    // Reverse the linked list using the iterative approach.
    ListNode* reversedHeadIterative = reverseLinkedList_Iterative(head); // Pass the original head
    std::cout << "Reversed Linked List (Iterative): ";
    printLinkedList(reversedHeadIterative);

     // Reverse the linked list using the recursive approach.
    ListNode* reversedHeadRecursive = reverseLinkedList_Recursive(reversedHeadIterative); // Pass the *reversed* list
    std::cout << "Reversed Linked List (Recursive): ";
    printLinkedList(reversedHeadRecursive); // print reversed list

    ListNode* reversedHeadSTL = reverseLinkedList_STL(reversedHeadRecursive);
    std::cout << "Reversed Linked List (STL): ";
    printLinkedList(reversedHeadSTL);

    // Don't forget to delete the linked list to free memory.  Important!
    deleteLinkedList(reversedHeadSTL); // Or any of the head pointers, they all point to the same list now.

    return 0;
}
