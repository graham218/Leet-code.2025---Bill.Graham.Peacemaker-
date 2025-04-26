#include <iostream>
#include <unordered_set>
#include <vector>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // Approach 1: Using a HashSet (unordered_set)
    // - Time Complexity: O(n), where n is the number of nodes in the list.
    // - Space Complexity: O(n), as we store each node in the set.
    bool hasCycle_hashset(ListNode *head) {
        std::unordered_set<ListNode*> visited;
        while (head) {
            if (visited.find(head) != visited.end()) {
                return true; // Cycle detected: node already in set
            }
            visited.insert(head); // Add the current node to the set
            head = head->next;     // Move to the next node
        }
        return false; // No cycle found: reached the end of the list
    }

    // Approach 2: Floyd's Cycle Detection Algorithm (Tortoise and Hare)
    // - Time Complexity: O(n), where n is the number of nodes in the list.
    // - Space Complexity: O(1), constant extra space.  This is the most efficient approach
    bool hasCycle_floyd(ListNode *head) {
        if (!head || !head->next) {
            return false; // Empty list or single node: no cycle possible
        }
        ListNode *slow = head;     // Slow pointer moves one step at a time
        ListNode *fast = head->next; // Fast pointer moves two steps at a time

        while (slow != fast) {
            if (!fast || !fast->next) {
                return false; // Fast pointer reached the end: no cycle
            }
            slow = slow->next;      // Slow pointer moves one step
            fast = fast->next->next; // Fast pointer moves two steps
        }
        return true; // Pointers met: cycle detected
    }

    // Approach 3: Using a Vector to store visited nodes
    // - Time Complexity: O(n), where n is the number of nodes.
    // - Space Complexity: O(n),  similar to the hashset approach.
    bool hasCycle_vector(ListNode *head) {
        std::vector<ListNode*> visited;
        while (head) {
            for (ListNode* node : visited) {
                if (node == head) {
                    return true;
                }
            }
            visited.push_back(head);
            head = head->next;
        }
        return false;
    }

    // Approach 4: Modifying the Linked List (Changing Node Values) - Destructive
    // - Time Complexity: O(n)
    // - Space Complexity: O(1)
    // - WARNING: This method modifies the original linked list, which might not be desirable.
    bool hasCycle_modify(ListNode *head) {
        int marker = 100001; // Choose a marker value outside the possible range of node values.  Problem constraints: -10^5 <= Node.val <= 10^5
        while (head) {
            if (head->val == marker) {
                return true; // Cycle detected: we've seen this node before
            }
            head->val = marker; // Mark the node as visited by changing its value
            head = head->next;
        }
        return false;
    }

     // Approach 5: Using a Stack (for demonstration, not ideal for cycle detection)
    // - Time Complexity: O(n)
    // - Space Complexity: O(n)
    // - Note: While stacks can be used in linked list problems, they are not the most efficient
    //       or intuitive choice for cycle detection.  This is included for completeness and
    //       to show a different data structure, but Floyd's algorithm is preferred.
    bool hasCycle_stack(ListNode *head) {
        std::vector<ListNode*> stack; // Using a vector as a stack
        while (head) {
            for (ListNode* node : stack) {
                if (node == head) {
                    return true;
                }
            }
            stack.push_back(head); // "Push" the node onto the stack
            head = head->next;
        }
        return false;
    }
};

// Helper function to create a linked list with a cycle (for testing)
ListNode* createLinkedListWithCycle(std::vector<int> values, int cycleStart) {
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    ListNode *cycleNode = nullptr; // Node where the cycle starts

    for (int i = 0; i < values.size(); ++i) {
        ListNode *newNode = new ListNode(values[i]);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        if (i == cycleStart) {
            cycleNode = newNode; // Mark the start of the cycle
        }
    }

    if (cycleStart >= 0 && cycleStart < values.size()) {
        tail->next = cycleNode; // Create the cycle
    }
    return head;
}

