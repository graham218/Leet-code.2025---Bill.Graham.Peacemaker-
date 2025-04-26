#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory> // For smart pointers

// Definition for singly-linked list.  Using a struct for simplicity and compatibility.
struct ListNode {
    int val;
    ListNode *next;
    // Constructor for convenience
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to create a linked list from a vector (useful for testing)
ListNode* createLinkedList(const std::vector<int>& nums) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int num : nums) {
        ListNode* newNode = new ListNode(num);
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

// Function to print a linked list (useful for testing)
void printLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current) {
        std::cout << current->val << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Function to free a linked list (to prevent memory leaks)
void freeLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}

// 1. Iterative Approach (Most Common, Efficient)
//   - Time Complexity: O(m+n), where m and n are the lengths of the lists.
//   - Space Complexity: O(1) - constant extra space.
//   - Real-world use case:  Merging sorted result sets from two database queries.  Very efficient and commonly used.
ListNode* mergeTwoListsIterative(ListNode* l1, ListNode* l2) {
    // Create a dummy node to simplify the logic.  This avoids special cases
    // for handling the head of the merged list.
    ListNode dummy(0);
    ListNode* tail = &dummy; // Use a pointer to the tail of the merged list.

    // Iterate while both lists have elements.
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1; // Add the smaller element from l1 to the merged list.
            l1 = l1->next;      // Move to the next node in l1.
        } else {
            tail->next = l2; // Add the smaller element from l2 to the merged list.
            l2 = l2->next;      // Move to the next node in l2.
        }
        tail = tail->next; // Move the tail pointer to the newly added node.
    }

    // Append the remaining elements of either list (if any).  Only one of
    // these two 'while' loops will execute.
    if (l1) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    return dummy.next; // Return the head of the merged list (excluding the dummy node).
}

// 2. Recursive Approach
//   - Time Complexity: O(m+n)
//   - Space Complexity: O(m+n) - due to the recursive call stack.
//   - Real-world use case:  Could be used in a divide-and-conquer algorithm, though
//     the iterative approach is usually preferred for its better space efficiency.
ListNode* mergeTwoListsRecursive(ListNode* l1, ListNode* l2) {
    // Base cases: if either list is empty, return the other list.
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->val <= l2->val) {
        // Recursively merge the rest of l1 with l2.
        l1->next = mergeTwoListsRecursive(l1->next, l2);
        return l1; // Return the current node (l1) as it's the smaller.
    } else {
        // Recursively merge l1 with the rest of l2.
        l2->next = mergeTwoListsRecursive(l1, l2->next);
        return l2; // Return the current node (l2) as it's the smaller.
    }
}

