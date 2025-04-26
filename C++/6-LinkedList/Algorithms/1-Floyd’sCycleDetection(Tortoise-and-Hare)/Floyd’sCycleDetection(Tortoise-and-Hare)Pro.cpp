/*
    Floyd’s Cycle Detection Algorithm (Tortoise and Hare)
    Different real-world project implementation styles.

    Problem: Detect a cycle in a linked list.
*/

#include <iostream>
#include <unordered_set>
using namespace std;

// Basic Node structure for Linked List
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

//------------------------------------------
// 1. Pure Floyd’s Cycle Detection (Academic Style)
//------------------------------------------
bool detectCycle_Floyd(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;          // Move by 1 step
        fast = fast->next->next;    // Move by 2 steps
        if (slow == fast)
            return true;            // Cycle detected
    }
    return false;                   // No cycle
}

//------------------------------------------
// 2. Using Hash Set (Memory-Intensive Project Like Web Crawlers)
//------------------------------------------
bool detectCycle_HashSet(Node* head) {
    unordered_set<Node*> visited;
    Node* current = head;

    while (current != nullptr) {
        if (visited.find(current) != visited.end())
            return true;            // Node already visited => cycle
        visited.insert(current);
        current = current->next;
    }
    return false;
}

//------------------------------------------
// 3. Cycle Detection + Entry Point (For Blockchain Linked Structures)
//------------------------------------------
Node* detectCycle_EntryPoint(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            Node* entry = head;
            while (entry != slow) {
                entry = entry->next;
                slow = slow->next;
            }
            return entry;           // Entry point of the cycle
        }
    }
    return nullptr;                 // No cycle
}

//------------------------------------------
// 4. Smart Pointer Simulation (Resource-Constrained Embedded Systems)
//------------------------------------------
// No real smart pointers in raw linked list, but idea is mimicked
bool detectCycle_SmartPtrSim(Node* head) {
    if (!head) return false;

    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }
    return false;
}

//------------------------------------------
// 5. Recursion with Memory (Artificial Intelligence / Path Learning)
//------------------------------------------
bool detectCycle_Recursive_Helper(Node* node, unordered_set<Node*>& visited) {
    if (node == nullptr)
        return false;

    if (visited.find(node) != visited.end())
        return true;                // Already visited

    visited.insert(node);
    return detectCycle_Recursive_Helper(node->next, visited);
}

bool detectCycle_Recursive(Node* head) {
    unordered_set<Node*> visited;
    return detectCycle_Recursive_Helper(head, visited);
}

//------------------------------------------
// Helper function to create a cycle for testing
//------------------------------------------
void createCycle(Node* head, int pos) {
    if (pos == -1) return;
    Node* cycleEntry = head;
    for (int i = 0; i < pos; i++) {
        if (cycleEntry->next)
            cycleEntry = cycleEntry->next;
    }

    Node* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
    tail->next = cycleEntry;
}

//------------------------------------------
// Main Function for Testing
//------------------------------------------
int main() {
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    createCycle(head, 2); // Create cycle at position 2 (0-indexed)

    cout << "Floyd's Algorithm: " << (detectCycle_Floyd(head) ? "Cycle Detected" : "No Cycle") << endl;
    cout << "Hash Set: " << (detectCycle_HashSet(head) ? "Cycle Detected" : "No Cycle") << endl;
    Node* cycleEntry = detectCycle_EntryPoint(head);
    cout << "Entry Point: " << (cycleEntry ? "Cycle starts at node with data " + to_string(cycleEntry->data) : "No Cycle") << endl;
    cout << "Smart Pointer Simulation: " << (detectCycle_SmartPtrSim(head) ? "Cycle Detected" : "No Cycle") << endl;
    cout << "Recursive Detection: " << (detectCycle_Recursive(head) ? "Cycle Detected" : "No Cycle") << endl;

    return 0;
}
