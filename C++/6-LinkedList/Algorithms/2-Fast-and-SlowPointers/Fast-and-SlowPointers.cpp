// Title: Linked List - Fast and Slow Pointers (5 Approaches)

#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Approach 1: Find Middle Node using Fast and Slow Pointers
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; // When fast reaches end, slow is at middle
}

// Approach 2: Detect Cycle in a Linked List
bool hasCycle(ListNode *head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true; // Cycle detected
    }
    return false; // No cycle
}

// Approach 3: Find Start of Cycle (if cycle exists)
ListNode* detectCycle(ListNode *head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { // Cycle detected
            ListNode* entry = head;
            while (entry != slow) {
                entry = entry->next;
                slow = slow->next;
            }
            return entry; // Start of cycle
        }
    }
    return nullptr; // No cycle
}

// Approach 4: Check if Linked List is Palindrome using Fast and Slow Pointers
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
        ListNode* nextNode = slow->next;
        slow->next = prev;
        prev = slow;
        slow = nextNode;
    }

    // Compare two halves
    ListNode* first = head;
    ListNode* second = prev;
    while (second) {
        if (first->val != second->val) return false;
        first = first->next;
        second = second->next;
    }
    return true;
}

// Approach 5: Find Kth Node from End using Fast and Slow Pointers
ListNode* findKthFromEnd(ListNode* head, int k) {
    ListNode* slow = head;
    ListNode* fast = head;

    // Move fast k steps ahead
    for (int i = 0; i < k; ++i) {
        if (!fast) return nullptr; // k is larger than length
        fast = fast->next;
    }

    // Move slow and fast together
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow; // Slow is now at k-th node from end
}

// Utility function to add node at the end
void appendNode(ListNode*& head, int val) {
    if (!head) {
        head = new ListNode(val);
        return;
    }
    ListNode* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = new ListNode(val);
}

// Utility function to print linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

// Main function to demonstrate
int main() {
    ListNode* head = nullptr;
    appendNode(head, 1);
    appendNode(head, 2);
    appendNode(head, 3);
    appendNode(head, 2);
    appendNode(head, 1);

    cout << "Original List: ";
    printList(head);

    ListNode* mid = findMiddle(head);
    cout << "Middle Node Value: " << (mid ? mid->val : -1) << endl;

    cout << "Is Palindrome: " << (isPalindrome(head) ? "Yes" : "No") << endl;

    int k = 2;
    ListNode* kthNode = findKthFromEnd(head, k);
    cout << k << "-th Node from End: " << (kthNode ? kthNode->val : -1) << endl;

    return 0;
}