// 3. Using a Vector and std::merge (STL Approach)
//   - Time Complexity: O(m+n)
//   - Space Complexity: O(m+n) - for the vector.
//   - Real-world use case:  Good for one-off merging tasks or when you need the
//     merged result in a contiguous memory block (e.g., for further processing
//     with other STL algorithms).  Not ideal if you *must* maintain a linked list.
ListNode* mergeTwoListsVector(ListNode* l1, ListNode* l2) {
    std::vector<int> mergedVector;
    // Iterate through the linked lists, adding elements to the vector.
    while (l1) {
        mergedVector.push_back(l1->val);
        l1 = l1->next;
    }
    while (l2) {
        mergedVector.push_back(l2->val);
        l2 = l2->next;
    }
    // Sort the vector.  std::sort is generally very efficient (often introsort).
    std::sort(mergedVector.begin(), mergedVector.end());

    // Alternatively, use std::merge:
    // std::vector<int> mergedVector(length of l1 + length of l2); //Pre-allocate, if size known
    // std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), mergedVector.begin());

    // Create a new linked list from the sorted vector.
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int val : mergedVector) {
        ListNode* newNode = new ListNode(val);
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

// 4. Using std::list and std::merge (STL List Approach)
//   - Time Complexity: O(m+n)
//   - Space Complexity: O(m+n) - for the lists.
//   - Real-world use case:  If you're already working with `std::list` in your project
//     (which is a doubly-linked list), this approach can be convenient.  `std::list`
//     has its own `merge` method.
ListNode* mergeTwoListsSTLList(ListNode* l1, ListNode* l2) {
    std::list<int> list1, list2, mergedList;

    // Copy the values from the input linked lists to std::list objects.
    while (l1) {
        list1.push_back(l1->val);
        l1 = l1->next;
    }
    while (l2) {
        list2.push_back(l2->val);
        l2 = l2->next;
    }
    //list1.sort(); //Ensure lists are sorted.  The input *should* be sorted, but good practice.
    //list2.sort();

     // Merge the two sorted lists using the std::list::merge() method.  This
     // method is specifically designed for merging sorted lists, and it
     // maintains the sorted order.  It's an in-place merge, meaning elements
     // are moved from list2 into list1.  After the merge, list2 will be empty.
    list1.merge(list2); // Merges list2 into list1, list2 becomes empty.
    mergedList = list1;

    // Create a new linked list from the merged std::list.
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int val : mergedList) {
        ListNode* newNode = new ListNode(val);
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

// 5. In-Place Merge (with modification of input lists, for specific scenarios)
//   - Time Complexity: O(m+n)
//   - Space Complexity: O(1) -  *if* you are allowed to modify the input lists.
//   - Real-world use case:  This is a more advanced technique.  It's useful in
//     memory-constrained environments where you cannot afford the extra space
//     for a new list.  **Important:** This modifies the original linked lists.
//     Use with caution!  This approach is similar to the iterative, but modifies the lists.
ListNode* mergeTwoListsInPlace(ListNode* l1, ListNode* l2) {
     if (!l1) return l2;
     if (!l2) return l1;

    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    // Determine the head of the merged list.
    if (l1->val <= l2->val) {
        head = l1;
        tail = l1;
        l1 = l1->next;
    } else {
        head = l2;
        tail = l2;
        l2 = l2->next;
    }

    // Merge the remaining nodes.
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
            tail = tail->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
            tail = tail->next;
        }
    }

    // Append the remaining nodes.
    if (l1) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    return head;
}

int main() {
    // Example usage:
    std::vector<int> nums1 = {1, 2, 4, 7, 9};
    std::vector<int> nums2 = {1, 3, 4, 6, 8, 10};

    ListNode* list1 = createLinkedList(nums1);
    ListNode* list2 = createLinkedList(nums2);

    std::cout << "List 1: ";
    printLinkedList(list1);
    std::cout << "List 2: ";
    printLinkedList(list2);
    std::cout << std::endl;

    // 1. Iterative Merge
    ListNode* mergedListIterative = mergeTwoListsIterative(list1, list2);
    std::cout << "Merged (Iterative): ";
    printLinkedList(mergedListIterative);
    freeLinkedList(mergedListIterative); // Clean up the allocated memory.
    list1 = createLinkedList(nums1);  //Recreate lists
    list2 = createLinkedList(nums2);

    // 2. Recursive Merge
    ListNode* mergedListRecursive = mergeTwoListsRecursive(list1, list2);
    std::cout << "Merged (Recursive): ";
    printLinkedList(mergedListRecursive);
    freeLinkedList(mergedListRecursive);
    list1 = createLinkedList(nums1);
    list2 = createLinkedList(nums2);

    // 3. Vector Merge
    ListNode* mergedListVector = mergeTwoListsVector(list1, list2);
    std::cout << "Merged (Vector): ";
    printLinkedList(mergedListVector);
    freeLinkedList(mergedListVector);
     list1 = createLinkedList(nums1);
    list2 = createLinkedList(nums2);

    // 4. STL List Merge
    ListNode* mergedListSTLList = mergeTwoListsSTLList(list1, list2);
    std::cout << "Merged (STL List): ";
    printLinkedList(mergedListSTLList);
    freeLinkedList(mergedListSTLList);
    list1 = createLinkedList(nums1);
    list2 = createLinkedList(nums2);

    // 5. In-Place Merge
    ListNode* mergedListInPlace = mergeTwoListsInPlace(list1, list2);
    std::cout << "Merged (In-Place): ";
    printLinkedList(mergedListInPlace);
    //The original lists are modified in-place merge.
    std::cout << "List 1 (Modified): ";
    printLinkedList(list1);
    std::cout << "List 2 (Modified): ";
    printLinkedList(list2);
    freeLinkedList(list1);  // Free, although they were modified.
    //freeLinkedList(list2); // Don't double free.  l2 is now empty after merge.
    //list1 = createLinkedList(nums1); // No need to recreate.

    return 0;
}
