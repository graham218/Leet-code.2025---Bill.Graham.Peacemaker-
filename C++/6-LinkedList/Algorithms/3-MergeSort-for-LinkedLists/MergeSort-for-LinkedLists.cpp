// Title: Merge Sort for Linked Lists - 5 Different Approaches (C++)

#include <iostream>
using namespace std;

// Define a basic linked list node
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

//---------------------------------------------
// Approach 1: Classic Recursive Merge Sort
//---------------------------------------------
class Solution1 {
public:
    // Main function to sort the linked list
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        // Find the middle of the list
        ListNode* mid = getMiddle(head);
        ListNode* left = head;
        ListNode* right = mid->next;
        mid->next = nullptr;

        // Recursively sort the two halves
        left = sortList(left);
        right = sortList(right);

        // Merge the sorted halves
        return merge(left, right);
    }

private:
    // Function to find the middle of the list
    ListNode* getMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // Function to merge two sorted lists
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
};

//---------------------------------------------
// Approach 2: Bottom-up Merge Sort (Iterative)
//---------------------------------------------
class Solution2 {
public:
    ListNode* sortList(ListNode* head) {
        if (!head) return head;

        // Get list length
        int length = 0;
        ListNode* node = head;
        while (node) {
            length++;
            node = node->next;
        }

        ListNode dummy(0);
        dummy.next = head;

        // Start merging from size 1, 2, 4, 8...
        for (int size = 1; size < length; size <<= 1) {
            ListNode* prev = &dummy;
            ListNode* curr = dummy.next;

            while (curr) {
                ListNode* left = curr;
                ListNode* right = split(left, size);
                curr = split(right, size);
                prev = merge(left, right, prev);
            }
        }
        return dummy.next;
    }

private:
    // Split the list after "size" nodes and return the next part
    ListNode* split(ListNode* head, int size) {
        for (int i = 1; head && i < size; i++) {
            head = head->next;
        }
        if (!head) return nullptr;
        ListNode* second = head->next;
        head->next = nullptr;
        return second;
    }

    // Merge two lists and attach to prev
    ListNode* merge(ListNode* l1, ListNode* l2, ListNode* prev) {
        ListNode* curr = prev;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        curr->next = l1 ? l1 : l2;
        while (curr->next) curr = curr->next;
        return curr;
    }
};

//---------------------------------------------
// Approach 3: Merge Sort with Memory Optimization
//---------------------------------------------
class Solution3 {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* mid = getMiddle(head);
        ListNode* right = mid->next;
        mid->next = nullptr;

        // Sort without extra dummy nodes
        return merge(sortList(head), sortList(right));
    }

private:
    ListNode* getMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* merge(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;

        if (l1->val < l2->val) {
            l1->next = merge(l1->next, l2);
            return l1;
        } else {
            l2->next = merge(l1, l2->next);
            return l2;
        }
    }
};

//---------------------------------------------
// Approach 4: Merge Sort with Custom Comparator (for extension)
//---------------------------------------------
class Solution4 {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* mid = getMiddle(head);
        ListNode* right = mid->next;
        mid->next = nullptr;

        return merge(sortList(head), sortList(right));
    }

private:
    ListNode* getMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // Custom comparator for future flexibility
    bool compare(int a, int b) {
        return a < b;
    }

    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 && l2) {
            if (compare(l1->val, l2->val)) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
};

//---------------------------------------------
// Approach 5: In-Place Merge Sort without Using Extra Space for Merge
//---------------------------------------------
class Solution5 {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* mid = findMiddle(head);
        ListNode* left = head;
        ListNode* right = mid->next;
        mid->next = nullptr;

        left = sortList(left);
        right = sortList(right);

        return mergeInPlace(left, right);
    }

private:
    ListNode* findMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* mergeInPlace(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;

        ListNode* head = nullptr;

        if (l1->val < l2->val) {
            head = l1;
            l1 = l1->next;
        } else {
            head = l2;
            l2 = l2->next;
        }

        ListNode* tail = head;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        tail->next = l1 ? l1 : l2;

        return head;
    }
};

//---------------------------------------------
// Helper functions to print and build linked lists (for testing)
//---------------------------------------------
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "NULL\n";
}

ListNode* buildList(initializer_list<int> vals) {
    ListNode* dummy = new ListNode(0);
    ListNode* tail = dummy;
    for (int val : vals) {
        tail->next = new ListNode(val);
        tail = tail->next;
    }
    ListNode* head = dummy->next;
    delete dummy;
    return head;
}

// Example usage:
int main() {
    ListNode* list1 = buildList({4, 2, 1, 3});
    ListNode* list2 = buildList({4, 2, 1, 3});
    ListNode* list3 = buildList({4, 2, 1, 3});
    ListNode* list4 = buildList({4, 2, 1, 3});
    ListNode* list5 = buildList({4, 2, 1, 3});

    Solution1 sol1;
    Solution2 sol2;
    Solution3 sol3;
    Solution4 sol4;
    Solution5 sol5;

    cout << "Solution1 Output:\n";
    printList(sol1.sortList(list1));
    cout << "Solution2 Output:\n";
    printList(sol2.sortList(list2));
    cout << "Solution3 Output:\n";
    printList(sol3.sortList(list3));
    cout << "Solution4 Output:\n";
    printList(sol4.sortList(list4));
    cout << "Solution5 Output:\n";
    printList(sol5.sortList(list5));

    return 0;
}