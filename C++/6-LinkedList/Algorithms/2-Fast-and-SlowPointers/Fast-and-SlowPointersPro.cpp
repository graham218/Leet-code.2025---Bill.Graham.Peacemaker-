/*
 * Title: Linked List Fast and Slow Pointer Techniques - Real World Project Implementations
 * Language: C++
 * Description: Different practical uses of fast and slow pointers in linked lists
 */

#include <iostream>
using namespace std;

// Definition of a singly linked list node
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Utility function to print a linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

/*************************************
 * Approach 1: Detect Cycle in a Linked List
 * Real-world: Detecting endless loops in routing or message passing
 *************************************/
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;           // Move slow by 1
        fast = fast->next->next;      // Move fast by 2
        if (slow == fast) return true; // If they meet, cycle exists
    }
    return false;
}

/*************************************
 * Approach 2: Find Middle of the Linked List
 * Real-world: Splitting linked lists for parallel processing
 *************************************/
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; // Slow is now at the middle
}

/*************************************
 * Approach 3: Remove N-th Node from End
 * Real-world: Memory management, LRU cache eviction
 *************************************/
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;

    // Move fast n+1 steps
    for (int i = 0; i <= n; ++i) {
        fast = fast->next;
    }

    // Move fast to the end, maintaining the gap
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }

    // Delete the nth node
    ListNode* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;

    return dummy.next;
}

/*************************************
 * Approach 4: Check if a Linked List is a Palindrome
 * Real-world: String validation in applications (e.g., usernames, identifiers)
 *************************************/
bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;

    // Find middle
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second half
    ListNode* prev = nullptr;
    while (slow) {
        ListNode* nextTemp = slow->next;
        slow->next = prev;
        prev = slow;
        slow = nextTemp;
    }

    // Check palindrome
    ListNode* left = head;
    ListNode* right = prev;
    while (right) {
        if (left->val != right->val) return false;
        left = left->next;
        right = right->next;
    }
    return true;
}

/*************************************
 * Approach 5: Find Start of Cycle
 * Real-world: Correctly identifying point of failure in tracking systems
 *************************************/
ListNode* detectCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            // Cycle detected
            ListNode* entry = head;
            while (entry != slow) {
                entry = entry->next;
                slow = slow->next;
            }
            return entry; // Start of the cycle
        }
    }
    return nullptr;
}

// Main function to demonstrate the code
int main() {
    // Create a sample list: 1->2->3->4->5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    cout << "Original list: ";
    printList(head);

    cout << "Middle Node Value: " << findMiddle(head)->val << endl;

    head = removeNthFromEnd(head, 2);
    cout << "List after removing 2nd node from end: ";
    printList(head);

    cout << "Is Palindrome: " << (isPalindrome(head) ? "Yes" : "No") << endl;

    // Create a cycle for testing
    head->next->next->next = head->next; // Creating a cycle

    cout << "Has Cycle: " << (hasCycle(head) ? "Yes" : "No") << endl;

    ListNode* startOfCycle = detectCycle(head);
    if (startOfCycle)
        cout << "Cycle starts at node with value: " << startOfCycle->val << endl;

    // Normally we would also delete allocated memory

    return 0;
}
