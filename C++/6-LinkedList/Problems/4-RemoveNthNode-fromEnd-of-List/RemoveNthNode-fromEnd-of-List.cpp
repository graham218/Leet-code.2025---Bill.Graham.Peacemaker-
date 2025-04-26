#include <iostream>
#include <vector>
#include <algorithm>
#include <stack> // Include the stack header

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
    while (head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

// Function to create a linked list from a vector
ListNode* createList(const std::vector<int>& vec) {
    if (vec.empty()) return nullptr;
    ListNode* head = new ListNode(vec[0]);
    ListNode* current = head;
    for (size_t i = 1; i < vec.size(); ++i) {
        current->next = new ListNode(vec[i]);
        current = current->next;
    }
    return head;
}

// Function to delete the entire linked list.  Useful for preventing memory leaks.
void deleteList(ListNode* head) {
    ListNode* current = head;
    ListNode* next;
    while (current) {
        next = current->next;
        delete current;
        current = next;
    }
}

// Approach 1: Two Pass - Calculate length first, then remove
// 1. Calculate the length of the linked list.
// 2. Traverse to the (length - n)th node and remove the nth node from the end.
ListNode* removeNthFromEnd_TwoPass(ListNode* head, int n) {
    if (!head) return nullptr;

    int length = 0;
    ListNode* current = head;
    while (current) {
        length++;
        current = current->next;
    }

    if (n > length) return head; // Handle invalid input

    if (n == length) { // Remove the head node
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    int toTraverse = length - n - 1; // Index of the node *before* the one to remove
    current = head;
    for (int i = 0; i < toTraverse; ++i) {
        current = current->next;
    }

    ListNode* temp = current->next;      // Node to be removed
    current->next = temp->next;          // Skip over the node to be removed
    delete temp;
    return head;
}

// Approach 2: Two Pointers - Fast and Slow pointers
// 1. Use two pointers, 'fast' and 'slow'.
// 2. Move 'fast' n nodes ahead of 'slow'.
// 3. Move both pointers until 'fast' reaches the end.
// 4. 'slow' will be pointing to the node before the one to delete.
ListNode* removeNthFromEnd_TwoPointers(ListNode* head, int n) {
    if (!head) return nullptr;

    ListNode* dummy = new ListNode(0); // Dummy node to handle edge case: remove head
    dummy->next = head;
    ListNode* slow = dummy;
    ListNode* fast = dummy;

    // Move fast pointer n steps ahead
    for (int i = 0; i < n; ++i) {
        if (!fast) return head; // Handle invalid n (n is larger than list size)
        fast = fast->next;
    }

    // Move both pointers until fast reaches the end
    while (fast->next) {
        slow = slow->next;
        fast = fast->next;
    }

    ListNode* temp = slow->next; // Node to be removed
    slow->next = temp->next;     // Skip the node to be removed
    delete temp;

    ListNode* result = dummy->next;
    delete dummy; // Clean up dummy node.
    return result;
}

// Approach 3: Using a Stack
// 1. Push all nodes into a stack.
// 2. Pop n nodes from the stack.
// 3. The top of the stack is the node before the one to remove.
ListNode* removeNthFromEnd_Stack(ListNode* head, int n) {
    if (!head) return nullptr;

    std::stack<ListNode*> stack; // Fix: Include std::
    ListNode* current = head;

    while (current) {
        stack.push(current);
        current = current->next;
    }

    if (n > stack.size()) return head; // Handle invalid input

    for (int i = 0; i < n; ++i) {
        stack.pop();
    }

    if (stack.empty()) { // Remove the head
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    ListNode* prev = stack.top(); // Node before the one to remove
    ListNode* toRemove = prev->next;
    prev->next = toRemove->next;
    delete toRemove;
    return head;
}

// Approach 4: Recursion
// 1. Use recursion to reach the end of the list.
// 2. Keep a counter. When the counter equals n, remove the node.
// 3. Return the modified list.
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
        return head;
    }
    return head;
}

ListNode* removeNthFromEnd_Recursive(ListNode* head, int n) {
    int count = 0;
    return removeNthFromEnd_Recursive(head, n, count);
}

// Approach 5: Using Vector
// 1. Store all the nodes in a vector.
// 2. Calculate the index of the node to be removed.
// 3. Remove the node from the vector and adjust pointers.
ListNode* removeNthFromEnd_Vector(ListNode* head, int n) {
    if (!head) return nullptr;

    std::vector<ListNode*> nodes;
    ListNode* current = head;
    while (current) {
        nodes.push_back(current);
        current = current->next;
    }

    if (n > nodes.size()) return head; // Handle invalid input

    int indexToRemove = nodes.size() - n;

    if (indexToRemove == 0) { // Remove the head
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return head;
    } else {
        ListNode* prevNode = nodes[indexToRemove - 1];
        ListNode* nodeToRemove = nodes[indexToRemove];
        prevNode->next = nodeToRemove->next;
        delete nodeToRemove;
        return head;
    }
}

int main() {
    // Example usage
    std::vector<int> values = {1, 2, 3, 4, 5};
    ListNode* head = createList(values);

    std::cout << "Original List: ";
    printList(head);

    int n = 2; // Remove the 2nd node from the end

    // Test each approach:
    ListNode* head1 = createList(values); // Create a new list for each test to avoid modifying the same list
    head1 = removeNthFromEnd_TwoPass(head1, n);
    std::cout << "Two Pass: ";
    printList(head1);
    deleteList(head1);

    ListNode* head2 = createList(values);
    head2 = removeNthFromEnd_TwoPointers(head2, n);
    std::cout << "Two Pointers: ";
    printList(head2);
    deleteList(head2);

    ListNode* head3 = createList(values);
    head3 = removeNthFromEnd_Stack(head3, n);
    std::cout << "Stack: ";
    printList(head3);
    deleteList(head3);

    ListNode* head4 = createList(values);
    head4 = removeNthFromEnd_Recursive(head4, n);
    std::cout << "Recursion: ";
    printList(head4);
    deleteList(head4);

    ListNode* head5 = createList(values);
    head5 = removeNthFromEnd_Vector(head5, n);
    std::cout << "Vector: ";
    printList(head5);
    deleteList(head5);

    return 0;
}
