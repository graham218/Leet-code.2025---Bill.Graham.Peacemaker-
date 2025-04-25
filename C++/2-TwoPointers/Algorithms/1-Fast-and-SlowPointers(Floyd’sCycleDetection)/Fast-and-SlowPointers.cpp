#include <iostream>
#include <unordered_set>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Helper function to create a linked list from a vector
ListNode* createLinkedList(const std::vector<int>& values, int cyclePos = -1) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    ListNode* cycleNode = nullptr;

    for (int i = 0; i < values.size(); ++i) {
        ListNode* newNode = new ListNode(values[i]);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        if (i == cyclePos) {
            cycleNode = newNode;
        }
    }
    if (cyclePos != -1) {
        tail->next = cycleNode; // Create the cycle
    }
    return head;
}

// Helper function to print the linked list
void printLinkedList(ListNode* head) {
    ListNode* current = head;
    std::unordered_set<ListNode*> visited;
    while (current) {
        if (visited.find(current) != visited.end()) {
            std::cout << "Cycle detected, stopping here." << std::endl;
            break;
        }
        visited.insert(current);
        std::cout << current->val << " -> ";
        current = current->next;
    }
    if (current == nullptr)
        std::cout << "nullptr" << std::endl;
}

// Helper function to free the linked list
void freeLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

// 1. Using a hash set to detect cycles.
//   - Time Complexity: O(n), where n is the number of nodes in the list.
//   - Space Complexity: O(n), for the hash set.
bool hasCycleUsingHashSet(ListNode *head) {
    std::unordered_set<ListNode*> visitedNodes;
    ListNode* current = head;
    while (current) {
        if (visitedNodes.find(current) != visitedNodes.end()) {
            return true; // Cycle detected: current node is already in the set.
        }
        visitedNodes.insert(current); // Add the current node to the set.
        current = current->next;
    }
    return false; // No cycle found: reached the end of the list.
}

// 2. Floyd's Cycle Detection Algorithm (Fast and Slow Pointers).
//   - Time Complexity: O(n), where n is the number of nodes in the list.
//   - Space Complexity: O(1), constant extra space.
bool hasCycleFloyd(ListNode *head) {
    if (!head || !head->next) {
        return false; // No cycle if the list is empty or has only one node.
    }
    ListNode* slow = head;
    ListNode* fast = head->next; // Start fast pointer one step ahead.

    while (fast && fast->next) {
        if (slow == fast) {
            return true; // Cycle detected: fast and slow pointers meet.
        }
        slow = slow->next;         // Slow pointer moves one step.
        fast = fast->next->next; // Fast pointer moves two steps.
    }
    return false; // No cycle found: fast pointer reached the end of the list.
}

// 3. Modifying the list nodes (Not recommended for read-only lists).
//   - Time Complexity: O(n), where n is the number of nodes in the list.
//   - Space Complexity: O(1), constant extra space.
bool hasCycleModifyingList(ListNode *head) {
    ListNode* current = head;
    ListNode* temp = new ListNode(0); // Use a dummy node as a marker.
    while (current) {
        if (current->next == temp) {
            delete temp;
            return true; // Cycle detected: next pointer points to the marker.
        }
        ListNode* next = current->next;
        current->next = temp; // Change next pointer to the marker.
        current = next;
    }
    delete temp;
    return false; // No cycle found: reached the end of the list.
}

// 4. Using a vector to store visited nodes (Similar to HashSet, but uses vector).
//   - Time Complexity: O(n^2) in the worst case, where n is the number of nodes.
//   - Space Complexity: O(n), for the vector.
bool hasCycleUsingVector(ListNode *head) {
    std::vector<ListNode*> visitedNodes;
    ListNode* current = head;
    while (current) {
        for (ListNode* node : visitedNodes) {
            if (node == current) {
                return true; // Cycle detected: current node is in the vector.
            }
        }
        visitedNodes.push_back(current); // Add the current node to the vector.
        current = current->next;
    }
    return false; // No cycle found: reached the end of the list.
}

