// Floyd's Cycle Detection - Tortoise and Hare
// 5 different C++ approaches with detailed comments

#include <iostream>
#include <unordered_set>
using namespace std;

// Definition for singly-linked list node.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

//--------------------------------------------------
// Approach 1: Classic Floyd's Cycle Detection
//--------------------------------------------------
bool hasCycle_Floyd(ListNode* head) {
    if (!head || !head->next) return false;

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;          // Move slow by 1
        fast = fast->next->next;     // Move fast by 2
        if (slow == fast) return true; // Cycle detected
    }

    return false; // No cycle
}

//--------------------------------------------------
// Approach 2: Using a Hash Set
//--------------------------------------------------
bool hasCycle_HashSet(ListNode* head) {
    unordered_set<ListNode*> visited;

    while (head) {
        if (visited.count(head)) return true; // Cycle detected
        visited.insert(head);
        head = head->next;
    }

    return false; // No cycle
}

//--------------------------------------------------
// Approach 3: Modify the Linked List (Mark visited nodes)
// (Not recommended for production code)
//--------------------------------------------------
bool hasCycle_ModifyList(ListNode* head) {
    ListNode* temp = new ListNode(0); // Dummy node

    while (head) {
        if (head->next == temp) return true; // Cycle detected
        ListNode* nextNode = head->next;
        head->next = temp; // Mark as visited
        head = nextNode;
    }

    return false; // No cycle
}

//--------------------------------------------------
// Approach 4: Recursive Hash Set Approach
//--------------------------------------------------
bool detectCycleRecursive(ListNode* node, unordered_set<ListNode*>& visited) {
    if (!node) return false;
    if (visited.count(node)) return true; // Cycle detected

    visited.insert(node);
    return detectCycleRecursive(node->next, visited);
}

bool hasCycle_Recursive(ListNode* head) {
    unordered_set<ListNode*> visited;
    return detectCycleRecursive(head, visited);
}

//--------------------------------------------------
// Approach 5: Two-Pointer Variation (Advance fast first)
//--------------------------------------------------
bool hasCycle_TwoPointerVariation(ListNode* head) {
    if (!head || !head->next) return false;

    ListNode* slow = head;
    ListNode* fast = head->next;

    while (slow != fast) {
        if (!fast || !fast->next) return false; // No cycle
        slow = slow->next;
        fast = fast->next->next;
    }

    return true; // Cycle detected
}

//--------------------------------------------------
// Helper Functions to create test cases
//--------------------------------------------------
ListNode* createCycleList() {
    ListNode* head = new ListNode(3);
    ListNode* second = new ListNode(2);
    ListNode* third = new ListNode(0);
    ListNode* fourth = new ListNode(-4);

    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = second; // Create cycle

    return head;
}

ListNode* createNonCycleList() {
    ListNode* head = new ListNode(1);
    ListNode* second = new ListNode(2);

    head->next = second;

    return head;
}

//--------------------------------------------------
// Main function to test all approaches
//--------------------------------------------------
int main() {
    ListNode* cycleList = createCycleList();
    ListNode* nonCycleList = createNonCycleList();

    cout << "Testing Classic Floyd's Algorithm: " << endl;
    cout << hasCycle_Floyd(cycleList) << " ";
    cout << hasCycle_Floyd(nonCycleList) << endl;

    cout << "\nTesting HashSet Approach: " << endl;
    cout << hasCycle_HashSet(cycleList) << " ";
    cout << hasCycle_HashSet(nonCycleList) << endl;

    cout << "\nTesting Modify List Approach: " << endl;
    cout << hasCycle_ModifyList(cycleList) << " ";
    cout << hasCycle_ModifyList(nonCycleList) << endl;

    cout << "\nTesting Recursive HashSet Approach: " << endl;
    cout << hasCycle_Recursive(cycleList) << " ";
    cout << hasCycle_Recursive(nonCycleList) << endl;

    cout << "\nTesting Two Pointer Variation Approach: " << endl;
    cout << hasCycle_TwoPointerVariation(cycleList) << " ";
    cout << hasCycle_TwoPointerVariation(nonCycleList) << endl;

    return 0;
}
