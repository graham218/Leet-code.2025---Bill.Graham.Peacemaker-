#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <memory> // For smart pointers

// Definition for singly-linked list.  Using a struct for simplicity and compatibility.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Function to print the linked list (for testing)
void printList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        std::cout << current->val << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Function to create a linked list from a vector (for testing)
ListNode* createList(const std::vector<int>& vec) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int val : vec) {
        ListNode* newNode = new ListNode(val);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Function to delete a linked list (to prevent memory leaks)
void deleteList(ListNode* head) {
    ListNode* current = head;
    ListNode* next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

// Approach 1: Iterative Merge (Most Common, Efficient)
// Time Complexity: O(m + n), Space Complexity: O(1) - Iterative, constant extra space
ListNode* mergeTwoListsIterative(ListNode* list1, ListNode* list2) {
    // Create a dummy node to simplify the logic.  This avoids needing to check
    // for empty lists as special cases within the main loop.
    ListNode dummy(0);
    ListNode* tail = &dummy; // Use a pointer to the tail of the merged list

    while (list1 != nullptr && list2 != nullptr) {
        if (list1->val <= list2->val) {
            tail->next = list1; // Connect the next node of result
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next; // Move the tail pointer forward
    }

    // Append the remaining nodes from either list (if any).  Only one of
    // these two 'while' loops will actually execute.
    if (list1 != nullptr) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }

    return dummy.next; // Return the head of the merged list (skipping the dummy)
}

// Approach 2: Recursive Merge
// Time Complexity: O(m + n), Space Complexity: O(m + n) - Recursive call stack
ListNode* mergeTwoListsRecursive(ListNode* list1, ListNode* list2) {
    // Base cases: If either list is empty, return the other list.
    if (list1 == nullptr) {
        return list2;
    }
    if (list2 == nullptr) {
        return list1;
    }

    // Recursive step: Compare the heads of the lists and merge accordingly.
    if (list1->val <= list2->val) {
        list1->next = mergeTwoListsRecursive(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeTwoListsRecursive(list1, list2->next);
        return list2;
    }
}

// Approach 3: Using a Vector (Not in-place, Simple)
// Time Complexity: O(m + n + k log k), Space Complexity: O(m + n) + O(k), where k is (m+n)
ListNode* mergeTwoListsVector(ListNode* list1, ListNode* list2) {
    std::vector<int> mergedValues;
    // 1. Copy all values from both lists into a vector.
    while (list1 != nullptr) {
        mergedValues.push_back(list1->val);
        list1 = list1->next;
    }
    while (list2 != nullptr) {
        mergedValues.push_back(list2->val);
        list2 = list2->next;
    }

    // 2. Sort the vector.  std::sort is generally implemented as an IntroSort
    //    (a hybrid of quicksort, heapsort, and insertion sort), giving O(n log n)
    //    on average and in the worst case.
    std::sort(mergedValues.begin(), mergedValues.end());

    // 3. Create a new linked list from the sorted vector.
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int val : mergedValues) {
        ListNode* newNode = new ListNode(val);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Approach 4: Using std::list (for practice with STL containers)
// Time Complexity: O(m + n), Space Complexity: O(m + n)
ListNode* mergeTwoListsSTLList(ListNode* list1, ListNode* list2) {
    std::list<int> mergedList;

    // Copy elements from the linked lists to the std::list.
    while (list1) {
        mergedList.push_back(list1->val);
        list1 = list1->next;
    }
    while (list2) {
        mergedList.push_back(list2->val);
        list2 = list2->next;
    }
    // Sort the merged list
    mergedList.sort();

    // Create the result linked list.
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int val : mergedList) {
        ListNode* newNode = new ListNode(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Approach 5: In-place Merge with std::list (Simulating In-Place)
// Time Complexity: O(m+n), Space Complexity: O(max(m,n))  - Uses list, but tries to minimize extra allocation.
ListNode* mergeTwoListsInPlaceSTLList(ListNode* list1, ListNode* list2) {
    std::list<int> mergedList;

    // Copy the elements from both lists into a std::list
     while (list1) {
        mergedList.push_back(list1->val);
        list1 = list1->next;
    }
    while (list2) {
        mergedList.push_back(list2->val);
        list2 = list2->next;
    }
    mergedList.sort();

    // Create new linked list.
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
     for (int val : mergedList) {
        ListNode* newNode = new ListNode(val);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

int main() {
    // Example usage:
    std::vector<int> vec1 = {1, 2, 4};
    std::vector<int> vec2 = {1, 3, 4};

    ListNode* list1 = createList(vec1);
    ListNode* list2 = createList(vec2);

    std::cout << "List 1: ";
    printList(list1);
    std::cout << "List 2: ";
    printList(list2);

    // Approach 1: Iterative Merge
    ListNode* mergedListIterative = mergeTwoListsIterative(list1, list2);
    std::cout << "Merged (Iterative): ";
    printList(mergedListIterative);
    deleteList(mergedListIterative); // Clean up the list

    // Approach 2: Recursive Merge
    ListNode* mergedListRecursive = mergeTwoListsRecursive(list1, list2);
    std::cout << "Merged (Recursive): ";
    printList(mergedListRecursive);
    deleteList(mergedListRecursive);

    // Approach 3: Using a Vector
    ListNode* mergedListVector = mergeTwoListsVector(list1, list2);
    std::cout << "Merged (Vector): ";
    printList(mergedListVector);
    deleteList(mergedListVector);

    // Approach 4: Using std::list
    ListNode* mergedListSTLList = mergeTwoListsSTLList(list1, list2);
    std::cout << "Merged (STL List): ";
    printList(mergedListSTLList);
    deleteList(mergedListSTLList);

     // Approach 5: In-place Merge with std::list
    ListNode* mergedListInPlaceSTLList = mergeTwoListsInPlaceSTLList(list1, list2);
    std::cout << "Merged (In-place STL List): ";
    printList(mergedListInPlaceSTLList);
    deleteList(mergedListInPlaceSTLList);

    // Clean up the original lists (important!)
    deleteList(list1);
    deleteList(list2);

    return 0;
}
