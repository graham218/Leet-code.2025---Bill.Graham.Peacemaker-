#include <iostream>
#include <vector>
#include <algorithm> // Required for std::merge, std::inplace_merge, std::lower_bound

// Definition for singly-linked list.  (Same as provided, for completeness)
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Function to print the linked list (Same as provided, for easy verification)
void printList(ListNode* head) {
    while (head) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Function to convert a vector to a linked list (for easier testing)
ListNode* vectorToList(const std::vector<int>& vec) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int val : vec) {
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

// Function to convert a linked list to a vector
std::vector<int> listToVector(ListNode* head) {
    std::vector<int> vec;
    while (head) {
        vec.push_back(head->val);
        head = head->next;
    }
    return vec;
}

// Approach 1: Iterative Merge (Standard Merge, no binary search used)
// Time Complexity: O(m + n), where m and n are lengths of the lists
// Space Complexity: O(m + n)
ListNode* mergeTwoLists_Iterative(ListNode* list1, ListNode* list2) {
    ListNode dummy(0); // Dummy node to simplify head handling
    ListNode* tail = &dummy;

    while (list1 && list2) {
        if (list1->val < list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    // Append the remaining elements of either list (only one will have remaining)
    tail->next = list1 ? list1 : list2;
    return dummy.next;
}

// Approach 2: Recursive Merge (Standard Recursive Merge, no binary search)
// Time Complexity: O(m + n)
// Space Complexity: O(m + n)  (due to recursive call stack)
ListNode* mergeTwoLists_Recursive(ListNode* list1, ListNode* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    if (list1->val < list2->val) {
        list1->next = mergeTwoLists_Recursive(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeTwoLists_Recursive(list1, list2->next);
        return list2;
    }
}

// Approach 3: Merge with Vector and Sort (Not using Binary Search for the merge logic itself)
// Time Complexity: O((m+n) log (m+n))  due to sorting
// Space Complexity: O(m + n)
ListNode* mergeTwoLists_VectorSort(ListNode* list1, ListNode* list2) {
    std::vector<int> merged;
    while (list1) {
        merged.push_back(list1->val);
        list1 = list1->next;
    }
    while (list2) {
        merged.push_back(list2->val);
        list2 = list2->next;
    }
    std::sort(merged.begin(), merged.end()); // Sort the combined vector

    // Convert the sorted vector back to a linked list
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int val : merged) {
        tail->next = new ListNode(val);
        tail = tail->next;
    }
    return dummy.next;
}

// Approach 4:  Using std::merge (STL Algorithm) -  NOT Binary Search *internally*
// Time Complexity: O(m + n)
// Space Complexity: O(m + n) (for the result list)
ListNode* mergeTwoLists_STLMerge(ListNode* list1, ListNode* list2) {
    std::vector<int> vec1 = listToVector(list1);
    std::vector<int> vec2 = listToVector(list2);
    std::vector<int> merged(vec1.size() + vec2.size()); // Pre-allocate for efficiency

    std::merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), merged.begin());

    return vectorToList(merged); //convert the vector to list
}

// Approach 5: In-place Merge with Binary Search (More complex, modifies lists directly)
// Time Complexity:  O(m log n)  if m is the length of list1, and n is the length of list2
// Space Complexity: O(1) -  In-place
ListNode* mergeTwoLists_InPlaceBinarySearch(ListNode* list1, ListNode* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    // Ensure list1 is the shorter list (for efficiency of binary search)
    if (list1->val > list2->val) {
        std::swap(list1, list2);
    }

    ListNode* head = list1; // Keep track of the head
    ListNode* prev1 = nullptr;

    while (list1 && list2) {
        // Binary search in list2 to find the insertion point for list1's current value
        ListNode* low = list2;
        ListNode* high = nullptr; // Initialize high to null
        ListNode* insertPos = nullptr;

        // Find the end of list2.  This is necessary to make the binary search work correctly.
        while(high && high->next) {
            high = high->next;
        }

        while (low) {
            ListNode* mid = low;
             if(low->next){
                ListNode* fast = low->next;
                while(fast && fast->next){
                    mid = mid->next;
                    fast = fast->next->next;
                }
             }

            if (list1->val < mid->val) {
                high = mid; //narrow high
                if(low == mid){
                    break;
                }
            } else if (list1->val > mid->val) {
                low = mid->next;  //narrow low
            } else {
                insertPos = mid;
                break;
            }
        }
        if (!low) {
            insertPos = high;
        }


        if (!insertPos) {
             // list1->val is greater than the remaining elements in list2
            prev1 = list1;
            list1 = list1->next;
            continue;
        }

        // Insert list1's node into list2
        if(prev1){
             prev1->next = insertPos->next;
        }
        ListNode* temp = list1->next;
        list1->next = insertPos->next;
        insertPos->next = list1;
        list1 = temp;
        prev1 = insertPos;
    }
    return head;
}

int main() {
    // Example usage and testing
    std::vector<int> vec1 = {1, 3, 5, 7, 9};
    std::vector<int> vec2 = {2, 4, 6, 8, 10};
    ListNode* list1 = vectorToList(vec1);
    ListNode* list2 = vectorToList(vec2);

    std::cout << "List 1: ";
    printList(list1);
    std::cout << "List 2: ";
    printList(list2);

    std::cout << "\nApproach 1: Iterative Merge" << std::endl;
    ListNode* merged1 = mergeTwoLists_Iterative(list1, list2);
    printList(merged1);
    // Remember to free the allocated memory for the linked list to prevent memory leaks.
    while (merged1) {
        ListNode* temp = merged1;
        merged1 = merged1->next;
        delete temp;
    }
    list1 = vectorToList(vec1);  //reset
    list2 = vectorToList(vec2);  //reset


    std::cout << "\nApproach 2: Recursive Merge" << std::endl;
    ListNode* merged2 = mergeTwoLists_Recursive(list1, list2);
    printList(merged2);
     while (merged2) {
        ListNode* temp = merged2;
        merged2 = merged2->next;
        delete temp;
    }
    list1 = vectorToList(vec1);  //reset
    list2 = vectorToList(vec2);  //reset

    std::cout << "\nApproach 3: Merge with Vector and Sort" << std::endl;
    ListNode* merged3 = mergeTwoLists_VectorSort(list1, list2);
    printList(merged3);
    while (merged3) {
        ListNode* temp = merged3;
        merged3 = merged3->next;
        delete temp;
    }
    list1 = vectorToList(vec1);  //reset
    list2 = vectorToList(vec2);  //reset

    std::cout << "\nApproach 4: Using std::merge" << std::endl;
    ListNode* merged4 = mergeTwoLists_STLMerge(list1, list2);
    printList(merged4);
    while (merged4) {
        ListNode* temp = merged4;
        merged4 = merged4->next;
        delete temp;
    }
     list1 = vectorToList(vec1);  //reset
    list2 = vectorToList(vec2);  //reset

    std::cout << "\nApproach 5: In-place Merge with Binary Search" << std::endl;
    ListNode* merged5 = mergeTwoLists_InPlaceBinarySearch(list1, list2);
    printList(merged5);
     while (merged5) {
        ListNode* temp = merged5;
        merged5 = merged5->next;
        delete temp;
    }

    return 0;
}