// Helper function to create a linked list without a cycle
ListNode* createLinkedList(std::vector<int> values) {
    ListNode *head = nullptr;
    ListNode *tail = nullptr;

    for (int val : values) {
        ListNode *newNode = new ListNode(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Helper function to print the linked list (for debugging) - prints up to 20 nodes
void printLinkedList(ListNode *head) {
    int count = 0;
    while (head && count < 20) { // Limit to prevent infinite loop if there's a cycle
        std::cout << head->val << " -> ";
        head = head->next;
        count++;
    }
    if (count >= 20) {
        std::cout << "...\n(Possible cycle, stopped printing after 20 nodes)";
    } else {
        std::cout << "nullptr" << std::endl;
    }
}

int main() {
    Solution sol;

    // Test case 1: No cycle
    ListNode *list1 = createLinkedList({1, 2, 3, 4, 5});
    std::cout << "List 1: ";
    printLinkedList(list1);
    std::cout << "Has Cycle (HashSet): " << sol.hasCycle_hashset(list1) << std::endl;
    std::cout << "Has Cycle (Floyd):   " << sol.hasCycle_floyd(list1) << std::endl;
    std::cout << "Has Cycle (Vector):  " << sol.hasCycle_vector(list1) << std::endl;
    std::cout << "Has Cycle (Modify):  " << sol.hasCycle_modify(list1) << std::endl;
    std::cout << "Has Cycle (Stack):   " << sol.hasCycle_stack(list1) << std::endl;
    std::cout << std::endl;

    // Test case 2: Cycle at the beginning
    ListNode *list2 = createLinkedListWithCycle({1, 2, 3, 4, 5}, 0);
    std::cout << "List 2 (Cycle at 0): ";
    printLinkedList(list2);
    std::cout << "Has Cycle (HashSet): " << sol.hasCycle_hashset(list2) << std::endl;
    std::cout << "Has Cycle (Floyd):   " << sol.hasCycle_floyd(list2) << std::endl;
    std::cout << "Has Cycle (Vector):  " << sol.hasCycle_vector(list2) << std::endl;
    //std::cout << "Has Cycle (Modify):  " << sol.hasCycle_modify(list2) << std::endl; // Caution: Modifies list
    std::cout << "Has Cycle (Stack):   " << sol.hasCycle_stack(list2) << std::endl;
    std::cout << std::endl;

    // Test case 3: Cycle in the middle
    ListNode *list3 = createLinkedListWithCycle({1, 2, 3, 4, 5}, 2);
    std::cout << "List 3 (Cycle at 2): ";
    printLinkedList(list3);
    std::cout << "Has Cycle (HashSet): " << sol.hasCycle_hashset(list3) << std::endl;
    std::cout << "Has Cycle (Floyd):   " << sol.hasCycle_floyd(list3) << std::endl;
    std::cout << "Has Cycle (Vector):  " << sol.hasCycle_vector(list3) << std::endl;
    //std::cout << "Has Cycle (Modify):  " << sol.hasCycle_modify(list3) << std::endl;  // Caution: Modifies list
    std::cout << "Has Cycle (Stack):   " << sol.hasCycle_stack(list3) << std::endl;
    std::cout << std::endl;

     // Test case 4: Single node with no cycle
    ListNode *list4 = new ListNode(1);
    std::cout << "List 4 (Single Node): ";
    printLinkedList(list4);
    std::cout << "Has Cycle (HashSet): " << sol.hasCycle_hashset(list4) << std::endl;
    std::cout << "Has Cycle (Floyd):   " << sol.hasCycle_floyd(list4) << std::endl;
    std::cout << "Has Cycle (Vector):  " << sol.hasCycle_vector(list4) << std::endl;
    std::cout << "Has Cycle (Modify):  " << sol.hasCycle_modify(list4) << std::endl;
    std::cout << "Has Cycle (Stack):   " << sol.hasCycle_stack(list4) << std::endl;
    std::cout << std::endl;

    // Test case 5: Empty list
    ListNode *list5 = nullptr;
    std::cout << "List 5 (Empty): ";
    printLinkedList(list5);
    std::cout << "Has Cycle (HashSet): " << sol.hasCycle_hashset(list5) << std::endl;
    std::cout << "Has Cycle (Floyd):   " << sol.hasCycle_floyd(list5) << std::endl;
    std::cout << "Has Cycle (Vector):  " << sol.hasCycle_vector(list5) << std::endl;
    std::cout << "Has Cycle (Modify):  " << sol.hasCycle_modify(list5) << std::endl;
    std::cout << "Has Cycle (Stack):   " << sol.hasCycle_stack(list5) << std::endl;
    std::cout << std::endl;

    // Remember to free the allocated memory to prevent memory leaks (important in C++)
    //  In a real application, you'd want to wrap this in a function or use smart pointers.
    delete list1;  // No cycle, so just delete the single head.
    ListNode* current2 = list2; //list2 has cycle
    ListNode* next2 = nullptr;
    std::unordered_set<ListNode*> visited2;
    while(current2 && visited2.find(current2) == visited2.end()){
        visited2.insert(current2);
        next2 = current2->next;
        current2->next = nullptr; // Break the cycle to allow safe deletion
        delete current2;
        current2 = next2;
    }
    delete current2;

     ListNode* current3 = list3; //list3 has cycle
    ListNode* next3 = nullptr;
    std::unordered_set<ListNode*> visited3;
    while(current3 && visited3.find(current3) == visited3.end()){
        visited3.insert(current3);
        next3 = current3->next;
        current3->next = nullptr; // Break the cycle to allow safe deletion
        delete current3;
        current3 = next3;
    }
    delete current3;
    delete list4;
    // list5 is nullptr, so no need to delete.

    return 0;
}
