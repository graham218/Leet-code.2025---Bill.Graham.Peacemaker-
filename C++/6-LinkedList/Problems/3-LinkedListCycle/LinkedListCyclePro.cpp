#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <climits> // Include climits for INT_MIN

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 1. Floyd's Cycle Detection Algorithm (Fast and Slow Pointers)
//   - Most common and efficient approach.
//   - Real-world application: Detecting loops in network routing tables.  If a router's table has a loop, packets can get stuck.
bool hasCycle_Floyd(ListNode *head) {
    if (!head || !head->next) {
        return false;
    }
    ListNode *slow = head;
    ListNode *fast = head->next; // Start fast pointer one step ahead

    while (fast && fast->next) {
        if (slow == fast) {
            return true; // Cycle detected
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return false; // No cycle
}

// 2. Hash Table Approach
//   - Uses extra space but is conceptually simple.
//   - Real-world application: Detecting if a file system has a circular directory link (though file systems usually have their own cycle prevention).
bool hasCycle_HashSet(ListNode *head) {
    std::unordered_set<ListNode*> visited;
    ListNode *current = head;
    while (current) {
        if (visited.find(current) != visited.end()) {
            return true; // Cycle detected
        }
        visited.insert(current);
        current = current->next;
    }
    return false; // No cycle
}

// 3. Visited Node Marker (Modifies the list)
//   - Modifies the linked list by changing the 'val' of visited nodes.
//   - Real-world application: Useful in some memory-constrained embedded systems where you can't use extra data structures, and modifying the list is acceptable.  For example, marking nodes during garbage collection in a very simple embedded environment.
bool hasCycle_VisitedMarker(ListNode *head) {
    ListNode *current = head;
    while (current) {
        if (current->val == INT_MIN) { // Using INT_MIN as a marker
            return true; // Cycle detected
        }
        current->val = INT_MIN; // Mark the node as visited
        current = current->next;
    }
    return false; // No cycle
}

// 4. Using a Vector to Store Visited Nodes
//   - Similar to the hash table approach, but uses a vector.  Less efficient for large lists, but shows an alternative.
//   - Real-world application:  Could be adapted for a very small, fixed-size linked list where you want to avoid hash table overhead.  For example, checking for a loop in a short chain of configuration settings in a device.
bool hasCycle_Vector(ListNode *head) {
    std::vector<ListNode*> visited;
    ListNode *current = head;
    while (current) {
        if (std::find(visited.begin(), visited.end(), current) != visited.end()) {
            return true; // Cycle detected
        }
        visited.push_back(current);
        current = current->next;
    }
    return false; // No cycle
}

// 5.  Limited Steps with Check
//    - This approach limits the number of steps taken to traverse the list.
//    - It's not a *guaranteed* cycle detection, but it's useful in situations where you want to prevent infinite loops in a process, even if you can't definitively say a cycle exists.
//    - Real-world application:  A "watchdog timer" in a system that processes linked data.  If the processing takes too long (exceeds the maxSteps), you assume a loop and abort.  This prevents a program from hanging indefinitely.
bool hasCycle_LimitedSteps(ListNode *head, int maxSteps) {
    ListNode *current = head;
    int steps = 0;
    while (current && steps <= maxSteps) {
        current = current->next;
        steps++;
    }
    return (steps > maxSteps); // Return true if it ran for maxSteps.  Indicates *possible* cycle.
}

int main() {
    // Create a linked list with a cycle for testing.
    ListNode *head = new ListNode(1);
    ListNode *node2 = new ListNode(2);
    ListNode *node3 = new ListNode(3);
    ListNode *node4 = new ListNode(4);
    ListNode *node5 = new ListNode(5);

    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node2; // Create the cycle: 5 points back to 2

    // Test the different cycle detection algorithms.
    std::cout << "Floyd's: " << (hasCycle_Floyd(head) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Hash Set: " << (hasCycle_HashSet(head) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Visited Marker: " << (hasCycle_VisitedMarker(head) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Vector: " << (hasCycle_Vector(head) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Limited Steps (10): " << (hasCycle_LimitedSteps(head, 10) ? "Possible Cycle" : "No Cycle") << std::endl;
    std::cout << "Limited Steps (3): " << (hasCycle_LimitedSteps(head, 3) ? "Possible Cycle" : "No Cycle") << std::endl;

    // Create a linear linked list (no cycle)
    ListNode *linearHead = new ListNode(10);
    ListNode *linearNode2 = new ListNode(20);
    ListNode *linearNode3 = new ListNode(30);
    linearHead->next = linearNode2;
    linearNode2->next = linearNode3;

     std::cout << "Floyd's (Linear): " << (hasCycle_Floyd(linearHead) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Hash Set (Linear): " << (hasCycle_HashSet(linearHead) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Visited Marker (Linear): " << (hasCycle_VisitedMarker(linearHead) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Vector (Linear): " << (hasCycle_Vector(linearHead) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Limited Steps (Linear, 10): " << (hasCycle_LimitedSteps(linearHead, 10) ? "Possible Cycle" : "No Cycle") << std::endl;


    // Remember to deallocate the memory, especially if you're running this
    // in an environment where memory management is critical (like an embedded system).
    // In a simple test like this, it's less crucial, but good practice.
    //  delete head;  // Not safe, because the list has a cycle.  Deleting 'head'
    //  would lead to a loop.  You'd need to break the cycle first, or
    //  delete nodes individually in a loop-aware way.
    //  For the linear list:
    delete linearHead;
    delete linearNode2;
    delete linearNode3;

    return 0;
}