// 5.  Check for cycle by comparing the address of the nodes.
//    - Time complexity: O(n^2)
//    - Space complexity: O(1)
bool hasCycleCompareAddress(ListNode* head) {
    if (!head) return false;

    ListNode* current = head;
    while (current) {
        ListNode* runner = head;
        while (runner != current) {
            if (runner == nullptr)
                break;
            if (runner->next == current)
                return true;
            runner = runner->next;
        }
        current = current->next;
    }
    return false;
}

int main() {
    // Test cases with and without cycles.
    std::vector<int> list1 = {1, 2, 3, 4, 5};
    std::vector<int> list2 = {1, 2, 3, 4, 5};
    std::vector<int> list3 = {1};
    std::vector<int> list4 = {};
    std::vector<int> list5 = {1, 2};

    ListNode* head1 = createLinkedList(list1);             // No cycle
    ListNode* head2 = createLinkedList(list2, 2);    // Cycle at index 2 (3)
    ListNode* head3 = createLinkedList(list3, 0);    // Cycle at index 0
    ListNode* head4 = createLinkedList(list4);           // Empty List
    ListNode* head5 = createLinkedList(list5, 1);

    std::cout << "Test Case 1: No Cycle" << std::endl;
    std::cout << "List: ";
    printLinkedList(head1);
    std::cout << "HashSet: " << (hasCycleUsingHashSet(head1) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Floyd's: " << (hasCycleFloyd(head1) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Modifying List: " << (hasCycleModifyingList(head1) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Vector: " << (hasCycleUsingVector(head1) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Compare Address: " << (hasCycleCompareAddress(head1) ? "Cycle Detected" : "No Cycle") << std::endl;
    freeLinkedList(head1);

    std::cout << "\nTest Case 2: Cycle at index 2" << std::endl;
    std::cout << "List: ";
    printLinkedList(head2);
    std::cout << "HashSet: " << (hasCycleUsingHashSet(head2) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Floyd's: " << (hasCycleFloyd(head2) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Modifying List: " << (hasCycleModifyingList(head2) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Vector: " << (hasCycleUsingVector(head2) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Compare Address: " << (hasCycleCompareAddress(head2) ? "Cycle Detected" : "No Cycle") << std::endl;
    freeLinkedList(head2);

    std::cout << "\nTest Case 3: Cycle at head" << std::endl;
    std::cout << "List: ";
    printLinkedList(head3);
    std::cout << "HashSet: " << (hasCycleUsingHashSet(head3) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Floyd's: " << (hasCycleFloyd(head3) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Modifying List: " << (hasCycleModifyingList(head3) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Vector: " << (hasCycleUsingVector(head3) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Compare Address: " << (hasCycleCompareAddress(head3) ? "Cycle Detected" : "No Cycle") << std::endl;
    freeLinkedList(head3);

    std::cout << "\nTest Case 4: Empty List" << std::endl;
    std::cout << "List: ";
    printLinkedList(head4);
    std::cout << "HashSet: " << (hasCycleUsingHashSet(head4) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Floyd's: " << (hasCycleFloyd(head4) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Modifying List: " << (hasCycleModifyingList(head4) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Vector: " << (hasCycleUsingVector(head4) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Compare Address: " << (hasCycleCompareAddress(head4) ? "Cycle Detected" : "No Cycle") << std::endl;
    freeLinkedList(head4);

    std::cout << "\nTest Case 5: Cycle at tail" << std::endl;
    std::cout << "List: ";
    printLinkedList(head5);
    std::cout << "HashSet: " << (hasCycleUsingHashSet(head5) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Floyd's: " << (hasCycleFloyd(head5) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Modifying List: " << (hasCycleModifyingList(head5) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Vector: " << (hasCycleUsingVector(head5) ? "Cycle Detected" : "No Cycle") << std::endl;
    std::cout << "Compare Address: " << (hasCycleCompareAddress(head5) ? "Cycle Detected" : "No Cycle") << std::endl;
    freeLinkedList(head5);

    return 0;
}
