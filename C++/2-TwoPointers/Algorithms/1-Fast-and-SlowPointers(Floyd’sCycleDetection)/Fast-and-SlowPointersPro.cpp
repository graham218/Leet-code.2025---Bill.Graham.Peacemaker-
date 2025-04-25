#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory> // For smart pointers

// 1. Linked List Cycle Detection (Classic Floyd's Algorithm)
//
//   * Real-world application: Detecting loops in linked lists representing data structures, such as detecting if a linked list representing a queue or stack has been corrupted and has an infinite loop.
//   * Explanation: This is the classic application of the Floyd's algorithm.  A linked list node contains a value and a pointer to the next node.  A cycle exists if, starting from the head, you can reach the same node again by following the 'next' pointers.
//   * Time Complexity: O(n)
//   * Space Complexity: O(1)
//
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool hasCycle(ListNode* head) {
    if (!head || !head->next) {
        return false;
    }
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

// 2. Detecting Cycles in Object Relationships
//
//   * Real-world application: Detecting circular dependencies in object graphs, such as in a dependency injection container or a scene graph in a game engine.  This prevents infinite loops during object construction or updates.
//   * Explanation:  Imagine objects where one object holds a reference to another.  A cycle exists if object A references B, B references C, and C references A.  This can cause problems in garbage collection or object serialization.  We can simulate this with a simplified object structure.  We use unique_ptr to manage the memory.
//   * Time Complexity: O(n) - where n is the number of objects.
//   * Space Complexity: O(1)
//
struct ObjectNode {
    int id;
    std::unique_ptr<ObjectNode> reference; // Using unique_ptr to manage ownership
    ObjectNode(int i) : id(i), reference(nullptr) {}
};

bool hasCircularReference(ObjectNode* startNode) {
    if (!startNode) return false;

    ObjectNode* slow = startNode;
    ObjectNode* fast = startNode;

    while (fast && fast->reference) {
        slow = slow->reference.get(); // Use .get() to get the raw pointer
        fast = fast->reference->reference.get(); // Access nested reference, safely.
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

// 3. Finding the Start of a Cycle in a Linked List
//
//   * Real-world application:  Identifying the entry point of a loop in data structures, which is crucial for debugging memory leaks or data corruption issues in complex systems.
//   * Explanation:  This extends the basic cycle detection to find the *starting* node of the cycle.  This is important for understanding the cause of the cycle.
//   * Time Complexity: O(n)
//   * Space Complexity: O(1)
//
ListNode* findCycleStart(ListNode* head) {
    if (!head || !head->next) {
        return nullptr;
    }
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { // Cycle detected
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow; // Returns the start of the cycle
        }
    }
    return nullptr; // No cycle
}

// 4. Detecting Cycles in a Finite State Machine (FSM)
//
//  * Real-world application: Verifying the correctness of state transitions in a finite state machine, used in embedded systems, protocol design, or game development.  A cycle might indicate a state machine that gets stuck in a loop.
//  * Explanation: A finite state machine consists of states and transitions between them.  We can model states as nodes and transitions as pointers.  A cycle means the FSM can return to a previous state, which might be intended or a bug.
//  * Time Complexity: O(n), where n is the number of states visited.
//  * Space Complexity: O(1)
//
enum class FSMState {
    STATE_A,
    STATE_B,
    STATE_C,
    STATE_D,
    STATE_E,
    STATE_F
};

FSMState getNextState(FSMState currentState, std::vector<FSMState>& history) {
    history.push_back(currentState); // Keep track of visited states
    switch (currentState) {
        case FSMState::STATE_A: return FSMState::STATE_B;
        case FSMState::STATE_B: return FSMState::STATE_C;
        case FSMState::STATE_C: return FSMState::STATE_D;
        case FSMState::STATE_D: return FSMState::STATE_E;
        case FSMState::STATE_E: return FSMState::STATE_F;
        case FSMState::STATE_F: return FSMState::STATE_B; // Cycle back to B
        default: return FSMState::STATE_A;
    }
}

bool hasCycleFSM() {
    FSMState slow = FSMState::STATE_A;
    FSMState fast = FSMState::STATE_A;
    std::vector<FSMState> history;

    for (int i = 0; i < 10; ++i) { // Limit iterations to prevent infinite loop in case of error
        slow = getNextState(slow, history);
        fast = getNextState(getNextState(fast, history), history);
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

// 5. Detecting Cycles in Iterators
//
//   * Real-world application:  Analyzing iterative processes where the same state can be reached multiple times, such as in simulations or game AI. Detecting cycles can help identify repeating patterns or potential infinite loops in the logic.
//   * Explanation: This applies the concept to any process where you repeatedly apply a function to get the next state.  The "next state" is like the 'next' pointer in a linked list.  We simulate this with a simple integer iterator.
//   * Time Complexity: O(n), where n is the number of iterations.
//   * Space Complexity: O(1)
//
int nextValue(int currentValue, std::vector<int>& history) {
    history.push_back(currentValue);
    return (currentValue * 2 + 1) % 10; // Example iteration function
}

bool hasCycleIterator() {
    int slow = 0;
    int fast = 0;
    std::vector<int> history;
    for (int i = 0; i < 20; ++i) { // Limit iterations
        slow = nextValue(slow, history);
        fast = nextValue(nextValue(fast, history), history);
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

int main() {
    // 1. Linked List Cycle Detection
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = head->next; // Create a cycle
    std::cout << "Linked List has cycle: " << (hasCycle(head) ? "true" : "false") << std::endl; // Output: true

    // Clean up linked list
    ListNode* current = head;
    ListNode* next;
    while (current) {
        next = current->next;
        // IMPORTANT:  Do NOT delete the node that closes the cycle (head->next in this case) twice.
        if (current != head->next) {
           delete current;
        }
        current = next;
        if (current == head) break; // Stop at the start of the cycle.
    }
    //  delete head->next; //  <- DON'T DO THIS.  It was already deleted.
    head = nullptr; // Set head to nullptr to prevent dangling pointer

    // 2. Detecting Cycles in Object Relationships
    std::unique_ptr<ObjectNode> obj1 = std::make_unique<ObjectNode>(1);
    std::unique_ptr<ObjectNode> obj2 = std::make_unique<ObjectNode>(2);
    std::unique_ptr<ObjectNode> obj3 = std::make_unique<ObjectNode>(3);

    obj1->reference = std::move(obj2);
    obj2->reference = std::move(obj3);
    obj3->reference = std::move(obj1); // Create a cycle
    std::cout << "Object graph has circular reference: " << (hasCircularReference(obj1.get()) ? "true" : "false") << std::endl; // Output: true

    // 3. Finding the Start of a Cycle in a Linked List
     head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = head->next; // Create a cycle
    ListNode* cycleStart = findCycleStart(head);
    if (cycleStart) {
        std::cout << "Cycle starts at node with value: " << cycleStart->val << std::endl; // Output: 2
    } else {
        std::cout << "No cycle found" << std::endl;
    }
     // Clean up linked list
     current = head;
     while (current) {
        next = current->next;
        if (current != head->next){
             delete current;
        }
        current = next;
        if (current == head) break;
    }
    head = nullptr;

    // 4. Detecting Cycles in a Finite State Machine
    std::cout << "FSM has cycle: " << (hasCycleFSM() ? "true" : "false") << std::endl; // Output: true

    // 5. Detecting Cycles in Iterators
    std::cout << "Iterator has cycle: " << (hasCycleIterator() ? "true" : "false") << std::endl; // Output: true

    return 0;
}
