#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Function to print the linked list
void printList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Function to create a linked list from a vector
ListNode* createList(const std::vector<int>& vec) {
    if (vec.empty()) {
        return nullptr;
    }
    ListNode* head = new ListNode(vec[0]);
    ListNode* current = head;
    for (size_t i = 1; i < vec.size(); ++i) {
        current->next = new ListNode(vec[i]);
        current = current->next;
    }
    return head;
}

// Function to delete a linked list
void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Approach 1: Two Pass - Calculate length first
ListNode* removeNthFromEnd_TwoPass(ListNode* head, int n) {
    if (!head) return nullptr;

    int length = 0;
    ListNode* current = head;
    while (current) {
        length++;
        current = current->next;
    }

    if (n > length) return head; // Handle invalid input
    if (n == length) { // Remove the head
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    current = head;
    for (int i = 0; i < length - n - 1; ++i) {
        current = current->next;
    }

    ListNode* temp = current->next;
    current->next = current->next->next;
    delete temp;

    return head;
}

// Approach 2: Two Pointers - Fast and Slow
ListNode* removeNthFromEnd_TwoPointers(ListNode* head, int n) {
    if (!head) return nullptr;

    ListNode* fast = head;
    ListNode* slow = head;

    // Move fast pointer n steps ahead
    for (int i = 0; i < n; ++i) {
        if (!fast) return head; // Handle cases where n is larger than the list length.
        fast = fast->next;
    }

    if (!fast) { // If fast is nullptr, it means we need to remove the head
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    // Move both pointers until fast reaches the end
    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }

    ListNode* temp = slow->next;
    slow->next = slow->next->next;
    delete temp;

    return head;
}

// Approach 3: Using a Stack
ListNode* removeNthFromEnd_Stack(ListNode* head, int n) {
    if (!head) return nullptr;

    std::stack<ListNode*> nodeStack;
    ListNode* current = head;

    while (current) {
        nodeStack.push(current);
        current = current->next;
    }

    if (n > nodeStack.size()) return head; // Handle invalid input

    for (int i = 0; i < n - 1; ++i) {
        nodeStack.pop();
    }

    if (nodeStack.size() == n) { // Removing the head
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return head;
    }
    ListNode* target = nodeStack.top();
    nodeStack.pop();
    ListNode* prev = nodeStack.top();

    prev->next = target->next;
    delete target;
    return head;
}

// Approach 4: Recursion
ListNode* removeNthFromEnd_Recursive(ListNode* head, int n, int& count) {
    if (!head) {
        count = 0;
        return nullptr;
    }

    head->next = removeNthFromEnd_Recursive(head->next, n, count);
    count++;

    if (count == n) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    return head;
}

ListNode* removeNthFromEnd_Recursion(ListNode* head, int n) {
    int count = 0;
    return removeNthFromEnd_Recursive(head, n, count);
}

// Approach 5: Dummy Node
ListNode* removeNthFromEnd_DummyNode(ListNode* head, int n) {
    if (!head) return nullptr;

    ListNode* dummy = new ListNode(0); // Create a dummy node
    dummy->next = head;
    ListNode* fast = dummy;
    ListNode* slow = dummy;

    // Move fast pointer n steps ahead
    for (int i = 0; i < n; ++i) {
        fast = fast->next;
    }

    // Move both pointers until fast reaches the end
    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }

    ListNode* temp = slow->next;
    slow->next = slow->next->next;
    delete temp;

    return dummy->next; // Return the head of the modified list
}

int main() {
    // Test cases
    std::vector<int> list1 = {1, 2, 3, 4, 5};
    std::vector<int> list2 = {1};
    std::vector<int> list3 = {1, 2};
    std::vector<int> list4 = {1, 2, 3, 4, 5};
    std::vector<int> list5 = {1, 2, 3, 4, 5};

    ListNode* head1 = createList(list1);
    ListNode* head2 = createList(list2);
    ListNode* head3 = createList(list3);
    ListNode* head4 = createList(list4);
    ListNode* head5 = createList(list5);

    // Test Approach 1: Two Pass
    std::cout << "Test Case 1 - Two Pass: Removing 2nd node from the end: " << std::endl;
    ListNode* result1 = removeNthFromEnd_TwoPass(head1, 2);
    printList(result1); // Expected output: 1 -> 2 -> 3 -> 5 -> nullptr
    deleteList(result1);

    // Test Approach 2: Two Pointers
    std::cout << "Test Case 2 - Two Pointers: Removing 1st node from the end: " << std::endl;
    ListNode* result2 = removeNthFromEnd_TwoPointers(head2, 1);
    printList(result2); // Expected output: nullptr
    deleteList(result2);

    // Test Approach 3: Stack
    std::cout << "Test Case 3 - Stack: Removing 2nd node from the end: " << std::endl;
    ListNode* result3 = removeNthFromEnd_Stack(head3, 2);
    printList(result3); // Expected output: 2 -> nullptr
    deleteList(result3);

    // Test Approach 4: Recursion
    std::cout << "Test Case 4 - Recursion: Removing 3rd node from the end: " << std::endl;
    ListNode* result4 = removeNthFromEnd_Recursion(head4, 3);
    printList(result4); // Expected output: 1 -> 2 -> 4 -> 5 -> nullptr
    deleteList(result4);

    // Test Approach 5: Dummy Node
    std::cout << "Test Case 5 - Dummy Node: Removing 4th node from the end: " << std::endl;
    ListNode* result5 = removeNthFromEnd_DummyNode(head5, 4);
    printList(result5); // Expected output: 1 -> 3 -> 4 -> 5 -> nullptr
    deleteList(result5);

    return 0;
}
